// C program to generate random numbers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>

using namespace std;

// Driver program
int gcd(int a, int b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

int random(int s)
{
    return (420 * s + 123) % 429496;
}

int main()
{
    // This program will create different sequence of
    // random numbers on every program run

    // Use current time as seed for random generator
    vector<int> t;
    vector<int> u;
    vector<int> rnd;
    int temp = random(420);
    rnd.push_back(temp);
    for (int i = 1; i < 1000; i++)
    {
        temp = random(temp);
        rnd.push_back(temp);
        t.push_back(rnd[i] - rnd[i-1]);
    }

    for (int i = 0; i < t.size() - 4; i++)
    {
        int left = t[i+2]*t[i];
        int right = t[i+1] * t[i+1];
        u.push_back( abs (left -  right));
    }

    // result is m
    int result = u[0];
    int prev_result = 0;
    for (int i = 1; i < u.size(); i++)
    {
        prev_result = result;
        result = gcd(u[i], result);
    }
    printf(" %d \n", result);

    for (int i = 0; i < 50; i++)
    {
        printf(" %d \n", rnd[i]);
    }

    //random number Sn+1 = a*Sn + b mod m
    // a*s[0] + b mod result = s[1]
    // a*s[1] + b mod result = s[2]



    return 0;
}
