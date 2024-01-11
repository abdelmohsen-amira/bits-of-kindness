#ifndef DONATION_BASE_HPP
#define DONATION_BASE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <sstream>
#include <algorithm>
#include <fstream>

class InventoryItem {
public:
    std::string itemName;
    int quantity;

    InventoryItem(const std::string& name, int qty);
};

class DonationBase {
public:
    virtual ~DonationBase() = default;

    virtual void displayDetails() const = 0;
};

class DonationRecord : public DonationBase {
public:
    int donationID;
    std::string donorName;
    std::string donorContact;
    std::vector<InventoryItem> inventoryItems;
    std::string description;
    time_t donationDate;

    DonationRecord(int id, const std::string& donor, const std::string& contact,
                   const std::vector<InventoryItem>& items, const std::string& desc, time_t date);

    // Implementing the virtual function from the base class
    void displayDetails() const override;
};

#endif  // DONATION_BASE_HPP