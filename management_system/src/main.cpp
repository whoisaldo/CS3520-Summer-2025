#include <iostream>
#include <memory>
#include <filesystem>
#include "../include/System.h"

void createDataDirectory() {
    // Create the data directory if it doesn't exist
    std::filesystem::path dataDir = "data";
    if (!std::filesystem::exists(dataDir)) {
        std::filesystem::create_directory(dataDir);
        std::cout << "Created data directory." << std::endl;
    }
}

void printWelcomeBanner() {
    std::cout << "*************************************************" << std::endl;
    std::cout << "*                                               *" << std::endl;
    std::cout << "*  CONVENTION CENTER MANAGEMENT SYSTEM          *" << std::endl;
    std::cout << "*                                               *" << std::endl;
    std::cout << "*  A comprehensive solution for managing        *" << std::endl;
    std::cout << "*  events, reservations, and ticketing.         *" << std::endl;
    std::cout << "*                                               *" << std::endl;
    std::cout << "*************************************************" << std::endl;
    std::cout << std::endl;
    
    std::cout << "Default Login Credentials:" << std::endl;
    std::cout << "-------------------------" << std::endl;
    std::cout << "Manager: username='manager', password='password'" << std::endl;
    std::cout << "Resident: username='resident1', password='password'" << std::endl;
    std::cout << "NonResident: username='nonresident1', password='password'" << std::endl;
    std::cout << "Organization: username='organization1', password='password'" << std::endl;
    std::cout << "City Official: username='city1', password='password'" << std::endl;
    std::cout << std::endl;
}

int main() {
    try {
        // Setup environment
        createDataDirectory();
        
        // Display welcome banner
        printWelcomeBanner();
        
        // Create and start the system
        std::unique_ptr<System> system = std::make_unique<System>();
        
        // Load the system state or create test data if no state exists
        if (!system->loadState()) {
            std::cout << "No previous system state found. Creating test data..." << std::endl;
            
            // Add a manager user for initial access
            system->createUser("Manager", "admin", "admin123", "System Administrator", "admin@convention.com");
            
            std::cout << "Initial setup complete. You can login as:" << std::endl;
            std::cout << "Username: admin" << std::endl;
            std::cout << "Password: admin123" << std::endl;
        }
        
        // Run the main program loop
        system->run();
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "ERROR: Unknown exception occurred." << std::endl;
        return 1;
    }
}
