#ifndef USER_TYPES_H
#define USER_TYPES_H

#include "User.h"

class Resident : public User {
public:
    Resident(const std::string& username, const std::string& password, 
             const std::string& name, const std::string& contactInfo, 
             const std::string& cityId);
    ~Resident() override;
    
    double getHourlyRate() const override;
    std::string getUserType() const override;
    std::string getCityId() const;

private:
    std::string cityId;
};

class NonResident : public User {
public:
    NonResident(const std::string& username, const std::string& password, 
                const std::string& name, const std::string& contactInfo);
    ~NonResident() override;
    
    double getHourlyRate() const override;
    std::string getUserType() const override;
};

class Organization : public User {
public:
    Organization(const std::string& username, const std::string& password, 
                 const std::string& name, const std::string& contactInfo,
                 const std::string& orgId, const std::string& orgName);
    ~Organization() override;
    
    double getHourlyRate() const override;
    std::string getUserType() const override;
    std::string getOrgId() const;
    std::string getOrgName() const;

private:
    std::string orgId;
    std::string orgName;
};

class City : public User {
public:
    City(const std::string& username, const std::string& password, 
         const std::string& name, const std::string& contactInfo,
         const std::string& departmentInfo);
    ~City() override;
    
    double getHourlyRate() const override;
    std::string getUserType() const override;
    std::string getDepartmentInfo() const;

private:
    std::string departmentInfo;
};

class Manager : public User {
public:
    Manager(const std::string& username, const std::string& password, 
            const std::string& name, const std::string& contactInfo);
    ~Manager() override;
    
    double getHourlyRate() const override;
    std::string getUserType() const override;
    
    // Manager-specific functionality
    bool approveReservation(int reservationId);
    bool processCancellation(int reservationId);
    double processRefund(int reservationId);
    void manageBudget();
    std::vector<std::shared_ptr<Reservation>> viewAllReservations() const;
};

#endif // USER_TYPES_H
