#include "System.h"
#include "Event.h"
#include "Reservation.h"
#include "Ticket.h"
#include "User.h"
#include "FileManager.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <filesystem>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <UserTypes.h>

// Constructor
System::System() {
    // Initialize the file manager
    fileManager = std::make_shared<FileManager>(
        "data/users.dat",
        "data/events.dat",
        "data/reservations.dat",
        "data/tickets.dat"
    );
    
    currentUser = nullptr;
}

// Destructor
System::~System() {
    // Save state when system is destroyed
    saveState();
}

// User Management Methods
std::shared_ptr<User> System::login(const std::string& username, const std::string& password) {
    for (auto& user : users) {
        if (user->getUsername() == username && user->authenticate(password)) {
            currentUser = user;
            std::cout << "Login successful. Welcome, " << user->getName() << "!" << std::endl;
            return user;
        }
    }
    
    std::cout << "Login failed. Invalid username or password." << std::endl;
    return nullptr;
}

bool System::createUser(const std::string& type, const std::string& username, const std::string& password,
                      const std::string& name, const std::string& contactInfo,
                      const std::string& additionalInfo) {
    // Check if username already exists
    for (auto& user : users) {
        if (user->getUsername() == username) {
            std::cout << "Username already exists. Please choose a different username." << std::endl;
            return false;
        }
    }
    
    std::shared_ptr<User> newUser = nullptr;
    
    if (type == "Resident") {
        newUser = std::make_shared<Resident>(username, password, name, contactInfo, additionalInfo);
    } else if (type == "NonResident") {
        newUser = std::make_shared<NonResident>(username, password, name, contactInfo);
    } else if (type == "Organization") {
        // Parse additionalInfo as "orgId|orgName"
        std::string orgId = additionalInfo;
        std::string orgName = "Default Organization";
        
        size_t pos = additionalInfo.find('|');
        if (pos != std::string::npos) {
            orgId = additionalInfo.substr(0, pos);
            orgName = additionalInfo.substr(pos + 1);
        }
        
        newUser = std::make_shared<Organization>(username, password, name, contactInfo, orgId, orgName);
    } else if (type == "City") {
        newUser = std::make_shared<City>(username, password, name, contactInfo, additionalInfo);
    } else if (type == "Manager") {
        newUser = std::make_shared<Manager>(username, password, name, contactInfo);
    } else {
        std::cout << "Invalid user type." << std::endl;
        return false;
    }
    
    users.push_back(newUser);
    std::cout << "User created successfully." << std::endl;
    return true;
}

void System::logout() {
    if (currentUser) {
        std::cout << "Goodbye, " << currentUser->getName() << "!" << std::endl;
        currentUser = nullptr;
    } else {
        std::cout << "No user is currently logged in." << std::endl;
    }
}

std::vector<std::shared_ptr<User>> System::getUsers() const {
    return users;
}

// Event Management Methods
std::shared_ptr<Event> System::createEvent(const std::string& name, 
                                         const std::string& startTime,
                                         const std::string& endTime,
                                         RoomLayout layout,
                                         bool isPublic,
                                         int maxAttendees) {
    if (!currentUser) {
        std::cout << "You must be logged in to create an event." << std::endl;
        return nullptr;
    }
    
    // Generate a unique event ID
    int eventId = 1;
    if (!events.empty()) {
        eventId = events.back()->getEventId() + 1;
    }
    
    auto event = std::make_shared<Event>(eventId, name, currentUser, startTime, endTime,
                                        layout, isPublic, maxAttendees);
    events.push_back(event);
    
    std::cout << "Event created successfully. Event ID: " << eventId << std::endl;
    return event;
}

std::vector<std::shared_ptr<Event>> System::getEvents() const {
    return events;
}

std::shared_ptr<Event> System::findEvent(int eventId) const {
    for (auto& event : events) {
        if (event->getEventId() == eventId) {
            return event;
        }
    }
    return nullptr;
}

