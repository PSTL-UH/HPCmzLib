#include <limits>
#include <algorithm>

#include "ChromatographicPeak.h"
#include "IsotopicEnvelope.h"
#include "Identification.h"
#include "SpectraFileInfo.h"
#include "IndexedMassSpectralPeak.h"
#include "../Chemistry/ClassExtensions.h"
#include "ProteinGroup.h"

using namespace Chemistry;

namespace FlashLFQ
{

    ChromatographicPeak::ChromatographicPeak(Identification *id, bool isMbrPeak,
                                             SpectraFileInfo *fileInfo) :
        spectraFileInfo(fileInfo), IsMbrPeak(isMbrPeak)
    {
        SplitRT = 0;
        setNumChargeStatesObserved(0);
        setMassError(NAN);
        setNumIdentificationsByBaseSeq(1);
        setNumIdentificationsByFullSeq(1);
        setIdentifications(std::vector<Identification*> {id});
        IsotopicEnvelopes = std::vector<IsotopicEnvelope*>();
    }

    IsotopicEnvelope *ChromatographicPeak::getApex() const
    {
        return privateApex;
    }

    void ChromatographicPeak::setApex(IsotopicEnvelope *value)
    {
        privateApex = value;
    }

    std::vector<Identification*> ChromatographicPeak::getIdentifications() const
    {
        return privateIdentifications;
    }

    void ChromatographicPeak::setIdentifications(const std::vector<Identification*> &value)
    {
        privateIdentifications = value;
    }

    int ChromatographicPeak::getNumChargeStatesObserved() const
    {
        return privateNumChargeStatesObserved;
    }

    void ChromatographicPeak::setNumChargeStatesObserved(int value)
    {
        privateNumChargeStatesObserved = value;
    }

    int ChromatographicPeak::getNumIdentificationsByBaseSeq() const
    {
        return privateNumIdentificationsByBaseSeq;
    }

    void ChromatographicPeak::setNumIdentificationsByBaseSeq(int value)
    {
        privateNumIdentificationsByBaseSeq = value;
    }

    int ChromatographicPeak::getNumIdentificationsByFullSeq() const
    {
        return privateNumIdentificationsByFullSeq;
    }

    void ChromatographicPeak::setNumIdentificationsByFullSeq(int value)
    {
        privateNumIdentificationsByFullSeq = value;
    }

    double ChromatographicPeak::getMassError() const
    {
        return privateMassError;
    }

    void ChromatographicPeak::setMassError(double value)
    {
        privateMassError = value;
    }

    std::string ChromatographicPeak::getTabSeparatedHeader()
    {
        auto sb = new StringBuilder();
        sb->append(std::string("File Name") + "\t");
        sb->append(std::string("Base Sequence") + "\t");
        sb->append(std::string("Full Sequence") + "\t");
        sb->append(std::string("Protein Group") + "\t");
        sb->append(std::string("Peptide Monoisotopic Mass") + "\t");
        sb->append(std::string("MS2 Retention Time") + "\t");
        sb->append(std::string("Precursor Charge") + "\t");
        sb->append(std::string("Theoretical MZ") + "\t");
        sb->append(std::string("Peak intensity") + "\t");
        sb->append(std::string("Peak RT Start") + "\t");
        sb->append(std::string("Peak RT Apex") + "\t");
        sb->append(std::string("Peak RT End") + "\t");
        sb->append(std::string("Peak MZ") + "\t");
        sb->append(std::string("Peak Charge") + "\t");
        sb->append(std::string("Num Charge States Observed") + "\t");
        sb->append(std::string("Peak Detection Type") + "\t");
        sb->append(std::string("PSMs Mapped") + "\t");
        sb->append(std::string("Base Sequences Mapped") + "\t");
        sb->append(std::string("Full Sequences Mapped") + "\t");
        sb->append(std::string("Peak Split Valley RT") + "\t");
        sb->append(std::string("Peak Apex Mass Error (ppm)") + "\t");
        //sb.Append("Timepoints");

        std::string s = sb->toString();
        delete sb;
        return s;
    }

