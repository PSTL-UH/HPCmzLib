#include "stringhelper.h"
#include "DatabaseReference.h"
#include "Assert.h"
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
        return Assert::SequenceEqual( getProperties(), d->getProperties() );
    }

    int DatabaseReference::GetHashCode() {
        int hash = StringHelper::GetHashCode(getType()) ^ StringHelper::GetHashCode(getId());
        for (auto property_Renamed : getProperties()) {
            hash = hash ^ StringHelper::GetHashCode(property_Renamed);
        }
        return hash;
    }
}
