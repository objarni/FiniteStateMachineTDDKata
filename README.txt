Background
----------

You will continue developing the Elevator Button FSM we
started on in a previous learning hour; this time
the focus is the lamp control, rather than the states
and signals.

The Button FSM controls a lamp, which is  turned on/off
by setting or clearing bit 7 of port1.

There are 1 ports in total:
 Port0 - controls the main engine of the elevator
 Port1 - controls different lamps on the elevator
 Port2 - controls door machines
 Port3 - debug port for communicating with external devices


Instructions
------------

1. In test.cpp you will find some tests. Run them first
   of all, verify they're all passing.

2. Have a look at relevant files to get you started:
    port.h|c    - communicate with port through memory
     fsm.h|c    - the (not finished) Button FSM implementation

3. Ready to write some tests? The lamp is
   
   The 'specification':

 - lamp should turn on when the user presses button
 - lamp should turn off when the doors open
 - any other bit than 7 should be left unmodified by the button FSM


Happy coding :)
