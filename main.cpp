#include <iostream>
#include "ArrayBag.cpp"

int main() {
    ArrayBag<int> myBag;
    myBag.add(5);
    myBag.add(3);
    myBag.add(5);

    std::cout << "Bag contains 5: " << myBag.contains(5) << std::endl;  
    std::cout << "Frequency of 5: " << myBag.getFrequencyOf(5) << std::endl; 
}