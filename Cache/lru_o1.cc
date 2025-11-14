#include <iostream>

#include <list>
#include <unordered_map>
#include <string>

template<typename Key, typename Value>
class LRUCache {
private:
    size_t capacity_;

    std::list<std::pair<Key, Value>> data_;
    std::unordered_map<Key, typename std::list<std::pair<Key, Value>>::iterator> cache_;

public:
    LRUCache(size_t capacity): capacity_(capacity)
    {
    }

    void Add(const Key& key, const Value& value) {
        auto iter = cache_.find(key);

        if (iter != cache_.end()) {
            // update value
            iter->second->second = value;
            data_.splice(data_.begin(), data_, iter->second);
            return;
        }

        if (data_.size() >= capacity_) {
            const auto& last_used = data_.back();
            cache_.erase(last_used.first);
            data_.pop_back();
        }

        data_.emplace_front(key, value);
        cache_[key] = data_.begin();
    }

    Value Get(const Key& key) {
        auto iter = cache_.find(key);

        if (iter == cache_.end()) {
            throw std::runtime_error(key);
        }

        data_.splice(data_.begin(), data_, iter->second);

        return iter->second->second;
    }

    bool Erase(const Key& key) {
        auto iter = cache_.find(key);

        if (iter == cache_.end()) {
            return false;
        }

        data_.erase(iter->second);
        //cache_erase(iter->first);
        cache_.erase(iter);

        return true;
    }

    bool Contains(const Key& key) const {
        return data_.find(key) != data_.end();
    }

    void Print() const {
        for (const auto& item: data_) {
            std::cout << "key: " << item.first << ", value: " << item.second << "\n";
        }
        std::cout << std::endl;
    }

};

int main() {
    LRUCache<std::string, std::string> cache{3};

    cache.Add("key1", "value1");
    cache.Add("key2", "value2");
    cache.Add("key3", "value3");
    cache.Print();
    cache.Add("key4", "value4");
    cache.Print();
    cache.Add("key3", "value3_1");
    cache.Print();
    cache.Add("key2", "value2_1");
    cache.Print();
    cache.Add("key5", "value5");
    cache.Print();


    return 1;
}