#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define KEY_LENGTH 8

// Function to generate the sequence based on the key
void generate_sequence(char *key, int *seq) {
    int len = strlen(key);
    for (int i = 0; i < len; i++) {
        int count = 0;
        for (int j = 0; j < len; j++) {
            if (key[i] > key[j]) {
                count++;
            }
        }
        seq[i] = count;
    }
}

// Function to encrypt the data using the transposition method
void encrypt(char *data, char *key, char cipher[][KEY_LENGTH]) {
    int len = strlen(key);
    int data_len = strlen(data);
    int rows = (data_len + len - 1) / len;  // Calculate the number of rows needed

    // Fill the cipher grid with the data
    for (int i = 0; i < data_len; i++) {
        cipher[i / len][i % len] = data[i];
    }

    // Fill the remaining cells with '.' if needed
    for (int i = data_len; i < rows * len; i++) {
        cipher[i / len][i % len] = '.';
    }

    int seq[KEY_LENGTH];
    generate_sequence(key, seq);

    // Print the encrypted data
    printf("Encrypted data:\n");
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            if (seq[j] == i) {
                for (int k = 0; k < rows; k++) {
                    printf("%c", cipher[k][j]);
                }
            }
        }
    }
    printf("\n");
}

// Function to decrypt the data using the transposition method
void decrypt(char *data, char *key, char cipher[][KEY_LENGTH]) {
    int len = strlen(key);
    int data_len = strlen(data);
    int rows = data_len / len;

    if (data_len % len != 0) {
        printf("Error: Invalid input length for decryption\n");
        return;
    }

    int seq[KEY_LENGTH];
    generate_sequence(key, seq);

    // Fill the cipher grid with the encrypted data
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            if (seq[j] == i) {
                for (int k = 0; k < rows; k++) {
                    cipher[k][j] = data[i * rows + k];
                }
            }
        }
    }

    // Print the decrypted data
    printf("Decrypted data:\n");
    for (int i = 0; i < data_len; i++) {
        printf("%c", cipher[i / len][i % len]);
    }
    printf("\n");
}

int main() {
    char data[100];
    char key[KEY_LENGTH + 1] = "MEGABUCK";  // Key is set to "MEGABUCK"
    char cipher[20][KEY_LENGTH];

    // Input the data to be encrypted
    printf("Enter data to encrypt: ");
    fgets(data, sizeof(data), stdin);
    data[strcspn(data, "\n")] = '\0';  // Remove newline character

    // Encrypt the data
    encrypt(data, key, cipher);

    // Input the data to be decrypted
    printf("Enter data to decrypt: ");
    fgets(data, sizeof(data), stdin);
    data[strcspn(data, "\n")] = '\0';  // Remove newline character

    // Decrypt the data
    decrypt(data, key, cipher);

    return 0;
}
