#include "lib/RFContext.h"
#include <unistd.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>

using namespace std;
const long SEED = 425;
const long RAND_A = 107;
const long RAND_B = 11;
const long RAND_M = 8388608; // 2^23


const int CHALLENGE_INTERVAL = 10000*3;

vector<int> codeCache;
const int CACHE_SIZE = 250;
int currentCode = 0;

/**
 * Linear Congruential Generator to generate random numbers
 */
long random(long s)
{
	return ((RAND_A * s)%RAND_M + RAND_B) % RAND_M;
}

/**
 * Setup the code cache by adding CACHE_SIZE codes to accepted set.
 */
void setupQueue(long rnd){
	codeCache.push_back(random(rnd));
	for(int i = 0; i < CACHE_SIZE; i++){
		codeCache.push_back(random(codeCache.back()));
	}
}

/**
 * Update codes that car is expecting by removing
 * from cache then shifting one more index to the right.
 * 
 * @param value code that was received
 */
void shiftCode(int value){
	int numShifted = 0;
	currentCode = codeCache.front();
	while (currentCode != value) {
		codeCache.erase(codeCache.begin());
		codeCache.push_back(random(codeCache.back()));
		currentCode = codeCache.front();
		numShifted++;
	}
	codeCache.erase(codeCache.begin());
	codeCache.push_back(random(codeCache.back()));
	currentCode = codeCache.front();
	codeCache.erase(codeCache.begin());
	codeCache.push_back(random(codeCache.back()));
	numShifted++;
	printf("cache shifted by %i codes\n", numShifted);
}

/**
 * Insertion point
 * 
 * @param argc number of CLI arguments
 * @param argv vector of CLI arguments
 */
int main(int argc, char *argv[]){
	RFContext ctx = RFContext();
	
	currentCode = random(SEED);
	setupQueue(currentCode);
	
	// Run forever
	unsigned long iterCount = 0;
	bool first = true;
	while(1){
		// Introduction
		if(first){
			printf("HELLO I AM CAR\nBASE CODE IS %i\n", currentCode);
			first = false;
		}
		if(iterCount % CHALLENGE_INTERVAL == 0){
			printf("Sending challenge message...%i\n", currentCode);
			ctx.send_code(currentCode);
		}
		// Receive incoming messages
		if (ctx.available()) {
			int value = ctx.getReceivedValue();
		
			if (value == 0) {
			  printf("ERR: Unknown encoding\n");
			}
			else {
				printf("Received %i\n", value);
				
				if(find(codeCache.begin(), codeCache.end(), value) != codeCache.end()){
					printf("Rolling code accepted (%i). Car is unlocked.\n", value);
					shiftCode(value);
					printf("New challenge message (%i).\n", currentCode);
				}
			}
			fflush(stdout);
	  	} 
		ctx.resetAvailable();
      usleep(100);	// Sleep for 0.0001 seconds
      iterCount++;
	}
	
	return 0;
}
