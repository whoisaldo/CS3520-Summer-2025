#include "ParkingSystem.hpp"
#include "Vehicle.hpp"
#include "Customer.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <memory>

using namespace std;

void testBasicParkingFunctionality() {
    cout << "\n=== Testing Basic Parking Functionality ===\n";
    
    ParkingLotManager manager;
    
    // Create vehicles
    auto car = make_unique<Car>("ABC123");
    auto suv = make_unique<SUV>("XYZ789");
    auto truck = make_unique<Truck>("TRK456");
    auto bike = make_unique<Bicycle>("BIK001");
    
    // Create customers
    auto regularCustomer = make_unique<RegularCustomer>("C001", "John Doe", "john@email.com");
    auto commuterCustomer = make_unique<CommuterCustomer>("C002", "Jane Smith", "jane@email.com");
    auto employeeCustomer = make_unique<EmployeeCustomer>("C003", "Bob Wilson", "bob@email.com", "EMP123");
    
    commuterCustomer->setMonthlyPass(true);
    
    cout << "Total spaces: " << manager.getTotalSpaces() << "\n";
    cout << "Available spaces: " << manager.getAvailableSpaces() << "\n";
    
    // Park vehicles
    ParkingTicket* ticket1 = manager.parkVehicle(car.get(), regularCustomer.get());
    ParkingTicket* ticket2 = manager.parkVehicle(suv.get(), commuterCustomer.get());
    ParkingTicket* ticket3 = manager.parkVehicle(truck.get(), employeeCustomer.get());
    ParkingTicket* ticket4 = manager.parkVehicle(bike.get(), regularCustomer.get());
    
    if (ticket1) {
        cout << "Car parked successfully. Ticket: " << ticket1->getTicketId() 
                  << ", Cost: $" << ticket1->getTotalCost() << "\n";
    }
    
    if (ticket2) {
        cout << "SUV parked successfully. Ticket: " << ticket2->getTicketId() 
                  << ", Cost: $" << ticket2->getTotalCost() << "\n";
    }
    
    if (ticket3) {
        cout << "Truck parked successfully. Ticket: " << ticket3->getTicketId() 
                  << ", Cost: $" << ticket3->getTotalCost() << "\n";
    }
    
    if (ticket4) {
        cout << "Bicycle parked successfully. Ticket: " << ticket4->getTicketId() 
                  << ", Cost: $" << ticket4->getTotalCost() << "\n";
    }
    
    cout << "Available spaces after parking: " << manager.getAvailableSpaces() << "\n";
    cout << "Occupancy rate: " << (manager.getOccupancyRate() * 100) << "%\n";
    
    // Simulate some time passing
    this_thread::sleep_for(chrono::seconds(2));
    
    // Remove vehicles
    double cost1 = manager.removeVehicle("ABC123");
    double cost2 = manager.removeVehicle("XYZ789");
    
    cout << "Car removal cost: $" << cost1 << "\n";
    cout << "SUV removal cost: $" << cost2 << "\n";
    
    cout << "Available spaces after removal: " << manager.getAvailableSpaces() << "\n";
}

void testCustomerDiscounts() {
    cout << "\n=== Testing Customer Discounts ===\n";
    
    ParkingLotManager manager;
    
    auto car1 = make_unique<Car>("REG001");
    auto car2 = make_unique<Car>("COM001");
    auto car3 = make_unique<Car>("EMP001");
    
    auto regularCustomer = make_unique<RegularCustomer>("R001", "Regular Customer", "reg@email.com");
    auto commuterCustomer = make_unique<CommuterCustomer>("C001", "Commuter Customer", "com@email.com");
    auto employeeCustomer = make_unique<EmployeeCustomer>("E001", "Employee Customer", "emp@email.com", "EMP001");
    
    commuterCustomer->setMonthlyPass(true);
    
    // Park vehicles and compare costs
    ParkingTicket* regTicket = manager.parkVehicle(car1.get(), regularCustomer.get());
    ParkingTicket* comTicket = manager.parkVehicle(car2.get(), commuterCustomer.get());
    ParkingTicket* empTicket = manager.parkVehicle(car3.get(), employeeCustomer.get());
    
    cout << "Regular Customer discount: " << (regularCustomer->getDiscountRate() * 100) << "%\n";
    cout << "Commuter Customer discount: " << (commuterCustomer->getDiscountRate() * 100) << "%\n";
    cout << "Employee Customer discount: " << (employeeCustomer->getDiscountRate() * 100) << "%\n";
    
    if (regTicket) cout << "Regular customer cost: $" << regTicket->getTotalCost() << "\n";
    if (comTicket) cout << "Commuter customer cost: $" << comTicket->getTotalCost() << "\n";
    if (empTicket) cout << "Employee customer cost: $" << empTicket->getTotalCost() << "\n";
}

