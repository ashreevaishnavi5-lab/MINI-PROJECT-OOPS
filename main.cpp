
#include <iostream>
#include <vector>
#include <string>
#include <utility>
using namespace std;

const string RESET = "\033[0m";
const string BOLD = "\033[1m";
const string DIM = "\033[2m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string MAGENTA = "\033[35m";
const string CYAN = "\033[36m";
const string WHITE = "\033[37m";

void printLine(char symbol = '=', int width = 48)
{
    cout << CYAN << BOLD;
    for (int i = 0; i < width; i++)
        cout << symbol;
    cout << RESET << endl;
}

void heading(string title)
{
    cout << "\n";
    printLine();
    cout << CYAN << BOLD << "  " << title << RESET << endl;
    printLine();
}

void success(string message)
{
    cout << GREEN << BOLD << "[SUCCESS] " << RESET << message << endl;
}

void error(string message)
{
    cout << RED << BOLD << "[ERROR] " << RESET << message << endl;
}

void warning(string message)
{
    cout << YELLOW << BOLD << "[WARNING] " << RESET << message << endl;
}

void info(string message)
{
    cout << BLUE << "[INFO] " << RESET << message << endl;
}

void prompt(string message)
{
    cout << YELLOW << BOLD << message << RESET;
}

void welcomeScreen()
{
    cout << "\n";
    cout << MAGENTA << BOLD;
    cout << "==================================================\n";
    cout << "                  GRAND HOTEL                     \n";
    cout << "              MANAGEMENT SYSTEM                   \n";
    cout << "==================================================\n";
    cout << RESET;
    cout << CYAN << "       Smart Reservations | Better Guest Care\n"
         << RESET;
    cout << DIM << "       C++17 Console Application\n"
         << RESET;
    printLine();
}

bool validDate(int date)
{
    int year = date / 10000;
    int month = (date / 100) % 100;
    int day = date % 100;

    if (year < 2020 || month < 1 || month > 12)
        return false;

    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    bool leap = (year % 400 == 0 ||
                 (year % 4 == 0 && year % 100 != 0));

    if (leap)
        days[1] = 29;

    return day >= 1 && day <= days[month - 1];
}

int dateToDays(int date)
{
    int year = date / 10000;
    int month = (date / 100) % 100;
    int day = date % 100;

    int previousYear = year - 1;

    int total = previousYear * 365 + previousYear / 4 - previousYear / 100 + previousYear / 400;

    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    for (int i = 0; i < month - 1; i++)
        total += days[i];

    bool leap = (year % 400 == 0 ||
                 (year % 4 == 0 && year % 100 != 0));

    if (leap && month > 2)
        total++;

    return total + day;
}

int readDate(string message)
{
    int date;

    while (true)
    {
        cout << message;
        cin >> date;

        if (validDate(date))
            return date;

        error("Invalid date! Use YYYYMMDD format.");
    }
}

class Customer
{
private:
    int customerId;
    string name;
    string phone;

    static int nextId;

public:
    Customer(string n, string p)
    {
        customerId = nextId++;
        name = n;
        phone = p;
    }

    int getId() const
    {
        return customerId;
    }

    string getName() const
    {
        return name;
    }

    void display() const
    {
        cout << "Customer ID: " << customerId << endl;
        cout << "Name: " << name << endl;
        cout << "Phone: " << phone << endl;
    }
};

int Customer::nextId = 1;

class Room
{
private:
    int roomNumber;
    vector<pair<int, int>> maintenanceDates;

public:
    Room(int number)
    {
        roomNumber = number;
    }

    virtual ~Room() {}

    int getRoomNumber() const
    {
        return roomNumber;
    }

    virtual string getCategory() const = 0;
    virtual double getRate() const = 0;

    void addMaintenance(int in, int out)
    {
        maintenanceDates.push_back({in, out});
    }

    void clearMaintenance()
    {
        maintenanceDates.clear();
    }

    bool isUnderMaintenance(int in, int out) const
    {
        for (int i = 0; i < maintenanceDates.size(); i++)
        {
            if (in < maintenanceDates[i].second &&
                maintenanceDates[i].first < out)
            {
                return true;
            }
        }

        return false;
    }

    virtual void display() const
    {
        cout << CYAN << "Room Number: " << RESET << roomNumber << endl;
        cout << CYAN << "Category: " << RESET << getCategory() << endl;
        cout << GREEN << "Price per night: Rs. " << getRate() << RESET << endl;
    }
};

class StandardRoom : public Room
{
public:
    StandardRoom(int number) : Room(number) {}

    string getCategory() const override
    {
        return "Standard";
    }

    double getRate() const override
    {
        return 1500;
    }
};

class DeluxeRoom : public Room
{
public:
    DeluxeRoom(int number) : Room(number) {}

    string getCategory() const override
    {
        return "Deluxe";
    }

    double getRate() const override
    {
        return 2500;
    }
};

class SuiteRoom : public Room
{
public:
    SuiteRoom(int number) : Room(number) {}

    string getCategory() const override
    {
        return "Suite";
    }

    double getRate() const override
    {
        return 4000;
    }
};

// ================= BOOKING CLASS =================

class Booking
{
private:
    int bookingId;
    Customer customer;
    int roomNumber;
    int checkIn;
    int checkOut;
    bool active;

    static int nextBookingId;

public:
    Booking(Customer c, int room, int in, int out)
        : customer(c)
    {

        bookingId = nextBookingId++;
        roomNumber = room;
        checkIn = in;
        checkOut = out;
        active = true;
    }

    int getId() const
    {
        return bookingId;
    }

    int getRoomNumber() const
    {
        return roomNumber;
    }

    int getCheckIn() const
    {
        return checkIn;
    }

    int getCheckOut() const
    {
        return checkOut;
    }

    bool isActive() const
    {
        return active;
    }

    string getCustomerName() const
    {
        return customer.getName();
    }

    void cancel()
    {
        active = false;
    }

    void changeRoom(int room)
    {
        roomNumber = room;
    }

    void extendStay(int date)
    {
        checkOut = date;
    }

    double calculateCost(double rate) const
    {
        int days = dateToDays(checkOut) - dateToDays(checkIn);
        return days * rate;
    }

    // Operator overloading

    friend ostream &operator<<(ostream &out, const Booking &b)
    {
        out << CYAN << BOLD << "\n--- BOOKING DETAILS ---" << RESET;
        out << "\nBooking ID: " << b.bookingId;
        out << "\nCustomer: " << b.customer.getName();
        out << "\nRoom Number: " << b.roomNumber;
        out << "\nCheck-in: " << b.checkIn;
        out << "\nCheck-out: " << b.checkOut;
        out << "\nStatus: "
            << (b.active ? GREEN + "Confirmed" + RESET
                         : RED + "Cancelled" + RESET);

        return out;
    }
};

int Booking::nextBookingId = 1001;

// ================= HOTEL CLASS =================

class Hotel
{
private:
    vector<Room *> rooms;
    vector<Booking> bookings;
    vector<string> history;

    Room *findRoom(int number)
    {
        for (int i = 0; i < rooms.size(); i++)
        {
            if (rooms[i]->getRoomNumber() == number)
                return rooms[i];
        }

        return NULL;
    }

    // Check room and booking conflicts

    bool isRoomAvailable(int roomNumber, int in, int out,
                         int ignoreBookingId = -1)
    {

        Room *room = findRoom(roomNumber);

        if (room == NULL)
            return false;

        if (room->isUnderMaintenance(in, out))
            return false;

        for (int i = 0; i < bookings.size(); i++)
        {

            if (bookings[i].isActive() &&
                bookings[i].getId() != ignoreBookingId &&
                bookings[i].getRoomNumber() == roomNumber)
            {

                int oldIn = bookings[i].getCheckIn();
                int oldOut = bookings[i].getCheckOut();

                if (in < oldOut && oldIn < out)
                    return false;
            }
        }

        return true;
    }

    // Find available rooms of a particular category

    vector<Room *> availableRooms(string category, int in, int out,
                                  int ignoreBookingId = -1)
    {

        vector<Room *> available;

        for (int i = 0; i < rooms.size(); i++)
        {

            if (rooms[i]->getCategory() == category &&
                isRoomAvailable(rooms[i]->getRoomNumber(),
                                in, out, ignoreBookingId))
            {

                available.push_back(rooms[i]);
            }
        }

        return available;
    }

    Booking *findBooking(int id)
    {
        for (int i = 0; i < bookings.size(); i++)
        {
            if (bookings[i].getId() == id)
                return &bookings[i];
        }

        return NULL;
    }

public:
    Hotel()
    {

        for (int i = 101; i <= 105; i++)
            rooms.push_back(new StandardRoom(i));

        for (int i = 201; i <= 204; i++)
            rooms.push_back(new DeluxeRoom(i));

        for (int i = 301; i <= 303; i++)
            rooms.push_back(new SuiteRoom(i));
    }

    // Destructor

    ~Hotel()
    {
        for (int i = 0; i < rooms.size(); i++)
            delete rooms[i];
    }

    // Display rooms

    void displayRooms()
    {
        heading("HOTEL ROOM DETAILS");

        for (int i = 0; i < rooms.size(); i++)
        {
            rooms[i]->display();
            cout << "-------------------------\n";
        }
    }

    // Function overloading: search by ID

    void searchBooking(int id)
    {
        heading("SEARCH BOOKING BY ID");
        Booking *b = findBooking(id);

        if (b != NULL)
            cout << *b << endl;
        else
            cout << "Booking not found!\n";
    }

    // Function overloading: search by name

    void searchBooking(string name)
    {
        heading("SEARCH BOOKING BY CUSTOMER NAME");
        bool found = false;

        for (int i = 0; i < bookings.size(); i++)
        {
            if (bookings[i].getCustomerName() == name)
            {
                cout << bookings[i] << endl;
                found = true;
            }
        }

        if (!found)
            cout << "No booking found for this customer.\n";
    }

    // Check availability

    void checkAvailability()
    {
        heading("CHECK ROOM AVAILABILITY");
        string category;
        int in, out;

        cout << "Enter room category (Standard/Deluxe/Suite): ";
        cin >> category;

        in = readDate("Enter check-in date (YYYYMMDD): ");
        out = readDate("Enter check-out date (YYYYMMDD): ");

        if (dateToDays(out) <= dateToDays(in))
        {
            cout << "Check-out must be after check-in!\n";
            return;
        }

        vector<Room *> available = availableRooms(category, in, out);

        cout << "\nAvailable rooms: " << available.size() << endl;

        for (int i = 0; i < available.size(); i++)
            cout << available[i]->getRoomNumber() << " ";

        if (available.empty())
            cout << "No rooms available. Try another category or dates.";

        cout << endl;
    }

    // Smart Overbooking Protection

    void makeBooking()
    {
        heading("NEW ROOM RESERVATION");
        string name, phone, category;
        int in, out, quantity;

        cout << "Enter customer name: ";
        cin >> ws;
        getline(cin, name);

        cout << "Enter phone number: ";
        cin >> phone;

        cout << "Enter category (Standard/Deluxe/Suite): ";
        cin >> category;

        in = readDate("Enter check-in date (YYYYMMDD): ");
        out = readDate("Enter check-out date (YYYYMMDD): ");

        if (dateToDays(out) <= dateToDays(in))
        {
            cout << "Invalid stay period!\n";
            return;
        }

        cout << "Enter number of rooms required: ";
        cin >> quantity;

        if (quantity <= 0)
        {
            cout << "Invalid room quantity!\n";
            return;
        }

        vector<Room *> available = availableRooms(category, in, out);

        cout << "\nChecking room availability...\n";

        if (available.size() < quantity)
        {
            error("BOOKING REJECTED!");
            cout << "Required rooms: " << quantity << endl;
            cout << "Available rooms: " << available.size() << endl;

            cout << "\nTrying alternative room categories...\n";

            string categories[] = {"Standard", "Deluxe", "Suite"};

            for (int i = 0; i < 3; i++)
            {
                if (categories[i] != category)
                {
                    vector<Room *> alternatives =
                        availableRooms(categories[i], in, out);

                    if (!alternatives.empty())
                        cout << categories[i] << ": "
                             << alternatives.size()
                             << " room(s) available.\n";
                }
            }

            cout << "Try different dates or room categories.\n";
            return;
        }

        Customer c(name, phone);

        for (int i = 0; i < quantity; i++)
        {

            Booking b(c, available[i]->getRoomNumber(), in, out);

            bookings.push_back(b);

            cout << GREEN << BOLD << "\n[BOOKING CONFIRMED]" << RESET;
            cout << "\nBooking ID: " << b.getId();
            cout << "\nRoom Number: " << b.getRoomNumber();

            double cost = b.calculateCost(available[i]->getRate());

            cout << "\nTotal Cost: Rs. " << cost << endl;

            history.push_back("New booking: " +
                              to_string(b.getId()));
        }

        cout << "\nAll requested rooms booked successfully!\n";
    }

    // Display bookings

    void displayBookings()
    {
        heading("ALL RESERVATIONS");
        if (bookings.empty())
        {
            cout << "No bookings available.\n";
            return;
        }

        for (int i = 0; i < bookings.size(); i++)
            cout << bookings[i] << "\n";
    }

    // Cancel booking

    void cancelBooking()
    {
        heading("CANCEL RESERVATION");
        int id;

        cout << "Enter booking ID: ";
        cin >> id;

        Booking *b = findBooking(id);

        if (b == NULL || !b->isActive())
        {
            cout << "Active booking not found!\n";
            return;
        }

        b->cancel();

        history.push_back("Booking cancelled: " + to_string(id));

        success("Booking cancelled successfully!");
        info("Room availability has been updated.");
    }

    // Manage maintenance

    void manageMaintenance()
    {
        heading("ROOM MAINTENANCE MANAGEMENT");
        int number, choice;

        cout << "Enter room number: ";
        cin >> number;

        Room *room = findRoom(number);

        if (room == NULL)
        {
            cout << "Invalid room number!\n";
            return;
        }

        cout << "1. Add maintenance period\n";
        cout << "2. Clear maintenance periods\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            int in = readDate("Enter maintenance start date: ");
            int out = readDate("Enter maintenance end date: ");

            if (dateToDays(out) <= dateToDays(in))
            {
                cout << "Invalid maintenance period!\n";
                return;
            }

            for (int i = 0; i < bookings.size(); i++)
            {
                if (bookings[i].isActive() &&
                    bookings[i].getRoomNumber() == number &&
                    in < bookings[i].getCheckOut() &&
                    bookings[i].getCheckIn() < out)
                {

                    cout << "Maintenance conflicts with booking ID "
                         << bookings[i].getId() << ".\n";
                    cout << "Cannot schedule maintenance.\n";
                    return;
                }
            }

            room->addMaintenance(in, out);

            history.push_back("Maintenance added for room " +
                              to_string(number));

            success("Maintenance period added successfully!");
        }
        else if (choice == 2)
        {
            room->clearMaintenance();

            history.push_back("Maintenance cleared for room " +
                              to_string(number));

            success("Maintenance periods cleared!");
        }
        else
        {
            error("Invalid choice!");
        }
    }

    // Hotel Booking Rescue Engine

    void rescueBooking()
    {
        heading("HOTEL BOOKING RESCUE ENGINE");
        int id, newOut;

        cout << "Enter booking ID: ";
        cin >> id;

        Booking *target = findBooking(id);

        if (target == NULL || !target->isActive())
        {
            cout << "Active booking not found!\n";
            return;
        }

        newOut = readDate("Enter requested new check-out date: ");

        if (dateToDays(newOut) <= dateToDays(target->getCheckOut()))
        {
            cout << "New check-out must be later than the old date!\n";
            return;
        }

        int roomNumber = target->getRoomNumber();
        int in = target->getCheckIn();

        Room *originalRoom = findRoom(roomNumber);

        vector<Booking *> conflicts;

        for (int i = 0; i < bookings.size(); i++)
        {

            if (bookings[i].isActive() &&
                bookings[i].getId() != id &&
                bookings[i].getRoomNumber() == roomNumber)
            {

                if (in < bookings[i].getCheckOut() &&
                    bookings[i].getCheckIn() < newOut)
                {

                    conflicts.push_back(&bookings[i]);
                }
            }
        }

        // No booking conflict

        if (conflicts.empty())
        {

            if (!isRoomAvailable(roomNumber, in, newOut, id))
            {
                cout << "Extension conflicts with maintenance.\n";
                return;
            }

            cout << "No booking conflict detected!\n";
            cout << "New check-out: " << newOut << endl;

            cout << "Manager approval required. Approve? (1=Yes, 0=No): ";

            int approval;
            cin >> approval;

            if (approval == 1)
            {
                target->extendStay(newOut);

                history.push_back("Stay extended for booking " +
                                  to_string(id));

                success("Stay extended successfully!");
            }
            else
            {
                cout << "Modification rejected. Original booking unchanged.\n";
            }

            return;
        }

        if (conflicts.size() > 1)
        {
            cout << "Multiple booking conflicts detected.\n";
            cout << "Cannot safely resolve all conflicts automatically.\n";
            return;
        }

        // One conflicting reservation

        Booking *conflict = conflicts[0];

        cout << "\nBOOKING CONFLICT DETECTED!\n";
        cout << "Conflicting booking ID: " << conflict->getId() << endl;
        cout << "Customer: " << conflict->getCustomerName() << endl;

        // Find alternative rooms

        vector<Room *> alternatives =
            availableRooms(originalRoom->getCategory(),
                           conflict->getCheckIn(),
                           conflict->getCheckOut(),
                           conflict->getId());

        // Corrected alternative room selection

        Room *alternative = NULL;

        for (int i = 0; i < alternatives.size(); i++)
        {
            if (alternatives[i]->getRoomNumber() != roomNumber)
            {
                alternative = alternatives[i];
                break;
            }
        }

        if (alternative == NULL)
        {
            cout << "No alternative room available.\n";
            cout << "Extension rejected. Original bookings unchanged.\n";
            return;
        }

        cout << "\nRESCUE ENGINE SUGGESTION\n";

        cout << "Guest requesting extension keeps Room "
             << roomNumber << endl;

        cout << "Conflicting guest can be moved to Room "
             << alternative->getRoomNumber() << endl;

        cout << "Room category: " << alternative->getCategory() << endl;
        cout << "New room price per night: Rs. "
             << alternative->getRate() << endl;

        cout << "\nManager approval required.\n";
        cout << "Approve this solution? (1=Yes, 0=No): ";

        int approval;
        cin >> approval;

        if (approval == 1)
        {

            conflict->changeRoom(alternative->getRoomNumber());
            target->extendStay(newOut);

            history.push_back("Rescue completed for booking " +
                              to_string(id));

            success("BOOKING RESCUE SUCCESSFUL!");
            cout << "Original guest's stay extended.\n";
            cout << "Other guest moved to alternative room.\n";
        }
        else
        {
            cout << "Suggestion rejected.\n";
            cout << "Original bookings remain unchanged.\n";
        }
    }

    // Display booking history

    void displayHistory()
    {
        heading("BOOKING MODIFICATION HISTORY");

        if (history.empty())
        {
            cout << "No history available.\n";
            return;
        }

        for (int i = 0; i < history.size(); i++)
            cout << i + 1 << ". " << history[i] << endl;
    }
};

