#include "RentalSystem.h"

RentalSystem::~RentalSystem() {
    saveToFile();
    for (auto v : fleet) delete v;
}

void RentalSystem::addVehicle(Vehicle* v) { fleet.push_back(v); }

void RentalSystem::saveToFile() {
    ofstream out(filename);
    for (auto v : fleet) out << v->toCSV() << endl;
    out.close();
}

void RentalSystem::loadFromFile() {
    ifstream in(filename);
    if (!in) return;
    string line;
    int max_id = 1000;
    while (getline(in, line)) {
        stringstream ss(line);
        string id_s, brand, rate_s, avail_s, type, s1, s2;
        getline(ss, id_s, ','); getline(ss, brand, ','); getline(ss, rate_s, ',');
        getline(ss, avail_s, ','); getline(ss, type, ','); getline(ss, s1, ','); getline(ss, s2, ',');

        if (id_s.empty()) continue;

        int id = stoi(id_s);
        if (id > max_id) max_id = id;

        if (type == "Car") 
            fleet.push_back(new Car(brand, stod(rate_s), avail_s == "1", stoi(s1), s2, id));
        else 
            fleet.push_back(new Bike(brand, stod(rate_s), avail_s == "1", id));
    }
    Vehicle::setCounter(max_id);
    in.close();
}

void RentalSystem::displayFleet(bool adminView) {
    cout << "\n" << BOLD << BLUE << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << RESET << endl;
    cout << BOLD << "                CURRENT VEHICLE FLEET                " << RESET << endl;
    cout << BOLD << BLUE << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << RESET << endl;
    for (auto v : fleet) {
        if (!adminView && !v->isAvailable()) continue;
        cout << *v << endl;
        v->showSpecs();
        cout << "──────────────────────────────────────────────────────" << endl;
    }
}

void RentalSystem::rentVehicle(int id, int days, string custName) {
    for (auto v : fleet) {
        if (v->getID() == id && v->isAvailable()) {
            v->setAvailable(false);
            
            double og_total = v->getRate() * days;
            double discount = 0;

            if(days > 5){
                discount = og_total * 0.10; // 10% discount logic
            }

            double final_total = og_total - discount;
            
            cout << "\n" << BOLD << GREEN << "      ★ RENTAL RECEIPT ★      " << RESET << endl;
            cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
            cout << "  Customer: " << custName << endl;
            cout << "  Vehicle : " << v->getBrand() << endl;
            cout << "  Duration: " << days << " Days" << endl;
            cout << "  Rate    : ₹" << (int)v->getRate() << "/day" << endl;
            cout << "  --------------------------" << endl;
            cout << "  Subtotal: ₹" << (int)og_total << endl;
            
            if (discount > 0) {
                cout << YELLOW << "  Discount: -₹" << (int)discount << " (Long Term)" << RESET << endl;
            }
            
            cout << BOLD << CYAN << "  NET TOTAL: ₹" << (int)final_total << RESET << endl;
            cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
            cout << GREEN << "  Drive safely! Visit again." << RESET << endl;
            return;
        }
    }
    cout << RED << "\n[Error] ID not found or already rented." << RESET << endl;
}

void RentalSystem::returnVehicle(int id) {
    for (auto v : fleet) {
        if (v->getID() == id) {
            if (!v->isAvailable()) {
                v->setAvailable(true); 
                cout << GREEN << "\n[Success] Vehicle ID " << id << " (" << v->getBrand() 
                     << ") returned successfully!" << RESET << endl;
                return;
            } else {
                cout << YELLOW << "\n[Info] This vehicle is already in the garage." << RESET << endl;
                return;
            }
        }
    }
    cout << RED << "\n[Error] Invalid Vehicle ID." << RESET << endl;
}