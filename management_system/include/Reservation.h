#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>
#include <memory>
#include "Event.h"
#include "User.h"

enum class ReservationStatus {
    PENDING,
    CONFIRMED,
    CANCELLED
};

class Reservation {
private:
    int reservationId;
    std::shared_ptr<Event> event;
    std::shared_ptr<User> requester;
    ReservationStatus status;
    double paymentAmount;
    std::string requestDate;
    bool isPaid;

public:
    Reservation(int reservationId, std::shared_ptr<Event> event,
                std::shared_ptr<User> requester,
                const std::string& requestDate);
    ~Reservation();
    
    // Getters
    int getReservationId() const;
    std::shared_ptr<Event> getEvent() const;
    std::shared_ptr<User> getRequester() const;
    ReservationStatus getStatus() const;
    double getPaymentAmount() const;
    std::string getRequestDate() const;
    bool getIsPaid() const;
    
    // Reservation management
    bool cancel();
    void confirm();
    double calculatePenalty() const;
    bool processPayment(double amount);
    
    // Status management
    void setStatus(ReservationStatus newStatus);
    
    // String representation
    std::string toString() const;
};

#endif // RESERVATION_H
