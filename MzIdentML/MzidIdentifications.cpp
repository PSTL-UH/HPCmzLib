#include "MzidIdentifications.h"
#include "mzIdentML110.h"
#include "mzIdentML111.h"
#include "mzIdentML120.h"
#include "../MzLibUtil/Tolerance.h"
#include "../MzLibUtil/AbsoluteTolerance.h"
#include "../MzLibUtil/PpmTolerance.h"

using namespace MassSpectrometry;
using namespace MzLibUtil;

namespace MzIdentML
{

    MzidIdentifications::MzidIdentifications(const std::string &mzidFile)
    {
        try
        {
            Stream stream = FileStream(mzidFile, FileMode::Open, FileAccess::Read, FileShare::Read);
            XmlSerializer *_indexedSerializer = new XmlSerializer(typeof(mzIdentML110::MzIdentMLType));
            // Read the XML file into the variable
            dd110 = dynamic_cast<mzIdentML110::MzIdentMLType*>(_indexedSerializer->Deserialize(stream));
            
            delete _indexedSerializer;
        }
        catch (...)
        {
            try
            {
                Stream stream = FileStream(mzidFile, FileMode::Open, FileAccess::Read, FileShare::Read);
                XmlSerializer *_indexedSerializer = new XmlSerializer(typeof(mzIdentML111::MzIdentMLType));
                // Read the XML file into the variable
                dd111 = dynamic_cast<mzIdentML111::MzIdentMLType*>(_indexedSerializer->Deserialize(stream));

                delete _indexedSerializer;
            }
            catch (...)
            {
                Stream stream = FileStream(mzidFile, FileMode::Open, FileAccess::Read, FileShare::Read);
                XmlSerializer *_indexedSerializer = new XmlSerializer(typeof(mzIdentML120::MzIdentMLType));
                // Read the XML file into the variable
                dd120 = dynamic_cast<mzIdentML120::MzIdentMLType*>(_indexedSerializer->Deserialize(stream));

                delete _indexedSerializer;
            }            
        }
    }

    Tolerance *MzidIdentifications::getParentTolerance() const
    {
        try
        {
            auto hm = dd110->AnalysisProtocolCollection().SpectrumIdentificationProtocol()[0].ParentTolerance();
            //AbsoluteTolerance tempVar(static_cast<double>(hm[0].value));
            AbsoluteTolerance tempVar(hm.get());
            return hm[0].unitName->Equals("dalton") ? static_cast<Tolerance*>(&tempVar): new PpmTolerance(static_cast<double>(hm[0].value));
        }
        catch (...)
        {
            try
            {
                auto hm = dd111->AnalysisProtocolCollection().SpectrumIdentificationProtocol()[0].ParentTolerance();
                AbsoluteTolerance tempVar2(static_cast<double>(hm[0].value));
                return hm[0].unitName->Equals("dalton") ? static_cast<Tolerance*>(&tempVar2): new PpmTolerance(static_cast<double>(hm[0].value));
            }
            catch (...)
            {
                auto hm = dd120->AnalysisProtocolCollection().SpectrumIdentificationProtocol()[0].ParentTolerance();
                AbsoluteTolerance tempVar3(static_cast<double>(hm[0].value));
                return hm[0].unitName->Equals("dalton") ? static_cast<Tolerance*>(&tempVar3): new PpmTolerance(static_cast<double>(hm[0].value));
            }
        }
    }

