# NetEye
Linux CLI Networking tool which scans any open ports that allow TCP traffic at a given IPv4 address.

## Installation
Option A: Pre-Compiled Binary(Recommended)
1. Download the compiled `port_scanner` binary from the **Releases** page.
2. Move the binary to a directory in your '$PATH' and ensure it has executable permissions:
```bash
chmod +x port_scanner
```


Option B Build From Source: 
1. Download the source code folder or clone this repository.
2. In the terminal, navigate to the project directory
3. Compile the binary using:
```bash
make port_scanner
```


Once these steps are completed, a `port_scanner` executable will appear in your directory.

## How it works
First, a network socket is opened which targets the user's specified IPv4 address. When the socket is successfully opened, it will be populated with the appropriate parameters to scan the given IPv4 address, and a connection to a single port will be attempted. The program watches for a change of state in the socket, which will be interpreted as a successful connection. Each connection attempt has a 500ms timeout to establish a TCP handshake before moving on. The connection process is repeated across up to 200 threads which each check a single port. A batching system is used here in order to better manage system resources and threads.

## Usage
Run the executable with 3 arguments: 
1. The target IPv4 address you would like to scan
2. The beginning port of the range you would like to scan
3. The ending port of the range you would like to scan

```bash
path/to/install/port_scanner <IPv4 Address> <Starting Port> <Ending Port>
```

## Example 
To scan ports 1–1000 on the standard IPv4 loopback address:
```bash
path/to/install/port_scanner 127.0.0.1 1 1000
```

