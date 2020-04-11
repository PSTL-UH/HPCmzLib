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
            //Stream stream = FileStream(mzidFile, FileMode::Open, FileAccess::Read, FileShare::Read);
            //XmlSerializer *_indexedSerializer = new XmlSerializer(typeof(mzIdentML110::MzIdentMLType));
            // Read the XML file into the variable
            //dd110 = dynamic_cast<mzIdentML110::MzIdentMLType*>(_indexedSerializer->Deserialize(stream));
            
            //delete _indexedSerializer;
            _type = MzidIdentType::v110;
        }
        catch (...)
        {
            try
            {
                //Stream stream = FileStream(mzidFile, FileMode::Open, FileAccess::Read, FileShare::Read);
                //XmlSerializer *_indexedSerializer = new XmlSerializer(typeof(mzIdentML111::MzIdentMLType));
                // Read the XML file into the variable
                //dd111 = dynamic_cast<mzIdentML111::MzIdentMLType*>(_indexedSerializer->Deserialize(stream));
                
                //delete _indexedSerializer;
                _type = MzidIdentType::v111;
            }
            catch (...)
            {
                //Stream stream = FileStream(mzidFile, FileMode::Open, FileAccess::Read, FileShare::Read);
                //XmlSerializer *_indexedSerializer = new XmlSerializer(typeof(mzIdentML120::MzIdentMLType));
                // Read the XML file into the variable
                //dd120 = dynamic_cast<mzIdentML120::MzIdentMLType*>(_indexedSerializer->Deserialize(stream));
                
                //delete _indexedSerializer;
                _type = MzidIdentType::v120;
            }            
        }
    }
    
    Tolerance *MzidIdentifications::getParentTolerance() const
    {
        if ( _type == MzidIdentType::v110 ) {
#ifdef ORIG
            auto hm = dd110->AnalysisProtocolCollection().SpectrumIdentificationProtocol()[0].ParentTolerance();
            AbsoluteTolerance tempVar(static_cast<double>(hm[0].value));
            return hm[0].unitName->Equals("dalton") ? static_cast<Tolerance*>(&tempVar): new PpmTolerance(static_cast<double>(hm[0].value));
#endif
            auto hm = dd110->AnalysisProtocolCollection().SpectrumIdentificationProtocol()[0].ParentTolerance().get().cvParam()[0];
            if ( hm.unitName().get()=="dalton" ) {
                auto tempVar = new AbsoluteTolerance (std::stod(hm.value().get()));
                return static_cast<Tolerance*>(tempVar);
            }
            return new PpmTolerance(std::stod((hm.value().get())));
        }
        else if ( _type == MzidIdentType::v111)  {
            auto hm = dd111->AnalysisProtocolCollection().SpectrumIdentificationProtocol()[0].ParentTolerance().get().cvParam()[0];
            if ( hm.unitName().get()=="dalton" ) {
                auto tempVar = new AbsoluteTolerance (std::stod(hm.value().get()));
                return static_cast<Tolerance*>(tempVar);
            }
            return new PpmTolerance(std::stod((hm.value().get())));
        }
        else if ( _type == MzidIdentType::v120 ) {
            auto hm = dd120->AnalysisProtocolCollection().SpectrumIdentificationProtocol()[0].ParentTolerance().get().cvParam()[0];
            if ( hm.unitName().get()=="dalton" ) {
                auto tempVar = new AbsoluteTolerance (std::stod(hm.value().get()));
                return static_cast<Tolerance*>(tempVar);
            }
            return new PpmTolerance(std::stod((hm.value().get())));
        }
    }
    
    Tolerance *MzidIdentifications::getFragmentTolerance() const
    {
        if ( _type == MzidIdentType::v110 ) {
#ifdef ORIG
            auto hm = dd110->AnalysisProtocolCollection().SpectrumIdentificationProtocol()[0].FragmentTolerance();
            //AbsoluteTolerance tempVar(static_cast<double>(hm[0].value));
            return hm[0].unitName->Equals("dalton") ? static_cast<Tolerance*>(&tempVar): new PpmTolerance(static_cast<double>(hm[0].value));
#endif
            auto hm = dd110->AnalysisProtocolCollection().SpectrumIdentificationProtocol()[0].FragmentTolerance().get().cvParam()[0];
            if ( hm.unitName().get()=="dalton" ) {
                auto tempVar = new AbsoluteTolerance (std::stod(hm.value().get()));
                return static_cast<Tolerance*>(tempVar);
            }
            return new PpmTolerance(std::stod((hm.value().get())));
        }
        else if ( _type == MzidIdentType::v111 ) {
            auto hm = dd111->AnalysisProtocolCollection().SpectrumIdentificationProtocol()[0].FragmentTolerance().get().cvParam()[0];
            if ( hm.unitName().get()=="dalton" ) {
                auto tempVar = new AbsoluteTolerance (std::stod(hm.value().get()));
                return static_cast<Tolerance*>(tempVar);
            }
            return new PpmTolerance(std::stod((hm.value().get())));
        }
        else if ( _type == MzidIdentType::v120 ) { 
            auto hm = dd120->AnalysisProtocolCollection().SpectrumIdentificationProtocol()[0].FragmentTolerance().get().cvParam()[0];
            if ( hm.unitName().get()=="dalton" ) {
                auto tempVar = new AbsoluteTolerance (std::stod(hm.value().get()));
                return static_cast<Tolerance*>(tempVar);
            }
            return new PpmTolerance(std::stod((hm.value().get())));
        }
    }
    
    int MzidIdentifications::getCount() const
    {
        if ( _type == MzidIdentType::v110 ) {
            return dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult().size();
        }
        else if ( _type == MzidIdentType::v111 ) {
            return dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult().size();
        }
        else if ( _type == MzidIdentType::v120 ) {
            return dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult().size();
        }
    }
    
    double MzidIdentifications::CalculatedMassToCharge(int sirIndex, int siiIndex)
    {
        if ( _type == MzidIdentType::v110 ) {
            return dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].calculatedMassToCharge().get();
        }
        else if ( _type == MzidIdentType::v111 ) {
            return dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].calculatedMassToCharge().get();
        }
        else if ( _type == MzidIdentType::v120 ) { 
            return dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].calculatedMassToCharge().get();
        }
    }

    int MzidIdentifications::ChargeState(int sirIndex, int siiIndex)
    {
        if ( _type == MzidIdentType::v110 ) {
            return dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].chargeState();
        }
        else if ( _type == MzidIdentType::v111 ) {
            return dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].chargeState();
        }
        else if ( _type == MzidIdentType::v120 ) {
            return dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].chargeState();
        }
    }

    double MzidIdentifications::ExperimentalMassToCharge(int sirIndex, int siiIndex)
    {
        if ( _type == MzidIdentType::v110 ) {
            return dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].experimentalMassToCharge();
        }
        else if ( _type == MzidIdentType::v111 ) {
            return dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].experimentalMassToCharge();
        }
        else if ( _type == MzidIdentType::v120 ) {
            return dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].experimentalMassToCharge();
        }
    }

    bool MzidIdentifications::IsDecoy(int sirIndex, int siiIndex)
    {
        //if any of the peptide evidences is decoy, is decoy
        if ( _type == MzidIdentType::v110 ) {
            for (auto pe : dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef() )
            {
                std::string peptideEvidenceRef = pe.peptideEvidence_ref();
                for (auto ok : dd110->SequenceCollection()->PeptideEvidence() )
                {
                    if (ok.id() == peptideEvidenceRef && !ok.isDecoy() )
                    {
                        return false;
                    }
                }
            }
            return true;
        }
        else if ( _type == MzidIdentType::v111 ) {
            for (auto pe : dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef() )
            {
                std::string peptideEvidenceRef = pe.peptideEvidence_ref();
                for (auto ok : dd111->SequenceCollection()->PeptideEvidence() )
                {
                    if (ok.id() == peptideEvidenceRef && !ok.isDecoy() )
                    {
                        return false;
                    }
                }
            }
            return true;
        }
        else if ( _type == MzidIdentType::v120 ) {
            for (auto pe : dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef())
            {
                std::string peptideEvidenceRef = pe.peptideEvidence_ref();
                for (auto ok : dd120->SequenceCollection()->PeptideEvidence() )
                {
                    if (ok.id() == peptideEvidenceRef && !ok.isDecoy() )
                    {
                        return false;
                    }
                    
                }
            }
            return true;
        }
    }

    double MzidIdentifications::QValue(int sirIndex, int siiIndex)
    {
        if ( _type == MzidIdentType::v110 ) {
#ifdef ORIG
            auto cvParam = dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].cvParam().Where([&] (std::any cv) {
                    return cv->accession == "MS:1002354";
                }).FirstOrDefault();
            return cvParam == nullptr ? -1 : static_cast<double>(cvParam->value);
#endif
            auto tmpParam = dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].cvParam();
            mzIdentML110::SpectrumIdentificationItemType::cvParam_sequence cvtmpParam;
            for ( auto cv : tmpParam ) {
                if ( cv.accession() == "MS:1002354" ) {
                    cvtmpParam.push_back(cv);
                }
            }
            auto cvParam = tmpParam.front();
            return cvtmpParam.empty() ? -1 : std::stod(cvParam.value().get());
        }
        else if ( _type == MzidIdentType::v111 ) {
            auto tmpParam = dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].cvParam();
            mzIdentML111::SpectrumIdentificationItemType::cvParam_sequence cvtmpParam;
            for ( auto cv : tmpParam ) {
                if ( cv.accession() == "MS:1002354" ) {
                    cvtmpParam.push_back(cv);
                }
            }
            auto cvParam = tmpParam.front();
            return cvtmpParam.empty() ? -1 : std::stod(cvParam.value().get());
        }
        else if ( _type == MzidIdentType::v120 ) {
            auto tmpParam = dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].cvParam();
            mzIdentML120::SpectrumIdentificationItemType::cvParam_sequence cvtmpParam;
            for ( auto cv : tmpParam ) {
                if ( cv.accession() == "MS:1002354" ) {
                    cvtmpParam.push_back(cv);
                }
            }
            auto cvParam = tmpParam.front();
            return cvtmpParam.empty() ? -1 : std::stod(cvParam.value().get());
        }
    }

    int MzidIdentifications::NumPSMsFromScan(int sirIndex)
    {
        if ( _type == MzidIdentType::v110 ) {
#ifdef ORIG
            return dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem->Count([&] (std::any i)  {
                    return i != nullptr;
                });
#endif
            auto tmp = dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem();
            int count=0;
            for ( auto i : tmp ) {
                if ( i ) {
                    count++;
                }
            }
            return count;
        }
        else if ( _type == MzidIdentType::v111 ) {
            auto tmp = dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem();
            int count=0;
            for ( auto i : tmp ) {
                if ( i ) {
                    count++;
                }
            }
            return count;
        }
        else if ( _type == MzidIdentType::v120 ) {
            auto tmp = dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem();
            int count=0;
            for ( auto i : tmp ) {
                if ( i ) {
                    count++;
                }
            }
            return count;
        }
    }

    std::string MzidIdentifications::ModificationAcession(int sirIndex, int siiIndex, int i)
    {
        std::string s = "";
        if ( _type == MzidIdentType::v110 ) { 
            std::string peptideEvidenceRef = dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef()[0].peptideEvidence_ref();
            for (auto ok : dd110->SequenceCollection()->PeptideEvidence())
            {
                if (ok.id() == peptideEvidenceRef )
                {
                    for (auto ok2 : dd110->SequenceCollection()->Peptide())
                    {
                        if (ok2.id() == ok.peptide_ref())
                        {
                            s = ok2.Modification()[i].cvParam()[0].accession();
                            break;
                        }
                    }
                }
            }
        }
        else if ( _type == MzidIdentType::v111 ) {
            std::string peptideEvidenceRef = dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef()[0].peptideEvidence_ref();
            for (auto ok : dd111->SequenceCollection()->PeptideEvidence())
            {
                if (ok.id() == peptideEvidenceRef )
                {
                    for (auto ok2 : dd111->SequenceCollection()->Peptide())
                    {
                        if (ok2.id() == ok.peptide_ref() )
                        {
                            s = ok2.Modification()[i].cvParam()[0].accession();
                            break;
                        }
                    }
                }
            }
        }
        else if ( _type == MzidIdentType::v120 ) {
            std::string peptideEvidenceRef = dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef()[0].peptideEvidence_ref();
            for (auto ok : dd120->SequenceCollection()->PeptideEvidence())
            {
                if (ok.id() == peptideEvidenceRef )
                {
                    for (auto ok2 : dd120->SequenceCollection()->Peptide())
                    {
                        if (ok2.id() == ok.peptide_ref() )
                        {
                            s = ok2.Modification()[i].cvParam()[0].accession();
                            break;
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
        if ( _type == MzidIdentType::v110 ) {
            std::string peptideEvidenceRef = dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef()[0].peptideEvidence_ref();
            for (auto ok : dd110->SequenceCollection()->PeptideEvidence())
            {
                if (ok.id() == peptideEvidenceRef )
                {
                    for (auto ok2 : dd110->SequenceCollection()->Peptide())
                    {
                        if (ok2.id() == ok.peptide_ref() )
                        {
                            s = ok2.Modification()[i].cvParam()[0].value().get();
                            break;
                        }
                    }
                }
            }
        }
        else if ( _type == MzidIdentType::v111 ) {
            std::string peptideEvidenceRef = dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef()[0].peptideEvidence_ref();
            for (auto ok : dd111->SequenceCollection()->PeptideEvidence())
            {
                if (ok.id() == peptideEvidenceRef )
                {
                    for (auto ok2 : dd111->SequenceCollection()->Peptide())
                    {
                        if (ok2.id() == ok.peptide_ref())
                        {
                            s = ok2.Modification()[i].cvParam()[0].value().get();
                            break;
                        }
                    }
                }
            }
        }
        else if ( _type == MzidIdentType::v120 ) {
            std::string peptideEvidenceRef = dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef()[0].peptideEvidence_ref();
            for (auto ok : dd120->SequenceCollection()->PeptideEvidence())
            {
                if (ok.id() == peptideEvidenceRef )
                {
                    for (auto ok2 : dd120->SequenceCollection()->Peptide())
                    {
                        if (ok2.id() == ok.peptide_ref())
                        {
                            s = ok2.Modification()[i].cvParam()[0].value().get();
                            break;
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
        if ( _type == MzidIdentType::v110 ) {        
            std::string peptideEvidenceRef = dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef()[0].peptideEvidence_ref();
            for (auto ok : dd110->SequenceCollection()->PeptideEvidence())
            {
                if (ok.id() == peptideEvidenceRef )
                {
                    for (auto ok2 : dd110->SequenceCollection()->Peptide())
                    {
                        if (ok2.id() == ok.peptide_ref())
                        {
                            s = ok2.Modification()[i].cvParam()[0].cvRef();
                            break;
                        }
                    }
                }
            }
        }
        else if ( _type == MzidIdentType::v111 ) {
            std::string peptideEvidenceRef = dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef()[0].peptideEvidence_ref();
            for (auto ok : dd111->SequenceCollection()->PeptideEvidence())
            {
                if (ok.id() == peptideEvidenceRef )
                {
                    for (auto ok2 : dd111->SequenceCollection()->Peptide())
                    {
                        if (ok2.id() == ok.peptide_ref() )
                        {
                            s = ok2.Modification()[i].cvParam()[0].cvRef();
                            break;
                        }
                    }
                }
            }
        }
        else if ( _type == MzidIdentType::v120 ) {
            std::string peptideEvidenceRef = dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef()[0].peptideEvidence_ref();
            for (auto ok : dd120->SequenceCollection()->PeptideEvidence())
            {
                if (ok.id() == peptideEvidenceRef )
                {
                    for (auto ok2 : dd120->SequenceCollection()->Peptide())
                    {
                        if (ok2.id() == ok.peptide_ref())
                        {
                            s = ok2.Modification()[i].cvParam()[0].cvRef();
                            break;
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
        if ( _type == MzidIdentType::v110 ) {               
            std::string peptideEvidenceRef = dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef()[0].peptideEvidence_ref();
            for (auto ok : dd110->SequenceCollection()->PeptideEvidence())
            {
                if (ok.id() == peptideEvidenceRef )
                {
                    for (auto ok2 : dd110->SequenceCollection()->Peptide())
                    {
                        if (ok2.id() == ok.peptide_ref())
                        {
                            modLoc = ok2.Modification()[i].location().get();
                            break;
                        }
                    }
                }
            }
        }
        else if ( _type == MzidIdentType::v111 ) { 
            std::string peptideEvidenceRef = dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef()[0].peptideEvidence_ref();
            for (auto ok : dd111->SequenceCollection()->PeptideEvidence())
            {
                if (ok.id() == peptideEvidenceRef )
                {
                    for (auto ok2 : dd111->SequenceCollection()->Peptide())
                    {
                        if (ok2.id() == ok.peptide_ref() )
                        {
                            modLoc = ok2.Modification()[i].location().get();
                            break;
                        }
                    }
                }
            }
        }
        else if ( _type == MzidIdentType::v120 ) {   
            std::string peptideEvidenceRef = dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef()[0].peptideEvidence_ref();
            for (auto ok : dd120->SequenceCollection()->PeptideEvidence())
            {
                if (ok.id() == peptideEvidenceRef )
                {
                    for (auto ok2 : dd120->SequenceCollection()->Peptide())
                    {
                        if (ok2.id() == ok.peptide_ref())
                        {
                            modLoc = ok2.Modification()[i].location().get();
                            break;
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
        if ( _type == MzidIdentType::v110 ) {
            std::string peptideEvidenceRef = dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef()[0].peptideEvidence_ref();
            for (auto ok : dd110->SequenceCollection()->PeptideEvidence())
            {
                if (ok.id() == peptideEvidenceRef )
                {
                    for (auto ok2 : dd110->SequenceCollection()->Peptide())
                    {
                        if (ok2.id() == ok.peptide_ref() )
                        {
                            modMass = ok2.Modification()[i].monoisotopicMassDelta().get();
                            break;
                        }
                    }
                }
            }
        }
        else if ( _type == MzidIdentType::v111 ) { 
            std::string peptideEvidenceRef = dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef()[0].peptideEvidence_ref();
            for (auto ok : dd111->SequenceCollection()->PeptideEvidence())
            {
                if (ok.id() == peptideEvidenceRef)
                {
                    for (auto ok2 : dd111->SequenceCollection()->Peptide())
                    {
                        if (ok2.id() == ok.peptide_ref())
                        {
                            modMass = ok2.Modification()[i].monoisotopicMassDelta().get();
                            break;
                        }
                    }
                }
            }
        }
        else if ( _type == MzidIdentType::v120 ) { 
            std::string peptideEvidenceRef = dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef()[0].peptideEvidence_ref();
            for (auto ok : dd120->SequenceCollection()->PeptideEvidence())
            {
                if (ok.id() == peptideEvidenceRef)
                {
                    for (auto ok2 : dd120->SequenceCollection()->Peptide())
                    {
                        if (ok2.id() == ok.peptide_ref())
                        {
                            modMass = ok2.Modification()[i].monoisotopicMassDelta().get();
                            break;
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
        if ( _type == MzidIdentType::v110 ) {                       
            std::string peptideEvidenceRef = dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef()[0].peptideEvidence_ref();
            for (auto ok : dd110->SequenceCollection()->PeptideEvidence())
            {
                if (ok.id() == peptideEvidenceRef)
                {
                    for (auto ok2 : dd110->SequenceCollection()->Peptide())
                    {
                        if (ok2.id() == ok.peptide_ref())
                        {
                            if (ok2.Modification().empty() )
                            {
                                break;
                            }
                            numMod = ok2.Modification().size();
                            break;
                        }
                    }
                }
            }
        }
        else if ( _type == MzidIdentType::v111 ) {
            std::string peptideEvidenceRef = dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef()[0].peptideEvidence_ref();
            for (auto ok : dd111->SequenceCollection()->PeptideEvidence())
            {
                if (ok.id() == peptideEvidenceRef)
                {
                    for (auto ok2 : dd111->SequenceCollection()->Peptide())
                    {
                        if (ok2.id() == ok.peptide_ref())
                        {
                            if (ok2.Modification().empty() )
                            {
                                break;
                            }
                            numMod = ok2.Modification().size();
                            break;
                        }
                    }
                }
            }
        }
        else if ( _type == MzidIdentType::v120 ) { 
            std::string peptideEvidenceRef = dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef()[0].peptideEvidence_ref();
            for (auto ok : dd120->SequenceCollection()->PeptideEvidence())
            {
                if (ok.id() == peptideEvidenceRef)
                {
                    for (auto ok2 : dd120->SequenceCollection()->Peptide())
                    {
                        if (ok2.id() == ok.peptide_ref())
                        {
                            if (ok2.Modification().empty() )
                            {
                                break;
                            }
                            numMod = ok2.Modification().size();
                            break;
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
        if ( _type == MzidIdentType::v110 ) {
            std::string peptideEvidenceRef = dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef()[0].peptideEvidence_ref();
            for (auto ok : dd110->SequenceCollection()->PeptideEvidence())
            {
                if (ok.id() == peptideEvidenceRef)
                {
                    for (auto ok2 : dd110->SequenceCollection()->Peptide())
                    {
                        if (ok2.id() == ok.peptide_ref())
                        {
                            s = ok2.PeptideSequence();
                            break;
                        }
                    }
                }
            }
        }
        else if ( _type == MzidIdentType::v111 ) { 
            std::string peptideEvidenceRef = dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef()[0].peptideEvidence_ref();
            for (auto ok : dd111->SequenceCollection()->PeptideEvidence())
            {
                if (ok.id() == peptideEvidenceRef)
                {
                    for (auto ok2 : dd111->SequenceCollection()->Peptide())
                    {
                        if (ok2.id() == ok.peptide_ref())
                        {
                            s = ok2.PeptideSequence();
                            break;
                        }
                    }
                }
            }
        }
        else if ( _type == MzidIdentType::v120 ) { 
            std::string peptideEvidenceRef = dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef()[0].peptideEvidence_ref();
            for (auto ok : dd120->SequenceCollection()->PeptideEvidence())
            {
                if (ok.id() == peptideEvidenceRef)
                {
                    for (auto ok2 : dd120->SequenceCollection()->Peptide())
                    {
                        if (ok2.id() == ok.peptide_ref())
                        {
                            s = ok2.PeptideSequence();
                            break;
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
        if ( _type == MzidIdentType::v110 ) {
            if (dd110->DataCollection().Inputs().SpectraData()[0].FileFormat().get().cvParam().name() == "Thermo RAW format" ||
                dd110->DataCollection().Inputs().SpectraData()[0].FileFormat().get().cvParam().name() == "mzML format" )
            {
                ms2id = dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].spectrumID();
            }
            else if (dd110->DataCollection().Inputs().SpectraData()[0].FileFormat().get().cvParam().name() == "Mascot MGF format")
            {
                ms2id = dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].cvParam()[0].value().get();
            }
        }
        else if ( _type == MzidIdentType::v111 ) { 
            if (dd111->DataCollection().Inputs().SpectraData()[0].FileFormat().get().cvParam().name() == "Thermo RAW format" ||
                dd111->DataCollection().Inputs().SpectraData()[0].FileFormat().get().cvParam().name() == "mzML format" )
            {
                ms2id = dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].spectrumID();
            }
            else if (dd111->DataCollection().Inputs().SpectraData()[0].FileFormat().get().cvParam().name() == "Mascot MGF format")
            {
                ms2id = dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].cvParam()[0].value().get();
            }
        }
        else if ( _type == MzidIdentType::v120 ) {   
            if (dd120->DataCollection().Inputs().SpectraData()[0].FileFormat().cvParam().name() == "Thermo RAW format" ||
                dd120->DataCollection().Inputs().SpectraData()[0].FileFormat().cvParam().name() == "mzML format" )
            {
                ms2id = dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].spectrumID();
            }
            else if (dd120->DataCollection().Inputs().SpectraData()[0].FileFormat().cvParam().name() == "Mascot MGF format")
            {
                ms2id = dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].cvParam()[0].value().get();
            }
        }
        
        return ms2id;
    }

    std::vector<float> MzidIdentifications::MatchedIons(int sirIndex, int siiIndex, int i)
    {
        if ( _type == MzidIdentType::v110 ) {  
            return dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].Fragmentation()[i].FragmentArray()[0].values;
        }
        else if ( _type == MzidIdentType::v111 ) {
            return dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].Fragmentation()[i].FragmentArray()[0].values;
        }
        else if ( _type == MzidIdentType::v120 ) {
            return dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].Fragmentation()[i].FragmentArray()[0].values;
        }
    }

    int MzidIdentifications::MatchedIonCounts(int sirIndex, int siiIndex, int i)
    {
        if ( _type == MzidIdentType::v110 ) { 
            return dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].Fragmentation()[i].FragmentArray()[0].values->Length;
        }
        else if ( _type == MzidIdentType::v111 ) {
            return dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].Fragmentation()[i].FragmentArray()[0].values->Length;
        }
        else if ( _type == MzidIdentType::v120 ) {
            return dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].Fragmentation()[i].FragmentArray()[0].values->Length;
        }
    }
    
    std::string MzidIdentifications::ProteinAccession(int sirIndex, int siiIndex)
    {
        std::string s = "";

        if ( _type == MzidIdentType::v110 ) { 
            std::string peptideEvidenceRef = dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef()[0].peptideEvidence_ref();
            for (auto ok : dd110->SequenceCollection()->PeptideEvidence())
            {
                if (ok.id() == peptideEvidenceRef )
                {
                    for (auto ok2 : dd110->SequenceCollection()->DBSequence())
                    {
                        if (ok2.id() == ok.dBSequence_ref())
                        {
                            s = ok2.accession();
                            break;
                        }
                    }
                }
            }
        }
        else if ( _type == MzidIdentType::v111 ) {
            std::string peptideEvidenceRef = dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef()[0].peptideEvidence_ref();
            for (auto ok : dd111->SequenceCollection()->PeptideEvidence())
            {
                if (ok.id() == peptideEvidenceRef)
                {
                    for (auto ok2 : dd111->SequenceCollection()->DBSequence())
                    {
                        if (ok2.id() == ok.dBSequence_ref())
                        {
                            s = ok2.accession();
                            break;
                        }
                    }
                }
            }
        }
        else if ( _type == MzidIdentType::v120 ) {
            std::string peptideEvidenceRef = dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef()[0].peptideEvidence_ref();
            for (auto ok : dd120->SequenceCollection()->PeptideEvidence())
            {
                if (ok.id() == peptideEvidenceRef)
                {
                    for (auto ok2 : dd120->SequenceCollection()->DBSequence())
                    {
                        if (ok2.id() == ok.dBSequence_ref())
                        {
                            s = ok2.accession();
                            break;
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

        if ( _type == MzidIdentType::v110 ) {
            for (auto pe : dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef())
            {
                std::string peptideEvidenceRef = pe.peptideEvidence_ref();
                for (auto ok : dd110->SequenceCollection()->PeptideEvidence())
                {
                    if (ok.id() == peptideEvidenceRef)
                    {
                        for (auto ok2 : dd110->SequenceCollection()->DBSequence())
                        {
                            if (ok2.id() == ok.dBSequence_ref())
                            {
                                if (s.length() != 0)
                                {
                                    s += " or ";
                                }
                                s += ok2.name().get();
                                break;
                            }
                        }
                    }
                }
            }
        }
        else if ( _type == MzidIdentType::v111 ) {    
            for (auto pe : dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef())
            {
                std::string peptideEvidenceRef = pe.peptideEvidence_ref();
                for (auto ok : dd111->SequenceCollection()->PeptideEvidence())
                {
                    if (ok.id() == peptideEvidenceRef)
                    {
                        for (auto ok2 : dd111->SequenceCollection()->DBSequence())
                        {
                            if (ok2.id() == ok.dBSequence_ref())
                            {
                                if (s.length() != 0)
                                {
                                    s += " or ";
                                }
                                s += ok2.name().get();
                                break;
                            }
                        }
                    }
                }
            }
        }
        else if ( _type == MzidIdentType::v120 ) {
            for (auto pe : dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef())
            {
                std::string peptideEvidenceRef = pe.peptideEvidence_ref();
                for (auto ok : dd120->SequenceCollection()->PeptideEvidence())
                {
                    if (ok.id() == peptideEvidenceRef)
                    {
                        for (auto ok2 : dd120->SequenceCollection()->DBSequence())
                        {
                            if (ok2.id() == ok.dBSequence_ref())
                            {
                                if (s.length() != 0)
                                {
                                    s += " or ";
                                }
                                s += ok2.name().get();
                                break;
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
        if ( _type == MzidIdentType::v110 ) {
            for (auto pe : dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef() )
            {
                std::string peptideEvidenceRef = pe.peptideEvidence_ref();
                for (auto ok : dd110->SequenceCollection()->PeptideEvidence())
                {
                    if (ok.id() == peptideEvidenceRef)
                    {
                        if (startResidue.length() != 0)
                        {
                            startResidue += " or ";
                        }
                        startResidue += ok.start().get();
                        break;
                    }
                }
            }
        }
        else if ( _type == MzidIdentType::v111 ) {
            for (auto pe : dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef())
            {
                std::string peptideEvidenceRef = pe.peptideEvidence_ref();
                for (auto ok : dd111->SequenceCollection()->PeptideEvidence())
                {
                    if (ok.id() == peptideEvidenceRef)
                    {
                        if (startResidue.length() != 0)
                        {
                            startResidue += " or ";
                        }
                        startResidue += ok.start().get();
                        break;
                    }
                }
            }
        }
        else if ( _type == MzidIdentType::v120 ) {
            for (auto pe : dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef())
            {
                std::string peptideEvidenceRef = pe.peptideEvidence_ref();
                for (auto ok : dd120->SequenceCollection()->PeptideEvidence())
                {
                    if (ok.id() == peptideEvidenceRef)
                    {
                        if (startResidue.length() != 0)
                        {
                            startResidue += " or ";
                        }
                        startResidue += ok.start().get();
                        break;
                    }
                }
            }
        }
        
        return startResidue;
    }

    std::string MzidIdentifications::EndResidueInProtein(int sirIndex, int siiIndex)
    {
        std::string endResidue = "";
        if ( _type == MzidIdentType::v110 ) {
            for (auto pe : dd110->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef())
            {
                std::string peptideEvidenceRef = pe.peptideEvidence_ref();
                for (auto ok : dd110->SequenceCollection()->PeptideEvidence())
                {
                    if (ok.id() == peptideEvidenceRef)
                    {
                        if (endResidue.length() != 0)
                        {
                            endResidue += " or ";
                        }
                        endResidue += ok.end().get();
                        break;
                    }
                }
            }
        }
        else if ( _type == MzidIdentType::v111 ) {
            for (auto pe : dd111->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef())
            {
                std::string peptideEvidenceRef = pe.peptideEvidence_ref();
                for (auto ok : dd111->SequenceCollection()->PeptideEvidence())
                {
                    if (ok.id() == peptideEvidenceRef)
                    {
                        if (endResidue.length() != 0)
                        {
                            endResidue += " or ";
                        }
                        endResidue += ok.end().get();
                        break;
                    }
                }
            }
        }
        else if ( _type == MzidIdentType::v120 ) {
            for (auto pe : dd120->DataCollection().AnalysisData().SpectrumIdentificationList()[0].SpectrumIdentificationResult()[sirIndex].SpectrumIdentificationItem()[siiIndex].PeptideEvidenceRef())
            {
                std::string peptideEvidenceRef = pe.peptideEvidence_ref();
                for (auto ok : dd120->SequenceCollection()->PeptideEvidence())
                {
                    if (ok.id() == peptideEvidenceRef)
                    {
                        if (endResidue.length() != 0)
                        {
                            endResidue += " or ";
                        }
                        endResidue += ok.end().get();
                        break;
                    }
                }
            }
        }
        
        return endResidue;
    }
}
