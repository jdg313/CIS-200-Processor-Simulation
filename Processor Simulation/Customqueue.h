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
    int priority = 0;
    bool processed = false;
    // default constructor
    jobEntry() : jobType('\0'), jobNumOverall(-1), jobTypeNum(-1), arrivalTime(0), processingTime(0) {}
    // parameterized constructor
    jobEntry(char jt, int jno, int jtn, int at, int pt) : jobType(jt), jobNumOverall(jno), 
    jobTypeNum(jtn), arrivalTime(at), processingTime(pt) {}
};

struct Processor {
    int timeRemaining;
    bool isIdle = true;
    int totalRunTime = 0;
    int totalIdleTime = 0;
    jobEntry currentJob;
    // default constructor
    Processor() {}
    // parameterized constructor
    Processor(int tr) : timeRemaining(tr) {}
};

class CustomQueue {
    public:
        vector<jobEntry> jobQueue;
        vector<jobEntry> interruptedQueue;
        Processor processorList[4];

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

        int front = 0;
        int rear = 0;

        vector<int> queueSizeAtTick;

        CustomQueue() {};
        ~CustomQueue() {};
        void enqueue(jobEntry job);
        void dequeue();
        bool isEmpty();
        void printQueue();
        jobEntry frontJob() { return jobQueue[front]; }
        jobEntry rearJob() { return jobQueue[rear]; };
        void reportMetrics(const int clock, CustomQueue interruptedQueue, vector<Processor> processors);
};