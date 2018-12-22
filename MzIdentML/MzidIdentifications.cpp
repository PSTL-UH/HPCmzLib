#include "MzidIdentifications.h"
#include "mzIdentML.Generated.MzIdentMLType.h"
#include "mzIdentML110.Generated.MzIdentMLType.h"
#include "../MzLibUtil/Tolerance.h"
#include "../MzLibUtil/AbsoluteTolerance.h"
#include "../MzLibUtil/PpmTolerance.h"
#include "mzIdentML.Generated.PeptideEvidenceRefType.h"
#include "mzIdentML110.Generated.PeptideEvidenceRefType.h"

using namespace MassSpectrometry;
using namespace MzLibUtil;

namespace MzIdentML {

    MzidIdentifications::MzidIdentifications(const std::wstring &mzidFile) {
        try {
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (Stream stream = new FileStream(mzidFile, FileMode.Open, FileAccess.Read, FileShare.Read))
        {
                Stream stream = FileStream(mzidFile, FileMode::Open, FileAccess::Read, FileShare::Read);
                XmlSerializer *_indexedSerializer = new XmlSerializer(mzIdentML::Generated::MzIdentMLType::typeid);
                // Read the XML file into the variable
                dd = dynamic_cast<mzIdentML::Generated::MzIdentMLType*>(_indexedSerializer->Deserialize(stream));

                delete _indexedSerializer;
        }
        }
        catch (...) {
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (Stream stream = new FileStream(mzidFile, FileMode.Open, FileAccess.Read, FileShare.Read))
        {
                Stream stream = FileStream(mzidFile, FileMode::Open, FileAccess::Read, FileShare::Read);
                XmlSerializer *_indexedSerializer = new XmlSerializer(mzIdentML110::Generated::MzIdentMLType::typeid);
                // Read the XML file into the variable
                dd110 = dynamic_cast<mzIdentML110::Generated::MzIdentMLType*>(_indexedSerializer->Deserialize(stream));

                delete _indexedSerializer;
        }
        }
    }

    Tolerance *MzidIdentifications::getParentTolerance() const {
        try {
            auto hm = dd->getAnalysisProtocolCollection()->getSpectrumIdentificationProtocol()[0]->ParentTolerance;
            AbsoluteTolerance tempVar(static_cast<double>(hm[0].value));
            return hm[0].unitName->Equals(L"dalton") ? static_cast<Tolerance*>(&tempVar): new PpmTolerance(static_cast<double>(hm[0].value));
        }
        catch (...) {
            auto hm = dd110->getAnalysisProtocolCollection()->getSpectrumIdentificationProtocol()[0]->ParentTolerance;
            AbsoluteTolerance tempVar2(static_cast<double>(hm[0].value));
            return hm[0].unitName->Equals(L"dalton") ? static_cast<Tolerance*>(&tempVar2): new PpmTolerance(static_cast<double>(hm[0].value));
        }
    }

    Tolerance *MzidIdentifications::getFragmentTolerance() const {
        try {
            auto hm = dd->getAnalysisProtocolCollection()->getSpectrumIdentificationProtocol()[0]->FragmentTolerance;
            AbsoluteTolerance tempVar(static_cast<double>(hm[0].value));
            return hm[0].unitName->Equals(L"dalton") ? static_cast<Tolerance*>(&tempVar): new PpmTolerance(static_cast<double>(hm[0].value));
        }
        catch (...) {
            auto hm = dd110->getAnalysisProtocolCollection()->getSpectrumIdentificationProtocol()[0]->FragmentTolerance;
            AbsoluteTolerance tempVar2(static_cast<double>(hm[0].value));
            return hm[0].unitName->Equals(L"dalton") ? static_cast<Tolerance*>(&tempVar2): new PpmTolerance(static_cast<double>(hm[0].value));
        }
    }

    int MzidIdentifications::getCount() const {
        try {
            return dd->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult->Count();
        }
        catch (...) {
            return dd110->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult->Count();
        }
    }

    double MzidIdentifications::CalculatedMassToCharge(int sirIndex, int siiIndex) {
        try {
            return dd->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[sirIndex].SpectrumIdentificationItem[siiIndex].calculatedMassToCharge;
        }
        catch (...) {
            return dd110->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[sirIndex].SpectrumIdentificationItem[siiIndex].calculatedMassToCharge;
        }
    }

