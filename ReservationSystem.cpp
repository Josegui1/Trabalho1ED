#include "ReservationSystem.hpp"
#include <iostream>


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

// Transforma os dias da semana em ints para poder comparar corretamente
int ReservationSystem::dayToNumber(std::string weekday){
    if(weekday == "segunda") return 1;
    if(weekday == "terca" || weekday == "terça") return 2;
    if(weekday == "quarta") return 3;
    if(weekday == "quinta") return 4;
    if(weekday == "sexta") return 5;
    if(weekday == "sabado" || weekday == "sábado") return 6;
    return 7;
}

// Compara se o primeiro dia e horario passado vem antes do segundo
bool ReservationSystem::comesBefore(std::string weekday1, int start1, std::string weekday2, int start2){
    int d1 = dayToNumber(weekday1);
    int d2 = dayToNumber(weekday2);

    if (d1 < d2){
        return true;
    }

    if (d1 > d2){
        return false;
    }

    return start1 < start2;
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

        if (!conflito) {
            // Sala disponível! Cria o novo nó e insere ele ordenado conforme dia
            ReservationNode* novo = new ReservationNode();
            novo->course_name = request.getCourseName();
            novo->weekday     = request.getWeekday();
            novo->start_hour  = request.getStartHour();
            novo->end_hour    = request.getEndHour();
            novo->room_index  = i;
            novo->next        = nullptr;
            
            ReservationNode* current = reservations[i];
            ReservationNode* prev = nullptr;

            // Avancamos para o ultimo que vem antes do que desejamos adicionar
            while (current != nullptr && comesBefore(current->weekday, current->start_hour, novo->weekday, novo->start_hour)){
                prev = current;
                current = current->next;
            }

            // Lida com o caso onde é o primeiro
            if (prev == nullptr){
                novo->next = reservations[i];
                reservations[i] = novo; 
            }
            else{// Lida com os outros casos
                novo->next = current;
                prev->next = novo;
            }

            return true; // reserva realizada com sucesso // sala ocupada nesse horário, testa a próxima
        }


    }

    return false; // nenhuma sala disponível
}


// Importante: Este metodo remove a primeira aparicao com o nome passado. Caso queira remover mais de uma, deve-se
// passar essa funcao novamente
bool ReservationSystem::cancel(std::string course_name){
    for (int i = 0; i < room_count; i++){ // Percorre cada sala 
        ReservationNode* current = reservations[i];
        ReservationNode* prev = nullptr;
        
        // Agora avalia para cada sala cada uma das reservas e verifica se existe uma reserva com esse nome
        while (current != nullptr){ 
            // Se encontramos, removemos esse node de reserva
            if (current->course_name == course_name){
                if(prev == nullptr){ // Se o node eh o primeiro, o começo da fila passa a ser o proximo
                    reservations[i] = current->next;
                }
                else{ // Se eh qualquer no diferente do primeiro, apenas pula do anteiror para o proximo
                    prev->next = current->next;
                }
                // deletamos o no atual e retornamos true
                delete current;
                return true;
            }
            // Avancamos para os próximos nodes
            prev = current;
            current = current->next;
        }
    }
    return false;
}
// A ideia eh semelhante, varrer todas as salas e mostar cada node
void ReservationSystem::printSchedule(){
    for(int i = 0; i < room_count; i++){

        std::cout << "Room " << i + 1 << std::endl;
        ReservationNode* current = reservations[i];
        std::string last_weekday = ""; // Vamos criar isso para organizar melhor os dias

        while(current!=nullptr){
            if(current->weekday != last_weekday){
                std::cout << current->weekday << ":" << std::endl;
                last_weekday = current->weekday;
            }

            std::cout << current->start_hour << "h~" << current->end_hour << "h: " << current->course_name << std::endl;
            current = current->next;
        }
        std::cout << std::endl;
    }
}