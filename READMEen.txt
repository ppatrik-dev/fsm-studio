Project ICP 2024/2025 – Moore Machine Simulator

Authors:

    Patrik Prochazka, xprochp00
    Miroslav Bašista, xbasism00
    Filip Ficka, xfickaf00

Program Description:

After launching, the program allows the user to create automata through a graphical interface, with the ability to add states and transitions.
Each state can be assigned a unique functionality, and transitions can be configured with custom transition conditions using the information panel on the right side of the application.
Each automaton can be assigned a name, description, inputs, outputs, and variables that are used within the automaton.
Transition conditions are written in JavaScript-style syntax, and the following operations are supported:

=   -> assignment
==  -> equality
!=  -> inequality
>=  -> greater than or equal
<=  -> less than or equal
>   -> greater than
<   -> less than
&&  -> logical AND
||  -> logical OR

For special timed transitions, the moore object is used, which contains the method timer. This method accepts the desired wait time. After the specified time elapses, the automaton proceeds to the next state.
Each transition condition should return a boolean value true or false.
In addition to creation, automata can be exported to .json files, and previously exported automata can also be reloaded.
To run and simulate the automaton, simply press the 'simulate' button, which prepares the automaton and opens a terminal window where the simulation steps are displayed.
After the simulation ends, the automaton can be reset, and the program can be re-run with a new input or continued with a modified one.

Makefile:
make            -> compiles the program
make run        -> compiles and runs the program
make doxygen    -> generates HTML documentation
make doxyClean  -> deletes the generated documentation
make clean      -> deletes the compiled program
make zip        -> creates a compressed folder with the contents of the directory
