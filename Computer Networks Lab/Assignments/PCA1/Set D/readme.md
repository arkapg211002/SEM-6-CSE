#### 1. To display the MAC Address
`ip addr show | awk '/ether/ {print $2}'`
#### 2. To display the IPv4 Address
Get the network interface name from `ifconfig` </br>
`ip -4 addr show <network interface name> | awk '/inet/ {print $2}'`
#### 3. To display the IPv6 Address
`ip -6 addr show <network interface name> | awk '/inet6/ {print $2}'`
