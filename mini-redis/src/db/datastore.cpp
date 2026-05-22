#include "datastore.hpp"
#include <mutex>

void DataStore::set(
    const std::string &key,
    const std::string &value)
{
    std::lock_guard<std::mutex> lock(_mutex);

    _store[key] = value;
}

std::optional<std::string> DataStore::get(
    const std::string &key)
{
    std::lock_guard<std::mutex> lock(_mutex);
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
    std::lock_guard<std::mutex> lock(_mutex);
    return _store.erase(key) > 0;
}