#include <iostream>
#include <type_traits>
#include <cassert>
#include <vector>

template<unsigned int MOD>
class ModInteger
{
public:

    ModInteger() : data(0) {
    }

    ModInteger(const ModInteger &rhs) : data(rhs.data) {
    }

    explicit ModInteger(const std::string& str) : data(0) {

        assert(str.size() > 0);

        bool flag = false;
        std::string a = str;

        if (str[0] == '-')
        {
            flag = true;
            a.erase(a.begin());
        }

        for (const char &c : a)
            this->data = (this->data * 10 + (c - '0')) % MOD;

        if (flag && this->data > 0)
            this->data = MOD - this->data;
    }

    explicit ModInteger(const unsigned int &rhs) : data(rhs % MOD) {
    }

    explicit ModInteger(const unsigned long long &rhs) : data(rhs % MOD) {
    }

    ModInteger(const int &rhs) : data(0) {

        if (rhs < 0)
        {
            this->data = (-rhs) % MOD;
            this->data = (MOD -this->data) % MOD;
        }
        else
        {
            this->data = rhs % MOD;
        }
    }

    explicit ModInteger(const long long &rhs) : data(0) {

        if (rhs < 0)
        {
            this->data = (-rhs) % MOD;
            this->data = (MOD -this->data) % MOD;
        }
        else
        {
            this->data = rhs % MOD;
        }
    }

    ModInteger operator + (const ModInteger &rhs) const
    {
        return ModInteger(this->data + rhs.data);
    }

    ModInteger& operator += (const ModInteger &rhs)
    {
        *this = *this + rhs;
        return *this;
    }

    ModInteger operator - (const ModInteger &rhs) const
    {
        return ModInteger(static_cast<long long>(this->data) - rhs.data);
    }

    ModInteger& operator -= (const ModInteger &rhs)
    {
        *this = *this - rhs;
        return *this;
    }

    ModInteger operator * (const ModInteger &rhs) const
    {
        return ModInteger(static_cast<long long>(this->data) * rhs.data);
    }

    ModInteger& operator *= (const ModInteger &rhs)
    {
        *this = *this * rhs;
        return *this;
    }

    ModInteger operator / (const ModInteger &rhs) const
    {
        ///fails if MOD is not prime
        return ModInteger(*this * power(rhs, MOD - 2));
    }

    ModInteger& operator /= (const ModInteger &rhs)
    {
        *this = *this / rhs;
        return *this;
    }

    ModInteger inverseMod(void) const
    {
        return power(*this, MOD - 2);
    }

    bool operator == (const ModInteger &rhs) const
    {
        return this->data == rhs.data;
    }

    bool operator != (const ModInteger &rhs) const
    {
        return this->data != rhs.data;
    }

    template<class T>
    ModInteger operator ^ (T p) const
    {
        static_assert(std::is_integral<T>::value, "Integer required.");
        return power(*this, p);
    }

    unsigned int toInteger(void) const
    {
        return this->data;
    }

    friend std::ostream& operator << (std::ostream& stream, const ModInteger& rhs)
    {
        stream << rhs.data;
        return stream;
    }

    friend std::istream& operator >> (std::istream& stream, ModInteger& rhs)
    {
        std::string tmp;
        stream >> tmp;
        rhs = ModInteger(tmp);

        return stream;
    }

    template<class T>
    static ModInteger power(ModInteger a, T p)
    {
        ModInteger solution(1U);

        while (p > 0)
        {
            if (p & 1)
                solution *= a;

            a *= a;
            p >>= 1;
        }

        return solution;
    }

private:

    unsigned int data;
};

int main()
{
    return 0;
}
