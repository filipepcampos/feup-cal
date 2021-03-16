#include "exercises.h"
#include <cstring>
#include <fstream>
#include <chrono>

#define BF_MAX_SIZE 0
#define DC_MAX_SIZE 0
#define MAX_TEST_SIZE 1000000
#define N_SAMPLES 10

int maxSubsequenceDP(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    int *dp = new int[n];
    memset(dp, 0, n*sizeof(int));
    i = 0; j = 0;
    dp[0] = A[0];
    int max = dp[0];
    unsigned tmp_i = 0;

    for(unsigned int k = 1; k < n; ++k){
        dp[k] = std::max(dp[k-1]+A[k], A[k]);
        if(A[k] > dp[k-1] + A[k]){
            tmp_i = k;
        }
        if(dp[k] > max){
            max = dp[k];
            i = tmp_i;
            j = k;
        }
    }
    free(dp);
    return max;
}

int maxSubsequenceBF(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    int maxSum = 0;
    for(unsigned int x = 0; x < n; ++x){
        for(unsigned int y = 0; y < n; ++y){
            int subarray_sum = 0;
            for(unsigned int k = x; k < y; ++k){
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

int _maxCrossingSubsequenceDC(int A[], unsigned int n, unsigned int&i, unsigned int &j){
    int mid_point = (j-i)/2;

    int sumLeft = 0, maxSumLeft = 0, maxIndexLeft = mid_point;
    for(int k = mid_point; k >= i; --k){
        if(k < 0 || k > n){break;}
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

int _maxSubsequenceDC(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    if(i==j){
        return A[i];
    }
    unsigned mid_point = i + (j-i)/2;
    unsigned int il = i, jl = mid_point, ir = mid_point+1, jr = j, ic=i, jc=j;
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

int maxSubsequenceDC(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    i = 0; j = n-1;
    return _maxSubsequenceDC(A, n, i, j);
}

void testPerformanceMaxSubsequence() {
    srand(0);
    int sequence[MAX_TEST_SIZE];
    unsigned int a, b;
    std::ofstream out_file;
    out_file.open("./result.csv");

    for(unsigned int i = 500; i <= MAX_TEST_SIZE; i += 500){
        long long int mean_bf = 0;
        long long int mean_dc = 0;
        long long int mean_dp = 0;
        for(int j = 0; j < N_SAMPLES; ++j){
            for(unsigned int k = 0; k < i; ++k){
                sequence[k] = rand() % (5000) - 2500;
            }

            a = 0; b = i;
            auto start = std::chrono::high_resolution_clock::now();
            maxSubsequenceDP(sequence, i, a, b);
            auto finish = std::chrono::high_resolution_clock::now();
            mean_dp += std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();


            if(i <= DC_MAX_SIZE){
                a = 0; b = i;
                start = std::chrono::high_resolution_clock::now();
                maxSubsequenceDC(sequence, i, a, b);
                finish = std::chrono::high_resolution_clock::now();
                mean_dc += std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
            }

            if(i <= BF_MAX_SIZE){
                a = 0; b = i;
                start = std::chrono::high_resolution_clock::now();
                maxSubsequenceBF(sequence, i, a, b);
                finish = std::chrono::high_resolution_clock::now();
                mean_bf += std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
            }
        }

        if(i <= BF_MAX_SIZE)
            out_file << i << "," << mean_dp/N_SAMPLES << "," << mean_dc/N_SAMPLES << "," << mean_bf/N_SAMPLES << "\n";
        else if(i <= DC_MAX_SIZE)
            out_file << i << "," << mean_dp/N_SAMPLES << "," << mean_dc/N_SAMPLES << "," << "\n";
        else
            out_file << i << "," << mean_dp/N_SAMPLES << "," << "," << "\n";
    }

    out_file.close();
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex6, testMaxSubsequence) {
    int A1[] = {1, 2, 3, 4};
    unsigned int n1 = 4;
    unsigned int i, j;
    EXPECT_EQ(maxSubsequenceDP(A1,n1,i,j), 10);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A2[] = {2, -1, -3, 4};
    unsigned int n2 = 4;
    EXPECT_EQ(maxSubsequenceDP(A2,n2,i,j), 4);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 3);

    int A3[] = {2, -1, 3, 4};
    unsigned int n3 = 4;
    EXPECT_EQ(maxSubsequenceDP(A3,n3,i,j), 8);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A4[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n4 = 9;
    EXPECT_EQ(maxSubsequenceDP(A4,n4,i,j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);

    testPerformanceMaxSubsequence();
}