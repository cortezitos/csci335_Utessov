#include <iostream>

extern "C" void notify_counter_reached_nine() {
    std::cout << "Counter reached 9!" << std::endl;
}