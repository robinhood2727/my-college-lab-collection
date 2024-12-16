run the server first then run client1 then run client 2
if any of the clients want to end the converstation then send "!EXIT"

The server is the middle man, the clients does not have the address of each other,
client 1 send message to server 
server forwards the message to client 2
client 2 sends reply to server
server forward the reply of client2 to client1
and the cycle repeats until one of the clients sends !EXIT
