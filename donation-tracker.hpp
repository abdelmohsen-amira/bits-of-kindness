#ifndef DONATION_TRACKER_HPP
#define DONATION_TRACKER_HPP

#include "donation-base.hpp"

class DonationTracker : public DonationBase {
private:
    std::vector<DonationBase*> donations;
    std::vector<InventoryItem> inventory;

    void sortDonationsByTime();
    void saveToFile(const std::string& fileName) const;
    DonationBase* parseCSVLine(const std::string& line) const;
    void updateInventory(const std::vector<InventoryItem>& donatedItems);

public:
    DonationTracker(int id, const std::string& donor, const std::string& contact,
                    const std::vector<InventoryItem>& items, const std::string& desc, time_t date);

    ~DonationTracker();

    void recordDonation(int id, const std::string& donor, const std::string& contact,
                        const std::vector<InventoryItem>& items, const std::string& desc, time_t date);

    void loadFromFile(const std::string& fileName);
    void displayDonations() const;
    void displayDonationsByFilter(const std::string& filter) const;
    void displayDonationDetails(int id) const;
    void searchDonationsByContact(const std::string& contact) const;
    void displayInventory() const;

    // Implementing the virtual function from the base class
    void displayDetails() const override;
};

#endif  // DONATION_TRACKER_HPP
