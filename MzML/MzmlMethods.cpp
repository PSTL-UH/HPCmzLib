#include "MzmlMethods.h"
#include "../MassSpectrometry/MsDataFile.h"
// #include "XSD/IO.MzML.Generated.mzMLType.h"
// #include "XSD/IO.MzML.Generated.CVListType.h"
// #include "XSD/IO.MzML.Generated.CVType.h"
// #include "XSD/IO.MzML.Generated.FileDescriptionType.h"
// #include "XSD/IO.MzML.Generated.ParamGroupType.h"
// #include "XSD/IO.MzML.Generated.SourceFileListType.h"
// #include "XSD/IO.MzML.Generated.SourceFileType.h"
// #include "XSD/IO.MzML.Generated.CVParamType.h"
// #include "XSD/IO.MzML.Generated.SoftwareListType.h"
// #include "XSD/IO.MzML.Generated.SoftwareType.h"
// #include "XSD/IO.MzML.Generated.InstrumentConfigurationListType.h"
// #include "XSD/IO.MzML.Generated.InstrumentConfigurationType.h"
// #include "XSD/IO.MzML.Generated.ComponentListType.h"
// #include "XSD/IO.MzML.Generated.SourceComponentType.h"
// #include "XSD/IO.MzML.Generated.AnalyzerComponentType.h"
// #include "XSD/IO.MzML.Generated.DetectorComponentType.h"
// #include "XSD/IO.MzML.Generated.DataProcessingListType.h"
// #include "XSD/IO.MzML.Generated.DataProcessingType.h"
// #include "XSD/IO.MzML.Generated.ProcessingMethodType.h"
// #include "XSD/IO.MzML.Generated.RunType.h"
// #include "XSD/IO.MzML.Generated.ChromatogramListType.h"
// #include "XSD/IO.MzML.Generated.ChromatogramType.h"
// #include "XSD/IO.MzML.Generated.BinaryDataArrayListType.h"
// #include "XSD/IO.MzML.Generated.BinaryDataArrayType.h"
#include "../MassSpectrometry/MzSpectra/MzSpectrum.h"
// #include "XSD/IO.MzML.Generated.SpectrumListType.h"
// #include "XSD/IO.MzML.Generated.SpectrumType.h"
// #include "XSD/IO.MzML.Generated.ScanListType.h"
// #include "XSD/IO.MzML.Generated.ScanType.h"
// #include "XSD/IO.MzML.Generated.PrecursorListType.h"
// #include "XSD/IO.MzML.Generated.PrecursorType.h"
// #include "XSD/IO.MzML.Generated.SelectedIonListType.h"
#include "../MzLibUtil/MzRange.h"
// #include "XSD/IO.MzML.Generated.UserParamType.h"
// #include "XSD/IO.MzML.Generated.ScanWindowListType.h"
// #include "XSD/IO.MzML.Generated.indexedmzML.h"
// #include "XSD/IO.MzML.Generated.IndexListType.h"
// #include "XSD/IO.MzML.Generated.IndexType.h"
// #include "XSD/mzML1_1_1_idx.h"
// #include "XSD/IO.MzML.Generated.OffsetType.h"
#include "XSD/mzML1.1.0.h"
#include "XSD/mzML1.1.1_idx.h"
#include <experimental/filesystem>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <../include/stringhelper.h>

using namespace MassSpectrometry;
using namespace MzLibUtil;
namespace IO
{
    namespace MzML
    {

#ifdef ORIG
XmlSerializer *const MzmlMethods::indexedSerializer = new XmlSerializer(typeof(ms::mzml::indexedmzML));
XmlSerializer *const MzmlMethods::mzmlSerializer = new XmlSerializer(typeof(ms::mzml::mzMLType));
#endif


std::unordered_map<DissociationType, std::string> MzmlMethods::DissociationTypeAccessions =
{
    {DissociationType::CID, "MS:1000133"},
    {DissociationType::ISCID, "MS:1001880"},
    {DissociationType::HCD, "MS:1000422"},
    {DissociationType::ETD, "MS:1000598"},
    {DissociationType::IRMPD, "MS:1000435"},
    {DissociationType::PQD, "MS:1000599"},
    {DissociationType::Unknown, "MS:1000044"}
};
std::unordered_map<DissociationType, std::string> MzmlMethods::DissociationTypeNames =
{
    {DissociationType::CID, "collision-induced dissociation"},
    {DissociationType::ISCID, "in-source collision-induced dissociation"},
    {DissociationType::HCD, "beam-type collision-induced dissociation"},
    {DissociationType::ETD, "electron transfer dissociation"},
    {DissociationType::IRMPD, "photodissociation"},
    {DissociationType::PQD, "pulsed q dissociation"},
    {DissociationType::Unknown, "dissociation method"}
};
std::unordered_map<MZAnalyzerType, std::string> MzmlMethods::analyzerDictionary =
{
    {MZAnalyzerType::Unknown, "MS:1000443"},
    {MZAnalyzerType::Quadrupole, "MS:1000081"},
    {MZAnalyzerType::IonTrap2D, "MS:1000291"},
    {MZAnalyzerType::IonTrap3D,"MS:1000082"},
    {MZAnalyzerType::Orbitrap,"MS:1000484"},
    {MZAnalyzerType::TOF,"MS:1000084"},
    {MZAnalyzerType::FTICR,"MS:1000079"},
    {MZAnalyzerType::Sector,"MS:1000080"}
};
std::unordered_map<std::string, std::string> MzmlMethods::nativeIdFormatAccessions =
{
    {"scan number only nativeID format", "MS:1000776"},
    {"Thermo nativeID format", "MS:1000768"},
    {"no nativeID format", "MS:1000824"}
};
std::unordered_map<std::string, std::string> MzmlMethods::MassSpectrometerFileFormatAccessions =
{
    {"Thermo RAW format", "MS:1000563"},
    {"mzML format", "MS:1000584"}
};
std::unordered_map<std::string, std::string> MzmlMethods::FileChecksumAccessions =
{
    {"MD5", "MS:1000568"},
    {"SHA-1", "MS:1000569"}
};
std::unordered_map<bool, std::string> MzmlMethods::CentroidAccessions =
{
    {true, "MS:1000127"},
    {false, "MS:1000128"}
};
std::unordered_map<bool, std::string> MzmlMethods::CentroidNames =
{
    {true, "centroid spectrum"},
    {false, "profile spectrum"}
};
std::unordered_map<Polarity, std::string> MzmlMethods::PolarityAccessions =
{
    {Polarity::Negative, "MS:1000129"},
    {Polarity::Positive, "MS:1000130"}
};
std::unordered_map<Polarity, std::string> MzmlMethods::PolarityNames =
{
    {Polarity::Negative, "negative scan"},
    {Polarity::Positive, "positive scan"}
};

