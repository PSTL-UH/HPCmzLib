#include "ProteaseDictionary.h"
#include "Protease.h"
#include "DigestionMotif.h"
#include "CleavageSpecificity.h"

using namespace Proteomics::Fragmentation;
namespace Proteomics
{
    namespace ProteolyticDigestion
    {

std::unordered_map<std::string, Protease*> ProteaseDictionary::privateDictionary;

        ProteaseDictionary::StaticConstructor::StaticConstructor()
        {
        auto pathToProgramFiles = Environment::GetFolderPath(Environment::SpecialFolder::ProgramFiles);
        std::string dataDirectory = !StringHelper::isEmptyOrWhiteSpace(pathToProgramFiles) && AppDomain::CurrentDomain->BaseDirectory.find(pathToProgramFiles) != std::string::npos && !AppDomain::CurrentDomain->BaseDirectory.find("Jenkins") != std::string::npos ? FileSystem::combine(Environment::GetFolderPath(Environment::SpecialFolder::LocalApplicationData), "MetaMorpheus") : AppDomain::CurrentDomain->BaseDirectory;
                
        std::string path = FileSystem::combine(dataDirectory, "ProteolyticDigestion", "proteases.tsv");
        setDictionary(LoadProteaseDictionary(path));
                
        }

ProteaseDictionary::StaticConstructor ProteaseDictionary::staticConstructor;

        std::unordered_map<std::string, Protease*> ProteaseDictionary::getDictionary()
        {
            return privateDictionary;
        }

        void ProteaseDictionary::setDictionary(const std::unordered_map<std::string, Protease*> &value)
        {
            privateDictionary = value;
        }

        std::unordered_map<std::string, Protease*> ProteaseDictionary::LoadProteaseDictionary(const std::string &path)
        {

            std::unordered_map<std::string, Protease*> dict = Dictionary<std::string, Protease*>();

            std::vector<std::string> myLines = File::ReadAllLines(path);
            myLines = myLines.Skip(1)->ToArray();

            for (auto line : myLines)
            {
                if (line.Trim() != "") // skip empty lines
                {
                    std::vector<std::string> fields = line.Split('\t');
                    std::vector<DigestionMotif*> motifList = DigestionMotif::ParseDigestionMotifsFromString(fields[1]);

                    std::string name = fields[0];
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
                    auto cleavageSpecificity = (std::any_cast<CleavageSpecificity>(Enum::Parse(typeof(CleavageSpecificity), fields[4], true)));
                    std::string psiMsAccessionNumber = fields[5];
                    std::string psiMsName = fields[6];
                    auto protease = new Protease(name, cleavageSpecificity, psiMsAccessionNumber, psiMsName, motifList);
                    dict.emplace(protease->getName(), protease);

//C# TO C++ CONVERTER TODO TASK: A 'delete protease' statement was not added since protease was passed to a method or constructor. Handle memory management manually.
                }
            }

            return dict;

        }
    }
}
