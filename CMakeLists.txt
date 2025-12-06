cmake_minimum_required(VERSION 4.0)
project(SmartMetro)

set(CMAKE_CXX_STANDARD 20)

add_executable(SmartMetro main.cpp
        Traffic/Brake/Brakes.h
        Traffic/Engine/Engine.h
        Traffic/Train/Train.h
        Traffic/Maintenance/MaintenanceRecord.h
        Traffic/Maintenance/MaintenanceLog.h)
