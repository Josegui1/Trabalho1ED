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
    // Percorre cada sala em ordem
    for (int i = 0; i < room_count; i++) {

        // Verifica se a sala tem capacidade suficiente
        if (room_capacities[i] < request.getStudentCount()) {
            continue; // sala muito pequena, testa a próxima
        }

        // Verifica se há conflito de horário nessa sala
        bool conflito = false;
        ReservationNode* current = reservations[i];
        while (current != nullptr) {
            // Mesmo dia E horários se sobrepõem?
            if (current->weekday == request.getWeekday() &&
                current->start_hour < request.getEndHour() &&
                current->end_hour > request.getStartHour()) {
                conflito = true;
                break;
            }
            current = current->next;
        }

        if (conflito) {
            continue; // sala ocupada nesse horário, testa a próxima
        }

        // Sala disponível! Cria o novo nó e insere no início da lista
        ReservationNode* novo = new ReservationNode();
        novo->course_name = request.getCourseName();
        novo->weekday     = request.getWeekday();
        novo->start_hour  = request.getStartHour();
        novo->end_hour    = request.getEndHour();
        novo->room_index  = i;
        novo->next        = reservations[i];
        reservations[i]   = novo;

        return true; // reserva realizada com sucesso
    }

    return false; // nenhuma sala disponível
}


bool ReservationSystem::cancel(std::string course_name) {
    return false; // temp
}

void ReservationSystem::printSchedule() {

}