#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <chrono>
using namespace std;
enum class VehicleType {
    CAR,
    SUV,
    TRUCK,
    BICYCLE
};

enum class SpaceSize {
    SMALL,
    MEDIUM,
    LARGE,
    EXTRA_LARGE
};

class Vehicle {
protected:
    string licensePlate;
    VehicleType type;
    chrono::system_clock::time_point entryTime;
    chrono::system_clock::time_point exitTime;

public:
    Vehicle(const string& licensePlate, VehicleType type);
    virtual ~Vehicle() = default;
    
    const string& getLicensePlate() const;
    VehicleType getType() const;
    void setEntryTime(const chrono::system_clock::time_point& time);
    void setExitTime(const chrono::system_clock::time_point& time);
    chrono::duration<double> getParkedDuration() const;
    
    virtual SpaceSize getRequiredSpaceSize() const = 0;
    virtual void reset(); // For object pool
};

class Car : public Vehicle {
public:
    explicit Car(const string& licensePlate = "");
    SpaceSize getRequiredSpaceSize() const override;
};

class SUV : public Vehicle {
public:
    explicit SUV(const string& licensePlate = "");
    SpaceSize getRequiredSpaceSize() const override;
};

class Truck : public Vehicle {
public:
    explicit Truck(const string& licensePlate = "");
    SpaceSize getRequiredSpaceSize() const override;
};

class Bicycle : public Vehicle {
public:
    explicit Bicycle(const string& licensePlate = "");
    SpaceSize getRequiredSpaceSize() const override;
};

#endif // VEHICLE_H
