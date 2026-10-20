#include "SeatAssignment.h"

// Usual cpp definition file for my header file
SeatAssignment::SeatAssignment(std::string name, int number) {
    this->name = name;
    this->number = number;
}

std::string SeatAssignment::getName() {
    return this->name;
}

int SeatAssignment::getSeatNumber() {
    return this->number;
}