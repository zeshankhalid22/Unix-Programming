The program implements a simple calculator that use **Client** to send Calculation Request to server, 
and use **Server** to send back the calculated response back to client.
we are using **Name Pipes (FIFO)** feature for shared memory.

Client.c
input $operation (+,-,*,/,%)    $num1    $num2
if $operation is invalid, server will response as -1.
press **q** for quit.
