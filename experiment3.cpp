#include "lib/RFContext.h"
#include <unistd.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>

using namespace std;
const long SEED = 425;
const long RAND_A = 153;
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
	currentCode = random(rnd);
	for(int i = 0; i < CACHE_SIZE; i++){
		codeCache.push_back(random(currentCode));
	}
}

/**
 * Update codes that car is expecting by removing
 * received code from cache.
 * 
 * @param value code that was received
 */
void shiftCode(int value){
	int numShifted = 0;
	currentCode = codeCache.front();
	while (currentCode != value) {
		codeCache.erase(codeCache.begin());
		codeCache.push_back(random(codeCache.end()));
		currentCode = codeCache.front();
		numShifted++;
	}
	// Update one more time
	codeCache.erase(codeCache.begin());
	codeCache.push_back(random(currentCode));
	currentCode = codeCache.front();
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
	if(argc < 2){
		printf("Gimme a mode yo (car or something else)\n");
		return -1;
	}
	char *mode = argv[1];
	bool isCar = (*mode == 'c');
	
	RFContext ctx = RFContext();
	
	long rnd = random(SEED);
	setupQueue(rnd);
	
	// Run forever
	unsigned long iterCount = 0;
	bool first = true;
	while(1){
		// Car logic
		if(isCar){
			// Introduction
			if(first){
				printf("HELLO I AM CAR\nBASE CODE IS %i\n", currentCode);
				first = false;
			}
			if(iterCount % CHALLENGE_INTERVAL == 0){
				printf("Sending challenge message...\n");
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
						printf("New challenge code (%i).\n", currentCode);
					}
				}
				fflush(stdout);
		  	} 
			ctx.resetAvailable();
	  }
	  // Key
	  else{
		  // Introduction
		  if(first){
			printf("HELLO I AM KEY\nWaiting for code %i\n", currentCode);
			first = false;
		  }
		  // If message there
		  if(ctx.available()){
			int value = ctx.getReceivedValue();
			
			if (value == 0) {
			  printf("ERR: Unknown encoding\n");
			}
			else{
				printf("Received message %i\n", value);
				// Received valid challenge message
				bool codeIsInCache = find(codeCache.begin(), codeCache.end(), value) != codeCache.end();
				if(value == currentCode || codeIsInCache){
					printf("Challenge message received (%i). Updating cache...", value);
					if(codeIsInCache){
						shiftCode(value);
					}
					// Get next rolling code
					codeCache.erase(codeCache.begin());
					codeCache.push_back(random(codeCache.end()));
					currentCode = codeCache.front();
					ctx.send_code(currentCode);
					printf("Sending rolling code (%i)...\n", currentCode);
				}
			}
			fflush(stdout);
		  }
		  ctx.resetAvailable();
	  }
      usleep(100);	// Sleep for 0.0001 seconds
      iterCount++;
	}
	
	return 0;
}