    void ChromatographicPeak::CalculateIntensityForThisFeature(bool integrate)
    {
        if (!IsotopicEnvelopes.empty())
        {
#ifdef ORIG
            double maxIntensity = IsotopicEnvelopes.Max([&] (std::any p)
            {
                p::Intensity;
            });
#endif
            double maxIntensity = 0.0;
            for ( auto p : IsotopicEnvelopes ) {
                if ( p->getIntensity() > maxIntensity ) {
                    maxIntensity = p->getIntensity();
                }
            }
            
#ifdef ORIG
            setApex(IsotopicEnvelopes.First([&] (std::any p)
            {
                return p->Intensity == maxIntensity;
            }));
#endif
            for ( auto p : IsotopicEnvelopes ) {
                if ( p->getIntensity() == maxIntensity ) {
                    setApex(p);
                    break;
                }
            }

            if (integrate)
            {
#ifdef ORIG
                Intensity = IsotopicEnvelopes.Sum([&] (std::any p)
                {
                    p::Intensity;
                });
#endif
                Intensity = 0.0;
                for ( auto p: IsotopicEnvelopes ) {
                    Intensity += p->getIntensity();
                }
            }
            else
            {
                Intensity = getApex()->getIntensity();
            }

#ifdef ORIG
            setMassError(getIdentifications().Min([&] (std::any p)
            {
                return ((ClassExtensions::ToMass(getApex()->IndexedPeak->Mz,
                                                 getApex()->ChargeState) - p::monoisotopicMass) /
                        p::monoisotopicMass) * 1e6;
            }));
#endif
            double minval = std::numeric_limits<double>::max();
            for ( auto p: getIdentifications() ) {
                double cval = Chemistry::ClassExtensions::ToMass(getApex()->IndexedPeak->Mz,
                                        (getApex()->ChargeState - p->monoisotopicMass /
                                         p->monoisotopicMass )) * 1e6;
                if ( cval < minval ) {
                    minval = cval;
                }
            }
            setMassError ( minval);

#ifdef ORIG
            setNumChargeStatesObserved(IsotopicEnvelopes.Select([&] (std::any p)
            {
                p::ChargeState;
            }).Distinct()->Count());
#endif
            std::vector<IsotopicEnvelope*> sortedenvelopes = IsotopicEnvelopes;
            std::sort ( sortedenvelopes.begin(), sortedenvelopes.end(), [&] (IsotopicEnvelope* l, IsotopicEnvelope *r ) {
                    return l->ChargeState < r->ChargeState;
                });
             auto ip = std::unique ( sortedenvelopes.begin(), sortedenvelopes.end() );
             int size = std::distance (ip, sortedenvelopes.begin());
             setNumChargeStatesObserved ( size);
        }
        else
        {
            Intensity = 0;
            setMassError(NAN);
            setNumChargeStatesObserved(0);
            setApex(nullptr);
        }
    }

