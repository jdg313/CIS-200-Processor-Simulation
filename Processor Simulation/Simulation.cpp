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

vector<jobEntry> readInputFile();
void runSimulation(vector<jobEntry> jobList);

int main() {
    // Read in data into a vector of jobEntrys
    vector<jobEntry> jobList = readInputFile();
    // Check if vector is empty
    if (jobList.empty()) {
        cerr << "Error: No data to process." << endl;
        return 1;
    }
    // Run simulation
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
    return jobList; // Create vector and return
}

void runSimulation(vector<jobEntry> jobList) {
    CustomQueue mainQueue;
    CustomQueue interruptedQueue;
    int clock = 0;
    int jobIterator = 0;
    int i;
    char jobType;
    vector<Processor> processorList(8);

    while (clock < 550) {
        cout << "Clock: " << clock << endl;
        // Check if job has arrived
        for (i = jobIterator; i < jobList.size(); i++) {
            if (jobList[i].arrivalTime == clock) {
                mainQueue.enqueue(jobList[i]);
                cout << "Job #" << jobIterator + 1 << " has arrived\n";
                jobIterator++;
                switch (jobList[i].jobType) {
                    case 'A':
                        mainQueue.totalAJobsArrived++;
                        break;
                    case 'B':
                        mainQueue.totalBJobsArrived++;
                        break;
                    case 'C':
                        mainQueue.totalCJobsArrived++;
                        break;
                    case 'D':
                        mainQueue.totalDJobsArrived++;
                        break;
                }
            }
        }
        // Check if processor is idle
        for (int i = 0; i < processorList.size(); i++) {
            if (processorList[i].isIdle && !mainQueue.isEmpty()) {
                processorList[i].currentJob = mainQueue.frontJob();
                processorList[i].timeRemaining = processorList[i].currentJob.processingTime;
                processorList[i].isIdle = false;
                mainQueue.dequeue();
                cout << "Processor " << i + 1 << " is processing job " << processorList[i].currentJob.jobType << "(#" << processorList[i].currentJob.jobTypeNum << ") "
                << "Processing Time Remaining: " << processorList[i].timeRemaining << " ticks\n";
            }
            else if (processorList[i].isIdle && mainQueue.isEmpty()) {
                // processor is idle
                mainQueue.totalTimeIdle++;
                cout << "Queue is empty. Processor " << i + 1 << " is idle.\n";
            }
            else {
                // processor is busy
                if (processorList[i].timeRemaining != 0) {
                    cout << "Processor " << i + 1 << " is processing Job Type " << processorList[i].currentJob.jobType << "(#" << processorList[i].currentJob.jobTypeNum << ") "
                    << "Processing Time Remaining: " << processorList[i].timeRemaining << " ticks\n";
                }
                else {
                    cout << "Processor " << i + 1 << " has completed processing Job Type " << processorList[i].currentJob.jobType << "(#" << processorList[i].currentJob.jobTypeNum << ")\n";
                }
            }
        }
        
        for (int i = 0; i < processorList.size(); i++) {
            if (!processorList[i].isIdle) {
                processorList[i].timeRemaining--;
            }
        }
        // Process jobs
        for (int i = 0; i < processorList.size(); i++) {
            if (!processorList[i].isIdle) {
                if (processorList[i].timeRemaining == 0) {
                    processorList[i].isIdle = true;
                    switch (processorList[i].currentJob.jobType) {
                        case 'A':
                            mainQueue.totalAJobsCompleted++;
                            break;
                        case 'B':
                            mainQueue.totalBJobsCompleted++;
                            break;
                        case 'C':
                            mainQueue.totalCJobsCompleted++;
                            break;
                        case 'D':
                            mainQueue.totalDJobsCompleted++;
                            break;
                    }
                    mainQueue.totalJobsCompleted++;
                }
            }
        }
        clock++;
    }
    mainQueue.reportMetrics();
}