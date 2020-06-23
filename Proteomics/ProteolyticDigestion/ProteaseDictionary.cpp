#include <iostream>
#include <fstream>

#include "ProteaseDictionary.h"
#include "Protease.h"
#include "DigestionMotif.h"
#include "CleavageSpecificity.h"
#include "stringhelper.h"
#include "tangible_filesystem.h"

//using namespace Proteomics::Fragmentation;
namespace Proteomics
{
    namespace ProteolyticDigestion
    {

        std::unordered_map<std::string, Protease*> ProteaseDictionary::privateDictionary;

        void ProteaseDictionary::StaticConstructor()
        {
#ifdef ORIG
            auto pathToProgramFiles = Environment::GetFolderPath(Environment::SpecialFolder::ProgramFiles);
            std::string dataDirectory = !StringHelper::isEmptyOrWhiteSpace(pathToProgramFiles) &&
                AppDomain::CurrentDomain->BaseDirectory.find(pathToProgramFiles) != std::string::npos &&
                !AppDomain::CurrentDomain->BaseDirectory.find("Jenkins") != std::string::npos ?
                FileSystem::combine(Environment::GetFolderPath(Environment::SpecialFolder::LocalApplicationData),
                                    "MetaMorpheus") :  AppDomain::CurrentDomain->BaseDirectory;
#endif

            std::string dataDirectory = FileSystem::getCurrentDirectory();
#ifdef ORIG
            std::string path = FileSystem::combine(dataDirectory, "ProteolyticDigestion", "proteases.tsv");
#endif
            std::string path = dataDirectory  + "/proteases.tsv";
            setDictionary(LoadProteaseDictionary(path));                
        }

        std::unordered_map<std::string, Protease*> ProteaseDictionary::getDictionary()
        {
            if (privateDictionary.size() == 0 ) {
                ProteaseDictionary::StaticConstructor();
            }
            return privateDictionary;
        }

        void ProteaseDictionary::setDictionary(const std::unordered_map<std::string, Protease*> &value)
        {
            privateDictionary = value;
        }

        // Edgar: new for the C++ version.
        void ProteaseDictionary::insert ( std::string name, Protease* value)
        {
            if (privateDictionary.size() == 0 ) {
                ProteaseDictionary::StaticConstructor();
            }
            privateDictionary.emplace(name, value);
        }

        
        std::unordered_map<std::string, Protease*> ProteaseDictionary::LoadProteaseDictionary(const std::string &path)
        {

            std::unordered_map<std::string, Protease*> dict = std::unordered_map<std::string, Protease*>();
#ifdef ORIG
            std::vector<std::string> myLines = File::ReadAllLines(path);
            myLines = myLines.Skip(1)->ToArray();
#endif
            std::vector<std::string> myLines;
            std::ifstream sr(path);
            if ( !sr.is_open() ) {
                std::cout << " Could not load Protease Dictionary " << path << std::endl;
                return dict;
            }
            
            std::string oneline;
            int n=0;
            while( getline (sr, oneline) ){
                if ( n!= 0 ) {
                    myLines.push_back(oneline);
                }
                n++;
            };

            for (auto line : myLines)
            {
                
                if (StringHelper::trim(line) != "") // skip empty lines
                {
                    std::vector<std::string> fields = StringHelper::split(line, '\t');
                    std::vector<DigestionMotif*> motifList = DigestionMotif::ParseDigestionMotifsFromString(fields[1]);

                    std::string name = fields[0];
#ifdef ORIG
                    auto cleavageSpecificity = (std::any_cast<CleavageSpecificity>(Enum::Parse(typeof(CleavageSpecificity), fields[4], true)));
#endif
                    auto cleavageSpecificity = CleavageSpecificityExtension::ParseString(fields[4]);
                    std::string psiMsAccessionNumber = fields[5];
                    std::string psiMsName = fields[6];
                    auto protease = new Protease(name, cleavageSpecificity, psiMsAccessionNumber, psiMsName, motifList);
                    dict.emplace(protease->getName(), protease);

                    // C# TO C++ CONVERTER TODO TASK: A 'delete protease' statement was not added since protease was
                    // passed to a method or constructor. Handle memory management manually.
                }
            }

            return dict;
        }
    }
}