    int MzidIdentifications::ChargeState(int sirIndex, int siiIndex) {
        try {
            return dd->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[sirIndex].SpectrumIdentificationItem[siiIndex].chargeState;
        }
        catch (...) {
            return dd110->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[sirIndex].SpectrumIdentificationItem[siiIndex].chargeState;
        }
    }

    double MzidIdentifications::ExperimentalMassToCharge(int sirIndex, int siiIndex) {
        try {
            return dd->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[sirIndex].SpectrumIdentificationItem[siiIndex].experimentalMassToCharge;
        }
        catch (...) {
            return dd110->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[sirIndex].SpectrumIdentificationItem[siiIndex].experimentalMassToCharge;
        }
    }

    bool MzidIdentifications::IsDecoy(int sirIndex, int siiIndex) {
        //if any of the peptide evidences is decoy, is decoy
        try {
            for (mzIdentML::Generated::PeptideEvidenceRefType *pe : dd->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[sirIndex].SpectrumIdentificationItem[siiIndex].PeptideEvidenceRef) {
                std::wstring peptideEvidenceRef = pe->getpeptideEvidence_ref();
                for (auto ok : dd->getSequenceCollection()->getPeptideEvidence()) {
                    if (ok->id->Equals(peptideEvidenceRef)) {
                        if (!ok->isDecoy) {
                            return false;
                        }
                    }
                }
            }
            return true;
        }
        catch (...) {
            for (mzIdentML110::Generated::PeptideEvidenceRefType *pe : dd110->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[sirIndex].SpectrumIdentificationItem[siiIndex].PeptideEvidenceRef) {
                std::wstring peptideEvidenceRef = pe->getpeptideEvidence_ref();
                for (auto ok : dd110->getSequenceCollection()->getPeptideEvidence()) {
                    if (ok->id->Equals(peptideEvidenceRef)) {
                        if (!ok->isDecoy) {
                            return false;
                        }
                    }
                }
            }
            return true;
        }
    }

    double MzidIdentifications::QValue(int sirIndex, int siiIndex) {
        try {
            auto cvParam = dd->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[sirIndex].SpectrumIdentificationItem[siiIndex].cvParam.Where([&] (std::any cv) {
                return cv->accession == L"MS:1002354";
            }).FirstOrDefault();
            return cvParam == nullptr ? -1 : static_cast<double>(cvParam->value);
        }
        catch (...) {
            auto cvParam = dd110->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[sirIndex].SpectrumIdentificationItem[siiIndex].cvParam.Where([&] (std::any cv) {
                return cv->accession == L"MS:1002354";
            }).FirstOrDefault();
            return cvParam == nullptr ? -1 : static_cast<double>(cvParam->value);
        }
    }

    int MzidIdentifications::NumPSMsFromScan(int sirIndex) {
        try {
            return dd->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[sirIndex].SpectrumIdentificationItem->Count([&] (std::any i) {
                return i != nullptr;
            });
        }
        catch (...) {
            return dd110->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[sirIndex].SpectrumIdentificationItem->Count([&] (std::any i) {
                return i != nullptr;
            });
        }
    }

    std::wstring MzidIdentifications::ModificationAcession(int sirIndex, int siiIndex, int i) {
        std::wstring s = L"";
        try {
            std::wstring peptideEvidenceRef = dd->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[sirIndex].SpectrumIdentificationItem[siiIndex].PeptideEvidenceRef[0].peptideEvidence_ref;
            for (auto ok : dd->getSequenceCollection()->getPeptideEvidence()) {
                if (ok->id->Equals(peptideEvidenceRef)) {
                    for (auto ok2 : dd->getSequenceCollection()->getPeptide()) {
                        if (ok2->id->Equals(ok->peptide_ref)) {
                            s = ok2->Modification[i].cvParam[0].accession;
                            break;
                        }
                    }
                }
            }
        }
        catch (...) {
            std::wstring peptideEvidenceRef = dd110->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[sirIndex].SpectrumIdentificationItem[siiIndex].PeptideEvidenceRef[0].peptideEvidence_ref;
            for (auto ok : dd110->getSequenceCollection()->getPeptideEvidence()) {
                if (ok->id->Equals(peptideEvidenceRef)) {
                    for (auto ok2 : dd110->getSequenceCollection()->getPeptide()) {
                        if (ok2->id->Equals(ok->peptide_ref)) {
                            s = ok2->Modification[i].cvParam[0].accession;
                            break;
                        }
                    }
                }
            }
        }
        return s;
    }