void testVehicleTypes() {
    cout << "\n=== Testing Different Vehicle Types ===\n";
    
    ParkingLotManager manager;
    auto customer = make_unique<RegularCustomer>("TEST", "Test Customer", "test@email.com");
    
    // Test different vehicle types
    auto car = make_unique<Car>("CAR001");
    auto suv = make_unique<SUV>("SUV001");
    auto truck = make_unique<Truck>("TRK001");
    auto bike = make_unique<Bicycle>("BIK001");
    
    cout << "Car required space: " << static_cast<int>(car->getRequiredSpaceSize()) << "\n";
    cout << "SUV required space: " << static_cast<int>(suv->getRequiredSpaceSize()) << "\n";
    cout << "Truck required space: " << static_cast<int>(truck->getRequiredSpaceSize()) << "\n";
    cout << "Bicycle required space: " << static_cast<int>(bike->getRequiredSpaceSize()) << "\n";
    
    // Park all vehicles
    ParkingTicket* carTicket = manager.parkVehicle(car.get(), customer.get());
    ParkingTicket* suvTicket = manager.parkVehicle(suv.get(), customer.get());
    ParkingTicket* truckTicket = manager.parkVehicle(truck.get(), customer.get());
    ParkingTicket* bikeTicket = manager.parkVehicle(bike.get(), customer.get());
    
    if (carTicket) cout << "Car parking cost: $" << carTicket->getTotalCost() << "\n";
    if (suvTicket) cout << "SUV parking cost: $" << suvTicket->getTotalCost() << "\n";
    if (truckTicket) cout << "Truck parking cost: $" << truckTicket->getTotalCost() << "\n";
    if (bikeTicket) cout << "Bicycle parking cost: $" << bikeTicket->getTotalCost() << "\n";
}

void testObjectPoolInParkingSystem() {
    cout << "\n=== Testing Object Pool in Parking System ===\n";
    
    ParkingLotManager manager;
    vector<unique_ptr<Vehicle>> vehicles;
    vector<unique_ptr<Customer>> customers;
    vector<ParkingTicket*> tickets;
    
    // Create multiple vehicles and customers
    for (int i = 0; i < 20; ++i) {
        vehicles.push_back(make_unique<Car>("CAR" + to_string(i)));
        customers.push_back(make_unique<RegularCustomer>(
            "CUST" + to_string(i), 
            "Customer " + to_string(i), 
            "customer" + to_string(i) + "@email.com"
        ));
    }
    
    // Park all vehicles (tests object pool allocation)
    cout << "Parking 20 vehicles...\n";
    for (int i = 0; i < 20; ++i) {
        ParkingTicket* ticket = manager.parkVehicle(vehicles[i].get(), customers[i].get());
        if (ticket) {
            tickets.push_back(ticket);
        }
    }
    
    cout << "Parked " << tickets.size() << " vehicles\n";
    cout << "Occupancy rate: " << (manager.getOccupancyRate() * 100) << "%\n";
    
    // Remove half of the vehicles (tests object pool return)
    cout << "Removing 10 vehicles...\n";
    for (int i = 0; i < 10; ++i) {
        double cost = manager.removeVehicle(vehicles[i]->getLicensePlate());
        cout << "Removed vehicle " << i << ", cost: $" << cost << "\n";
    }
    
    cout << "Occupancy rate after removal: " << (manager.getOccupancyRate() * 100) << "%\n";
}

void stressTest() {
    cout << "\n=== Stress Test ===\n";
    
    ParkingLotManager manager;
    const int numVehicles = 100;
    
    vector<unique_ptr<Vehicle>> vehicles;
    vector<unique_ptr<Customer>> customers;
    
    // Create vehicles and customers
    for (int i = 0; i < numVehicles; ++i) {
        if (i % 4 == 0) vehicles.push_back(make_unique<Car>("V" + to_string(i)));
        else if (i % 4 == 1) vehicles.push_back(make_unique<SUV>("V" + to_string(i)));
        else if (i % 4 == 2) vehicles.push_back(make_unique<Truck>("V" + to_string(i)));
        else vehicles.push_back(make_unique<Bicycle>("V" + to_string(i)));
        
        if (i % 3 == 0) customers.push_back(make_unique<RegularCustomer>("C" + to_string(i), "Customer", "email"));
        else if (i % 3 == 1) customers.push_back(make_unique<CommuterCustomer>("C" + to_string(i), "Customer", "email"));
        else customers.push_back(make_unique<EmployeeCustomer>("C" + to_string(i), "Customer", "email", "EMP"));
    }
    
    auto start = chrono::high_resolution_clock::now();
    
    // Park all vehicles
    int parkedCount = 0;
    for (int i = 0; i < numVehicles; ++i) {
        ParkingTicket* ticket = manager.parkVehicle(vehicles[i].get(), customers[i].get());
        if (ticket) parkedCount++;
    }
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    
    cout << "Parked " << parkedCount << " out of " << numVehicles << " vehicles\n";
    cout << "Time taken: " << duration.count() << " milliseconds\n";
    cout << "Final occupancy rate: " << (manager.getOccupancyRate() * 100) << "%\n";
}

int main() {
    cout << "Parking System Testing Program\n";
    cout << "===============================\n";
    
    testBasicParkingFunctionality();
    testCustomerDiscounts();
    testVehicleTypes();
    testObjectPoolInParkingSystem();
    stressTest();
    
    cout << "\n=== All parking system tests completed! ===\n";
    return 0;
}
