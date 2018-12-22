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

    void Loaders::UpdateUniprot(const std::wstring &uniprotLocation) {
        DownloadUniprot(uniprotLocation);
        if (!FileSystem::fileExists(uniprotLocation)) {
            std::wcout << L"Uniprot database did not exist, writing to disk" << std::endl;
            FileSystem::renamePath(uniprotLocation + L".temp", uniprotLocation);
            return;
        }
        bool ye = FilesAreEqual_Hash(uniprotLocation + L".temp", uniprotLocation);
        if (ye) {
            std::wcout << L"Uniprot database is up to date, doing nothing" << std::endl;
            File::Delete(uniprotLocation + L".temp");
        }
        else {
            std::wcout << L"Uniprot database updated, saving old version as backup" << std::endl;
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
            FileSystem::renamePath(uniprotLocation, uniprotLocation + DateTime::Now.ToString(L"dd-MMM-yyyy-HH-mm-ss"));
            FileSystem::renamePath(uniprotLocation + L".temp", uniprotLocation);
        }
    }

    void Loaders::UpdateUnimod(const std::wstring &unimodLocation) {
        DownloadUnimod(unimodLocation);
        if (!FileSystem::fileExists(unimodLocation)) {
            std::wcout << L"Unimod database did not exist, writing to disk" << std::endl;
            FileSystem::renamePath(unimodLocation + L".temp", unimodLocation);
            return;
        }
        bool ye = FilesAreEqual_Hash(unimodLocation + L".temp", unimodLocation);
        if (ye) {
            std::wcout << L"Unimod database is up to date, doing nothing" << std::endl;
            File::Delete(unimodLocation + L".temp");
        }
        else {
            std::wcout << L"Unimod database updated, saving old version as backup" << std::endl;
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
            FileSystem::renamePath(unimodLocation, unimodLocation + DateTime::Now.ToString(L"dd-MMM-yyyy-HH-mm-ss"));
            FileSystem::renamePath(unimodLocation + L".temp", unimodLocation);
        }
    }

    void Loaders::UpdatePsiMod(const std::wstring &psimodLocation) {
        DownloadPsiMod(psimodLocation);
        if (!FileSystem::fileExists(psimodLocation)) {
            std::wcout << L"PSI-MOD database did not exist, writing to disk" << std::endl;
            FileSystem::renamePath(psimodLocation + L".temp", psimodLocation);
            return;
        }
        if (FilesAreEqual_Hash(psimodLocation + L".temp", psimodLocation)) {
            std::wcout << L"PSI-MOD database is up to date, doing nothing" << std::endl;
            File::Delete(psimodLocation + L".temp");
        }
        else {
            std::wcout << L"PSI-MOD database updated, saving old version as backup" << std::endl;
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
            FileSystem::renamePath(psimodLocation, psimodLocation + DateTime::Now.ToString(L"dd-MMM-yyyy-HH-mm-ss"));
            FileSystem::renamePath(psimodLocation + L".temp", psimodLocation);
        }
    }

    void Loaders::UpdateElements(const std::wstring &elementLocation) {
        DownloadElements(elementLocation);
        if (!FileSystem::fileExists(elementLocation)) {
            std::wcout << L"Element database did not exist, writing to disk" << std::endl;
            FileSystem::renamePath(elementLocation + L".temp", elementLocation);
            return;
        }
        if (FilesAreEqual_Hash(elementLocation + L".temp", elementLocation)) {
            std::wcout << L"Element database is up to date, doing nothing" << std::endl;
            File::Delete(elementLocation + L".temp");
        }
        else {
            std::wcout << L"Element database updated, saving old version as backup" << std::endl;
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
            FileSystem::renamePath(elementLocation, elementLocation + DateTime::Now.ToString(L"dd-MMM-yyyy-HH-mm-ss"));
            FileSystem::renamePath(elementLocation + L".temp", elementLocation);
        }
    }

    std::unordered_map<std::wstring, int> Loaders::GetFormalChargesDictionary(obo *psiModDeserialized) {
        auto modsWithFormalCharges = psiModDeserialized->getItems().OfType<UsefulProteomicsDatabases::Generated::oboTerm*>().Where([&] (std::any b) {
            return b::xref_analog != nullptr && b::xref_analog::Any([&] (std::any c) {
                c::dbname->Equals(L"FormalCharge");
            });
        });
        Regex *digitsOnly = new Regex(LR"([^\d])");

        delete digitsOnly;
//C# TO C++ CONVERTER TODO TASK: The following lambda expression could not be converted:
        return modsWithFormalCharges->ToDictionary(b => TangibleLambdaToken237public static void LoadElements(std::wstring elementLocation){if (!FileSystem::fileExists(elementLocation))UpdateElements(elementLocation);
        PeriodicTableLoader::Load(elementLocation);
    }

    std::vector<ModificationWithLocation*> Loaders::LoadUnimod(const std::wstring &unimodLocation) {
        if (!FileSystem::fileExists(unimodLocation)) {
            UpdateUnimod(unimodLocation);
        }
        return UnimodLoader::ReadMods(unimodLocation);
    }

    Generated::obo *Loaders::LoadPsiMod(const std::wstring &psimodLocation) {
        auto psimodSerializer = new XmlSerializer(Generated::obo::typeid);

        if (!FileSystem::fileExists(psimodLocation)) {
            UpdatePsiMod(psimodLocation);
        }

        delete psimodSerializer;
        FileStream tempVar(psimodLocation, FileMode::Open, FileAccess::Read, FileShare::Read);
        return dynamic_cast<Generated::obo*>(psimodSerializer->Deserialize(&tempVar));
    }

    std::vector<ModificationWithLocation*> Loaders::LoadUniprot(const std::wstring &uniprotLocation, std::unordered_map<std::wstring, int> &formalChargesDictionary) {
        if (!FileSystem::fileExists(uniprotLocation)) {
            UpdateUniprot(uniprotLocation);
        }
        return PtmListLoader::ReadModsFromFile(uniprotLocation, formalChargesDictionary).OfType<ModificationWithLocation*>();
    }

    bool Loaders::FilesAreEqual_Hash(const std::wstring &first, const std::wstring &second) {
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (FileStream a = File.Open(first, FileMode.Open, FileAccess.Read))
    {
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
    }

    void Loaders::DownloadPsiMod(const std::wstring &psimodLocation) {
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (WebClient Client = new WebClient())
    {
            WebClient Client = WebClient();
            Client.DownloadFile(LR"(http://psidev.cvs.sourceforge.net/viewvc/psidev/psi/mod/data/PSI-MOD.obo.xml)", psimodLocation + L".temp");
    }
    }

    void Loaders::DownloadUnimod(const std::wstring &unimodLocation) {
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (WebClient Client = new WebClient())
    {
            WebClient Client = WebClient();
            Client.DownloadFile(LR"(http://www.unimod.org/xml/unimod.xml)", unimodLocation + L".temp");
    }
    }

    void Loaders::DownloadElements(const std::wstring &elementLocation) {
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (WebClient Client = new WebClient())
    {
            WebClient Client = WebClient();
            Client.DownloadFile(LR"(http://physics.nist.gov/cgi-bin/Compositions/stand_alone.pl?ele=&ascii=ascii2&isotype=some)", elementLocation + L".temp");
    }
    }

    void Loaders::DownloadUniprot(const std::wstring &uniprotLocation) {
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (WebClient Client = new WebClient())
    {
            WebClient Client = WebClient();
            Client.DownloadFile(LR"(http://www.uniprot.org/docs/ptmlist.txt)", uniprotLocation + L".temp");
    }
    }
}