    std::wstring MzidIdentifications::ModificationValue(int sirIndex, int siiIndex, int i) {
        std::wstring s = L"";
        try {
            std::wstring peptideEvidenceRef = dd->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[sirIndex].SpectrumIdentificationItem[siiIndex].PeptideEvidenceRef[0].peptideEvidence_ref;
            for (auto ok : dd->getSequenceCollection()->getPeptideEvidence()) {
                if (ok->id->Equals(peptideEvidenceRef)) {
                    for (auto ok2 : dd->getSequenceCollection()->getPeptide()) {
                        if (ok2->id->Equals(ok->peptide_ref)) {
                            s = ok2->Modification[i].cvParam[0].value;
                            break;
                        }
                    }
                }
            }
        }
        catch (...) {
            std::wstring peptideEvidenceRef = dd110->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[sirIndex].SpectrumIdentificationItem[siiIndex].PeptideEvidenceRef[0].peptideEvidence_ref;
            for (auto ok : dd110->getSequenceCollection()->getPeptideEvidence()) {
                if (ok->id->Equals(peptideEvidenceRef)) {
                    for (auto ok2 : dd110->getSequenceCollection()->getPeptide()) {
                        if (ok2->id->Equals(ok->peptide_ref)) {
                            s = ok2->Modification[i].cvParam[0].value;
                            break;
                        }
                    }
                }
            }
        }
        return s;
    }

    std::wstring MzidIdentifications::ModificationDictionary(int sirIndex, int siiIndex, int i) {
        std::wstring s = L"";
        try {
            std::wstring peptideEvidenceRef = dd->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[sirIndex].SpectrumIdentificationItem[siiIndex].PeptideEvidenceRef[0].peptideEvidence_ref;
            for (auto ok : dd->getSequenceCollection()->getPeptideEvidence()) {
                if (ok->id->Equals(peptideEvidenceRef)) {
                    for (auto ok2 : dd->getSequenceCollection()->getPeptide()) {
                        if (ok2->id->Equals(ok->peptide_ref)) {
                            s = ok2->Modification[i].cvParam[0].cvRef;
                            break;
                        }
                    }
                }
            }
        }
        catch (...) {
            std::wstring peptideEvidenceRef = dd110->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[sirIndex].SpectrumIdentificationItem[siiIndex].PeptideEvidenceRef[0].peptideEvidence_ref;
            for (auto ok : dd110->getSequenceCollection()->getPeptideEvidence()) {
                if (ok->id->Equals(peptideEvidenceRef)) {
                    for (auto ok2 : dd110->getSequenceCollection()->getPeptide()) {
                        if (ok2->id->Equals(ok->peptide_ref)) {
                            s = ok2->Modification[i].cvParam[0].cvRef;
                            break;
                        }
                    }
                }
            }
        }
        return s;
    }

    int MzidIdentifications::ModificationLocation(int sirIndex, int siiIndex, int i) {
        int modLoc = -1;
        try {
            std::wstring peptideEvidenceRef = dd->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[sirIndex].SpectrumIdentificationItem[siiIndex].PeptideEvidenceRef[0].peptideEvidence_ref;
            for (auto ok : dd->getSequenceCollection()->getPeptideEvidence()) {
                if (ok->id->Equals(peptideEvidenceRef)) {
                    for (auto ok2 : dd->getSequenceCollection()->getPeptide()) {
                        if (ok2->id->Equals(ok->peptide_ref)) {
                            modLoc = ok2->Modification[i].location;
                            break;
                        }
                    }
                }
            }
        }
        catch (...) {
            std::wstring peptideEvidenceRef = dd110->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[sirIndex].SpectrumIdentificationItem[siiIndex].PeptideEvidenceRef[0].peptideEvidence_ref;
            for (auto ok : dd110->getSequenceCollection()->getPeptideEvidence()) {
                if (ok->id->Equals(peptideEvidenceRef)) {
                    for (auto ok2 : dd110->getSequenceCollection()->getPeptide()) {
                        if (ok2->id->Equals(ok->peptide_ref)) {
                            modLoc = ok2->Modification[i].location;
                            break;
                        }
                    }
                }
            }
        }
        return modLoc;
    }

