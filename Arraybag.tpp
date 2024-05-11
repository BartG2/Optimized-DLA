#include "ArrayBag.hpp"

template <typename T, std::size_t MAX_CAPACITY>
ArrayBag<T, MAX_CAPACITY>::ArrayBag() : itemCount(0) {}

template <typename T, std::size_t MAX_CAPACITY>
ArrayBag<T, MAX_CAPACITY>::~ArrayBag() {}

template <typename T, std::size_t MAX_CAPACITY>
std::size_t ArrayBag<T, MAX_CAPACITY>::getCurrentSize() const
{
    return itemCount;
}

template <typename T, std::size_t MAX_CAPACITY>
bool ArrayBag<T, MAX_CAPACITY>::isEmpty() const override { return itemCount == 0; }

template <typename T, std::size_t MAX_CAPACITY>
bool ArrayBag<T, MAX_CAPACITY>::add(const T &entry)
{
    if (itemCount < MAX_CAPACITY)
    {
        items[itemCount++] = entry;
        return true;
    }
    return false; // Bag is full
}

template <typename T, std::size_t MAX_CAPACITY>
bool ArrayBag<T, MAX_CAPACITY>::remove(const T &entry) override
{
    for (std::size_t i = 0; i < itemCount; ++i)
    {
        if (items[i] == entry)
        {
            items[i] = items[--itemCount]; // Replace with last item and decrement count
            return true;
        }
    }
    return false; // Item not found
}

template <typename T, std::size_t MAX_CAPACITY>
void ArrayBag<T, MAX_CAPACITY>::clear() override { itemCount = 0; } // Simply reset the item count

template <typename T, std::size_t MAX_CAPACITY>
std::size_t ArrayBag<T, MAX_CAPACITY>::getFrequencyOf(const T &entry) const override
{
    std::size_t frequency = 0;
    for (std::size_t i = 0; i < itemCount; ++i)
    {
        if (items[i] == entry)
        {
            ++frequency;
        }
    }
    return frequency;
}

template <typename T, std::size_t MAX_CAPACITY>
bool ArrayBag<T, MAX_CAPACITY>::contains(const T &entry) const override
{
    return getFrequencyOf(entry) > 0;
}
