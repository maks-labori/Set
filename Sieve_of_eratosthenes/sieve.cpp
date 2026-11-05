#include "set.h"
#include <chrono>
#include <cmath>

int count = 0;

Set sieve_alg(Set& set) {
    size_t size = set.max_power();
    set.erase(1);
    for (int i = 2;i < sqrt(size)+1;++i) {
      if (!set.isMember(i)) {continue;}
        for (int j = i*i;j <= size;j += i) {
            set.erase(j);
            count++;
        }
    }
    return set;
}


int main() {
    std::cout << "Start Algorithm\n";
    Set sieve(100'000);
    for (int i = 1;i < 100'000;++i) {
        sieve.insert(i);
    }
    Set ans = sieve_alg(sieve);
    std::cout << count;
    //std::cout << "\n" << ans;
    return 0;
}