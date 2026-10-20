#pragma once
#include <initializer_list>
#include <iostream>
class Bitfield {
private:
    unsigned int* data_;
    size_t max_power;
    unsigned int get_mask(size_t pos)const noexcept;
    size_t get_index(size_t pos)const;
public:
    Bitfield();
    Bitfield(size_t max_power);
    Bitfield(const Bitfield& other);
    Bitfield(std::initializer_list<unsigned int> list);
    ~Bitfield();

    inline size_t get_size()const noexcept {
        return (max_power / 32);
    }
    inline size_t get_power()const noexcept {
        return max_power;
    }
    void set_bit(size_t pos);
    void reset_bit(size_t pos);
    bool get_bit(size_t pos);
    
    bool operator==(const Bitfield& other)const noexcept;
    bool operator!=(const Bitfield& other)const noexcept;

    friend void swap(Bitfield& this_field ,Bitfield& other);
    
    Bitfield& operator=(const Bitfield& other)noexcept;
    Bitfield& operator=(Bitfield&& other)noexcept;

    Bitfield operator|(const Bitfield& other)const;
    Bitfield operator&(const Bitfield& other)const;
    Bitfield operator~()const;

    Bitfield& operator|=(const Bitfield& other);
    Bitfield& operator&=(const Bitfield& other);
};
