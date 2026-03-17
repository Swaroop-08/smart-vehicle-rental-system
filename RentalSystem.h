#ifndef RENTALSYSTEM_H
#define RENTALSYSTEM_H

#include <vector>
#include <fstream>
#include <sstream>
#include "Vehicle.h"

class RentalSystem {
private:
    vector<Vehicle*> fleet;
    const string filename = "database.csv";

public:
    ~RentalSystem();
    void addVehicle(Vehicle* v);
    void displayFleet(bool adminView);
    void rentVehicle(int id, int days, string custName);
    void returnVehicle(int id); // ✅ New Function
    
    void saveToFile();
    void loadFromFile();
};

#endif