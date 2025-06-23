#include "../include/FileManager.h"
#include "../include/UserTypes.h"
#include "../include/Event.h"
#include "../include/Reservation.h"
#include "../include/Ticket.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

FileManager::FileManager(const std::string& usersFile, const std::string& eventsFile,
                         const std::string& reservationsFile, const std::string& ticketsFile)
    : usersFile(usersFile), eventsFile(eventsFile), 
      reservationsFile(reservationsFile), ticketsFile(ticketsFile) {
}

FileManager::~FileManager() = default;

bool FileManager::saveUsers(const std::vector<std::shared_ptr<User>>& users) {
    std::ofstream file(usersFile);
    if (!file) {
        std::cerr << "Failed to open file for writing: " << usersFile << std::endl;
        return false;
    }
    
    for (const auto& user : users) {
        file << serializeUser(user) << std::endl;
    }
    
    return true;
}

std::vector<std::shared_ptr<User>> FileManager::loadUsers() {
    std::vector<std::shared_ptr<User>> users;
    std::ifstream file(usersFile);
    
    if (!file) {
        std::cerr << "Failed to open file for reading: " << usersFile << std::endl;
        return users;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        auto user = deserializeUser(line);
        if (user) {
            users.push_back(user);
        }
    }
    
    return users;
}

bool FileManager::saveEvents(const std::vector<std::shared_ptr<Event>>& events) {
    std::ofstream file(eventsFile);
    if (!file) {
        std::cerr << "Failed to open file for writing: " << eventsFile << std::endl;
        return false;
    }
    
    for (const auto& event : events) {
        file << serializeEvent(event) << std::endl;
    }
    
    return true;
}

std::vector<std::shared_ptr<Event>> FileManager::loadEvents(
    const std::vector<std::shared_ptr<User>>& users) {
    std::vector<std::shared_ptr<Event>> events;
    std::ifstream file(eventsFile);
    
    if (!file) {
        std::cerr << "Failed to open file for reading: " << eventsFile << std::endl;
        return events;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        auto event = deserializeEvent(line, users);
        if (event) {
            events.push_back(event);
        }
    }
    
    return events;
}

bool FileManager::saveReservations(const std::vector<std::shared_ptr<Reservation>>& reservations) {
    std::ofstream file(reservationsFile);
    if (!file) {
        std::cerr << "Failed to open file for writing: " << reservationsFile << std::endl;
        return false;
    }
    
    for (const auto& reservation : reservations) {
        file << serializeReservation(reservation) << std::endl;
    }
    
    return true;
}

std::vector<std::shared_ptr<Reservation>> FileManager::loadReservations(
    const std::vector<std::shared_ptr<Event>>& events,
    const std::vector<std::shared_ptr<User>>& users) {
    std::vector<std::shared_ptr<Reservation>> reservations;
    std::ifstream file(reservationsFile);
    
    if (!file) {
        std::cerr << "Failed to open file for reading: " << reservationsFile << std::endl;
        return reservations;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        auto reservation = deserializeReservation(line, events, users);
        if (reservation) {
            reservations.push_back(reservation);
        }
    }
    
    return reservations;
}

bool FileManager::saveTickets(const std::vector<std::shared_ptr<Ticket>>& tickets) {
    std::ofstream file(ticketsFile);
    if (!file) {
        std::cerr << "Failed to open file for writing: " << ticketsFile << std::endl;
        return false;
    }
    
    for (const auto& ticket : tickets) {
        file << serializeTicket(ticket) << std::endl;
    }
    
    return true;
}

std::vector<std::shared_ptr<Ticket>> FileManager::loadTickets(
    const std::vector<std::shared_ptr<Event>>& events,
    const std::vector<std::shared_ptr<User>>& users) {
    std::vector<std::shared_ptr<Ticket>> tickets;
    std::ifstream file(ticketsFile);
    
    if (!file) {
        std::cerr << "Failed to open file for reading: " << ticketsFile << std::endl;
        return tickets;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        auto ticket = deserializeTicket(line, events, users);
        if (ticket) {
            tickets.push_back(ticket);
        }
    }
    
    return tickets;
}

