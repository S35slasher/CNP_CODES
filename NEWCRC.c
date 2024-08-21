#include <stdio.h>

#define DEGREE 16

int mod2add(int x, int y) {
    return x ^ y;  // XOR operation for mod-2 addition
}

int getnext(int *array, int pos) {
    while (pos < DEGREE * 2 && array[pos] == 0) {
        pos++;
    }
    return pos;
}

void calc_crc(int *result, int length) {
    int ccitt[DEGREE + 1] = {1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,1};  // Polynomial
    int pos = 0;

    while (pos <= length - DEGREE) {
        for (int i = 0; i <= DEGREE; i++) {
            result[pos + i] = mod2add(result[pos + i], ccitt[i]);
        }
        pos = getnext(result, pos);
    }
}

int main() {
    int array[50], result[50];
    int length = 0;
    char ch;

    // Input data stream
    printf("Enter the data (Message) stream: ");
    while ((ch = getchar()) != '\n' && length < 50 - DEGREE) {
        array[length++] = ch - '0';
    }

    // Append DEGREE number of zeros to the message
    for (int i = 0; i < DEGREE; i++) {
        array[length + i] = 0;
    }

    // Copy the array into the result array
    for (int i = 0; i < length + DEGREE; i++) {
        result[i] = array[i];
    }

    // CRC Calculation
    calc_crc(result, length + DEGREE);

    // Print the transmitted frame (message + CRC remainder)
    printf("The transmitted frame is: ");
    for (int i = 0; i < length; i++) {
        printf("%d", array[i]);  // Message
    }
    for (int i = length; i < length + DEGREE; i++) {
        printf("%d", result[i]);  // CRC remainder
    }

    // CRC Verification (Decoding)
    printf("\nEnter the stream for which CRC has to be checked: ");
    length = 0;
    while ((ch = getchar()) != '\n' && length < 50) {
        array[length++] = ch - '0';
    }

    // Copy the array into the result array for verification
    for (int i = 0; i < length; i++) {
        result[i] = array[i];
    }

    // CRC Calculation for verification
    calc_crc(result, length);

    // Print the calculated checksum
    printf("Calculated Checksum: ");
    for (int i = length - DEGREE; i < length; i++) {
        printf("%d", result[i]);
    }
    printf("\n");

    return 0;
}
