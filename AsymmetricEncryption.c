#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    int n;
    int e;
    int d;
} RSAKeyPair;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

RSAKeyPair generate_rsa_keys() {
    int p = 61;
    int q = 53;
    int n = p * q;
    int phi = (p-1) * (q-1);
    int e = 17;
    int d = 2753;

    RSAKeyPair keys = {n, e, d};
    return keys;
}

int mod_pow(int base, int exp, int mod) {
    int result = 1;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp = exp / 2;
    }
    return result;
}

void rsa_encrypt(const char* plaintext, int* ciphertext, RSAKeyPair pub, int len) {
    for (int i = 0; i < len; i++) {
        ciphertext[i] = mod_pow(plaintext[i], pub.e, pub.n);
    }
}

void rsa_decrypt(int* ciphertext, char* decrypted, RSAKeyPair priv, int len) {
    for (int i = 0; i < len; i++) {
        decrypted[i] = mod_pow(ciphertext[i], priv.d, priv.n);
    }
}

int main() {
    RSAKeyPair keys = generate_rsa_keys();
    char text[256];
    int encrypted[256];
    char decrypted[256];

    printf("Public Key (n=%d, e=%d)\n", keys.n, keys.e);
    printf("Private Key (n=%d, d=%d)\n", keys.n, keys.d);

    printf("Enter text to encrypt: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0;

    int len = strlen(text) + 1;

    rsa_encrypt(text, encrypted, keys, len);
    printf("Original bytes: ");
    for (int i = 0; i < len; i++) {
        printf("%d ", (unsigned char)text[i]);
    }
    printf("\n");

    printf("Encrypted bytes: ");
    for (int i = 0; i < len; i++) {
        printf("%d ", encrypted[i]);
    }
    printf("\n");
    rsa_decrypt(encrypted, decrypted, keys, len);

    printf("Original: %s\n", text);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}
