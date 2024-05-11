#ifndef ARRAYBAG_HPP
#define ARRAYBAG_HPP

#include <cstdlib>
#include "AbstractBag.hpp"

template <typename T, std::size_t MAX_CAPACITY>
class ArrayBag : public AbstractBag<T> {
public:
    ArrayBag();  
    ~ArrayBag(); 

    std::size_t getCurrentSize() const override;
    bool isEmpty() const override;
    bool add(const T& entry) override;
    bool remove(const T& entry) override;
    void clear() override;
    std::size_t getFrequencyOf(const T& entry) const override;
    bool contains(const T& entry) const override;

private:
    T items[MAX_CAPACITY];  
    std::size_t itemCount;  
};

#endif // ARRAYBAG_HPP