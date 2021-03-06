//
// Created by ubuntu on 2021-03-03.
//

#include "fsm.h"

unsigned int Factorial(unsigned int number) {
    int i = 5;
    return number <= 1 ? number : Factorial(number-1)*number;
}
