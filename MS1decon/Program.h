#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <optional>
#include "stringbuilder.h"

using namespace Fclp;
using namespace IO::MzML;
using namespace IO::Thermo;
using namespace MassSpectrometry;
using namespace UsefulProteomicsDatabases;

namespace ConsoleApp1 {
    class Program {
//        #region Private Methods

    private:
        static void Main(std::vector<std::wstring> &args);

        static void DoFileDecon(std::vector<std::wstring> &args);
            else {
                std::wcout << L"BAD PARAMETERS" << std::endl;
                std::wcout << result::ErrorText << std::endl;
            }
    };

//        #endregion Private Methods
}

    class ApplicationArguments {
//        #region Public Properties

    public:
        std::optional<int> getMinScan() const;
        void setMinScan(const std::optional<int> &value);
        std::optional<int> getMaxScan() const;
        void setMaxScan(const std::optional<int> &value);
        int getMaxAssumedChargeState() const;
        void setMaxAssumedChargeState(int value);
        double getDeconvolutionTolerancePpm() const;
        void setDeconvolutionTolerancePpm(double value);
        double getIntensityRatioLimit() const;
        void setIntensityRatioLimit(double value);
        double getAggregationTolerancePpm() const;
        void setAggregationTolerancePpm(double value);
        std::wstring getFilePath() const;
        void setFilePath(const std::wstring &value);

//        #endregion Public Properties

//        #region Public Methods

        std::wstring ToString() override;

//        #endregion Public Methods
    };
}
