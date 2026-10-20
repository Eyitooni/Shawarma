#include <iostream>
#include <fstream>
#include <vector>
#include "SeatScheduler.cpp"

int main() {
    std::vector<std::string> data;

    std::fstream dataset;
    std::string line;

    // opens the input file and saves each line for the scheduler
    dataset.open("input.txt", std::ios_base::in);

    if (dataset.is_open()) {
        while(!dataset.eof()) {
            getline(dataset, line);
            data.push_back(line);
        }
        dataset.close();
    };

    // gets the regular and adventure seat sizes from the first line
    std::vector<std::string> SeatChart = split(data[0], ' ');
    SeatScheduler SharwarmaJoint(SeatChart[0], SeatChart[1]);

    // runs through the file and handles each command
    SharwarmaJoint.ScheduleAll(data);
};