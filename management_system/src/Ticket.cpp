#include "../include/Ticket.h"
#include "../include/Event.h"
#include "../include/User.h"
#include <sstream>
#include <iostream>

Ticket::Ticket(int ticketId, std::shared_ptr<Event> event,
               std::shared_ptr<User> holder, double price)
    : ticketId(ticketId), event(event), holder(holder), price(price), isPaid(false) {
}

Ticket::~Ticket() = default;

int Ticket::getTicketId() const {
    return ticketId;
}

std::shared_ptr<Event> Ticket::getEvent() const {
    return event;
}

std::shared_ptr<User> Ticket::getHolder() const {
    return holder;
}

double Ticket::getPrice() const {
    return price;
}

bool Ticket::getIsPaid() const {
    return isPaid;
}

void Ticket::setPaid(bool status) {
    isPaid = status;
    if (isPaid) {
        std::cout << "Ticket #" << ticketId << " has been marked as paid" << std::endl;
    } else {
        std::cout << "Ticket #" << ticketId << " has been marked as unpaid" << std::endl;
    }
}

double Ticket::refund() const {
    if (!isPaid) {
        std::cout << "Ticket #" << ticketId << " has not been paid for, no refund necessary" << std::endl;
        return 0.0;
    }
    
    // In a real system, refund might be prorated based on event proximity
    std::cout << "Refunding $" << price << " for ticket #" << ticketId << std::endl;
    return price;
}

std::string Ticket::toString() const {
    std::ostringstream oss;
    oss << "Ticket #" << ticketId << "\n";
    oss << "Event: " << event->getName() << " (ID: " << event->getEventId() << ")\n";
    oss << "Holder: " << holder->getName() << "\n";
    oss << "Price: $" << price << "\n";
    oss << "Paid: " << (isPaid ? "Yes" : "No") << "\n";
    
    return oss.str();
}
