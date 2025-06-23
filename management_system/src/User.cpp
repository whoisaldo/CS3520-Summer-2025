#include "../include/User.h"
#include "../include/Event.h"
#include <algorithm>
#include <iostream>

User::User(const std::string& username, const std::string& password, 
           const std::string& name, const std::string& contactInfo)
    : username(username), password(password), name(name), contactInfo(contactInfo), userId(-1) {
    // User ID will be set when added to the system
    static int nextUserId = 1;
    userId = nextUserId++;
}

User::~User() {
    // Nothing specific to clean up
}

bool User::authenticate(const std::string& enteredPassword) const {
    return password == enteredPassword;
}

std::string User::getUsername() const {
    return username;
}

std::string User::getName() const {
    return name;
}

void User::setName(const std::string& newName) {
    username = newName;
}

void User::setContactInfo(const std::string& newContactInfo){
    contactInfo = newContactInfo;
}

std::string User::getContactInfo() const {
    return contactInfo;
}

int User::getUserId() const {
    return userId;
}

std::vector<std::shared_ptr<Event>> User::viewSchedule(const std::string& date) const {
    // This would typically query the system to find events on the given date
    // For now, return an empty vector as the implementation depends on system access
    std::vector<std::shared_ptr<Event>> result;
    return result;
}

std::shared_ptr<Event> User::viewEventDetails(int eventId) const {
    // This would typically query the system to find an event with the given ID
    // For now, return nullptr as the implementation depends on system access
    return nullptr;
}