// Reservation Management Methods
std::shared_ptr<Reservation> System::createReservation(int eventId) {
    if (!currentUser) {
        std::cout << "You must be logged in to create a reservation." << std::endl;
        return nullptr;
    }
    
    auto event = findEvent(eventId);
    if (!event) {
        std::cout << "Event not found." << std::endl;
        return nullptr;
    }
    
    // Generate a unique reservation ID
    int reservationId = 1;
    if (!reservations.empty()) {
        reservationId = reservations.back()->getReservationId() + 1;
    }
    
    // Get current date
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");
    std::string currentDate = ss.str();
    
    auto reservation = std::make_shared<Reservation>(reservationId, event, currentUser, currentDate);
    reservations.push_back(reservation);
    
    std::cout << "Reservation created successfully. Reservation ID: " << reservationId << std::endl;
    std::cout << "Total amount due: $" << reservation->getPaymentAmount() << std::endl;
    
    return reservation;
}

std::vector<std::shared_ptr<Reservation>> System::getReservations() const {
    return reservations;
}

std::shared_ptr<Reservation> System::findReservation(int reservationId) const {
    for (auto& reservation : reservations) {
        if (reservation->getReservationId() == reservationId) {
            return reservation;
        }
    }
    return nullptr;
}

// Ticket Management Methods
std::shared_ptr<Ticket> System::purchaseTicket(int eventId) {
    if (!currentUser) {
        std::cout << "You must be logged in to purchase a ticket." << std::endl;
        return nullptr;
    }
    
    auto event = findEvent(eventId);
    if (!event) {
        std::cout << "Event not found." << std::endl;
        return nullptr;
    }
    
    if (!event->getIsPublic()) {
        std::cout << "This event is not open for public ticket sales." << std::endl;
        return nullptr;
    }
    
    if (event->isFull()) {
        std::cout << "This event is full. Would you like to be added to the waitlist? (y/n): ";
        char response;
        std::cin >> response;
        
        if (response == 'y' || response == 'Y') {
            if (event->addToWaitlist(currentUser)) {
                std::cout << "You have been added to the waitlist." << std::endl;
            } else {
                std::cout << "You are already on the waitlist." << std::endl;
            }
        }
        
        return nullptr;
    }
    
    // Generate a unique ticket ID
    int ticketId = 1;
    if (!tickets.empty()) {
        ticketId = tickets.back()->getTicketId() + 1;
    }
    
    // Calculate ticket price based on event type and user type
    double basePrice = 25.0;
    if (event->getLayout() == RoomLayout::WEDDING) basePrice = 50.0;
    if (event->getLayout() == RoomLayout::DANCE) basePrice = 40.0;
    
    // Apply user type discount
    double userDiscount = 1.0;
    if (currentUser->getUserType() == "Resident") userDiscount = 0.8;
    if (currentUser->getUserType() == "Organization") userDiscount = 0.9;
    
    double finalPrice = basePrice * userDiscount;
    
    auto ticket = std::make_shared<Ticket>(ticketId, event, currentUser, finalPrice);
    tickets.push_back(ticket);
    
    // Add ticket to event
    event->addTicket(ticket);
    
    std::cout << "Ticket purchased successfully. Ticket ID: " << ticketId << std::endl;
    std::cout << "Price: $" << finalPrice << std::endl;
    
    // Process payment
    std::cout << "Processing payment of $" << finalPrice << "... ";
    ticket->setPaid(true);
    std::cout << "Payment complete." << std::endl;
    
    return ticket;
}

bool System::returnTicket(int ticketId) {
    if (!currentUser) {
        std::cout << "You must be logged in to return a ticket." << std::endl;
        return false;
    }
    
    // Find the ticket
    auto it = std::find_if(tickets.begin(), tickets.end(), 
                         [ticketId](const auto& ticket) { return ticket->getTicketId() == ticketId; });
    
    if (it == tickets.end()) {
        std::cout << "Ticket not found." << std::endl;
        return false;
    }
    
    auto ticket = *it;
    
    // Check if the current user owns the ticket
    if (ticket->getHolder()->getUserId() != currentUser->getUserId()) {
        std::cout << "You can only return tickets that you own." << std::endl;
        return false;
    }
    
    // Process refund
    double refundAmount = ticket->refund();
    
    // Remove the ticket
    tickets.erase(it);
    
    std::cout << "Ticket returned successfully. Refund amount: $" << refundAmount << std::endl;
    
    // Process waitlist for the event
    ticket->getEvent()->processWaitlist();
    
    return true;
}

std::vector<std::shared_ptr<Ticket>> System::getTickets() const {
    return tickets;
}

