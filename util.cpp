#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string>
#include "headers/util.h"
using namespace std;

void logLine(string logData) {
	cout << logData << endl;
}

int* getRandomNumbers(int* randomNumbers, int maxRecordNum) { 

	for(int i=0;i<CHOOSING_THREAD_NUM;i++) {
		while(true) {
			randomNumbers[i] = rand()%maxRecordNum;

			bool isDuplicate = false;

			for(int j=0;j<i;j++) {
				if(randomNumbers[i] == randomNumbers[j]) {
					isDuplicate = true;
					break;
				}
			}

			if(!isDuplicate) {
				break;
			}
		}
	}

	return randomNumbers;
}

void printCommitLog(int commitId, int* idx, long long valI, long long valJ, long long valK, long threadNum) {
	cout << commitId << " " << idx[0]+1 << " " << idx[1]+1 << " " << idx[2]+1 << " " << valI << " " << valJ << " " << valK << endl;
	string fileName = "thread.txt";
	fileName.insert(6, to_string(threadNum + 1));
	ofstream output(fileName, ios::app);
	output << commitId << " " << idx[0]+1 << " " << idx[1]+1 << " " << idx[2]+1 << " " << valI << " " << valJ << " " << valK << endl;
	output.close();
}