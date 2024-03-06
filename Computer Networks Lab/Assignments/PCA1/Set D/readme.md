#### Write a C program using UNIX File Socket where the client sends its MAC Address to the server and the server returns the reverse of the MAC Address to the client

#### 1. To display the MAC Address
`ip addr show | awk '/ether/ {print $2}'`
#### 2. To display the IPv4 Address
Get the network interface name from `ifconfig` </br>
`ip -4 addr show <network interface name> | awk '/inet/ {print $2}'`
#### 3. To display the IPv6 Address
`ip -6 addr show <network interface name> | awk '/inet6/ {print $2}'`

#### Getting the addresses in the C program
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

void main() 
{
    FILE *fp;
    char mac[MAX];
    char ipv4[MAX];
    char ipv6[MAX];

    // Execute shell commands and read their outputs
    fp=popen("ip addr show | awk '/ether/ {print $2}'", "r");
    fgets(mac, MAX, fp);
    pclose(fp);

    fp=popen("ip -4 addr show enp0s3 | awk '/inet/ {print $2}'", "r");
    fgets(ipv4, MAX, fp);
    pclose(fp);

    fp = popen("ip -6 addr show enp0s3 | awk '/inet6/ {print $2}'", "r");
    fgets(ipv6, MAX, fp);
    pclose(fp);

    // Remove trailing newline characters
    mac[strcspn(mac, "\n")] = 0;
    ipv4[strcspn(ipv4, "\n")] = 0;
    ipv6[strcspn(ipv6, "\n")] = 0;

    printf("MAC Address: %s\n", mac);
    printf("IPv4 Address: %s\n", ipv4);
    printf("IPv6 Address: %s\n", ipv6);
}

```
