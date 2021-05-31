#include <vector>
#include <string>
#include <utility>
#include <iostream>
#include <optional>

struct Hash {
    explicit Hash(int i) : value_(i) {}

    Hash operator++(int) { return (Hash) value_++; }

    Hash operator--(int) { return (Hash) value_--; }

    explicit operator int() const { return value_; }

    bool operator==(const Hash &other) const { return value_ == other.value_; }

private:
    int value_;

};

class HashTable {
public:

    explicit HashTable(int in) : size_(in) {
        for (int i = 0; i < size(); ++i) {
            data_.emplace_back(std::nullopt);
        }
    }

    void add(int key, const std::string &value) {
        Hash hash = make_hash(key);
        // todo there is an infinite loop here if whole array is full there is do while there
        while (data((Hash) ((int) hash % size())).has_value())
            hash++;
        data((Hash)((int)hash % size())) = std::make_pair(key, value);
    }

    void remove(int key) {
        Hash hash = make_hash(key);
        // todo there is an infinite loop here if whole array is full there is do while there
        while (data((Hash) ((int) hash % size()))->first != key)
            hash++;
        // fixme nie ma przesuwania wartosci
//    data(hash).reset();
        auto item = data(hash)->first;
        data(hash) = std::nullopt;
        rehash(make_hash(item));
    }

    void print() {
        for (int i = 0; i < size(); i++) {
            if (data((Hash) i).has_value())
                std::cout << i << " " << data((Hash) i)->first << " " << data((Hash) i)->second << std::endl;
        }
        std::cout << std::endl;
    }

private:

    [[nodiscard]]
    Hash make_hash(int key) const {
        return (Hash) (key % size());
    }

    [[nodiscard]]
    int size() const {
        return this->size_;
    }

    std::optional<std::pair<int, std::string>> &data(Hash hash) {
        return data_.at((int) hash);
    }

    void rehash(Hash hash) {
//    auto position = (int) hash + 1;
        auto position = (int) hash;
        while ((++position % size()) != (int) hash) {
            auto item = data((Hash) (position % size()));
            // jezeli jest pusty koncz
            if (!item)
                continue;
            // jezeli nie jest taki sam hash koncz
            if (!(make_hash(item->first) == hash))
                continue;
            // wyczysc mijesce w ktorym byl poprzednio
            data((Hash) (position % size())) = std::nullopt;
            // wprowadz najblizej poprawnego miejsca jak to mozliwe
            add(item->first, item->second);
        }

        position = (int) hash;
        while ((++position % size()) != (int) hash) {
            auto item = data((Hash) (position % size()));
            // jezeli jest pusty koncz
            if (!item)
                continue;
            // jezeli nie jest taki sam hash koncz
            if (make_hash(item->first) == hash)
                continue;
            // wyczysc mijesce w ktorym byl poprzednio
            data((Hash) (position % size())) = std::nullopt;
            // wprowadz najblizej poprawnego miejsca jak to mozliwe
            add(item->first, item->second);
        }

        /*
         * while (hash == make_hash((data(hash).value_or(std::make_pair(-1, ""))).first)) {
            hash--;
            rehash(hash);
            }
         */
    }

    int size_;
    std::vector<
            std::optional<
                    std::pair<int, std::string>>> data_;
};

enum class Action {
    Size,
    Add,
    Delete,
    Print,
    Stop,
    BadAction
};

Action parse(const std::string &text) {
    if (text == "size") {
        return Action::Size;
    }
    if (text == "add") {
        return Action::Add;
    }
    if (text == "delete") {
        return Action::Delete;
    }
    if (text == "print") {
        return Action::Print;
    }
    if (text == "stop") {
        return Action::Stop;
    }
    return Action::BadAction;
}

int main() {
    int no_cases;
    std::cin >> no_cases;
    HashTable *table;
    while (no_cases--) {
        bool end_of_testcase = false;
        while (!end_of_testcase) {
            std::string text;
            std::cin >> text;
            switch (parse(text)) {
                case Action::Size: {
                    int size;
                    std::cin >> size;
                    table = new HashTable(size);
                    break;
                }
                case Action::Add: {
                    int klucz;
                    std::string wartosc;
                    std::cin >> klucz;
                    std::cin >> wartosc;
                    table->add(klucz, wartosc);
                    break;
                }
                case Action::Delete: {
                    int klucz;
                    std::cin >> klucz;
                    table->remove(klucz);
                    break;
                }
                case Action::Print: {
                    table->print();
                    break;
                }
                case Action::Stop: {
                    delete table;
                    end_of_testcase = true;
                    break;
                }
                case Action::BadAction: {
                    std::cout << "Parsing error bad action" << std::endl;
                    exit(1);
                }
            }
        }

    }
}
