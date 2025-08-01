#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <memory>

// Forward declarations
class Event;
class Reservation;

class User {
protected:
    std::string username;
    std::string password;
    std::string name;
    std::string contactInfo;
    int userId;

public:
    // Constructor and destructor
    User(const std::string& username, const std::string& password, const std::string& name, const std::string& contactInfo);
    virtual ~User();
    
    // Authentication methods
    bool authenticate(const std::string& enteredPassword) const;
    
    // Getter methods
    std::string getUsername() const;
    std::string getName() const;
    void setName(const std::string& newName);
    void setContactInfo(const std::string& newContactInfo);
    std::string getContactInfo() const;
    int getUserId() const;
    
    // Pure virtual methods
    virtual double getHourlyRate() const = 0;
    virtual std::string getUserType() const = 0;
    
    // Common functionality for all users
    std::vector<std::shared_ptr<Event>> viewSchedule(const std::string& date) const;
    std::shared_ptr<Event> viewEventDetails(int eventId) const;
};

#endif // USER_H
