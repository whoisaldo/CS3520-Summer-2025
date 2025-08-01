// src/User.cpp

#include "../include/User.h"
#include "../include/Event.h"
#include <algorithm>
#include <iostream>

// Destructor must be defined out-of-line to emit User’s vtable/typeinfo
User::~User() {
    // nothing to clean up in base class
}

User::User(const std::string& username,
           const std::string& password,
           const std::string& name,
           const std::string& contactInfo)
  : username(username)
  , password(password)
  , name(name)
  , contactInfo(contactInfo)
  , userId(-1)
{
    // User ID will be set when added to the system
    static int nextUserId = 1;
    userId = nextUserId++;
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
    name = newName;
}

void User::setContactInfo(const std::string& newContactInfo) {
    contactInfo = newContactInfo;
}

std::string User::getContactInfo() const {
    return contactInfo;
}

int User::getUserId() const {
    return userId;
}

std::vector<std::shared_ptr<Event>>
User::viewSchedule(const std::string& date) const {
    // This would typically query the system to find events on the given date
    // For now, return an empty vector as the implementation depends on system access
    (void)date;
    std::vector<std::shared_ptr<Event>> result;
    return result;
}

std::shared_ptr<Event>
User::viewEventDetails(int eventId) const {
    // This would typically query the system to find an event with the given ID
    // For now, return nullptr as the implementation depends on system access
    (void)eventId;
    return nullptr;
}

