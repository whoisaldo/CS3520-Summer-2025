/* 
 * Author:  Ali Younes & Ali Tleis 
 * Course:  CS3520
 * Date:    6/17/2025
 * Assignment 6: Automatic Parking Lot + Object Pool
 */
#include "Vehicle.hpp"
using namespace std;
Vehicle::Vehicle(const string& licensePlate, VehicleType type)
    : licensePlate(licensePlate), type(type) {
    entryTime = chrono::system_clock::now();
}

const string& Vehicle::getLicensePlate() const {
    return licensePlate;
}

VehicleType Vehicle::getType() const {
    return type;
}

void Vehicle::setEntryTime(const chrono::system_clock::time_point& time) {
    entryTime = time;
}

void Vehicle::setExitTime(const chrono::system_clock::time_point& time) {
    exitTime = time;
}

chrono::duration<double> Vehicle::getParkedDuration() const {
    auto endTime = (exitTime.time_since_epoch().count() == 0) ? 
                   chrono::system_clock::now() : exitTime;
    return endTime - entryTime;
}

void Vehicle::reset() {
    licensePlate.clear();
    entryTime = chrono::system_clock::now();
    exitTime = chrono::system_clock::time_point{};
}

// Car implementation
Car::Car(const string& licensePlate) 
    : Vehicle(licensePlate, VehicleType::CAR) {}

SpaceSize Car::getRequiredSpaceSize() const {
    return SpaceSize::MEDIUM;
}

// SUV implementation
SUV::SUV(const string& licensePlate) 
    : Vehicle(licensePlate, VehicleType::SUV) {}

SpaceSize SUV::getRequiredSpaceSize() const {
    return SpaceSize::LARGE;
}

// Truck implementation
Truck::Truck(const string& licensePlate) 
    : Vehicle(licensePlate, VehicleType::TRUCK) {}

SpaceSize Truck::getRequiredSpaceSize() const {
    return SpaceSize::EXTRA_LARGE;
}

// Bicycle implementation
Bicycle::Bicycle(const string& licensePlate) 
    : Vehicle(licensePlate, VehicleType::BICYCLE) {}

SpaceSize Bicycle::getRequiredSpaceSize() const {
    return SpaceSize::SMALL;
}
