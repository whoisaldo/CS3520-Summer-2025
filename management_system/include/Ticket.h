#ifndef TICKET_H
#define TICKET_H

#include <memory>
#include <string>

class Event;
class User;

class Ticket {
private:
    int ticketId;
    std::shared_ptr<Event> event;
    std::shared_ptr<User> holder;
    double price;
    bool isPaid;

public:
    Ticket(int ticketId, std::shared_ptr<Event> event,
           std::shared_ptr<User> holder, double price);
    ~Ticket();
    
    // Getters
    int getTicketId() const;
    std::shared_ptr<Event> getEvent() const;
    std::shared_ptr<User> getHolder() const;
    double getPrice() const;
    bool getIsPaid() const;
    
    // Ticket management
    void setPaid(bool status);
    double refund() const;
    
    // String representation
    std::string toString() const;
};

#endif // TICKET_H
