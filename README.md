# Hotel Management System (C++)

This is a console-based Hotel Management System developed using C++ as part of our OOP project.

The idea behind this project is to make basic hotel operations easier, such as managing rooms, handling reservations, checking availability, cancelling bookings and modifying existing reservations.

Apart from the basic features, we have also worked on two additional features: a Smart Overbooking Protection System and a Hotel Booking Rescue Engine.

## Features

**1. Room Management**
- View all available hotel rooms.
- Three room categories: Standard, Deluxe and Suite.
- Manage room maintenance schedules.

**2. Booking Management**
- Enter customer details and make reservations.
- Check room availability for selected dates.
- Calculate the total booking cost.
- View and search existing bookings.
- Cancel reservations.
- View booking history.

**3. Smart Overbooking Protection**

This feature checks whether enough rooms are available for the customer's entire stay before confirming a reservation.

It considers existing bookings and maintenance schedules to avoid assigning the same room to multiple customers for overlapping dates. If there aren't enough rooms, it rejects the booking and shows available alternatives in other room categories.

**4. Hotel Booking Rescue Engine**

This feature handles situations where a guest wants to extend their stay, but another reservation is already scheduled for the same room.

The system checks for the conflict and searches for another available room in the same category. It then suggests moving the conflicting reservation to that room.

The change is made only after manager approval. If no suitable room is available or the suggestion is rejected, the original bookings remain unchanged.

## Room Categories and Prices

| Room Type | Price per Night |
|---|---:|
| Standard | ₹1,500 |
| Deluxe | ₹2,500 |
| Suite | ₹4,000 |

## Technologies Used

- C++
- C++17
- Visual Studio Code
- GCC Compiler
- STL Vectors
- ANSI escape codes for terminal colours

## OOP Concepts Used

While developing this project, we have implemented several OOP concepts:

- Classes and Objects
- Encapsulation
- Inheritance
- Abstraction
- Runtime Polymorphism
- Constructors and Destructors
- Static Data Members
- Function Overloading
- Operator Overloading
- Friend Function
- Composition

## How to Run

**Requirements:** VS Code and a C++ compiler (GCC).

1. Clone or download this repository.
2. Open the project folder in VS Code.
3. Open the terminal.
4. Compile the program:

```bash
g++ -std=c++17 main.cpp -o main.exe
```

5. Run the application:

```powershell
.\main.exe
```

## Project Structure

```text
Hotel-Management-System/
│
├── main.cpp
└── README.md
```

## Current Limitations

- Data is stored in memory, so bookings are reset when the program is closed.
- There is no database or online booking facility.
- The rescue engine currently handles one conflicting reservation at a time.
- The application runs through the terminal rather than a graphical interface.

## Future Improvements

We would like to improve the project further by adding database support, a graphical interface, permanent booking records and more advanced conflict handling.

---

**Developed as an academic project using C++ and Object-Oriented Programming.**
