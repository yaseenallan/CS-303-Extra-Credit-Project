#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <queue>
#include <vector>

using namespace std;

// Struct to represent a user's elevator request
struct Request {
    int requestTime;         // Time when the request was made
    int originFloor;         // Starting floor of the request
    int destinationFloor;    // Destination floor of the request
    bool goingUp;            // Direction of the request
};

// Elevator class manages a single elevator's state and requests
class Elevator {
public:
    Elevator();
    void handleRequest(const Request& req); // Add a request to the queue
    void move(int currentTime);             // Process one move step
    bool hasPendingRequests() const;        // Check if there are requests left
    int getCurrentFloor() const;            // Get current floor of the elevator
    bool isIdle() const;                    // Check if elevator is idle
    vector<int> getWaitingTimes() const;    // Return recorded waiting times

private:
    int currentFloor;          // Elevator's current floor
    bool goingUp;              // Current direction of movement
    queue<Request> upQueue;    // Queue for upward requests
    queue<Request> downQueue;  // Queue for downward requests
    vector<int> waitingTimes;  // Store waiting times for statistics
};

#endif