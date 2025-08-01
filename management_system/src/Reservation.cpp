#include "../include/Reservation.h"
#include <iostream>
#include <sstream>

Reservation::Reservation(int reservationId, std::shared_ptr<Event> event,
                         std::shared_ptr<User> requester, const std::string& requestDate)
    : reservationId(reservationId), event(event), requester(requester),
      status(ReservationStatus::PENDING), requestDate(requestDate), isPaid(false) {
    
    // Calculate payment amount based on event cost
    paymentAmount = event->getCost();
}

Reservation::~Reservation() = default;

int Reservation::getReservationId() const {
    return reservationId;
}

std::shared_ptr<Event> Reservation::getEvent() const {
    return event;
}

std::shared_ptr<User> Reservation::getRequester() const {
    return requester;
}

ReservationStatus Reservation::getStatus() const {
    return status;
}

double Reservation::getPaymentAmount() const {
    return paymentAmount;
}

std::string Reservation::getRequestDate() const {
    return requestDate;
}

bool Reservation::getIsPaid() const {
    return isPaid;
}

bool Reservation::cancel() {
    // Check if cancellation is allowed based on status
    if (status == ReservationStatus::CANCELLED) {
        std::cout << "Reservation #" << reservationId << " is already cancelled" << std::endl;
        return false;
    }
    
    status = ReservationStatus::CANCELLED;
    std::cout << "Reservation #" << reservationId << " has been cancelled" << std::endl;
    
    // Calculate and apply any cancellation penalties
    double penalty = calculatePenalty();
    if (penalty > 0 && isPaid) {
        std::cout << "Cancellation penalty: $" << penalty << std::endl;
        // Process refund of paymentAmount - penalty
        double refundAmount = paymentAmount - penalty;
        std::cout << "Refund amount: $" << refundAmount << std::endl;
    }
    
    return true;
}

void Reservation::confirm() {
    status = ReservationStatus::CONFIRMED;
    std::cout << "Reservation #" << reservationId << " has been confirmed" << std::endl;
}

double Reservation::calculatePenalty() const {
    // Simplified penalty calculation
    // In a real system, this would depend on how close to the event date the cancellation is
    if (status != ReservationStatus::CANCELLED) {
        return 0.0;
    }
    
    // For now, use a flat 10% cancellation fee
    return paymentAmount * 0.1;
}

bool Reservation::processPayment(double amount) {
    // Check if payment matches the required amount
    if (amount < paymentAmount) {
        std::cout << "Payment amount insufficient. Required: $" << paymentAmount << std::endl;
        return false;
    }
    
    isPaid = true;
    std::cout << "Payment of $" << amount << " processed for reservation #" << reservationId << std::endl;
    
    // Automatically confirm the reservation if payment is complete
    if (status == ReservationStatus::PENDING) {
        confirm();
    }
    
    return true;
}

void Reservation::setStatus(ReservationStatus newStatus) {
    status = newStatus;
}

std::string Reservation::toString() const {
    std::ostringstream oss;
    oss << "Reservation #" << reservationId << "\n";
    oss << "Event: " << event->getName() << " (ID: " << event->getEventId() << ")\n";
    oss << "Requester: " << requester->getName() << "\n";
    oss << "Request Date: " << requestDate << "\n";
    oss << "Status: ";
    
    switch (status) {
        case ReservationStatus::PENDING: oss << "Pending"; break;
        case ReservationStatus::CONFIRMED: oss << "Confirmed"; break;
        case ReservationStatus::CANCELLED: oss << "Cancelled"; break;
    }
    
    oss << "\n";
    oss << "Payment Amount: $" << paymentAmount << "\n";
    oss << "Paid: " << (isPaid ? "Yes" : "No") << "\n";
    
    return oss.str();
}
