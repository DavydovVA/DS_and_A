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
        auto it = cache_.find(key);

        if (it != cache_.end()) {
            // обновляем значение
            it->second->second = value;
            // перемещаем в начало (теперь самый недавно использованный)
            data_.splice(data_.begin(), data_, it->second);
            return;
        }

        // если нужно вытолкнуть LRU
        if (data_.size() >= capacity_) {
            auto& back = data_.back();
            cache_.erase(back.first);
            data_.pop_back();
        }

        // вставляем новый элемент
        data_.emplace_front(key, value);
        cache_[key] = data_.begin();
    }

    Value Get(const Key& key) {
        auto it = cache_.find(key);

        if (it == cache_.end()) {
            if constexpr (std::is_convertible_v<Key, std::string>) {
                throw std::runtime_error("Key not found: " + key);
            } else {
                throw std::runtime_error("Key not found");
            }
        }

        // перемещаем в начало
        data_.splice(data_.begin(), data_, it->second);

        return it->second->second;
    }

    bool Erase(const Key& key) {
        auto it = cache_.find(key);

        if (it == cache_.end()) {
            return false;
        }

        data_.erase(it->second);
        cache_.erase(it);

        return true;
    }

    bool Contains(const Key& key) const {
        return cache_.find(key) != cache_.end();
    }

    void Print() const {
        for (const auto& item : data_) {
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