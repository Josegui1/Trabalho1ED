// #include <iostream>
// #include "ReservationRequest.hpp"

// int main(){
//     ReservationRequest request("Linear Algebra", "segunda", 9, 11, 40);

//     std::cout << request.getCourseName() << std::endl;
//     std::cout << request.getStudentCount() << std::endl;
//     std::cout << request.getStartHour() << std::endl;
//     std::cout << request.getEndHour()<< std::endl;
//     std::cout << request.getWeekday() << std::endl;

//     return 0;
// }

#include <iostream>
#include "ReservationSystem.hpp"
#include "ReservationRequest.hpp"

int main() {

    ReservationRequest request("Linear Algebra", "segunda", 9, 11, 40);

    std::cout << request.getCourseName() << std::endl;
    std::cout << request.getStudentCount() << std::endl;
    std::cout << request.getStartHour() << std::endl;
    std::cout << request.getEndHour()<< std::endl;
    std::cout << request.getWeekday() << std::endl;


    // Cria o sistema com 3 salas de capacidades 30, 50 e 80
    int capacities[3] = {30, 50, 80};
    ReservationSystem system(3, capacities);

    std::cout << "=== Teste 1: Reserva bem-sucedida ===" << std::endl;
    ReservationRequest r1("Estruturas de Dados", "segunda", 7, 9, 25);
    if (system.reserve(r1))
        std::cout << "Reserva realizada com sucesso!" << std::endl;
    else
        std::cout << "Falha na reserva." << std::endl;

    std::cout << "\n=== Teste 2: Teste de Capacidade ===" << std::endl;
    ReservationRequest r2("Calculo", "segunda", 8, 10, 25);
    if (system.reserve(r2))
        std::cout << "Reserva realizada com sucesso!" << std::endl;
    else
        std::cout << "Sem salas disponiveis nesse horario." << std::endl;

    std::cout << "\n=== Grade atual ===" << std::endl;
    system.printSchedule();

    return 0;
}

