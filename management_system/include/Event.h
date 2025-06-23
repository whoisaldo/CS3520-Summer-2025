#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <vector>
#include <memory>
#include "User.h"

enum class RoomLayout {
    MEETING,
    LECTURE,
    WEDDING,
    DANCE
};

class Ticket;

class Event {
private:
    int eventId;
    std::string name;
    std::shared_ptr<User> organizer;
    std::string startTime;
    std::string endTime;
    double cost;
    RoomLayout layout;
    bool isPublic;
    int maxAttendees;
    std::vector<std::shared_ptr<Ticket>> tickets;
    std::vector<std::shared_ptr<User>> waitList;
    
public:
    Event(int eventId, const std::string& name, std::shared_ptr<User> organizer,
          const std::string& startTime, const std::string& endTime,
          RoomLayout layout, bool isPublic, int maxAttendees);
    ~Event();
    
    // Getters
    int getEventId() const;
    std::string getName() const;
    std::shared_ptr<User> getOrganizer() const;
    std::string getStartTime() const;
    std::string getEndTime() const;
    double getCost() const;
    RoomLayout getLayout() const;
    bool getIsPublic() const;
    int getMaxAttendees() const;
    
    // Event management
    double calculateCost();
    bool isFull() const;
    bool addToWaitlist(std::shared_ptr<User> user);
    void processWaitlist();
    bool cancelEvent();
    
    // Ticket management
    bool addTicket(std::shared_ptr<Ticket> ticket);
    std::vector<std::shared_ptr<Ticket>> getTickets() const;
    int getAvailableSeats() const;
    
    // String representation
    std::string toString() const;
};

#endif // EVENT_H

