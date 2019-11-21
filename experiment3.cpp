#include "sample/RFContext.h"
#include <unistd.h>
#include <stdlib.h>
#include <queue>

using namespace std;
const int SEED = 345091389;

const int CHALLENGE_INTERVAL = 10000;

queue<int> codeCache;
const int CACHE_SIZE = 250;
int currentCode = 0;

void setupQueue(){
	currentCode = rand();
	for(int i = 0; i < CACHE_SIZE; i++){
		codeCache.push(rand());
	}
}

void shiftCode(int value){
	currentCode = codeCache.front();
	while (currentCode != value) {
		codeCache.pop();
		codeCache.push(rand());
		currentCode = codeCache.front();
	}
	codeCache.pop();
	codeCache.push(rand());
}

int main(int argc, char *argv[]){
	if(argc < 2){
		printf("Gimme a mode yo (car or something else)\n");
		return -1;
	}
	char *mode = argv[1];
	bool isCar = (*mode == 'c');
	
	RFContext ctx = RFContext();
	
	srand(SEED);
	int rollin_code = rand();
	setupQueue();
	
	// Run forever
	unsigned long iterCount = 0;
	bool first = true;
	while(1){
		// Car
		if(isCar){
			if(first){
				printf("HELLO I AM CAR\n");
				first = false;
			}
			if(iterCount % CHALLENGE_INTERVAL == 0){
				ctx.send_code(rollin_code);
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
		  if(first){
			printf("HELLO I AM KEY\n");
			first = false;
		  }
		  // If message there
		  if(ctx.available()){
			int value = ctx.getReceivedValue();
			
			if (value == 0) {
			  printf("ERR: Unknown encoding\n");
			}
			else{
				// Good code
				if(value == rollin_code){
					printf("Challenge message received (%i). Sending response...\n", value);
					usleep(1000);
					ctx.resetAvailable();
					ctx.send_code(rand());
				}
			}
			fflush(stdout);
		  }
		ctx.resetAvailable();
	  }
      usleep(1000000);	// Sleep for 1 seconds
      iterCount++;
	}
	
	return 0;
}
