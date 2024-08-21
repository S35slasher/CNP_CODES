#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to compute gcd
int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Function to compute the modular inverse
int modInverse(int e, int phi) {
    int d = 1;
    while ((d * e) % phi != 1) {
        d++;
    }
    return d;
}

// Function to compute (base^exp) % mod
long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

// Function to generate RSA keys
void generateRSAKeys(int p, int q, int* n, int* e, int* d) {
    int phi;
    *n = p * q;
    phi = (p - 1) * (q - 1);

    // Find e
    *e = 2;
    while (*e < phi) {
        if (gcd(*e, phi) == 1) {
            break;
        }
        (*e)++;
    }

    // Find d
    *d = modInverse(*e, phi);
}

// Function to encrypt a message
long long encrypt(int message, int e, int n) {
    return modExp(message, e, n);
}

// Function to decrypt a message
long long decrypt(long long cipher, int d, int n) {
    return modExp(cipher, d, n);
}

int main() {
    int p, q, n, e, d;
    int message;
    long long cipher, decryptedMessage;

    // Example prime numbers (in practice, these should be large)
    p = 61;
    q = 53;

    // Generate RSA keys
    generateRSAKeys(p, q, &n, &e, &d);

    printf("Public Key: (e = %d, n = %d)\n", e, n);
    printf("Private Key: (d = %d, n = %d)\n", d, n);

    // Example message to encrypt
    message = 65; // ASCII code for 'A'

    // Encrypt the message
    cipher = encrypt(message, e, n);
    printf("Encrypted Message: %lld\n", cipher);

    // Decrypt the message
    decryptedMessage = decrypt(cipher, d, n);
    printf("Decrypted Message: %c\n", decryptedMessage);

    return 0;
}
