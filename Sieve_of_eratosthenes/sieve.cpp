#include "set.h"
#include <chrono>
#include <cmath>

Set sieve_alg(Set& set) {
    size_t size = set.max_power();
    set.erase(1);
    for (int i = 2;i < sqrt(size)+1;++i) {
        for (int j = i*i;j <= size;j += i) {
            set.erase(j);
        }
    }
    return set;
}


int main() {
    std::cout << "Start Algorithm";
    Set sieve(1'000'000);
    for (int i = 1;i < 1'000'000;++i) {
        sieve.insert(i);
    }
    Set ans = sieve_alg(sieve);
    //std::cout << "\n" << ans;
    return 0;
}