#include "RentalSystem.h"

int main() {
    RentalSystem agency;
    agency.loadFromFile();

    cout << BOLD << CYAN << "\n==============================================" << RESET << endl;
    cout << BOLD << "      SMART VEHICLE RENTAL SYSTEM (OOPS)      " << RESET << endl;
    cout << BOLD << CYAN << "==============================================" << RESET << endl;

    int role;
    cout << "1. Admin Login\n2. Customer Portal\nChoice: ";
    cin >> role;

    if (role == 1) {
        string pass;
        cout << "Enter Admin Password: "; cin >> pass;
        if (pass != "admin@123") { 
            cout << RED << "Authentication Failed!" << RESET << endl;
            return 0;
        }
    }

    int choice;
    do {
        cout << "\n" << BOLD << BLUE << ">> " << (role == 1 ? "ADMIN PANEL" : "CUSTOMER PORTAL") << RESET << endl;
        
        // Dynamic Menu based on Role
        if (role == 1) {
            cout << "1. View All Vehicles (Fleet Status)\n2. Add New Vehicle to Fleet\n3. Exit System\nSelect Action: ";
        } else {
            cout << "1. View Available Vehicles\n2. Rent a Vehicle\n3. Return a Vehicle\n4. Exit System\nSelect Action: ";
        }
        
        cin >> choice;

        if (choice == 1) {
            // Admin sees everything, Customer sees only Available ones
            agency.displayFleet(role == 1);
        } 
        else if (choice == 2) {
            if (role == 1) {
                // ADMIN: Add Vehicle Logic
                string b, t; double r; int type, s;
                cout << "\n--- Adding New Vehicle ---" << endl;
                cout << "Brand Name: "; cin.ignore(); getline(cin, b);
                cout << "Daily Rate (₹): "; cin >> r;
                cout << "Vehicle Type (1: Car, 2: Bike): "; cin >> type;
                if (type == 1) {
                    cout << "Seats: "; cin >> s;
                    cout << "Transmission (Manual/Auto): "; cin >> t;
                    agency.addVehicle(new Car(b, r, true, s, t));
                } else {
                    agency.addVehicle(new Bike(b, r, true));
                }
                cout << GREEN << "Successfully added to database!" << RESET << endl;
            } else {
                // CUSTOMER: Rent Vehicle Logic
                int id, d; string name;
                cout << "\n--- Rental Process ---" << endl;
                cout << "Your Name: "; cin.ignore(); getline(cin, name);
                cout << "Enter Vehicle ID: "; cin >> id;
                cout << "Duration (Days): "; cin >> d;
                agency.rentVehicle(id, d, name);
            }
        }
        else if (choice == 3 && role == 2) {
            // CUSTOMER: Return Vehicle Logic
            int id;
            cout << "\n--- Return Process ---" << endl;
            cout << "Enter the Vehicle ID you are returning: ";
            cin >> id;
            agency.returnVehicle(id);
        }
        else if ((choice == 3 && role == 1) || (choice == 4 && role == 2)) {
            // Break the loop to exit
            break;
        }
        else {
            cout << RED << "Invalid selection. Please try again." << RESET << endl;
        }

    } while (true);

    cout << BOLD << YELLOW << "\n[System] Saving changes to database... Done." << RESET << endl;
    cout << BOLD << GREEN << "Thank you for using Smart Rental! Session Closed." << RESET << endl;
    return 0;
}

/*
g++ main.cpp Vehicle.cpp RentalSystem.cpp -o smart_rental && ./smart_rental
*/