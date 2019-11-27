#include "sample/RFContext.h"
#include <unistd.h>
#include <stdlib.h>
#include <queue>

using namespace std;
const long SEED = 425;
const long RAND_A = 153;
const long RAND_B = 11;
const long RAND_M = 1073741824;


const int CHALLENGE_INTERVAL = 10000*3;

queue<int> codeCache;
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
		codeCache.push(random(currentCode));
	}
}

/**
 * Update codes that car is expecting by removing
 * received code from cache.
 * 
 * @param value code that was received
 */
void shiftCode(int value){
	currentCode = codeCache.front();
	while (currentCode != value) {
		codeCache.pop();
		codeCache.push(random(currentCode));
		currentCode = codeCache.front();
	}
	codeCache.pop();
	codeCache.push(random(currentCode));
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
					
					queue <int> copyCache = codeCache;
					for(int i = 0; i < codeCache.size(); i++) {
						int code = copyCache.front();
						if(value == code) {
							printf("Rolling code accepted (%i). Car is unlocked.\n", code);
							shiftCode(code);
							printf("New challenge code (%i).\n", currentCode);
						}
						copyCache.pop();
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
				// Good code
				if(value == currentCode){
					usleep(1000);
					ctx.resetAvailable();
					long temp = random(currentCode);
					ctx.send_code(temp);
					printf("Challenge message received (%i). Sending response (%i)...\n", value, temp);
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