    double MzidIdentifications::ModificationMass(int sirIndex, int siiIndex, int i) {
        double modMass = -1;
        try {
            std::wstring peptideEvidenceRef = dd->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[sirIndex].SpectrumIdentificationItem[siiIndex].PeptideEvidenceRef[0].peptideEvidence_ref;
            for (auto ok : dd->getSequenceCollection()->getPeptideEvidence()) {
                if (ok->id->Equals(peptideEvidenceRef)) {
                    for (auto ok2 : dd->getSequenceCollection()->getPeptide()) {
                        if (ok2->id->Equals(ok->peptide_ref)) {
                            modMass = ok2->Modification[i].monoisotopicMassDelta;
                            break;
                        }
                    }
                }
            }
        }
        catch (...) {
            std::wstring peptideEvidenceRef = dd110->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[sirIndex].SpectrumIdentificationItem[siiIndex].PeptideEvidenceRef[0].peptideEvidence_ref;
            for (auto ok : dd110->getSequenceCollection()->getPeptideEvidence()) {
                if (ok->id->Equals(peptideEvidenceRef)) {
                    for (auto ok2 : dd110->getSequenceCollection()->getPeptide()) {
                        if (ok2->id->Equals(ok->peptide_ref)) {
                            modMass = ok2->Modification[i].monoisotopicMassDelta;
                            break;
                        }
                    }
                }
            }
        }
        return modMass;
    }

    int MzidIdentifications::NumModifications(int sirIndex, int siiIndex) {
        int numMod = 0;
        try {
            std::wstring peptideEvidenceRef = dd->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[sirIndex].SpectrumIdentificationItem[siiIndex].PeptideEvidenceRef[0].peptideEvidence_ref;
            for (auto ok : dd->getSequenceCollection()->getPeptideEvidence()) {
                if (ok->id->Equals(peptideEvidenceRef)) {
                    for (auto ok2 : dd->getSequenceCollection()->getPeptide()) {
                        if (ok2->id->Equals(ok->peptide_ref)) {
                            if (ok2->Modification == nullptr) {
                                break;
                            }
                            numMod = ok2->Modification->Length;
                            break;
                        }
                    }
                }
            }
        }
        catch (...) {
            std::wstring peptideEvidenceRef = dd110->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[sirIndex].SpectrumIdentificationItem[siiIndex].PeptideEvidenceRef[0].peptideEvidence_ref;
            for (auto ok : dd110->getSequenceCollection()->getPeptideEvidence()) {
                if (ok->id->Equals(peptideEvidenceRef)) {
                    for (auto ok2 : dd110->getSequenceCollection()->getPeptide()) {
                        if (ok2->id->Equals(ok->peptide_ref)) {
                            if (ok2->Modification == nullptr) {
                                break;
                            }
                            numMod = ok2->Modification->Length;
                            break;
                        }
                    }
                }
            }
        }
        return numMod;
    }

    std::wstring MzidIdentifications::PeptideSequenceWithoutModifications(int sirIndex, int siiIndex) {
        std::wstring s = L"";
        try {
            std::wstring peptideEvidenceRef = dd->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[sirIndex].SpectrumIdentificationItem[siiIndex].PeptideEvidenceRef[0].peptideEvidence_ref;
            for (auto ok : dd->getSequenceCollection()->getPeptideEvidence()) {
                if (ok->id->Equals(peptideEvidenceRef)) {
                    for (auto ok2 : dd->getSequenceCollection()->getPeptide()) {
                        if (ok2->id->Equals(ok->peptide_ref)) {
                            s = ok2->PeptideSequence;
                            break;
                        }
                    }
                }
            }
        }
        catch (...) {
            std::wstring peptideEvidenceRef = dd110->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[sirIndex].SpectrumIdentificationItem[siiIndex].PeptideEvidenceRef[0].peptideEvidence_ref;
            for (auto ok : dd110->getSequenceCollection()->getPeptideEvidence()) {
                if (ok->id->Equals(peptideEvidenceRef)) {
                    for (auto ok2 : dd110->getSequenceCollection()->getPeptide()) {
                        if (ok2->id->Equals(ok->peptide_ref)) {
                            s = ok2->PeptideSequence;
                            break;
                        }
                    }
                }
            }
        }
        return s;
    }

