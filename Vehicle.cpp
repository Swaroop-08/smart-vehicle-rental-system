#include "Vehicle.h"

int Vehicle::static_id_counter = 1000; // ✅ Starts at 1000, first will be 1001

Vehicle::Vehicle(string b, double r, bool a, string t, int existing_id) 
    : brand(b), rate(r), available(a), type(t) {
    if (existing_id == 0) id = ++static_id_counter;
    else id = existing_id;
}

string Vehicle::toCSV() const {
    return to_string(id) + "," + brand + "," + to_string(rate) + "," + (available ? "1" : "0") + "," + type;
}

ostream& operator<<(ostream& os, const Vehicle& v) {
    os << BOLD << CYAN << "[" << v.id << "]" << RESET << " " 
       << left << setw(18) << v.brand << " | Rate: " << GREEN << "₹" << (int)v.rate << "/day" << RESET;
    if (v.available) os << " | " << GREEN << "AVAILABLE" << RESET;
    else os << " | " << RED << "RENTED" << RESET;
    return os;
}

Car::Car(string b, double r, bool a, int s, string t, int existing_id) 
    : Vehicle(b, r, a, "Car", existing_id), seats(s), trans(t) {}

void Car::showSpecs() const {
    cout << YELLOW << "      Specs: " << seats << " Seater | " << trans << " Transmission" << RESET << endl;
}

string Car::toCSV() const {
    return Vehicle::toCSV() + "," + to_string(seats) + "," + trans;
}

Bike::Bike(string b, double r, bool a, int existing_id) 
    : Vehicle(b, r, a, "Bike", existing_id) {}

void Bike::showSpecs() const {
    cout << YELLOW << "      Specs: Sports Engine | Complimentary Helmet" << RESET << endl;
}

string Bike::toCSV() const {
    return Vehicle::toCSV() + ",0,N/A";
}