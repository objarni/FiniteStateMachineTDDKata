Instructions
------------

1. In test.cpp you will find some tests
   to get you started. Run them first of all,
   verify they're all passing.

2. Have a look at relevant files to get you started:
    port.h|c    - communicate with port through memory
    fsm.h|c     - the (not finished) Button FSM implementation

3. Ready to write some tests? Here are some scenarios:

 - lamp should turn on when the user presses button
 - lamp should turn off when the doors open
 - port1 should not have any other bit than 7
   modified by the button FSM (several tests possibly)

Happy coding :)

IMPROVEMENT IDEAS
-----------------
- bugs in jamboard
- 0 based bit counting
- port0, port1 etc global pointers instead of set/get array API
   OR
- test list above tests, so array structure more clear
- context of ports, e.g. controlling elevator machine, doors etc.

