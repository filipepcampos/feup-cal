#include "exercises.h"
#include <sstream>
#include <cstring>
#include <chrono>
#include <fstream>
#include <vector>

#define INF (int)1e9
#define MAX_SIZE 10000

std::string calcSum(int sequence[], unsigned long n) {
    int dp[MAX_SIZE] = {0};
    std::ostringstream ss;

    for(int m = 1; m <= n; ++m){
        int min_index = -1; int min_value = INF;
        for(int i = 0; i <= n - m; ++i){
            dp[i] += sequence[i+m-1];
            if(dp[i] < min_value){
                min_index = i;
                min_value = dp[i];
            }
        }
        ss << min_value << "," << min_index << ";";
    }

    return ss.str();
}

void testPerformanceCalcSum() {
    srand(NULL);
    int sequence[10000];
    std::ofstream out_file;
    out_file.open("./result.csv");

    for(unsigned int i = 500; i <= 100000; i += 500){
        long long int mean = 0;
        for(int j = 0; j < 100; ++j){
            for(int k = 0; k < i; ++k){
                sequence[k] = rand() % (10*i);
            }
            auto start = std::chrono::high_resolution_clock::now();
            calcSum(sequence, i);
            auto finish = std::chrono::high_resolution_clock::now();
            mean += std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
        }
        out_file << i << "," << mean/100 << "\n";
    }

    out_file.close();
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex4, CalcSumArrayTest) {
    int sequence[5] = {4,7,2,8,1};
    int sequence2[9] = {6,1,10,3,2,6,7,2,4};

    EXPECT_EQ("1,4;9,1;11,2;18,1;22,0;",calcSum(sequence, 5));
    EXPECT_EQ("1,1;5,3;11,3;16,1;20,3;24,3;31,1;35,1;41,0;",calcSum(sequence2, 9));
	
	//testPerformanceCalcSum();
}