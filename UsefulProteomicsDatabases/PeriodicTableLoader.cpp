#include "PeriodicTableLoader.h"
#include "../Chemistry/Element.h"
#include "../Chemistry/PeriodicTable.h"

using namespace Chemistry;

namespace UsefulProteomicsDatabases {

    void PeriodicTableLoader::Load(const std::wstring &elementLocation) {
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (StreamReader sr = new StreamReader(elementLocation))
    {
            StreamReader sr = StreamReader(elementLocation);
            std::wstring line = sr.ReadLine();
            while (!line.find(L"Atomic Number") != std::wstring::npos) {
                line = sr.ReadLine();
            }
            auto prevAtomicNumber = -1;
            Element *element = new Element(L"fake", prevAtomicNumber, -1);
            do {
                int atomicNumber = Convert::ToInt32(Regex::Match(line, LR"(\d+)")->Value, CultureInfo::InvariantCulture);

                line = sr.ReadLine();
                std::wstring atomicSymbol = Regex::Match(line, LR"([A-Za-z]+$)")->Value;

                line = sr.ReadLine();
                int massNumber = Convert::ToInt32(Regex::Match(line, LR"(\d+)")->Value, CultureInfo::InvariantCulture);

                line = sr.ReadLine();
                double atomicMass = Convert::ToDouble(Regex::Match(line, LR"([\d\.]+)")->Value, CultureInfo::InvariantCulture);

                line = sr.ReadLine();
                double abundance;
                if (Regex::Match(line, LR"([\d\.]+)")->Success) {
                    abundance = Convert::ToDouble(Regex::Match(line, LR"([\d\.]+)")->Value, CultureInfo::InvariantCulture);
                }
                else {
                    sr.ReadLine();
                    sr.ReadLine();
                    sr.ReadLine();
                    line = sr.ReadLine();
                    continue;
                }

                line = sr.ReadLine();
                double averageMass;
                if (Regex::Match(line, LR"(\[)")->Success) {
                    double averageMass1 = Convert::ToDouble(Regex::Match(line, LR"((?<=\[)[\d\.]+)")->Value, CultureInfo::InvariantCulture);
                    auto kkajsdf = Regex::Match(line, LR"((?<=,)[\d\.]+)")->Value;
                    double averageMass2 = Convert::ToDouble(kkajsdf, CultureInfo::InvariantCulture);
                    averageMass = (averageMass1 + averageMass2) / 2;
                }
                else {
                    averageMass = Convert::ToDouble(Regex::Match(line, LR"([\d\.]+)")->Value, CultureInfo::InvariantCulture);
                }

                if (atomicNumber != prevAtomicNumber) {
                    element = new Element(atomicSymbol, atomicNumber, averageMass);
                    PeriodicTable::Add(element);
                }

                element->AddIsotope(massNumber, atomicMass, abundance);

                sr.ReadLine();
                sr.ReadLine();
                line = sr.ReadLine();
                prevAtomicNumber = atomicNumber;
            } while (line.find(L"Atomic Number") != std::wstring::npos);

//C# TO C++ CONVERTER TODO TASK: A 'delete element' statement was not added since element was passed to a method or constructor. Handle memory management manually.
    }
    }
}