    std::wstring MzidIdentifications::Ms2SpectrumID(int sirIndex) {
        std::wstring ms2id = L"";
        try {
            if (dd->getDataCollection()->getInputs()->getSpectraData()[0]->FileFormat.cvParam.name->Equals(L"Thermo RAW format") || dd->getDataCollection()->getInputs()->getSpectraData()[0]->FileFormat.cvParam.name->Equals(L"mzML format")) {
                ms2id = dd->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[sirIndex].spectrumID;
            }
            else if (dd->getDataCollection()->getInputs()->getSpectraData()[0]->FileFormat.cvParam.name->Equals(L"Mascot MGF format")) {
                ms2id = dd->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[sirIndex].cvParam[0].value;
            }
        }
        catch (...) {
            if (dd110->getDataCollection()->getInputs()->getSpectraData()[0]->FileFormat.cvParam.name->Equals(L"Thermo RAW format") || dd110->getDataCollection()->getInputs()->getSpectraData()[0]->FileFormat.cvParam.name->Equals(L"mzML format")) {
                ms2id = dd110->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[sirIndex].spectrumID;
            }
            else if (dd110->getDataCollection()->getInputs()->getSpectraData()[0]->FileFormat.cvParam.name->Equals(L"Mascot MGF format")) {
                ms2id = dd110->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[sirIndex].cvParam[0].value;
            }
        }
        return ms2id;
    }

    std::vector<float> MzidIdentifications::MatchedIons(int sirIndex, int siiIndex, int i) {
        try {
            return dd->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[sirIndex].SpectrumIdentificationItem[siiIndex].Fragmentation[i].FragmentArray[0].values;
        }
        catch (...) {
            return dd110->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[sirIndex].SpectrumIdentificationItem[siiIndex].Fragmentation[i].FragmentArray[0].values;
        }
    }

    int MzidIdentifications::MatchedIonCounts(int sirIndex, int siiIndex, int i) {
        try {
            return dd->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[sirIndex].SpectrumIdentificationItem[siiIndex].Fragmentation[i].FragmentArray[0].values->Length;
        }
        catch (...) {
            return dd110->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[sirIndex].SpectrumIdentificationItem[siiIndex].Fragmentation[i].FragmentArray[0].values->Length;
        }
    }

    std::wstring MzidIdentifications::ProteinAccession(int sirIndex, int siiIndex) {
        std::wstring s = L"";

        try {
            std::wstring peptideEvidenceRef = dd->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[sirIndex].SpectrumIdentificationItem[siiIndex].PeptideEvidenceRef[0].peptideEvidence_ref;
            for (auto ok : dd->getSequenceCollection()->getPeptideEvidence()) {
                if (ok->id->Equals(peptideEvidenceRef)) {
                    for (auto ok2 : dd->getSequenceCollection()->getDBSequence()) {
                        if (ok2->id->Equals(ok->dBSequence_ref)) {
                            s = ok2->accession;
                            break;
                        }
                    }
                }
            }
        }
        catch (...) {
            std::wstring peptideEvidenceRef = dd110->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[sirIndex].SpectrumIdentificationItem[siiIndex].PeptideEvidenceRef[0].peptideEvidence_ref;
            for (auto ok : dd110->getSequenceCollection()->getPeptideEvidence()) {
                if (ok->id->Equals(peptideEvidenceRef)) {
                    for (auto ok2 : dd110->getSequenceCollection()->getDBSequence()) {
                        if (ok2->id->Equals(ok->dBSequence_ref)) {
                            s = ok2->accession;
                            break;
                        }
                    }
                }
            }
        }
        return s;
    }

