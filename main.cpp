#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <iomanip>

using namespace std;

// ================= COLOR DEFINITIONS =================
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

// ================= VEHICLE BASE CLASS =================
class Vehicle {
protected:
    static int nextID;
    int id;
    string brand;
    double rate;
    bool available;

public:
    Vehicle(string b, double r) {
        id = ++nextID;
        brand = b;
        rate = r;
        available = true;
    }

    virtual ~Vehicle() {}

    int getID() { return id; }
    string getBrand() { return brand; }
    double getRate() { return rate; }
    bool isAvailable() { return available; }

    void rentVehicle() { available = false; }
    void makeAvailable() { available = true; }

    virtual string getType() = 0;

    virtual void display() {
        cout << CYAN << setw(5) << id << RESET
             << setw(15) << brand
             << setw(10) << getType()
             << " ₹" << setw(8) << rate << "  ";

        if (available)
            cout << GREEN << "Available" << RESET;
        else
            cout << RED << "Rented" << RESET;

        cout << endl;
    }
};

int Vehicle::nextID = 1000;

// ================= CAR CLASS =================
class Car : public Vehicle {
    int seats;

public:
    Car(string b, double r, int s) : Vehicle(b, r) {
        seats = s;
    }

    string getType() override {
        return "Car";
    }
};

// ================= BIKE CLASS =================
class Bike : public Vehicle {
public:
    Bike(string b, double r) : Vehicle(b, r) {}

    string getType() override {
        return "Bike";
    }
};

// ================= RENTAL HISTORY =================
class RentalRecord {
public:
    string customer;
    string vehicle;
    int id;
    int days;
    double total;

    RentalRecord(string c, string v, int i, int d, double t) {
        customer = c;
        vehicle = v;
        id = i;
        days = d;
        total = t;
    }

    void display() {
        cout << setw(15) << customer
             << setw(15) << vehicle
             << setw(6) << id
             << setw(6) << days
             << "  ₹" << total << endl;
    }
};

// ================= RENTAL SYSTEM =================
class RentalSystem {

    vector<unique_ptr<Vehicle>> fleet;
    vector<RentalRecord> history;

public:

    void addVehicle(unique_ptr<Vehicle> v) {
        fleet.push_back(move(v));
    }

    void displayVehicles(bool onlyAvailable = false) {

        cout << BOLD << YELLOW
             << "\n===========================================\n";
        cout << "            VEHICLE FLEET STATUS\n";
        cout << "===========================================\n"
             << RESET;

        cout << "ID   Brand          Type      Rate(₹)    Status\n";
        cout << "------------------------------------------------\n";

        for (auto &v : fleet) {

            if (onlyAvailable && !v->isAvailable())
                continue;

            v->display();
        }

        cout << "\nTotal Vehicles: " << fleet.size() << endl;
    }

    // ================= RECEIPT FUNCTION =================
    void printReceipt(string customer, string brand, int id, int days, double rate) {

        double total = days * rate;

        cout << BOLD << CYAN;
        cout << "\n=====================================\n";
        cout << "           RENTAL RECEIPT\n";
        cout << "=====================================\n";
        cout << RESET;

        cout << "Customer Name : " << customer << endl;
        cout << "Vehicle Brand : " << brand << endl;
        cout << "Vehicle ID    : " << id << endl;
        cout << "Rental Days   : " << days << endl;
        cout << "Rate / Day    : ₹" << rate << endl;

        cout << "-------------------------------------\n";

        cout << GREEN << "Total Amount  : ₹" << total << RESET << endl;

        cout << BOLD << CYAN;
        cout << "=====================================\n";
        cout << RESET;

        cout << "Thank you for choosing our service!\n";
    }