std::string FileManager::serializeUser(std::shared_ptr<User> user) {
    std::ostringstream oss;
    
    oss << user->getUserType() << "|";
    oss << user->getUserId() << "|";
    oss << user->getUsername() << "|";
    oss << user->getName() << "|";
    oss << user->getContactInfo() << "|";
    
    // Add type-specific data
    if (user->getUserType() == "Resident") {
        auto resident = std::dynamic_pointer_cast<Resident>(user);
        oss << resident->getCityId();
    } else if (user->getUserType() == "Organization") {
        auto org = std::dynamic_pointer_cast<Organization>(user);
        oss << org->getOrgId() << "|" << org->getOrgName();
    } else if (user->getUserType() == "City") {
        auto city = std::dynamic_pointer_cast<City>(user);
        oss << city->getDepartmentInfo();
    }
    
    return oss.str();
}

std::shared_ptr<User> FileManager::deserializeUser(const std::string& userData) {
    std::istringstream iss(userData);
    std::string type, idStr, username, name, contactInfo, extraInfo1, extraInfo2;
    
    std::getline(iss, type, '|');
    std::getline(iss, idStr, '|');
    std::getline(iss, username, '|');
    std::getline(iss, name, '|');
    std::getline(iss, contactInfo, '|');
    
    // For simplicity, we're using a fixed password "password" for loaded users
    std::string password = "password";
    
    std::shared_ptr<User> user;
    
    if (type == "Resident") {
        std::getline(iss, extraInfo1); // cityId
        user = std::make_shared<Resident>(username, password, name, contactInfo, extraInfo1);
    } else if (type == "NonResident") {
        user = std::make_shared<NonResident>(username, password, name, contactInfo);
    } else if (type == "Organization") {
        std::getline(iss, extraInfo1, '|'); // orgId
        std::getline(iss, extraInfo2); // orgName
        user = std::make_shared<Organization>(username, password, name, contactInfo, extraInfo1, extraInfo2);
    } else if (type == "City") {
        std::getline(iss, extraInfo1); // departmentInfo
        user = std::make_shared<City>(username, password, name, contactInfo, extraInfo1);
    } else if (type == "Manager") {
        user = std::make_shared<Manager>(username, password, name, contactInfo);
    } else {
        std::cerr << "Unknown user type: " << type << std::endl;
        return nullptr;
    }
    
    return user;
}

std::string FileManager::serializeEvent(std::shared_ptr<Event> event) {
    std::ostringstream oss;
    
    oss << event->getEventId() << "|";
    oss << event->getName() << "|";
    oss << event->getOrganizer()->getUserId() << "|";
    oss << event->getStartTime() << "|";
    oss << event->getEndTime() << "|";
    oss << static_cast<int>(event->getLayout()) << "|";
    oss << (event->getIsPublic() ? "1" : "0") << "|";
    oss << event->getMaxAttendees();
    
    return oss.str();
}

std::shared_ptr<Event> FileManager::deserializeEvent(
    const std::string& eventData,
    const std::vector<std::shared_ptr<User>>& users) {
    std::istringstream iss(eventData);
    std::string idStr, name, organizerIdStr, startTime, endTime;
    std::string layoutStr, isPublicStr, maxAttendeesStr;
    
    std::getline(iss, idStr, '|');
    std::getline(iss, name, '|');
    std::getline(iss, organizerIdStr, '|');
    std::getline(iss, startTime, '|');
    std::getline(iss, endTime, '|');
    std::getline(iss, layoutStr, '|');
    std::getline(iss, isPublicStr, '|');
    std::getline(iss, maxAttendeesStr);
    
    int id = std::stoi(idStr);
    int organizerId = std::stoi(organizerIdStr);
    RoomLayout layout = static_cast<RoomLayout>(std::stoi(layoutStr));
    bool isPublic = (isPublicStr == "1");
    int maxAttendees = std::stoi(maxAttendeesStr);
    
    // Find the organizer
    std::shared_ptr<User> organizer = nullptr;
    for (const auto& user : users) {
        if (user->getUserId() == organizerId) {
            organizer = user;
            break;
        }
    }
    
    if (!organizer) {
        std::cerr << "Organizer not found for event: " << name << std::endl;
        return nullptr;
    }
    
    auto event = std::make_shared<Event>(id, name, organizer, startTime, endTime,
                                        layout, isPublic, maxAttendees);
    return event;
}

