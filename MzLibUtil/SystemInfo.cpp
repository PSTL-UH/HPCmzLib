#include "SystemInfo.h"

using namespace Microsoft::Win32;
#if ! defined(ONLYNETSTANDARD)
#endif

namespace MzLibUtil {

    std::wstring SystemInfo::CompleteSystemInfo() {
        StringBuilder *fullSystemString = new StringBuilder();

        fullSystemString->append(SystemProse() + L"\n");

        fullSystemString->append(DotNet());
        fullSystemString->append(MsFileReader_FileIo());
        fullSystemString->append(MsFileReader_Fregistry());
        fullSystemString->append(MsFileReader_XRawfile2());

        delete fullSystemString;
        return fullSystemString->toString();
    }

    std::wstring SystemInfo::SystemProse() {
        StringBuilder *fullSystemProse = new StringBuilder();

        fullSystemProse->append(L"Data files were processed on a " + GetManufacturer() + L" computer ");
        fullSystemProse->append(L"using " + WindowsOperatingSystemVersion());
        fullSystemProse->append(L" with a " + GetCpuRegister());
        fullSystemProse->append(L" and " + ProcessorCount() + L" cores ");
        fullSystemProse->append(L"operating at " + GetMaxClockSpeed() + L"GHz ");
        fullSystemProse->append(L"and " + InstalledRam() + L"GB installed RAM.");

        delete fullSystemProse;
        return fullSystemProse->toString();
    }

    std::wstring SystemInfo::GetManufacturer() {
        std::wstring computerModel = L"UNDETERMINED";
    #if defined(ONLYNETSTANDARD)
        return computerModel;
    #else
        try {
            System::Management::SelectQuery *query = new System::Management::SelectQuery(LR"(Select * from Win32_ComputerSystem)");

//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (System.Management.ManagementObjectSearcher searcher = new System.Management.ManagementObjectSearcher(query))
            {
                System::Management::ManagementObjectSearcher searcher = System::Management::ManagementObjectSearcher(query);
                for (System::Management::ManagementObject *process : searcher.Get()) {
                    process->Get();
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
                    computerModel = process[L"Manufacturer"].ToString() + L" " + process[L"Model"].ToString();
                }
            }

//C# TO C++ CONVERTER TODO TASK: A 'delete query' statement was not added since query was passed to a method or constructor. Handle memory management manually.
            return computerModel;
        }
        catch (...) {
            return computerModel;
        }
    #endif
    }

    std::wstring SystemInfo::GetWindowsOs() {
    #if defined(ONLYNETSTANDARD)
        return L"UNDETERMINED OPERATING SYSTEM";
    #else
        try {
            auto reg = Registry::LocalMachine->OpenSubKey(LR"(SOFTWARE\Microsoft\Windows NT\CurrentVersion)");

            return (std::any_cast<std::wstring>(reg->GetValue(L"ProductName")));
        }
        catch (...) {
            return L"UNDETERMINED OPERATING SYSTEM";
        }
    #endif
    }

    std::wstring SystemInfo::GetCpuRegister() {
        try {
            if (Environment::Is64BitOperatingSystem) {
                return L"64-Bit processor";
            }
            else {
                return L"32-Bit processor";
            }
        }
        catch (...) {
            return L"UNDETERMINED-BIT PROCESSOR";
        }
    }

    std::wstring SystemInfo::GetMaxClockSpeed() {
    #if defined(ONLYNETSTANDARD)
        return L"UNDETERMINED";
    #else
        try {
            RegistryKey *registrykeyHKLM = Registry::LocalMachine;
            std::wstring keyPath = LR"(HARDWARE\DESCRIPTION\System\CentralProcessor\0)";
            RegistryKey *registrykeyCPU = registrykeyHKLM->OpenSubKey(keyPath, false);
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
            std::wstring MHz = registrykeyCPU->GetValue(L"~MHz").ToString();
            double numericalMHz = std::stod(MHz) / 1000;
            registrykeyCPU->Close();
            return std::to_wstring(numericalMHz);
        }
        catch (...) {
            return L"UNDETERMINED";
        }
    #endif
    }

    std::wstring SystemInfo::WindowsOperatingSystemVersion() {
        try {
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
            return (L"Windows version " + Environment::OSVersion->Version->ToString());
        }
        catch (...) {
            return L"UNDETERMINED OPERATING SYSTEM";
        }
    }

