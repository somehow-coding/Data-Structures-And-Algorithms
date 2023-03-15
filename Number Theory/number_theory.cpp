#include <bits/stdc++.h>
using namespace std;

/**
 * **************************number theory************************
*/

//counting no of divisors of number n

//tc = sqrt(n)
void divisors1(int n) {
    int cnt = 0;
    for(int i=1; i<=sqrt(n); i++) {
        if(n%i) {
            //here factor one is i and other is n/i
            if((n/i)==i) cnt+=1;
            else cnt+=2;
        }
    }
}

/**
 * if we want to check for a number is prime or not we can check if it has
 * more than 2 divisors i.e after excluding the 1 and the number itself.
 * so to check a single number we have time complexity as O(sqrt(n)), so
 * for all the numbers from 1 to n the tc will close to n(sqrt(n)) but we can do better
 * 
 * Instead of going like that we can go for the multiples of the number 
 * for(i=1;i<=n;i++) 
 *   for(j=i;j<=n;j+=i)
 * 
 * In above approach we are iterating over the mulitples of number.
 * 
 * Tc = O(nlogn) on lesser side
*/

/**
 * sieve of eratosthenes.
 * TC = O(nlog(logn))
*/

void sieve(int n) {
    vector<int> prime(n + 1, 1);
    vector<int> primeF(n + 1);
    prime[1] = 0;
    for(int i = 2; i * i <= n; i++) {
        if(!prime[i]) continue;
        for(int j=i*i; j<=n; j+=i) {
            prime[j] = 0;
            primeF[j] = i;
        }
    }
    for (int i = 2; i <= n; i++) {
        if (prime[i]) primeF[i] = i;
    } 
    // all primes lessss than equal to n
    vector<int> primes;

    for (int i=2; i<=n;i++) {
        if (prime[i]) primes.push_back(i);
    }
}


/**
 * prime factorisation
 * number as multiplication of prime numbers.
*/

vector<int> factors(int n) {
    vector<int> primes;//all the primes which are less than equal to n
    vector<int> f;
    for(int p: primes) {
        if(p*p > n) {
            // checked for all primes below p now x can't be a product of
            // 2 unchecked primes since p^2 > x so x must be prime.
            if(n==1) break;
            f.push_back(n);
            break;
        }
        else {
            while((n%p)==0) {
                f.push_back(p);
                n /= p;
            }
        }
    }
}

/***
 * lcm(a,b) = (a*b)/gcd(a,b)
*/

/**
 * concept of multiplicative inverse
 * (a/b)%m = (a%m) * multiplicative_inverse(b%m)
 * 
 * for prime m
 * multiplicative_inverse of x for mod m = (x^(m-2))%m
 * x^-1 = x^(m-2)%m
 * 
*/

/**
 * modular division of two number given the mod is prime.
 * (a/b)%mod = (a*modular_inverse(b))%mod
*/

int modular_inverse(int n, int mod) {
    return power(n, mod-2, mod);
}

// (x ^ i) % mod
int power(int x, int i, int mod) {
    int ret = 1;
    while(i > 0) {
        if(i & 1) ret = (ret * x)%mod;
        i >>= 1;
        x = (x * x)%mod;
    }
    return ret;
}