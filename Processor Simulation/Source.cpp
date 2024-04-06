/*
Author: Jacob Gehr
Date Created: 4.4.24
Date Modified: 4.4.24
Purpose: Processor Simulation
*/

#include <vector>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <queue>

using namespace std;

struct jobEntry {
    char jobType;
    int arrivalTime;
    int processingTime;
    int jobNum;
    // default constructor
    jobEntry() : jobType('\0'), arrivalTime(0), processingTime(0), jobNum(-1){}
    // parameterized constructor
    jobEntry(char jt, int at, int pt, int jn) : jobType(jt), arrivalTime(at),
    processingTime(pt), jobNum(jn) {}
};

struct processor {
    bool isBusy = false;
    jobEntry currentJob;
    int timeJobStarted = 0;
};

struct jobComparator {
    bool operator()(const jobEntry& a, const jobEntry& b) const {
        if (a.arrivalTime == b.arrivalTime) return a.jobType > b.jobType; // 'D' has the highest priority on equal arrivalTime
        return a.arrivalTime > b.arrivalTime;
    }
};

void simPriorityQueue(priority_queue<jobEntry, vector<jobEntry>, jobComparator>& queue, int numOfProcessors);

int main() {
    ifstream inputData("mergedData.txt");
    priority_queue<jobEntry, vector<jobEntry>, jobComparator> queue;

    char jobType;
    int arrivalTime, processingTime, numOfProcessors;
    int jobNum = 1;

    while (inputData >> jobType >> arrivalTime >> processingTime) {
        jobEntry newEntry(jobType, arrivalTime, processingTime, jobNum);
        queue.push(newEntry);    
        jobNum++;
    }

    numOfProcessors = 4;

    simPriorityQueue(queue, numOfProcessors);
}

void simPriorityQueue(priority_queue<jobEntry, vector<jobEntry>, jobComparator>& queue, int numOfProcessors) {
    int clock = 0;
    vector<processor> processors(numOfProcessors);

    while (clock < 550) {
        cout << "Time " << clock << ":\n";

        for (int i = 0; i < processors.size(); ++i) {
            auto& processor = processors[i];
            // Check if the processor is busy and if the current job has finished
            if (processor.isBusy && (clock - processor.timeJobStarted >= processor.currentJob.processingTime)) {
                cout << "Processor #" << (i + 1) << " finished task " << processor.currentJob.jobNum <<
                "(" << processor.currentJob.jobType << ")\n";
                processor.isBusy = false; // Mark the processor as idle after finishing the job
            }
            else if (processor.isBusy) {
                // If the processor is busy but the job hasn't finished yet, print the remaining time
                cout << "Processor #" << (i + 1) << " is busy with task " << processor.currentJob.jobNum <<
                "(" << processor.currentJob.jobType << "), " 
                << processor.currentJob.processingTime - (clock - processor.timeJobStarted) << " minutes remaining\n"; 
            }

            // Assign new jobs to idle processors, considering their arrival times
            if (!processor.isBusy && !queue.empty()) {
                auto nextJob = queue.top(); // Look at the next job without removing it
                if (nextJob.arrivalTime <= clock) { // Check if the job has arrived
                    queue.pop(); // Remove the job from the queue since it's starting
                    processor.currentJob = nextJob; // Assign the job to the processor
                    processor.isBusy = true;
                    processor.timeJobStarted = clock; // Record the start time of the job
                    cout << "Processor #" << (i + 1) << " started task " << 
                    nextJob.jobNum << "(" << nextJob.jobType << "),"
                    << " with " << nextJob.processingTime << " minutes of processing time\n";
                }
            }

            // Note: The condition for processor idle status is removed because it's implicitly covered
            // by the conditions above. If a processor is idle and there are no jobs in the queue,
            // there's no need for an additional message every clock tick.
        }

        clock++; // Advance the simulation time
    }
}