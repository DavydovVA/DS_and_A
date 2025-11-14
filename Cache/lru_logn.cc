#include <iostream>
#include <cstdint>

#include <map>
#include <unordered_map>
#include <string>

using TimePoint = uint64_t;

template<typename Key, typename Value>
class LRUCache {
private:
    size_t capacity_;
    TimePoint tp_;

    // std::set<std::pair<TimePoint, Key> tp_to_key_;
    std::map<TimePoint, Key> tp_to_key_;
    std::unordered_map<Key, TimePoint> key_to_tp_;
    std::unordered_map<Key, Value> data_;

public:
    LRUCache(size_t capacity): capacity_(capacity)
    {
    }

    void Add(const Key& key, const Value& value) {
        if (Contains(key)) {
            Erase(key);
        }

        if (data_.size() >= capacity_) {
            const auto& item_to_erase = tp_to_key_.begin();
            Erase(item_to_erase->second);
        }

        data_[key] = value;
        tp_to_key_[tp_] = key;
        key_to_tp_[key] = tp_++;
    }

    Value Get(const Key& key) {
        if (Contains(key) == false) {
            throw std::runtime_error(key);
        }

        // Update key's tp
        const auto old_tp = key_to_tp_.at(key);
        tp_to_key_.erase(old_tp);
        key_to_tp_.eraes(key);

        key_to_tp_[key] = tp_;
        tp_to_key_[tp_++] = key;

        return data_.at(key);
    }

    bool Erase(const Key& key) {
        if (Contains(key) == false) {
            return false;
        }

        const auto tp = key_to_tp_.at(key);
        tp_to_key_.erase(tp);
        key_to_tp_.erase(key);
        data_.erase(key);

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