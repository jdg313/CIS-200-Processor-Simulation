#pragma once
#include <iostream>
#include <vector>

using namespace std;

struct jobEntry {
    char jobType;
    int jobNumOverall;
    int jobTypeNum;
    int arrivalTime;
    int processingTime;
    bool processed = false;
    jobEntry* next = nullptr;
    // default constructor
    jobEntry() : jobType('\0'), jobNumOverall(-1), jobTypeNum(-1), arrivalTime(0), processingTime(0) {}
    // parameterized constructor
    jobEntry(char jt, int jno, int jtn, int at, int pt) : jobType(jt), jobNumOverall(jno), 
    jobTypeNum(jtn), arrivalTime(at), processingTime(pt) {}
};

class CustomQueue {
    private:
        vector<jobEntry> jobQueue;
        int currentSize = 0;
        float averageQueueSize = 0;
        int maxQueueSize = 0;
        int totalTimeJobsInQueue = 0;
        float averageTimeJobsInQueue = 0;
        int totalAJobsArrived = 0;
        int totalAJobsCompleted = 0;
        int totalBJobsArrived = 0;
        int totalBJobsCompleted = 0;
        int totalCJobsArrived = 0;
        int totalCJobsCompleted = 0;
        int totalDJobsArrived = 0;
        int totalDJobsCompleted = 0;
        int totalJobsCompleted = 0;
        int totalTimeProcessing = 0;
        int totalTimeIdle = 0;

    public:
        CustomQueue();
        ~CustomQueue();
        
};