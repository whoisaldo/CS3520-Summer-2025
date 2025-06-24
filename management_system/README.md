# Convention Center Management System

## Overview
This system manages event reservations, ticket sales, and facility scheduling for a convention center. It provides functionality for different user types (residents, non-residents, organizations, city officials, and managers) with appropriate access controls.

FOR FINAL REPORT GO TO design

## Features
- User management with different user types
- Reservation scheduling and management
- Event creation and management
- Ticketing system with waitlist capability
- Room layout configuration options
- Payment processing and refund handling
- State persistence

## Prerequisites
- C++17-compatible compiler (`g++` recommended)
- `make` utility

## Group Members
- **Ali Younes** (Younes.al@northeastern.edu)
- **Ali Tleis** (Tleis.a@northeastern.edu)

## Building
To compile and link the program, simply run:
```bash
make
```
This will:
1. Compile all `.cpp` files in `src/` with the include path `include/`.
2. Place object files in `build/` and the final executable in `bin/management_system`.

## Cleaning
To remove all compiled objects and executables:
```bash
make clean
```

## Running the Program
After building, run:
```bash
./bin/management_system
```
You must run this command from the project root so that the `data/` directory is resolved correctly.

## Makefile Targets
- **all** (default): Build the executable and its dependencies.
- **clean**: Delete `build/` and `bin/` directories.
- **help** (optional): Show usage information.

## Default Users and Data Files

The system will pre-populate the following default users on first run if `data/users.dat` does not exist:

| Role          | Username      | Password |
|---------------|---------------|----------|
| Manager       | manager       | password |
| Resident      | resident1     | password |
| Non-Resident  | nonresident1  | password |
| Organization  | organization1 | password |
| City Official | city1         | password |

Default data files are located under the `data/` directory:

- `data/users.dat`  
- `data/events.dat`  
- `data/reservations.dat`  
- `data/tickets.dat`  

If these files are missing, they will be created automatically on startup.

## System Design
The system follows object-oriented design principles:
- SOLID principles for class structure
- STL for data structures
- Smart pointers for memory management
- Proper encapsulation and inheritance hierarchies

### Key Classes
- `User` (abstract base class)  
  - `Resident`  
  - `NonResident`  
  - `Organization`  
  - `City`  
  - `Manager`  
- `Event`  
- `Reservation`  
- `Ticket`  
- `System`  
- `FileManager`  

## State Persistence
All system data is automatically saved to files in the `data/` directory when the program exits:
- `users.dat`
- `events.dat`
- `reservations.dat`
- `tickets.dat`

## Testing
The system has been tested for:
- User authentication and error handling
- Event creation and management
- Reservation scheduling and view (day/week)
- Ticket purchasing, waitlist, and refunds
- Enforcement of reservation rules (overlaps, time limits, budget)
- Data persistence across sessions

## Notes
- Ensure you run `make clean` before `make` after any Makefile changes.
- Always run `./bin/management_system` from the project root.
- If you encounter missing file errors, verify the `data/` directory exists and is writable.