// ================= MAIN FUNCTION =================

int main()
{

    Hotel hotel;

    int choice;

    welcomeScreen();

    do
    {
        cout << CYAN << BOLD << "\n                 MAIN MENU\n"
             << RESET;
        printLine('-');
        cout << GREEN << "  1. " << RESET << "Display All Rooms\n";
        cout << GREEN << "  2. " << RESET << "Check Room Availability\n";
        cout << GREEN << "  3. " << RESET << "Make a Reservation\n";
        cout << GREEN << "  4. " << RESET << "View All Reservations\n";
        cout << GREEN << "  5. " << RESET << "Search Reservation\n";
        cout << GREEN << "  6. " << RESET << "Cancel Reservation\n";
        cout << GREEN << "  7. " << RESET << "Manage Room Maintenance\n";
        cout << MAGENTA << BOLD << "  8. " << RESET << "Hotel Booking Rescue Engine\n";
        cout << GREEN << "  9. " << RESET << "View Booking History\n";
        cout << RED << "  0. " << RESET << "Exit\n";
        printLine('-');

        prompt("  Enter your choice: ");
        cin >> choice;

        switch (choice)
        {

        case 1:
            hotel.displayRooms();
            break;

        case 2:
            hotel.checkAvailability();
            break;

        case 3:
            hotel.makeBooking();
            break;

        case 4:
            hotel.displayBookings();
            break;

        case 5:
        {
            int type;

            cout << "1. Search by Booking ID\n";
            cout << "2. Search by Customer Name\n";
            cout << "Enter choice: ";
            cin >> type;

            if (type == 1)
            {
                int id;

                cout << "Enter booking ID: ";
                cin >> id;

                hotel.searchBooking(id);
            }
            else if (type == 2)
            {
                string name;

                cout << "Enter customer name: ";
                cin >> ws;
                getline(cin, name);

                hotel.searchBooking(name);
            }
            else
            {
                error("Invalid choice!");
            }

            break;
        }

        case 6:
            hotel.cancelBooking();
            break;

        case 7:
            hotel.manageMaintenance();
            break;

        case 8:
            hotel.rescueBooking();
            break;

        case 9:
            hotel.displayHistory();
            break;

        case 0:
            success("Thank you for using Grand Hotel Management System!");
            break;

        default:
            error("Invalid choice! Try again.");
        }

    } while (choice != 0);

    return 0;
}
