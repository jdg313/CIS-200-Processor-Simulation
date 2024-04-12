/*
Author: Jacob Gehr
Date Created: 4.4.24
Date Modified: 4.4.24
Purpose: Processor Simulation
*/

#include <vector>
#include <iostream>
#include <fstream>
#include "Customqueue.h"

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

struct Processor {
    int processorNum;
    int timeRemaining;
    bool isIdle = true;
    jobEntry* currentJob = nullptr;
    // default constructor
    Processor() : processorNum(-1), timeRemaining(0) {}
    // parameterized constructor
    Processor(int pn, int tr) : processorNum(pn), timeRemaining(tr) {}
};

vector<jobEntry> readInputFile();
void runSimulation(vector<jobEntry> jobList);

int main() {
    // Read in data into a vector of jobEntrys
    vector<jobEntry> jobList = readInputFile();
    // Check if head is null
    if (jobList.empty()) {
        cerr << "Error: No data to process." << endl;
        return 1;
    }
    // Add the linked list to a waiting queue
    runSimulation(jobList);

    return 0;
}


vector<jobEntry> readInputFile() {
    ifstream inputData("mergedData.txt"); // Open file
    vector<jobEntry> jobList;
    if (!inputData.is_open()) { // Check if file is open
        cerr << "Error: Unable to open file." << endl;
        return jobList;
    }
    char jobType;
    int jobNumOverall = 0, arrivalTime, processingTime;
    vector<int> jobTypeNum(4, 0); // 0 = A, 1 = B, 2 = C, 3 = D
    while (inputData >> jobType >> arrivalTime >> processingTime) {
        ++jobNumOverall; // Increment jobnum
        switch (jobType) { // Increment jobTypeNum based on jobType and push jobEntry to jobList
            case 'A':
                jobTypeNum[0]++;
                jobList.push_back(jobEntry(jobType, jobNumOverall, jobTypeNum[0], arrivalTime, processingTime));
                break;
            case 'B':
                jobTypeNum[1]++;
                jobList.push_back(jobEntry(jobType, jobNumOverall, jobTypeNum[1], arrivalTime, processingTime));
                break;
            case 'C':
                jobTypeNum[2]++;
                jobList.push_back(jobEntry(jobType, jobNumOverall, jobTypeNum[2], arrivalTime, processingTime));
                break;
            case 'D':
                jobTypeNum[3]++;
                jobList.push_back(jobEntry(jobType, jobNumOverall, jobTypeNum[3], arrivalTime, processingTime));
                break;
        }
    }
    inputData.close(); // Close file
    return jobList; // Create linked list and return head to main
}

void runSimulation(vector<jobEntry> jobList) {
    CustomQueue queue(jobList);
}