// By: Gonçalo Leão

#include "exercises.h"

int maxSubsequence(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    int maxSum = 0;

    for(int x = 0; x < n; ++x){
        for(int y = 0; y < n; ++y){
            int subarray_sum = 0;
            for(int k = x; k < y; ++k){
                subarray_sum += A[k];
            }
            if(subarray_sum > maxSum){
                maxSum = subarray_sum;
                i = x;
                j = y-1;
            }
        }
    }

    return maxSum;
}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP1_Ex2, maxSubsequence) {
    int A[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n = 9;
    unsigned int i, j;
    EXPECT_EQ(maxSubsequence(A,n,i,j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);
}