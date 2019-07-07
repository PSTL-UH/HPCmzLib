#pragma once

#include <string>

namespace Proteomics
{
    class SpliceSite
    {
    private:
        int privateOneBasedBeginPosition = 0;
        int privateOneBasedEndPosition = 0;
        std::string privateDescription;

    public:
        SpliceSite(int oneBasedBegin, int oneBasedEnd, const std::string &description);

        SpliceSite(int oneBasedPosition, const std::string &description);

        int getOneBasedBeginPosition() const;
        int getOneBasedEndPosition() const;
        std::string getDescription() const;

        bool Equals(std::any obj) override;

        int GetHashCode() override;
    };
}
