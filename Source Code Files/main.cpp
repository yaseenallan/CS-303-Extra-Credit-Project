// Name: Yaseen Allan
// Date: 04/25/2025
// Description: This program simulates an elevator system for both single elevator and multiple elevator modes.

#include "Elevator.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <numeric>

using namespace std;

// Simulates elevator system for both single and multi-elevator configurations
void simulate(int numFloors, int numTicks, int requestFrequency, int numElevators) {
    vector<Elevator> elevators(numElevators); // Create elevators

    for (int time = 0; time < numTicks; ++time) {
        // Generate new requests periodically
        if (time % requestFrequency == 0) {
            int origin = rand() % numFloors;
            int dest = rand() % numFloors;
            while (dest == origin) dest = rand() % numFloors;

            bool up = dest > origin;
            Request req = {time, origin, dest, up};

            // For single-elevator system, just use the first elevator
            if (numElevators == 1) {
                elevators[0].handleRequest(req);
                cout << "New request at time " << time << ": Floor " << origin << " to " << dest << (up ? " (UP)" : " (DOWN)") << " assigned to Elevator 0\n";
            } else {
                // Multi-elevator: assign to the closest or idle elevator
                int bestElevator = -1;
                int minDistance = numFloors + 1;
                for (int i = 0; i < numElevators; ++i) {
                    int distance = abs(elevators[i].getCurrentFloor() - origin);
                    if (elevators[i].isIdle() || distance < minDistance) {
                        bestElevator = i;
                        minDistance = distance;
                    }
                }

                if (bestElevator != -1) {
                    elevators[bestElevator].handleRequest(req);
                    cout << "New request at time " << time << ": Floor " << origin << " to " << dest << (up ? " (UP)" : " (DOWN)") << " assigned to Elevator " << bestElevator << "\n";
                }
            }
        }

        // Process each elevator's movement
        for (int i = 0; i < numElevators; ++i) {
            if (elevators[i].hasPendingRequests()) {
                elevators[i].move(time);
            } else {
                cout << "Elevator " << i << " is idle at floor " << elevators[i].getCurrentFloor() << "\n";
            }
        }
    }

    // Calculate and print the average waiting time
    vector<int> allWaitingTimes;
    for (const auto& elevator : elevators) {
        vector<int> wt = elevator.getWaitingTimes();
        allWaitingTimes.insert(allWaitingTimes.end(), wt.begin(), wt.end());
    }

    if (!allWaitingTimes.empty()) {
        double avgWait = accumulate(allWaitingTimes.begin(), allWaitingTimes.end(), 0.0) / allWaitingTimes.size();
        cout << "\nAverage waiting time: " << avgWait << " ticks\n";
    } else {
        cout << "\nNo requests were served.\n";
    }
}

int main() {
    srand(time(0)); // Seed random number generator
    int numFloors = 10;           // Number of floors
    int numTicks = 50;            // Number of simulation ticks
    int requestFrequency = 3;     // Request every X ticks
    int numElevators = 2;         // Change to 1 for single-elevator mode

    simulate(numFloors, numTicks, requestFrequency, numElevators);

    return 0;
}