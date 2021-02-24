#include "exercises.h"
#include <algorithm>

bool noOverlaps(const std::vector<Activity> &acts) {
    for(unsigned int i = 0; i < acts.size(); i++) {
        Activity A1 = acts.at(i);
        for(unsigned int j = i + 1; j < acts.size(); j++) {
            Activity A2 = acts.at(j);
            if(A1.overlaps(A2)) return false;
        }
    }
    return true;
}

bool Activity::operator==(const Activity &a2) const {
    return start == a2.start && finish == a2.finish;
}

bool Activity::overlaps(const Activity &a2) const {
    return (start < a2.finish) && (a2.start < finish);
}


std::vector<Activity> activityBacktracking(std::vector<Activity> placed, std::vector<Activity> available, int nAvailable) {
    if(nAvailable == 0){
        return placed;
    }
    int maxSize = placed.size();
    std::vector<Activity> maxVec = placed;
    for(const Activity &a : available){
        placed.push_back(a);
        if(noOverlaps(placed)){
            std::vector<Activity> result = activityBacktracking(placed,available,nAvailable-1);
            if(result.size() > maxSize){
                maxVec = result;
                maxSize = result.size();
            }
        }
        placed.pop_back();
    }
    return maxVec;
}

std::vector<Activity> activitySelectionBacktracking(std::vector<Activity> A) {
    return activityBacktracking(std::vector<Activity>(), A, A.size());
}

/// TESTS ///
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(TP2_Ex4, activityScheduling) {
    std::vector<Activity> A = {{10,20}, {30, 35}, {5, 15}, {10, 40}, {40, 50}};
    std::vector<Activity> V = activitySelectionBacktracking(A);
    EXPECT_EQ(V.size(), 3 );
    EXPECT_EQ(noOverlaps(V), true);
}