    Tolerance *MzidIdentifications::getFragmentTolerance() const
    {
        try
        {
            auto hm = dd110->AnalysisProtocolCollection().SpectrumIdentificationProtocol()[0].FragmentTolerance();
            AbsoluteTolerance tempVar(static_cast<double>(hm[0].value));
            return hm[0].unitName->Equals("dalton") ? static_cast<Tolerance*>(&tempVar): new PpmTolerance(static_cast<double>(hm[0].value));
        }
        catch (...)
        {
            try
            {
                auto hm = dd111->AnalysisProtocolCollection().SpectrumIdentificationProtocol()[0].FragmentTolerance();
                AbsoluteTolerance tempVar2(static_cast<double>(hm[0].value));
                return hm[0].unitName->Equals("dalton") ? static_cast<Tolerance*>(&tempVar2): new PpmTolerance(static_cast<double>(hm[0].value));
            }
            catch (...)
            {
                auto hm = dd120->AnalysisProtocolCollection().SpectrumIdentificationProtocol()[0].FragmentTolerance();
                AbsoluteTolerance tempVar3(static_cast<double>(hm[0].value));
                return hm[0].unitName->Equals("dalton") ? static_cast<Tolerance*>(&tempVar3): new PpmTolerance(static_cast<double>(hm[0].value));
            }
        }
    }

    int MzidIdentifications::getCount() const
    {
        try
        {
            return dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()->Count();
        }
        catch (...)
        {
            try
            {
                return dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()->Count();
            }
            catch (...)
            {
                return dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()->Count();
            }
        }
    }

