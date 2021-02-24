// By: Gonçalo Leão

#include "exercises.h"
#include <vector>
#include <algorithm>

std::vector<std::vector<unsigned int>> makeCombinations(unsigned int C[], unsigned int n, unsigned int T, unsigned int currentSum, unsigned int lastCoin){
    std::vector<std::vector<unsigned int>> result;
    for(unsigned int i = 0; i < n; ++i){
        if(currentSum + C[i] < T and i >= lastCoin){
            std::vector<std::vector<unsigned int>> possibleCombos = makeCombinations(C,n,T,currentSum+C[i],i);
            for(auto & possibleCombo : possibleCombos){
                possibleCombo.push_back(i);
                result.push_back(possibleCombo);
            }
        }
        if(currentSum + C[i] == T){
            result.push_back(std::vector<unsigned int>{i});
        }
    }
    return result;
}

void clrArray(unsigned int arr[], unsigned int size){
    for(int i = 0; i < size; ++i){
        arr[i] = 0;
    }
}

bool changeMakingBF(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    std::vector<std::vector<unsigned int>> possibleCombinations = makeCombinations(C, n, T, 0, 0);
    std::sort(possibleCombinations.begin(), possibleCombinations.end(),[](std::vector<unsigned int> &v1, std::vector<unsigned int> &v2){
        return v1.size() < v2.size();
    });
    for(const auto &combo : possibleCombinations){
        bool valid = true; clrArray(usedCoins,n);
        for(auto i : combo) usedCoins[i]++;
        for(int i = 0; i < n; ++i){
            if(usedCoins[i] > Stock[i]){
                valid = false;
                break;
            }
        }
        if(valid){
            return true;
        }
    }
    return false;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP1_Ex3, smallScaleTest) {
    unsigned int C[] = {1,2};
    unsigned int Stock[] = {1,1};
    unsigned int n = 2;
    unsigned int usedCoins[2];

    EXPECT_EQ(changeMakingBF(C,Stock,n,3,usedCoins), true);
}

TEST(TP1_Ex3, hasBFChangeCanonical) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {1,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBF(C,Stock,n,13,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    unsigned int Stock2[] = {1,2,4,2};
    EXPECT_EQ(changeMakingBF(C,Stock2,n,38,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 3);
    EXPECT_EQ(usedCoins[3], 2);
}

TEST(TP1_Ex3, hasBFChangeNonCanonical) {
    unsigned int C[] = {1,4,5};
    unsigned int Stock[] = {2,2,1};
    unsigned int n = 3;
    unsigned int usedCoins[3];

    EXPECT_EQ(changeMakingBF(C,Stock,n,6,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingBF(C,Stock,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);
}

TEST(TP1_Ex3, hasNoBFChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {0,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingBF(C,Stock,n,18,usedCoins), false);
    EXPECT_EQ(changeMakingBF(C,Stock,n,1,usedCoins), false);
}