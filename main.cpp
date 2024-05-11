#include "ArrayBag.hpp"
#include <iostream>

int main() {
    ArrayBag<int, 10> intBag;

    intBag.add(5);
    intBag.add(3);
    intBag.add(5); // Adding a duplicate

    std::cout << "Bag contains 5: " << intBag.contains(5) << std::endl;
    std::cout << "Bag contains 7: " << intBag.contains(7) << std::endl;
    std::cout << "Frequency of 5: " << intBag.getFrequencyOf(5) << std::endl; 

    intBag.remove(5); // Remove one instance of 5
    std::cout << "Frequency of 5 after removal: " << intBag.getFrequencyOf(5) << std::endl;

}