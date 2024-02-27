#### Decimal to Octal to Decimal
```c
#include <stdio.h>

int main() {
    int decimalNum, convertedDecimal;
    char octalStr[20]; // Assuming a reasonable size for the octal string

    // Input
    printf("Enter a decimal number: ");
    scanf("%d", &decimalNum);

    // Convert decimal to octal and store in octalStr
    sprintf(octalStr, "%o", decimalNum);

    // Print octal equivalent
    printf("Octal equivalent: %s\n", octalStr);

    // Convert octal back to decimal and print decimal equivalent
    sscanf(octalStr, "%o", &convertedDecimal);
    printf("Decimal equivalent (from octal): %d\n", convertedDecimal);

    return 0;
}

```

#### Decimal to Hexadecimal to Decimal
```c
#include <stdio.h>

int main() {
    int decimalNum, convertedDecimal;
    char hexStr[20]; // Assuming a reasonable size for the hexadecimal string

    // Input
    printf("Enter a decimal number: ");
    scanf("%d", &decimalNum);

    // Convert decimal to hexadecimal and store in hexStr
    sprintf(hexStr, "%x", decimalNum);

    // Print hexadecimal equivalent
    printf("Hexadecimal equivalent: %s\n", hexStr);

    // Convert hexadecimal back to decimal and print decimal equivalent
    sscanf(hexStr, "%x", &convertedDecimal);
    printf("Decimal equivalent (from hexadecimal): %d\n", convertedDecimal);

    return 0;
}

```
