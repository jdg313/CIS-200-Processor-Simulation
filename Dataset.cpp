/*
Author: Jacob Gehr
Date Created: 4.2.24
Date Modified: 4.2.24
Purpose: Create dataset for simulation
*/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <limits>
#include <vector>
#include <fstream>
#include <ostream>
#include <sstream>

using namespace std;

struct jobEntry {
    char jobType;
    int arrivalTime;
    int processingTime;
};

int main () {
    srand(time(0)); // Randomize rand seed

    char jobTypeA = 'A';
    char jobTypeB = 'B';
    char jobTypeC = 'C';
    char jobTypeD = 'D'; // Priority job
    int arrivalTimeA = 0, arrivalTimeB = 0, arrivalTimeC = 0, arrivalTimeD = 0;
    int processingTimeA = 0, processingTimeB = 0, processingTimeC = 0, processingTimeD = 0;

    ofstream outputFileA("outputDataTypeA.txt");
    ofstream outputFileB("outputDataTypeB.txt");
    ofstream outputFileC("outputDataTypeC.txt");
    ofstream outputFileD("outputDataTypeD.txt");

    // Check if file opened
    if (!outputFileA || !outputFileB || !outputFileC || !outputFileD) {
        cout << "Output file failed to open\n";
        return 0;
    }

    // Type A Generation (2400 Iterations)
    for (int i = 0; i < 2400; ++i) {
        arrivalTimeA += 6 + (rand() % 3);
        processingTimeA = 1 + (rand() % 5);

        cout << jobTypeA << " " << arrivalTimeA << " " << processingTimeA << endl;
        outputFileA << jobTypeA << " " << arrivalTimeA << " " << processingTimeA << endl;
    }

    cout << endl;

    // Type B Generation (2000 Iterations)
    for (int i = 0; i < 2000; ++i) {
        arrivalTimeB += 2 + (rand() % 7);
        processingTimeB = 3 + (rand() % 11);

        cout << jobTypeB << " " << arrivalTimeB << " " << processingTimeB << endl;
        outputFileB << jobTypeB << " " << arrivalTimeB << " " << processingTimeB << endl;
    }

    cout << endl;

    // Type C Generation (1100 Iterations)
    for (int i = 0; i < 1100; ++i) {
        arrivalTimeC += 4 + (rand() % 15);
        processingTimeC = 6 + (rand() % 7);

        cout << jobTypeC << " " << arrivalTimeC << " " << processingTimeC << endl;
        outputFileC << jobTypeC << " " << arrivalTimeC << " " << processingTimeC << endl;
    }

    cout << endl;

    // Type D Generation (1500 Iterations)
    for (int i = 0; i < 1500; ++i) {
        arrivalTimeD += 2 + (rand() % 11);
        processingTimeD = 2 + (rand() % 21);

        cout << jobTypeD << " " << arrivalTimeD << " " << processingTimeD << endl;
        outputFileD << jobTypeD << " " << arrivalTimeD << " " << processingTimeD << endl;
    }

    // Merging Data Together
    ifstream inputDataA("outputDataTypeA.txt");
    ifstream inputDataB("outputDataTypeB.txt");
    ifstream inputDataC("outputDataTypeC.txt");
    ifstream inputDataD("outputDataTypeD.txt");
    ofstream mergedData("mergedData.txt");

    char tempCharStorage;
    int tempArrivalStorage;
    int tempProcessingStorage;

    jobEntry typeA[2400];
    jobEntry typeB[2000];
    jobEntry typeC[1100];
    jobEntry typeD[1500];

    // Type A Structs
    for (int i = 0; i < 2400; ++i) {
        inputDataA >> tempCharStorage >> tempArrivalStorage >> tempProcessingStorage;
        typeA[i].jobType = tempCharStorage;
        typeA[i].arrivalTime = tempArrivalStorage;
        typeA[i].processingTime = tempProcessingStorage;
    }
    // Type B Structs
    for (int i = 0; i < 2000; ++i) {
        inputDataB >> tempCharStorage >> tempArrivalStorage >> tempProcessingStorage;
        typeB[i].jobType = tempCharStorage;
        typeB[i].arrivalTime = tempArrivalStorage;
        typeB[i].processingTime = tempProcessingStorage;
    }
    // Type C Structs
    for (int i = 0; i < 1100; ++i) {
        inputDataC >> tempCharStorage >> tempArrivalStorage >> tempProcessingStorage;
        typeC[i].jobType = tempCharStorage;
        typeC[i].arrivalTime = tempArrivalStorage;
        typeC[i].processingTime = tempProcessingStorage;
    }
    // Type D Structs
    for (int i = 0; i < 1500; ++i) {
        inputDataD >> tempCharStorage >> tempArrivalStorage >> tempProcessingStorage;
        typeD[i].jobType = tempCharStorage;
        typeD[i].arrivalTime = tempArrivalStorage;
        typeD[i].processingTime = tempProcessingStorage;
    }

    int aIndex = 0;
    int bIndex = 0;
    int cIndex = 0;
    int dIndex = 0;

    while (aIndex < 2400 || bIndex < 2000 || cIndex < 1100 || dIndex < 1500) {
        int lowestTime = INT_MAX;
        char selectedType;
        int selectedArrival = 0, selectedProcessing = 0;
        int* selectedIndex = nullptr;

        // Check Type A
        if (aIndex < 2400 && typeA[aIndex].arrivalTime < lowestTime) {
            lowestTime = typeA[aIndex].arrivalTime;
            selectedType = typeA[aIndex].jobType;
            selectedArrival = typeA[aIndex].arrivalTime;
            selectedProcessing = typeA[aIndex].processingTime;
            selectedIndex = &aIndex;
        }

        // Check Type B
        if (bIndex < 2000 && typeB[bIndex].arrivalTime < lowestTime) {
            lowestTime = typeB[bIndex].arrivalTime;
            selectedType = typeB[bIndex].jobType;
            selectedArrival = typeB[bIndex].arrivalTime;
            selectedProcessing = typeB[bIndex].processingTime;
            selectedIndex = &bIndex;
        }

        // Check Type C
        if (cIndex < 1100 && typeC[cIndex].arrivalTime < lowestTime) {
            lowestTime = typeC[cIndex].arrivalTime;
            selectedType = typeC[cIndex].jobType;
            selectedArrival = typeC[cIndex].arrivalTime;
            selectedProcessing = typeC[cIndex].processingTime;
            selectedIndex = &cIndex;
        }

        // Check Type D
        if (dIndex < 1500 && typeD[dIndex].arrivalTime <= lowestTime) {
            lowestTime = typeD[dIndex].arrivalTime;
            selectedType = typeD[dIndex].jobType;
            selectedArrival = typeD[dIndex].arrivalTime;
            selectedProcessing = typeD[dIndex].processingTime;
            selectedIndex = &dIndex;
        }

        // Write the selected entry to mergedData
        if (selectedIndex != nullptr) {
            mergedData << selectedType << " " << selectedArrival << " " << selectedProcessing << "\n";
            (*selectedIndex)++; // Move to the next entry in the selected array
        }
    }
    return 0;
}