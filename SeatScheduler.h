#pragma once
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include "SeatAssignment.cpp"

class SeatScheduler {
    private:
        int R_Size; // keeps track of the regular seat size
        int A_Size; // keeps track of the adventure seat size
        int datalength;
        std::vector<SeatAssignment> S_A; // stores all the seat assignments

        std::stack<std::string> *RegularStack;
        std::queue<std::string> *RegularQueue;

        std::stack<std::string> *AdvengerStack;
        std::queue<std::string> *AdvengerQueue;

    public:
        // sets up the regular and adventure seats when the scheduler is created
        SeatScheduler(std::string R_Size, std::string A_Size);

        // goes through the list and schedules all the customers
        void ScheduleAll(std::vector<std::string> schedule);

        // adds a customer to the scheduler when they arrive
        void enterCustomer(std::string name);

        // removes a customer from the scheduler when they leave
        void exitCustomer(std::string name);

        // displays the available seats and the customers waiting in line
        void printAvailable(std::stack<std::string> *s);
        void printQueue(std::queue<std::string> *q);

        // prints out the scheduling report
        void Report();
};