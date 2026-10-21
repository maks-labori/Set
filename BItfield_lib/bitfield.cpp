#include "bitfield.h"

void swap(Bitfield& this_field, Bitfield& other) {
    using std::swap;
    swap(this_field.data_, other.data_);
    swap(this_field.max_power, other.max_power);
}

Bitfield::Bitfield():max_power(0),data_(nullptr) {}

Bitfield::Bitfield(size_t max_power) {
    (*this).max_power = ((max_power + 31) / 32) * 32;
    size_t size = get_size();
    data_ = new unsigned int[size];
    for (size_t i = 0;i < size;++i) {
        data_[i] = 0;
    }
}

Bitfield::Bitfield(const Bitfield& other) {
    max_power = other.max_power;
    size_t size = get_size();
    data_ = new unsigned int[size];
    for (size_t i = 0;i < size;++i) {
        data_[i] = other.data_[i];
    }
}

Bitfield::Bitfield(std::initializer_list<unsigned int> list) {
    (*this).max_power = list.size()*32;
    size_t size = get_size();
    data_ = new unsigned int[size];
    int i = 0;
    for (auto elem : list) {
        data_[i] = elem;
        i++;
    }
    max_power = size * 32;
}

Bitfield::~Bitfield() {
    max_power = 0;
    if (data_) {
        delete[] data_;
    }
    data_ = nullptr;
}

unsigned int Bitfield::get_mask(size_t pos)const noexcept { //передаем индекс с нуля
    return (1 << (31 - pos));
}

size_t Bitfield::get_index(size_t pos)const { // по индексу бита индекс ячейки
    if (pos >= max_power) { throw std::out_of_range("out of range"); }
    return pos / 32;
}

void Bitfield::set_bit(size_t pos) { //все по индексу бита,а не значению
    if (pos >= max_power) { throw std::out_of_range("out of range"); }
    size_t index = get_index(pos);
    unsigned int mask = get_mask(pos - (32 * index));
    data_[index] |= mask;
}

void Bitfield::reset_bit(size_t pos) {
    if (pos >= max_power) { throw std::out_of_range("out of range"); }
    size_t index = get_index(pos);
    unsigned int mask = get_mask(pos - (32 * index));
    data_[index] &= ~mask;
}

bool Bitfield::get_bit(size_t pos)const {
    if (pos >= max_power) { throw std::out_of_range("out of range"); }
    size_t index = get_index(pos);
    unsigned int mask = get_mask(pos - (32 * index));
    return data_[index] & mask;
}

bool Bitfield::operator==(const Bitfield& other)const noexcept {
    if ((*this).max_power != other.max_power) { return false; }
    size_t size = (*this).get_size();
    for (size_t i = 0;i < size;++i) {
        if ((*this).data_[i] != other.data_[i]) { return false; }
    }
    return true;
}

bool Bitfield::operator!=(const Bitfield& other)const noexcept {
    return !((*this) == other);
}

Bitfield Bitfield::operator~()const {
    Bitfield res((*this));
    size_t size = res.get_size();
    for (size_t i = 0;i < size;++i) {
        res.data_[i] = ~res.data_[i];
    }
    return res;
}

Bitfield& Bitfield::operator=(const Bitfield& other)noexcept {
    Bitfield res(other);
    swap((*this), res);
    return (*this);
}

Bitfield& Bitfield::operator=(Bitfield&& other)noexcept {
    swap((*this), other);
    return (*this);
}

Bitfield Bitfield::operator|(const Bitfield& other)const {
    if ((*this).get_power() != other.get_power()) { throw std::logic_error("diferent dimension"); }
    Bitfield res(other.max_power);
    size_t size = res.get_size();
    for (size_t i = 0;i < size;++i) {
        res.data_[i] = (*this).data_[i] | other.data_[i];
    }
    return res;
}

Bitfield Bitfield::operator&(const Bitfield& other)const {
    if ((*this).get_power() != other.get_power()) { throw std::logic_error("diferent dimension"); }
    Bitfield res(other.max_power);
    size_t size = res.get_size();
    for (size_t i = 0;i < size;++i) {
        res.data_[i] = (*this).data_[i] & other.data_[i];
    }
    return res;
}

Bitfield& Bitfield::operator|=(const Bitfield& other) {
    (*this) = (*this) | other;
    return (*this);
}

Bitfield& Bitfield::operator&=(const Bitfield& other) {
    (*this) = (*this) & other;
    return (*this);
}