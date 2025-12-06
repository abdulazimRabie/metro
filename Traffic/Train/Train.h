#pragma once
#include <string>
#include <iostream>
#include "../Engine/Engine.h"
#include "../Brake/Brakes.h"
#include "../Maintenance/MaintenanceLog.h"
#include "../Maintenance/MaintenanceRecord.h"

using namespace std;

class Train {
private:
    string ID;
    int capacity;
    int mileage; // If this value became more than 1k -> then maintenance is needed
    bool needsMaintenance;

protected:
    Engine engine;                      // Composition
    Brake brake;                        // Composition
    MaintenanceLog maintenanceLog;      // Composition

public:
    // Constructor
    Train(
        string trainID, int capacity,
        string engineModel, int enginePower, EngineType engineType,
        string brakeModel, BrakeType brakeType
    ) : ID(trainID), capacity(capacity), mileage(0), needsMaintenance(false),
        engine(engineModel, enginePower, engineType),
        brake(brakeModel, brakeType),
        maintenanceLog(trainID) {

        cout << "\n========================================" << endl;
        cout << "[Train] T-" << this->ID << " has been CREATED!" << endl;
        cout << "Capacity: " << capacity << " passengers" << endl;
        cout << "========================================\n" << endl;
    }

    // Destructor
    ~Train() {
        cout << "\n[Train] T-" << this->ID << " has been KILLED!" << endl;
    }

    // Start the train
    void start() {
        cout << "\n[Train] Starting train T-" << this->ID << "..." << endl;

        // Check maintenance status
        if (needsMaintenance) {
            cout << "[Train] WARNING: Train needs maintenance!" << endl;
            cout << "[Train] Starting anyway (not recommended)..." << endl;
        }

        // Check if brakes are engaged
        if (brake.engaged()) {
            cout << "[Train] Cannot start! Brakes are still engaged." << endl;
            cout << "[Train] Releasing brakes first..." << endl;
            brake.release();
        }

        // Start the engine
        engine.start();
        cout << "[Train] T-" << this->ID << " is now moving!!" << endl;
    }

    // Stop the train
    void stop() {
        cout << "\n[Train] Stopping train T-" << this->ID << "..." << endl;
        brake.apply(100);
        engine.stop();
        cout << "[Train] Train T-" << this->ID << " has stopped." << endl;
    }

    // Gradual stop
    void gradualStop() {
        cout << "\n[Train] Gradual stop initiated for train T-" << this->ID << "..." << endl;
        brake.apply(30);
        cout << "[Train] Speed reducing..." << endl;
        brake.apply(60);
        cout << "[Train] Speed reducing more..." << endl;
        brake.apply(100);
        cout << "[Train] Train stopped completely." << endl;
        engine.stop();
    }

    // Emergency stop
    void emergencyStop() {
        cout << "\n[Train] *** EMERGENCY STOP for train T-" << this->ID << " ***" << endl;
        brake.emergencyStop();
        engine.stop();
        cout << "[Train] Emergency stop completed." << endl;
    }

    // Simulate travel (increases mileage, might trigger maintenance)
    void travel(int distance) {
        if (distance <= 0) {
            cout << "[Train] Invalid distance!" << endl;
            return;
        }

        mileage += distance;
        cout << "[Train] T-" << this->ID << " traveled " << distance
             << " km. Total mileage: " << mileage << " km" << endl;

        // Check if scheduled maintenance is needed (every 10000 km)
        if (mileage % 10000 == 0 && mileage > 0) {
            needsMaintenance = true;
            cout << "[Train] !!! SCHEDULED MAINTENANCE REQUIRED at "
                 << mileage << " km !!!" << endl;
        }
    }

    // Perform maintenance (adds record to log)
    void performMaintenance(string partName, double cost, string date,
                           string description = "", string technician = "N/A") {
        cout << "\n[Train] ========================================" << endl;
        cout << "[Train] Performing maintenance on T-" << this->ID << "..." << endl;
        cout << "[Train] Part: " << partName << endl;
        cout << "[Train] Cost: $" << fixed << setprecision(2) << cost << endl;

        maintenanceLog.addRecord(partName, cost, date, description, technician);

        // Reset maintenance flag if it was set
        if (needsMaintenance) {
            needsMaintenance = false;
            cout << "[Train] Scheduled maintenance completed!" << endl;
        }

        cout << "[Train] Maintenance completed for T-" << this->ID << endl;
        cout << "[Train] ========================================\n" << endl;
    }

    // Quick maintenance (convenience method with auto date)
    void performQuickMaintenance(string partName, double cost, string technician = "N/A") {
        performMaintenance(partName, cost, "2024-12-06", "Regular maintenance", technician);
    }

    // Show maintenance history
    void showMaintenanceHistory() {
        maintenanceLog.showAll();
    }

    // Show maintenance summary
    void showMaintenanceSummary() {
        maintenanceLog.showSummary();
    }

    // Show maintenance grouped by part
    void showMaintenanceByPart() {
        maintenanceLog.showByPart();
    }

    // Export maintenance log
    void exportMaintenanceLog() {
        maintenanceLog.exportToText();
    }

    // Check if maintenance is needed
    bool requiresMaintenance() const {
        return needsMaintenance;
    }

    // Getters
    Engine getEngine() { return this->engine; }
    Brake getBrake() { return this->brake; }
    string getID() const { return this->ID; }
    int getCapacity() const { return this->capacity; }
    int getMileage() const { return this->mileage; }
    int getMaintenanceRecordCount() const {
        return maintenanceLog.getRecordCount();
    }
    double getTotalMaintenanceCost() const {
        return maintenanceLog.getTotalCost();
    }

    // Show complete train status
    void showStatus() {
        cout << "\n========================================" << endl;
        cout << "     TRAIN STATUS - T-" << this->ID << endl;
        cout << "========================================" << endl;
        cout << "Capacity: " << this->capacity << " passengers" << endl;
        cout << "Mileage: " << this->mileage << " km" << endl;

        if (needsMaintenance) {
            cout << "Status: *** MAINTENANCE REQUIRED ***" << endl;
        } else {
            cout << "Status: Operational" << endl;
        }

        cout << "\n" << engine.getStatus() << endl;
        cout << brake.getStatus() << endl;

        // Show maintenance summary
        if (maintenanceLog.getRecordCount() > 0) {
            cout << "\nMaintenance Records: " << maintenanceLog.getRecordCount() << endl;
            cout << "Total Maintenance Cost: $" << fixed << setprecision(2)
                 << maintenanceLog.getTotalCost() << endl;
        } else {
            cout << "\nNo maintenance records." << endl;
        }
        cout << "========================================\n" << endl;
    }
};