#ifndef ARRAY_BAG_HPP 
#define ARRAY_BAG_HPP

#include <cstdlib>  // For std::size_t
#include "AbstractBag.hpp"

template <typename T, std::size_t MAX_CAPACITY>
class ArrayBag : public AbstractBag<T> {
public:
    // Constructor
    ArrayBag();

    // Destructor (not strictly necessary, but good practice)
    ~ArrayBag(); 

    // Implementations of the AbstractBag interface (only declarations)
    std::size_t getCurrentSize() const override;
    bool isEmpty() const override;
    bool add(const T& entry) override;
    bool remove(const T& entry) override;
    void clear() override;
    std::size_t getFrequencyOf(const T& entry) const override;
    bool contains(const T& entry) const override;

private:
    T items[MAX_CAPACITY];    // Fixed-size C-style array to store items
    std::size_t itemCount;    // Number of items currently in the bag
};

#endif // ARRAY_BAG_HPP