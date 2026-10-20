#include "SeatScheduler.h"
#include <iostream>
#include <string>
#include "Splitting.cpp"

SeatScheduler::SeatScheduler(std::string R_Size, std::string A_Size) {
    this->A_Size = std::stoi(A_Size);
    this->R_Size = std::stoi(R_Size);

    // creates the stacks and queues for both seat types
    RegularStack = new std::stack<std::string>[this->R_Size];
    RegularQueue = new std::queue<std::string>[this->R_Size];

    AdvengerStack = new std::stack<std::string>[this->A_Size];
    AdvengerQueue = new std::queue<std::string>[this->A_Size];

    // fills the seats starting from the highest seat number
    for (int seat = this->R_Size + this->A_Size; seat > 0; seat--) {
        if (seat > 4) {
           AdvengerStack->push(std::to_string(seat));
        }else{
            RegularStack->push(std::to_string(seat));
        }
    };
 }

void SeatScheduler::ScheduleAll(std::vector<std::string> schedule) {
    std::vector<std::string> arranged;
    this->datalength = schedule.size();

    // reads each command and calls the function that matches it
    for (int s = 0; s < this->datalength; s++) {
        arranged = split(schedule[s], '-');
        if (arranged[0] == "ENTER") {
            enterCustomer(arranged[1]);
        }else if (arranged[0] == "EXIT") {
            exitCustomer(arranged[1]);
        }else if (arranged[0] == "REPORT" || schedule[s] == "REPORT") {
            Report();
        }
    }
}

void SeatScheduler::enterCustomer(std::string name) {
    // customers with a * get adventure seats first
    if (name.find('*') <= datalength) {
        if (!AdvengerStack->empty()) {
            S_A.push_back(SeatAssignment(name, std::stoi(AdvengerStack->top())));
            AdvengerStack->pop();
            return;
        }else {
            if (!RegularStack->empty()) {
                S_A.push_back(SeatAssignment(name, std::stoi(RegularStack->top())));
                RegularStack->pop();
            }
            return;
        } 
        if (AdvengerStack->empty() && RegularStack->empty()) {
            AdvengerQueue->push(name);
        }
    }else {
        if (!RegularStack->empty()) {
            S_A.push_back(SeatAssignment(name, std::stoi(RegularStack->top())));
            RegularStack->pop();
        }else {
            RegularQueue->push(name);
        }
    }
}

void SeatScheduler::exitCustomer(std::string name) {
    int size = S_A.size();

    // finds the customer and frees up their seat when they leave
    if (name.find('*') <= datalength) {
        for (int s = 0; s < size; s++) {
            if (name == S_A[s].getName()) {
                AdvengerStack->push(std::to_string(S_A[s].getSeatNumber()));

                // gives the next adventure customer a seat if someone is waiting
                if (!AdvengerQueue->empty()) {
                    enterCustomer(AdvengerQueue->front());
                    AdvengerQueue->pop();
                }
                S_A.erase(S_A.begin() + s);
            }
        }
    }else {
        for (int s = 0; s < size; s++) {
            if (name == S_A[s].getName()) {
                RegularStack->push(std::to_string(S_A[s].getSeatNumber()));

                // checks the waiting lines to see who gets the open seat
                if (!AdvengerQueue->empty()) {
                    enterCustomer(AdvengerQueue->front());
                    AdvengerQueue->pop();
                }else if (!RegularQueue->empty()) {
                    enterCustomer(RegularQueue->front());
                    RegularQueue->pop();
                }
                S_A.erase(S_A.begin() + s);
            }
        }
    }

}

void SeatScheduler::printAvailable(std::stack<std::string> *s) {
    int size = s->size();
    std::stack<std::string> temp;

    // prints the seats without changing their original order
    for (int a = 0; a < size; a++) {
        temp.push(s->top());
        std::cout << s->top() << std::endl;
        s->pop();
    }   

    int tsize = temp.size();
    for (int t = 0; t < tsize; t++) {
        s->push(temp.top());
        temp.pop();
    }
}

void SeatScheduler::printQueue(std::queue<std::string> *q){
    int qsize = q->size();
    std::string temp;

    // goes through the line and puts everyone back in the same order
    for (int l = 0; l < qsize; l++) {
        temp = q->front();
        std::cout<< temp << std::endl;
        q->pop();
        q->push(temp);
    }
};

void SeatScheduler::Report() {
    std::cout << " SHAWARMA JOINT " << std::endl;
    std::cout << " --- ALL AVAILABLE ---" << std::endl;

    // shows which seats are still open
    std::cout << "Regular Seats: " << std::endl;
    printAvailable(RegularStack);
    std::cout << "Advenger Seats: " << std::endl;
    printAvailable(AdvengerStack);

    std::cout << "___ QUEUE STATUS ___" << std::endl;

    // prints the waiting lines or lets us know if they're empty
    std::cout << "Regular Queue: " << std::endl;
    if (!RegularQueue->empty()) {
        printQueue(RegularQueue);
    }else {
         std::cout << "No One In Line.." << std::endl;
    }
    std::cout << "Advenger Queue: " << std::endl;
    if (!AdvengerQueue->empty()) {
        printQueue(AdvengerQueue);
    }else {
        std::cout << "No One In Line.." << std::endl;
    }

    // shows where each customer is sitting
    for (int i = 0; i < S_A.size(); i++) {
        std::cout << S_A[i].getName() << " Is Seating At Seat #" << S_A[i].getSeatNumber() << std::endl; 
    }

    std::cout << std::endl << "--------LOG CLOSED-------" << std::endl;

}