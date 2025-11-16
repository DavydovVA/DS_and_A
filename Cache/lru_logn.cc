#include <iostream>
#include <cstdint>
//#include <set>
#include <map>
#include <unordered_map>
#include <string>

using TimePoint = uint64_t;

template<typename Key, typename Value>
class LRUCache {
private:
    size_t capacity_;
    TimePoint tp_ = 0;

    //std::set<std::pair<TimePoint, Key>> tp_to_key_;
    std::map<TimePoint, Key> tp_to_key_;
    std::unordered_map<Key, TimePoint> key_to_tp_;
    std::unordered_map<Key, Value> data_;

public:
    LRUCache(size_t capacity) : capacity_(capacity) {}

    void Add(const Key& key, const Value& value) {
        // Если ключ уже есть — удаляем перед обновлением
        auto it = data_.find(key);
        if (it != data_.end()) {
            Erase(key);
        }

        // Если кэш заполнен — удалить самый старый
        if (data_.size() >= capacity_) {
            auto oldest = tp_to_key_.begin();
            Erase(oldest->second);
        }

        // Добавление
        data_[key] = value;
        //tp_to_key_.emplace(tp_, key);
        tp_to_key_[tp_] = key;
        key_to_tp_[key] = tp_;

        ++tp_;
    }

    Value Get(const Key& key) {
        // Ищем один раз
        auto it = data_.find(key);
        if (it == data_.end()) {
            throw std::runtime_error("Key not found: " + key);
        }

        // Получаем старый tp
        auto old_tp = key_to_tp_[key];

        // Удаляем пару (tp, key) из map
        tp_to_key_.erase(old_tp);
        tp_to_key_[tp_] = key;
        //tp_to_key_.erase({old_tp, key});
        //tp_to_key_.emplace(tp_, key);

        // Обновляем tp
        key_to_tp_[key] = tp_;

        ++tp_;

        return it->second;
    }

    bool Erase(const Key& key) {
        auto it = data_.find(key);
        if (it == data_.end()) {
            return false;
        }

        auto old_tp = key_to_tp_[key];

        tp_to_key_.erase(old_tp);
        //tp_to_key_.erase({old_tp, key});
        key_to_tp_.erase(key);
        //key_to_tp_.erase(key);
        data_.erase(it);

        return true;
    }

    bool Contains(const Key& key) const {
        return data_.find(key) != data_.end();
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