# Socket Programming Tutorial in C

Part 1: https://www.youtube.com/watch?v=LtXEMwSG5-8
Part 2: https://www.youtube.com/watch?v=mStnzIEprH8

## Why sockets?

THe low level endpoint used to communicate across a network

Communications protocols like HTTP and FTP are implemented on top of sockets

A socket is a two-way endpoint. There is no distinction between server and client

A client socket :
1. is created with socket()
2. connects to a remote address via connect()
3. receives data via recv()

A server socket:
1. is created with socket()
2. binds to an IP and port via bind()
3. listens for incoming socket requests via listen()
4. accepts a connection via accept()
3. then sensds via send() and receives via recv()