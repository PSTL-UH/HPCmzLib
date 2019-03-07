#include "PeriodicTableLoader.h"
#include "../Chemistry/Element.h"
#include "../Chemistry/PeriodicTable.h"

#include <iostream>
#include <fstream>

//using namespace Chemistry;

namespace UsefulProteomicsDatabases {

    void PeriodicTableLoader::Load(const std::string &elementLocation) {
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (StreamReader sr = new StreamReader(elementLocation))
#ifdef ORIG
        StreamReader sr = StreamReader(elementLocation);
        std::string line = sr.ReadLine();
        while (!line.find("Atomic Number") != std::string::npos) {
            line = sr.ReadLine();
        }
#endif
        std::ifstream sr(elementLocation);
        std::string line;
        while ( getline(sr, line) ){
            if ( line.find("Atomic Number", 0) != std::string::npos ) {
                break;
            }
        }
        
        auto prevAtomicNumber = -1;
        Element *element = new Element("fake", prevAtomicNumber, -1);
        do {
            //int atomicNumber = Convert::ToInt32(Regex::Match(line, R"(\d+)")->Value);
            int atomicNumber=-1;
            std::regex atomicNumberRegex(R"(\d+)");
            std::smatch amatch;
            if ( std::regex_search(line, amatch, atomicNumberRegex) ) {
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
            std::regex atomicSymbolRegex(R"([A-Za-z]+$)");
            std::smatch atmatch;
            if ( std::regex_search(line, atmatch, atomicNumberRegex) ) {
                atomicSymbol = atmatch.str();
            }
        
            getline(sr, line);
            //int massNumber = Convert::ToInt32(Regex::Match(line, R"(\d+)")->Value);
            int massNumber=-1;
            std::smatch mmatch;
            if ( std::regex_search(line, mmatch, atomicNumberRegex) ) {
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
            std::regex atomicMassRegex(R"([\d\.]+)");
            std::smatch ammatch;
            if ( std::regex_search(line, ammatch, atomicMassRegex) ) {
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
            if (std::regex_search(line, abmatch, atomicMassRegex )) {
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
            std::regex averageMass1Regex(R"((?<=\[)[\d\.]+)");
            std::smatch opmatch;
            if (std::regex_search (line, opmatch, openParRegex))  {
                //double averageMass1 = Convert::ToDouble(Regex::Match(line, R"((?<=\[)[\d\.]+)")->Value);
                double averageMass1=-1;
                std::regex_search (line, opmatch, averageMass1Regex);
                try {
                    averageMass1 = std::stod(opmatch.str());
                }
                catch (std::invalid_argument &e ) {
                    std::cout << "Could not extract average Mass 1 " << std::endl;
                }
                
                //auto kkajsdf = Regex::Match(line, R"((?<=,)[\d\.]+)")->Value;
                std::regex kkajsdfRegex(R"((?<=,)[\d\.]+)");
                std::regex_search(line, opmatch, kkajsdfRegex);
                double averageMass2 = -1;
                try {
                    averageMass2 = std::stod(opmatch.str());
                }
                catch (std::invalid_argument &e ) {
                    std::cout << "Could not extract average Mass 2 " << std::endl;
                }
                averageMass = (averageMass1 + averageMass2) / 2;
            }
            else {
                //averageMass = Convert::ToDouble(Regex::Match(line, R"([\d\.]+)")->Value);
                std::regex_search(line, opmatch, atomicMassRegex ); 
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
