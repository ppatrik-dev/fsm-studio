/**
 * @mainpage ICP2 Project – Documentation
 *
 * @section intro Introduction
 * This project is part of the ICP course and implements a Qt-based application
 * for configuring and visualizing finite state machines (FSM).
 *
 * The application provides a GUI interface for defining FSM states, transitions,
 * and behavior based on user interaction. It also includes parsing logic
 * to load and save FSM configurations in JSON format.
 *
 * @section author Author
 * Miroslav Bašista - xbasism00
 * 
 * Patrik Prochazka - xprochp00
 * 
 * Filip Ficka - xfickaf00
 *
 * @section version Version
 * 1.2 – 2025-05-10
 *
 * @section structure Structure
 * - `src/gui/` – contains Qt widgets for the graphical user interface, such as:
 *   - `GenericRowWidget`, `TerminalWidget`, `FSMView`, `FSMGui`, etc.
 * - `src/parser/` – includes classes and strategies for FSM logic and JSON processing, e.g.:
 *   - `MooreMachine`, `MooreState`, `ExecutionStrategy`, `AutomateJsonDocument`
 *
 * @section build Building Documentation
 * To build the documentation, run:
 * ```
 * make doxygen
 * ```
 * The output is generated in the `doc/html/` directory.
 */