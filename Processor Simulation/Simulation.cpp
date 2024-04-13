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
    ofstream logFile("logFile.txt");
    CustomQueue mainQueue;
    CustomQueue interruptedQueue;
    int clock = 1;
    int jobIterator = 0;
    int i;
    char jobType;
    vector<Processor> processorList(2);

    while (clock <= 10000) {
        cout << "Tick: " << clock << endl;
        // Check if job has arrived
        for (i = jobIterator; i < jobList.size(); i++) {
            if (jobList[i].arrivalTime == clock) {
                mainQueue.enqueue(jobList[i]);
                cout << "Job #" << jobIterator + 1 << " has arrived\n";
                logFile << "Tick: " << clock << ": Arrival: Overall Job #" << jobIterator + 1 << ": Job Type " 
                << jobList[i].jobType << "(#" << jobList[i].jobTypeNum << "): Processing Time: " << jobList[i].processingTime << endl;
                jobIterator++;
                /* switch (jobList[i].jobType) {
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
                } */
            }
        }
        // Move any priority jobs to front of queue
        for (i = 0; i < mainQueue.currentSize; i++) {
            if (mainQueue.jobQueue[i].priority == 1) {
                jobEntry tempJob = mainQueue.jobQueue[i];
                mainQueue.jobQueue.erase(mainQueue.jobQueue.begin() + i);
                mainQueue.jobQueue.insert(mainQueue.jobQueue.begin(), tempJob);
            }
        }
        // Check if priority job is at front of queue and interrupt
        for (i = 0; i < processorList.size(); i++) {
            if (!processorList[i].isIdle && processorList[i].currentJob.priority < mainQueue.frontJob().priority) {
                // Interrupt job
                jobEntry interruptedJob = processorList[i].currentJob;
                interruptedJob.processingTime = processorList[i].timeRemaining;
                interruptedQueue.enqueue(interruptedJob);
                processorList[i].isIdle = true;
                cout << "Processor " << i + 1 << " was interrupted by Job Type " << mainQueue.frontJob().jobType << "(#" << mainQueue.frontJob().jobTypeNum << ")\n";
                logFile << "Tick: " << clock << ": Interrupted: Processor " << i + 1 << " was interrupted by Job "
                << mainQueue.frontJob().jobType << "(#" << mainQueue.frontJob().jobTypeNum << ") \n";
                // Assign new job to processor
                processorList[i].currentJob = mainQueue.frontJob();
                processorList[i].timeRemaining = processorList[i].currentJob.processingTime;
                processorList[i].isIdle = false;
                mainQueue.dequeue();
                cout << "Processor " << i + 1 << " started processing job " << processorList[i].currentJob.jobType << "(#" << processorList[i].currentJob.jobTypeNum << ") "
                << "Processing Time: " << processorList[i].timeRemaining << " ticks\n";
            }
        }

        // Check if processor is idle
        for (int i = 0; i < processorList.size(); i++) {
            if (processorList[i].isIdle && !mainQueue.isEmpty()) {
                if (!interruptedQueue.isEmpty()) {
                    // Assign interrupted job to processor
                    processorList[i].currentJob = interruptedQueue.frontJob();
                    processorList[i].timeRemaining = processorList[i].currentJob.processingTime;
                    processorList[i].isIdle = false;
                    interruptedQueue.dequeue();
                    cout << "Processor " << i + 1 << " resumed processing job " << processorList[i].currentJob.jobType << "(#" << processorList[i].currentJob.jobTypeNum << ") "
                    << "Processing Time Remaining: " << processorList[i].timeRemaining << " ticks\n";

                    logFile << "Tick: " << clock << ": Resumed: Processor " << i + 1 << " resumed processing Job " 
                    << processorList[i].currentJob.jobType << "(#" << processorList[i].currentJob.jobTypeNum << ") \n";
                }
                else {
                    // Assign new job to processor
                    processorList[i].currentJob = mainQueue.frontJob();
                    processorList[i].timeRemaining = processorList[i].currentJob.processingTime;
                    processorList[i].isIdle = false;
                    mainQueue.dequeue();
                    cout << "Processor " << i + 1 << " started processing job " << processorList[i].currentJob.jobType << "(#" << processorList[i].currentJob.jobTypeNum << ") "
                    << "Processing Time: " << processorList[i].timeRemaining << " ticks\n";

                    logFile << "Tick: " << clock << ": Started: Processor " << i + 1 << " started processing Job "
                    << processorList[i].currentJob.jobType << "(#" << processorList[i].currentJob.jobTypeNum << ") \n";
                }
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
                processorList[i].totalRunTime++;
            }
            else {
                processorList[i].totalIdleTime++;
            }
        }
        // Process jobs
        for (int i = 0; i < processorList.size(); i++) {
            if (!processorList[i].isIdle) {
                if (processorList[i].timeRemaining == 0) {
                    processorList[i].isIdle = true;
                    /* switch (processorList[i].currentJob.jobType) {
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
                    mainQueue.totalJobsCompleted++; */
                }
            }
        }
        


        interruptedQueue.totalTimeJobsInQueue += interruptedQueue.currentSize;
        interruptedQueue.queueSizeAtTick.push_back(interruptedQueue.currentSize);
        mainQueue.totalTimeJobsInQueue += mainQueue.currentSize;
        mainQueue.queueSizeAtTick.push_back(mainQueue.currentSize);
        cout << "Queue Size at Tick " << clock << ": " 
        << mainQueue.queueSizeAtTick[clock - 1] + interruptedQueue.queueSizeAtTick[clock - 1] << "\n\n";
        // log status statement
        logFile << "Tick: " << clock << ": Queue Size: " 
        << mainQueue.queueSizeAtTick[clock - 1] + interruptedQueue.queueSizeAtTick[clock - 1];
        for (int i = 0; i < processorList.size(); i++) {
            if (processorList[i].isIdle)
                logFile << ": Processor " << i + 1 << " Idle Time: " << processorList[i].totalIdleTime;
            else {
                logFile << ": Processor " << i + 1 << " Running Time: " << processorList[i].totalRunTime;
            }
        }
        logFile << endl;
        clock++;

        if (clock == 550) {
            cout << "Initial metrics report for " << processorList.size() << " processors\n";
            mainQueue.reportMetrics(clock, interruptedQueue, processorList);
            cout << "Continue Simulation? (y/n): ";
            char response;
            cin >> response;
            if (response == 'n') {
                logFile.close();
                return;
            }
        }
    }
    cout << "Final metrics report for " << processorList.size() << " processors\n";
    mainQueue.reportMetrics(clock, interruptedQueue, processorList);
    logFile.close();
    return;
}