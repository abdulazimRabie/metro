#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <iomanip>
#include <stdexcept>
#include "MaintenanceRecord.h"


using namespace std;
class MaintenanceLog {
private:
    vector<MaintenanceRecord> records;  // Aggregation - stores copies
    string trainID;
    double totalCost;
    int nextRecordID;

public:
    MaintenanceLog(string trainID = "Unknown") 
        : trainID(trainID), totalCost(0.0), nextRecordID(1) {
        cout << "[MaintenanceLog] Maintenance log initialized for Train: " << trainID << endl;
    }

    void addRecord(const MaintenanceRecord& record) {
        records.push_back(record);  // Copies the record
        totalCost += record.getCost();
        cout << "[MaintenanceLog] Record #" << nextRecordID 
             << " added for Train " << trainID 
             << ": " << record.getPartName() 
             << " ($" << fixed << setprecision(2) << record.getCost() << ")" << endl;
        nextRecordID++;
    }

    void addRecord(string partName, double cost, string date,
                   string description = "", string technician = "N/A") {
        MaintenanceRecord record(partName, cost, date, description, technician);
        addRecord(record);
    }

    void showAll() const {
        cout << "\n============================================" << endl;
        cout << "  MAINTENANCE LOG - Train: " << trainID << endl;
        cout << "============================================" << endl;
        
        if (records.empty()) {
            cout << "  No maintenance records found." << endl;
            cout << "============================================\n" << endl;
            return;
        }
        
        cout << "  Total Records: " << records.size() << endl;
        cout << "  Total Cost: $" << fixed << setprecision(2) << totalCost << endl;
        cout << "\n  Maintenance History:" << endl;
        
        for (size_t i = 0; i < records.size(); i++) {
            cout << "\n  Record #" << (i + 1) << ":" << endl;
            records[i].showRecord();
        }
        
        cout << "============================================\n" << endl;
    }

    int getRecordCount() const {
        return records.size();
    }

    double getTotalCost() const {
        return totalCost;
    }

    string getTrainID() const {
        return trainID;
    }

    vector<MaintenanceRecord> getRecordsByPart(string partName) const {
        vector<MaintenanceRecord> result;
        for (const auto& record : records) {
            if (record.getPartName() == partName) {
                result.push_back(record);
            }
        }
        return result;
    }

    vector<MaintenanceRecord> getRecordsByTechnician(string technician) const {
        vector<MaintenanceRecord> result;
        for (const auto& record : records) {
            if (record.getTechnician() == technician) {
                result.push_back(record);
            }
        }
        return result;
    }

    vector<MaintenanceRecord> getRecentRecords(int count) const {
        vector<MaintenanceRecord> result;
        int start = max(0, (int)records.size() - count);
        for (int i = start; i < (int)records.size(); i++) {
            result.push_back(records[i]);
        }
        return result;
    }

    MaintenanceRecord getMostExpensive() const {
        if (records.empty()) {
            throw runtime_error("[MaintenanceLog] No records available");
        }
        
        MaintenanceRecord mostExpensive = records[0];
        for (const auto& record : records) {
            if (record.getCost() > mostExpensive.getCost()) {
                mostExpensive = record;
            }
        }
        return mostExpensive;
    }

    void clearLog() {
        records.clear();
        totalCost = 0.0;
        nextRecordID = 1;
        cout << "[MaintenanceLog] All records cleared for Train " << trainID << endl;
    }

    void showSummary() const {
        cout << "\n========================================" << endl;
        cout << "  MAINTENANCE SUMMARY - Train " << trainID << endl;
        cout << "========================================" << endl;
        cout << "  Total Records: " << records.size() << endl;
        cout << "  Total Cost: $" << fixed << setprecision(2) << totalCost << endl;
        
        if (!records.empty()) {
            cout << "  Average Cost: $" 
                 << fixed << setprecision(2) << (totalCost / records.size()) << endl;
            
            try {
                MaintenanceRecord expensive = getMostExpensive();
                cout << "  Most Expensive: " << expensive.getPartName() 
                     << " ($" << fixed << setprecision(2) << expensive.getCost() << ")" << endl;
            } catch (...) {}
        }
        cout << "========================================\n" << endl;
    }

    // Show records grouped by part
    void showByPart() const {
        cout << "\n========================================" << endl;
        cout << "  MAINTENANCE BY PART - Train " << trainID << endl;
        cout << "========================================" << endl;
        
        if (records.empty()) {
            cout << "  No maintenance records found." << endl;
            cout << "========================================\n" << endl;
            return;
        }

        // Create a simple grouping
        vector<string> parts;
        for (const auto& record : records) {
            bool found = false;
            for (const auto& part : parts) {
                if (part == record.getPartName()) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                parts.push_back(record.getPartName());
            }
        }

        // Display grouped records
        for (const auto& part : parts) {
            vector<MaintenanceRecord> partRecords = getRecordsByPart(part);
            double partTotal = 0.0;
            
            cout << "\n  Part: " << part << " (" << partRecords.size() << " records)" << endl;
            
            for (const auto& record : partRecords) {
                partTotal += record.getCost();
                cout << "    - " << record << endl;
            }
            
            cout << "    Total for " << part << ": $" 
                 << fixed << setprecision(2) << partTotal << endl;
        }
        
        cout << "========================================\n" << endl;
    }

    void exportToText() const {
        cout << "\n=== MAINTENANCE LOG EXPORT ===" << endl;
        cout << "Train: " << trainID << endl;
        cout << "Total Records: " << records.size() << endl;
        cout << "Total Cost: $" << fixed << setprecision(2) << totalCost << endl;
        cout << "\nRecords:" << endl;
        
        for (size_t i = 0; i < records.size(); i++) {
            const auto& r = records[i];
            cout << (i+1) << "," << r.getDate() << "," << r.getPartName() 
                 << "," << r.getCost() << "," << r.getTechnician() 
                 << "," << r.getDescription() << endl;
        }
        cout << "=== END OF EXPORT ===\n" << endl;
    }
};