std::string FileManager::serializeReservation(std::shared_ptr<Reservation> reservation) {
    std::ostringstream oss;
    
    oss << reservation->getReservationId() << "|";
    oss << reservation->getEvent()->getEventId() << "|";
    oss << reservation->getRequester()->getUserId() << "|";
    oss << static_cast<int>(reservation->getStatus()) << "|";
    oss << reservation->getPaymentAmount() << "|";
    oss << reservation->getRequestDate() << "|";
    oss << (reservation->getIsPaid() ? "1" : "0");
    
    return oss.str();
}

std::shared_ptr<Reservation> FileManager::deserializeReservation(
    const std::string& reservationData,
    const std::vector<std::shared_ptr<Event>>& events,
    const std::vector<std::shared_ptr<User>>& users) {
    std::istringstream iss(reservationData);
    std::string idStr, eventIdStr, requesterIdStr, statusStr;
    std::string paymentAmountStr, requestDate, isPaidStr;
    
    std::getline(iss, idStr, '|');
    std::getline(iss, eventIdStr, '|');
    std::getline(iss, requesterIdStr, '|');
    std::getline(iss, statusStr, '|');
    std::getline(iss, paymentAmountStr, '|');
    std::getline(iss, requestDate, '|');
    std::getline(iss, isPaidStr);
    
    int id = std::stoi(idStr);
    int eventId = std::stoi(eventIdStr);
    int requesterId = std::stoi(requesterIdStr);
    ReservationStatus status = static_cast<ReservationStatus>(std::stoi(statusStr));
    double paymentAmount = std::stod(paymentAmountStr);
    bool isPaid = (isPaidStr == "1");
    
    // Find the event and requester
    std::shared_ptr<Event> event = nullptr;
    for (const auto& e : events) {
        if (e->getEventId() == eventId) {
            event = e;
            break;
        }
    }
    
    std::shared_ptr<User> requester = nullptr;
    for (const auto& user : users) {
        if (user->getUserId() == requesterId) {
            requester = user;
            break;
        }
    }
    
    if (!event || !requester) {
        std::cerr << "Event or requester not found for reservation: " << id << std::endl;
        return nullptr;
    }
    
    auto reservation = std::make_shared<Reservation>(id, event, requester, requestDate);
    reservation->setStatus(status);
    if (isPaid) {
        reservation->processPayment(paymentAmount);
    }
    
    return reservation;
}

std::string FileManager::serializeTicket(std::shared_ptr<Ticket> ticket) {
    std::ostringstream oss;
    
    oss << ticket->getTicketId() << "|";
    oss << ticket->getEvent()->getEventId() << "|";
    oss << ticket->getHolder()->getUserId() << "|";
    oss << ticket->getPrice() << "|";
    oss << (ticket->getIsPaid() ? "1" : "0");
    
    return oss.str();
}

std::shared_ptr<Ticket> FileManager::deserializeTicket(
    const std::string& ticketData,
    const std::vector<std::shared_ptr<Event>>& events,
    const std::vector<std::shared_ptr<User>>& users) {
    std::istringstream iss(ticketData);
    std::string idStr, eventIdStr, holderIdStr, priceStr, isPaidStr;
    
    std::getline(iss, idStr, '|');
    std::getline(iss, eventIdStr, '|');
    std::getline(iss, holderIdStr, '|');
    std::getline(iss, priceStr, '|');
    std::getline(iss, isPaidStr);
    
    int id = std::stoi(idStr);
    int eventId = std::stoi(eventIdStr);
    int holderId = std::stoi(holderIdStr);
    double price = std::stod(priceStr);
    bool isPaid = (isPaidStr == "1");
    
    // Find the event and holder
    std::shared_ptr<Event> event = nullptr;
    for (const auto& e : events) {
        if (e->getEventId() == eventId) {
            event = e;
            break;
        }
    }
    
    std::shared_ptr<User> holder = nullptr;
    for (const auto& user : users) {
        if (user->getUserId() == holderId) {
            holder = user;
            break;
        }
    }
    
    if (!event || !holder) {
        std::cerr << "Event or holder not found for ticket: " << id << std::endl;
        return nullptr;
    }
    
    auto ticket = std::make_shared<Ticket>(id, event, holder, price);
    if (isPaid) {
        ticket->setPaid(true);
    }
    
    return ticket;
}

