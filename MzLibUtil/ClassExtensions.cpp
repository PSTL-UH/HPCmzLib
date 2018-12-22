#include "ClassExtensions.h"


namespace MzLibUtil {

    std::vector<double> ClassExtensions::BoxCarSmooth(std::vector<double> &data, int points) {
        // Force to be odd
        points = points - (1 - points % 2);

        int count = data.size();

        int newCount = count - points + 1;

        std::vector<double> smoothedData(newCount);

        for (int i = 0; i < newCount; i++) {
            double value = 0;

            for (int j = i; j < i + points; j++) {
                value += data[j];
            }

            smoothedData[i] = value / points;
        }
        return smoothedData;
    }

template<typename T>
    std::vector<T> ClassExtensions::SubArray(std::vector<T> &data, int index, int length) {
        std::vector<T> result(length);
        Array::Copy(data, index, result, 0, length);
        return result;
    }

template<typename T>
    bool ClassExtensions::ScrambledEquals(std::vector<T> &list1, std::vector<T> &list2) {
        auto cnt = std::unordered_map<T, int>();
        for (auto s : list1) {
            if (cnt.find(s) != cnt.end()) {
                cnt[s]++;
            }
            else {
                cnt.emplace(s, 1);
            }
        }
        for (auto s : list2) {
            if (cnt.find(s) != cnt.end()) {
                cnt[s]--;
            }
            else {
                return false;
            }
        }
        return cnt.Values->All([&] (std::any c) {
            return c == 0;
        });
    }
}
