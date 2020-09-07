#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include "stringhelper.h"

namespace FlashLFQ
{
    class IndexedMassSpectralPeak
    {
    public:
        const int ZeroBasedMs1ScanIndex;
        const double Mz;
        const double RetentionTime;
        const double Intensity;

        IndexedMassSpectralPeak(double mz, double intensity, int zeroBasedMs1ScanIndex, double retentionTime);

        bool Equals(IndexedMassSpectralPeak* obj);

        int GetHashCode();

        std::string ToString();

        static void Serialize(std::string &filename, std::vector<std::vector<IndexedMassSpectralPeak *>> iVec )
        {
            std::ofstream output (filename);
            if ( output.is_open() ) {
                output << iVec.size() << std::endl;
                for ( int i =0; i< iVec.size(); i++ ) {
                    if ( iVec[i].size() > 0 ) {
                        output << i << "\t" << iVec[i].size() << std::endl;                
                        for ( auto ind : iVec[i] ) {
                            output << ind->Mz << "\t" <<
                                ind->Intensity << "\t" <<
                                ind->ZeroBasedMs1ScanIndex <<  "\t" <<
                                ind->RetentionTime << "\t" <<std::endl;                
                        }
                    }
                }
                output.close();
            }
            else {
                std::cout <<"IndexedMassSpectralPeak::Serialize : Could not create file " << filename << std::endl;
            }
        }

        static void Deserialize (std::string &filename, std::vector<std::vector<IndexedMassSpectralPeak*>> &iVec )
        {
            std::ifstream input (filename);
            if ( input.is_open() ) {
                std::string line;
                getline ( input, line );
                int vecSize = std::stoi ( line );
                iVec.resize(vecSize);
                
                while (getline ( input, line) ) {
                    std::vector<std::string> splitsX = StringHelper::split(line, '\t');
                    int index = std::stoi(splitsX[0]);
                    int indvecSize = std::stoi ( splitsX[1] );

                    for (int j = 0; j < indvecSize; j++ ) {
                        getline ( input, line);
                        std::vector<std::string> splits = StringHelper::split(line, '\t');
                        
                        double mz = std::stod(splits[0]);
                        double intensity = std::stod(splits[1]);
                        int zeroBasedMs1ScanIndex = std::stoi(splits[2]);
                        double retentionTime = std::stod(splits[3]);
                        
                        auto newpeak = new IndexedMassSpectralPeak(mz, intensity, zeroBasedMs1ScanIndex,
                                                                   retentionTime);
                        iVec[index].push_back(newpeak);
                    }
                }
                input.close();
            }
            else {
                std::cout << "IndexedMassSpectralPeak::Deserialize : Could not open file " << filename << std::endl;
            }
        }
    };
}
