#include "ParkingSystem.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

// ParkingSpace implementation
ParkingSpace::ParkingSpace(int id, SpaceSize size) 
    : spaceId(id), size(size), occupied(false), occupyingVehicle(nullptr) {}

int ParkingSpace::getId() const {
    return spaceId;
}

SpaceSize ParkingSpace::getSize() const {
    return size;
}

bool ParkingSpace::isAvailable() const {
    return !occupied;
}

bool ParkingSpace::parkVehicle(Vehicle* vehicle) {
    if (occupied || !vehicle) return false;
    
    SpaceSize requiredSize = vehicle->getRequiredSpaceSize();
    if (static_cast<int>(size) < static_cast<int>(requiredSize)) {
        return false;
    }
    
    occupied = true;
    occupyingVehicle = vehicle;
    vehicle->setEntryTime(chrono::system_clock::now());
    return true;
}

Vehicle* ParkingSpace::removeVehicle() {
    if (!occupied) return nullptr;
    
    Vehicle* vehicle = occupyingVehicle;
    occupied = false;
    occupyingVehicle = nullptr;
    
    if (vehicle) {
        vehicle->setExitTime(chrono::system_clock::now());
    }
    
    return vehicle;
}

Vehicle* ParkingSpace::getOccupyingVehicle() const {
    return occupyingVehicle;
}

// HourlyPricing implementation
HourlyPricing::HourlyPricing() {
    hourlyRates[SpaceSize::SMALL] = 2.0;
    hourlyRates[SpaceSize::MEDIUM] = 3.0;
    hourlyRates[SpaceSize::LARGE] = 4.0;
    hourlyRates[SpaceSize::EXTRA_LARGE] = 5.0;
}

double HourlyPricing::calculatePrice(Vehicle* vehicle, Customer* customer) const {
    if (!vehicle || !customer) return 0.0;
    
    double duration = vehicle->getParkedDuration().count() / 3600.0; // Convert to hours
    duration = max(duration, 1.0); // Minimum 1 hour
    
    SpaceSize spaceSize = vehicle->getRequiredSpaceSize();
    double baseRate = hourlyRates.at(spaceSize);
    double totalCost = baseRate * duration;
    
    // Apply customer discount
    double discount = customer->getDiscountRate();
    totalCost *= (1.0 - discount);
    
    return totalCost;
}

// ParkingTicket implementation
int ParkingTicket::nextTicketNumber = 1;

ParkingTicket::ParkingTicket() 
    : vehicle(nullptr), customer(nullptr), assignedSpace(nullptr), 
      totalCost(0.0), paid(false) {}

ParkingTicket::ParkingTicket(Vehicle* vehicle, Customer* customer, ParkingSpace* space)
    : vehicle(vehicle), customer(customer), assignedSpace(space), 
      totalCost(0.0), paid(false) {
    
    stringstream ss;
    ss << "TKT" << setfill('0') << setw(6) << nextTicketNumber++;
    ticketId = ss.str();
    issueTime = chrono::system_clock::now();
}

void ParkingTicket::initialize(Vehicle* vehicle, Customer* customer, ParkingSpace* space) {
    this->vehicle = vehicle;
    this->customer = customer;
    this->assignedSpace = space;
    this->totalCost = 0.0;
    this->paid = false;
    
    stringstream ss;
    ss << "TKT" << setfill('0') << setw(6) << nextTicketNumber++;
    ticketId = ss.str();
    issueTime = chrono::system_clock::now();
}

void ParkingTicket::calculateCost(const PricingStrategy* strategy) {
    if (strategy && vehicle && customer) {
        totalCost = strategy->calculatePrice(vehicle, customer);
    }
}

void ParkingTicket::markAsPaid() {
    paid = true;
}

const string& ParkingTicket::getTicketId() const {
    return ticketId;
}

double ParkingTicket::getTotalCost() const {
    return totalCost;
}

Vehicle* ParkingTicket::getVehicle() const {
    return vehicle;
}

bool ParkingTicket::isPaid() const {
    return paid;
}

