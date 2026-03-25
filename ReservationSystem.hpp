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
    // Essas funcoes serao utilizadas internamentes para ajudar a reservar as salas de modo ordenado
    int dayToNumber(std::string weekday);
    bool comesBefore(std::string weekday1, int start1, std::string weekday2, int start2);

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