#include "exercises.h"

int _maxCrossingSubsequenceDC(int A[], unsigned int n, int &i, int &j){
    int mid_point = (j-i)/2;

    int sumLeft = 0, maxSumLeft = 0, maxIndexLeft = mid_point;
    for(int k = mid_point; k >= i; --k){
        sumLeft += A[k];
        if(sumLeft > maxSumLeft){
            maxIndexLeft = k;
            maxSumLeft = sumLeft;
        }
    }

    int sumRight = 0, maxSumRight = 0, maxIndexRight = mid_point;
    for(int k = mid_point+1; k <= j; ++k){
        sumRight += A[k];
        if(sumRight > maxSumRight){
            maxIndexRight = k;
            maxSumRight = sumRight;
        }
    }
    i = maxIndexLeft; j = maxIndexRight;
    return maxSumRight + maxSumLeft;
}

int _maxSubsequenceDC(int A[], unsigned int n, int &i, int &j) {
    if(i==j){
        return A[i];
    }
    int mid_point = i + (j-i)/2;
    int il = i, jl = mid_point, ir = mid_point+1, jr = j, ic=i, jc=j;
    int res_left = _maxSubsequenceDC(A, n, il, jl);
    int res_right = _maxSubsequenceDC(A, n, ir, jr);
    int res_middle = _maxCrossingSubsequenceDC(A, n, ic, jc);

    if(res_left > res_right){
        if(res_left > res_middle){
            i = il; j = jl;
            return res_left;
        }
        else{
            i = ic; j = jc;
            return res_middle;
        }
    }
    else{
        if(res_right > res_middle){
            i = ir; j = jr;
            return res_right;
        }
        else{
            i = ic; j = jc;
            return res_middle;
        }
    }
    return 0;
}

int maxSubsequenceDC(int A[], unsigned int n, int &i, int &j) {
    i = 0; j = n-1;
    return _maxSubsequenceDC(A, n, i, j);
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP3_Ex2, testMaxSubsequence) {
    int A1[] = {1, 2, 3, 4};
    unsigned int n1 = 4;
    int i, j;
    EXPECT_EQ(maxSubsequenceDC(A1,n1,i,j), 10);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A2[] = {2, -1, -3, 4};
    unsigned int n2 = 4;
    EXPECT_EQ(maxSubsequenceDC(A2,n2,i,j), 4);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 3);

    int A3[] = {2, -1, 3, 4};
    unsigned int n3 = 4;
    EXPECT_EQ(maxSubsequenceDC(A3,n3,i,j), 8);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A4[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n4 = 9;
    EXPECT_EQ(maxSubsequenceDC(A4,n4,i,j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);
}