#include "../include/UserTypes.h"
#include "../include/Reservation.h"
#include <iostream>

// Resident implementation
Resident::Resident(const std::string& username, const std::string& password, 
                  const std::string& name, const std::string& contactInfo, 
                  const std::string& cityId)
    : User(username, password, name, contactInfo), cityId(cityId) {
}

Resident::~Resident() = default;

double Resident::getHourlyRate() const {
    // Residents get a discount
    return 50.0;
}

std::string Resident::getUserType() const {
    return "Resident";
}

std::string Resident::getCityId() const {
    return cityId;
}

// NonResident implementation
NonResident::NonResident(const std::string& username, const std::string& password, 
                         const std::string& name, const std::string& contactInfo)
    : User(username, password, name, contactInfo) {
}

NonResident::~NonResident() = default;

double NonResident::getHourlyRate() const {
    // Non-residents pay standard rate
    return 100.0;
}

std::string NonResident::getUserType() const {
    return "NonResident";
}

// Organization implementation
Organization::Organization(const std::string& username, const std::string& password, 
                          const std::string& name, const std::string& contactInfo,
                          const std::string& orgId, const std::string& orgName)
    : User(username, password, name, contactInfo), orgId(orgId), orgName(orgName) {
}

Organization::~Organization() = default;

double Organization::getHourlyRate() const {
    // Organizations get a slight discount
    return 75.0;
}

std::string Organization::getUserType() const {
    return "Organization";
}

std::string Organization::getOrgId() const {
    return orgId;
}

std::string Organization::getOrgName() const {
    return orgName;
}

// City implementation
City::City(const std::string& username, const std::string& password, 
          const std::string& name, const std::string& contactInfo,
          const std::string& departmentInfo)
    : User(username, password, name, contactInfo), departmentInfo(departmentInfo) {
}

City::~City() = default;

double City::getHourlyRate() const {
    // City officials get significant discount
    return 25.0;
}

std::string City::getUserType() const {
    return "City";
}

std::string City::getDepartmentInfo() const {
    return departmentInfo;
}

// Manager implementation
Manager::Manager(const std::string& username, const std::string& password, 
                const std::string& name, const std::string& contactInfo)
    : User(username, password, name, contactInfo) {
}

Manager::~Manager() = default;

double Manager::getHourlyRate() const {
    // Managers have no use for hourly rates, but must implement
    return 0.0;
}

std::string Manager::getUserType() const {
    return "Manager";
}

bool Manager::approveReservation(int reservationId) {
    // Implementation would interact with the system to approve reservation
    std::cout << "Manager " << getName() << " approved reservation #" << reservationId << std::endl;
    return true;
}

bool Manager::processCancellation(int reservationId) {
    // Implementation would interact with the system to process cancellation
    std::cout << "Manager " << getName() << " processed cancellation for reservation #" << reservationId << std::endl;
    return true;
}

double Manager::processRefund(int reservationId) {
    // Implementation would calculate and process a refund
    std::cout << "Manager " << getName() << " processed refund for reservation #" << reservationId << std::endl;
    return 0.0; // Placeholder
}

void Manager::manageBudget() {
    // Implementation would provide budget management functionality
    std::cout << "Manager " << getName() << " accessed budget management" << std::endl;
}

std::vector<std::shared_ptr<Reservation>> Manager::viewAllReservations() const {
    // Implementation would query the system for all reservations
    // For now, return an empty vector
    return std::vector<std::shared_ptr<Reservation>>();
}
