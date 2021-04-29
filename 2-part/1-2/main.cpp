//Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией. Хранимые строки непустые и состоят из строчных латинских букв.
//Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
//Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.
//Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки принадлежности данной строки множеству.
// 1_2. Для разрешения коллизий используйте двойное хеширование.

#include <string>
#include <iostream>
#include <vector>

using namespace std;

#define MULTIPLIER 79
#define MULTIPLIER1 97
#define DELETED "__DEL__"
#define NIL "__NIL__"
float FILL_FACTOR = 0.75;

struct DeleteChecker {
    bool Check(const string &value) {
        return value == DELETED;
    }
};

struct NillChecker {
    bool Check(const string &value) {
        return value == NIL;
    }
};

struct Counter {
    size_t Count(const string &value, const int &mult) {
        size_t count = 0;
        for (auto v: value) {
            count = count * mult + v;
        }
        return count;
    }
};

class HashTable {
public:
    HashTable(int capacity) : capacity(capacity), size(0), counter(Counter{}),
                              nillChecker(NillChecker{}), deleteChecker(DeleteChecker{}) {
        holder = vector<string>(capacity, NIL);
    };


    bool Get(const string &element) {
        int i = 0;
        auto exHash = 2 * counter.Count(element, MULTIPLIER1) + 1;
        auto mainHash = counter.Count(element, MULTIPLIER);
        auto pos = (mainHash + i * exHash) % capacity;

        while (!nillChecker.Check(holder[pos]) && i < capacity) {
            if (holder[pos] == element)
                return true;


            ++i;
            pos = (mainHash + i * exHash) % capacity;
        }

        return false;
    };

    bool Delete(const string &element) {
        int i = 0;
        auto exHash = 2 * counter.Count(element, MULTIPLIER1) + 1;
        auto mainHash = counter.Count(element, MULTIPLIER);
        auto pos = (mainHash + i * exHash) % capacity;

        while (!nillChecker.Check(holder[pos]) && i < capacity) {
            if (holder[pos] == element) {
                holder[pos] = DELETED;
                --size;
                return true;
            }

            ++i;
            pos = (mainHash + i * exHash) % capacity;
        }

        return false;
    };

    bool Add(const string &element) {
        if (float(size) >= float(capacity) * FILL_FACTOR)
            rehash();

        int i = 0;
        auto exHash = 2 * counter.Count(element, MULTIPLIER1) + 1;
        auto mainHash = counter.Count(element, MULTIPLIER);
        auto pos = (mainHash + i * exHash) % capacity;
        auto firstDeletedPos = -1;

        while (!nillChecker.Check(holder[pos]) && i < capacity) {
            if (holder[pos] == element)
                return false;

            if (firstDeletedPos == -1 && deleteChecker.Check(holder[pos]))
                firstDeletedPos = pos;

            ++i;
            pos = (mainHash + i * exHash) % capacity;
        }
        if(firstDeletedPos == -1 && i == capacity)
            return false;

        if (firstDeletedPos != -1)
            pos = firstDeletedPos;

        holder[pos] = element;
        size++;
        return true;
    };

private:
    void rehash() {
        capacity *= 2;
        auto newHolder = vector<string>(capacity, NIL);

        size_t added = 0;
        for (const auto &v: holder) {
            if (nillChecker.Check(v) || deleteChecker.Check(v))
                continue;

            int i = 0;
            auto exHash = 2 * counter.Count(v, MULTIPLIER1) + 1;
            auto mainHash = counter.Count(v, MULTIPLIER);
            auto pos = (mainHash + i * exHash) % capacity;

            while (!nillChecker.Check(newHolder[pos])) {
                ++i;
                pos = (mainHash + i * exHash) % capacity;
            }

            newHolder[pos] = v;
            added++;

            if (added >= size)
                break;
        }

        holder = move(newHolder);
    };

    NillChecker nillChecker;
    DeleteChecker deleteChecker;
    Counter counter;

    int size, capacity;
    vector<string> holder;
};

int main() {
    auto table = HashTable(8);
    char op;
    string key;

    while (cin >> op >> key) {
        switch (op) {
            case '?': {
                auto answr = table.Get(key) ? "OK" : "FAIL";
                cout << answr << endl;
                break;
            }
            case '+': {
                auto answr = table.Add(key) ? "OK" : "FAIL";
                cout << answr << endl;
                break;
            }

            case '-': {
                auto answr = table.Delete(key) ? "OK" : "FAIL";
                cout << answr << endl;
                break;
            }
        }
    }

    return 0;
}
