#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;
const int MIN_PRIME = 2;
/**
 * @brief 获取maxValue之内的prime列表
 *
 * @param maxValue
 * @return vector<int>
 */
vector<int> GeneratePrimes(int maxValue);

vector<int> GeneratePrimes(int maxValue)
{
    vector<int> primeList;
    if (maxValue < 2)
    {
        return primeList;
    }
    // init isPrimeList
    vector<bool> isPrimeList(maxValue + 1, true);
    isPrimeList[0] = isPrimeList[1] = false;

    //
    int limit = sqrt(maxValue);
    for (int i = 2; i <= limit; i++)
    {
        if (isPrimeList[i])
        {
            for (int j = i + i; j <= maxValue; j += i)
            {
                isPrimeList[j] = false;
            }
        }
    }

    for (int i = 2; i <= maxValue; i++)
    {
        if (isPrimeList[i])
        {
            primeList.push_back(i);
        }
    }

    return primeList;
}

int *GeneratePrimeC(int maxValue)
{
    if (maxValue < 2)
    {
        return NULL;
    }

    int *isPrimeList = (int *)malloc((maxValue + 1) * sizeof(int));
    isPrimeList[0] = isPrimeList[1] = 0;
    for (int i = 2; i < maxValue + 1; i++)
    {
        isPrimeList[i] = 1;
    }

    int numLimit = sqrt(maxValue) + 1;
    for (int i = 2; i < numLimit; i++)
    {
        if (isPrimeList[i]) // if i is uncrossed ,cross its multiple
        {
            for (int j = i + i; j < maxValue + 1; j++)
            {
                isPrimeList[j] = 0;
            }
        }
    }

    int count = 0;
    for (int i = 2; i < maxValue + 1; i++)
    {
        if (isPrimeList[i])
            count++;
    }

    int *primeList = (int *)malloc(count * sizeof(int));
    for (int i = 2, j = 0; i < maxValue + 1; i++)
    {
        if (isPrimeList[i])
        {
            primeList[j++] = i;
        }
    }

    free(isPrimeList);
    return primeList;
}

class PrimeGenerator
{
public:
    vector<int> generatePrimes(int maxValue)
    {
        if (maxValue < MIN_PRIME)
        {
            return vector<int>();
        }
        else
        {
            UncrossIntergetsUpTo(maxValue);
            CrossOutMultiples();
            return GetPrimeListFromCrossOut();
        }
    }

private:
    void UncrossIntergetsUpTo(int maxValue)
    {
        for (int i = 0; i < MIN_PRIME; i++)
        {
            crossOut[i] = true;
        }
        for (int i = MIN_PRIME; i < maxValue + 1; i++)
        {
            crossOut[i] = false;
        }
    }
    void CrossOutMultiples()
    {
        int maxLimit = DetermineIterationLimit();
        for (int i = MIN_PRIME; i <= maxLimit; i++)
        {
            if (IsPrime(i))
            {
                CrossOutMultiplesOf(i);
            }
        }
    }
    int DetermineIterationLimit()
    {
        return sqrt(crossOut.size() - 1);
    }
    void CrossOutMultiplesOf(int prime)
    {
        for (int multi = 2 * prime; multi < crossOut.size(); multi += prime)
        {
            crossOut[multi] = true;
        }
    }
    bool IsPrime(int num)
    {
        return crossOut[num] == false;
    }
    vector<int> GetPrimeListFromCrossOut()
    {
        vector<int> primeList;
        for (auto i : crossOut)
        {
            if (IsPrime(i))
            {
                primeList.push_back(i);
            }
        }
        return primeList;
    }
    vector<bool> crossOut;
};

class PrimeGenerator2
{
public:
    vector<int> generator(int n)
    {

        vector<int> primeList;
        if (n <= 0)
        {
            return primeList;
        }
        else if (n == 1)
        {
            primeList.push_back(MIN_PRIME);
            multisOfPrimeFactors.push_back(MIN_PRIME);
            return primeList;
        }
        else
        {
            primeList.push_back(MIN_ODD_PRIME);
            multisOfPrimeFactors.push_back(SQUARE_OF_MIN_ODD_PRIME);
            int count = 2;
            int candiate = MIN_ODD_PRIME;
            int primeIndex = 1;
            int square = SQUARE_OF_MIN_ODD_PRIME;
            while (count < n)
            {
                candiate += 2;
                if (candiate == square)
                {
                    auto index = multisOfPrimeFactors.size();
                    multisOfPrimeFactors.push_back(square);
                    square = primeList[index] * primeList[index];
                }
                bool isPrime = true;
                for (int i = primeIndex; i < multisOfPrimeFactors.size(); i++)
                {
                    auto &multis = multisOfPrimeFactors[i];
                    while (multis < candiate)
                    {
                        multis += primeList[i] * 2;
                    }
                    if (multis == candiate)
                    {
                        isPrime = false;
                        break;
                    }
                }
                if (isPrime)
                {
                    count++;
                    primeList.push_back(candiate);
                }
            }
        }
        return primeList;
    }

private:
    static const int MIN_ODD_PRIME = 3;
    static const int SQUARE_OF_MIN_ODD_PRIME = 3;
    vector<int> multisOfPrimeFactors;
};