    std::wstring MzidIdentifications::ProteinFullName(int sirIndex, int siiIndex) {
        std::wstring s = L"";

        try {
            for (mzIdentML::Generated::PeptideEvidenceRefType *pe : dd->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[sirIndex].SpectrumIdentificationItem[siiIndex].PeptideEvidenceRef) {
                std::wstring peptideEvidenceRef = pe->getpeptideEvidence_ref();
                for (auto ok : dd->getSequenceCollection()->getPeptideEvidence()) {
                    if (ok->id->Equals(peptideEvidenceRef)) {
                        for (auto ok2 : dd->getSequenceCollection()->getDBSequence()) {
                            if (ok2->id->Equals(ok->dBSequence_ref)) {
                                if (s.length() != 0) {
                                    s += L" or ";
                                }
                                s += ok2->name;
                                break;
                            }
                        }
                    }
                }
            }
        }
        catch (...) {
            for (mzIdentML110::Generated::PeptideEvidenceRefType *pe : dd110->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[sirIndex].SpectrumIdentificationItem[siiIndex].PeptideEvidenceRef) {
                std::wstring peptideEvidenceRef = pe->getpeptideEvidence_ref();
                for (auto ok : dd110->getSequenceCollection()->getPeptideEvidence()) {
                    if (ok->id->Equals(peptideEvidenceRef)) {
                        for (auto ok2 : dd110->getSequenceCollection()->getDBSequence()) {
                            if (ok2->id->Equals(ok->dBSequence_ref)) {
                                if (s.length() != 0) {
                                    s += L" or ";
                                }
                                s += ok2->name;
                                break;
                            }
                        }
                    }
                }
            }
        }
        return s;
    }

    std::wstring MzidIdentifications::StartResidueInProtein(int sirIndex, int siiIndex) {
        std::wstring startResidue = L"";
        try {
            for (mzIdentML::Generated::PeptideEvidenceRefType *pe : dd->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[sirIndex].SpectrumIdentificationItem[siiIndex].PeptideEvidenceRef) {
                std::wstring peptideEvidenceRef = pe->getpeptideEvidence_ref();
                for (auto ok : dd->getSequenceCollection()->getPeptideEvidence()) {
                    if (ok->id->Equals(peptideEvidenceRef)) {
                        if (startResidue.length() != 0) {
                            startResidue += L" or ";
                        }
                        startResidue += ok->start;
                        break;
                    }
                }
            }
        }
        catch (...) {
            for (mzIdentML110::Generated::PeptideEvidenceRefType *pe : dd110->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[sirIndex].SpectrumIdentificationItem[siiIndex].PeptideEvidenceRef) {
                std::wstring peptideEvidenceRef = pe->getpeptideEvidence_ref();
                for (auto ok : dd110->getSequenceCollection()->getPeptideEvidence()) {
                    if (ok->id->Equals(peptideEvidenceRef)) {
                        if (startResidue.length() != 0) {
                            startResidue += L" or ";
                        }
                        startResidue += ok->start;
                        break;
                    }
                }
            }
        }
        return startResidue;
    }

    std::wstring MzidIdentifications::EndResidueInProtein(int sirIndex, int siiIndex) {
        std::wstring endResidue = L"";
        try {
            for (mzIdentML::Generated::PeptideEvidenceRefType *pe : dd->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[sirIndex].SpectrumIdentificationItem[siiIndex].PeptideEvidenceRef) {
                std::wstring peptideEvidenceRef = pe->getpeptideEvidence_ref();
                for (auto ok : dd->getSequenceCollection()->getPeptideEvidence()) {
                    if (ok->id->Equals(peptideEvidenceRef)) {
                        if (endResidue.length() != 0) {
                            endResidue += L" or ";
                        }
                        endResidue += ok->end;
                        break;
                    }
                }
            }
        }
        catch (...) {
            for (mzIdentML110::Generated::PeptideEvidenceRefType *pe : dd110->getDataCollection()->getAnalysisData()->getSpectrumIdentificationList()[0]->SpectrumIdentificationResult[sirIndex].SpectrumIdentificationItem[siiIndex].PeptideEvidenceRef) {
                std::wstring peptideEvidenceRef = pe->getpeptideEvidence_ref();
                for (auto ok : dd110->getSequenceCollection()->getPeptideEvidence()) {
                    if (ok->id->Equals(peptideEvidenceRef)) {
                        if (endResidue.length() != 0) {
                            endResidue += L" or ";
                        }
                        endResidue += ok->end;
                        break;
                    }
                }
            }
        }
        return endResidue;
    }
}
