#### Create a multi-client TCP server. A client will send an IPv4 address (a.b.c.d) to the server. The server will verify whether the address is valid or not and send back 'YES' or 'NO' as a result to the client.

#### Using inet_pton to check Valid IPv4 and IPv6 Address
```c
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main() {
    char ip_address[INET6_ADDRSTRLEN];
    printf("Enter an IPv4 or IPv6 address: ");
    fgets(ip_address, sizeof(ip_address), stdin);
    
    // Remove trailing newline character
    if (ip_address[strlen(ip_address) - 1] == '\n')
        ip_address[strlen(ip_address) - 1] = '\0';
    
    struct in_addr ipv4;
    struct in6_addr ipv6;

    // Try parsing as IPv4 address
    if (inet_pton(AF_INET, ip_address, &ipv4) == 1) {
        printf("Valid IPv4 address: %s\n", ip_address);
    } 
    // Try parsing as IPv6 address
    else if (inet_pton(AF_INET6, ip_address, &ipv6) == 1) {
        printf("Valid IPv6 address: %s\n", ip_address);
    } 
    // Invalid address
    else {
        printf("Invalid IP address.\n");
    }
    
    return 0;
}

```
