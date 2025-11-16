#include <iostream>
#include <cstdint>

#include <set>
#include <unordered_map>

using TimePoint = uint64_t;
using Frequency = uint32_t;


template<typename Key, typename Value>
class LFUCache {
private:
    size_t capacity_;
    TimePoint tp_;

    // modified from pair to tuple
    std::set<std::tuple<Frequency, TimePoint, Key>> queue_;
    std::unordered_map<Key, TimePoint> key_to_tp_;
    std::unordered_map<Key, Frequency> key_to_freq_; // NEW field
    std::unordered_map<Key, Value> data_;

private:
    void Touch(const Key& key) {
        queue_.erase({key_to_freq_.at(key), key_to_tp_.at(key), key});

        key_to_freq_[key]++;

        key_to_tp_[key] = tp_++;

        queue_.emplace(key_to_freq_.at(key), key_to_tp_.at(key), key);
    }

public:
    LFUCache(size_t capacity): capacity_(capacity)
    {
    }

    void Add(const Key& key, const Value& value) {
        auto iter = data_.find(key);

        if (iter != data_.end()) {
            data_[key] = value;
            Touch(key);
            return;
        }

        if (data_.size() >= capacity_) {
            const auto [freq, tp, key_to_erase] = *queue_.begin();
            Erase(key_to_erase);
        }

        key_to_freq_[key] = 1;
        key_to_tp_[key] = tp_++;
        queue_.emplace(key_to_freq_.at(key), key_to_tp_.at(key), key);
        data_[key] = value;
    }

    Value Get(const Key& key) {
        auto iter = data_.find(key);

        if (iter == data_.end()) {
            return Value{}; // TODO
        }

        Touch(key);

        return data_.at(key);
    }

    bool Erase(const Key& key) {
        if (Contains(key) == false) {
            return false;
        }

        queue_.erase({key_to_freq_.at(key), key_to_tp_.at(key), key});
        key_to_freq_.erase(key);
        key_to_tp_.erase(key);
        data_.erase(key);

        return true;
    }

    bool Contains(const Key& key) const {
        return data_.find(key) != data_.end();
    }

    void Print() const {
        for(const auto& [freq, tp, key]: queue_) {
            std::cout << "key: " << key << ", value: " << data_.at(key) << "\n";
        }
        std::cout << std::endl;
    }
};

int main() {
    LFUCache<std::string, std::string> cache{3};

    cache.Add("key1", "value1");
    cache.Add("key2", "value2");
    cache.Get("key1");
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