    std::wstring SystemInfo::DotNet() {
    #if defined(ONLYNETSTANDARD)
        return L"Windows .Net Version could not be determined.\n";
    #else
        try {
            const std::wstring subkey = LR"(SOFTWARE\Microsoft\NET Framework Setup\NDP\v4\Full\)";

//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (RegistryKey ndpKey = RegistryKey.OpenBaseKey(RegistryHive.LocalMachine, RegistryView.Registry32).OpenSubKey(subkey))
            {
                RegistryKey ndpKey = RegistryKey::OpenBaseKey(RegistryHive::LocalMachine, RegistryView::Registry32)->OpenSubKey(subkey);
                if (ndpKey != nullptr && ndpKey.GetValue(L"Release") != nullptr) {
                    return L".NET Framework Version: " + CheckFor45PlusVersion(std::any_cast<int>(ndpKey.GetValue(L"Release")));
                }
                else {
                    return L".NET Framework Version 4.5 or later is not detected.";
                }
            }
        }
        catch (...) {
            return L"Windows .Net Version could not be determined.\n";
        }
    #endif
    }

    std::wstring SystemInfo::InstalledRam() {
    #if defined(ONLYNETSTANDARD)
        return L"UNKNOWN ";
    #else
        try {
            std::wstring Query = L"SELECT Capacity FROM Win32_PhysicalMemory";
            ManagementObjectSearcher *searcher = new ManagementObjectSearcher(Query);

            unsigned long long Capacity = 0;
            for (ManagementObject *WniPART : searcher->Get()) {
                Capacity += static_cast<unsigned long long>(WniPART->Properties[L"Capacity"]->Value);
            }

            delete searcher;
            return (std::to_wstring(Capacity / 1073741824));
        }
        catch (...) {
            return L"UNKNOWN ";
        }
    #endif
    }

    std::wstring SystemInfo::ProcessorCount() {
        try {
            return (std::to_wstring(Environment::ProcessorCount));
        }
        catch (...) {
            return L"AN UNKNOWN NUMBER OF ";
        }
    }

    std::wstring SystemInfo::MsFileReader_FileIo() {
        try {
            FileVersionInfo *myFileVersionInfo = FileVersionInfo::GetVersionInfo(LR"(C:\Program Files\Thermo\MSFileReader\Fileio_x64.dll)");
            return (L"Thermo MSFileReader " + myFileVersionInfo->FileDescription + L"\t\t" + L"Version: " + myFileVersionInfo->FileVersion + L"\n");
        }
        catch (...) {
            return LR"(C:\Program Files\Thermo\MSFileReader\Fileio_x64.dll MISSING\n)";
        }
    }

    std::wstring SystemInfo::MsFileReader_Fregistry() {
        try {
            FileVersionInfo *myFileVersionInfo = FileVersionInfo::GetVersionInfo(LR"(C:\Program Files\Thermo\MSFileReader\fregistry_x64.dll)");
            return (L"Thermo MSFileReader " + myFileVersionInfo->FileDescription + L"\t\t" + L"Version: " + myFileVersionInfo->FileVersion + L"\n");
        }
        catch (...) {
            return LR"(C:\Program Files\Thermo\MSFileReader\fregistry_x64.dll MISSING\n)";
        }
    }

    std::wstring SystemInfo::MsFileReader_XRawfile2() {
        try {
            FileVersionInfo *myFileVersionInfo = FileVersionInfo::GetVersionInfo(LR"(C:\Program Files\Thermo\MSFileReader\XRawfile2_x64.dll)");
            return (L"Thermo MSFileReader " + myFileVersionInfo->FileDescription + L"\t\t" + L"Version: " + myFileVersionInfo->FileVersion + L"\n");
        }
        catch (...) {
            return LR"(C:\Program Files\Thermo\MSFileReader\XRawfile2_x64.dll MISSING\n)";
        }
    }

    std::wstring SystemInfo::CheckFor45PlusVersion(int releaseKey) {
        if (releaseKey >= 460798) {
            return L"4.7 or later";
        }
        if (releaseKey >= 394802) {
            return L"4.6.2";
        }
        if (releaseKey >= 394254) {
            return L"4.6.1";
        }
        if (releaseKey >= 393295) {
            return L"4.6";
        }
        if ((releaseKey >= 379893)) {
            return L"4.5.2";
        }
        if ((releaseKey >= 378675)) {
            return L"4.5.1";
        }
        if ((releaseKey >= 378389)) {
            return L"4.5";
        }
        // This code should never execute. A non-null release key should mean
        // that 4.5 or later is installed.
        return L"No 4.5 or later version detected";
    }
}
