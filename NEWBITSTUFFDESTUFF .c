#include <stdio.h>
#include <string.h>

int main() {
    char ch, array[100] = "01111110", read_array[50];
    int count = 0, i = 8, k = 0;

    printf("Enter data to be transmitted: ");
    while ((ch = getchar()) != '\n') {
        array[i++] = ch;
        count = (ch == '1') ? count + 1 : 0;
        if (count == 5) {
            array[i++] = '0';
            count = 0;
        }
    }
    strcat(array, "01111110");

    printf("\nTransmitted bit stream (after stuffing): %s", array);

    count = 0;
    for (int j = 8; j < i - 1; j++) {
        read_array[k++] = array[j];
        count = (array[j] == '1') ? count + 1 : 0;
        if (count == 5 && array[j + 1] == '0') {
            j++;
            count = 0;
        }
    }
    read_array[k] = '\0';

    printf("\nDestuffed data at the receiver: %s\n", read_array);
    return 0;
}

