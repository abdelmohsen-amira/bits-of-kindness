#include "donation-tracker.hpp"

// Implementation of DonationTracker class
DonationTracker::DonationTracker(int id, const std::string& donor, const std::string& contact,
                                 const std::vector<InventoryItem>& items, const std::string& desc, time_t date)
    : DonationBase() {}

DonationTracker::~DonationTracker() {
    // Cleanup dynamically allocated memory
    for (auto& donation : donations) {
        delete donation;
    }
}

void DonationTracker::recordDonation(int id, const std::string& donor, const std::string& contact,
                                     const std::vector<InventoryItem>& items, const std::string& desc, time_t date) {
    DonationBase* newDonation = new DonationRecord(id, donor, contact, items, desc, date);
    donations.push_back(newDonation);

    // Update inventory
    updateInventory(items);

    // Sort donations by time
    sortDonationsByTime();

    saveToFile("donations.csv");  // Save donation to file after recording
}

void DonationTracker::loadFromFile(const std::string& fileName) {
    donations.clear();  // Clear existing data before loading
    std::ifstream file(fileName);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            DonationBase* donation = parseCSVLine(line);
            donations.push_back(donation);
        }
        file.close();
    } else {
        std::cerr << "Error: Unable to open the file for reading.\n";
    }
}

void DonationTracker::displayDonations() const {
    std::cout << "Donation History:\n";
    for (const auto& donation : donations) {
        donation->displayDetails();
        std::cout << "\n";
    }
}

void DonationTracker::displayDonationsByFilter(const std::string& filter) const {
    std::cout << "Donations with filter \"" << filter << "\":\n";
    for (const auto& donation : donations) {
        for (const auto& item : static_cast<DonationRecord*>(donation)->inventoryItems) {
            if (item.itemName == filter) {
                donation->displayDetails();
                std::cout << "\n";
                break; // Display the donation only once
            }
        }
    }
}

void DonationTracker::displayDonationDetails(int id) const {
    for (const auto& donation : donations) {
        if (static_cast<DonationRecord*>(donation)->donationID == id) {
            donation->displayDetails();
            std::cout << "\n";
            return;
        }
    }
    std::cout << "Donation with ID " << id << " not found.\n";
}

void DonationTracker::searchDonationsByContact(const std::string& contact) const {
    std::cout << "Donations by Contact " << contact << ":\n";
    for (const auto& donation : donations) {
        if (static_cast<DonationRecord*>(donation)->donorContact == contact) {
            donation->displayDetails();
            std::cout << "\n";
        }
    }
}

void DonationTracker::displayInventory() const {
    std::cout << "Current Inventory:\n";
    for (const auto& item : inventory) {
        std::cout << "Item: " << item.itemName << ", Quantity: " << item.quantity << " units\n";
    }
}

void DonationTracker::sortDonationsByTime() {
    std::sort(donations.begin(), donations.end(), [](const DonationBase* a, const DonationBase* b) {
        return static_cast<DonationRecord*>(a)->donationDate < static_cast<DonationRecord*>(b)->donationDate;
    });
}

void DonationTracker::saveToFile(const std::string& fileName) const {
    std::ofstream file(fileName, std::ios::app);
    if (file.is_open()) {
        file << static_cast<DonationRecord*>(this)->donationID << ","
             << static_cast<DonationRecord*>(this)->donorName << ","
             << static_cast<DonationRecord*>(this)->donorContact << ",";
        for (const auto& item : static_cast<DonationRecord*>(this)->inventoryItems) {
            file << item.itemName << ":" << item.quantity << ",";
        }
        file << static_cast<DonationRecord*>(this)->description << ","
             << ctime(&static_cast<DonationRecord*>(this)->donationDate);
        file.close();
    } else {
        std::cerr << "Error: Unable to open the file for writing.\n";
    }
}

DonationBase* DonationTracker::parseCSVLine(const std::string& line) const {
    std::istringstream iss(line);
    int id;
    std::string donor, contact, desc;
    std::vector<InventoryItem> items;
    std::getline(iss, id, ',');
    std::getline(iss, donor, ',');
    std::getline(iss, contact, ',');
    std::string itemInfo;
    while (std::getline(iss, itemInfo, ',')) {
        std::istringstream itemStream(itemInfo);
        std::string itemName;
        int quantity;
        std::getline(itemStream, itemName, ':');
        itemStream >> quantity;
        items.emplace_back(itemName, quantity);
    }
    std::getline(iss, desc, ',');
    std::string dateStr;
    std::getline(iss, dateStr);
    std::tm tm = {};
    std::istringstream dateStream(dateStr);
    dateStream >> std::get_time(&tm, "%a %b %d %H:%M:%S %Y");
    time_t date = std::mktime(&tm);
    return new DonationRecord(id, donor, contact, items, desc, date);
}

void DonationTracker::updateInventory(const std::vector<InventoryItem>& donatedItems) {
    for (const auto& donatedItem : donatedItems) {
        bool found = false;
        for (auto& inventoryItem : inventory) {
            if (inventoryItem.itemName == donatedItem.itemName) {
                inventoryItem.quantity += donatedItem.quantity;
                found = true;
                break;
            }
        }
        if (!found) {
            inventory.push_back(donatedItem);
        }
    }
}

void DonationTracker::displayDetails() const {
    // Implementing the virtual function from the base class
    displayDonations();
}