// System Management Methods
void System::saveState() {
    std::cout << "Saving system state..." << std::endl;
    
    // Create data directory if it doesn't exist
    if (!std::filesystem::exists("data")) {
        std::filesystem::create_directory("data");
    }
    
    bool usersSaved = fileManager->saveUsers(users);
    bool eventsSaved = fileManager->saveEvents(events);
    bool reservationsSaved = fileManager->saveReservations(reservations);
    bool ticketsSaved = fileManager->saveTickets(tickets);
    
    if (usersSaved && eventsSaved && reservationsSaved && ticketsSaved) {
        std::cout << "System state saved successfully." << std::endl;
    } else {
        std::cout << "Error saving system state." << std::endl;
    }
}

bool System::loadState() {
    std::cout << "Loading system state..." << std::endl;
    
    // Create data directory if it doesn't exist
    if (!std::filesystem::exists("data")) {
        std::filesystem::create_directory("data");
    }
    
    users = fileManager->loadUsers();
    events = fileManager->loadEvents(users);
    reservations = fileManager->loadReservations(events, users);
    tickets = fileManager->loadTickets(events, users);
    
    if (users.empty() && events.empty() && reservations.empty() && tickets.empty()) {
        std::cout << "No existing data found. Creating test data..." << std::endl;
        fileManager->createTestData();
        
        // Reload after creating test data
        users = fileManager->loadUsers();
        events = fileManager->loadEvents(users);
        reservations = fileManager->loadReservations(events, users);
        tickets = fileManager->loadTickets(events, users);
    }
    
    std::cout << "System state loaded successfully." << std::endl;
    std::cout << "Loaded " << users.size() << " users, " << events.size() << " events, "
              << reservations.size() << " reservations, and " << tickets.size() << " tickets." << std::endl;
    
    return true;
}

void System::displayMainMenu() {
    if (!currentUser) {
        std::cout << "\n=== Convention Center Management System ===" << std::endl;
        std::cout << "1. Login" << std::endl;
        std::cout << "2. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        
        int choice;
        std::cin >> choice;
        
        switch (choice) {
            case 1: {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::string username, password;
                std::cout << "Username: ";
                std::getline(std::cin, username);
                std::cout << "Password: ";
                std::getline(std::cin, password);
                login(username, password);
                break;
            }
            case 2:
                std::cout << "Goodbye!" << std::endl;
                exit(0);
                break;
            default:
                std::cout << "Invalid choice." << std::endl;
                break;
        }
    } else {
        std::string userType = currentUser->getUserType();
        
        if (userType == "Resident") {
            displayResidentMenu();
        } else if (userType == "NonResident") {
            displayNonResidentMenu();
        } else if (userType == "Organization") {
            displayOrganizationMenu();
        } else if (userType == "City") {
            displayCityMenu();
        } else if (userType == "Manager") {
            displayManagerMenu();
        } else {
            std::cout << "Invalid user type." << std::endl;
            logout();
        }
    }
}

