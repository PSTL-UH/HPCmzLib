#pragma once

#include <string>

namespace Proteomics {
    class DisulfideBond {
    private:
        int privateOneBasedBeginPosition = 0;
        int privateOneBasedEndPosition = 0;
        std::string privateDescription;

    public:
        DisulfideBond(int OneBasedBeginPosition, int OneBasedEndPosition, const std::string &Description);

        /// For interchain disulfide bonds, sets begin and end to the same position.
        DisulfideBond(int OneBasedPosition, const std::string &Description);

        /// <summary>
        /// Beginning position of disulfide bond
        /// </summary>
        int getOneBasedBeginPosition() const;
        void setOneBasedBeginPosition(int value);

        /// <summary>
        /// End position of disulfide bond
        /// </summary>
        int getOneBasedEndPosition() const;
        void setOneBasedEndPosition(int value);

        /// <summary>
        /// Description of this variation (optional)
        /// </summary>
        std::string getDescription() const;
        void setDescription(const std::string &value);

        bool Equals(std::any obj) override;

        int GetHashCode() override;

    };
}