    double MzidIdentifications::CalculatedMassToCharge(int sirIndex, int siiIndex)
    {
        try
        {
            return dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].calculatedMassToCharge();
        }
        catch (...)
        {
            try
            {
                return dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].calculatedMassToCharge();
            }
            catch (...)
            {
                return dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].calculatedMassToCharge();
            }
        }
    }

    int MzidIdentifications::ChargeState(int sirIndex, int siiIndex)
    {
        try
        {
            return dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].chargeState();
        }
        catch (...)
        {
            try
            {
                return dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].chargeState();
            }
            catch (...)
            {
                return dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].chargeState();
            }
        }
    }

    double MzidIdentifications::ExperimentalMassToCharge(int sirIndex, int siiIndex)
    {
        try
        {
            return dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].experimentalMassToCharge();
        }
        catch (...)
        {
            try
            {
                return dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].experimentalMassToCharge();
            }
            catch (...)
            {
                return dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].experimentalMassToCharge();
            }
        }
    }

    bool MzidIdentifications::IsDecoy(int sirIndex, int siiIndex)
    {
        //if any of the peptide evidences is decoy, is decoy
        try
        {
            for (mzIdentML110::PeptideEvidenceRefType *pe : dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef)
            {
                std::string peptideEvidenceRef = pe->peptideEvidence_ref();
                for (auto ok : dd110->SequenceCollection()->PeptideEvidence())
                {
                    if (ok->id->Equals(peptideEvidenceRef))
                    {
                        if (!ok->isDecoy)
                        {
                            return false;
                        }
                    }
                }
            }
            return true;
        }
        catch (...)
        {
            try
            {

                for (mzIdentML111::PeptideEvidenceRefType *pe : dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef)
                {
                    std::string peptideEvidenceRef = pe->peptideEvidence_ref();
                    for (auto ok : dd111->SequenceCollection()->PeptideEvidence())
                    {
                        //if (ok.id.Equals(peptideEvidenceRef))
                        //{
                        //    if (!ok.isDecoy) return false;
                        //}

                        if (ok->id->Equals(peptideEvidenceRef) && !ok->isDecoy)
                        {
                            return false;
                        }
                    }
                }
                return true;
            }
            catch (...)
            {
                for (mzIdentML120::PeptideEvidenceRefType *pe : dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef)
                {
                    std::string peptideEvidenceRef = pe->peptideEvidence_ref();
                    for (auto ok : dd120->SequenceCollection()->PeptideEvidence())
                    {
                        //if (ok.id.Equals(peptideEvidenceRef))
                        //{
                        //    if (!ok.isDecoy) return false;
                        //}

                        if (ok->id->Equals(peptideEvidenceRef) && !ok->isDecoy)
                        {
                            return false;
                        }

                    }
                }
                return true;
            }
        }
    }

    double MzidIdentifications::QValue(int sirIndex, int siiIndex)
    {
        try
        {
            auto cvParam = dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].cvParam().Where([&] (std::any cv)
            {
                return cv->accession == "MS:1002354";
            }).FirstOrDefault();
            return cvParam == nullptr ? -1 : static_cast<double>(cvParam->value);
        }
        catch (...)
        {
            try
            {
                auto cvParam = dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].cvParam().Where([&] (std::any cv)
                {
                    return cv->accession == "MS:1002354";
                }).FirstOrDefault();
                return cvParam == nullptr ? -1 : static_cast<double>(cvParam->value);
            }
            catch (...)
            {
                auto cvParam = dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].cvParam().Where([&] (std::any cv)
                {
                    return cv->accession == "MS:1002354";
                }).FirstOrDefault();
                return cvParam == nullptr ? -1 : static_cast<double>(cvParam->value);
            }

        }
    }

    int MzidIdentifications::NumPSMsFromScan(int sirIndex)
    {
        try
        {
            return dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem->Count([&] (std::any i)
            {
                return i != nullptr;
            });
        }
        catch (...)
        {
            try
            {
                return dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem->Count([&] (std::any i)
                {
                    return i != nullptr;
                });
            }
            catch (...)
            {
                return dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem->Count([&] (std::any i)
                {
                    return i != nullptr;
                });
            }
        }
    }

    std::string MzidIdentifications::ModificationAcession(int sirIndex, int siiIndex, int i)
    {
        std::string s = "";
        try
        {
            std::string peptideEvidenceRef = dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef[0].peptideEvidence_ref;
            for (auto ok : dd110->SequenceCollection()->PeptideEvidence())
            {
                if (ok->id->Equals(peptideEvidenceRef))
                {
                    for (auto ok2 : dd110->SequenceCollection()->Peptide())
                    {
                        if (ok2->id->Equals(ok->peptide_ref))
                        {
                            s = ok2->Modification[i].cvParam()[0].accession;
                            break;
                        }
                    }
                }
            }
        }
        catch (...)
        {
            try
            {
                std::string peptideEvidenceRef = dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef[0].peptideEvidence_ref;
                for (auto ok : dd111->SequenceCollection()->PeptideEvidence())
                {
                    if (ok->id->Equals(peptideEvidenceRef))
                    {
                        for (auto ok2 : dd111->SequenceCollection()->Peptide())
                        {
                            if (ok2->id->Equals(ok->peptide_ref))
                            {
                                s = ok2->Modification[i].cvParam()[0].accession;
                                break;
                            }
                        }
                    }
                }
            }
            catch (...)
            {
                std::string peptideEvidenceRef = dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef[0].peptideEvidence_ref;
                for (auto ok : dd120->SequenceCollection()->PeptideEvidence())
                {
                    if (ok->id->Equals(peptideEvidenceRef))
                    {
                        for (auto ok2 : dd120->SequenceCollection()->Peptide())
                        {
                            if (ok2->id->Equals(ok->peptide_ref))
                            {
                                s = ok2->Modification[i].cvParam()[0].accession;
                                break;
                            }
                        }
                    }
                }
            }


        }
        return s;
    }

    std::string MzidIdentifications::ModificationValue(int sirIndex, int siiIndex, int i)
    {
        std::string s = "";
        try
        {
            std::string peptideEvidenceRef = dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef[0].peptideEvidence_ref;
            for (auto ok : dd110->SequenceCollection()->PeptideEvidence())
            {
                if (ok->id->Equals(peptideEvidenceRef))
                {
                    for (auto ok2 : dd110->SequenceCollection()->Peptide())
                    {
                        if (ok2->id->Equals(ok->peptide_ref))
                        {
                            s = ok2->Modification[i].cvParam()[0].value;
                            break;
                        }
                    }
                }
            }
        }
        catch (...)
        {
            try
            {
                std::string peptideEvidenceRef = dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef[0].peptideEvidence_ref;
                for (auto ok : dd111->SequenceCollection()->PeptideEvidence())
                {
                    if (ok->id->Equals(peptideEvidenceRef))
                    {
                        for (auto ok2 : dd111->SequenceCollection()->Peptide())
                        {
                            if (ok2->id->Equals(ok->peptide_ref))
                            {
                                s = ok2->Modification[i].cvParam()[0].value;
                                break;
                            }
                        }
                    }
                }
            }
            catch (...)
            {
                std::string peptideEvidenceRef = dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef[0].peptideEvidence_ref;
                for (auto ok : dd120->SequenceCollection()->PeptideEvidence())
                {
                    if (ok->id->Equals(peptideEvidenceRef))
                    {
                        for (auto ok2 : dd120->SequenceCollection()->Peptide())
                        {
                            if (ok2->id->Equals(ok->peptide_ref))
                            {
                                s = ok2->Modification[i].cvParam()[0].value;
                                break;
                            }
                        }
                    }
                }
            }

        }
        return s;
    }

    std::string MzidIdentifications::ModificationDictionary(int sirIndex, int siiIndex, int i)
    {
        std::string s = "";
        try
        {
            std::string peptideEvidenceRef = dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef[0].peptideEvidence_ref;
            for (auto ok : dd110->SequenceCollection()->PeptideEvidence())
            {
                if (ok->id->Equals(peptideEvidenceRef))
                {
                    for (auto ok2 : dd110->SequenceCollection()->Peptide())
                    {
                        if (ok2->id->Equals(ok->peptide_ref))
                        {
                            s = ok2->Modification[i].cvParam()[0].cvRef;
                            break;
                        }
                    }
                }
            }
        }
        catch (...)
        {
            try
            {
                std::string peptideEvidenceRef = dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef[0].peptideEvidence_ref;
                for (auto ok : dd111->SequenceCollection()->PeptideEvidence())
                {
                    if (ok->id->Equals(peptideEvidenceRef))
                    {
                        for (auto ok2 : dd111->SequenceCollection()->Peptide())
                        {
                            if (ok2->id->Equals(ok->peptide_ref))
                            {
                                s = ok2->Modification[i].cvParam()[0].cvRef;
                                break;
                            }
                        }
                    }
                }
            }
            catch (...)
            {
                std::string peptideEvidenceRef = dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef[0].peptideEvidence_ref;
                for (auto ok : dd120->SequenceCollection()->PeptideEvidence())
                {
                    if (ok->id->Equals(peptideEvidenceRef))
                    {
                        for (auto ok2 : dd120->SequenceCollection()->Peptide())
                        {
                            if (ok2->id->Equals(ok->peptide_ref))
                            {
                                s = ok2->Modification[i].cvParam()[0].cvRef;
                                break;
                            }
                        }
                    }
                }
            }

        }
        return s;
    }

    int MzidIdentifications::ModificationLocation(int sirIndex, int siiIndex, int i)
    {
        int modLoc = -1;
        try
        {
            std::string peptideEvidenceRef = dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef[0].peptideEvidence_ref;
            for (auto ok : dd110->SequenceCollection()->PeptideEvidence())
            {
                if (ok->id->Equals(peptideEvidenceRef))
                {
                    for (auto ok2 : dd110->SequenceCollection()->Peptide())
                    {
                        if (ok2->id->Equals(ok->peptide_ref))
                        {
                            modLoc = ok2->Modification[i].location;
                            break;
                        }
                    }
                }
            }
        }
        catch (...)
        {
            try
            {
                std::string peptideEvidenceRef = dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef[0].peptideEvidence_ref;
                for (auto ok : dd111->SequenceCollection()->PeptideEvidence())
                {
                    if (ok->id->Equals(peptideEvidenceRef))
                    {
                        for (auto ok2 : dd111->SequenceCollection()->Peptide())
                        {
                            if (ok2->id->Equals(ok->peptide_ref))
                            {
                                modLoc = ok2->Modification[i].location;
                                break;
                            }
                        }
                    }
                }
            }
            catch (...)
            {
                std::string peptideEvidenceRef = dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef[0].peptideEvidence_ref;
                for (auto ok : dd120->SequenceCollection()->PeptideEvidence())
                {
                    if (ok->id->Equals(peptideEvidenceRef))
                    {
                        for (auto ok2 : dd120->SequenceCollection()->Peptide())
                        {
                            if (ok2->id->Equals(ok->peptide_ref))
                            {
                                modLoc = ok2->Modification[i].location;
                                break;
                            }
                        }
                    }
                }
            }

        }
        return modLoc;
    }

    double MzidIdentifications::ModificationMass(int sirIndex, int siiIndex, int i)
    {
        double modMass = -1;
        try
        {
            std::string peptideEvidenceRef = dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef[0].peptideEvidence_ref;
            for (auto ok : dd110->SequenceCollection()->PeptideEvidence())
            {
                if (ok->id->Equals(peptideEvidenceRef))
                {
                    for (auto ok2 : dd110->SequenceCollection()->Peptide())
                    {
                        if (ok2->id->Equals(ok->peptide_ref))
                        {
                            modMass = ok2->Modification[i].monoisotopicMassDelta;
                            break;
                        }
                    }
                }
            }
        }
        catch (...)
        {
            try
            {
                std::string peptideEvidenceRef = dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef[0].peptideEvidence_ref;
                for (auto ok : dd111->SequenceCollection()->PeptideEvidence())
                {
                    if (ok->id->Equals(peptideEvidenceRef))
                    {
                        for (auto ok2 : dd111->SequenceCollection()->Peptide())
                        {
                            if (ok2->id->Equals(ok->peptide_ref))
                            {
                                modMass = ok2->Modification[i].monoisotopicMassDelta;
                                break;
                            }
                        }
                    }
                }
            }
            catch (...)
            {
                std::string peptideEvidenceRef = dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef[0].peptideEvidence_ref;
                for (auto ok : dd120->SequenceCollection()->PeptideEvidence())
                {
                    if (ok->id->Equals(peptideEvidenceRef))
                    {
                        for (auto ok2 : dd120->SequenceCollection()->Peptide())
                        {
                            if (ok2->id->Equals(ok->peptide_ref))
                            {
                                modMass = ok2->Modification[i].monoisotopicMassDelta;
                                break;
                            }
                        }
                    }
                }
            }

        }
        return modMass;
    }

    int MzidIdentifications::NumModifications(int sirIndex, int siiIndex)
    {
        int numMod = 0;
        try
        {
            std::string peptideEvidenceRef = dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef[0].peptideEvidence_ref;
            for (auto ok : dd110->SequenceCollection()->PeptideEvidence())
            {
                if (ok->id->Equals(peptideEvidenceRef))
                {
                    for (auto ok2 : dd110->SequenceCollection()->Peptide())
                    {
                        if (ok2->id->Equals(ok->peptide_ref))
                        {
                            if (ok2->Modification == nullptr)
                            {
                                break;
                            }
                            numMod = ok2->Modification->Length;
                            break;
                        }
                    }
                }
            }
        }
        catch (...)
        {
            try
            {
                std::string peptideEvidenceRef = dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef[0].peptideEvidence_ref;
                for (auto ok : dd111->SequenceCollection()->PeptideEvidence())
                {
                    if (ok->id->Equals(peptideEvidenceRef))
                    {
                        for (auto ok2 : dd111->SequenceCollection()->Peptide())
                        {
                            if (ok2->id->Equals(ok->peptide_ref))
                            {
                                if (ok2->Modification == nullptr)
                                {
                                    break;
                                }
                                numMod = ok2->Modification->Length;
                                break;
                            }
                        }
                    }
                }
            }
            catch (...)
            {
                std::string peptideEvidenceRef = dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef[0].peptideEvidence_ref;
                for (auto ok : dd120->SequenceCollection()->PeptideEvidence())
                {
                    if (ok->id->Equals(peptideEvidenceRef))
                    {
                        for (auto ok2 : dd120->SequenceCollection()->Peptide())
                        {
                            if (ok2->id->Equals(ok->peptide_ref))
                            {
                                if (ok2->Modification == nullptr)
                                {
                                    break;
                                }
                                numMod = ok2->Modification->Length;
                                break;
                            }
                        }
                    }
                }
            }

        }
        return numMod;
    }

    std::string MzidIdentifications::PeptideSequenceWithoutModifications(int sirIndex, int siiIndex)
    {
        std::string s = "";
        try
        {
            std::string peptideEvidenceRef = dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef[0].peptideEvidence_ref;
            for (auto ok : dd110->SequenceCollection()->PeptideEvidence())
            {
                if (ok->id->Equals(peptideEvidenceRef))
                {
                    for (auto ok2 : dd110->SequenceCollection()->Peptide())
                    {
                        if (ok2->id->Equals(ok->peptide_ref))
                        {
                            s = ok2->PeptideSequence;
                            break;
                        }
                    }
                }
            }
        }
        catch (...)
        {
            try
            {
                std::string peptideEvidenceRef = dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef[0].peptideEvidence_ref;
                for (auto ok : dd111->SequenceCollection()->PeptideEvidence())
                {
                    if (ok->id->Equals(peptideEvidenceRef))
                    {
                        for (auto ok2 : dd111->SequenceCollection()->Peptide())
                        {
                            if (ok2->id->Equals(ok->peptide_ref))
                            {
                                s = ok2->PeptideSequence;
                                break;
                            }
                        }
                    }
                }
            }
            catch (...)
            {
                std::string peptideEvidenceRef = dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef[0].peptideEvidence_ref;
                for (auto ok : dd120->SequenceCollection()->PeptideEvidence())
                {
                    if (ok->id->Equals(peptideEvidenceRef))
                    {
                        for (auto ok2 : dd120->SequenceCollection()->Peptide())
                        {
                            if (ok2->id->Equals(ok->peptide_ref))
                            {
                                s = ok2->PeptideSequence;
                                break;
                            }
                        }
                    }
                }
            }

        }
        return s;
    }

    std::string MzidIdentifications::Ms2SpectrumID(int sirIndex)
    {
        std::string ms2id = "";
        try
        {
            if (dd110->DataCollection().Inputs().SpectraData()[0].FileFormat.cvParam().name->Equals("Thermo RAW format") || dd110->DataCollection().Inputs().SpectraData()[0].FileFormat.cvParam().name->Equals("mzML format"))
            {
                ms2id = dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].spectrumID();
            }
            else if (dd110->DataCollection().Inputs().SpectraData()[0].FileFormat.cvParam().name->Equals("Mascot MGF format"))
            {
                ms2id = dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].cvParam()[0].value;
            }
        }
        catch (...)
        {
            try
            {
                if (dd111->DataCollection().Inputs().SpectraData()[0].FileFormat.cvParam().name->Equals("Thermo RAW format") || dd111->DataCollection().Inputs().SpectraData()[0].FileFormat.cvParam().name->Equals("mzML format"))
                {
                    ms2id = dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].spectrumID();
                }
                else if (dd111->DataCollection().Inputs().SpectraData()[0].FileFormat.cvParam().name->Equals("Mascot MGF format"))
                {
                    ms2id = dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].cvParam()[0].value;
                }
            }
            catch (...)
            {
                if (dd120->DataCollection().Inputs().SpectraData()[0].FileFormat.cvParam().name->Equals("Thermo RAW format") || dd120->DataCollection().Inputs().SpectraData()[0].FileFormat.cvParam().name->Equals("mzML format"))
                {
                    ms2id = dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].spectrumID();
                }
                else if (dd120->DataCollection().Inputs().SpectraData()[0].FileFormat.cvParam().name->Equals("Mascot MGF format"))
                {
                    ms2id = dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].cvParam()[0].value;
                }
            }


        }
        return ms2id;
    }

    std::vector<float> MzidIdentifications::MatchedIons(int sirIndex, int siiIndex, int i)
    {
        try
        {
            return dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].Fragmentation()[i].FragmentArray[0].values;
        }
        catch (...)
        {
            try
            {
                return dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].Fragmentation()[i].FragmentArray[0].values;
            }
            catch (...)
            {
                return dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].Fragmentation()[i].FragmentArray[0].values;
            }
        }
    }

    int MzidIdentifications::MatchedIonCounts(int sirIndex, int siiIndex, int i)
    {
        try
        {
            return dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].Fragmentation()[i].FragmentArray[0].values->Length;
        }
        catch (...)
        {
            try
            {
                return dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].Fragmentation()[i].FragmentArray[0].values->Length;
            }
            catch (...)
            {
                return dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].Fragmentation()[i].FragmentArray[0].values->Length;
            }
        }
    }

    std::string MzidIdentifications::ProteinAccession(int sirIndex, int siiIndex)
    {
        std::string s = "";

        try
        {
            std::string peptideEvidenceRef = dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef()[0].peptideEvidence_ref;
            for (auto ok : dd110->SequenceCollection()->PeptideEvidence())
            {
                if (ok->id->Equals(peptideEvidenceRef))
                {
                    for (auto ok2 : dd110->SequenceCollection()->DBSequence())
                    {
                        if (ok2->id->Equals(ok->dBSequence_ref))
                        {
                            s = ok2->accession;
                            break;
                        }
                    }
                }
            }
        }
        catch (...)
        {
            try
            {
                std::string peptideEvidenceRef = dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef()[0].peptideEvidence_ref;
                for (auto ok : dd111->SequenceCollection()->PeptideEvidence())
                {
                    if (ok->id->Equals(peptideEvidenceRef))
                    {
                        for (auto ok2 : dd111->SequenceCollection()->DBSequence())
                        {
                            if (ok2->id->Equals(ok->dBSequence_ref))
                            {
                                s = ok2->accession;
                                break;
                            }
                        }
                    }
                }
            }
            catch (...)
            {
                std::string peptideEvidenceRef = dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef()[0].peptideEvidence_ref;
                for (auto ok : dd120->SequenceCollection()->PeptideEvidence())
                {
                    if (ok->id->Equals(peptideEvidenceRef))
                    {
                        for (auto ok2 : dd120->SequenceCollection()->DBSequence())
                        {
                            if (ok2->id->Equals(ok->dBSequence_ref))
                            {
                                s = ok2->accession;
                                break;
                            }
                        }
                    }
                }
            }

        }
        return s;
    }

    std::string MzidIdentifications::ProteinFullName(int sirIndex, int siiIndex)
    {
        std::string s = "";

        try
        {
            for (mzIdentML110::PeptideEvidenceRefType *pe : dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef())
            {
                std::string peptideEvidenceRef = pe->peptideEvidence_ref();
                for (auto ok : dd110->SequenceCollection()->PeptideEvidence())
                {
                    if (ok->id->Equals(peptideEvidenceRef))
                    {
                        for (auto ok2 : dd110->SequenceCollection()->DBSequence())
                        {
                            if (ok2->id->Equals(ok->dBSequence_ref))
                            {
                                if (s.length() != 0)
                                {
                                    s += " or ";
                                }
                                s += ok2->name;
                                break;
                            }
                        }
                    }
                }
            }
        }
        catch (...)
        {
            try
            {
                for (mzIdentML111::PeptideEvidenceRefType *pe : dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef())
                {
                    std::string peptideEvidenceRef = pe->peptideEvidence_ref();
                    for (auto ok : dd111->SequenceCollection()->PeptideEvidence())
                    {
                        if (ok->id->Equals(peptideEvidenceRef))
                        {
                            for (auto ok2 : dd111->SequenceCollection()->DBSequence())
                            {
                                if (ok2->id->Equals(ok->dBSequence_ref))
                                {
                                    if (s.length() != 0)
                                    {
                                        s += " or ";
                                    }
                                    s += ok2->name;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            catch (...)
            {
                for (mzIdentML120::PeptideEvidenceRefType *pe : dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef())
                {
                    std::string peptideEvidenceRef = pe->peptideEvidence_ref();
                    for (auto ok : dd120->SequenceCollection()->PeptideEvidence())
                    {
                        if (ok->id->Equals(peptideEvidenceRef))
                        {
                            for (auto ok2 : dd120->SequenceCollection()->DBSequence())
                            {
                                if (ok2->id->Equals(ok->dBSequence_ref))
                                {
                                    if (s.length() != 0)
                                    {
                                        s += " or ";
                                    }
                                    s += ok2->name;
                                    break;
                                }
                            }
                        }
                    }
                }
            }

        }
        return s;
    }

    std::string MzidIdentifications::StartResidueInProtein(int sirIndex, int siiIndex)
    {
        std::string startResidue = "";
        try
        {
            for (mzIdentML110::PeptideEvidenceRefType *pe : dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef()
            {
                std::string peptideEvidenceRef = pe->peptideEvidence_ref();
                for (auto ok : dd110->SequenceCollection()->PeptideEvidence())
                {
                    if (ok->id->Equals(peptideEvidenceRef))
                    {
                        if (startResidue.length() != 0)
                        {
                            startResidue += " or ";
                        }
                        startResidue += ok->start;
                        break;
                    }
                }
            }
        }
        catch (...)
        {
            try
            {

                for (mzIdentML111::PeptideEvidenceRefType *pe : dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef())
                {
                    std::string peptideEvidenceRef = pe->peptideEvidence_ref();
                    for (auto ok : dd111->SequenceCollection()->PeptideEvidence())
                    {
                        if (ok->id->Equals(peptideEvidenceRef))
                        {
                            if (startResidue.length() != 0)
                            {
                                startResidue += " or ";
                            }
                            startResidue += ok->start;
                            break;
                        }
                    }
                }
            }
            catch (...)
            {
                for (mzIdentML120::PeptideEvidenceRefType *pe : dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef())
                {
                    std::string peptideEvidenceRef = pe->peptideEvidence_ref();
                    for (auto ok : dd120->SequenceCollection()->PeptideEvidence())
                    {
                        if (ok->id->Equals(peptideEvidenceRef))
                        {
                            if (startResidue.length() != 0)
                            {
                                startResidue += " or ";
                            }
                            startResidue += ok->start;
                            break;
                        }
                    }
                }
            }

        }
        return startResidue;
    }

    std::string MzidIdentifications::EndResidueInProtein(int sirIndex, int siiIndex)
    {
        std::string endResidue = "";
        try
        {
            for (mzIdentML110::PeptideEvidenceRefType *pe : dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef())
            {
                std::string peptideEvidenceRef = pe->peptideEvidence_ref();
                for (auto ok : dd110->SequenceCollection()->PeptideEvidence())
                {
                    if (ok->id->Equals(peptideEvidenceRef))
                    {
                        if (endResidue.length() != 0)
                        {
                            endResidue += " or ";
                        }
                        endResidue += ok->end;
                        break;
                    }
                }
            }
        }
        catch (...)
        {
            try
            {
                for (mzIdentML111::PeptideEvidenceRefType *pe : dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef())
                {
                    std::string peptideEvidenceRef = pe->peptideEvidence_ref();
                    for (auto ok : dd111->SequenceCollection()->PeptideEvidence())
                    {
                        if (ok->id->Equals(peptideEvidenceRef))
                        {
                            if (endResidue.length() != 0)
                            {
                                endResidue += " or ";
                            }
                            endResidue += ok->end;
                            break;
                        }
                    }
                }
            }
            catch (...)
            {
                for (mzIdentML120::PeptideEvidenceRefType *pe : dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef())
                {
                    std::string peptideEvidenceRef = pe->peptideEvidence_ref();
                    for (auto ok : dd120->SequenceCollection()->PeptideEvidence())
                    {
                        if (ok->id->Equals(peptideEvidenceRef))
                        {
                            if (endResidue.length() != 0)
                            {
                                endResidue += " or ";
                            }
                            endResidue += ok->end;
                            break;
                        }
                    }
                }
            }

        }
        return endResidue;
    }
}