    void ChromatographicPeak::MergeFeatureWith(ChromatographicPeak *otherFeature, bool integrate)
    {
        if (otherFeature != this)
        {
#ifdef ORIG
            auto thisFeaturesPeaks = std::unordered_set<IndexedMassSpectralPeak*>(IsotopicEnvelopes.Select([&] (std::any p)
            {
                p::IndexedPeak;
            }));
#endif
            std::unordered_set<IndexedMassSpectralPeak*> thisFeaturesPeaks;
            for ( auto p : IsotopicEnvelopes ) {
                thisFeaturesPeaks.insert(p->IndexedPeak);
            }
            
#ifdef ORIG
            this->setIdentifications(this->getIdentifications().Union(otherFeature->getIdentifications())->Distinct().ToList());
#endif
            std::vector<Identification*> v;
            std::vector<Identification*>::iterator vit;
            vit = std::set_union(this->getIdentifications().begin(),
                                 this->getIdentifications().end(),
                                 otherFeature->getIdentifications().begin(),
                                 otherFeature->getIdentifications().end(),
                                 v.begin() );
            v.erase( vit, v.end() );
            this->setIdentifications(v);
            
            ResolveIdentifications();
#ifdef ORIG
            this->IsotopicEnvelopes.AddRange(otherFeature->IsotopicEnvelopes.Where([&] (std::any p)
            {
                !std::find(thisFeaturesPeaks.begin(), thisFeaturesPeaks.end(), p::IndexedPeak) != thisFeaturesPeaks.end();
            }));
#endif
            for ( auto p : IsotopicEnvelopes ) {
                if ( std::find(thisFeaturesPeaks.begin(), thisFeaturesPeaks.end(), p->IndexedPeak) == thisFeaturesPeaks.end() ) {
                    this->IsotopicEnvelopes.push_back( p);
                }
            }
            this->CalculateIntensityForThisFeature(integrate);
        }
    }

    void ChromatographicPeak::ResolveIdentifications()
    {
#ifdef ORIG
        this->setNumIdentificationsByBaseSeq(getIdentifications().Select([&] (std::any v)
        {
            v::BaseSequence;
        }).Distinct()->Count());
#endif
        std::vector<Identification*> sortedidents = getIdentifications();
        std::sort ( sortedidents.begin(), sortedidents.end(), [&] (Identification* l, Identification *r ) {
                    return l->BaseSequence < r->BaseSequence;
            });
        auto ip = std::unique ( sortedidents.begin(), sortedidents.end() );
        int size = std::distance (ip, sortedidents.begin());
        this->setNumIdentificationsByBaseSeq (size);
        
#ifdef ORIG
        this->setNumIdentificationsByFullSeq(getIdentifications().Select([&] (std::any v)
        {
            v::ModifiedSequence;
        }).Distinct()->Count());
#endif

        sortedidents.clear();
        sortedidents = getIdentifications();
        std::sort ( sortedidents.begin(), sortedidents.end(), [&] (Identification* l, Identification *r ) {
                    return l->ModifiedSequence < r->ModifiedSequence;
            });
        auto ip2 = std::unique ( sortedidents.begin(), sortedidents.end() );
        size = std::distance (ip2, sortedidents.begin());
        this->setNumIdentificationsByFullSeq(size);
    }

