#pragma once
#include <iostream>

// Same old header file declaration

class SeatAssignment{
    private:
        std::string name;
        int number;
    public:
        SeatAssignment(std::string name, int number);

        std::string getName();
        int getSeatNumber();
};