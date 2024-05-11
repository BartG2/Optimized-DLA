#include <cstdlib>
#include <algorithm> // For std::find
#include "AbstractBag.hpp"

template <typename T>
class ArrayBag : public AbstractBag<T> {
private:
    static const int DEFAULT_CAPACITY = 10; // Initial array size
    T *items;                               // Dynamic array for items
    int itemCount;                          // Number of items in the bag
    int maxItems;                           // Current maximum capacity

    // Helper function to resize the array when needed
    void doubleCapacity() {
        maxItems *= 2;
        T *temp = new T[maxItems];
        for (int i = 0; i < itemCount; ++i) {
            temp[i] = items[i];
        }
        delete[] items;
        items = temp;
    }

public:
    // Constructor
    ArrayBag(int capacity = DEFAULT_CAPACITY) : itemCount(0), maxItems(capacity) {
        items = new T[maxItems]; 
    }

    // Destructor
    ~ArrayBag() {
        delete[] items;
    }

    std::size_t getCurrentSize() const override {
        return itemCount;
    }

    bool isEmpty() const override {
        return itemCount == 0;
    }

    bool add(const T& entry) override {
        if (itemCount == maxItems) {
            doubleCapacity(); // If full, double the size
        }
        items[itemCount] = entry;
        ++itemCount;
        return true;
    }

    bool remove(const T& entry) override {
        int index = -1;
        for (int i = 0; i < itemCount; ++i) {
            if (items[i] == entry) {
                index = i;
                break;
            }
        }

        if (index >= 0) {
            // Shift items over to remove the element
            for (int i = index; i < itemCount - 1; ++i) {
                items[i] = items[i + 1];
            }
            --itemCount;
            return true;
        }
        return false; // Entry not found
    }

    void clear() override {
        itemCount = 0; // Reset the item count (no need to delete elements)
    }

    std::size_t getFrequencyOf(const T& entry) const override {
        std::size_t count = 0;
        for (int i = 0; i < itemCount; ++i) {
            if (items[i] == entry) {
                ++count;
            }
        }
        return count;
    }

    bool contains(const T& entry) const override {
        return std::find(items, items + itemCount, entry) != items + itemCount;
    }
};