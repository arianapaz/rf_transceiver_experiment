#include "lib/RFContext.h"
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <cstdlib>
#include <cmath>

using namespace std;

const int BROADCAST_INTERVAL = 30000;

struct GCDReturn {
	int a, b, c;
};

GCDReturn xgcd(long x, long y) {
	vector<long> r, u, v, q;
	r.push_back(x);
	r.push_back(y);
	u.push_back(1);
	u.push_back(0);
	v.push_back(0);
	v.push_back(1);
	long n = 1;
	while (r[n] != 0) {
		n++;
		r.push_back(r[n - 2] % r[n - 1]);
		q.push_back((int)(r[n - 2] / r[n - 1]));
		u.push_back(u[n - 2] - q[n-2] * u[n - 1]);
		v.push_back(v[n - 2] - q[n-2] * v[n - 1]);
	}

	GCDReturn ret;
	ret.a = r[n - 1];
	ret.b = u[n - 1];
	ret.c = v[n - 1];
	return ret;
}

long gcd(long a, long b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

long nextRandom(long s, long a, long b, long m)
{
	return ((a * s) % m + b) % m;
}

/**
 * Agent that will retain any codes observed, then replay them in attempt to unlock car.
 */
int main(int argc, char *argv[]){
	RFContext ctx = RFContext();
	vector<long> codes, t, u;
	long a = 0, b = 0, m = 1;
	bool CRACKED = false;
	
	
	int iterCount = 0;
	/**
	 * sniffs 100 codes and crack their randomness
	 */
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
			if(codes.size() >= 10 && !CRACKED)
			{
				for (long i = 1; i < 7; i++)
				{
					t.push_back(codes[i] - codes[i-1]);
				}
				for (long i = 0; i < t.size() - 2; i++)
				{	
					long left = t[i + 2] * t[i];
					long right = t[i + 1] * t[i + 1];
					u.push_back(abs(left - right));
				}
				// result is m
				long result = u[0];
				long prev_result = u[0];
				for (long i = 1; i < u.size(); i++)
				{
					result = gcd(u[i], prev_result);
					prev_result = result;
				}
				m = result;
				// Find A
				GCDReturn modInv = xgcd(codes[1]-codes[0], result);
				long aInv = modInv.b % result;
				a = ((codes[2] - codes[1]) * aInv) % result;
				if (a < 0) {
					a += result;
				}
				// Find b
				b = (codes[1] - a * codes[0]) % result;
				while(b < 0){
					b += result;
				}
				printf("A:%d,B:%d,M:%d\n", a, b, result);
				CRACKED = true;
			}
			// If time to yell, do
			if(codes.size() > 0 && iterCount % BROADCAST_INTERVAL == 0){
				long nextValue = nextRandom(value, a, b, m);
				printf("Next code in the sequence will be: %ld \n", nextValue);
				ctx.send_code(value);
				printf("SENDING PREVIOUS CODE %i\n", value);
			}
			fflush(stdout);
		}
		
		usleep(100);
		iterCount++;
	}
	return 0;
}
