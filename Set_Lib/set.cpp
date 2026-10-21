#include "set.h"

void swap(Set& this_set, Set& other_set) {
    using std::swap;
    swap(this_set.bitfield_, other_set.bitfield_);
}

Set::Set(size_t max_power) :bitfield_(max_power) {}

Set::Set(const Set& set) :bitfield_(set.bitfield_) {}

Set::Set(Set&& other) {
    swap((*this), other);
}

Set::Set(std::initializer_list<int> list):bitfield_(std::max(list)) {
    for (auto elem : list) {
        insert(elem);
    }
}

Set::Set(const Bitfield& bitfield) :bitfield_(bitfield) {}

Set::operator Bitfield()const noexcept {
    return bitfield_;
}

void Set::insert(int value) {
    if (value <= 0 || value > max_power()) { throw std::out_of_range("out of range"); }
    return bitfield_.set_bit(value - 1);
}

void Set::erase(int value) {
    if (value <= 0 || value > max_power()) { throw std::out_of_range("out of range"); }
    return bitfield_.reset_bit(value - 1);
}

Set Set::operator+(int elem) {
    Set res((*this));
    res.insert(elem);
    return res;
}

Set Set::operator-(int elem) {
    Set res((*this));
    res.erase(elem);
    return res;
}

Set& Set::operator+=(int elem) {
    (*this).insert(elem);
    return (*this);
}

Set& Set::operator-=(int elem) {
    (*this).erase(elem);
    return (*this);
}

Set Set::operator+(const Set& other) {
    Set res((*this));
    res.bitfield_ |= other.bitfield_;
    return res;
}

Set Set::operator-(const Set& other) {
    Set res((*this));
    res.bitfield_ &= ~other.bitfield_;
    return res;
}

Set Set::operator*(const Set& other) {
    Set res((*this));
    res.bitfield_ &= other.bitfield_;
    return res;
}

Set& Set::operator+=(const Set& other) {
    (*this) = (*this) + other;
    return (*this);
}

Set& Set::operator-=(const Set& other) {
    (*this) = (*this) - other;
    return (*this);
}

Set& Set::operator*=(const Set& other) {
    (*this) = (*this) * other;
    return (*this);
}

Set Set::operator~() {
    Set res((*this));
    res.bitfield_ = ~res.bitfield_;
    return res;
}

bool Set::operator==(const Set& other) {
    return ((*this).bitfield_ == other.bitfield_);
}

bool Set::operator!=(const Set& other) {
    return !((*this) == other);
}

Set& Set::operator=(const Set& other) {
    Set res(other);
    swap((*this), res);
    return (*this);
}

Set& Set::operator=(Set&& other) {
    swap((*this), other);
    return (*this);
}

std::ostream& operator<<(std::ostream& out, const Set& set) {
    size_t size = set.max_power();
    out << "{";
    for (int i = 0;i < size;++i) {
        if (set.bitfield_.get_bit(i)) { out << i + 1 << " "; }
    }
    out << "}";
    return out;
}
