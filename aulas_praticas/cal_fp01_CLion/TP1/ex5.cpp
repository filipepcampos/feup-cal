// By: Gonçalo Leão

#include "exercises.h"

unsigned int sumArray(unsigned int a[], unsigned int n) {
    unsigned int sum = 0;
    for(unsigned int i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum;
}

bool isCanonical(unsigned int C[], unsigned int n) {
    unsigned int lower_bound = n > 2 ? C[2] : n-1;
    unsigned int upper_bound = n >= 2 ? C[n-2] + C[n-1] : n;

    auto *used_coins_bf = new unsigned int[n];
    auto *used_coins_greedy = new unsigned int[n];
    auto *stock = new unsigned int[n];
    for(int i = 0; i < n; ++i){
        stock[i] = (unsigned int) 1e9;
    }

    for(unsigned int i = lower_bound; i < upper_bound; ++i){
        if(changeMakingBF(C, stock, n, i, used_coins_bf) != changeMakingGreedy(C, stock, n, i, used_coins_greedy) ||
            sumArray(used_coins_bf, n) != sumArray(used_coins_greedy, n)){
            return false;
        }
    }
    return true;
}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP1_Ex5, canonicalTrue) {
    unsigned int C[] = {1,2,5};
    EXPECT_EQ(isCanonical(C,3), true);

    unsigned int C2[] = {1,2,5,10};
    EXPECT_EQ(isCanonical(C2,4), true);
}

TEST(TP1_Ex5, canonicalFalse) {
    unsigned int C[] = {1,4,5};
    EXPECT_EQ(isCanonical(C,3), false);
}