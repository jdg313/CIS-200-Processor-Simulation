#include "Customqueue.h"

using namespace std;

void CustomQueue::enqueue(jobEntry job) {
    jobQueue.push_back(job);
    currentSize++;
    totalTimeJobsInQueue += currentSize;
    if (currentSize > maxQueueSize) maxQueueSize = currentSize;
    switch (job.jobType) {
        case 'A':
            totalAJobsArrived++;
            break;
        case 'B':
            totalBJobsArrived++;
            break;
        case 'C':
            totalCJobsArrived++;
            break;
        case 'D':
            totalDJobsArrived++;
            break;
    }
    // update rear
    rear = currentSize - 1;
}

void CustomQueue::dequeue() {
    if (currentSize == 0) {
        cerr << "Error: Queue is empty." << endl;
        return;
    }
    jobEntry job = jobQueue[front];
    jobQueue.erase(jobQueue.begin());
    currentSize--;
    totalTimeJobsInQueue += currentSize;
    switch (job.jobType) {
        case 'A':
            totalAJobsCompleted++;
            break;
        case 'B':
            totalBJobsCompleted++;
            break;
        case 'C':
            totalCJobsCompleted++;
            break;
        case 'D':
            totalDJobsCompleted++;
            break;
    }
    totalJobsCompleted++;
    totalTimeProcessing += job.processingTime;
    // update front
    front = 0;
}

bool CustomQueue::isEmpty() {
    return currentSize == 0 ? true : false;
}

void CustomQueue::printQueue() {
    for (int i = 0; i < currentSize; i++) {
        cout << "Job Type " << jobQueue[i].jobType << "(#" << jobQueue[i].jobTypeNum << ")" << "\nJob # " 
        << jobQueue[i].jobNumOverall << "\nArrival Time: " 
        << jobQueue[i].arrivalTime << "\nProcessing Time: " << jobQueue[i].processingTime << endl;
    }
}

void CustomQueue::reportMetrics() {
    cout << "Average Queue Size: " << averageQueueSize << endl;
    cout << "Max Queue Size: " << maxQueueSize << endl;
    cout << "Average Time Jobs in Queue: " << averageTimeJobsInQueue << endl;
    cout << "Total A Jobs Arrived: " << totalAJobsArrived << endl;
    cout << "Total A Jobs Completed: " << totalAJobsCompleted << endl;
    cout << "Total B Jobs Arrived: " << totalBJobsArrived << endl;
    cout << "Total B Jobs Completed: " << totalBJobsCompleted << endl;
    cout << "Total C Jobs Arrived: " << totalCJobsArrived << endl;
    cout << "Total C Jobs Completed: " << totalCJobsCompleted << endl;
    cout << "Total D Jobs Arrived: " << totalDJobsArrived << endl;
    cout << "Total D Jobs Completed: " << totalDJobsCompleted << endl;
    cout << "Total Jobs Completed: " << totalJobsCompleted << endl;
    cout << "Total Time Processing: " << totalTimeProcessing << endl;
    cout << "Total Time Idle: " << totalTimeIdle << endl;
}