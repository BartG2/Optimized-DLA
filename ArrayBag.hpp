#include <cstdlib>  // For std::size_t
#include "AbstractBag.hpp" // Include the interface

template <typename T, std::size_t MAX_CAPACITY>
class ArrayBag : public AbstractBag<T> {
private:
    T items[MAX_CAPACITY];    // Fixed-size C-style array to store items
    std::size_t itemCount;    // Number of items currently in the bag

public:
    // Constructor
    ArrayBag() : itemCount(0) {} 

    // Destructor (not strictly necessary, but good practice)
    ~ArrayBag() {}

    // Implementations of the AbstractBag interface
    std::size_t getCurrentSize() const override { return itemCount; }
    bool isEmpty() const override { return itemCount == 0; }

    bool add(const T& entry) override {
        if (itemCount < MAX_CAPACITY) {
            items[itemCount++] = entry;
            return true;
        }
        return false; // Bag is full
    }

    bool remove(const T& entry) override {
        for (std::size_t i = 0; i < itemCount; ++i) {
            if (items[i] == entry) {
                items[i] = items[--itemCount]; // Replace with last item and decrement count
                return true;
            }
        }
        return false; // Item not found
    }

    void clear() override { itemCount = 0; } // Simply reset the item count

    std::size_t getFrequencyOf(const T& entry) const override {
        std::size_t frequency = 0;
        for (std::size_t i = 0; i < itemCount; ++i) {
            if (items[i] == entry) {
                ++frequency;
            }
        }
        return frequency;
    }

    bool contains(const T& entry) const override {
        return getFrequencyOf(entry) > 0; 
    }
};