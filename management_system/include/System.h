#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <memory>
#include <string>
#include <map>
#include "User.h"
#include "Event.h"
#include "Reservation.h"
#include "Ticket.h"
#include "FileManager.h"

class System {
private:
    std::vector<std::shared_ptr<User>> users;
    std::vector<std::shared_ptr<Event>> events;
    std::vector<std::shared_ptr<Reservation>> reservations;
    std::vector<std::shared_ptr<Ticket>> tickets;
    std::shared_ptr<FileManager> fileManager;
    std::shared_ptr<User> currentUser;
    
    // Helper methods
    void displayResidentMenu();
    void displayNonResidentMenu();
    void displayOrganizationMenu();
    void displayCityMenu();
    void displayManagerMenu();

public:
    System();
    ~System();
    
    // User management
    std::shared_ptr<User> login(const std::string& username, const std::string& password);
    bool createUser(const std::string& type, const std::string& username, const std::string& password,
                   const std::string& name, const std::string& contactInfo,
                   const std::string& additionalInfo = "");
    void logout();
    std::vector<std::shared_ptr<User>> getUsers() const;
    
    // Event management
    std::shared_ptr<Event> createEvent(const std::string& name, 
                                      const std::string& startTime,
                                      const std::string& endTime,
                                      RoomLayout layout,
                                      bool isPublic,
                                      int maxAttendees);
    std::vector<std::shared_ptr<Event>> getEvents() const;
    std::shared_ptr<Event> findEvent(int eventId) const;
    
    // Reservation management
    std::shared_ptr<Reservation> createReservation(int eventId);
    std::vector<std::shared_ptr<Reservation>> getReservations() const;
    std::shared_ptr<Reservation> findReservation(int reservationId) const;
    
    // Ticket management
    std::shared_ptr<Ticket> purchaseTicket(int eventId);
    bool returnTicket(int ticketId);
    std::vector<std::shared_ptr<Ticket>> getTickets() const;
    
    // System management
    void saveState();
    bool loadState();
    void displayMainMenu();
    void run();
};

#endif // SYSTEM_H
