#include "datastore.hpp"

void DataStore::set(
    const std::string &key,
    const std::string &value)
{
    _store[key] = value;
}

std::optional<std::string> DataStore::get(
    const std::string &key)
{
    auto it = _store.find(key);

    if (it == _store.end())
    {
        return std::nullopt;
    }

    return it->second;
}

bool DataStore::del(
    const std::string &key)
{
    return _store.erase(key) > 0;
}