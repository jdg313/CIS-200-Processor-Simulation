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
    for (int i = 0; i < 20; ++i) {
        arrivalTimeA += 6 + (rand() % 3);
        processingTimeA = 1 + (rand() % 5);

        cout << jobTypeA << " " << arrivalTimeA << " " << processingTimeA << endl;
        outputFileA << jobTypeA << " " << arrivalTimeA << " " << processingTimeA << endl;
    }

    cout << endl;

    // Type B Generation (2000 Iterations)
    for (int i = 0; i < 20; ++i) {
        arrivalTimeB += 2 + (rand() % 7);
        processingTimeB = 3 + (rand() % 11);

        cout << jobTypeB << " " << arrivalTimeB << " " << processingTimeB << endl;
        outputFileB << jobTypeB << " " << arrivalTimeB << " " << processingTimeB << endl;
    }

    cout << endl;

    // Type C Generation (1100 Iterations)
    for (int i = 0; i < 20; ++i) {
        arrivalTimeC += 4 + (rand() % 15);
        processingTimeC = 6 + (rand() % 7);

        cout << jobTypeC << " " << arrivalTimeC << " " << processingTimeC << endl;
        outputFileC << jobTypeC << " " << arrivalTimeC << " " << processingTimeC << endl;
    }

    cout << endl;

    // Type D Generation (1500 Iterations)
    for (int i = 0; i < 20; ++i) {
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
    stringstream test; // Might need

    int lowestArrivalTimeOverall = 0;
    int lowestProcessingTimeOverall = 0;
    int lowestArrivalTimeA = 0, lowestArrivalTimeB = 0, lowestArrivalTimeC = 0, lowestArrivalTimeD = 0;
    int lowestProcessingTimeA = 0, lowestProcessingTimeB = 0, lowestProcessingTimeC = 0, lowestProcessingTimeD = 0;
    int indexPositionA = 0, indexPositionB = 0, indexPositionC = 0, indexPositionD = 0;
    char lowJobType = '\0';
    char tempJobType ='\0';

    int tempStoreArrive;
    int tempStoreProcess;
    char tempStoreType;

    // inputDataA >> tempJobType >> lowestArrivalTimeA >> lowestProcessingTimeA;
    // cout << tempJobType << lowestArrivalTimeA << lowestProcessingTimeA;

    for (int i = 0; i < 80; ++i) {
        // Start from position last recorded
        inputDataA.seekg(indexPositionA);
        inputDataB.seekg(indexPositionB);
        inputDataC.seekg(indexPositionC);
        inputDataD.seekg(indexPositionD);
        // Grab lowest
        inputDataA >> tempJobType >> lowestArrivalTimeA >> lowestProcessingTimeA;
        inputDataB >> tempJobType >> lowestArrivalTimeB >> lowestProcessingTimeB;
        inputDataC >> tempJobType >> lowestArrivalTimeC >> lowestProcessingTimeC;
        inputDataD >> tempJobType >> lowestArrivalTimeD >> lowestProcessingTimeD;

        if (lowestArrivalTimeA <= lowestArrivalTimeB) {
            if (lowestArrivalTimeA <= lowestArrivalTimeC) {
                if (lowestArrivalTimeA < lowestArrivalTimeD) {
                    lowestArrivalTimeOverall = lowestArrivalTimeA;
                    indexPositionA += 9;
                    mergedData << jobTypeA << " " << lowestArrivalTimeOverall << " " << lowestProcessingTimeA << endl;
                    continue;
                }
                else if (lowestArrivalTimeA == lowestArrivalTimeD) {
                    lowestArrivalTimeOverall = lowestArrivalTimeD;
                    indexPositionD += 9;
                    mergedData << jobTypeD << " " << lowestArrivalTimeOverall << " " << lowestProcessingTimeD << endl;
                    continue;
                }
            }
        }
        else if (lowestArrivalTimeA > lowestArrivalTimeB) {
            if (lowestArrivalTimeB <= lowestArrivalTimeC) {
                if (lowestArrivalTimeB < lowestArrivalTimeD) {
                    lowestArrivalTimeOverall = lowestArrivalTimeB;
                    indexPositionB += 9;
                    mergedData << jobTypeB << " " << lowestArrivalTimeOverall << " " << lowestProcessingTimeB << endl;
                    continue;
                }
                else if (lowestArrivalTimeB == lowestArrivalTimeD) {
                    lowestArrivalTimeOverall = lowestArrivalTimeD;
                    indexPositionD += 9;
                    mergedData << jobTypeD << " " << lowestArrivalTimeOverall << " " << lowestProcessingTimeD << endl;
                    continue;
                }
            }
        }
        else if (lowestArrivalTimeB > lowestArrivalTimeC) {
            if (lowestArrivalTimeC < lowestArrivalTimeD) {
                lowestArrivalTimeOverall = lowestArrivalTimeC;
                indexPositionC += 9;
                mergedData << jobTypeC << " " << lowestArrivalTimeOverall << " " << lowestProcessingTimeC << endl;
                continue;
            }
            else if (lowestArrivalTimeB == lowestArrivalTimeD) {
                    lowestArrivalTimeOverall = lowestArrivalTimeD;
                    indexPositionD += 9;
                    mergedData << jobTypeD << " " << lowestArrivalTimeOverall << " " << lowestProcessingTimeD << endl;
                    continue;
            }
        }
    }

    return 0;
}