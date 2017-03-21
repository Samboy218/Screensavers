#include <stdio.h>
#include <cmath>

double calcInside(int n);
double calcOutside(int n);

int main()
{
}

double getdigit(int n)
{
    int N = (10*n)/(3) + 1;
    int* array = new int[N];
    for (int i = 0; i < N; i++)
    {
        array[i] = 2;
    }

    for (int k = N; k > 0; k--)
    {
        double q = array[k] / (2*k + 1);
        array[k] %= (2*k + 1);
        array[k-1] += q * k;
    }

}