void FileManager::createTestData() {
    // This function creates test data and writes it directly to files
    // It's useful for initial setup or testing
    
    // Create test users
    std::ofstream userFile(usersFile);
    userFile << "Manager|1|manager|Admin|admin@convention.com" << std::endl;
    userFile << "Resident|2|resident1|John Doe|john@example.com|R12345" << std::endl;
    userFile << "NonResident|3|nonresident1|Jane Smith|jane@example.com" << std::endl;
    userFile << "Organization|4|organization1|Acme Corp|info@acme.com|ORG001|Acme Corporation" << std::endl;
    userFile << "City|5|city1|Public Works|works@citygovt.com|Infrastructure Department" << std::endl;
    userFile << "Resident|6|resident2|Mark Wilson|mark@example.com|R54321" << std::endl;
    userFile << "Organization|7|organization2|Tech Summit|info@techsummit.com|ORG002|Tech Summit Inc." << std::endl;
    userFile << "NonResident|8|nonresident2|Sarah Johnson|sarah@example.com" << std::endl;
    userFile << "Resident|9|resident3|Emily Davis|emily@example.com|R78901" << std::endl;
    userFile << "NonResident|10|nonresident3|Mike Brown|mike@example.com" << std::endl;
    userFile.close();
    
    // Create test events
    std::ofstream eventFile(eventsFile);
    eventFile << "1|City Council Meeting|5|2023-11-15 09:00|2023-11-15 12:00|0|0|50" << std::endl;
    eventFile << "2|Tech Conference|7|2023-11-20 09:00|2023-11-20 17:00|1|1|200" << std::endl;
    eventFile << "3|Community Wedding|2|2023-11-25 14:00|2023-11-25 22:00|2|0|150" << std::endl;
    eventFile << "4|Charity Gala|4|2023-11-30 18:00|2023-11-30 23:00|3|1|300" << std::endl;
    eventFile << "5|Small Business Meeting|6|2023-12-05 10:00|2023-12-05 12:00|0|0|30" << std::endl;
    eventFile << "6|Holiday Dance|9|2023-12-15 19:00|2023-12-15 23:00|3|1|250" << std::endl;
    eventFile << "7|New Year's Celebration|3|2023-12-31 20:00|2024-01-01 02:00|3|1|500" << std::endl;
    eventFile << "8|Job Fair|7|2024-01-15 10:00|2024-01-15 16:00|1|1|200" << std::endl;
    eventFile << "9|Art Exhibition|8|2024-01-20 09:00|2024-01-22 18:00|1|1|150" << std::endl;
    eventFile << "10|Community Workshop|5|2024-02-01 13:00|2024-02-01 17:00|0|1|75" << std::endl;
    eventFile.close();
    
    // Create test reservations
    std::ofstream reservationFile(reservationsFile);
    reservationFile << "1|1|5|1|75.0|2023-11-01|1" << std::endl;
    reservationFile << "2|2|7|1|225.0|2023-11-05|1" << std::endl;
    reservationFile << "3|3|2|1|800.0|2023-11-10|1" << std::endl;
    reservationFile << "4|4|4|0|300.0|2023-11-15|0" << std::endl;
    reservationFile << "5|5|6|1|100.0|2023-11-20|1" << std::endl;
    reservationFile << "6|6|9|2|200.0|2023-11-25|0" << std::endl;
    reservationFile << "7|7|3|1|400.0|2023-12-01|1" << std::endl;
    reservationFile << "8|8|7|1|225.0|2023-12-05|1" << std::endl;
    reservationFile << "9|9|8|0|150.0|2023-12-10|0" << std::endl;
    reservationFile << "10|10|5|1|100.0|2023-12-15|1" << std::endl;
    reservationFile.close();
    
    // Create test tickets
    std::ofstream ticketFile(ticketsFile);
    ticketFile << "1|2|3|35.0|1" << std::endl;
    ticketFile << "2|2|8|35.0|1" << std::endl;
    ticketFile << "3|4|2|50.0|1" << std::endl;
    ticketFile << "4|4|9|50.0|1" << std::endl;
    ticketFile << "5|6|10|40.0|1" << std::endl;
    ticketFile << "6|7|6|75.0|1" << std::endl;
    ticketFile << "7|7|2|75.0|1" << std::endl;
    ticketFile << "8|7|9|75.0|1" << std::endl;
    ticketFile << "9|8|3|25.0|1" << std::endl;
    ticketFile << "10|9|10|15.0|1" << std::endl;
    ticketFile.close();
    
    std::cout << "Test data created successfully!" << std::endl;
}
