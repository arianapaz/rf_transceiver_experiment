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
int currentChallengeMessage = 0, currentRollingCode = 0;

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
	currentChallengeMessage = random(rnd);
	codeCache.push_back(currentChallengeMessage);
	for(int i = 0; i < CACHE_SIZE; i++){
		codeCache.push_back(random(codeCache.back()));
	}
	codeCache.erase(codeCache.begin());
	currentRollingCode = codeCache.front();
}

/**
 * Update codes that car is expecting by removing
 * from cache then shifting one more index to the right.
 * 
 * @param value code that was received
 */
void shiftCode(int value){
	int numShifted = 0;
	currentChallengeMessage = codeCache.front();
	while (currentChallengeMessage != value) {
		codeCache.erase(codeCache.begin());
		codeCache.push_back(random(codeCache.back()));
		currentChallengeMessage = codeCache.front();
		numShifted++;
	}
	// Set next challenge message
	currentChallengeMessage = codeCache.front();
	codeCache.erase(codeCache.begin());
	codeCache.push_back(random(codeCache.back()));
	numShifted++;

	// Get next roll code
	currentRollingCode = codeCache.front();
	// Remove next roll code from cache
	codeCache.erase(codeCache.begin());
	codeCache.push_back(random(codeCache.back()));
	printf("cache shifted by %i codes.\n", numShifted);
}

/**
 * Insertion point
 * 
 * @param argc number of CLI arguments
 * @param argv vector of CLI arguments
 */
int main(int argc, char *argv[]){
	RFContext ctx = RFContext();
	
	long rnd = random(SEED);
	setupQueue(rnd);
	
	// Run forever
	unsigned long iterCount = 0;
	bool first = true;
	while(1){
	  // Introduction
	  if(first){
		printf("HELLO I AM KEY\nWaiting for code %i\n", currentChallengeMessage);
		first = false;
	  }
	  // If message there
	  if(ctx.available()){
		int value = ctx.getReceivedValue();
		
		if (value == 0) {
		  printf("ERR: Unknown encoding\n");
		}
		else{
			printf("Received message %i, expecting %i\n", value, currentChallengeMessage);
			// Received valid challenge message
			bool codeIsInCache = find(codeCache.begin(), codeCache.end(), value) != codeCache.end();
			if(value == currentChallengeMessage || codeIsInCache){
				printf("Challenge message received (%i). Current rolling code (%i)\n", value, currentRollingCode);
				if(codeIsInCache){
					printf("Updating cache...");
					shiftCode(value);
					printf("New challenge message: %i\n", currentChallengeMessage);
				}
				// Send current roll code
				printf("Sending rolling code (%i)...\n", currentRollingCode);
				ctx.send_code(currentRollingCode);
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
