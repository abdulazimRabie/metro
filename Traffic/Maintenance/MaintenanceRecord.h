#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include <stdexcept>

using namespace std;

// ============================================
// MaintenanceRecord Class
// ============================================
class MaintenanceRecord {
private:
    string partName;
    double cost;
    string date;  // Format: "YYYY-MM-DD" or "DD/MM/YYYY"
    string description;
    string technician;

public:
    // Constructor with validation
    MaintenanceRecord(string partName, double cost, string date,
                     string description = "", string technician = "N/A")
        : partName(partName), cost(cost), date(date),
          description(description), technician(technician) {

        if (cost < 0) {
            throw invalid_argument("[MaintenanceRecord] Cost cannot be negative");
        }
        if (partName.empty()) {
            throw invalid_argument("[MaintenanceRecord] Part name cannot be empty");
        }
        if (date.empty()) {
            throw invalid_argument("[MaintenanceRecord] Date cannot be empty");
        }
    }

    // Default constructor
    MaintenanceRecord()
        : partName("Unknown"), cost(0.0), date("N/A"),
          description(""), technician("N/A") {}

    // Getters
    string getPartName() const {
        return partName;
    }

    double getCost() const {
        return cost;
    }

    string getDate() const {
        return date;
    }

    string getDescription() const {
        return description;
    }

    string getTechnician() const {
        return technician;
    }

    // Show single record in detailed format
    void showRecord() const {
        cout << "  +------------------------------------------" << endl;
        cout << "  | Part: " << partName << endl;
        cout << "  | Cost: $" << fixed << setprecision(2) << cost << endl;
        cout << "  | Date: " << date << endl;
        if (!description.empty()) {
            cout << "  | Description: " << description << endl;
        }
        cout << "  | Technician: " << technician << endl;
        cout << "  +------------------------------------------" << endl;
    }

    // Operator overloading for easy printing
    friend ostream& operator<<(ostream& os, const MaintenanceRecord& record) {
        os << "[" << record.date << "] " << record.partName
           << " - $" << fixed << setprecision(2) << record.cost
           << " (by " << record.technician << ")";
        return os;
    }
};