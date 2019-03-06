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
        bool found=false;
        while ( !found ) {
            getline(sr, line);
            //parse for "Atomic Number");
        }
        
        auto prevAtomicNumber = -1;
        Element *element = new Element("fake", prevAtomicNumber, -1);
        do {
            int atomicNumber = Convert::ToInt32(Regex::Match(line, R"(\d+)")->Value);
            
            getline(sr, line);
            std::string atomicSymbol = Regex::Match(line, R"([A-Za-z]+$)")->Value;
            
            getline(sr, line);
            int massNumber = Convert::ToInt32(Regex::Match(line, R"(\d+)")->Value);
            
            getline(sr, line);
            double atomicMass = Convert::ToDouble(Regex::Match(line, R"([\d\.]+)")->Value);
            
            getline(sr, line);
            double abundance;
            if (Regex::Match(line, R"([\d\.]+)")->Success) {
                abundance = Convert::ToDouble(Regex::Match(line, R"([\d\.]+)")->Value);
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
            if (Regex::Match(line, R"(\[)")->Success) {
                double averageMass1 = Convert::ToDouble(Regex::Match(line, R"((?<=\[)[\d\.]+)")->Value);
                auto kkajsdf = Regex::Match(line, R"((?<=,)[\d\.]+)")->Value;
                double averageMass2 = Convert::ToDouble(kkajsdf);
                averageMass = (averageMass1 + averageMass2) / 2;
            }
            else {
                averageMass = Convert::ToDouble(Regex::Match(line, R"([\d\.]+)")->Value);
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
