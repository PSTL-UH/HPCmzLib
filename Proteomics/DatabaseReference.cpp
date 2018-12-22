#include "DatabaseReference.h"


namespace Proteomics {

    DatabaseReference::DatabaseReference(const std::wstring &type, const std::wstring &id, std::vector<std::tuple<std::wstring, std::wstring>> &properties) {
        Type = type;
        Id = id;
        Properties = properties;
    }

    std::wstring DatabaseReference::getType() const {
        return privateType;
    }

    std::wstring DatabaseReference::getId() const {
        return privateId;
    }

    std::vector<std::tuple<std::wstring, std::wstring>> DatabaseReference::getProperties() const {
        return privateProperties;
    }

    bool DatabaseReference::Equals(std::any obj) {
        DatabaseReference *d = dynamic_cast<DatabaseReference*>(obj);
        return obj != nullptr && d->getType() == getType() && d->getId() == getId() && d->getProperties().OrderBy([&] (std::any x) {
            return x;
        }).SequenceEqual(getProperties().OrderBy([&] (std::any x) {
            return x;
        }));
    }

    int DatabaseReference::GetHashCode() {
        int hash = getType().GetHashCode() ^ getId().GetHashCode();
        for (auto property_Renamed : getProperties()) {
            hash = hash ^ property_Renamed.GetHashCode();
        }
        return hash;
    }
}
