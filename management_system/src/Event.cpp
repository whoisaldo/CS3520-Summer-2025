#include "../include/Event.h"
#include "../include/Ticket.h"
#include <iostream>
#include <sstream>

Event::Event(int eventId, const std::string& name, std::shared_ptr<User> organizer,
             const std::string& startTime, const std::string& endTime,
             RoomLayout layout, bool isPublic, int maxAttendees)
    : eventId(eventId), name(name), organizer(organizer), startTime(startTime),
      endTime(endTime), layout(layout), isPublic(isPublic), maxAttendees(maxAttendees) {
    // Calculate cost based on user type and duration
    calculateCost();
}

Event::~Event() = default;

int Event::getEventId() const {
    return eventId;
}

std::string Event::getName() const {
    return name;
}

std::shared_ptr<User> Event::getOrganizer() const {
    return organizer;
}

std::string Event::getStartTime() const {
    return startTime;
}

std::string Event::getEndTime() const {
    return endTime;
}

double Event::getCost() const {
    return cost;
}

RoomLayout Event::getLayout() const {
    return layout;
}

bool Event::getIsPublic() const {
    return isPublic;
}

int Event::getMaxAttendees() const {
    return maxAttendees;
}

double Event::calculateCost() {
    // Basic calculation based on duration and user type
    // For simplicity, assume times are in the format "YYYY-MM-DD HH:MM"
    // and calculate hours as a fixed value based on layout
    int hours = 0;
    switch (layout) {
        case RoomLayout::MEETING: hours = 2; break;
        case RoomLayout::LECTURE: hours = 3; break;
        case RoomLayout::WEDDING: hours = 6; break;
        case RoomLayout::DANCE: hours = 4; break;
    }
    
    double hourlyRate = organizer->getHourlyRate();
    cost = hours * hourlyRate;
    
    // Add costs for additional services based on layout
    if (layout == RoomLayout::WEDDING) cost += 500;  // Wedding setup fee
    if (layout == RoomLayout::DANCE) cost += 250;    // Sound system fee
    
    return cost;
}

bool Event::isFull() const {
    return tickets.size() >= static_cast<size_t>(maxAttendees);
}

bool Event::addToWaitlist(std::shared_ptr<User> user) {
    // Check if user is already in waitlist
    for (auto& u : waitList) {
        if (u->getUserId() == user->getUserId()) {
            return false;
        }
    }
    
    waitList.push_back(user);
    std::cout << "User " << user->getName() << " added to waitlist for event " << name << std::endl;
    return true;
}

void Event::processWaitlist() {
    while (!waitList.empty() && !isFull()) {
        auto user = waitList.front();
        waitList.erase(waitList.begin());
        
        // Create a ticket for this user
        // Note: This would normally be done through the system
        std::cout << "Processing waitlist: User " << user->getName() 
                  << " can now purchase a ticket for event " << name << std::endl;
    }
}

bool Event::cancelEvent() {
    std::cout << "Event " << name << " has been cancelled" << std::endl;
    
    // Process refunds for all ticket holders
    for (auto& ticket : tickets) {
        double refundAmount = ticket->refund();
        std::cout << "Refunded $" << refundAmount << " to " << ticket->getHolder()->getName() << std::endl;
    }
    
    tickets.clear();
    waitList.clear();
    
    return true;
}

bool Event::addTicket(std::shared_ptr<Ticket> ticket) {
    if (isFull()) {
        return false;
    }
    
    tickets.push_back(ticket);
    return true;
}

std::vector<std::shared_ptr<Ticket>> Event::getTickets() const {
    return tickets;
}

int Event::getAvailableSeats() const {
    return maxAttendees - static_cast<int>(tickets.size());
}

std::string Event::toString() const {
    std::ostringstream oss;
    oss << "Event #" << eventId << ": " << name << "\n";
    oss << "Organized by: " << organizer->getName() << "\n";
    oss << "Time: " << startTime << " to " << endTime << "\n";
    oss << "Layout: ";
    switch (layout) {
        case RoomLayout::MEETING: oss << "Meeting"; break;
        case RoomLayout::LECTURE: oss << "Lecture"; break;
        case RoomLayout::WEDDING: oss << "Wedding"; break;
        case RoomLayout::DANCE: oss << "Dance"; break;
    }
    oss << "\n";
    oss << "Cost: $" << cost << "\n";
    oss << "Public event: " << (isPublic ? "Yes" : "No") << "\n";
    oss << "Capacity: " << tickets.size() << "/" << maxAttendees << "\n";
    oss << "Waitlist size: " << waitList.size() << "\n";
    
    return oss.str();
}

