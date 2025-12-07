#pragma once
#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;

enum class EngineType {
    ELECTRIC,
    DIESEL,
    HYBRID,
    MAGNETIC_LEVITATION
};

inline string engineTypeToString(EngineType type) {
    switch(type) {
        case EngineType::ELECTRIC: 
            return "Electric";
        case EngineType::DIESEL: 
            return "Diesel";
        case EngineType::HYBRID: 
            return "Hybrid";
        case EngineType::MAGNETIC_LEVITATION: 
            return "Magnetic Levitation";
        default: 
            return "Unknown";
    }
}

class Engine {
private:
    string model;
    EngineType type;
    int power;
    bool isRunning;

public:
    Engine(string model, int power, EngineType type = EngineType::ELECTRIC)
        : model(model), type(type), isRunning(false) {
        if (power < 0) {
            throw invalid_argument("[Engine] Power cannot be negative");
        }
        this->power = power;
        cout << "[Engine] " << engineTypeToString(this->type) 
             << " engine (" << power << " HP) initialized: " << model << endl;
    }

    ~Engine() {
        cout << "[Engine] " << this->model << " " 
             << engineTypeToString(this->type) << " has been KILLED!" << endl;
    }

    void start() {
        if (!isRunning) {
            isRunning = true;
            cout << "[Engine] " << model << " STARTED." << endl;
        } else {
            cout << "[Engine] " << model << " already running." << endl;
        }
    }

    void stop() {
        if (isRunning) {
            isRunning = false;
            cout << "[Engine] " << model << " STOPPED." << endl;
        } else {
            cout << "[Engine] " << model << " already stopped." << endl;
        }
    }

    string getModel() {
        return this->model;
    }

    string getType() {
        return engineTypeToString(this->type);
    }

    int getPower() {
        return this->power;
    }

    bool running() {
        return this->isRunning;
    }

    string getStatus() {
        string status = isRunning ? "Running" : "Stopped";
        return "[Engine] " + this->model + "-" + engineTypeToString(this->type) +
               " : " + status + ", Power = " + to_string(this->power) + " HP";
    }
};