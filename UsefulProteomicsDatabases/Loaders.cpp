#include "Loaders.h"
#include "Generated/UsefulProteomicsDatabases.Generated.oboTerm.h"
#include "PeriodicTableLoader.h"
#include "../Proteomics/ModificationWithLocation.h"
#include "UnimodLoader.h"
#include "Generated/UsefulProteomicsDatabases.Generated.obo.h"
#include "PtmListLoader.h"

using namespace Proteomics;
using namespace UsefulProteomicsDatabases::Generated;

namespace UsefulProteomicsDatabases {

    Loaders::StaticConstructor::StaticConstructor() {
        ServicePointManager::SecurityProtocol = SecurityProtocolType::Tls12 | SecurityProtocolType::Tls11 | SecurityProtocolType::Tls;
    }

Loaders::StaticConstructor Loaders::staticConstructor;

    void Loaders::UpdateUniprot(const std::string &uniprotLocation) {
        DownloadUniprot(uniprotLocation);
        if (!FileSystem::fileExists(uniprotLocation)) {
            std::cout << "Uniprot database did not exist, writing to disk" << std::endl;
            FileSystem::renamePath(uniprotLocation + ".temp", uniprotLocation);
            return;
        }
        bool ye = FilesAreEqual_Hash(uniprotLocation + ".temp", uniprotLocation);
        if (ye) {
            std::cout << "Uniprot database is up to date, doing nothing" << std::endl;
            File::Delete(uniprotLocation + ".temp");
        }
        else {
            std::cout << "Uniprot database updated, saving old version as backup" << std::endl;
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
            FileSystem::renamePath(uniprotLocation, uniprotLocation + DateTime::Now.ToString("dd-MMM-yyyy-HH-mm-ss"));
            FileSystem::renamePath(uniprotLocation + ".temp", uniprotLocation);
        }
    }

    void Loaders::UpdateUnimod(const std::string &unimodLocation) {
        DownloadUnimod(unimodLocation);
        if (!FileSystem::fileExists(unimodLocation)) {
            std::cout << "Unimod database did not exist, writing to disk" << std::endl;
            FileSystem::renamePath(unimodLocation + ".temp", unimodLocation);
            return;
        }
        bool ye = FilesAreEqual_Hash(unimodLocation + ".temp", unimodLocation);
        if (ye) {
            std::cout << "Unimod database is up to date, doing nothing" << std::endl;
            File::Delete(unimodLocation + ".temp");
        }
        else {
            std::cout << "Unimod database updated, saving old version as backup" << std::endl;
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
            FileSystem::renamePath(unimodLocation, unimodLocation + DateTime::Now.ToString("dd-MMM-yyyy-HH-mm-ss"));
            FileSystem::renamePath(unimodLocation + ".temp", unimodLocation);
        }
    }

    void Loaders::UpdatePsiMod(const std::string &psimodLocation) {
        DownloadPsiMod(psimodLocation);
        if (!FileSystem::fileExists(psimodLocation)) {
            std::cout << "PSI-MOD database did not exist, writing to disk" << std::endl;
            FileSystem::renamePath(psimodLocation + ".temp", psimodLocation);
            return;
        }
        if (FilesAreEqual_Hash(psimodLocation + ".temp", psimodLocation)) {
            std::cout << "PSI-MOD database is up to date, doing nothing" << std::endl;
            File::Delete(psimodLocation + ".temp");
        }
        else {
            std::cout << "PSI-MOD database updated, saving old version as backup" << std::endl;
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
            FileSystem::renamePath(psimodLocation, psimodLocation + DateTime::Now.ToString("dd-MMM-yyyy-HH-mm-ss"));
            FileSystem::renamePath(psimodLocation + ".temp", psimodLocation);
        }
    }

    void Loaders::UpdateElements(const std::string &elementLocation) {
        DownloadElements(elementLocation);
        if (!FileSystem::fileExists(elementLocation)) {
            std::cout << "Element database did not exist, writing to disk" << std::endl;
            FileSystem::renamePath(elementLocation + ".temp", elementLocation);
            return;
        }
        if (FilesAreEqual_Hash(elementLocation + ".temp", elementLocation)) {
            std::cout << "Element database is up to date, doing nothing" << std::endl;
            File::Delete(elementLocation + ".temp");
        }
        else {
            std::cout << "Element database updated, saving old version as backup" << std::endl;
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
            FileSystem::renamePath(elementLocation, elementLocation + DateTime::Now.ToString("dd-MMM-yyyy-HH-mm-ss"));
            FileSystem::renamePath(elementLocation + ".temp", elementLocation);
        }
    }