    std::string ChromatographicPeak::ToString()
    {
        StringBuilder *sb = new StringBuilder();
        sb->append(spectraFileInfo->FilenameWithoutExtension + "\t");
#ifdef ORIG
        sb->append(std::string::Join("|", getIdentifications().Select([&] (std::any p)
        {
            p::BaseSequence;
        }).Distinct()) + StringHelper::toString('\t'));
#endif
        std::vector<std::string> sts;
        for ( auto p: getIdentifications() ){
            if ( std::find(sts.begin(), sts.end(), p->BaseSequence) == sts.end() ) {
                sts.push_back(p->BaseSequence );
            }
        }
        sb->append(StringHelper::join(sts, '|') + StringHelper::toString('\t'));
        
#ifdef ORIG
        sb->append(std::string::Join("|", getIdentifications().Select([&] (std::any p)
        {
            p::ModifiedSequence;
        }).Distinct()) + StringHelper::toString('\t'));
#endif
        sts.clear();
        for ( auto p: getIdentifications() ){
            if ( std::find(sts.begin(), sts.end(), p->ModifiedSequence) == sts.end() ) {
                sts.push_back(p->ModifiedSequence );
            }
        }
        sb->append(StringHelper::join(sts, '|') + StringHelper::toString('\t'));
        
#ifdef ORIG
        auto t = getIdentifications().SelectMany([&] (std::any p)
        {
            p::proteinGroups->Select([&] (std::any v)
            {
                v::ProteinGroupName;
            });
        }).Distinct().OrderBy([&] (std::any p)
        {
            delete sb;
            return p;
        });
#endif
        std::vector<std::string> t;
        for ( Identification* p : getIdentifications() ) {
            for ( ProteinGroup* v: p->proteinGroups ) {
                t.push_back(v->ProteinGroupName );
            }
        }

        if (!t.empty())
        {
            sb->append(StringHelper::join(t, ';') + StringHelper::toString('\t'));
        }
        else
        {
            sb->append("" + StringHelper::toString('\t'));
        }

        sb->append("" + std::to_string(getIdentifications().front()->monoisotopicMass) + '\t');
        if (!IsMbrPeak)
        {
            sb->append("" + std::to_string(getIdentifications().front()->ms2RetentionTimeInMinutes) + '\t');
        }
        else
        {
            sb->append("" + StringHelper::toString('\t'));
        }

        sb->append("" + getIdentifications().front()->precursorChargeState + '\t');
        sb->append("" + std::to_string(Chemistry::ClassExtensions::ToMz(getIdentifications().front()->monoisotopicMass,
                                                             getIdentifications().front()->precursorChargeState)) + StringHelper::toString('\t'));
        sb->append("" + std::to_string(Intensity) + "\t");

        if (getApex() != nullptr)
        {
#ifdef ORIG
            sb->append("" + IsotopicEnvelopes.Select([&] (std::any p)
            {
                p::IndexedPeak::RetentionTime;
            }).Min() + "\t");
#endif
            double minval = std::numeric_limits<double>::max();
            double maxval =0.0;
            for ( auto p: IsotopicEnvelopes ) {
                if ( p->IndexedPeak->RetentionTime  < minval ) {
                    minval = p->IndexedPeak->RetentionTime;
                }
                if ( p->IndexedPeak->RetentionTime  > maxval ) {
                    maxval = p->IndexedPeak->RetentionTime;
                }
            }
            sb->append("" + std::to_string(minval) + "\t" );
            sb->append("" + std::to_string(getApex()->IndexedPeak->RetentionTime) + "\t");
#ifdef ORIG
            sb->append("" + IsotopicEnvelopes.Select([&] (std::any p)
            {
                p::IndexedPeak::RetentionTime;
            }).Max() + "\t");
#endif
            sb->append("" + std::to_string(maxval) + "\t");
            sb->append("" + std::to_string(getApex()->IndexedPeak->Mz) + "\t");
            sb->append("" + std::to_string(getApex()->ChargeState) + "\t");
        }
        else
        {
            sb->append(std::string("") + "-" + "\t");
            sb->append(std::string("") + "-" + "\t");
            sb->append(std::string("") + "-" + "\t");

            sb->append(std::string("") + "-" + "\t");
            sb->append(std::string("") + "-" + "\t");
        }

        sb->append("" + std::to_string(getNumChargeStatesObserved()) + "\t");

        if (IsMbrPeak)
        {
            sb->append(std::string("") + "MBR" + "\t");
        }
        else
        {
            sb->append(std::string("") + "MSMS" + "\t");
        }

        sb->append("" + std::to_string(getIdentifications().size()) + "\t");
        sb->append("" + std::to_string(getNumIdentificationsByBaseSeq()) + "\t");
        sb->append("" + std::to_string(getNumIdentificationsByFullSeq()) + "\t");
        sb->append("" + std::to_string(SplitRT) + "\t");
        sb->append("" + std::to_string(getMassError()) + "\t");
        //sb.Append(string.Join(",", IsotopicEnvelopes.OrderBy(p => p.ChargeState).ThenBy(p => p.IndexedPeak.ZeroBasedMs1ScanIndex).Select(p => p.ToString())));

        std::string s = sb->toString();
        delete sb;
        return s;
    }
}
