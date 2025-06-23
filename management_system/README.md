# Convention Center Management System

## Overview
This system manages event reservations, ticket sales, and facility scheduling for a convention center. It provides functionality for different user types (residents, non-residents, organizations, city officials, and managers) with appropriate access controls.

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

## Makefile Targets
- **all** (default): Build the executable and its dependencies.
- **clean**: Delete `build/` and `bin/` directories.
- **help** (optional): Show usage information.

## Default Users
The system comes with the following pre-populated user accounts:

1. **Manager**
   - Username: `manager`
   - Password: `admin123`
2. **Resident**
   - Username: `resident1`
   - Password: `pass123`
3. **Non-Resident**
   - Username: `nonresident1`
   - Password: `pass123`
4. **Organization**
   - Username: `organization1`
   - Password: `pass123`
5. **City Official**
   - Username: `city1`
   - Password: `pass123`

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

## Testing
The system has been thoroughly tested for:
- User authentication
- Event creation and management
- Reservation processing
- Ticket purchasing and refunds
- Data persistence

## State Persistence
All system data is automatically saved to files:
- `users.dat`
- `events.dat`
- `reservations.dat`
- `tickets.dat`
