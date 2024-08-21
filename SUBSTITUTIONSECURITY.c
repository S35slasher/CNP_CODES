#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char data[], char encoded[]) {
    char seq[] = "qwertyuiopasdfghjklzxcvbnm1234567890";
    int len = strlen(data);

    for (int i = 0; i < len; i++) {
        if (isupper(data[i]))
            encoded[i] = toupper(seq[data[i] - 'A']);
        else if (islower(data[i]))
            encoded[i] = seq[data[i] - 'a'];
        else if (isdigit(data[i]))
            encoded[i] = seq[data[i] - '0' + 26];
        else
            encoded[i] = data[i];
    }
    encoded[len] = '\0';  // Null-terminate the encoded string
}

void decrypt(char data[], char decoded[]) {
    char seq[] = "qwertyuiopasdfghjklzxcvbnm1234567890";
    int len = strlen(data);

    for (int i = 0; i < len; i++) {
        int found = 0;
        for (int j = 0; j < 36; j++) {
            if (seq[j] == tolower(data[i])) {
                if (j < 26)
                    decoded[i] = isupper(data[i]) ? 'A' + j : 'a' + j;
                else
                    decoded[i] = '0' + (j - 26);
                found = 1;
                break;
            }
        }
        if (!found)
            decoded[i] = data[i];
    }
    decoded[len] = '\0';  // Null-terminate the decoded string
}

int main() {
    char data[100], encoded[100], decoded[100];
    
    // Input and Encryption
    printf("Enter data to encrypt: ");
    fgets(data, sizeof(data), stdin);
    data[strcspn(data, "\n")] = '\0';  // Remove the newline character

    encrypt(data, encoded);
    printf("Encoded string is: %s\n", encoded);

    // Decryption
    decrypt(encoded, decoded);
    printf("Decoded string is: %s\n", decoded);

    return 0;
}
