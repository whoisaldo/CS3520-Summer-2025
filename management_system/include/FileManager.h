#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <vector>
#include <memory>
#include <string>

class User;
class Event;
class Reservation;
class Ticket;

class FileManager {
private:
    std::string usersFile;
    std::string eventsFile;
    std::string reservationsFile;
    std::string ticketsFile;
    
    // Helper methods
    std::string serializeUser(std::shared_ptr<User> user);
    std::shared_ptr<User> deserializeUser(const std::string& userData);
    
    std::string serializeEvent(std::shared_ptr<Event> event);
    std::shared_ptr<Event> deserializeEvent(const std::string& eventData, 
                                          const std::vector<std::shared_ptr<User>>& users);
    
    std::string serializeReservation(std::shared_ptr<Reservation> reservation);
    std::shared_ptr<Reservation> deserializeReservation(const std::string& reservationData,
                                                       const std::vector<std::shared_ptr<Event>>& events,
                                                       const std::vector<std::shared_ptr<User>>& users);
                                                       
    std::string serializeTicket(std::shared_ptr<Ticket> ticket);
    std::shared_ptr<Ticket> deserializeTicket(const std::string& ticketData,
                                            const std::vector<std::shared_ptr<Event>>& events,
                                            const std::vector<std::shared_ptr<User>>& users);

public:
    FileManager(const std::string& usersFile,
                const std::string& eventsFile,
                const std::string& reservationsFile,
                const std::string& ticketsFile);
    ~FileManager();
    
    // File operations
    bool saveUsers(const std::vector<std::shared_ptr<User>>& users);
    std::vector<std::shared_ptr<User>> loadUsers();
    
    bool saveEvents(const std::vector<std::shared_ptr<Event>>& events);
    std::vector<std::shared_ptr<Event>> loadEvents(const std::vector<std::shared_ptr<User>>& users);
    
    bool saveReservations(const std::vector<std::shared_ptr<Reservation>>& reservations);
    std::vector<std::shared_ptr<Reservation>> loadReservations(
        const std::vector<std::shared_ptr<Event>>& events,
        const std::vector<std::shared_ptr<User>>& users);
        
    bool saveTickets(const std::vector<std::shared_ptr<Ticket>>& tickets);
    std::vector<std::shared_ptr<Ticket>> loadTickets(
        const std::vector<std::shared_ptr<Event>>& events,
        const std::vector<std::shared_ptr<User>>& users);
        
    // Initialize with test data
    void createTestData();
};

#endif // FILE_MANAGER_H
