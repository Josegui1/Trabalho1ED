#include "ReservationSystem.hpp"


ReservationSystem::ReservationSystem(int room_count, int* room_capacities) {
    this->room_count = room_count;

    this->room_capacities = new int[this->room_count];
    for(int i = 0; i < room_count; i++) {
        this->room_capacities[i] = room_capacities[i];
    }

    this->reservations = new ReservationNode*[room_count];
    for(int i = 0; i < room_count; i++){
        this->reservations[i] = nullptr;
    }
}

ReservationSystem::~ReservationSystem(){
    for (int i = 0; i < room_count; i++) {
        ReservationNode* current = reservations[i];
        while (current != nullptr) {
            ReservationNode* next = current->next;
            delete current;
            current = next;
        }

    }

    delete reservations;
    delete room_capacities;

}

bool ReservationSystem::reserve(ReservationRequest request) {
    return false; // temp
}

bool ReservationSystem::cancel(std::string course_name) {
    return false; // temp
}

void ReservationSystem::printSchedule() {

}