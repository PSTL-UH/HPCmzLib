#include "Mgf.h"
#include "../MassSpectrometry/MsDataScan.h"
#include "../MassSpectrometry/SourceFile.h"
#include "../MassSpectrometry/FilteringParams.h"
#include "../MzLibUtil/MzLibException.h"
#include "../MassSpectrometry/MzSpectra/MzSpectrum.h"
#include "../MassSpectrometry/Enums/DissociationType.h"
#include "../MassSpectrometry/Enums/MzAnalyzerType.h"
#include "../MassSpectrometry/Enums/Polarity.h"
#include "../MzLibUtil/MzRange.h"

using namespace MassSpectrometry;
using namespace MzLibUtil;
namespace IO
{
    namespace Mgf
    {

        Mgf::Mgf(std::vector<MsDataScan*> &scans, MassSpectrometry::SourceFile *sourceFile) : MsDataFile(scans, sourceFile)
        {
            indexedScans = std::vector<MsDataScan*>(scans[scans.size() - 1]->getOneBasedScanNumber());
            for (auto scan : scans)
            {
                indexedScans[scan->getOneBasedScanNumber() - 1] = scan;
            }
        }

        Mgf *Mgf::LoadAllStaticData(const std::string &filePath, FilteringParams *filterParams)
        {
            if (!FileSystem::fileExists(filePath))
            {
                throw FileNotFoundException();
            }

            std::vector<MsDataScan*> scans;
            std::unordered_set<int> checkForDuplicateScans;

//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (FileStream fs = new FileStream(filePath, FileMode.Open, FileAccess.Read, FileShare.Read))
            {
                FileStream fs = FileStream(filePath, FileMode::Open, FileAccess::Read, FileShare::Read);
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (BufferedStream bs = new BufferedStream(fs))
                {
                    BufferedStream bs = BufferedStream(fs);
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (StreamReader sr = new StreamReader(bs))
                    {
                        StreamReader sr = StreamReader(bs);
                        std::string s;
                        while ((s = sr.ReadLine()) != "" && s != "BEGIN IONS")
                        {
                            //do nothing with the first few scans
                        }
                        bool readingPeaks = false;
                        std::vector<double> mzs;
                        std::vector<double> intensities;
                        double precursorMz = 0;
                        int charge = 2;
                        int scanNumber = 0;
                        int oldScanNumber = 0;
                        double rtInMinutes = 0;

                        while ((s = sr.ReadLine()) != "")
                        {
                            if (s == "END IONS")
                            {
                                if (!checkForDuplicateScans.insert(scanNumber)) //returns false if the scan already exists
                                {
                                    throw MzLibException("Scan number " + std::to_string(scanNumber) + " appeared multiple times in " + filePath + ", which is not allowed because we assume all scan numbers are unique.");
                                }

                                readingPeaks = false;
                                MzSpectrum *spectrum = new MzSpectrum(mzs.ToArray(), intensities.ToArray(), false);
                                MsDataScan tempVar(spectrum, scanNumber, 2, true, charge > 0 ? Polarity::Positive: Polarity::Negative, rtInMinutes, new MzRange(mzs[0], mzs[mzs.size() - 1]), "", MZAnalyzerType::Unknown, intensities.Sum(), std::make_optional(0), std::vector<std::vector<double>>(), "", std::make_optional(precursorMz), std::make_optional(charge), std::nullopt, std::make_optional(precursorMz), std::nullopt, std::make_optional(DissociationType::Unknown), std::nullopt, std::make_optional(precursorMz));
                                scans.push_back(&tempVar);
                                mzs = std::vector<double>();
                                intensities = std::vector<double>();
                                oldScanNumber = scanNumber;
                                charge = 2; //default when unknown

                                //skip the next two lines which are "" and "BEGIN IONS"
                                while ((s = sr.ReadLine()) != "" && s != "BEGIN IONS")
                                {
                                    //do nothing
                                }

//C# TO C++ CONVERTER TODO TASK: A 'delete spectrum' statement was not added since spectrum was passed to a method or constructor. Handle memory management manually.
                            }
                            else
                            {
                                if (readingPeaks)
                                {
                                    std::vector<std::string> sArray = StringHelper::split(s, ' ');
                                    mzs.push_back(std::stod(sArray[0]));
                                    intensities.push_back(std::stod(sArray[1]));
                                }
                                else
                                {
                                    std::vector<std::string> sArray = StringHelper::split(s, '=');
                                    if (sArray.size() == 1)
                                    {
                                        readingPeaks = true;
                                        sArray = StringHelper::split(s, ' ');
                                        mzs.push_back(std::stod(sArray[0]));
                                        intensities.push_back(std::stod(sArray[1]));

                                        if (oldScanNumber == scanNumber) //if there's no recorded scan number, simply index them.
                                        {
                                            scanNumber++;
                                        }
                                    }
                                    else
                                    {
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//                                        switch (sArray[0])
//ORIGINAL LINE: case "PEPMASS":
                                        if (sArray[0] == "PEPMASS")
                                        {
                                                sArray = StringHelper::split(sArray[1], ' ');
                                                precursorMz = std::stod(sArray[0]);

                                        }
//ORIGINAL LINE: case "CHARGE":
                                        else if (sArray[0] == "CHARGE")
                                        {
                                                std::string entry = sArray[1];
                                                charge = std::stoi(entry.substr(0, entry.length() - 1));
                                                if (entry[entry.length() - 1].Equals("-"))
                                                {
                                                    charge *= -1;
                                                }

                                        }
//ORIGINAL LINE: case "SCANS":
                                        else if (sArray[0] == "SCANS")
                                        {
                                                scanNumber = std::stoi(sArray[1]);

                                        }
//ORIGINAL LINE: case "RTINSECONDS":
                                        else if (sArray[0] == "RTINSECONDS")
                                        {
                                                rtInMinutes = std::stod(sArray[sArray.size() - 1]) / 60.0;

                                        }
                                        else
                                        {
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            MassSpectrometry::SourceFile *sourceFile = new SourceFile("no nativeID format", "mgf format", "", "", "");

            delete sourceFile;
            return new Mgf(scans.OrderBy([&] (std::any x)
            {
                x::OneBasedScanNumber;
            })->ToArray(), sourceFile);

//C# TO C++ CONVERTER TODO TASK: A 'delete sourceFile' statement was not added since sourceFile was passed to a method or constructor. Handle memory management manually.
        }

        MsDataScan *Mgf::GetOneBasedScan(int scanNumber)
        {
            return indexedScans[scanNumber - 1];
        }
    }
}