void System::displayResidentMenu() {
    std::cout << "\n=== Resident Menu ===" << std::endl;
    std::cout << "1. View Available Events" << std::endl;
    std::cout << "2. View My Tickets" << std::endl;
    std::cout << "3. Purchase Ticket" << std::endl;
    std::cout << "4. Return Ticket" << std::endl;
    std::cout << "5. Create Reservation Request" << std::endl;
    std::cout << "6. View My Reservations" << std::endl;
    std::cout << "7. Logout" << std::endl;
    std::cout << "Enter your choice: ";
    
    int choice;
    std::cin >> choice;
    
    switch (choice) {
        case 1: {
            std::cout << "\n=== Available Events ===" << std::endl;
            for (const auto& event : events) {
                if (event->getIsPublic()) {
                    std::cout << "Event ID: " << event->getEventId() << " - " << event->getName() << std::endl;
                    std::cout << "Date: " << event->getStartTime() << " to " << event->getEndTime() << std::endl;
                    std::cout << "Available seats: " << event->getAvailableSeats() << "/" << event->getMaxAttendees() << std::endl;
                    std::cout << "-------------------------------------" << std::endl;
                }
            }
            break;
        }
        case 2: {
            std::cout << "\n=== My Tickets ===" << std::endl;
            bool hasTickets = false;
            for (const auto& ticket : tickets) {
                if (ticket->getHolder()->getUserId() == currentUser->getUserId()) {
                    hasTickets = true;
                    std::cout << "Ticket ID: " << ticket->getTicketId() << std::endl;
                    std::cout << "Event: " << ticket->getEvent()->getName() << std::endl;
                    std::cout << "Date: " << ticket->getEvent()->getStartTime() << std::endl;
                    std::cout << "Price: $" << ticket->getPrice() << std::endl;
                    std::cout << "Paid: " << (ticket->getIsPaid() ? "Yes" : "No") << std::endl;
                    std::cout << "-------------------------------------" << std::endl;
                }
            }
            if (!hasTickets) {
                std::cout << "You don't have any tickets." << std::endl;
            }
            break;
        }
        case 3: {
            std::cout << "Enter event ID: ";
            int eventId;
            std::cin >> eventId;
            purchaseTicket(eventId);
            break;
        }
        case 4: {
            std::cout << "Enter ticket ID: ";
            int ticketId;
            std::cin >> ticketId;
            returnTicket(ticketId);
            break;
        }
        case 5: {
            std::cout << "\n=== Available Spaces for Reservation ===" << std::endl;
            for (const auto& event : events) {
                // Show only events organized by the current user or public spaces
                if (!event->getIsPublic()) {
                    std::cout << "Space ID: " << event->getEventId() << " - Available for private booking" << std::endl;
                    std::cout << "-------------------------------------" << std::endl;
                }
            }
            
            std::cout << "Enter space ID to reserve: ";
            int eventId;
            std::cin >> eventId;
            createReservation(eventId);
            break;
        }
        case 6: {
            std::cout << "\n=== My Reservations ===" << std::endl;
            bool hasReservations = false;
            for (const auto& reservation : reservations) {
                if (reservation->getRequester()->getUserId() == currentUser->getUserId()) {
                    hasReservations = true;
                    std::cout << "Reservation ID: " << reservation->getReservationId() << std::endl;
                    std::cout << "Event: " << reservation->getEvent()->getName() << std::endl;
                    std::cout << "Date: " << reservation->getEvent()->getStartTime() << std::endl;
                    std::cout << "Status: ";
                    switch (reservation->getStatus()) {
                        case ReservationStatus::PENDING: std::cout << "Pending"; break;
                        case ReservationStatus::CONFIRMED: std::cout << "Confirmed"; break;
                        case ReservationStatus::CANCELLED: std::cout << "Cancelled"; break;
                    }
                    std::cout << std::endl;
                    std::cout << "Amount: $" << reservation->getPaymentAmount() << std::endl;
                    std::cout << "Paid: " << (reservation->getIsPaid() ? "Yes" : "No") << std::endl;
                    std::cout << "-------------------------------------" << std::endl;
                }
            }
            if (!hasReservations) {
                std::cout << "You don't have any reservations." << std::endl;
            }
            break;
        }
        case 7:
            logout();
            break;
        default:
            std::cout << "Invalid choice." << std::endl;
            break;
    }
}

void System::displayNonResidentMenu() {
    // Similar to resident menu but with different pricing
    displayResidentMenu();  // For simplicity, reuse resident menu
}

