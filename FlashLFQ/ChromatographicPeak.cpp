#include "ChromatographicPeak.h"
#include "IsotopicEnvelope.h"
#include "Identification.h"
#include "SpectraFileInfo.h"
#include "IndexedMassSpectralPeak.h"
#include "../Chemistry/ClassExtensions.h"

using namespace Chemistry;

namespace FlashLFQ
{

    ChromatographicPeak::ChromatographicPeak(Identification *id, bool isMbrPeak, SpectraFileInfo *fileInfo) : SpectraFileInfo(fileInfo), IsMbrPeak(isMbrPeak)
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

        delete sb;
        return sb->toString();
    }

    void ChromatographicPeak::CalculateIntensityForThisFeature(bool integrate)
    {
        if (IsotopicEnvelopes.Any())
        {
            double maxIntensity = IsotopicEnvelopes.Max([&] (std::any p)
            {
                p::Intensity;
            });
            setApex(IsotopicEnvelopes.First([&] (std::any p)
            {
                return p->Intensity == maxIntensity;
            }));

            if (integrate)
            {
                Intensity = IsotopicEnvelopes.Sum([&] (std::any p)
                {
                    p::Intensity;
                });
            }
            else
            {
                Intensity = getApex()->getIntensity();
            }

            setMassError(getIdentifications().Min([&] (std::any p)
            {
                return ((ClassExtensions::ToMass(getApex()->IndexedPeak->Mz, getApex()->ChargeState) - p::monoisotopicMass) / p::monoisotopicMass) * 1e6;
            }));
            setNumChargeStatesObserved(IsotopicEnvelopes.Select([&] (std::any p)
            {
                p::ChargeState;
            }).Distinct()->Count());
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
            auto thisFeaturesPeaks = std::unordered_set<IndexedMassSpectralPeak*>(IsotopicEnvelopes.Select([&] (std::any p)
            {
                p::IndexedPeak;
            }));
            this->setIdentifications(this->getIdentifications().Union(otherFeature->getIdentifications())->Distinct().ToList());
            ResolveIdentifications();
            this->IsotopicEnvelopes.AddRange(otherFeature->IsotopicEnvelopes.Where([&] (std::any p)
            {
                !std::find(thisFeaturesPeaks.begin(), thisFeaturesPeaks.end(), p::IndexedPeak) != thisFeaturesPeaks.end();
            }));
            this->CalculateIntensityForThisFeature(integrate);
        }
    }

    void ChromatographicPeak::ResolveIdentifications()
    {
        this->setNumIdentificationsByBaseSeq(getIdentifications().Select([&] (std::any v)
        {
            v::BaseSequence;
        }).Distinct()->Count());
        this->setNumIdentificationsByFullSeq(getIdentifications().Select([&] (std::any v)
        {
            v::ModifiedSequence;
        }).Distinct()->Count());
    }

    std::string ChromatographicPeak::ToString()
    {
        StringBuilder *sb = new StringBuilder();
        sb->append(SpectraFileInfo->FilenameWithoutExtension + "\t");
        sb->append(std::string::Join("|", getIdentifications().Select([&] (std::any p)
        {
            p::BaseSequence;
        }).Distinct()) + StringHelper::toString('\t'));
        sb->append(std::string::Join("|", getIdentifications().Select([&] (std::any p)
        {
            p::ModifiedSequence;
        }).Distinct()) + StringHelper::toString('\t'));

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
        if (t->Any())
        {
            sb->append(std::string::Join(";", t) + StringHelper::toString('\t'));
        }
        else
        {
            sb->append("" + StringHelper::toString('\t'));
        }

        sb->append("" + getIdentifications().front().monoisotopicMass + '\t');
        if (!IsMbrPeak)
        {
            sb->append("" + getIdentifications().front().ms2RetentionTimeInMinutes + '\t');
        }
        else
        {
            sb->append("" + StringHelper::toString('\t'));
        }

        sb->append("" + getIdentifications().front().precursorChargeState + '\t');
        sb->append("" + std::to_string(ClassExtensions::ToMz(getIdentifications().front().monoisotopicMass, getIdentifications().front().precursorChargeState)) + StringHelper::toString('\t'));
        sb->append("" + std::to_string(Intensity) + "\t");

        if (getApex() != nullptr)
        {
            sb->append("" + IsotopicEnvelopes.Select([&] (std::any p)
            {
                p::IndexedPeak::RetentionTime;
            }).Min() + "\t");
            sb->append("" + std::to_string(getApex()->IndexedPeak->RetentionTime) + "\t");
            sb->append("" + IsotopicEnvelopes.Select([&] (std::any p)
            {
                p::IndexedPeak::RetentionTime;
            }).Max() + "\t");

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

        delete sb;
        return sb->toString();
    }
}
