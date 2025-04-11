#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define KEY_SIZE 32

void generate_symmetric_key(char* key) {
    srand(time(NULL));
    for (int i = 0; i < KEY_SIZE; i++) {
        key[i] = rand() % 256;
    }
}

void visualize(const char* label, const char* data, int len) {
    printf("%s: ", label);
    for (int i = 0; i < len; i++) {
        printf("%02X ", (unsigned char)data[i]);
    }
    printf("\n");
}

void xor_encrypt_decrypt(const char* input, char* output, const char* key, int len) {
    for (int i = 0; i < len; i++) {
        output[i] = input[i] ^ key[i % KEY_SIZE];
    }
}

int main() {
    char key[KEY_SIZE];
    char text[256];
    char encrypted[256];
    char decrypted[256];

    generate_symmetric_key(key);
    
    printf("Enter text to encrypt: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0;

    int len = strlen(text) + 1;
    xor_encrypt_decrypt(text, encrypted, key, len);
    xor_encrypt_decrypt(encrypted, decrypted, key, len);

    visualize("Original ", text, len);
    visualize("Key      ", key, KEY_SIZE);
    visualize("Encrypted", encrypted, len);
    visualize("Decrypted", decrypted, len);

    return 0;
}