void System::displayOrganizationMenu() {
    std::cout << "\n=== Organization Menu ===" << std::endl;
    std::cout << "1. View Profile" << std::endl;
    std::cout << "2. Update Profile" << std::endl;
    std::cout << "3. View Events" << std::endl;
    std::cout << "4. Create Event" << std::endl;
    std::cout << "5. View Reservations" << std::endl;
    std::cout << "6. Create Reservation" << std::endl;
    std::cout << "7. Logout" << std::endl;
    std::cout << "Enter your choice: ";
    
    int choice;
    std::cin >> choice;
    
    switch (choice) {
        case 1: {
            // View profile
            std::cout << "=== Profile Information ===" << std::endl;
            std::cout << "Name: " << currentUser->getName() << std::endl;
            std::cout << "Contact: " << currentUser->getContactInfo() << std::endl;
            std::cout << "Organization ID: " << currentUser->getContactInfo() << std::endl;
            std::cout << "-------------------------------------" << std::endl;
            break;
        }
        case 2: {
            // Update profile
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            std::string name;
            std::cout << "Enter new name: ";
            std::getline(std::cin, name);
            
            std::string contactInfo;
            std::cout << "Enter new contact info: ";
            std::getline(std::cin, contactInfo);
            
            currentUser->setName(name);
            currentUser->setContactInfo(contactInfo);
            std::cout << "Profile updated successfully." << std::endl;
            break;
        }
        case 3: {
            // View events
            std::cout << "\n=== Your Events ===" << std::endl;
            for (const auto& event : events) {
                if (event->getOrganizer()->getUserId() == currentUser->getUserId()) {
                    std::cout << "Event ID: " << event->getEventId() << " - " << event->getName() << std::endl;
                    std::cout << "Date: " << event->getStartTime() << " to " << event->getEndTime() << std::endl;
                    std::cout << "Public: " << (event->getIsPublic() ? "Yes" : "No") << std::endl;
                    std::cout << "Available seats: " << event->getAvailableSeats() << "/" << event->getMaxAttendees() << std::endl;
                    std::cout << "-------------------------------------" << std::endl;
                }
            }
            break;
        }
        case 4: {
            // Create event
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            std::string name;
            std::cout << "Enter event name: ";
            std::getline(std::cin, name);
            
            std::string startTime;
            std::cout << "Enter start time (YYYY-MM-DD HH:MM): ";
            std::getline(std::cin, startTime);
            
            std::string endTime;
            std::cout << "Enter end time (YYYY-MM-DD HH:MM): ";
            std::getline(std::cin, endTime);
            
            std::cout << "Select layout:" << std::endl;
            std::cout << "0. Meeting" << std::endl;
            std::cout << "1. Lecture" << std::endl;
            std::cout << "2. Wedding" << std::endl;
            std::cout << "3. Dance" << std::endl;
            
            int layoutChoice;
            std::cin >> layoutChoice;
            RoomLayout layout = static_cast<RoomLayout>(layoutChoice);
            
            std::cout << "Is this a public event? (1 for yes, 0 for no): ";
            int isPublicChoice;
            std::cin >> isPublicChoice;
            bool isPublic = (isPublicChoice == 1);
            
            std::cout << "Enter maximum number of attendees: ";
            int maxAttendees;
            std::cin >> maxAttendees;
            
            createEvent(name, startTime, endTime, layout, isPublic, maxAttendees);
            break;
        }
        case 5: {
            // View reservations
            std::cout << "\n=== Your Reservations ===" << std::endl;
            for (const auto& reservation : reservations) {
                if (reservation->getRequester()->getUserId() == currentUser->getUserId()) {
                    std::cout << "Reservation ID: " << reservation->getReservationId() << std::endl;
                    std::cout << "Event: " << reservation->getEvent()->getName() << std::endl;
                    std::cout << "Status: ";
                    switch (reservation->getStatus()) {
                        case ReservationStatus::PENDING: std::cout << "Pending"; break;
                        case ReservationStatus::CONFIRMED: std::cout << "Confirmed"; break;
                        case ReservationStatus::CANCELLED: std::cout << "Cancelled"; break;
                    }
                    std::cout << std::endl;
                    std::cout << "Amount: $" << reservation->getPaymentAmount() << std::endl;
                    std::cout << "Paid: " << (reservation->getIsPaid() ? "Yes" : "No") << std::endl;
                    std::cout << "-------------------------------------" << std::endl;
                }
            }
            break;
        }
        case 6: {
            // Create reservation
            std::cout << "\n=== Create Reservation ===" << std::endl;
            std::cout << "Enter event ID: ";
            int eventId;
            std::cin >> eventId;
            
            // Check if event exists and is not full
            auto event = findEvent(eventId);
            if (!event) {
                std::cout << "Event not found." << std::endl;
                break;
            }
            
            if (event->getIsPublic() || event->getAvailableSeats() > 0) {
                createReservation(eventId);
            } else {
                std::cout << "No available seats for this event." << std::endl;
            }
            break;
        }
        case 7:
            logout();
            break;
        default:
            std::cout << "Invalid choice." << std::endl;
            break;
    }
}

