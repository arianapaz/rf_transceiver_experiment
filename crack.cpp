// C program to generate random numbers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

const long SEED = 425;
const long RAND_A = 153;
const long RAND_B = 11;
const long RAND_M = 1073741824;

long random(long s)
{
	return ((RAND_A * s)%RAND_M + RAND_B) % RAND_M;
}

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

int _main() {
	GCDReturn test = xgcd(595, 408);
	printf("(%d, %d, %d)\n", test.a, test.b, test.c);
	return 0;
}

int main()
{
	// This program will create different sequence of
	// random numbers on every program run

	// Use current time as seed for random generator
	vector<long> t;
	vector<long> u;
	vector<long> rnd;
	long temp = random(SEED);
	rnd.push_back(temp);
	for (long i = 1; i < 1000; i++)
	{
		temp = random(temp);
		rnd.push_back(temp);
		t.push_back(rnd[i] - rnd[i - 1]);
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
		printf("GCD (%d): %d \n", i, result);
		prev_result = result;
	}

	//random number Sn+1 = a*Sn + b mod m
	// a*s[0] + b mod result = s[1]
	// a*s[1] + b mod result = s[2]

	// Find A
	GCDReturn modInv = xgcd(rnd[1]-rnd[0], result);
	long aInv = modInv.b % result;

	long a = ((rnd[2] - rnd[1]) * aInv) % result;
	if (a < 0) {
		a += result;
	}
	// Find b
	long b = (rnd[1] - a * rnd[0]) % result;

	printf("A:%d,B:%d,M:%d\n", a, b, result);

	return 0;
}
