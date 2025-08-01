#ifndef PARKING_SYSTEM_H
#define PARKING_SYSTEM_H

#include "Vehicle.hpp"
#include "Customer.hpp"
#include "ObjectPool.hpp"
#include <vector>
#include <map>
#include <memory>
#include <string>
using namespace std;
class ParkingSpace {
private:
    int spaceId;
    SpaceSize size;
    bool occupied;
    Vehicle* occupyingVehicle;

public:
    ParkingSpace(int id, SpaceSize size);
    
    int getId() const;
    SpaceSize getSize() const;
    bool isAvailable() const;
    bool parkVehicle(Vehicle* vehicle);
    Vehicle* removeVehicle();
    Vehicle* getOccupyingVehicle() const;
};

class PricingStrategy {
public:
    virtual ~PricingStrategy() = default;
    virtual double calculatePrice(Vehicle* vehicle, Customer* customer) const = 0;
};

class HourlyPricing : public PricingStrategy {
private:
    map<SpaceSize, double> hourlyRates;

public:
    HourlyPricing();
    double calculatePrice(Vehicle* vehicle, Customer* customer) const override;
};

class ParkingTicket {
private:
    string ticketId;
    Vehicle* vehicle;
    Customer* customer;
    ParkingSpace* assignedSpace;
    chrono::system_clock::time_point issueTime;
    double totalCost;
    bool paid;
    static int nextTicketNumber;

public:
    ParkingTicket();
    ParkingTicket(Vehicle* vehicle, Customer* customer, ParkingSpace* space);
    
    void initialize(Vehicle* vehicle, Customer* customer, ParkingSpace* space);
    void calculateCost(const PricingStrategy* strategy);
    void markAsPaid();
    
    const string& getTicketId() const;
    double getTotalCost() const;
    Vehicle* getVehicle() const;
    bool isPaid() const;
    void reset(); // For object pool
};

class ParkingLotManager {
private:
    vector<unique_ptr<ParkingSpace>> spaces;
    map<string, ParkingTicket*> activeTickets;
    unique_ptr<PricingStrategy> pricingStrategy;
    unique_ptr<ObjectPool<ParkingTicket>> ticketPool;

public:
    ParkingLotManager();
    ~ParkingLotManager();
    
    void addParkingSpace(SpaceSize size);
    ParkingSpace* findAvailableSpace(SpaceSize requiredSize);
    ParkingTicket* parkVehicle(Vehicle* vehicle, Customer* customer);
    double removeVehicle(const string& licensePlate);
    double getOccupancyRate() const;
    void setPricingStrategy(unique_ptr<PricingStrategy> strategy);
    
    // For testing
    int getTotalSpaces() const;
    int getAvailableSpaces() const;
};

#endif // PARKING_SYSTEM_H