void System::displayCityMenu() {
    std::cout << "\n=== City Official Menu ===" << std::endl;
    std::cout << "1. View All Events" << std::endl;
    std::cout << "2. Create New Event" << std::endl;
    std::cout << "3. View All Reservations" << std::endl;
    std::cout << "4. Create Reservation Request" << std::endl;
    std::cout << "5. Logout" << std::endl;
    std::cout << "Enter your choice: ";
    
    int choice;
    std::cin >> choice;
    
    switch (choice) {
        case 1: {
            std::cout << "\n=== All Events ===" << std::endl;
            for (const auto& event : events) {
                std::cout << "Event ID: " << event->getEventId() << " - " << event->getName() << std::endl;
                std::cout << "Organizer: " << event->getOrganizer()->getName() << std::endl;
                std::cout << "Date: " << event->getStartTime() << " to " << event->getEndTime() << std::endl;
                std::cout << "Public: " << (event->getIsPublic() ? "Yes" : "No") << std::endl;
                std::cout << "Available seats: " << event->getAvailableSeats() << "/" << event->getMaxAttendees() << std::endl;
                std::cout << "-------------------------------------" << std::endl;
            }
            break;
        }
        case 2: {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            std::string name;
            std::cout << "Enter event name: ";
            std::getline(std::cin, name);
            
            std::string startTime;
            std::cout << "Enter start time (YYYY-MM-DD HH:MM): ";
            std::getline(std::cin, startTime);
            
            std::string endTime;
            std::cout << "Enter end time (YYYY-MM-DD HH:MM): ";
            std::getline(std::cin, endTime);
            
            std::cout << "Select layout:" << std::endl;
            std::cout << "0. Meeting" << std::endl;
            std::cout << "1. Lecture" << std::endl;
            std::cout << "2. Wedding" << std::endl;
            std::cout << "3. Dance" << std::endl;
            
            int layoutChoice;
            std::cin >> layoutChoice;
            RoomLayout layout = static_cast<RoomLayout>(layoutChoice);
            
            std::cout << "Is this a public event? (1 for yes, 0 for no): ";
            int isPublicChoice;
            std::cin >> isPublicChoice;
            bool isPublic = (isPublicChoice == 1);
            
            std::cout << "Enter maximum number of attendees: ";
            int maxAttendees;
            std::cin >> maxAttendees;
            
            createEvent(name, startTime, endTime, layout, isPublic, maxAttendees);
            break;
        }
        case 3: {
            std::cout << "\n=== All Reservations ===" << std::endl;
            if (reservations.empty()) {
                std::cout << "There are no reservations in the system." << std::endl;
            }
            else {
                for (const auto& reservation : reservations) {
                    std::cout << "Reservation ID: " << reservation->getReservationId() << std::endl;
                    std::cout << "Event: " << reservation->getEvent()->getName() << std::endl;
                    std::cout << "Requester: " << reservation->getRequester()->getName() << std::endl;
                    std::cout << "Status: ";
                    switch (reservation->getStatus()) {
                        case ReservationStatus::PENDING: std::cout << "Pending"; break;
                        case ReservationStatus::CONFIRMED: std::cout << "Confirmed"; break;
                        case ReservationStatus::CANCELLED: std::cout << "Cancelled"; break;
                    }
                    std::cout << std::endl;
                    std::cout << "Amount: $" << reservation->getPaymentAmount() << std::endl;
                    std::cout << "Paid: " << (reservation->getIsPaid() ? "Yes" : "No") << std::endl;
                    std::cout << "-------------------------------------" << std::endl;
                }
            }
            break;
        }
        case 4: {
            std::cout << "\n=== Available Spaces for Reservation ===" << std::endl;
            bool hasAvailableSpaces = false;
            for (const auto& event : events) {
                if (!event->getIsPublic()) {
                    hasAvailableSpaces = true;
                    std::cout << "Space ID: " << event->getEventId() << " - Available for private booking" << std::endl;
                    std::cout << "-------------------------------------" << std::endl;
                }
            }
            
            if (!hasAvailableSpaces) {
                std::cout << "No spaces available for reservation." << std::endl;
                break;
            }
            
            std::cout << "Enter space ID to reserve: ";
            int eventId;
            std::cin >> eventId;
            createReservation(eventId);
            break;
        }
        case 5:
            logout();
            break;
        default:
            std::cout << "Invalid choice." << std::endl;
            break;
    }
}

