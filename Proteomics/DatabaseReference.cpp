#include "stringhelper.h"
#include "DatabaseReference.h"
#include <bits/stdc++.h>
#include <algorithm>

namespace Proteomics {

    DatabaseReference::DatabaseReference(const std::string &type, const std::string &id, std::vector<std::tuple<std::string, std::string>> &properties) {
        privateType = type;
        privateId = id;
        privateProperties = properties;
    }

    std::string DatabaseReference::getType() const {
        return privateType;
    }

    std::string DatabaseReference::getId() const {
        return privateId;
    }

    std::vector<std::tuple<std::string, std::string>> DatabaseReference::getProperties() const {
        return privateProperties;
    }

    bool DatabaseReference::Equals(DatabaseReference *d) {
#ifdef ORIG
        DatabaseReference *d = dynamic_cast<DatabaseReference*>(obj);
        return d != nullptr              &&
               d->getType() == getType() &&
               d->getId() == getId()     &&
               d->getProperties().OrderBy([&] (std::any x) { return x; }).SequenceEqual(getProperties().OrderBy([&] (std::any x) { return x; }));
#endif
        
        if (d == nullptr || d->getType() != getType() || d->getId() != getId() ){
            return false;
        }
        std::vector<std::tuple<std::string, std::string>> dp1 = d->getProperties();
        std::sort(dp1.begin(), dp1.end());
        std::vector<std::tuple<std::string, std::string>> dp = getProperties();
        std::sort(dp.begin(), dp.end());
        // Sort dp1 and dp to ensure that Properties are listed in
        // alphabetical order. If there is a mismatch, return false;
        if (dp.size() != dp1.size() ) {
            return false;
        }
        return std::equal(dp1.begin(), dp1.end(), dp.begin());
    }

    int DatabaseReference::GetHashCode() {
        int hash = StringHelper::GetHashCode(getType()) ^ StringHelper::GetHashCode(getId());
        for (auto property_Renamed : getProperties()) {
            hash = hash ^ StringHelper::GetHashCode(property_Renamed);
        }
        return hash;
    }
}
