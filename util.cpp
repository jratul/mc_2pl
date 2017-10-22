#include <stdlib.h>
#include <time.h>
#include "headers/util.h"

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
					//cout << i << " : " << randomNumbers[i] << " ? " << j << " : " << randomNumbers[j] << endl;
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

void printCommitLog(int commitId, int* idx, long valI, long valJ, long valK) {
	cout << commitId << " " << idx[0]+1 << " " << idx[1]+1 << " " << idx[2]+1 << " " << valI << " " << valJ << " " << valK << endl;
}