    std::unordered_map<std::string, int> Loaders::GetFormalChargesDictionary(obo *psiModDeserialized) {
        auto modsWithFormalCharges = psiModDeserialized->getItems().OfType<UsefulProteomicsDatabases::Generated::oboTerm*>().Where([&] (std::any b) {
            return b::xref_analog != nullptr && b::xref_analog::Any([&] (std::any c) {
                c::dbname->Equals("FormalCharge");
            });
        });
        Regex *digitsOnly = new Regex(LR"([^\d])");

        delete digitsOnly;
//C# TO C++ CONVERTER TODO TASK: The following lambda expression could not be converted:
        return modsWithFormalCharges->ToDictionary(b => TangibleLambdaToken237public static void LoadElements(std::string elementLocation){if (!FileSystem::fileExists(elementLocation))UpdateElements(elementLocation);
        PeriodicTableLoader::Load(elementLocation);
    }

    std::vector<ModificationWithLocation*> Loaders::LoadUnimod(const std::string &unimodLocation) {
        if (!FileSystem::fileExists(unimodLocation)) {
            UpdateUnimod(unimodLocation);
        }
        return UnimodLoader::ReadMods(unimodLocation);
    }

    Generated::obo *Loaders::LoadPsiMod(const std::string &psimodLocation) {
        auto psimodSerializer = new XmlSerializer(Generated::obo::typeid);

        if (!FileSystem::fileExists(psimodLocation)) {
            UpdatePsiMod(psimodLocation);
        }

        delete psimodSerializer;
        FileStream tempVar(psimodLocation, FileMode::Open, FileAccess::Read, FileShare::Read);
        return dynamic_cast<Generated::obo*>(psimodSerializer->Deserialize(&tempVar));
    }

    std::vector<ModificationWithLocation*> Loaders::LoadUniprot(const std::string &uniprotLocation, std::unordered_map<std::string, int> &formalChargesDictionary) {
        if (!FileSystem::fileExists(uniprotLocation)) {
            UpdateUniprot(uniprotLocation);
        }
        return PtmListLoader::ReadModsFromFile(uniprotLocation, formalChargesDictionary).OfType<ModificationWithLocation*>();
    }

    bool Loaders::FilesAreEqual_Hash(const std::string &first, const std::string &second) {
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (FileStream a = File.Open(first, FileMode.Open, FileAccess.Read))
            FileStream a = File::Open(first, FileMode::Open, FileAccess::Read);
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (FileStream b = File.Open(second, FileMode.Open, FileAccess.Read))
            {
            FileStream b = File::Open(second, FileMode::Open, FileAccess::Read);
            std::vector<unsigned char> firstHash = MD5::Create()->ComputeHash(a);
            std::vector<unsigned char> secondHash = MD5::Create()->ComputeHash(b);
            for (int i = 0; i < firstHash.size(); i++) {
                if (firstHash[i] != secondHash[i]) {
                    return false;
                }
            }
            return true;
            }
    }

    void Loaders::DownloadPsiMod(const std::string &psimodLocation) {
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (WebClient Client = new WebClient())
            WebClient Client = WebClient();
            Client.DownloadFile(LR"(http://psidev.cvs.sourceforge.net/viewvc/psidev/psi/mod/data/PSI-MOD.obo.xml)", psimodLocation + ".temp");
    }

    void Loaders::DownloadUnimod(const std::string &unimodLocation) {
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (WebClient Client = new WebClient())
            WebClient Client = WebClient();
            Client.DownloadFile(LR"(http://www.unimod.org/xml/unimod.xml)", unimodLocation + ".temp");
    }

    void Loaders::DownloadElements(const std::string &elementLocation) {
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (WebClient Client = new WebClient())
            WebClient Client = WebClient();
            Client.DownloadFile(LR"(http://physics.nist.gov/cgi-bin/Compositions/stand_alone.pl?ele=&ascii=ascii2&isotype=some)", elementLocation + ".temp");
    }

    void Loaders::DownloadUniprot(const std::string &uniprotLocation) {
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (WebClient Client = new WebClient())
            WebClient Client = WebClient();
            Client.DownloadFile(LR"(http://www.uniprot.org/docs/ptmlist.txt)", uniprotLocation + ".temp");
    }
}
