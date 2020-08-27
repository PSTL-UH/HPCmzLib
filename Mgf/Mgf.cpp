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

#include <iostream>
#include <fstream>
#include <stdlib.h>

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
                //throw FileNotFoundException();
                throw std::runtime_error("Mgf::LoadAllStaticData:: Could not open file" + filePath);
            }

            std::vector<MsDataScan*> scans;
            std::unordered_set<int> checkForDuplicateScans;

#ifdef ORIG
            FileStream fs = FileStream(filePath, FileMode::Open, FileAccess::Read, FileShare::Read);                
            BufferedStream bs = BufferedStream(fs);
            StreamReader sr = StreamReader(bs);
#endif
            std::ifstream sr ( filePath );
            if ( !sr.is_open() ) {
                std::cout << "Could not open file " << filePath << std::endl;
                exit(-1);
            }
            std::string s;

            //while ((s = sr.ReadLine()) != "" && s != "BEGIN IONS")
            //while (getline(sr, s) && s != "" && s != "BEGIN IONS") 
            //{
                //do nothing with the first few scans
            //}
            bool readingPeaks = false;
            std::vector<double> mzs;
            std::vector<double> intensities;
            double precursorMz = 0;
            int charge = 2;
            int scanNumber = 0;
            int oldScanNumber = 0;
            double rtInMinutes = 0;
            
            //while ((s = sr.ReadLine()) != "")
            while (getline(sr, s))
            {
                if ( s == "" ||  s[0] == '#' || s == "\r") {
                    continue;
                }                
                if (s[s.size() - 1] == '\r') {
                    s.erase(s.size() - 1);
                }
                if ( s == "BEGIN IONS") {
                    continue;
                }
                if (s == "END IONS")
                {
                    if (!std::get<1>(checkForDuplicateScans.insert(scanNumber))) //returns false if the scan already exists
                    {
                        throw MzLibException("Scan number " + std::to_string(scanNumber) + " appeared multiple times in " + filePath
                                             + ", which is not allowed because we assume all scan numbers are unique.");
                    }
                    
                    readingPeaks = false;
                    double intensities_sum = 0.0;
                    for ( auto p: intensities  ) {
                        intensities_sum += p;
                    }
                    
                    MzSpectrum *spectrum = new MzSpectrum(mzs, intensities, false);
                    auto tempVar = new MsDataScan (spectrum, scanNumber, 2, true, charge > 0 ? Polarity::Positive:
                                                   Polarity::Negative, rtInMinutes, new MzRange(mzs[0], mzs[mzs.size() - 1]), "",
                                                   MZAnalyzerType::Unknown, intensities_sum, std::make_optional(0),
                                                   std::vector<std::vector<double>>(), "", std::make_optional(precursorMz),
                                                   std::make_optional(charge), std::nullopt, std::make_optional(precursorMz),
                                                   std::nullopt, std::make_optional(DissociationType::Unknown), std::nullopt,
                                                   std::make_optional(precursorMz));
                    scans.push_back(tempVar);
                    mzs.clear();
                    intensities.clear();
                    oldScanNumber = scanNumber;
                    charge = 2; //default when unknown
                    
                    //skip the next two lines which are "" and "BEGIN IONS"
                    //while ((s = sr.ReadLine()) != "" && s != "BEGIN IONS")
                    //while (getline(sr, s) && s != "" && s != "BEGIN IONS") 
                    //{
                        //do nothing
                    //}
                    
                    //C# TO C++ CONVERTER TODO TASK: A 'delete spectrum' statement was not added since spectrum was
                    //passed to a method or constructor. Handle memory management manually.
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
                            if (sArray[0] == "PEPMASS")
                            {
                                sArray = StringHelper::split(sArray[1], ' ');
                                precursorMz = std::stod(sArray[0]);
                                
                            }
                            else if (sArray[0] == "CHARGE")
                            {
                                std::string entry = sArray[1];
                                char ctemp = '-';
                                charge = std::stoi(entry.substr(0, entry.length() - 1));
                                if (entry[entry.length() - 1] == ctemp )
                                {
                                    charge *= -1;
                                }
                                
                            }
                            else if (sArray[0] == "SCANS")
                            {
                                scanNumber = std::stoi(sArray[1]);
                                
                            }
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
                        
            MassSpectrometry::SourceFile *sourceFile = new SourceFile("no nativeID format", "mgf format", "", "", "");

#ifdef ORIG
            return = new Mgf(scans.OrderBy([&] (std::any x)  {
                        x::OneBasedScanNumber;
            })->ToArray(), sourceFile);
#endif
            std::sort (scans.begin(), scans.end(), [&] (auto *l, auto *r) {
                    return l->getOneBasedScanNumber() < r->getOneBasedScanNumber();
                });
            auto thismgf = new Mgf(scans, sourceFile );
            return  thismgf;
            //C# TO C++ CONVERTER TODO TASK: A 'delete sourceFile' statement was not added since sourceFile
            //was passed to a method or constructor. Handle memory management manually.
        }

        MsDataScan *Mgf::GetOneBasedScan(int scanNumber)
        {
            return indexedScans[scanNumber - 1];
        }
    }
}
