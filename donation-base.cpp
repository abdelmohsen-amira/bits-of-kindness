#include "donation-base.hpp"

// Implementation of InventoryItem class
InventoryItem::InventoryItem(const std::string& name, int qty)
    : itemName(name), quantity(qty) {}

// Implementation of DonationRecord class
DonationRecord::DonationRecord(int id, const std::string& donor, const std::string& contact,
                               const std::vector<InventoryItem>& items, const std::string& desc, time_t date)
    : donationID(id), donorName(donor), donorContact(contact),
      inventoryItems(items), description(desc), donationDate(date) {}

void DonationRecord::displayDetails() const {
    std::cout << "Donation ID: " << donationID << "\n";
    std::cout << "Donor: " << donorName << "\n";
    std::cout << "Contact: " << donorContact << "\n";
    std::cout << "Items:\n";
    for (const auto& item : inventoryItems) {
        std::cout << "  - " << item.itemName << ": " << item.quantity << " units\n";
    }
    std::cout << "Description: " << description << "\n";
    std::cout << "Date: " << ctime(&donationDate) << "\n";
}