    // ================= RENT VEHICLE =================
    void rentVehicle(string customer) {

        int id, days;

        cout << "\nEnter Vehicle ID: ";
        cin >> id;

        cout << "Number of days: ";
        cin >> days;

        for (auto &v : fleet) {

            if (v->getID() == id && v->isAvailable()) {

                v->rentVehicle();

                double total = days * v->getRate();

                history.push_back(
                    RentalRecord(customer,
                                 v->getBrand(),
                                 v->getID(),
                                 days,
                                 total));

                cout << GREEN << BOLD
                     << "\n✔ Rental Successful!\n"
                     << RESET;

                printReceipt(customer,
                             v->getBrand(),
                             v->getID(),
                             days,
                             v->getRate());

                return;
            }
        }

        cout << RED << "\n✖ Vehicle not available.\n" << RESET;
    }

    // ================= RETURN VEHICLE =================
    void returnVehicle() {

        int id;

        cout << "Enter Vehicle ID to return: ";
        cin >> id;

        for (auto &v : fleet) {

            if (v->getID() == id && !v->isAvailable()) {

                v->makeAvailable();

                cout << GREEN << "Vehicle returned successfully!\n" << RESET;
                return;
            }
        }

        cout << RED << "Invalid Vehicle ID or already available!\n" << RESET;
    }

    void showHistory() {

        cout << BOLD << CYAN
             << "\n========== RENTAL HISTORY ==========\n"
             << RESET;

        cout << "Customer        Vehicle        ID   Days   Total\n";
        cout << "---------------------------------------------------\n";

        for (auto &r : history)
            r.display();
    }
};

// ================= MAIN =================
int main() {

    cout << fixed << setprecision(2);

    RentalSystem system;

    // Preloaded Vehicles
    system.addVehicle(make_unique<Car>("Toyota", 3000, 5));
    system.addVehicle(make_unique<Car>("Tesla", 5000, 5));
    system.addVehicle(make_unique<Bike>("Yamaha", 1200));

    int role;

    while (true) {

        cout << BOLD << CYAN
             << "\n=====================================\n";
        cout << "       SMART VEHICLE RENTAL SYSTEM\n";
        cout << "=====================================\n"
             << RESET;

        cout << "1. Admin Panel\n";
        cout << "2. Customer Panel\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> role;

        if (role == 0)
            break;

        // ================= ADMIN =================
        if (role == 1) {

            int choice;

            while (true) {

                cout << YELLOW << "\n--- ADMIN MENU ---\n" << RESET;
                cout << "1. View Fleet\n";
                cout << "2. Add Vehicle\n";
                cout << "3. View Rental History\n";
                cout << "4. Return Vehicle\n";
                cout << "0. Logout\n";
                cout << "Choice: ";
                cin >> choice;

                if (choice == 0)
                    break;

                if (choice == 1)
                    system.displayVehicles();

                else if (choice == 2) {

                    int type;
                    string brand;
                    double rate;

                    cout << "1.Car  2.Bike : ";
                    cin >> type;

                    cout << "Brand: ";
                    getline(cin >> ws, brand);

                    cout << "Rate per day: ";
                    cin >> rate;

                    if (type == 1) {

                        int seats;
                        cout << "Seats: ";
                        cin >> seats;

                        system.addVehicle(
                            make_unique<Car>(brand, rate, seats));
                    }
                    else {

                        system.addVehicle(
                            make_unique<Bike>(brand, rate));
                    }

                    cout << GREEN << "Vehicle Added Successfully!\n" << RESET;
                }

                else if (choice == 3)
                    system.showHistory();

                else if (choice == 4)
                    system.returnVehicle();
            }
        }

        // ================= CUSTOMER =================
        else if (role == 2) {

            string name;

            cout << "\nEnter your name: ";
            getline(cin >> ws, name);

            int choice;

            while (true) {

                cout << CYAN << "\n--- CUSTOMER MENU ---\n" << RESET;
                cout << "1. View Available Vehicles\n";
                cout << "2. Rent Vehicle\n";
                cout << "0. Logout\n";
                cout << "Choice: ";
                cin >> choice;

                if (choice == 0)
                    break;

                if (choice == 1)
                    system.displayVehicles(true);

                else if (choice == 2)
                    system.rentVehicle(name);
            }
        }
    }

    cout << GREEN << "\nThank you for using the system!\n" << RESET;

    return 0;
}