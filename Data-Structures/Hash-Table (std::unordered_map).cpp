#include <vector>
#include <memory>
#include <limits>
#include <functional>
#include <random>
#include <cassert>

template<typename T, typename V>
class HashTable
{
private:

    const unsigned int numberOfPrimes = 15;
    const std::vector<unsigned int> primes{359,149,71,2789,41,2003,79,83,977,97,1049,283,157,1013,661};

    unsigned int generatePrime()
    {
        static std::default_random_engine e{};
        static std::uniform_int_distribution<unsigned int> d{0, numberOfPrimes - 1};

        return primes[d(e)];
    }

    unsigned int prime;

    unsigned int MAX_SIZE = 1 << 5;
    unsigned int MASK = MAX_SIZE - 1;

    const int EMPTY = std::numeric_limits<T>::max();
    const int ERASED = std::numeric_limits<T>::max() - 1;

    std::hash<T> hasher;
    std::unique_ptr<std::pair<T,V>[]> table;

    unsigned int _size;

    void init(std::unique_ptr<std::pair<T,V>[]>& _table)
    {
        for (unsigned int i = 0; i < MAX_SIZE; ++i)
        {
            _table[i].first = EMPTY;
            _table[i].second = V();
        }
    }

    unsigned int check(const std::unique_ptr<std::pair<T,V>[]>& _table, const unsigned int p, const T& key) const
    {
        return _table[p].first != EMPTY && _table[p].first != key;
    }

    unsigned int supposedPosition(const std::unique_ptr<std::pair<T,V>[]>& _table, const T& key) const
    {
        unsigned int p = (prime * hasher(key)) & MASK;

        while (check(_table, p, key))
            p = (p + 1) & MASK;

        return p;
    }

    void insert(std::unique_ptr<std::pair<T,V>[]>& _table, const T& key, const V& value)
    {
        unsigned int p = supposedPosition(_table, key);

        if (_table[p].first != key)
        {
            _table[p].first = key;
            this->_size++;
        }

        _table[p].second = value;
    }

    void erase(std::unique_ptr<std::pair<T,V>[]>& _table, const T& key)
    {
        unsigned int p = supposedPosition(_table, key);

        if (_table[p].first == key)
        {
            _table[p].first = ERASED;
            _table[p].second = V();
        }
    }

    void rehash()
    {
        unsigned int __size = this->_size;
        this->_size = 0;

        MAX_SIZE *= 2;
        MASK = MAX_SIZE - 1;

        std::unique_ptr<std::pair<T,V>[]> _table(new std::pair<T,V>[MAX_SIZE]);
        init(_table);

        for (unsigned int i = 0; 2 * i < MAX_SIZE; ++i)
            if (this->table[i].first != ERASED && this->table[i].first != EMPTY)
                this->insert(_table, this->table[i].first, this->table[i].second);

        this->_size = __size;
        this->table = std::move(_table);
    }

public:

    HashTable() : prime(generatePrime()), hasher(), table(), _size(0)
    {
        this->table = std::make_unique<std::pair<T,V>[]>(MAX_SIZE);
        this->init(this->table);
    }

    HashTable(const HashTable &rhs) : prime(rhs.prime), hasher(rhs.hasher), table(), _size(0)
    {
        this->table = std::make_unique<std::pair<T,V>[]>(MAX_SIZE);
        this->init(this->table);

        for (unsigned int i = 0; i < rhs.MAX_SIZE; ++i)
            if (rhs.table[i].first != ERASED && rhs.table[i].first != EMPTY)
                this->insert(this->table, rhs.table[i].first, rhs.table[i].second);
    }

    void insert(const T& key, const V& value)
    {
        this->insert(this->table, key, value);

        if (2 * this->_size >= MAX_SIZE)
            rehash();
    }

    V& operator [] (const T& key)
    {
        unsigned int p = supposedPosition(this->table, key);

        if (this->table[p].first != key)
        {
            this->table[p].first = key;
            this->table[p].second = V();
            _size++;

            if (2 * this->_size >= MAX_SIZE)
                rehash();

            p = supposedPosition(this->table, key);
            assert(this->table[p].first == key);
        }

        return this->table[p].second;
    }

    void erase(const T& key)
    {
        this->erase(this->table, key);
    }

    bool find(const T& key) const
    {
        unsigned int p = supposedPosition(this->table, key);
        return this->table[p].first == key;
    }

    V count(const T& key) const
    {
        unsigned int p = supposedPosition(this->table, key);

        if (this->table[p].first == key)
            return this->table[p].second;
        else
            return V();
    }

    size_t size() const
    {
        return static_cast<size_t>(this->_size);
    }

    bool empty() const
    {
        return this->_size == 0;
    }

    size_t max_size() const
    {
        return static_cast<size_t>(this->MAX_SIZE);
    }
};

int main()
{
    return 0;
}
