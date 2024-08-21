#include <stdio.h>
#include <string.h>

#define DLE 16
#define STX 2
#define ETX 3

int main() {
    char ch;
    char arr[100] = {DLE, STX};
    int i = 2;

    printf("\nEnter the data stream (CTRL+B->STX, CTRL+C->ETX, CTRL+P->DLE):\n");

    while ((ch = getchar()) != '\n') {
        if (ch == DLE) {
            arr[i++] = DLE;  // Stuffing DLE if encountered in the data stream
        }
        arr[i++] = ch;  // Add the character to the array
    }

    arr[i++] = DLE;
    arr[i++] = ETX;

    printf("\nThe stuffed stream is:\n");
    for (int j = 0; j < i; j++) {
        if (arr[j] == DLE) {
            printf("DLE");
        } else if (arr[j] == STX) {
            printf("STX");
        } else if (arr[j] == ETX) {
            printf("ETX");
        } else {
            printf("%c", arr[j]);
        }
    }

    printf("\n\nThe de-stuffed data is:\n");
    for (int j = 2; j < i - 2; j++) {
        if (arr[j] == DLE && arr[j + 1] == DLE) {
            printf("DLE");
            j++;  // Skip the stuffed DLE
        } else if (arr[j] == STX) {
            printf("STX");
        } else if (arr[j] == ETX) {
            printf("ETX");
        } else {
            printf("%c", arr[j]);
        }
    }

    printf("\n");
    return 0;
}
