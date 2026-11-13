# NetEye
Linux CLI Networking tool which scans any open ports that allow TCP traffic at a given IPv4 address.

***How it works***
First, a network socket is opened which targets the user's specified IPv4 address. When the socket is successfully opened, it will be populated with the appropriate parameters to scan the given IPv4 address, and a connection to a single port will be attempted. The program watches for a change of state in the socket, which will be interpreted as a successful connection. Each connection attempt has a 500ms timeout to establish a TCP handshake before moving on. The connection process is repeated across up to 200 virtual threads which each check a single port. A batching system is used here in order to better manage system resources and threads.

***Usage***
You (the user) will provide 3 arguments to this application. 
1: The target IPv4 address you would like to scan
2: The beginning port of the range you would like to scan
3: The ending port of the range you would like to scan

path/to/install/port_scanner <IPv4 Address> <Starting Port #> <Ending Port #>

For example: If i wanted to scan ports 1-1000 on the standard IPv4 loop-back address I would enter something like...
path/to/install/port_scanner 127.0.0.1 1 1000
