#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// --- UI Color Macros ---
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

class Vehicle {
protected:
    static int static_id_counter; // ✅ Static counter for auto-increment
    int id;
    string brand;
    double rate;
    bool available;
    string type;

public:
    Vehicle(string b, double r, bool a, string t, int existing_id = 0);
    virtual ~Vehicle() {}

    int getID() const { return id; }
    string getBrand() const { return brand; }
    double getRate() const { return rate; }
    bool isAvailable() const { return available; }
    void setAvailable(bool status) { available = status; }
    string getType() const { return type; }

    static void setCounter(int val) { static_id_counter = val; }

    virtual void showSpecs() const = 0;
    virtual string toCSV() const;

    friend ostream& operator<<(ostream& os, const Vehicle& v);
};

class Car : public Vehicle {
    int seats;
    string trans;
public:
    Car(string b, double r, bool a, int s, string t, int existing_id = 0);
    void showSpecs() const override;
    string toCSV() const override;
};

class Bike : public Vehicle {
public:
    Bike(string b, double r, bool a, int existing_id = 0);
    void showSpecs() const override;
    string toCSV() const override;
};

#endif