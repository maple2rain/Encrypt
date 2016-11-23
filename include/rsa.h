#ifndef RSA_H
#define RSA_H

#include "encrypt.h"

class RSA {
public:
    RSA(long p, long q);
    RSA(long random);
    ~RSA() {}

    long getPrimeP() { return p; }  //get prime numeber p
    long getPrimeQ() { return q; }  //get prime numeber q
    void setPrimeP(long random);    //set prime number p
    void setPrimeQ(long random);    //set prime number q
    long getPrivateKey() { return privateKey; } //get private key
    long getPublicKey() { return publicKey; }   //get public key
    long getN() { return n; }
    long getEuler() { return euler; }

    void encrypt(long &clear);      //to encrypt a clear text
    void deEncrypt(long &cipher);   //to dencrypt a cipher
    static long gcdEX(long a, long b, long &x, long &y);   //extend Euclid algorithm

private:
    long selectPrimeNum(const long random);    //get a prime number less than random
    void construct(void);

private:
    long p; //prime number p
    long q; //prime number q
    long n; //the product of p and q
    long euler; //the result of euler function about n
    long publicKey; //the public key
    long privateKey; //the private key
};

#endif // RSA_H
