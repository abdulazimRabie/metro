#include <iostream>
#include "Traffic/Brake/Brakes.h"
#include "Traffic/Engine/Engine.h"
#include "Traffic/Train/Train.h"

int main() {

    // Brake b("B-01", BrakeType::ELECTRIC);
    // b.apply(-30);
    // cout << b.getStatus() << endl;
    //
    // Engine e("0m3", 450, EngineType::DIESEL);

    // cout << "=== SMART METRO MANAGEMENT SYSTEM ===" << endl;
    // cout << "=== Complete Train Demo ===" << endl;
    //
    // // Create a train with Electric engine and Hydraulic brakes
    // Train metro1(
    //     "M-001", 500,
    //     "E-001", 1500, EngineType::ELECTRIC,
    //     "B-001", BrakeType::HYDRAULIC
    // );
    //
    // // Show initial status
    // metro1.showStatus();
    //
    // // Start the train
    // metro1.start();
    // metro1.showStatus();
    //
    // // Stop the train normally
    // metro1.stop();
    // metro1.showStatus();
    //
    // // Start again and test gradual stop
    // metro1.start();
    // metro1.gradualStop();
    // metro1.showStatus();
    //
    // // Test emergency stop
    // metro1.start();
    // metro1.emergencyStop();
    // metro1.showStatus();

    cout << "================================================" << endl;
    cout << "   SMART METRO MANAGEMENT SYSTEM" << endl;
    cout << "   Complete Train with Maintenance Demo" << endl;
    cout << "================================================\n" << endl;

    // ============================================
    // Create Train
    // ============================================
    Train metro1(
        "M-001", 500,
        "E-001", 1500, EngineType::ELECTRIC,
        "B-001", BrakeType::HYDRAULIC
    );

    metro1.showStatus();

    // ============================================
    // Operate Train - Phase 1
    // ============================================
    cout << "\n=== PHASE 1: Initial Operation ===" << endl;
    metro1.start();
    metro1.travel(3000);
    metro1.stop();

    // ============================================
    // First Maintenance
    // ============================================
    cout << "\n=== PHASE 2: First Maintenance ===" << endl;
    metro1.performMaintenance(
        "Brake Pads",
        450.50,
        "2024-12-01",
        "Replaced worn front brake pads",
        "John Smith"
    );

    metro1.performMaintenance(
        "Engine Oil",
        120.00,
        "2024-12-01",
        "Regular oil change and filter replacement",
        "Sarah Johnson"
    );

    metro1.showStatus();

    // ============================================
    // Continue Operation
    // ============================================
    cout << "\n=== PHASE 3: Continued Operation ===" << endl;
    metro1.start();
    metro1.travel(4000);
    metro1.gradualStop();

    metro1.travel(3000);  // Total: 10000 km - should trigger maintenance alert
    metro1.stop();

    metro1.showStatus();

    // ============================================
    // Scheduled Maintenance at 10000 km
    // ============================================
    cout << "\n=== PHASE 4: Scheduled Maintenance ===" << endl;

    metro1.performMaintenance(
        "Air Filter",
        85.75,
        "2024-12-05",
        "Replaced clogged air filter",
        "Mike Davis"
    );

    metro1.performMaintenance(
        "Brake Fluid",
        95.00,
        "2024-12-05",
        "Brake fluid flush and refill",
        "John Smith"
    );

    metro1.performMaintenance(
        "Wheel Bearings",
        320.00,
        "2024-12-05",
        "Lubricated and inspected wheel bearings",
        "Sarah Johnson"
    );

    metro1.showStatus();

    // ============================================
    // More Operation and Additional Maintenance
    // ============================================
    cout << "\n=== PHASE 5: Extended Operation ===" << endl;
    metro1.start();
    metro1.travel(5000);
    metro1.stop();

    metro1.performMaintenance(
        "Brake Pads",
        460.00,
        "2024-12-10",
        "Front brake pad replacement",
        "John Smith"
    );

    metro1.performQuickMaintenance("Battery Check", 50.00, "Mike Davis");

    // ============================================
    // Show Complete Maintenance Reports
    // ============================================
    cout << "\n=== MAINTENANCE REPORTS ===" << endl;

    // Summary
    metro1.showMaintenanceSummary();

    // Full history
    metro1.showMaintenanceHistory();

    // Grouped by part
    metro1.showMaintenanceByPart();

    // Export log
    metro1.exportMaintenanceLog();

    // ============================================
    // Final Status
    // ============================================
    cout << "\n=== FINAL TRAIN STATUS ===" << endl;
    metro1.showStatus();

    // ============================================
    // Create Second Train for Comparison
    // ============================================
    cout << "\n\n=== CREATING SECOND TRAIN ===" << endl;
    Train metro2(
        "M-002", 600,
        "E-002", 2000, EngineType::DIESEL,
        "B-002", BrakeType::PNEUMATIC
    );

    metro2.start();
    metro2.travel(2000);
    metro2.stop();

    metro2.performQuickMaintenance("Inspection", 100.00, "Inspector");
    metro2.showStatus();

    // ============================================
    // Comparison
    // ============================================
    cout << "\n=== TRAIN COMPARISON ===" << endl;
    cout << "Train M-001:" << endl;
    cout << "  - Mileage: " << metro1.getMileage() << " km" << endl;
    cout << "  - Maintenance Records: " << metro1.getMaintenanceRecordCount() << endl;
    cout << "  - Total Maintenance Cost: $" << metro1.getTotalMaintenanceCost() << endl;

    cout << "\nTrain M-002:" << endl;
    cout << "  - Mileage: " << metro2.getMileage() << " km" << endl;
    cout << "  - Maintenance Records: " << metro2.getMaintenanceRecordCount() << endl;
    cout << "  - Total Maintenance Cost: $" << metro2.getTotalMaintenanceCost() << endl;

    cout << "\n================================================" << endl;
    cout << "   End of Demo - Trains will be destroyed" << endl;
    cout << "================================================\n" << endl;


    return 0;
}