README file for the C++ 
Project Q 100: Hotel Reservation System, 
 Some key point included in this project to explain
•	A clear task description
•	Explanation of implementation
•	Full annotated version of the source code with inline comments
We have some task to be completed in this project
•	Inheritance and Polymorphism (via abstract classes and virtual functions)
•	Dynamic Memory Management
•	Basic Input/ Output operations
•	Encapsulation and object-oriented design principles
This system it will allow users to:
•	Book rooms (Standard or Premium) for specific dates.
•	Check if a room is already booked on a given date.
•	List all rooms and their first booked date.
•	Remove a booked room from the system.
This project how it will be completed
	We will consider this : 
•	 Base abstract class Room Base with virtual methods.
•	Two derived classes: Standard and Premium Suite.
•	A Date structure for handling date-related operations.
•	Dynamic arrays to manage bookings and room collections.
•	Global counters to track room availability.
•	A simple menu-driven interface to interact with the user.
Memory is allocated and deallocated appropriately using new and delete to avoid memory leaks.

#include <iostream> // Includes standard input and output stream
#include <cstring> // Includes C-style string functions (like strcmp)

using namespace std; // Allows us to use cout, cin, etc., directly without std::

struct Date { // Define a structure to store a calendar date
    int day, month, year; // day, month, and year components of the date
    
    bool equals(const Date* other) const { // Method to check if two dates are equal
        return day == other->day && month == other->month && year == other->year; // true if all components match
    }
    void print() const { // Method to print the date in DD/MM/YYYY format
        cout << day << "/" << month << "/" << year; // Prints day, then slash, then month, then slash, then year
    }
};

class RoomBase { // Abstract base class for a hotel room
protected:
    Date* bookedDates; // Dynamic array of dates that are already booked
    int nDates; // Number of booking dates

public:
    RoomBase() : bookedDates(nullptr), nDates(0) {} // Initializes with no booking dates
    virtual ~RoomBase() { delete[] bookedDates; } // Cleans up the dynamic array upon destruction
    
    virtual bool isBooked(const Date* d) = 0; // Pure virtual: checks if a given date is already booked
    virtual void book(const Date* d) = 0; // Pure virtual: books a given date
    virtual void printType() const = 0; // Pure virtual: prints room's type
    virtual const char* getType() const = 0; // Pure virtual: returns room's type as C-style string
    
    Date getFirstDate() const { // Helper to retrieve first booking
        return nDates > 0 ? bookedDates[0] : Date{0, 0, 0}; // If we have at least 1 booking, return first; otherwise return 0
    }
};

class StandardRoom : public RoomBase { // Standard room derives from base
public:
    bool isBooked(const Date* d) override { // Check if given date is already booked
        for (int i = 0; i < nDates; ++i) // Loop through all booking dates
            if ((bookedDates + i)->equals(d)) return true; // If match is found, return true immediately
        return false; // Otherwise, it's not booked
    }
    void book(const Date* d) override { // Book a new date if it's not already booked
        if (isBooked(d)) { // If it's already booked
            cout << "? Date already booked.\n"; // Display a message
            return; // Don't book again
        }
        Date* newDates = new Date[nDates + 1]; // Allocate new array with space for 1 more
        for (int i = 0; i < nDates; ++i) // Loop through existing dates
            newDates[i] = bookedDates[i]; // Copy each to new array
        newDates[nDates] = *d; // Add new booking at the last spot

        delete[] bookedDates; // Free old array
        bookedDates = newDates; // Point to new array
        nDates++; // Update count
    }
    void printType() const override { cout << "Standard Room"; } // Prints room's Type
    const char* getType() const override { return "Standard Room"; } // Returns room's Type
};

class PremiumSuite : public RoomBase { // Premium suite is implemented identically to Standard
public:
    bool isBooked(const Date* d) override { // Check if a given date is already booked
        for (int i = 0; i < nDates; ++i) // Loop through all booking dates
            if ((bookedDates + i)->equals(d)) return true; // If match is found, return true immediately
        return false; // Otherwise, it's not booked
    }
    void book(const Date* d) override { // Book a new date if it's not already booked
        if (isBooked(d)) { // If it's already booked
            cout << "? Date already booked.\n"; // Display a message
            return; // Don't book again
        }
        Date* newDates = new Date[nDates + 1]; // Allocate new array with 1 more space
        for (int i = 0; i < nDates; ++i) // Loop through existing dates
            newDates[i] = bookedDates[i]; // Copy dates into new array
        newDates[nDates] = *d; // Add the new booking
        delete[] bookedDates; // Free old array
        bookedDates = newDates; // Point to new array
        nDates++; // Update count
    }
    void printType() const override { cout << "Premium Suite"; } // Prints room's Type
    const char* getType() const override { return "Premium Suite"; } // Returns room's Type
};

RoomBase** rooms = nullptr; // Global array of room pointers
int nRooms = 0; // Number of rooms currently in the hotel
const int maxStandardRooms = 5; // Max number of Standard rooms available
const int maxPremiumSuites = 3; // Max number of Premium suites available
int availableStandardRooms = maxStandardRooms; // Standard available starts from maximum
int availablePremiumSuites = maxPremiumSuites; // Premium available starts from maximum

