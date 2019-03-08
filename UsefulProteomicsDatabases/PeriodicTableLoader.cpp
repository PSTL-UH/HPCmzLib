#include "PeriodicTableLoader.h"
#include "../Chemistry/Element.h"
#include "../Chemistry/PeriodicTable.h"

#include <iostream>
#include <fstream>

namespace UsefulProteomicsDatabases {

    void PeriodicTableLoader::Load(const std::string &elementLocation) {
        std::ifstream sr(elementLocation);
        std::string line;
        while ( getline(sr, line) ){
            if ( line.find("Atomic Number", 0) != std::string::npos ) {
                break;
            }
        }
        
        int prevAtomicNumber = -1;
        Element *element = new Element("fake", prevAtomicNumber, -1);
        do {
            //int atomicNumber = Convert::ToInt32(Regex::Match(line, R"(\d+)")->Value);
            int atomicNumber=-1;
            std::regex IntegerRegex(R"(\d+)");
            std::smatch amatch;
            if ( std::regex_search(line, amatch, IntegerRegex) ) {
                try {
                    atomicNumber = std::stoi(amatch.str());
                }
                catch (std::invalid_argument &e ) {
                    std::cout << "Could not extract atomic number " << std::endl;
                }
            }
            
            getline(sr, line);
            //std::string atomicSymbol = Regex::Match(line, R"([A-Za-z]+$)")->Value;
            std::string atomicSymbol;
            std::regex atomicSymbolRegex(R"(([A-Z][a-z]?\s*)$)"); 
            std::smatch atmatch;
            if ( std::regex_search(line, atmatch, atomicSymbolRegex) ) {
                atomicSymbol = atmatch.str();
            }
            
            getline(sr, line);
            // int massNumber = Convert::ToInt32(Regex::Match(line, R"(\d+)")->Value); 
            int massNumber=-1;
            std::smatch mmatch;
            if ( std::regex_search(line, mmatch, IntegerRegex) ) {
                try {
                    massNumber = std::stoi(mmatch.str());
                }
                catch (std::invalid_argument &e ) {
                    std::cout << "Could not extract mass number " << std::endl;
                }
            }
            
            getline(sr, line);
            //double atomicMass = Convert::ToDouble(Regex::Match(line, R"([\d\.]+)")->Value);
            double atomicMass=-1;
            std::regex DoubleRegex(R"([\d\.]+)");
            std::smatch ammatch;
            if ( std::regex_search(line, ammatch, DoubleRegex) ) {
                try {
                    atomicMass = std::stod(ammatch.str());
                }
                catch (std::invalid_argument &e ) {
                    std::cout << "Could not extract atomic Mass " << std::endl;
                }
            }
            
            getline(sr, line);
            double abundance=-1;
            std::smatch abmatch;
            if (std::regex_search(line, abmatch, DoubleRegex )) {
                try {
                    abundance = std::stod(abmatch.str());
                }
                catch (std::invalid_argument &e ) {
                    std::cout << "Could not extract Abundance " << std::endl;
                }
            }
            else {
                getline(sr, line);
                getline(sr, line);
                getline(sr, line);
                getline(sr, line);
                continue;
            }
            
            getline(sr, line);
            double averageMass;
            std::regex openParRegex(R"(\[)");
            std::smatch opmatch;
            if (std::regex_search (line, opmatch, openParRegex))  {
                std::sregex_iterator it(line.begin(), line.end(), DoubleRegex);
                std::sregex_iterator reg_end;
                double averageMass1=-1;
                double averageMass2=-1;
                int i=0;
                
                for ( ; it!= reg_end; ++it, ++i ) {
                    if ( i== 0 ) {
                        try {
                            averageMass1 = std::stod(it->str());
                        }
                        catch (std::invalid_argument &e ) {
                            std::cout << "Could not extract average Mass 1 " << std::endl;
                        }
                    }else if ( i == 1 ) {
                        try {
                            averageMass2 = std::stod(it->str());
                        }
                        catch (std::invalid_argument &e ) {
                            std::cout << "Could not extract average Mass 2 " << std::endl;
                        }
                    }
                }
                averageMass = (averageMass1 + averageMass2) / 2;
            }
            else {
                //averageMass = Convert::ToDouble(Regex::Match(line, R"([\d\.]+)")->Value);
                std::regex_search(line, opmatch, DoubleRegex ); 
                try {
                    averageMass = std::stod(opmatch.str());
                }
                catch (std::invalid_argument &e ) {
                    std::cout << "Could not extract average Mass " << std::endl;
                }
                
            }
            
            if (atomicNumber != prevAtomicNumber) {
                element = new Element(atomicSymbol, atomicNumber, averageMass);
                PeriodicTable::Add(element);
            }
            
            element->AddIsotope(massNumber, atomicMass, abundance);
            
            getline(sr, line);
            getline(sr, line);
            getline(sr, line);
            prevAtomicNumber = atomicNumber;
        } while (line.find("Atomic Number") != std::string::npos);
        
//C# TO C++ CONVERTER TODO TASK: A 'delete element' statement was not added since element was passed to a method or constructor. Handle memory management manually.
        sr.close();
    }
}