void System::displayManagerMenu() {
    std::cout << "\n=== Manager Menu ===" << std::endl;
    std::cout << "1. View All Users" << std::endl;
    std::cout << "2. View All Events" << std::endl;
    std::cout << "3. View All Reservations" << std::endl;
    std::cout << "4. View All Tickets" << std::endl;
    std::cout << "5. Create New Event" << std::endl;
    std::cout << "6. Process Reservation" << std::endl;
    std::cout << "7. Create New User" << std::endl;
    std::cout << "8. Save System State" << std::endl;
    std::cout << "9. Create Test Data" << std::endl;
    std::cout << "10. Logout" << std::endl;
    std::cout << "Enter your choice: ";
    
    int choice;
    std::cin >> choice;
    
    switch (choice) {
        case 1: {
            std::cout << "\n=== All Users ===" << std::endl;
            for (const auto& user : users) {
                std::cout << "User ID: " << user->getUserId() << std::endl;
                std::cout << "Username: " << user->getUsername() << std::endl;
                std::cout << "Name: " << user->getName() << std::endl;
                std::cout << "Type: " << user->getUserType() << std::endl;
                std::cout << "Contact: " << user->getContactInfo() << std::endl;
                std::cout << "-------------------------------------" << std::endl;
            }
            break;
        }
        case 2: {
            std::cout << "\n=== All Events ===" << std::endl;
            for (const auto& event : events) {
                std::cout << "Event ID: " << event->getEventId() << " - " << event->getName() << std::endl;
                std::cout << "Organizer: " << event->getOrganizer()->getName() << std::endl;
                std::cout << "Date: " << event->getStartTime() << " to " << event->getEndTime() << std::endl;
                std::cout << "Public: " << (event->getIsPublic() ? "Yes" : "No") << std::endl;
                std::cout << "Capacity: " << event->getAvailableSeats() << "/" << event->getMaxAttendees() << std::endl;
                std::cout << "Cost: $" << event->getCost() << std::endl;
                std::cout << "-------------------------------------" << std::endl;
            }
            break;
        }
        case 3: {
            std::cout << "\n=== All Reservations ===" << std::endl;
            if (reservations.empty()) {
                std::cout << "There are no reservations in the system." << std::endl;
            }
            else {
                for (const auto& reservation : reservations) {
                    std::cout << "Reservation ID: " << reservation->getReservationId() << std::endl;
                    std::cout << "Event: " << reservation->getEvent()->getName() << std::endl;
                    std::cout << "Requester: " << reservation->getRequester()->getName() << std::endl;
                    std::cout << "Status: ";
                    switch (reservation->getStatus()) {
                        case ReservationStatus::PENDING: std::cout << "Pending"; break;
                        case ReservationStatus::CONFIRMED: std::cout << "Confirmed"; break;
                        case ReservationStatus::CANCELLED: std::cout << "Cancelled"; break;
                    }
                    std::cout << std::endl;
                    std::cout << "Amount: $" << reservation->getPaymentAmount() << std::endl;
                    std::cout << "Paid: " << (reservation->getIsPaid() ? "Yes" : "No") << std::endl;
                    std::cout << "-------------------------------------" << std::endl;
                }
            }
            break;
        }
        case 4: {
            std::cout << "\n=== All Tickets ===" << std::endl;
            if (tickets.empty()) {
                std::cout << "There are no tickets in the system." << std::endl;
            }
            else {
                for (const auto& ticket : tickets) {
                    std::cout << "Ticket ID: " << ticket->getTicketId() << std::endl;
                    std::cout << "Event: " << ticket->getEvent()->getName() << std::endl;
                    std::cout << "Holder: " << ticket->getHolder()->getName() << std::endl;
                    std::cout << "Price: $" << ticket->getPrice() << std::endl;
                    std::cout << "Paid: " << (ticket->getIsPaid() ? "Yes" : "No") << std::endl;
                    std::cout << "-------------------------------------" << std::endl;
                }
            }
            break;
        }
        case 5: {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            std::string name;
            std::cout << "Enter event name: ";
            std::getline(std::cin, name);
            
            std::string startTime;
            std::cout << "Enter start time (YYYY-MM-DD HH:MM): ";
            std::getline(std::cin, startTime);
            
            std::string endTime;
            std::cout << "Enter end time (YYYY-MM-DD HH:MM): ";
            std::getline(std::cin, endTime);
            
            std::cout << "Select layout:" << std::endl;
            std::cout << "0. Meeting" << std::endl;
            std::cout << "1. Lecture" << std::endl;
            std::cout << "2. Wedding" << std::endl;
            std::cout << "3. Dance" << std::endl;
            
            int layoutChoice;
            std::cin >> layoutChoice;
            RoomLayout layout = static_cast<RoomLayout>(layoutChoice);
            
            std::cout << "Is this a public event? (1 for yes, 0 for no): ";
            int isPublicChoice;
            std::cin >> isPublicChoice;
            bool isPublic = (isPublicChoice == 1);
            
            std::cout << "Enter maximum number of attendees: ";
            int maxAttendees;
            std::cin >> maxAttendees;
            
            createEvent(name, startTime, endTime, layout, isPublic, maxAttendees);
            break;
        }
        case 6: {
            std::cout << "Enter reservation ID: ";
            int reservationId;
            std::cin >> reservationId;
            
            auto reservation = findReservation(reservationId);
            if (!reservation) {
                std::cout << "Reservation not found." << std::endl;
                break;
            }
            
            std::cout << "Reservation details:" << std::endl;
            std::cout << "ID: " << reservation->getReservationId() << std::endl;
            std::cout << "Event: " << reservation->getEvent()->getName() << std::endl;
            std::cout << "Requester: " << reservation->getRequester()->getName() << std::endl;
            std::cout << "Status: ";
            switch (reservation->getStatus()) {
                case ReservationStatus::PENDING: std::cout << "Pending"; break;
                case ReservationStatus::CONFIRMED: std::cout << "Confirmed"; break;
                case ReservationStatus::CANCELLED: std::cout << "Cancelled"; break;
            }
            std::cout << std::endl;
            std::cout << "Amount: $" << reservation->getPaymentAmount() << std::endl;
            std::cout << "Paid: " << (reservation->getIsPaid() ? "Yes" : "No") << std::endl;
            
            std::cout << "Actions:" << std::endl;
            std::cout << "1. Approve Reservation" << std::endl;
            std::cout << "2. Cancel Reservation" << std::endl;
            std::cout << "3. Process Payment" << std::endl;
            std::cout << "Enter action: ";
            
            int action;
            std::cin >> action;
            
            switch (action) {
                case 1:
                    if (reservation->getStatus() == ReservationStatus::PENDING) {
                        reservation->confirm();
                    } else {
                        std::cout << "Reservation is not in pending state." << std::endl;
                    }
                    break;
                case 2:
                    reservation->cancel();
                    break;
                case 3:
                    if (!reservation->getIsPaid()) {
                        double amount = reservation->getPaymentAmount();
                        std::cout << "Processing payment of $" << amount << "... ";
                        reservation->processPayment(amount);
                    } else {
                        std::cout << "Reservation is already paid." << std::endl;
                    }
                    break;
                default:
                    std::cout << "Invalid action." << std::endl;
            }
            break;
        }
        case 7: {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            std::cout << "Select user type:" << std::endl;
            std::cout << "1. Resident" << std::endl;
            std::cout << "2. NonResident" << std::endl;
            std::cout << "3. Organization" << std::endl;
            std::cout << "4. City Official" << std::endl;
            std::cout << "5. Manager" << std::endl;
            
            int typeChoice;
            std::cin >> typeChoice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            std::string type;
            switch (typeChoice) {
                case 1: type = "Resident"; break;
                case 2: type = "NonResident"; break;
                case 3: type = "Organization"; break;
                case 4: type = "City"; break;
                case 5: type = "Manager"; break;
                default:
                    std::cout << "Invalid type." << std::endl;
                    return;
            }
            
            std::string username;
            std::cout << "Enter username: ";
            std::getline(std::cin, username);
            
            std::string password;
            std::cout << "Enter password: ";
            std::getline(std::cin, password);
            
            std::string name;
            std::cout << "Enter name: ";
            std::getline(std::cin, name);
            
            std::string contactInfo;
            std::cout << "Enter contact info: ";
            std::getline(std::cin, contactInfo);
            
            std::string additionalInfo;
            if (type == "Resident") {
                std::cout << "Enter city ID: ";
                std::getline(std::cin, additionalInfo);
            } else if (type == "Organization") {
                std::string orgId;
                std::cout << "Enter organization ID: ";
                std::getline(std::cin, orgId);
                
                std::string orgName;
                std::cout << "Enter organization name: ";
                std::getline(std::cin, orgName);
                
                additionalInfo = orgId + "|" + orgName;
            } else if (type == "City") {
                std::cout << "Enter department info: ";
                std::getline(std::cin, additionalInfo);
            }
            
            createUser(type, username, password, name, contactInfo, additionalInfo);
            break;
        }
        case 8:
            saveState();
            break;
        case 9:
            fileManager->createTestData();
            loadState();
            break;
        case 10:
            logout();
            break;
        default:
            std::cout << "Invalid choice." << std::endl;
            break;
    }
}

void System::run() {
    while (true) {
        displayMainMenu();
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}