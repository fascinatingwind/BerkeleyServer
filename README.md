# Server Client example
Use BSD Sockets
For this case I'm using poll (not epoll)
Better practice use libevent.



## run Server 
Enter port in comand line

## run Client
Enter address, port protocol (tcp, udp) and message

## TODO
Connection.h - remove #inlcude <sys/socket.h>. add pimpl for struct sockaddr_storage 
EventManager.h - remove #include <sys/poll.h>. add pimpl for pollfd
Add test for cmake projects

## Improvement Hints
ClientParser.cpp - using StringSplitter class. I suppose better way is working with sstringstream for spliting string.
NetworkHelper.cpp - for createing UDP socket need add if statement for substring "udp". right now if input string not contain tcp we create udp.
For all sockets setup "info.ai_family = AF_UNSPEC" for suporting ipv6
For Connections need add test for Write method. I suppose here a problem when BSD socket can sent data partially.
