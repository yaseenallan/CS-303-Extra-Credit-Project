#include "Elevator.h"
#include <iostream>

using namespace std;

Elevator::Elevator() : currentFloor(0), goingUp(true) {}

void Elevator::handleRequest(const Request& req) {
    if (req.goingUp)
        upQueue.push(req);
    else
        downQueue.push(req);
}

void Elevator::move(int currentTime) {
    if (goingUp) {
        if (!upQueue.empty()) {
            Request req = upQueue.front();
            upQueue.pop();
            cout << "Picking up at floor " << req.originFloor << " and going to floor " << req.destinationFloor << " (UP)\n";
            currentFloor = req.destinationFloor;
            int waitTime = currentTime - req.requestTime;
            waitingTimes.push_back(waitTime);
        } else if (!downQueue.empty()) {
            goingUp = false; // Switch direction if no more up requests
        }
    } else {
        if (!downQueue.empty()) {
            Request req = downQueue.front();
            downQueue.pop();
            cout << "Picking up at floor " << req.originFloor << " and going to floor " << req.destinationFloor << " (DOWN)\n";
            currentFloor = req.destinationFloor;
            int waitTime = currentTime - req.requestTime;
            waitingTimes.push_back(waitTime);
        } else if (!upQueue.empty()) {
            goingUp = true; // Switch back to up if no more down requests
        }
    }
}

bool Elevator::hasPendingRequests() const {
    return !upQueue.empty() || !downQueue.empty();
}

int Elevator::getCurrentFloor() const {
    return currentFloor;
}

bool Elevator::isIdle() const {
    return !hasPendingRequests();
}

vector<int> Elevator::getWaitingTimes() const {
    return waitingTimes;
}