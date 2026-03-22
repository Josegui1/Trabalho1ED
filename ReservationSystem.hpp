#ifndef RESERVATIONSYSTEM_HPP
#define RESERVATIONSYSTEM_HPP

#include "ReservationRequest.hpp"
#include <string>


struct ReservationNode {
    std::string course_name;
    std::string weekday;
    int start_hour;
    int end_hour;
    int room_index;
    ReservationNode* next;
};

class ReservationSystem {

private:
    int room_count;
    int* room_capacities;

    // Lista encadeada de reservas por sala
    // reservations[i] aponta para a lista de reservas da sala i
    ReservationNode** reservations;

    // Estruturas internas escolhidas pelos alunos
    // para armazenar e gerenciar as reservas, os horários, ...

public:

    ReservationSystem(int room_count, int* room_capacities);
    ~ReservationSystem();

    bool reserve(ReservationRequest request);
    bool cancel(std::string course_name);

    void printSchedule();

    // Outros métodos utilitários necessários
    // para auxiliar nas funções requisitadas
};

#endif