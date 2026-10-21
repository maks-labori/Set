#pragma once
#include "bitfield.h"

class Set {
private:
    Bitfield bitfield_;
public:
    Set(size_t max_power);
    Set(const Set& set);
    Set(Set&& other);
    Set(const Bitfield& bitfield);
    operator Bitfield()const noexcept;

    inline size_t max_power()const noexcept {
        return bitfield_.get_power(); 
    }

    friend void swap(Set& this_set,Set& other_set);

    void insert(int value);
    void erase(int value);

    Set operator+(int elem);
    Set operator-(int elem);

    Set& operator+=(int elem);
    Set& operator-=(int elem);

    Set operator+(const Set& other);
    Set operator-(const Set& other);
    Set operator*(const Set& other);

    Set& operator+=(const Set& other);
    Set& operator-=(const Set& other);
    Set& operator*=(const Set& other);

    Set operator~();

    bool operator==(const Set& other);
    bool operator!=(const Set& other);

    Set& operator=(const Set& other);
    Set& operator=(Set&& other);
};
