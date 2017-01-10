#include "../include/rsa.h"
#include <cmath>
#include <ctime>
#include <random>
#include <vector>
#include <QDebug>

long RSA::selectPrimeNum(const long random)
{
    std::vector<bool> arr(random, 0);
    long sq = sqrt(random) + 1;

    for (long i = 2; i < sq; ++i){
        if(arr[i] == 0){ //if arr[i] is not a non_prime number, that make it true
            for(long j = 2; j < random; ++j){
                if(j % i == 0 && j != i){
                    arr[j] = 1;  //make it true
                }
            }
        }
    }

    srand((unsigned)time(NULL));
#define MAX 100
    int i = rand () % MAX;  //select a rand number to choose a prime number
    long ret = 2;
    for(int j = 0; j < i; ++j){
        do{
            ret = (ret + 1) % random;   //look for a prime number
        }while(arr[ret] != 0);

        if(ret < 2)
            ret = 2;    //if ret is less than 2, make it 2
    }

    return ret;
}

void RSA::setPrimeP(long random)
{
    p = selectPrimeNum(random);
}

void RSA::setPrimeQ(long random)
{
    q = selectPrimeNum(random);
}

long RSA::gcdEX(long a, long b, long &x, long &y)
{
    if(b == 0){
        x = 1;
        y = 0;
        return a;
    }else{
        long ret = gcdEX(b, a % b, x, y);   //recursive compute the value
        long tmp = x;
        x = y;  //exchange
        y = tmp - a / b * y; //exchange
        return ret;
    }
}

long long easyPow(long base, int power)
{
    long long tmp = base;
    long long product = 1;

    while(power){
        if(power & 0x01)
            product *= tmp;

        tmp *= tmp;
        power /= 2;
    }
    return product;
}

//mode extend
long modeEx(long a, long n, long m)
{
    long ret = 1;

    while(n){
        if(n & 0x01){
            ret = ret * a % m;
        }

        a = a * a % m;
        n /= 2;
    }
    return ret;
}

void RSA::encrypt(long &clear)
{
    //clear = easyPow(clear, publicKey) % n;
    clear = modeEx(clear, publicKey, n);
}

void RSA::deEncrypt(long &cipher)
{
    //cipher = easyPow(cipher, privateKey) % n;
    cipher = modeEx(cipher, privateKey, n);
}

void RSA::construct(void)
{
    n = p * q; //set product n
    euler = (p - 1) * (q - 1); //set euler

    do{
        publicKey = selectPrimeNum(euler);  //select a prime number as public key
    }while(euler % publicKey == 0);

    //publicKey = 17;//because we can't use big integer, so make publicKey as small as possible

    long y;
    gcdEX(publicKey, euler, privateKey, y); //get private key

    privateKey = (privateKey < 0) ? (privateKey + euler) : privateKey;  //if private key is less than 0, that make it more than 0
}

RSA::RSA(long p, long q) :
    p(p), q(q)
{
    construct();
}

RSA::RSA(long random)
{
    /* set p and q */
    p = selectPrimeNum(random);
    do{
        q = selectPrimeNum(random);
    }while(q == p);

    construct();
}
