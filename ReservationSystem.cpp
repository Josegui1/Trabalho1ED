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

    delete[] reservations;
    delete[] room_capacities;

}

bool ReservationSystem::reserve(ReservationRequest request) {

    for (int i = 0; i < room_count;) {

        if (room_capacities[i] < request.getStudentCount()){
            i++;
        }

        bool conflito = false;
        ReservationNode* current = reservations[i];
        while(current != nullptr) {
            if(current->weekday == request.getWeekday() && current->start_hour < request.getStartHour()
        && current->end_hour < request.getEndHour()) {
            conflito = true;
            break;
        }
            current = current->next;
        }
        if (conflito = true) {
            i++;
        } else {
            ReservationNode* new_reservation = new ReservationNode;
            new_reservation->course_name = request.getCourseName();
            new_reservation->weekday = request.getWeekday();
            new_reservation->start_hour = request.getStartHour();
            new_reservation->end_hour = request.getEndHour();
            new_reservation->room_index = i;
            new_reservation->next = reservations[i];
            reservations[i] = new_reservation;
            return true;
        }

        }
        return 0;
    }


bool ReservationSystem::cancel(std::string course_name) {
    return false; // temp
}

void ReservationSystem::printSchedule() {

}