        void MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(MsDataFile *myMsDataFile, const std::string &outputFile, bool writeIndexed)
        {
            //original
            // std::string title = Path::GetFileNameWithoutExtension(outputFile);

            //returns filename WITH extension
            std::string title_with_extension = std::experimental::filesystem::path(outputFile).filename();

            //remove file extension from name
            size_t lastindex = title_with_extension.find_last_of("."); 
            std::string title = title_with_extension.substr(0, lastindex); 

            std::string idTitle = isdigit(title[0]) ? "id:" + title : title;


                //   mzMLType (const cvList_type&,
                // const fileDescription_type&,
                // const softwareList_type&,
                // const instrumentConfigurationList_type&,
                // const dataProcessingList_type&,
                // const run_type&,
                // const version_type&);


            //original
            // auto mzML = new ms::mzml::mzMLType();
            // ms::mzml::mzMLType *mzML;



            // mzML->version("1.1.0");

            //creating CVList of size 2 for mzML
            ms::mzml::CVListType *tempVar = new ms::mzml::CVListType(2);
            // ms::mzml::CVListType *tempVar;

            //original
            // mzML->cvList(&tempVar);
            // mzML->cvList(*tempVar);

            // mzML->id(idTitle);

            //original
            // ms::mzml::CVListType *tempVar2 = new ms::mzml::CVListType(1);
            // ms::mzml::CVListType *tempVar2;

            //original
            // mzML->cvList(&tempVar2);
            // mzML->cvList(*tempVar2);

            //original
            // mzML->cvList()->setcount("2");
            // mzML->cvList()->setcv(std::vector<ms::mzml::CVType*>(2));
            // mzML->cvList().count(2);
            // mzML->cvList().cv(std::vector<ms::mzml::CVType*>(2));

            // ms::mzml::CVType *tempVar3 = new ms::mzml::CVType();


            //Creating 2 CVTypes for CVlist for mzML
            ms::mzml::CVType *tempVar3 = new ms::mzml::CVType("MS", "Proteomics Standards Initiative Mass Spectrometry Ontology", "(https://raw.githubusercontent.com/HUPO-PSI/psi-ms-CV/master/psi-ms.obo)");
            // tempVar3->setURI(R"(https://raw.githubusercontent.com/HUPO-PSI/psi-ms-CV/master/psi-ms.obo)");
            // tempVar3->setfullName("Proteomics Standards Initiative Mass Spectrometry Ontology");
            // tempVar3->setid("MS");
            tempVar3->version("4.0.1");

            //need to set mzml
            // mzML->getcvList()->getcv()[0] = tempVar3;

            ms::mzml::CVType *tempVar4 = new ms::mzml::CVType("UO", "Unit Ontology", "(http://obo.cvs.sourceforge.net/*checkout*/obo/obo/ontology/phenotype/unit.obo)");
            // tempVar4->setURI(R"(http://obo.cvs.sourceforge.net/*checkout*/obo/obo/ontology/phenotype/unit.obo)");
            // tempVar4->setfullName("Unit Ontology");
            // tempVar4->setid("UO");
            tempVar4->version("12:10:2011");

            //need to set mzml
            // mzML->getcvList()->getcv()[1] = tempVar4;

            //add cvtypes to cvlist
            tempVar->cv()[0] = *tempVar3;
            tempVar->cv()[1] = *tempVar4;

            // ms::mzml::FileDescriptionType tempVar5();
            // mzML->setfileDescription(&tempVar5);
            ms::mzml::ParamGroupType tempVar6 = ms::mzml::ParamGroupType();
            ms::mzml::FileDescriptionType tempVar5 = ms::mzml::FileDescriptionType(tempVar6);
            // mzML->getfileDescription()->setfileContent(&tempVar6);

            ms::mzml::SourceFileListType tempVar7 = ms::mzml::SourceFileListType(1);
            // mzML->getfileDescription()->setsourceFileList(&tempVar7);

            if (myMsDataFile->getSourceFile()->getNativeIdFormat() != "" && myMsDataFile->getSourceFile()->getMassSpectrometerFileFormat() != "" && myMsDataFile->getSourceFile()->getFileChecksumType() != "")
            {
                ms::mzml::SourceFileListType tempVar8 = ms::mzml::SourceFileListType(1);

                // mzML->getfileDescription()->setsourceFileList(&tempVar8);
                // mzML->getfileDescription()->getsourceFileList()->setcount("1");
                // mzML->getfileDescription()->getsourceFileList()->setsourceFile(std::vector<ms::mzml::SourceFileType*>(1));
#ifdef ORIG
                std::string idName = char::IsNumber(myMsDataFile->getSourceFile()->getFileName()[0]) ? "id:" + myMsDataFile->getSourceFile()->getFileName()[0] : myMsDataFile->getSourceFile()->getFileName();
#endif

                std::string idName = isdigit(myMsDataFile->getSourceFile()->getFileName()[0]) ? "id:" + myMsDataFile->getSourceFile()->getFileName()[0] : myMsDataFile->getSourceFile()->getFileName();

                //TODO getFileName() in Uri class returns string of path.  This should be the same as getUri()->ToString()
                ms::mzml::SourceFileType *tempVar9 = new ms::mzml::SourceFileType(idName, myMsDataFile->getSourceFile()->getFileName(), myMsDataFile->getSourceFile()->getUri()->getFileName());
                tempVar8.sourceFile()[0] = *tempVar9;

//                 tempVar9->setid(idName);
//                 tempVar9->setname(myMsDataFile->getSourceFile()->getFileName());
// //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
//                 tempVar9->setlocation(myMsDataFile->getSourceFile()->getUri()->ToString());


                // mzML->getfileDescription()->getsourceFileList()->getsourceFile()[0] = tempVar9;

                // mzML->getfileDescription()->getsourceFileList()->getsourceFile()[0]->cvParam = std::vector<ms::mzml::CVParamType*>(3);


                ms::mzml::CVParamType *tempVar10 = new ms::mzml::CVParamType("MS", nativeIdFormatAccessions[myMsDataFile->getSourceFile()->getNativeIdFormat()], myMsDataFile->getSourceFile()->getNativeIdFormat());
                // tempVar10->setaccession(nativeIdFormatAccessions[myMsDataFile->getSourceFile()->getNativeIdFormat()]);
                // tempVar10->setname(myMsDataFile->getSourceFile()->getNativeIdFormat());
                // tempVar10->setcvRef("MS");
                tempVar10->value("");
                tempVar8.sourceFile()[0].cvParam().push_back(*tempVar10);
                // mzML->getfileDescription()->getsourceFileList()->getsourceFile()[0]->cvParam[0] = tempVar10;


                ms::mzml::CVParamType *tempVar11 = new ms::mzml::CVParamType("MS", MassSpectrometerFileFormatAccessions[myMsDataFile->getSourceFile()->getMassSpectrometerFileFormat()], myMsDataFile->getSourceFile()->getMassSpectrometerFileFormat());
                // tempVar11->setaccession(MassSpectrometerFileFormatAccessions[myMsDataFile->getSourceFile()->getMassSpectrometerFileFormat()]);
                // tempVar11->setname(myMsDataFile->getSourceFile()->getMassSpectrometerFileFormat());
                // tempVar11->setcvRef("MS");
                tempVar11->value("");
                tempVar8.sourceFile()[0].cvParam().push_back(*tempVar11);
                // mzML->getfileDescription()->getsourceFileList()->getsourceFile()[0]->cvParam[1] = tempVar11;


                ms::mzml::CVParamType *tempVar12 = new ms::mzml::CVParamType("MS", FileChecksumAccessions[myMsDataFile->getSourceFile()->getFileChecksumType()], myMsDataFile->getSourceFile()->getFileChecksumType());
                // tempVar12->setaccession(FileChecksumAccessions[myMsDataFile->getSourceFile()->getFileChecksumType()]);
                // tempVar12->setname(myMsDataFile->getSourceFile()->getFileChecksumType());
                // tempVar12->setcvRef("MS");
                

                //TODO:  getCheckSum returns string not pointer.  How to check if NULL? Use empty()? isnt that the same as s = ""?
                std::string tempVar13 = myMsDataFile->getSourceFile()->getCheckSum();
                
                //original
                // tempVar12->value((tempVar13 != nullptr) ? tempVar13 : "");
                tempVar12->value((!tempVar13.empty()) ? tempVar13 : "");
                // mzML->getfileDescription()->getsourceFileList()->getsourceFile()[0]->cvParam[2] = tempVar12;

                tempVar8.sourceFile()[0].cvParam().push_back(*tempVar12);
                // delete tempVar12;
                // delete tempVar11;
                // delete tempVar10;
                // delete tempVar9;

                //******************
                //SourceFileList is tempVar8
                //fileDescription is tempVar5
                //add sourcefilelist to filedescription
                tempVar5.sourceFileList(tempVar8);
            }



            // mzML->getfileDescription()->getfileContent()->setcvParam(std::vector<ms::mzml::CVParamType*>(2));
            ms::mzml::CVParamType *tempVar14 = new ms::mzml::CVParamType("MS", "MS:1000579", "MS1 spectrum");
            // tempVar14->setaccession("MS:1000579");
            // tempVar14->setname("MS1 spectrum");
            // tempVar14->setcvRef("MS");
            tempVar14->value("");
            tempVar5.fileContent().cvParam().push_back(*tempVar14);
            // mzML->getfileDescription()->getfileContent()->getcvParam()[0] = tempVar14;


            ms::mzml::CVParamType *tempVar15 = new ms::mzml::CVParamType("MS", "MS:1000580", "MSn spectrum");
            // tempVar15->setaccession("MS:1000580");
            // tempVar15->setname("MSn spectrum");
            // tempVar15->setcvRef("MS");
            tempVar15->value("");
            tempVar5.fileContent().cvParam().push_back(*tempVar15);
            // mzML->getfileDescription()->getfileContent()->getcvParam()[1] = tempVar15;

            ms::mzml::SoftwareListType *tempVar16 = new ms::mzml::SoftwareListType(2);
            // mzML->setsoftwareList(&tempVar16);
            // mzML->getsoftwareList()->setcount("2");
            // mzML->getsoftwareList()->setsoftware(std::vector<ms::mzml::SoftwareType*>(2));

            // TODO: add the raw file fields
            ms::mzml::SoftwareType *tempVar17 = new ms::mzml::SoftwareType("mzLib", "1");
            tempVar16->software()[0] = (*tempVar17);
            // tempVar17->setid("mzLib");
            // tempVar17->setversion("1");
            // tempVar17->cvParam(std::vector<ms::mzml::CVParamType*>(1));
            // mzML->getsoftwareList()->getsoftware()[0] = tempVar17;

            ms::mzml::CVParamType *tempVar18 = new ms::mzml::CVParamType("MS", "MS:1000799", "custom unreleased software tool");
            // tempVar18->setaccession("MS:1000799");
            tempVar18->value("mzLib");
            tempVar16->software()[0].cvParam().push_back(*tempVar18);
            // tempVar18->setname("custom unreleased software tool");
            // tempVar18->setcvRef("MS");
            // mzML->getsoftwareList()->getsoftware()[0]->cvParam[0] = tempVar18;

#ifdef ORIG
            // CS version:
            // List<MZAnalyzerType> analyzersInThisFile = (new HashSet<MZAnalyzerType>(myMsDataFile.GetAllScansList().S
            // Dictionary<MZAnalyzerType, string> analyzersInThisFileDict = new Dictionary<MZAnalyzerType, string>();
            std::vector<MZAnalyzerType> analyzersInThisFile = (std::unordered_set<MZAnalyzerType>(myMsDataFile->GetAllScansList().Select([&] (std::any b)
            {
                b::MzAnalyzer;
            })))->ToList();
            std::unordered_map<MZAnalyzerType, std::string> analyzersInThisFileDict;
#endif

            //TODO  Need to convert std::vector<MassSpectrometry::MsDataScan*> to std::unordered_set?
            std::vector<MassSpectrometry::MsDataScan*> dataScans = myMsDataFile->GetAllScansList();
            std::vector<MZAnalyzerType> analyzersInThisFile;
            for (auto i : dataScans){
                analyzersInThisFile.push_back(i->getMzAnalyzer());
            }

            std::unordered_map<MZAnalyzerType, std::string> analyzersInThisFileDict;
            // Leaving empty. Can't figure out the configurations.
            // ToDo: read instrumentConfigurationList from mzML file
            //original
            // ms::mzml::InstrumentConfigurationListType tempVar19 = new ms::mzml::InstrumentConfigurationListType(std::to_string(analyzersInThisFile.size()));
            ms::mzml::InstrumentConfigurationListType *tempVar19 = new ms::mzml::InstrumentConfigurationListType(analyzersInThisFile.size());

            // mzML->setinstrumentConfigurationList(&tempVar19);
            // mzML->getinstrumentConfigurationList()->setcount(std::to_string(analyzersInThisFile.size()));
            // mzML->getinstrumentConfigurationList()->setinstrumentConfiguration(std::vector<ms::mzml::InstrumentConfigurationType*>(analyzersInThisFile.size()));

            // Write the analyzers, also the default, also in the scans if needed
            //original
            // for (int i = 0; i < mzML->instrumentConfigurationList()->instrumentConfiguration().size(); i++)
            for (long long unsigned int i = 0; i < tempVar19->count(); i++)
            {
                //original
                analyzersInThisFileDict[analyzersInThisFile[i]] = "IC" + std::to_string(i + 1);
                ms::mzml::InstrumentConfigurationType *tempVar20 = new ms::mzml::InstrumentConfigurationType("IC" + std::to_string(i + 1));
                // tempVar20->setid("IC" + std::to_string(i + 1));
                ms::mzml::ComponentListType *tempVar21 = new ms::mzml::ComponentListType(3);
                tempVar20->componentList(*tempVar21);
                // tempVar20->cvParam(std::vector<ms::mzml::CVParamType*>(1));
                // mzML->instrumentConfigurationList()->instrumentConfiguration()[i] = tempVar20;

                ms::mzml::CVParamType *tempVar22 = new ms::mzml::CVParamType("MS", "MS:1000031", "instrument model");
                // tempVar22->setcvRef("MS");
                // tempVar22->setaccession("MS:1000031");
                // tempVar22->setname("instrument model");
                tempVar22->value("");
                tempVar20->cvParam().push_back(*tempVar22);
                // mzML->getinstrumentConfigurationList()->getinstrumentConfiguration()[i]->cvParam[0] = tempVar22;

                // mzML->instrumentConfigurationList()->instrumentConfiguration()[i]->componentList = new ms::mzml::ComponentListType();
                // .componentList->count = std::to_string(3);
                // .componentList->source = std::vector<ms::mzml::SourceComponentType*>(1);
                // .componentList->analyzer = std::vector<ms::mzml::AnalyzerComponentType*>(1);
                // .componentList->detector = std::vector<ms::mzml::DetectorComponentType*>(1);

                ms::mzml::SourceComponentType *tempVar23 = new ms::mzml::SourceComponentType(1);
                // tempVar23->setorder(1);
                // tempVar23->cvParam(std::vector<ms::mzml::CVParamType*>(1));

                //original
                // mzML->instrumentConfigurationList()->instrumentConfiguration()[i]->componentList.source[0] = tempVar23;
                ms::mzml::CVParamType *tempVar24 = new ms::mzml::CVParamType("MS", "MS:1000008", "ionization type");
                // tempVar24->setcvRef("MS");
                // tempVar24->setaccession("MS:1000008");
                // tempVar24->setname("ionization type");
                tempVar24->value("");
                tempVar23->cvParam().push_back(*tempVar24);
                // mzML->instrumentConfigurationList()->instrumentConfiguration()[i]->componentList.source[0].cvParam[0] = tempVar24;

                ms::mzml::AnalyzerComponentType *tempVar25 = new ms::mzml::AnalyzerComponentType(2);
                // tempVar25->setorder(2);
                // tempVar25->cvParam(std::vector<ms::mzml::CVParamType*>(1));
                // mzML->instrumentConfigurationList()->instrumentConfiguration()[i]->componentList.analyzer[0] = tempVar25;
                std::string anName = "";
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':

                //MzAnalyzerType is enum class with the following values:
                // Unknown = 0,
                // Quadrupole = 1,
                // IonTrap2D = 2,
                // IonTrap3D = 3,
                // Orbitrap = 4,
                // TOF = 5,
                // FTICR = 6,
                // Sector = 7

                //original
                // if (analyzersInThisFile[i].ToString()->ToLower() == "unknown")
                if (analyzersInThisFile[i] == MZAnalyzerType::Unknown)
                {
                    anName = "mass analyzer type";
                }
                else
                {
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
                    //original
                    // anName = analyzersInThisFile[i].ToString()->ToLower();

                    if (analyzersInThisFile[i] == MZAnalyzerType::Quadrupole)
                        anName = "Quadrupole";
                    else if (analyzersInThisFile[i] == MZAnalyzerType::IonTrap2D)
                        anName = "IonTrap2D";
                    else if (analyzersInThisFile[i] == MZAnalyzerType::IonTrap3D)
                        anName = "IonTrap3D";
                    else if (analyzersInThisFile[i] == MZAnalyzerType::Orbitrap)
                        anName = "Orbitrap";
                    else if (analyzersInThisFile[i] == MZAnalyzerType::TOF)
                        anName = "TOF";
                    else if (analyzersInThisFile[i] == MZAnalyzerType::FTICR)
                        anName = "FTICR";
                    else if (analyzersInThisFile[i] == MZAnalyzerType::Sector)
                        anName = "Sector";
                }

                //cvParam for analyzerComponentType
                ms::mzml::CVParamType *tempVar26 = new ms::mzml::CVParamType("MS", analyzerDictionary[analyzersInThisFile[i]], anName);
                // tempVar26->setcvRef("MS");
                // tempVar26->setaccession(analyzerDictionary[analyzersInThisFile[i]]);
                // tempVar26->setname(anName);
                tempVar26->value("");
                tempVar25->cvParam().push_back(*tempVar26);
                // mzML->getinstrumentConfigurationList()->getinstrumentConfiguration()[i]->componentList.analyzer[0].cvParam[0] = tempVar26;

                ms::mzml::DetectorComponentType *tempVar27 = new ms::mzml::DetectorComponentType(3);
                // tempVar27->setorder(3);
                // tempVar27->cvParam(std::vector<ms::mzml::CVParamType*>(1));
                // mzML->getinstrumentConfigurationList()->getinstrumentConfiguration()[i]->componentList.detector[0] = tempVar27;
                ms::mzml::CVParamType *tempVar28 = new ms::mzml::CVParamType("MS", "MS:1000026", "detector type");
                // tempVar28->setcvRef("MS");
                // tempVar28->setaccession("MS:1000026");
                // tempVar28->setname("detector type");
                tempVar28->value("");
                tempVar27->cvParam().push_back(*tempVar28);
                // mzML->getinstrumentConfigurationList()->getinstrumentConfiguration()[i]->componentList.detector[0].cvParam[0] = tempVar28;

                //add sourcecomponenttype (tempVar23), analyzer component type (tempVar25), and detector component type (tempVar27) to component list type (tempVar21)
                tempVar21->source().push_back(*tempVar23);
                tempVar21->analyzer().push_back(*tempVar25);
                tempVar21->detector().push_back(*tempVar27);

                //add instrumentConfiguration (tempVar20) to instrumentonfigurationList (tmepVar19)
                tempVar19->instrumentConfiguration().push_back(*tempVar20);

                delete tempVar28;
                delete tempVar27;
                delete tempVar26;
                delete tempVar25;
                delete tempVar24;
                delete tempVar23;
                delete tempVar22;
                delete tempVar20;
            }

            ms::mzml::DataProcessingListType *tempVar29 = new ms::mzml::DataProcessingListType(1);
            // mzML->setdataProcessingList(&tempVar29);
            // mzML->getdataProcessingList()->setcount("1");
            // mzML->getdataProcessingList()->setdataProcessing(std::vector<ms::mzml::DataProcessingType*>(1));

            // Only writing mine! Might have had some other data processing (but not if it is a raw file)
            // ToDo: read dataProcessingList from mzML file
            ms::mzml::DataProcessingType *tempVar30 = new ms::mzml::DataProcessingType("mzLibProcessing");
            // tempVar30->setid("mzLibProcessing");
            // tempVar30->processingMethod(std::vector<ms::mzml::ProcessingMethodType*>(1));
            // mzML->getdataProcessingList()->getdataProcessing()[0] = tempVar30;
            tempVar29->dataProcessing()[0] = *tempVar30;

            ms::mzml::ProcessingMethodType *tempVar31 = new ms::mzml::ProcessingMethodType(0, "mzLib");
            // tempVar31->setorder("0");
            // tempVar31->setsoftwareRef("mzLib");
            // tempVar31->cvParam(std::vector<ms::mzml::CVParamType*>(1));
            // mzML->getdataProcessingList()->getdataProcessing()[0]->processingMethod[0] = tempVar31;

            ms::mzml::CVParamType *tempVar32 = new ms::mzml::CVParamType("MS", "MS:1000544", "Conversion to mzML");
            // tempVar32->setaccession("MS:1000544");
            // tempVar32->setcvRef("MS");
            // tempVar32->setname("Conversion to mzML");
            tempVar32->value("");

            //add cvparam to processingmethodtype (tempVar31)
            tempVar31->cvParam().push_back(*tempVar32);
            // mzML->getdataProcessingList()->getdataProcessing()[0]->processingMethod[0].cvParam[0] = tempVar32;

            ms::mzml::RunType *tempVar33 = new ms::mzml::RunType(idTitle, analyzersInThisFileDict[analyzersInThisFile[0]]);
            // mzML->setrun(&tempVar33);
            // mzML->getrun()->setdefaultInstrumentConfigurationRef(analyzersInThisFileDict[analyzersInThisFile[0]]);
            // mzML->getrun()->setid(idTitle);

            //---------------------------------------------
            //Can now create instance of mzMLType
            //arguments needed for constructor:  
            //cvList_type   -> *tempVar
            //fileDescription_type   -> tempVar5
            //softwareList_type   -> *tempVar16
            //instrumentConfigurationList_type   -> *tempVar19
            //dataProcessingList_type   -> *tempVar29
            //run_type   -> *tempVar33
            //version_type   -> "1.1.0"
            ms::mzml::mzMLType *mzML_type = new ms::mzml::mzMLType(*tempVar, tempVar5, *tempVar16, *tempVar19, *tempVar29, *tempVar33, "1.1.0");


            ms::mzml::ChromatogramListType *tempVar34 = new ms::mzml::ChromatogramListType(1, "mzLibProcessing");
            // mzML->getrun()->setchromatogramList(&tempVar34);
            // // mzML->getrun()->getchromatogramList()->setcount("1");
            // mzML->getrun()->getchromatogramList()->setchromatogram(std::vector<ms::mzml::ChromatogramType*>(1));
            // mzML->getrun()->getchromatogramList()->setdefaultDataProcessingRef("mzLibProcessing");
            mzML_type->run().chromatogramList(*tempVar34);

            //Chromatagram info
            // ms::mzml::ChromatogramType *tempVar35 = new ms::mzml::ChromatogramType();
            // tempVar35->setdefaultArrayLength(myMsDataFile->getNumSpectra());
            // tempVar35->setid("TIC");
            // tempVar35->setindex("0");
            // tempVar35->setdataProcessingRef("mzLibProcessing");
            ms::mzml::BinaryDataArrayListType *tempVar36 = new ms::mzml::BinaryDataArrayListType(2);

            ms::mzml::ChromatogramType *tempVar35 = new ms::mzml::ChromatogramType(*tempVar36, "TIC", 0, myMsDataFile->getNumSpectra());
            // tempVar35->setdefaultArrayLength(myMsDataFile->getNumSpectra());
            // tempVar35->setid("TIC");
            // tempVar35->setindex("0");
            tempVar35->dataProcessingRef("mzLibProcessing");

            // tempVar35->setbinaryDataArrayList(&tempVar36);
            // tempVar35->getbinaryDataArrayList()->setcount("2");
            // tempVar35->getbinaryDataArrayList()->setbinaryDataArray(std::vector<ms::mzml::BinaryDataArrayType*>(2));
            // tempVar35->setcvParam(std::vector<ms::mzml::CVParamType*>(1));
            mzML_type->run().chromatogramList()->chromatogram()[0] = *tempVar35;

            ms::mzml::CVParamType *tempVar37 = new ms::mzml::CVParamType("MS", "MS:1000235", "total ion current chromatogram");
            // tempVar37->setaccession("MS:1000235");
            // tempVar37->setname("total ion current chromatogram");
            // tempVar37->setcvRef("MS");
            tempVar37->value("");
            mzML_type->run().chromatogramList()->chromatogram()[0].cvParam()[0] = *tempVar37;

            std::vector<double> times(myMsDataFile->getNumSpectra());
            std::vector<double> intensities(myMsDataFile->getNumSpectra());

            for (int i = 1; i <= myMsDataFile->getNumSpectra(); i++)
            {
                times[i - 1] = myMsDataFile->GetOneBasedScan(i)->getRetentionTime();
                //original
                // intensities[i - 1] = myMsDataFile->GetOneBasedScan(i)->MassSpectrum.SumOfAllY;
                intensities[i - 1] = myMsDataFile->GetOneBasedScan(i)->getMassSpectrum()->getSumOfAllY();
            }



            //Chromatofram X axis (time)
            //original
            // ms::mzml::BinaryDataArrayType *tempVar38 = new ms::mzml::BinaryDataArrayType();
            // tempVar38->setbinary(MzSpectrum::Get64Bitarray(times));
            //TODO:  original C# is binary.Length...does this mean the length of a string? if so C++ version should be binary().encode().length(), encode() to get string
            // double binsize = static_cast<double>(mzML->run().chromatogramList()->chromatogram()[0].binaryDataArrayList().binaryDataArray()[0].binary().encode().length()) / 3;
            std::vector<unsigned char> bin_times_vector = MzSpectrum::Get64Bitarray(times);
            xml_schema::base64_binary bindata(bin_times_vector.size());  

            //iterate through unsigned char bin_times_vector and copy each element to base^$_binary bindata buffer
            auto it_vector = bin_times_vector.begin();
            for (auto it_binary = bindata.begin(); it_binary != bindata.end(); ++it_binary) {
                *it_binary = *it_vector;;
                it_vector++;
            }

            //TODO uses .ToString(CultureInfo::InvariantCulture).  is that the same as std::to_string(double)?
            ms::mzml::BinaryDataArrayType *tempVar38 = new ms::mzml::BinaryDataArrayType(bindata, 4 * std::ceil((static_cast<double>(mzML_type->run().chromatogramList()->chromatogram()[0].binaryDataArrayList().binaryDataArray()[0].binary().encode().length()) / 3)));
            mzML_type->run().chromatogramList()->chromatogram()[0].binaryDataArrayList().binaryDataArray()[0] = *tempVar38;




//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
            // mzML->getrun()->getchromatogramList()->getchromatogram()[0]->binaryDataArrayList.binaryDataArray[0]->encodedLength = (4 * std::ceil((static_cast<double>(mzML->getrun()->getchromatogramList()->getchromatogram()[0]->binaryDataArrayList.binaryDataArray[0].binary->Length) / 3))).ToString(CultureInfo::InvariantCulture);

            // mzML->run().chromatogramList()->chromatogram()[0].binaryDataArrayList().binaryDataArray()[0]->cvParam() = std::vector<ms::mzml::CVParamType*>(3);

            ms::mzml::CVParamType *tempVar39 = new ms::mzml::CVParamType("MS","MS:1000523","64-bit float");
            // tempVar39->setaccession("MS:1000523");
            // tempVar39->setname("64-bit float");
            // tempVar39->setcvRef("MS");
            tempVar39->value("");
            mzML_type->run().chromatogramList()->chromatogram()[0].binaryDataArrayList().binaryDataArray()[0].cvParam().push_back(*tempVar39);

            ms::mzml::CVParamType *tempVar40 = new ms::mzml::CVParamType("MS", "MS:1000576", "no compression");
            // tempVar40->setaccession("MS:1000576");
            // tempVar40->setname("no compression");
            // tempVar40->setcvRef("MS");
            tempVar40->value("");
            //original
            // mzML->getrun()->getchromatogramList()->getchromatogram()[0]->binaryDataArrayList.binaryDataArray[0].cvParam[1] = tempVar40;
            mzML_type->run().chromatogramList()->chromatogram()[0].binaryDataArrayList().binaryDataArray()[0].cvParam().push_back(*tempVar40);

            ms::mzml::CVParamType *tempVar41 = new ms::mzml::CVParamType("MS", "MS:1000595", "time array");
            // tempVar41->setaccession("MS:1000595");
            // tempVar41->setname("time array");
            tempVar41->unitCvRef("UO");
            tempVar41->unitAccession("UO:0000031");
            tempVar41->unitName("Minutes");
            // tempVar41->setcvRef("MS");
            tempVar41->value("");
            //original
            // mzML->getrun()->getchromatogramList()->getchromatogram()[0]->binaryDataArrayList.binaryDataArray[0].cvParam[2] = tempVar41;
            mzML_type->run().chromatogramList()->chromatogram()[0].binaryDataArrayList().binaryDataArray()[0].cvParam().push_back(*tempVar40);



            //TODO figure out binary64 type conversion
            //Chromatogram Y axis (total intensity)
            //uses CultureInfo.InvariantCulture

            std::vector<unsigned char> bin_intensities_vector = MzSpectrum::Get64Bitarray(intensities);
            xml_schema::base64_binary bindata_intensities(bin_intensities_vector.size());  

            //iterate through unsigned char bin_times_vector and copy each element to base^$_binary bindata buffer
            it_vector = bin_intensities_vector.begin();
            for (auto it_binary = bindata_intensities.begin(); it_binary != bindata_intensities.end(); ++it_binary) {
                *it_binary = *it_vector;;
                it_vector++;
            }
            ms::mzml::BinaryDataArrayType *tempVar42 = new ms::mzml::BinaryDataArrayType(bindata_intensities, 4 * std::ceil((static_cast<double>(mzML_type->run().chromatogramList()->chromatogram()[0].binaryDataArrayList().binaryDataArray()[1].binary().encode().length()) / 3)));
            // tempVar42->setbinary(MzSpectrum::Get64Bitarray(intensities));


            mzML_type->run().chromatogramList()->chromatogram()[0].binaryDataArrayList().binaryDataArray()[1] = *tempVar42;

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
            // mzML->getrun()->getchromatogramList()->getchromatogram()[0]->binaryDataArrayList.binaryDataArray[1]->encodedLength = (4 * std::ceil((static_cast<double>(mzML->getrun()->getchromatogramList()->getchromatogram()[0]->binaryDataArrayList.binaryDataArray[1].binary->Length) / 3))).ToString(CultureInfo::InvariantCulture);





            // mzML->getrun()->getchromatogramList()->getchromatogram()[0]->binaryDataArrayList.binaryDataArray[1]->cvParam = std::vector<ms::mzml::CVParamType*>(3);

            ms::mzml::CVParamType *tempVar43 = new ms::mzml::CVParamType("MS", "MS:1000523", "64-bit float");
            // tempVar43->setaccession("MS:1000523");
            // tempVar43->setname("64-bit float");
            // tempVar43->setcvRef("MS");
            tempVar43->value("");
            mzML_type->run().chromatogramList()->chromatogram()[0].binaryDataArrayList().binaryDataArray()[1].cvParam().push_back(*tempVar43);

            ms::mzml::CVParamType *tempVar44 = new ms::mzml::CVParamType("MS", "MS:1000576", "no compression");
            // tempVar44->setaccession("MS:1000576");
            // tempVar44->setname("no compression");
            // tempVar44->setcvRef("MS");
            tempVar44->value("");
            mzML_type->run().chromatogramList()->chromatogram()[0].binaryDataArrayList().binaryDataArray()[1].cvParam().push_back(*tempVar44);

            ms::mzml::CVParamType *tempVar45 = new ms::mzml::CVParamType("MS", "MS:1000515", "intensity array");
            // tempVar45->setaccession("MS:1000515");
            // tempVar45->setname("intensity array");
            // tempVar45->setCvRef("MS");
            tempVar45->unitAccession("MS:1000131");
            tempVar45->unitName("number of counts");
            tempVar45->unitCvRef("MS");
            tempVar45->value("");
            mzML_type->run().chromatogramList()->chromatogram()[0].binaryDataArrayList().binaryDataArray()[1].cvParam().push_back(*tempVar45);

            //original
//             ms::mzml::SpectrumListType tempVar46();
//             mzML->getrun()->setspectrumList(&tempVar46);
// //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
//             mzML->getrun()->getspectrumList()->setcount((myMsDataFile->getNumSpectra()).ToString(CultureInfo::InvariantCulture));
//             mzML->getrun()->getspectrumList()->setdefaultDataProcessingRef("mzLibProcessing");
//             mzML->getrun()->getspectrumList()->setspectrum(std::vector<ms::mzml::SpectrumType*>(myMsDataFile->getNumSpectra()));

            ms::mzml::SpectrumListType *tempVar46 = new ms::mzml::SpectrumListType((myMsDataFile->getNumSpectra()), "mzLibProcessing");
            mzML_type->run().spectrumList(*tempVar46);
            // mzML->run().spectrumList().spectrum();


            // Loop over all spectra
            for (int i = 1; i <= myMsDataFile->getNumSpectra(); i++)
            {
                //id, index, defaultarraylength
                //TODO CultureInfo::InvariantCulture
                ms::mzml::SpectrumType *tempVar47 = new ms::mzml::SpectrumType(myMsDataFile->GetOneBasedScan(i)->getNativeId(), i - 1, myMsDataFile->GetOneBasedScan(i)->getMassSpectrum()->getYArray().size());
                // tempVar47->setdefaultArrayLength(myMsDataFile->GetOneBasedScan(i)->MassSpectrum.YArray->Length);
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
                // tempVar47->setindex((i - 1).ToString(CultureInfo::InvariantCulture));
                tempVar47->id(myMsDataFile->GetOneBasedScan(i)->getNativeId());


                //push back 9 cvparams for tempVar47
                // tempVar47->cvParam(std::vector<ms::mzml::CVParamType*>(9));

                //original
                // ms::mzml::ScanListType tempVar48();
                ms::mzml::ScanListType *tempVar48 = new ms::mzml::ScanListType(0);
                tempVar47->scanList(*tempVar48);

                //need 9 cvparams
                mzML_type->run().spectrumList()->spectrum()[i - 1] = *tempVar47;


                ms::mzml::ScanListType *tempScanList = new ms::mzml::ScanListType(1);
                mzML_type->run().spectrumList()->spectrum()[i - 1].scanList(*tempScanList);
                // .scanList->count = std::to_string(1);

                //TODO push_back scantype and cvparamtype?
                // .scanList->scan = std::vector<ms::mzml::ScanType*>(1);
                // .scanList->cvParam = std::vector<ms::mzml::CVParamType*>(1);

                if (myMsDataFile->GetOneBasedScan(i)->getMsnOrder() == 1)
                {
                    ms::mzml::CVParamType *tempVar49 = new ms::mzml::CVParamType("MS", "MS:1000579", "MS1 spectrum");
                    // tempVar49->setaccession("MS:1000579");
                    // tempVar49->setcvRef("MS");
                    // tempVar49->setname("MS1 spectrum");
                    tempVar49->value("");
                    mzML_type->run().spectrumList()->spectrum()[i - 1].cvParam().push_back(*tempVar49);

                    //TODO will this delete list entry above?
                    delete tempVar49;
                }
                else if (myMsDataFile->GetOneBasedScan(i)->getMsnOrder() != 1)
                {
                    auto scanWithPrecursor = myMsDataFile->GetOneBasedScan(i);
                    ms::mzml::CVParamType *tempVar50 = new ms::mzml::CVParamType("MS", "MS:1000580", "MSn spectrum");
                    // tempVar50->setaccession("MS:1000580");
                    // tempVar50->setcvRef("MS");
                    // tempVar50->setname("MSn spectrum");
                    tempVar50->value("");

                    //TODO is push_back appropriate here?
                    mzML_type->run().spectrumList()->spectrum()[i - 1].cvParam().push_back(*tempVar50);

                    // So needs a precursor!
                    //original
                    // mzML->run().spectrumList()->spectrum()[i - 1].precursorList() = new ms::mzml::PrecursorListType(1);
                    // .precursorList->count = std::to_string(1);

                    ms::mzml::PrecursorListType *tempPrecursor = new ms::mzml::PrecursorListType(1);
                    mzML_type->run().spectrumList()->spectrum()[i - 1].precursorList() = *tempPrecursor;

                    //original, is push_back OK?
                    // .precursorList->precursor = std::vector<ms::mzml::PrecursorType*>(1);
                    // mzML->run().spectrumList()->spectrum()[i - 1].precursorList()->precursor() = std::vector<ms::mzml::PrecursorType*>(1);

                    //PrecursorType needs activationType in constructor.  This is defined on lines 893 - 904.  those lines have been modified and moved here
                    ms::mzml::ParamGroupType *tempActivation = new ms::mzml::ParamGroupType();
                    DissociationType dissociationType = scanWithPrecursor->getDissociationType().value();
                    ms::mzml::CVParamType *activationCVParam = new ms::mzml::CVParamType("MS", DissociationTypeAccessions[dissociationType], DissociationTypeNames[dissociationType]);
                    activationCVParam->value("");
                    //original
                    // mzML->run().spectrumList()->spectrum()[i - 1].precursor()[0].activation().cvParam()[0]->value() = "";
                    // mzML->run().spectrumList()->spectrum()[i - 1].precursorList()[0].activation().cvParam()[0]->value() = "";
                    ms::mzml::PrecursorType *tempVar51 = new ms::mzml::PrecursorType(*tempActivation);
                    ms::mzml::SelectedIonListType *tempVar52 = new ms::mzml::SelectedIonListType(1);
                    tempVar51->selectedIonList(*tempVar52);
                    // tempVar51->selectedIonList()->count(std::to_string(1));
                    // tempVar51->selectedIonList()->selectedIon(std::vector<ms::mzml::ParamGroupType*>(1));
                    ms::mzml::ParamGroupType *selectedIonParam = new ms::mzml::ParamGroupType();
                    tempVar51->selectedIonList()->selectedIon().push_back(*selectedIonParam);

                    mzML_type->run().spectrumList()->spectrum()[i - 1].precursorList()->precursor()[0] = *tempVar51;
                    mzML_type->run().spectrumList()->spectrum()[i - 1].precursorList()->precursor()[0].activation().cvParam().push_back(*activationCVParam);

                    if (scanWithPrecursor->getOneBasedPrecursorScanNumber())
                    {
                        std::string precursorID = myMsDataFile->GetOneBasedScan(scanWithPrecursor->getOneBasedPrecursorScanNumber().value())->getNativeId();
                        mzML_type->run().spectrumList()->spectrum()[i - 1].precursorList()->precursor()[0].spectrumRef() = precursorID;
                    }

                    ms::mzml::ParamGroupType *tempVar53 = new ms::mzml::ParamGroupType();

                    //pushback 3 cvparams
                    // tempVar53->cvParam(std::vector<ms::mzml::CVParamType*>(3));
                    mzML_type->run().spectrumList()->spectrum()[i - 1].precursorList()->precursor()[0].selectedIonList()->selectedIon()[0] = *tempVar53;

                    // Selected ion MZ
                    ms::mzml::CVParamType *tempVar54 = new ms::mzml::CVParamType("MS", "MS:1000744", "selected ion m/z");
                    // tempVar54->setname("selected ion m/z");
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':

                    //ToString(CultureInfo::InvariantCulture))
                    tempVar54->value(std::to_string(scanWithPrecursor->getSelectedIonMZ().value()));
                    // tempVar54->setaccession("MS:1000744");
                    // tempVar54->setcvRef("MS");
                    tempVar54->unitCvRef("MS");
                    tempVar54->unitAccession("MS:1000040");
                    tempVar54->unitName("m/z");
                    //original
                    // mzML_type->run().spectrumList()->spectrum()[i - 1].precursorList()->precursor()[0].selectedIonList()->selectedIon()[0].cvParam()[0] = tempVar54;
                    mzML_type->run().spectrumList()->spectrum()[i - 1].precursorList()->precursor()[0].selectedIonList()->selectedIon()[0].cvParam().push_back(*tempVar54);

                    // Charge State
                    if (scanWithPrecursor->getSelectedIonChargeStateGuess())
                    {
                        ms::mzml::CVParamType *tempVar55 = new ms::mzml::CVParamType("MS", "MS:1000041", "charge state");
                        // tempVar55->setname("charge state");
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':

                        //ToString(CultureInfo::InvariantCulture))
                        tempVar55->value(std::to_string(scanWithPrecursor->getSelectedIonChargeStateGuess().value()));
                        // tempVar55->setaccession("MS:1000041");
                        // tempVar55->setcvRef("MS", );
                        //original
                        // mzML_type->run().spectrumList()->spectrum()[i - 1].precursorList()->precursor()[0].selectedIonList()->selectedIon()[0].cvParam()[1] = tempVar55;
                        mzML_type->run().spectrumList()->spectrum()[i - 1].precursorList()->precursor()[0].selectedIonList()->selectedIon()[0].cvParam().push_back(*tempVar55);

                        delete tempVar55;
                    }

                    // Selected ion intensity
                    if (scanWithPrecursor->getSelectedIonIntensity())
                    {
                        ms::mzml::CVParamType *tempVar56 = new ms::mzml::CVParamType("MS", "MS:1000042", "peak intensity");
                        // tempVar56->setname("peak intensity");
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':

                        //ToString(CultureInfo::InvariantCulture))
                        tempVar56->value(std::to_string(scanWithPrecursor->getSelectedIonIntensity().value()));
                        // tempVar56->setaccession("MS:1000042");
                        // tempVar56->setcvRef("MS");
                        //original
                        // mzML_type->run().spectrumList()->spectrum()[i - 1].precursorList()->precursor()[0].selectedIonList()->selectedIon()[0].cvParam()[2] = tempVar56;
                        mzML_type->run().spectrumList()->spectrum()[i - 1].precursorList()->precursor()[0].selectedIonList()->selectedIon()[0].cvParam().push_back(*tempVar56);

                        delete tempVar56;
                    }
                    if (scanWithPrecursor->getIsolationMz())
                    {
                        MzRange *isolationRange = scanWithPrecursor->getIsolationRange();
                        
                        //original
                        // mzML_type->run().spectrumList()->spectrum()[i - 1].precursorList()->precursor()[0]->isolationWindow() = new ms::mzml::ParamGroupType();
                        ms::mzml::ParamGroupType *isolationWindowParam = new ms::mzml::ParamGroupType();
                        mzML_type->run().spectrumList()->spectrum()[i - 1].precursorList()->precursor()[0].isolationWindow() = *isolationWindowParam;

                        //push back 3 cvparams
                        // .isolationWindow->cvParam = std::vector<ms::mzml::CVParamType*>(3);
                        ms::mzml::CVParamType *tempVar57 = new ms::mzml::CVParamType("MS", "MS:1000827", "isolation window target m/z");
                        // tempVar57->setaccession("MS:1000827");
                        // tempVar57->setname("isolation window target m/z");
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':

                        //uses ToString(CultureInfo::InvariantCulture))
                        tempVar57->value(std::to_string(isolationRange->getMean()));
                        // tempVar57->setcvRef("MS");
                        tempVar57->unitCvRef("MS");
                        tempVar57->unitAccession("MS:1000040");
                        tempVar57->unitName("m/z");

                        //original
                        // mzML_type->run().spectrumList()->spectrum()[i - 1].precursorList()->precursor()[0].isolationWindow()->cvParam()[0] = tempVar57;
                        mzML_type->run().spectrumList()->spectrum()[i - 1].precursorList()->precursor()[0].isolationWindow()->cvParam().push_back(*tempVar57);

                        ms::mzml::CVParamType *tempVar58 = new ms::mzml::CVParamType("MS", "MS:1000828", "isolation window lower offset");
                        // tempVar58->setaccession("MS:1000828");
                        // tempVar58->setname("isolation window lower offset");
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':

                        //uses ToString(CultureInfo::InvariantCulture))
                        tempVar58->value(std::to_string(isolationRange->getWidth() / 2));
                        // tempVar58->setcvRef("MS");
                        tempVar58->unitCvRef("MS");
                        tempVar58->unitAccession("MS:1000040");
                        tempVar58->unitName("m/z");
                        //original
                        // mzML_type->run().spectrumList()->spectrum()[i - 1].precursorList()->precursor()[0].isolationWindow()->cvParam()[1] = tempVar58;
                        mzML_type->run().spectrumList()->spectrum()[i - 1].precursorList()->precursor()[0].isolationWindow()->cvParam().push_back(*tempVar58);

                        ms::mzml::CVParamType *tempVar59 = new ms::mzml::CVParamType("MS", "MS:1000829", "isolation window upper offset");
                        // tempVar59->accession("MS:1000829");
                        // tempVar59->name("isolation window upper offset");
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':

                        //uses CultureInfo::InvariantCulture
                        tempVar59->value(std::to_string(isolationRange->getWidth() / 2));
                        // tempVar59->cvRef("MS");
                        tempVar59->unitCvRef("MS");
                        tempVar59->unitAccession("MS:1000040");
                        tempVar59->unitName("m/z");
                        //original
                        // mzML_type->run().spectrumList()->spectrum()[i - 1].precursorList()->precursor()[0].isolationWindow()->cvParam()[2] = tempVar59;
                        mzML_type->run().spectrumList()->spectrum()[i - 1].precursorList()->precursor()[0].isolationWindow()->cvParam().push_back(*tempVar59);

                        delete tempVar59;
                        delete tempVar58;
                        delete tempVar57;
                    }
                    // mzML->run().spectrumList()->spectrum()[i - 1].precursorList()->precursor()[0].activation() = new ms::mzml::ParamGroupType();
                    // .activation->cvParam = std::vector<ms::mzml::CVParamType*>(1);
                    // mzML->run().spectrumList()->spectrum()[i - 1].precursorList()->precursor()[0].activation().cvParam()[0] = new ms::mzml::CVParamType();

                    // DissociationType dissociationType = scanWithPrecursor->getDissociationType().value();

                    // mzML->run().spectrumList()->spectrum()[i - 1].precursorList()->precursor()[0].activation().cvParam()[0].accession() = DissociationTypeAccessions[dissociationType];
                    // mzML->run().spectrumList()->spectrum()[i - 1].precursorList()->precursor()[0].activation().cvParam()[0].name() = DissociationTypeNames[dissociationType];
                    // mzML->run().spectrumList()->spectrum()[i - 1].precursorList()->precursor()[0].activation().cvParam()[0].cvRef() = "MS";
                    // //original
                    // // mzML->run().spectrumList()->spectrum()[i - 1].precursor()[0].activation().cvParam()[0]->value() = "";
                    // mzML->run().spectrumList()->spectrum()[i - 1].precursorList()[0].activation().cvParam()[0]->value() = "";

                    delete tempVar54;
                    delete tempVar53;
                    delete tempVar51;
                    delete tempVar50;
                }

                ms::mzml::CVParamType *tempVar60 = new ms::mzml::CVParamType("MS", "MS:1000511", "ms level");
                // tempVar60->setname("ms level");
                // tempVar60->setaccession("MS:1000511");
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':

                //ToString(CultureInfo::InvariantCulture)
                tempVar60->value(std::to_string(myMsDataFile->GetOneBasedScan(i)->getMsnOrder()));
                // tempVar60->setcvRef("MS");
                //original
                // mzML_type->run().spectrumList()->spectrum()[i - 1].cvParam()[1] = tempVar60;
                mzML_type->run().spectrumList()->spectrum()[i - 1].cvParam().push_back(*tempVar60);

                ms::mzml::CVParamType *tempVar61 = new ms::mzml::CVParamType("MS", CentroidAccessions[myMsDataFile->GetOneBasedScan(i)->getIsCentroid()], CentroidNames[myMsDataFile->GetOneBasedScan(i)->getIsCentroid()]);
                // tempVar61->setname(CentroidNames[myMsDataFile->GetOneBasedScan(i)->getIsCentroid()]);
                // tempVar61->setaccession(CentroidAccessions[myMsDataFile->GetOneBasedScan(i)->getIsCentroid()]);
                // tempVar61->setcvRef("MS");
                tempVar61->value("");
                //original
                // mzML_type->run().spectrumList()->spectrum()[i - 1].cvParam()[2] = tempVar61;
                mzML_type->run().spectrumList()->spectrum()[i - 1].cvParam().push_back(*tempVar61);

                std::string polarityName;
                std::string polarityAccession;
                std::unordered_map<Polarity, std::string>::const_iterator PolarityAccessions_iterator = PolarityAccessions.find(myMsDataFile->GetOneBasedScan(i)->getPolarity());
                std::unordered_map<Polarity, std::string>::const_iterator PolarityNames_iterator = PolarityNames.find(myMsDataFile->GetOneBasedScan(i)->getPolarity());
                if (PolarityNames_iterator != PolarityNames.end() && PolarityAccessions_iterator != PolarityAccessions.end())
                {
                    polarityName = PolarityNames_iterator->second;
                    polarityAccession = PolarityAccessions_iterator->second;
                    ms::mzml::CVParamType *tempVar62 = new ms::mzml::CVParamType("MS", polarityAccession, polarityName);
                    // tempVar62->setname(polarityName);
                    // tempVar62->setaccession(polarityAccession);
                    // tempVar62->setcvRef("MS");
                    tempVar62->value("");
                    //original
                    // mzML_type->run().spectrumList()->spectrum()[i - 1].cvParam()[3] = tempVar62;
                    mzML_type->run().spectrumList()->spectrum()[i - 1].cvParam().push_back(*tempVar62);

                    delete tempVar62;
                }
                else
                {
                    polarityName = PolarityNames_iterator->second;
                    polarityAccession = PolarityAccessions_iterator->second;
                }
                // Spectrum title
                //string title = System.IO.Path.GetFileNameWithoutExtension(outputFile);

                if ((myMsDataFile->GetOneBasedScan(i)->getMassSpectrum()->getSize()) > 0)
                {
                    // Lowest observed mz
                    ms::mzml::CVParamType *tempVar63 = new ms::mzml::CVParamType("MS", "MS:1000528", "lowest observed m/z");
                    // tempVar63->setname("lowest observed m/z");
                    // tempVar63->setaccession("MS:1000528");
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':

                    //ToString(CultureInfo::InvariantCulture)
                    tempVar63->value(std::to_string(myMsDataFile->GetOneBasedScan(i)->getMassSpectrum()->getFirstX().value()));
                    tempVar63->unitCvRef("MS");
                    tempVar63->unitAccession("MS:1000040");
                    tempVar63->unitName("m/z");
                    // tempVar63->setcvRef("MS");
                    //original
                    // mzML_type->run().spectrumList()->spectrum()[i - 1].cvParam()[4] = tempVar63;
                    mzML_type->run().spectrumList()->spectrum()[i - 1].cvParam().push_back(*tempVar63);

                    // Highest observed mz
                    ms::mzml::CVParamType *tempVar64 = new ms::mzml::CVParamType("MS", "MS:1000527", "highest observed m/z");
                    // tempVar64->setname("highest observed m/z");
                    // tempVar64->setaccession("MS:1000527");
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':

                    //ToString(CultureInfo::InvariantCulture)
                    tempVar64->value(std::to_string(myMsDataFile->GetOneBasedScan(i)->getMassSpectrum()->getLastX().value()));
                    tempVar64->unitAccession("MS:1000040");
                    tempVar64->unitName("m/z");
                    tempVar64->unitCvRef("MS");
                    // tempVar64->setcvRef("MS");
                    //original
                    // mzML_type->run().spectrumList()->spectrum()[i - 1].cvParam()[5] = tempVar64;
                    mzML_type->run().spectrumList()->spectrum()[i - 1].cvParam().push_back(*tempVar64);

                    delete tempVar64;
                    delete tempVar63;
                }

                // Total ion current
                ms::mzml::CVParamType *tempVar65 = new ms::mzml::CVParamType("MS", "MS:1000285", "total ion current");
                // tempVar65->setname("total ion current");
                // tempVar65->setaccession("MS:1000285");
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':

                //ToString(CultureInfo::InvariantCulture)
                tempVar65->value(std::to_string(myMsDataFile->GetOneBasedScan(i)->getTotalIonCurrent()));
                // tempVar65->setcvRef("MS");
                //original
                // mzML_type->run().spectrumList()->spectrum()[i - 1]->cvParam[6] = tempVar65;
                mzML_type->run().spectrumList()->spectrum()[i - 1].cvParam().push_back(*tempVar65);

                if (myMsDataFile->GetOneBasedScan(i)->getMassSpectrum()->getSize() > 0)
                {
                    //base peak m/z
                    ms::mzml::CVParamType *tempVar66 = new ms::mzml::CVParamType("MS", "MS:1000504", "base peak m/z");
                    // tempVar66->setname("base peak m/z");
                    // tempVar66->setaccession("MS:1000504");
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
                    tempVar66->value(std::to_string(myMsDataFile->GetOneBasedScan(i)->getMassSpectrum()->getXofPeakWithHighestY().value()));
                    tempVar66->unitCvRef("MS");
                    tempVar66->unitName("m/z");
                    tempVar66->unitAccession("MS:1000040");
                    // tempVar66->setcvRef("MS");
                    //original
                    // mzML_type->run().spectrumList()->spectrum()[i - 1]->cvParam[7] = tempVar66;
                    mzML_type->run().spectrumList()->spectrum()[i - 1].cvParam().push_back(*tempVar66);

                    //base peak intensity
                    ms::mzml::CVParamType *tempVar67 = new ms::mzml::CVParamType("MS", "MS:1000505", "base peak intensity");
                    // tempVar67->setname("base peak intensity");
                    // tempVar67->setaccession("MS:1000505");
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
                    tempVar67->value(std::to_string(myMsDataFile->GetOneBasedScan(i)->getMassSpectrum()->getYofPeakWithHighestY().value()));
                    tempVar67->unitCvRef("MS");
                    tempVar67->unitName("number of detector counts");
                    tempVar67->unitAccession("MS:1000131");
                    // tempVar67->setcvRef("MS");
                    //original
                    // mzML_type->run().spectrumList()->spectrum()[i - 1]->cvParam[8] = tempVar67;
                    mzML_type->run().spectrumList()->spectrum()[i - 1].cvParam().push_back(*tempVar67);

                    delete tempVar67;
                    delete tempVar66;
                }

                // Retention time
                //original
                // mzML_type->run().spectrumList()->spectrum()[i - 1]->scanList = new ms::mzml::ScanListType(1);
                ms::mzml::ScanListType *spectrumScanList = new ms::mzml::ScanListType(1);
                mzML_type->run().spectrumList()->spectrum()[i - 1].scanList() = *spectrumScanList;
                // .scanList->count = "1";
                //push back 1 scan 
                // .scanList->scan = std::vector<ms::mzml::ScanType*>(1);
                //pushback 1 cvparam
                // .scanList->cvParam = std::vector<ms::mzml::CVParamType*>(1);

                ms::mzml::CVParamType *tempVar68 = new ms::mzml::CVParamType("MS", "MS:1000795", "no combination");
                // tempVar68->setaccession("MS:1000795");
                // tempVar68->setcvRef("MS");
                // tempVar68->setname("no combination");
                tempVar68->value("");
                //original
                // mzML_type->run().spectrumList()->spectrum()[i - 1]->scanList().cvParam()[0] = tempVar68;
                mzML_type->run().spectrumList()->spectrum()[i - 1].scanList()->cvParam().push_back(*tempVar68);

                // if (myMsDataFile->GetOneBasedScan(i)->getMzAnalyzer().Equals(analyzersInThisFile[0]))
                if (myMsDataFile->GetOneBasedScan(i)->getMzAnalyzer() == analyzersInThisFile[0])
                {
                    ms::mzml::ScanType *tempVar69 = new ms::mzml::ScanType();
                    //push back 3 cvparams
                    // tempVar69->setcvParam(std::vector<ms::mzml::CVParamType*>(3));
                    //original
                    // mzML_type->run().spectrumList()->spectrum()[i - 1]->scanList.scan[0] = tempVar69;
                    mzML_type->run().spectrumList()->spectrum()[i - 1].scanList()->scan().push_back(*tempVar69);

                    delete tempVar69;
                }
                else
                {
                    ms::mzml::ScanType *tempVar70 = new ms::mzml::ScanType();
                    //push back 3 cvparams
                    // tempVar70->setcvParam(std::vector<ms::mzml::CVParamType*>(3));
                    tempVar70->instrumentConfigurationRef(analyzersInThisFileDict[myMsDataFile->GetOneBasedScan(i)->getMzAnalyzer()]);
                    //original
                    // mzML_type->run().spectrumList()->spectrum()[i - 1]->scanList().scan()[0] = tempVar70;
                    mzML_type->run().spectrumList()->spectrum()[i - 1].scanList()->scan().push_back(*tempVar70);

                    delete tempVar70;
                }
                ms::mzml::CVParamType *tempVar71 = new ms::mzml::CVParamType("MS", "MS:1000016", "scan start time");
                // tempVar71->setname("scan start time");
                // tempVar71->setaccession("MS:1000016");
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
                tempVar71->value(std::to_string(myMsDataFile->GetOneBasedScan(i)->getRetentionTime()));
                tempVar71->unitCvRef("UO");
                tempVar71->unitAccession("UO:0000031");
                tempVar71->unitName("minute");
                // tempVar71->setcvRef("MS");
                //original
                // mzML_type->run().spectrumList()->spectrum()[i - 1]->scanList().scan()[0].cvParam()[0] = tempVar71;
                mzML_type->run().spectrumList()->spectrum()[i - 1].scanList()->scan()[0].cvParam().push_back(*tempVar71);

                ms::mzml::CVParamType *tempVar72 = new ms::mzml::CVParamType("MS", "MS:1000512", "filter string");
                // tempVar72->setname("filter string");
                // tempVar72->setaccession("MS:1000512");
                tempVar72->value(myMsDataFile->GetOneBasedScan(i)->getScanFilter());
                // tempVar72->setcvRef("MS");
                //original
                // mzML_type->run().spectrumList()->spectrum()[i - 1]->scanList().scan()[0].cvParam()[1] = tempVar72;
                mzML_type->run().spectrumList()->spectrum()[i - 1].scanList()->scan()[0].cvParam().push_back(*tempVar72);

                if (myMsDataFile->GetOneBasedScan(i)->getInjectionTime())
                {
                    ms::mzml::CVParamType *tempVar73 = new ms::mzml::CVParamType("MS", "MS:1000927", "ion injection time");
                    // tempVar73->setname("ion injection time");
                    // tempVar73->setaccession("MS:1000927");
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':

                    //ToString(CultureInfo::InvariantCulture)
                    tempVar73->value(std::to_string(myMsDataFile->GetOneBasedScan(i)->getInjectionTime().value()));
                    // tempVar73->setcvRef("MS");
                    tempVar73->unitName("millisecond");
                    tempVar73->unitAccession("UO:0000028");
                    tempVar73->unitCvRef("UO");
                    //original
                    // mzML_type->run().spectrumList()->spectrum()[i - 1].scanList()->scan()[0].cvParam()[2] = tempVar73;
                    mzML_type->run().spectrumList()->spectrum()[i - 1].scanList()->scan()[0].cvParam().push_back(*tempVar73);

                    delete tempVar73;
                }
                if (myMsDataFile->GetOneBasedScan(i)->getMsnOrder() != 1)
                {
                    auto scanWithPrecursor = myMsDataFile->GetOneBasedScan(i);
                    if (scanWithPrecursor->getSelectedIonMonoisotopicGuessMz())
                    {
                        //original -> push back userparamtype
                        // mzML_type->run().spectrumList()->spectrum()[i - 1]->scanList.scan[0]->userParam = std::vector<ms::mzml::UserParamType*>(1);
                        ms::mzml::UserParamType *tempVar74 = new ms::mzml::UserParamType("[mzLib]Monoisotopic M/Z:");
                        // tempVar74->name("[mzLib]Monoisotopic M/Z:");
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':

                        //ToString(CultureInfo::InvariantCulture)
                        tempVar74->value(std::to_string(scanWithPrecursor->getSelectedIonMonoisotopicGuessMz().value()));
                        //original
                        // mzML_type->run().spectrumList()->spectrum()[i - 1]->scanList().scan()[0].userParam()[0] = tempVar74;
                        mzML_type->run().spectrumList()->spectrum()[i - 1].scanList()->scan()[0].userParam().push_back(*tempVar74);

                        delete tempVar74;
                    }
                }

                //original
                // mzML_type->run().spectrumList()->spectrum()[i - 1]->scanList().scan()[0]->scanWindowList() = new ms::mzml::ScanWindowListType();
                ms::mzml::ScanWindowListType *spectrumScanWindow = new ms::mzml::ScanWindowListType(1);
                 mzML_type->run().spectrumList()->spectrum()[i - 1].scanList()->scan()[0].scanWindowList(*spectrumScanWindow);
                // .scanWindowList->count = 1;
                //push back 1 param group
                // .scanWindowList->scanWindow = std::vector<ms::mzml::ParamGroupType*>(1);
                ms::mzml::ParamGroupType *tempVar75 = new ms::mzml::ParamGroupType();
                //push back 2 cvparams
                // tempVar75->cvParam(std::vector<ms::mzml::CVParamType*>(2));
                //original
                // mzML_type->run().spectrumList()->spectrum()[i - 1]->scanList().scan()[0].scanWindowList().scanWindow()[0] = tempVar75;
                mzML_type->run().spectrumList()->spectrum()[i - 1].scanList()->scan()[0].scanWindowList()->scanWindow().push_back(*tempVar75);

                ms::mzml::CVParamType *tempVar76 = new ms::mzml::CVParamType("MS", "MS:1000501", "scan window lower limit");
                // tempVar76->setname("scan window lower limit");
                // tempVar76->setaccession("MS:1000501");
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':

                //ToString(CultureInfo::InvariantCulture)
                tempVar76->value(std::to_string(myMsDataFile->GetOneBasedScan(i)->getScanWindowRange()->getMinimum()));
                // tempVar76->setcvRef("MS");
                tempVar76->unitCvRef("MS");
                tempVar76->unitAccession("MS:1000040");
                tempVar76->unitName("m/z");
                //original
                // mzML_type->run().spectrumList()->spectrum()[i - 1].scanList()->scan()[0].scanWindowList()->scanWindow()[0].cvParam()[0] = tempVar76;
                mzML_type->run().spectrumList()->spectrum()[i - 1].scanList()->scan()[0].scanWindowList()->scanWindow()[0].cvParam().push_back(*tempVar76);

                ms::mzml::CVParamType *tempVar77 = new ms::mzml::CVParamType("MS", "MS:1000500", "scan window upper limit");
                // tempVar77->setname("scan window upper limit");
                // tempVar77->setaccession("MS:1000500");
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':

                //ToString(CultureInfo::InvariantCulture)
                tempVar77->value(std::to_string(myMsDataFile->GetOneBasedScan(i)->getScanWindowRange()->getMaximum()));
                // tempVar77->setcvRef("MS");
                tempVar77->unitCvRef("MS");
                tempVar77->unitAccession("MS:1000040");
                tempVar77->unitName("m/z");
                //original
                // mzML_type->run().spectrumList()->spectrum()[i - 1].scanList()->scan()[0].scanWindowList()->scanWindow()[0].cvParam()[1] = tempVar77;
                mzML_type->run().spectrumList()->spectrum()[i - 1].scanList()->scan()[0].scanWindowList()->scanWindow()[0].cvParam().push_back(*tempVar77);
                if (myMsDataFile->GetOneBasedScan(i)->getNoiseData().empty())
                {
                    //original
                    // mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList = new ms::mzml::BinaryDataArrayListType();
                    // .binaryDataArrayList->count = std::to_string(2);
                    // .binaryDataArrayList->binaryDataArray = std::vector<ms::mzml::BinaryDataArrayType*>(2);
                    ms::mzml::BinaryDataArrayListType *spectrumBinDataList = new ms::mzml::BinaryDataArrayListType(2);
                    mzML_type->run().spectrumList()->spectrum()[i - 1].binaryDataArrayList(*spectrumBinDataList);
                }

                if (!myMsDataFile->GetOneBasedScan(i)->getNoiseData().empty())
                {
                    //original
                    // mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList = new ms::mzml::BinaryDataArrayListType();
                    // .binaryDataArrayList->count = std::to_string(5);
                    // .binaryDataArrayList->binaryDataArray = std::vector<ms::mzml::BinaryDataArrayType*>(5);
                    ms::mzml::BinaryDataArrayListType *spectrumBinDataList = new ms::mzml::BinaryDataArrayListType(5);
                    mzML_type->run().spectrumList()->spectrum()[i - 1].binaryDataArrayList(*spectrumBinDataList);
                }

                // M/Z Data
                //original
                // ms::mzml::BinaryDataArrayType *tempVar78 = new ms::mzml::BinaryDataArrayType();
                // tempVar78->setbinary(myMsDataFile->GetOneBasedScan(i)->getMassSpectrum().Get64BitXarray());

                std::vector<unsigned char> XArray = myMsDataFile->GetOneBasedScan(i)->getMassSpectrum()->Get64BitXarray();
                xml_schema::base64_binary binary_64bitXArray(XArray.size());  

                //iterate through unsigned char bin_times_vector and copy each element to base^$_binary bindata buffer
                it_vector = XArray.begin();
                for (auto it_binary = binary_64bitXArray.begin(); it_binary != binary_64bitXArray.end(); ++it_binary) {
                    *it_binary = *it_vector;;
                    it_vector++;
                }
                //uses .ToString(CultureInfo::InvariantCulture)
                ms::mzml::BinaryDataArrayType *tempVar78 = new ms::mzml::BinaryDataArrayType(binary_64bitXArray, 4 * std::ceil((static_cast<double>(mzML_type->run().spectrumList()->spectrum()[i - 1].binaryDataArrayList()->binaryDataArray()[0].binary().encode().length()) / 3)));

                //original
                // mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList.binaryDataArray[0] = tempVar78;
                mzML_type->run().spectrumList()->spectrum()[i - 1].binaryDataArrayList()->binaryDataArray().push_back(*tempVar78);
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
                // mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList.binaryDataArray[0]->encodedLength = (4 * std::ceil((static_cast<double>(mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList.binaryDataArray[0].binary->Length) / 3))).ToString(CultureInfo::InvariantCulture);
                //push back 3 cvparams
                // mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList.binaryDataArray[0]->cvParam = std::vector<ms::mzml::CVParamType*>(3);

                ms::mzml::CVParamType *tempVar79 = new ms::mzml::CVParamType("MS", "MS:1000514", "m/z array");
                // tempVar79->setaccession("MS:1000514");
                // tempVar79->setname("m/z array");
                // tempVar79->setcvRef("MS");
                tempVar79->unitName("m/z");
                tempVar79->value("");
                tempVar79->unitCvRef("MS");
                tempVar79->unitAccession("MS:1000040");
                //original
                // mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList().binaryDataArray()[0].cvParam()[0] = tempVar79;
                mzML_type->run().spectrumList()->spectrum()[i - 1].binaryDataArrayList()->binaryDataArray()[0].cvParam().push_back(*tempVar79);

                ms::mzml::CVParamType *tempVar80 = new ms::mzml::CVParamType("MS", "MS:1000523", "64-bit float");
                // tempVar80->setaccession("MS:1000523");
                // tempVar80->setname("64-bit float");
                // tempVar80->setcvRef("MS");
                tempVar80->value("");
                //original
                // mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList().binaryDataArray()[0].cvParam()[1] = tempVar80;
                mzML_type->run().spectrumList()->spectrum()[i - 1].binaryDataArrayList()->binaryDataArray()[0].cvParam().push_back(*tempVar80);

                ms::mzml::CVParamType *tempVar81 = new ms::mzml::CVParamType("MS", "MS:1000576", "no compression");
                // tempVar81->setaccession("MS:1000576");
                // tempVar81->setname("no compression");
                // tempVar81->setcvRef("MS");
                tempVar81->value("");
                //original
                // mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList().binaryDataArray()[0].cvParam()[2] = tempVar81;
                mzML_type->run().spectrumList()->spectrum()[i - 1].binaryDataArrayList()->binaryDataArray()[0].cvParam().push_back(*tempVar81);

                // Intensity Data
                //original
//                 ms::mzml::BinaryDataArrayType *tempVar82 = new ms::mzml::BinaryDataArrayType();
//                 tempVar82->setbinary(myMsDataFile->GetOneBasedScan(i)->getMassSpectrum().Get64BitYarray());
//                 mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList().binaryDataArray()[1] = tempVar82;
// //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
//                 mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList().binaryDataArray()[1]->encodedLength() = (4 * std::ceil((static_cast<double>(mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList.binaryDataArray[1].binary->Length) / 3))).ToString(CultureInfo::InvariantCulture);

                std::vector<unsigned char> YArray = myMsDataFile->GetOneBasedScan(i)->getMassSpectrum()->Get64BitXarray();
                xml_schema::base64_binary binary_64bitYArray(YArray.size());  

                //iterate through unsigned char bin_times_vector and copy each element to base^$_binary bindata buffer
                it_vector = YArray.begin();
                for (auto it_binary = binary_64bitYArray.begin(); it_binary != binary_64bitYArray.end(); ++it_binary) {
                    *it_binary = *it_vector;
                    it_vector++;
                }

                ms::mzml::BinaryDataArrayType *tempVar82 = new ms::mzml::BinaryDataArrayType(binary_64bitYArray, 4 * std::ceil((static_cast<double>(mzML_type->run().spectrumList()->spectrum()[i - 1].binaryDataArrayList()->binaryDataArray()[1].binary().encode().length()) / 3)));

                mzML_type->run().spectrumList()->spectrum()[i - 1].binaryDataArrayList()->binaryDataArray().push_back(*tempVar82);

                //push back 3 cvparams
                // mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList().binaryDataArray()[1]->cvParam() = std::vector<ms::mzml::CVParamType*>(3);

                ms::mzml::CVParamType *tempVar83 = new ms::mzml::CVParamType("MS", "MS:1000515", "intensity array");
                // tempVar83->setaccession("MS:1000515");
                // tempVar83->setname("intensity array");
                // tempVar83->setcvRef("MS");
                tempVar83->unitCvRef("MS");
                tempVar83->unitAccession("MS:1000131");
                tempVar83->unitName("number of counts");
                tempVar83->value("");
                //original
                // mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList().binaryDataArray()[1].cvParam()[0] = tempVar83;
                mzML_type->run().spectrumList()->spectrum()[i - 1].binaryDataArrayList()->binaryDataArray()[1].cvParam().push_back(*tempVar83);

                ms::mzml::CVParamType *tempVar84 = new ms::mzml::CVParamType("MS", "MS:1000523", "64-bit float");
                // tempVar84->setaccession("MS:1000523");
                // tempVar84->setname("64-bit float");
                // tempVar84->setcvRef("MS");
                tempVar84->value("");
                //original
                // mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList().binaryDataArray()[1].cvParam()[1] = tempVar84;
                mzML_type->run().spectrumList()->spectrum()[i - 1].binaryDataArrayList()->binaryDataArray()[1].cvParam().push_back(*tempVar84);

                ms::mzml::CVParamType *tempVar85 = new ms::mzml::CVParamType("MS", "MS:1000576", "no compression");
                // tempVar85->setaccession("MS:1000576");
                // tempVar85->setname("no compression");
                // tempVar85->setcvRef("MS");
                tempVar85->value("");
                //original
                // mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList().binaryDataArray()[1].cvParam()[2] = tempVar85;
                mzML_type->run().spectrumList()->spectrum()[i - 1].binaryDataArrayList()->binaryDataArray()[1].cvParam().push_back(*tempVar85);

                if (!myMsDataFile->GetOneBasedScan(i)->getNoiseData().empty())
                {
                    // mass
                    // ms::mzml::BinaryDataArrayType *tempVar86 = new ms::mzml::BinaryDataArrayType();
                    // tempVar86->setbinary(myMsDataFile->GetOneBasedScan(i)->Get64BitNoiseDataMass());
                    // mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList().binaryDataArray()[2] = tempVar86;
                    // mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList().binaryDataArray()[2]->arrayLength() = std::to_string(mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList.binaryDataArray[2].binary->Length / 8);
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
                    // mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList().binaryDataArray()[2]->encodedLength() = (4 * std::ceil((static_cast<double>(mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList.binaryDataArray[2].binary->Length) / 3))).ToString(CultureInfo::InvariantCulture);
                    //push back 3 cvparams
                    // mzML_type->run().spectrumList()->spectrum()[i - 1].binaryDataArrayList()->binaryDataArray()[2].cvParam() = std::vector<ms::mzml::CVParamType*>(3);


                    std::vector<unsigned char> noiseDataMass = myMsDataFile->GetOneBasedScan(i)->Get64BitNoiseDataMass();
                    xml_schema::base64_binary binary_noiseDataMass(noiseDataMass.size());  

                    //iterate through unsigned char bin_times_vector and copy each element to base^$_binary bindata buffer
                    it_vector = noiseDataMass.begin();
                    for (auto it_binary = binary_noiseDataMass.begin(); it_binary != binary_noiseDataMass.end(); ++it_binary) {
                        *it_binary = *it_vector;;
                        it_vector++;
                    }

                    ms::mzml::BinaryDataArrayType *tempVar86 = new ms::mzml::BinaryDataArrayType(binary_noiseDataMass, 4 * std::ceil((static_cast<double>(mzML_type->run().spectrumList()->spectrum()[i - 1].binaryDataArrayList()->binaryDataArray()[2].binary().encode().length()) / 3)));

                    mzML_type->run().spectrumList()->spectrum()[i - 1].binaryDataArrayList()->binaryDataArray().push_back(*tempVar86);
                    mzML_type->run().spectrumList()->spectrum()[i - 1].binaryDataArrayList()->binaryDataArray()[2].arrayLength() = mzML_type->run().spectrumList()->spectrum()[i - 1].binaryDataArrayList()->binaryDataArray()[2].binary().encode().length() / 8;

                    ms::mzml::CVParamType *tempVar87 = new ms::mzml::CVParamType("MS", "MS:1000786", "non-standard data array");
                    // tempVar87->setaccession("MS:1000786");
                    // tempVar87->setname("non-standard data array");
                    // tempVar87->setcvRef("MS");
                    tempVar87->value("mass");
                    tempVar87->unitCvRef("MS");
                    //original
                    // mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList().binaryDataArray()[2].cvParam()[0] = tempVar87;
                    mzML_type->run().spectrumList()->spectrum()[i - 1].binaryDataArrayList()->binaryDataArray()[2].cvParam().push_back(*tempVar87);

                    ms::mzml::CVParamType *tempVar88 = new ms::mzml::CVParamType("MS", "MS:1000523", "64-bit float");
                    // tempVar88->setaccession("MS:1000523");
                    // tempVar88->setname("64-bit float");
                    // tempVar88->setcvRef("MS");
                    tempVar88->value("");
                    //original
                    // mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList().binaryDataArray()[2].cvParam()[1] = tempVar88;
                    mzML_type->run().spectrumList()->spectrum()[i - 1].binaryDataArrayList()->binaryDataArray()[2].cvParam().push_back(*tempVar88);

                    ms::mzml::CVParamType *tempVar89 = new ms::mzml::CVParamType("MS", "MS:1000576", "no compression");
                    // tempVar89->setaccession("MS:1000576");
                    // tempVar89->setname("no compression");
                    // tempVar89->setcvRef("MS");
                    tempVar89->value("");
                    //original
                    // mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList().binaryDataArray()[2].cvParam()[2] = tempVar89;
                    mzML_type->run().spectrumList()->spectrum()[i - 1].binaryDataArrayList()->binaryDataArray()[2].cvParam().push_back(*tempVar89);

                    //push back 1 user param
                    // mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList().binaryDataArray()[2]->userParam() = std::vector<ms::mzml::UserParamType*>(1);
                    
                    ms::mzml::UserParamType *tempVar90 = new ms::mzml::UserParamType("kelleherCustomType");
                    // tempVar90->setname("kelleherCustomType");
                    tempVar90->value("noise m/z");
                    //original
                    // mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList().binaryDataArray()[2].userParam()[0] = tempVar90;
                    mzML_type->run().spectrumList()->spectrum()[i - 1].binaryDataArrayList()->binaryDataArray()[2].userParam().push_back(*tempVar90);

                    // noise
                    // ms::mzml::BinaryDataArrayType *tempVar91 = new ms::mzml::BinaryDataArrayType();
                    // tempVar91->setbinary(myMsDataFile->GetOneBasedScan(i)->Get64BitNoiseDataNoise());
                    // mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList.binaryDataArray[3] = tempVar91;
                    // mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList.binaryDataArray[3]->arrayLength = std::to_string(mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList.binaryDataArray[3].binary->Length / 8);
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
                    // mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList.binaryDataArray[3]->encodedLength = (4 * std::ceil((static_cast<double>(mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList.binaryDataArray[3].binary->Length) / 3))).ToString(CultureInfo::InvariantCulture);
                    //push back 3 cvparams
                    // mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList.binaryDataArray[3]->cvParam = std::vector<ms::mzml::CVParamType*>(3);

                    std::vector<unsigned char> noiseDataNoise = myMsDataFile->GetOneBasedScan(i)->Get64BitNoiseDataNoise();
                    xml_schema::base64_binary binary_noiseDataNoise(noiseDataNoise.size());  

                    //iterate through unsigned char bin_times_vector and copy each element to base^$_binary bindata buffer
                    it_vector = noiseDataNoise.begin();
                    for (auto it_binary = binary_noiseDataNoise.begin(); it_binary != binary_noiseDataNoise.end(); ++it_binary) {
                        *it_binary = *it_vector;;
                        it_vector++;
                    }

                    ms::mzml::BinaryDataArrayType *tempVar91 = new ms::mzml::BinaryDataArrayType(binary_noiseDataNoise, 4 * std::ceil((static_cast<double>(mzML_type->run().spectrumList()->spectrum()[i - 1].binaryDataArrayList()->binaryDataArray()[3].binary().encode().length()) / 3)));
                    mzML_type->run().spectrumList()->spectrum()[i - 1].binaryDataArrayList()->binaryDataArray().push_back(*tempVar91);

                    mzML_type->run().spectrumList()->spectrum()[i - 1].binaryDataArrayList()->binaryDataArray()[3].arrayLength() = mzML_type->run().spectrumList()->spectrum()[i - 1].binaryDataArrayList()->binaryDataArray()[3].binary().encode().length() / 8;


                    ms::mzml::CVParamType *tempVar92 = new ms::mzml::CVParamType("MS", "MS:1000786", "non-standard data array");
                    // tempVar92->setaccession("MS:1000786");
                    // tempVar92->setname("non-standard data array");
                    // tempVar92->setcvRef("MS");
                    tempVar92->value("SignalToNoise");
                    //original
                    // mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList().binaryDataArray()[3].cvParam()[0] = tempVar92;
                    mzML_type->run().spectrumList()->spectrum()[i - 1].binaryDataArrayList()->binaryDataArray()[3].cvParam().push_back(*tempVar92);

                    ms::mzml::CVParamType *tempVar93 = new ms::mzml::CVParamType("MS", "MS:1000523", "64-bit float");
                    // tempVar93->setaccession("MS:1000523");
                    // tempVar93->setname("64-bit float");
                    // tempVar93->setcvRef("MS");
                    tempVar93->value("");
                    //original
                    // mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList().binaryDataArray()[3].cvParam()[1] = tempVar93;
                    mzML_type->run().spectrumList()->spectrum()[i - 1].binaryDataArrayList()->binaryDataArray()[3].cvParam().push_back(*tempVar93);

                    ms::mzml::CVParamType *tempVar94 = new ms::mzml::CVParamType("MS", "MS:1000576", "no compression");
                    // tempVar94->setaccession("MS:1000576");
                    // tempVar94->setname("no compression");
                    // tempVar94->setcvRef("MS");
                    tempVar94->value("");
                    //original
                    // mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList().binaryDataArray()[3].cvParam()[2] = tempVar94;
                    mzML_type->run().spectrumList()->spectrum()[i - 1].binaryDataArrayList()->binaryDataArray()[3].cvParam().push_back(*tempVar94);

                    //push back 1 user param
                    // mzML_type->run().spectrumList()->spectrum()[i - 1].binaryDataArrayList()->binaryDataArray()[3]->userParam() = std::vector<ms::mzml::UserParamType*>(1);
                    
                    ms::mzml::UserParamType *tempVar95 = new ms::mzml::UserParamType("kelleherCustomType");
                    // tempVar95->setname("kelleherCustomType");
                    tempVar95->value("noise baseline");
                    mzML_type->run().spectrumList()->spectrum()[i - 1].binaryDataArrayList()->binaryDataArray()[3].userParam().push_back(*tempVar95);

                    // baseline
                    // ms::mzml::BinaryDataArrayType *tempVar96 = new ms::mzml::BinaryDataArrayType();
                    // tempVar96->setbinary(myMsDataFile->GetOneBasedScan(i)->Get64BitNoiseDataBaseline());
                    // mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList().binaryDataArray().push_back(*tempVar96);
                    // mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList().binaryDataArray()[4]->arrayLength() = std::to_string(mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList.binaryDataArray[4].binary->Length / 8);
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
                    // mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList().binaryDataArray()[4]->encodedLength() = (4 * std::ceil((static_cast<double>(mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList.binaryDataArray[4].binary->Length) / 3))).ToString(CultureInfo::InvariantCulture);
                    //push back 4 cvparams
                    // mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList().binaryDataArray()[4]->cvParam() = std::vector<ms::mzml::CVParamType*>(3);

                    std::vector<unsigned char> noiseDataBaseline = myMsDataFile->GetOneBasedScan(i)->Get64BitNoiseDataBaseline();
                    xml_schema::base64_binary binary_noiseDataBaseline(noiseDataBaseline.size());  

                    //iterate through unsigned char bin_times_vector and copy each element to base^$_binary bindata buffer
                    it_vector = noiseDataBaseline.begin();
                    for (auto it_binary = binary_noiseDataBaseline.begin(); it_binary != binary_noiseDataBaseline.end(); ++it_binary) {
                        *it_binary = *it_vector;;
                        it_vector++;
                    }

                    ms::mzml::BinaryDataArrayType *tempVar96 = new ms::mzml::BinaryDataArrayType(binary_noiseDataBaseline, 4 * std::ceil((static_cast<double>(mzML_type->run().spectrumList()->spectrum()[i - 1].binaryDataArrayList()->binaryDataArray()[4].binary().encode().length()) / 3)));
                    mzML_type->run().spectrumList()->spectrum()[i - 1].binaryDataArrayList()->binaryDataArray().push_back(*tempVar96);
                    mzML_type->run().spectrumList()->spectrum()[i - 1].binaryDataArrayList()->binaryDataArray()[4].arrayLength() = mzML_type->run().spectrumList()->spectrum()[i - 1].binaryDataArrayList()->binaryDataArray()[4].binary().encode().length() / 8;

                    ms::mzml::CVParamType *tempVar97 = new ms::mzml::CVParamType("MS", "MS:1000786", "non-standard data array");
                    // tempVar97->setaccession("MS:1000786");
                    // tempVar97->setname("non-standard data array");
                    // tempVar97->setcvRef("MS");
                    tempVar97->value("baseline");
                    //original
                    // mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList().binaryDataArray()[4].cvParam()[0] = tempVar97;
                    mzML_type->run().spectrumList()->spectrum()[i - 1].binaryDataArrayList()->binaryDataArray()[4].cvParam().push_back(*tempVar97);

                    ms::mzml::CVParamType *tempVar98 = new ms::mzml::CVParamType("MS", "MS:1000523", "64-bit float");
                    // tempVar98->setaccession("MS:1000523");
                    // tempVar98->setname("64-bit float");
                    // tempVar98->setcvRef("MS");
                    tempVar98->value("");
                    //original
                    // mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList().binaryDataArray()[4].cvParam()[1] = tempVar98;
                    mzML_type->run().spectrumList()->spectrum()[i - 1].binaryDataArrayList()->binaryDataArray()[4].cvParam().push_back(*tempVar98);

                    ms::mzml::CVParamType *tempVar99 = new ms::mzml::CVParamType("MS", "MS:1000576", "no compression");
                    // tempVar99->setaccession("MS:1000576");
                    // tempVar99->setname("no compression");
                    // tempVar99->setcvRef("MS");
                    tempVar99->value("");
                    //original
                    // mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList().binaryDataArray()[4].cvParam()[2] = tempVar99;
                    mzML_type->run().spectrumList()->spectrum()[i - 1].binaryDataArrayList()->binaryDataArray()[4].cvParam().push_back(*tempVar99);
                    //push back 1 user param
                    // mzML_type->run().spectrumList()->spectrum()[i - 1]->binaryDataArrayList().binaryDataArray()[4]->userParam() = std::vector<ms::mzml::UserParamType*>(1);

                    ms::mzml::UserParamType *tempVar100 = new ms::mzml::UserParamType("kelleherCustomType");
                    // tempVar100->setname("kelleherCustomType");
                    tempVar100->value("noise intensity");
                    //original
                    mzML_type->run().spectrumList()->spectrum()[i - 1].binaryDataArrayList()->binaryDataArray()[4].userParam().push_back(*tempVar100);

                    delete tempVar100;
                    delete tempVar99;
                    delete tempVar98;
                    delete tempVar97;
                    delete tempVar96;
                    delete tempVar95;
                    delete tempVar94;
                    delete tempVar93;
                    delete tempVar92;
                    delete tempVar91;
                    delete tempVar90;
                    delete tempVar89;
                    delete tempVar88;
                    delete tempVar87;
                    delete tempVar86;
                }

                delete tempVar85;
                delete tempVar84;
                delete tempVar83;
                delete tempVar82;
                delete tempVar81;
                delete tempVar80;
                delete tempVar79;
                delete tempVar78;
                delete tempVar77;
                delete tempVar76;
                delete tempVar75;
                delete tempVar72;
                delete tempVar71;
                delete tempVar68;
                delete tempVar65;
                delete tempVar61;
                delete tempVar60;
                delete tempVar47;
            }

            if (!writeIndexed)
            {
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (TextWriter writer = new StreamWriter(outputFile))
#ifdef ORIG
                TextWriter writer = StreamWriter(outputFile);
                mzmlSerializer->Serialize(writer, mzML);
#endif
                xml_schema::namespace_infomap map;
                // map["xsn"].name = "http://www.w3.org/2001/XMLSchema-instance";
                map[""].name = "";
                map[""].schema = "mzML1.1.0.xsd";

                // Serialize to a file.
                try{
                    std::ofstream ofs (outputFile);
                    mzML (ofs, *mzML_type, map);
                    ofs.close();
                }

                catch (const xml_schema::exception& e)
                {
                    std::cerr << e << std::endl;
                }         

            }
            else if (writeIndexed)
            {

                //indexedmzml constructor arguments:  mzML_type&, const indexList_type&, const indexListOffset_type&, const fileChecksum_type&
                // ms::mzml::indexedmzML *indexedMzml = new ms::mzml::indexedmzML();

                // auto inMemoryTextWriter = new MemoryStream();
                auto inMemoryTextWriter = std::ostringstream();

                //compute total offset
                // indexedMzml->mzML(mzML_type);

                // indexedSerializer->Serialize(inMemoryTextWriter, indexedMzml);

                xml_schema::namespace_infomap map;
                // map["xsn"].name = "http://www.w3.org/2001/XMLSchema-instance";
                map[""].name = "";
                map[""].schema = "mzML1.1.0.xsd";

                // Serialize to a file.
                try{
                    mzML (inMemoryTextWriter, *mzML_type, map);
                    // ofs.close();
                }

                catch (const xml_schema::exception& e)
                {
                    std::cerr << e << std::endl;
                }   

                // std::string allmzMLData = StringHelper::replace(Encoding::UTF8->GetString(inMemoryTextWriter->ToArray()), "\r\n", "\n");
                std::string allmzMLData = StringHelper::replace(inMemoryTextWriter.str(), "\r\n", "\n");

                std::optional<long long> indexListOffset = std::make_optional(allmzMLData.length());

                //new stream with correct formatting

                // ms::mzml::IndexListType tempVar101();
                // indexedMzml->indexList(&tempVar101);
                // indexedMzml->indexList()->count("2");
                //push back two indexes
                // indexedMzml->indexList()->index(std::vector<ms::mzml::IndexType*>(2));
                ms::mzml::IndexListType *tempVar101 = new ms::mzml::IndexListType(2);

                //starts as spectrum be defualt
                // auto indexname = new ms::mzml::IndexTypeName();
                auto indexname = ms::mzml::name(ms::mzml::name::value::spectrum);

                //spectra naming
                // ms::mzml::IndexType *tempVar102 = new ms::mzml::IndexType();
                // tempVar102->name(indexname);
                // indexedMzml->indexList()->index()[0] = tempVar102;
                ms::mzml::IndexType *tempVar102 = new ms::mzml::IndexType(indexname);
                tempVar101->index()[0] = *tempVar102;

                //switch to chromatogram name
                indexname = ms::mzml::name::value::chromatogram;

                //chroma naming
                // ms::mzml::IndexType *tempVar103 = new ms::mzml::IndexType();
                // tempVar103->name(indexname);
                // indexedMzml->indexList()->index()[1] = tempVar103;

                ms::mzml::IndexType *tempVar103 = new ms::mzml::IndexType(indexname);
                tempVar101->index()[1] = *tempVar103;

                int numScans = myMsDataFile->getNumSpectra();
                //original
                // int numChromas = std::stoi(mzML_type->run().chromatogramList()->count());
                int numChromas = mzML_type->run().chromatogramList()->count();

                //now calculate offsets of each scan and chroma

                //add spectra offsets
                // indexedMzml->indexList()->index()[0]->offset() = std::vector<ms::mzml::OffsetType*>(numScans);
                //add chroma offsets
                // indexedMzml->indexList()->index()[1]->offset() = std::vector<ms::mzml::OffsetType*>(numChromas);

                //compute checksum
                std::string chksum = "Dummy";

                //indexedmzml constructor arguments:  mzML_type&, const indexList_type&, const indexListOffset_type&, const fileChecksum_type&
                ms::mzml::indexedmzML *indexedMzml = new ms::mzml::indexedmzML(*mzML_type, *tempVar101, indexListOffset.value(), chksum);

                int i = 0;
                int a = 1;
                int index;
                //indexOf search returns location fom beginning of line (3 characters short)
                int offsetFromBeforeScanTag = 3;
                //spectra offset loop
                while (i < numScans)
                {
                    index = (int)allmzMLData.find(mzML_type->run().spectrumList()->spectrum()[i].id(), (a - 1));
                    if (index != -1)
                    {
                        a = index;
                        // ms::mzml::OffsetType *tempVar104 = new ms::mzml::OffsetType();
                        // tempVar104->idRef(mzML_type->run().spectrumList()->spectrum()[i]->id);
                        // tempVar104->setValue(a + offsetFromBeforeScanTag);
                        // indexedMzml->indexList()->index()[0]->offset()[i] = tempVar104;

                        ms::mzml::OffsetType *tempVar104 = new ms::mzml::OffsetType(a + offsetFromBeforeScanTag, mzML_type->run().spectrumList()->spectrum()[i].id());
                        indexedMzml->indexList().index()[0].offset().push_back(*tempVar104);
                        i++;

                        delete tempVar104;
                    }
                }
                int offsetFromBeforeChromaTag = 3;
                index = (int)allmzMLData.find("id=\"" + mzML_type->run().chromatogramList()->chromatogram()[0].id() + "\"", (a - 1));
                if (index != -1)
                {
                    a = index;
                    // ms::mzml::OffsetType *tempVar105 = new ms::mzml::OffsetType();
                    // tempVar105->idRef(mzML_type->run()->getchromatogramList()->getchromatogram()[0]->id);
                    // tempVar105->setValue(a + offsetFromBeforeChromaTag);
                    // indexedMzml->indexList()->index()[1]->offset()[0] = tempVar105;
                    ms::mzml::OffsetType *tempVar105 = new ms::mzml::OffsetType(a + offsetFromBeforeChromaTag, mzML_type->run().chromatogramList()->chromatogram()[0].id());
                    //or is push_back appropriate here?
                    indexedMzml->indexList().index()[1].offset()[0] = *tempVar105;

                    delete tempVar105;
                }
                //offset
                int offsetFromNullIndexList = 32;

                //indexlistoffset?
                indexedMzml->indexListOffset(indexListOffset.value() - offsetFromNullIndexList);

                // //compute checksum
                // std::string chksum = "Dummy";

                // //indexedmzml constructor arguments:  mzML_type&, const indexList_type&, const indexListOffset_type&, const fileChecksum_type&
                // ms::mzml::indexedmzML *indexedMzml = new ms::mzml::indexedmzML(mzML_type, tempVar101, indexListOffset - offsetFromNullIndexList, chksum);

                indexedMzml->fileChecksum(chksum);
                // indexedSerializer->Serialize(inMemoryTextWriter, indexedMzml);

                //necessary to clear ostringstream?
                inMemoryTextWriter.str("");
                inMemoryTextWriter.clear();

                xml_schema::namespace_infomap indexed_map;
                // map["xsn"].name = "http://www.w3.org/2001/XMLSchema-instance";
                indexed_map[""].name = "";
                indexed_map[""].schema = "mzML1.1.1_idx.xsd";

                // Serialize to a file.
                try{
                    indexedmzML_ (inMemoryTextWriter, *indexedMzml, indexed_map);
                    // ofs.close();
                }

                catch (const xml_schema::exception& e)
                {
                    std::cerr << e << std::endl;
                }   

                //original, ToArray() returns byte array?
                // std::string indexedMzmlwithBlankChecksumStream = Encoding::UTF8->GetString(inMemoryTextWriter->ToArray());
                std::string indexedMzmlwithBlankChecksumStream = inMemoryTextWriter.str();

                std::string indexedMzmlwithBlankChecksumString = indexedMzmlwithBlankChecksumStream.substr(0, (int)indexedMzmlwithBlankChecksumStream.find("<fileChecksum>", (a - 1)));

                // inMemoryTextWriter->Close();
                //clear() rather than close because this is a stringstream is OK?
                inMemoryTextWriter.str("");
                inMemoryTextWriter.clear();

                //original
                // inMemoryTextWriter = new MemoryStream(Encoding::UTF8->GetBytes(indexedMzmlwithBlankChecksumString));
                inMemoryTextWriter << indexedMzmlwithBlankChecksumString;
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
                //original hash computation for checksum
                // chksum = BitConverter::ToString(System::Security::Cryptography::SHA1::Create()->ComputeHash(inMemoryTextWriter));
                //new checksum method returns int, just convert to string with to_string?
                chksum = std::to_string(StringHelper::GetHashCode(inMemoryTextWriter.str()));
                // inMemoryTextWriter->Close();

                chksum = StringHelper::replace(chksum, "-", "");
                chksum = StringHelper::toLower(chksum);
                indexedMzml->fileChecksum(chksum);

                //finally write the indexedmzml
                // TextWriter writer = StreamWriter(outputFile);
                // writer.NewLine = "\n";
                // indexedSerializer->Serialize(writer, indexedMzml);
                // writer.Close();

                // xml_schema::namespace_infomap map;
                // // map["xsn"].name = "http://www.w3.org/2001/XMLSchema-instance";
                // map[""].name = "";
                // map[""].schema = "mzML1.1.1_idx.xsd";

                // Serialize to a file.
                try{
                    std::ofstream ofs (outputFile);
                    indexedmzML_ (ofs, *indexedMzml, indexed_map);
                    ofs.close();
                }

                catch (const xml_schema::exception& e)
                {
                    std::cerr << e << std::endl;
                }      


                delete tempVar103;
                delete tempVar102;
//C# TO C++ CONVERTER TODO TASK: A 'delete inMemoryTextWriter' statement was not added since inMemoryTextWriter was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete indexedMzml' statement was not added since indexedMzml was passed to a method or constructor. Handle memory management manually.
            }

            delete tempVar45;
            delete tempVar44;
            delete tempVar43;
            delete tempVar42;
            delete tempVar41;
            delete tempVar40;
            delete tempVar39;
            delete tempVar38;
            delete tempVar37;
            delete tempVar35;
            delete tempVar32;
            delete tempVar31;
            delete tempVar30;
            delete tempVar18;
            delete tempVar17;
            delete tempVar15;
            delete tempVar14;
            delete tempVar4;
            delete tempVar3;
//C# TO C++ CONVERTER TODO TASK: A 'delete mzML' statement was not added since mzML was passed to a method or constructor. Handle memory management manually.
        }
    }
}
