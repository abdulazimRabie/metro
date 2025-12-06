#pragma once
#include <string>
#include <iostream>
using namespace std;

// ============================================
// Enum for Brake Types
// ============================================
enum class BrakeType {
    HYDRAULIC,
    PNEUMATIC,
    ELECTRIC,
    ELECTROMAGNETIC,
    REGENERATIVE
};

// ============================================
// Helper Function - Convert Enum to String
// ============================================
inline string brakeTypeToString(BrakeType b) {
    switch (b) {
        case BrakeType::HYDRAULIC:
            return "Hydraulic";
        case BrakeType::PNEUMATIC:
            return "Pneumatic";
        case BrakeType::ELECTRIC:
            return "Electric";
        case BrakeType::ELECTROMAGNETIC:
            return "Electromagnetic";
        case BrakeType::REGENERATIVE:
            return "Regenerative";
        default:
            return "Unknown";
    }
}

// ============================================
// Brake Class - Complete Implementation
// ============================================
class Brake {
private:
    string model;
    BrakeType type;
    bool isEngaged;
    int brakeForce;

public:
    // Constructor
    Brake(string model, BrakeType type = BrakeType::HYDRAULIC) 
        : model(model), type(type), isEngaged(false), brakeForce(0) {
        cout << "[Brake] Brake system created: " << brakeTypeToString(this->type) << endl;
    }

    // Destructor
    ~Brake() {
        cout << "[Brake] " << this->model << " Brake has been destructured!" << endl;
    }

    // Apply brakes with force validation
    void apply(int force) {
        if (force < 0 || force > 100) {
            cout << "[Brake] " << this->model << " only force in this range [0-100]" << endl;
            return;
        }

        this->brakeForce = force;
        this->isEngaged = true;
        cout << "[Brake] " << this->model << " applied at " << force << "% force." << endl;
    }

    // Release brakes
    void release() {
        if (this->engaged()) {
            this->brakeForce = 0;
            this->isEngaged = false;
            cout << "[Brake] " << this->model << " has been RELEASED!" << endl;
        } else {
            cout << "[Brake] " << this->model << " is already released." << endl;
        }
    }

    // Emergency stop
    void emergencyStop() {
        apply(100);
        cout << "[Brake] *** EMERGENCY BRAKE ACTIVATED for " << this->model << " ***" << endl;
    }

    // Getters
    string getType() {
        return brakeTypeToString(this->type);
    }

    string getModel() {
        return this->model;
    }

    bool engaged() {
        return this->isEngaged;
    }

    int getForce() {
        return this->brakeForce;
    }

    // Get complete status
    string getStatus() {
        string status = engaged() ? "Engaged" : "Released";
        return "[Brake] " + model + ", " + brakeTypeToString(type) + 
               " : Status = " + status + ", BrakeForce = " + to_string(brakeForce) + "%";
    }
};