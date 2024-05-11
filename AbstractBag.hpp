#include <cstdlib>

template<typename T> class AbstractBag{
public:
    /*destructor/
    virtual ~AbstractBag() {}

/**returns size of bag*/
virtual std::size_t getCurrentSize() const = 0;

/**returns true if bag is empty*/
virtual bool isEmpty() const = 0;

/**adds entry to bag*/
virtual bool add(const T& entry) = 0;

/**removes entry from bag*/
virtual bool remove(const T& entry) = 0;

/**clears bag*/
virtual void clear() = 0;

/**returns frequency/number of repeats of entry in bag*/
virtual std::size_t getFrequencyOf(const T& entry) const = 0;

/**returns true if bag contains entry*/
virtual bool contains(const T& entry) const = 0;

};