Instructions
------------

1. In test.cpp you will find some tests. Run them first
   of all, verify they're all passing.

2. Have a look at relevant files to get you started:
    port.h|c    - communicate with port through memory
     fsm.h|c    - the (not finished) Button FSM implementation

3. Ready to write some tests? The lamp is turned on/off
   by setting or clearing bit 7 of port1.
   
   The 'specification':

 - lamp should turn on when the user presses button
 - lamp should turn off when the doors open
 - any other bit than 7 should be left unmodified by the button FSM


Happy coding :)
