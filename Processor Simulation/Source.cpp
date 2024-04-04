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
    jobEntry* next;
    // default constructor
    jobEntry() : jobType('\0'), arrivalTime(0), processingTime(0), next(nullptr) {}
    // parameterized constructor
    jobEntry(char jt, int at, int pt, jobEntry* ptr) : jobType(jt), arrivalTime(at),
    processingTime(pt), next(ptr) {}
};

struct jobComparator {
    bool operator()(const jobEntry& a, const jobEntry& b) const {
        // Priority logic: earlier arrivalTime or higher priority for same arrivalTime
        if (a.arrivalTime == b.arrivalTime) return a.jobType < b.jobType; // Assuming 'D' > 'A', 'B', 'C'
        return a.arrivalTime > b.arrivalTime;
    }
};

int main() {
    int clock = 0;
    ifstream inputData("mergedData.txt");

    // Create a linked list of all jobs from input data
    jobEntry* head = nullptr;
    jobEntry* tail = nullptr;
    jobEntry* temp = nullptr;

    char jobType;
    int arrivalTime, processingTime;

    while (inputData >> jobType >> arrivalTime >> processingTime) {
        jobEntry* newEntry = new jobEntry(jobType, arrivalTime, processingTime, nullptr);

        if (head == nullptr) {
            head = newEntry;
            temp = newEntry;
        }
        else {
            temp->next = newEntry;
            temp = newEntry;
        }
    }
    tail = temp;
    temp = nullptr;
    delete temp;

    jobEntry* current = head;
    while (current != nullptr) {
        cout << "Type: " << current->jobType << endl;
        cout << "Arrival Time: " << current->arrivalTime << endl;
        cout << "Processing Time: " << current->processingTime << endl;

        current = current->next;
    }    

    priority_queue<jobEntry*, vector<jobEntry*>, jobComparator> queue;

    while (clock < 100) {
        if (queue.empty()) {
            
        }
    }
    
    // Delete and free memory once done
    current = head;
    while (current != nullptr) {
        jobEntry* toDelete = current;
        current = current->next;
        delete toDelete;
    }
}