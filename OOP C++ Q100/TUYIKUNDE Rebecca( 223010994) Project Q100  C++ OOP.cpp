#include <iostream>
#include <cstring>
using namespace std;

struct Date {
    int day, month, year;
    bool equals(const Date* other) const {
        return day == other->day && month == other->month && year == other->year;
    }
    void print() const {
        cout << day << "/" << month << "/" << year;
    }
};

class RoomBase {
protected:
    Date* bookedDates;
    int nDates;

public:
    RoomBase() : bookedDates(nullptr), nDates(0) {}
    virtual ~RoomBase() { delete[] bookedDates; }

    virtual bool isBooked(const Date* d) = 0;
    virtual void book(const Date* d) = 0;
    virtual void printType() const = 0;
    virtual const char* getType() const = 0;
    Date getFirstDate() const { return nDates > 0 ? bookedDates[0] : Date{0, 0, 0}; }
};

class StandardRoom : public RoomBase {
public:
    bool isBooked(const Date* d) override {
        for (int i = 0; i < nDates; ++i)
            if ((bookedDates + i)->equals(d)) return true;
        return false;
    }

    void book(const Date* d) override {
        if (isBooked(d)) {
            cout << "? Date already booked.\n";
            return;
        }
        Date* newDates = new Date[nDates + 1];
        for (int i = 0; i < nDates; ++i)
            newDates[i] = bookedDates[i];
        newDates[nDates] = *d;
        delete[] bookedDates;
        bookedDates = newDates;
        nDates++;
    }

    void printType() const override {
        cout << "Standard Room";
    }

    const char* getType() const override {
        return "Standard Room";
    }
};

class PremiumSuite : public RoomBase {
public:
    bool isBooked(const Date* d) override {
        for (int i = 0; i < nDates; ++i)
            if ((bookedDates + i)->equals(d)) return true;
        return false;
    }

    void book(const Date* d) override {
        if (isBooked(d)) {
            cout << "? Date already booked.\n";
            return;
        }
        Date* newDates = new Date[nDates + 1];
        for (int i = 0; i < nDates; ++i)
            newDates[i] = bookedDates[i];
        newDates[nDates] = *d;
        delete[] bookedDates;
        bookedDates = newDates;
        nDates++;
    }

    void printType() const override {
        cout << "Premium Suite";
    }

    const char* getType() const override {
        return "Premium Suite";
    }
};

RoomBase** rooms = nullptr;
int nRooms = 0;
const int maxStandardRooms = 5;
const int maxPremiumSuites = 3;
int availableStandardRooms = maxStandardRooms;
int availablePremiumSuites = maxPremiumSuites;

void addRoom(RoomBase* room) {
    RoomBase** newRooms = new RoomBase*[nRooms + 1];
    for (int i = 0; i < nRooms; ++i)
        newRooms[i] = rooms[i];
    newRooms[nRooms] = room;
    delete[] rooms;
    rooms = newRooms;
    nRooms++;
}

void removeRoom(int index) {
    if (index < 0 || index >= nRooms) {
        cout << "Invalid room index.\n";
        return;
    }

    const char* type = rooms[index]->getType();
    if (strcmp(type, "Standard Room") == 0) availableStandardRooms++;
    else if (strcmp(type, "Premium Suite") == 0) availablePremiumSuites++;

    delete rooms[index];

    RoomBase** newRooms = new RoomBase*[nRooms - 1];
    for (int i = 0, j = 0; i < nRooms; ++i)
        if (i != index)
            newRooms[j++] = rooms[i];

    delete[] rooms;
    rooms = newRooms;
    nRooms--;

    cout << "? Room removed.\n";
}

void listRooms() {
    if (nRooms == 0) {
        cout << "No rooms available.\n";
        return;
    }

    for (int i = 0; i < nRooms; ++i) {
        cout << i << ". " << rooms[i]->getType()
             << " - Booked on: ";
        rooms[i]->getFirstDate().print();
        cout << endl;
    }
}

int main() {
    int choice;

    while (true) {
        cout << "\n========== ?? Hotel Reservation System ==========\n";
        cout << "Available: Standard = " << availableStandardRooms
             << ", Premium = " << availablePremiumSuites << endl;
        cout << "1. Book a Room (choose type + date)\n";
        cout << "2. Check if a Room is Booked\n";
        cout << "3. List All Rooms\n";
        cout << "4. Remove Room by Index\n";
        cout << "0. Exit\n";
        cout << "===============================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 0) break;

        switch (choice) {
            case 1: {
                int type;
                cout << "Choose Room Type:\n";
                cout << "1. Standard Room\n";
                cout << "2. Premium Suite\n";
                cout << "Enter choice: ";
                cin >> type;

                if ((type == 1 && availableStandardRooms == 0) ||
                    (type == 2 && availablePremiumSuites == 0)) {
                    cout << "? No rooms of selected type available.\n";
                    break;
                }

                Date d;
                cout << "Enter date (day month year): ";
                cin >> d.day >> d.month >> d.year;

                RoomBase* room = nullptr;
                if (type == 1) {
                    room = new StandardRoom();
                    availableStandardRooms--;
                } else if (type == 2) {
                    room = new PremiumSuite();
                    availablePremiumSuites--;
                } else {
                    cout << "Invalid room type.\n";
                    break;
                }

                room->book(&d);
                addRoom(room);
                cout << "? Booking Confirmed!\n";
                cout << "Room Index: " << nRooms - 1 << "\n";
                cout << "Room Type: " << room->getType() << "\n";
                cout << "Booked Date: "; d.print(); cout << endl;
                break;
            }

            case 2: {
                listRooms();
                if (nRooms == 0) break;
                int index;
                cout << "Enter room index: ";
                cin >> index;
                if (index < 0 || index >= nRooms) {
                    cout << "Invalid index.\n";
                    break;
                }

                Date d;
                cout << "Enter date (day month year): ";
                cin >> d.day >> d.month >> d.year;
                if (rooms[index]->isBooked(&d)) {
                    cout << "? Already booked on ";
                    d.print(); cout << endl;
                } else {
                    cout << "? Available on ";
                    d.print(); cout << endl;
                }
                break;
            }

            case 3:
                listRooms();
                break;

            case 4: {
                listRooms();
                if (nRooms == 0) break;
                int index;
                cout << "Enter index of room to remove: ";
                cin >> index;
                removeRoom(index);
                break;
            }

            default:
                cout << "? Invalid option.\n";
        }
    }

    for (int i = 0; i < nRooms; ++i)
        delete rooms[i];
    delete[] rooms;

    cout << "?? Exiting system. Goodbye!\n";
    return 0;
}