void ParkingTicket::reset() {
    ticketId.clear();
    vehicle = nullptr;
    customer = nullptr;
    assignedSpace = nullptr;
    totalCost = 0.0;
    paid = false;
}

// ParkingLotManager implementation
ParkingLotManager::ParkingLotManager() 
    : pricingStrategy(make_unique<HourlyPricing>()),
      ticketPool(make_unique<ObjectPool<ParkingTicket>>(10)) {
    
    // Initialize with some parking spaces
    for (int i = 0; i < 20; ++i) {
        addParkingSpace(SpaceSize::SMALL);
    }
    for (int i = 0; i < 30; ++i) {
        addParkingSpace(SpaceSize::MEDIUM);
    }
    for (int i = 0; i < 15; ++i) {
        addParkingSpace(SpaceSize::LARGE);
    }
    for (int i = 0; i < 5; ++i) {
        addParkingSpace(SpaceSize::EXTRA_LARGE);
    }
}

ParkingLotManager::~ParkingLotManager() {
    // Return all active tickets to pool
    for (auto& pair : activeTickets) {
        ticketPool->return_object(pair.second);
    }
}

void ParkingLotManager::addParkingSpace(SpaceSize size) {
    int id = spaces.size() + 1;
    spaces.push_back(make_unique<ParkingSpace>(id, size));
}

ParkingSpace* ParkingLotManager::findAvailableSpace(SpaceSize requiredSize) {
    for (auto& space : spaces) {
        if (space->isAvailable() && 
            static_cast<int>(space->getSize()) >= static_cast<int>(requiredSize)) {
            return space.get();
        }
    }
    return nullptr;
}

ParkingTicket* ParkingLotManager::parkVehicle(Vehicle* vehicle, Customer* customer) {
    if (!vehicle || !customer) return nullptr;
    
    SpaceSize requiredSize = vehicle->getRequiredSpaceSize();
    ParkingSpace* space = findAvailableSpace(requiredSize);
    
    if (!space) {
        cout << "No available space for vehicle type\n";
        return nullptr;
    }
    
    if (!space->parkVehicle(vehicle)) {
        cout << "Failed to park vehicle\n";
        return nullptr;
    }
    
    ParkingTicket* ticket = ticketPool->get_object();
    ticket->initialize(vehicle, customer, space);
    ticket->calculateCost(pricingStrategy.get());
    
    activeTickets[vehicle->getLicensePlate()] = ticket;
    
    return ticket;
}

double ParkingLotManager::removeVehicle(const string& licensePlate) {
    auto it = activeTickets.find(licensePlate);
    if (it == activeTickets.end()) {
        cout << "Ticket not found for license plate: " << licensePlate << "\n";
        return 0.0;
    }
    
    ParkingTicket* ticket = it->second;
    Vehicle* vehicle = ticket->getVehicle();
    
    // Find and remove vehicle from space
    for (auto& space : spaces) {
        if (space->getOccupyingVehicle() == vehicle) {
            space->removeVehicle();
            break;
        }
    }
    
    // Recalculate cost based on actual time
    ticket->calculateCost(pricingStrategy.get());
    double totalCost = ticket->getTotalCost();
    
    // Return ticket to pool and remove from active tickets
    ticketPool->return_object(ticket);
    activeTickets.erase(it);
    
    return totalCost;
}

double ParkingLotManager::getOccupancyRate() const {
    int totalSpaces = spaces.size();
    int occupiedSpaces = 0;
    
    for (const auto& space : spaces) {
        if (!space->isAvailable()) {
            occupiedSpaces++;
        }
    }
    
    return totalSpaces > 0 ? static_cast<double>(occupiedSpaces) / totalSpaces : 0.0;
}

void ParkingLotManager::setPricingStrategy(unique_ptr<PricingStrategy> strategy) {
    pricingStrategy = move(strategy);
}

int ParkingLotManager::getTotalSpaces() const {
    return spaces.size();
}

int ParkingLotManager::getAvailableSpaces() const {
    int available = 0;
    for (const auto& space : spaces) {
        if (space->isAvailable()) {
            available++;
        }
    }
    return available;
}
