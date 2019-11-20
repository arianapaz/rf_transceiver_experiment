#include "./sample/RFContext.h"
#include <unistd.h>

int RESPONSE_CODE = 420;
int CHALLENGE_CODE = 210;

unsigned long CHALLENGE_INTERVAL = 1;

// Car
int main(int argc, char *argv[]){
	if(argc < 2){
		printf("Gimme a mode yo (car or something else)\n");
		return -1;
	}
	char *mode = argv[1];
	bool isCar = (*mode == 'c');
	RFContext sender = RFContext();
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
				sender.send_code(CHALLENGE_CODE);
			}
			// Receive incoming messages
			if (sender.available()) {
				int value = sender.getReceivedValue();
			
				if (value == 0) {
				  printf("ERR: Unknown encoding\n");
				}
				else{
					if(value == RESPONSE_CODE) {
						printf("Expected response received (%i). Car is unlocked.\n", RESPONSE_CODE);
					}
					else{
						printf("Received %i\n", value);
					}
				}
				
				fflush(stdout);
		  }
		  
		sender.resetAvailable();
	  }
	  // Key
	  else{
		  if(first){
			printf("HELLO I AM KEY\n");
			first = false;
		  }
		  // If message there
		  if(sender.available()){
			int value = sender.getReceivedValue();
			
			if (value == 0) {
			  printf("ERR: Unknown encoding\n");
			}
			else{
				// Good code
				if(value == CHALLENGE_CODE){
					printf("Challenge message received (%i). Sending response...\n", value);
					usleep(1000);
					sender.resetAvailable();
					sender.send_code(RESPONSE_CODE);
				}
			}
			fflush(stdout);
		  }
		sender.resetAvailable();
	  }
      usleep(1000000);	// Sleep for 1 seconds
      iterCount++;
	}
}
