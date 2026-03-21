#include <iostream>
#include "ReservationRequest.hpp"

int main(){
    ReservationRequest request("Linear Algebra", "segunda", 9, 11, 40);

    std::cout << request.getCourseName() << std::endl;
    std::cout << request.getStudentCount() << std::endl;
    std::cout << request.getStartHour() << std::endl;
    std::cout << request.getEndHour()<< std::endl;
    std::cout << request.getWeekday() << std::endl;

    return 0;
}