void addRoom(RoomBase* room) { // Adds a new room to the array
    RoomBase** newRooms = new RoomBase*[nRooms + 1]; // Allocate new array with 1 more
    for (int i = 0; i < nRooms; ++i) // Loop through existing
        newRooms[i] = rooms[i]; // Copy into new array
    newRooms[nRooms] = room; // Add new room at the last
    delete[] rooms; // Free old array
    rooms = newRooms; // Point to new array
    nRooms++; // Update total count
}

void removeRoom(int index) { // Remove a room by index
    if (index < 0 || index >= nRooms) { // Validate index first
        cout << "Invalid room index.\n";
        return;
    }
    const char* type = rooms[index]->getType(); // Get room's Type
    if (strcmp(type, "Standard Room") == 0) availableStandardRooms++; // If Standard, increase its availability
    else if (strcmp(type, "Premium Suite") == 0) availablePremiumSuites++; // If Premium, increase its availability

    delete rooms[index]; // Free the room's memory
    RoomBase** newRooms = new RoomBase*[nRooms - 1]; // Allocate array of size nRooms-1
    for (int i = 0, j = 0; i < nRooms; ++i) // Loop through
        if (i != index) // If it's not the removed one
            newRooms[j++] = rooms[i]; // Move it into new array

    delete[] rooms; // Free old array
    rooms = newRooms; // Update
    nRooms--; // Decrement count

    cout << "? Room removed.\n";
}

void listRooms() { // Prints all room booking information
    if (nRooms == 0) { // If hotel is empty
        cout << "No rooms available.\n";
        return;
    }
    for (int i = 0; i < nRooms; ++i) { // Loop through all
        cout << i << ". " << rooms[i]->getType()
             << " - Booked on: "; // Display index and room's Type
        rooms[i]->getFirstDate().print(); // Prints first booking
        cout << endl;
    }
}

int main() { // Main function, handles UI
    int choice; // Stores menu choice

    while (true) { // Loop until 0 (exit) is entered
        cout << "\n========== ?? Hotel Reservation System ==========\n";
        cout << "Available: Standard = " << availableStandardRooms
             << ", Premium = " << availablePremiumSuites << endl;
        cout << "1. Book a Room (choose type + date)\n";
        cout << "2. Check if a Room is Booked\n";
        cout << "3. List All Rooms\n";
        cout << "4. Remove Room by Index\n";
        cout << "0. Exit\n";
        cout << "===============================================\n";
        cout << "Enter your choice: "; // Prompt for menu choice
        cin >> choice; // Input choice

        if (choice == 0) break; // If 0, exit the loop

        switch (choice) { // Handle the choice
        case 1: { // Book a room
                int type;
                cout << "Choose Room Type:\n";
                cout << "1. Standard Room\n";
                cout << "2. Premium Suite\n";
                cout << "Enter choice: "; // Ask for room's Type
                cin >> type; // Input Type

                if ((type == 1 && availableStandardRooms == 0) ||
                    (type == 2 && availablePremiumSuites == 0)) { // Check if available
                    cout << "? No rooms of selected type available.\n";
                    break;
                }
                
                Date d;
                cout << "Enter date (day month year): "; // Ask for booking date
                cin >> d.day >> d.month >> d.year; // Input day,month,year

                RoomBase* room = nullptr; // Prepare pointer
                if (type == 1) { // If Standard
                    room = new StandardRoom();
                    availableStandardRooms--;
                } else if (type == 2) { // If Premium
                    room = new PremiumSuite();
                    availablePremiumSuites--;
                } else { // If invalid
                    cout << "Invalid room type.\n";
                    break;
                }
                
                room->book(&d); // Book the room for given date
                addRoom(room); // Add it to hotel's array

                cout << "? Booking Confirmed!\n";
                cout << "Room Index: " << nRooms - 1 << "\n";
                cout << "Room Type: " << room->getType() << "\n";
                cout << "Booked Date: "; d.print(); cout << endl;
                break;
            }
        case 2: { // Check if a room is booked
                listRooms();
                if (nRooms == 0) break;
                int index;
                cout << "Enter room index: "; // Ask for room
                cin >> index; // Input
                if (index < 0 || index >= nRooms) { // Validate
                    cout << "Invalid index.\n";
                    break;
                }
                
                Date d;
                cout << "Enter date (day month year): "; // Ask for date to check
                cin >> d.day >> d.month >> d.year; // Input
                
                if (rooms[index]->isBooked(&d)) { // Check booking
                    cout << "? Already booked on "; d.print(); cout << endl;
                } else { // If not
                    cout << "? Available on "; d.print(); cout << endl;
                }
                break;
            }
        case 3: // List all
                listRooms();
                break;
        case 4: { // Remove a room
                listRooms();
                if (nRooms == 0) break;
                int index;
                cout << "Enter index of room to remove: "; // Ask which
                cin >> index; // Input
                removeRoom(index); // Remove
                break;
            }
        default:
                cout << "? Invalid option.\n";
        }
    }
    for (int i = 0; i < nRooms; ++i) // Cleanup all
        delete rooms[i];
    delete[] rooms;

    cout << "?? Exiting system.";
    return 0;
}•You can expand this by adding features like room numbers, customer names, or full calendars.
• For real applications, consider using std::vector and std::shared_ptr, but this code strictly uses dynamic memory and pointer arithmetic as required.
