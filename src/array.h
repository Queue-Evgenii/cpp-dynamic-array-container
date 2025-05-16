#ifndef ARRAY_H
#define ARRAY_H

/**
 * @class Array
 * @brief A dynamic array container that supports resizing, 
 *        push/pop, shift/unshift, and element search operations.
 * 
 * @tparam T Type of elements stored in the array.
 */
template <typename T>
class Array {
private:
    T* data;
    int size;
    int capacity;

    /**
     * @brief Ensures that the internal storage has at least the specified capacity.
     *        If not, resizes the storage by doubling capacity until it fits.
     * 
     * @param minCapacity Minimum capacity required.
     */
    void ensureCapacity(int minCapacity) {
        if (capacity >= minCapacity) return;

        int newCapacity = capacity > 0 ? capacity * 2 : 1;
        while (newCapacity < minCapacity)
            newCapacity *= 2;

        T* newData = new T[newCapacity];
        for (int i = 0; i < size; ++i)
            newData[i] = data[i];

        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    /**
     * @brief Constructs an empty Array with an optional initial capacity.
     * 
     * @param initialCapacity Initial allocated capacity (default 4).
     */
    explicit Array(int initialCapacity = 4) 
        : data(new T[initialCapacity]()), size(0), capacity(initialCapacity) {}

    /**
     * @brief Destructor releases allocated memory.
     */
    ~Array() { delete[] data; }

    /**
     * @brief Copy constructor performs deep copy of another Array.
     * 
     * @param other Array to copy from.
     */
    Array(const Array& other) 
        : data(new T[other.capacity]()), size(other.size), capacity(other.capacity) {
        for (int i = 0; i < size; ++i)
            data[i] = other.data[i];
    }

    /**
     * @brief Copy assignment operator performs deep copy.
     * 
     * @param other Array to copy from.
     * @return Reference to *this.
     */
    Array& operator=(const Array& other) {
        if (this == &other) return *this;
        
        delete[] data;
        data = new T[other.capacity]();
        size = other.size;
        capacity = other.capacity;
        for (int i = 0; i < size; ++i)
            data[i] = other.data[i];
       
    }

    /**
     * @brief Move constructor transfers ownership from another Array.
     * 
     * @param other Array to move from.
     */
    Array(Array&& other) noexcept 
        : data(other.data), size(other.size), capacity(other.capacity) {
        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;
    }

    /**
     * @brief Move assignment operator transfers ownership from another Array.
     * 
     * @param other Array to move from.
     * @return Reference to *this.
     */
    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            capacity = other.capacity;
            other.data = nullptr;
            other.size = 0;
            other.capacity = 0;
        }
        return *this;
    }

    /**
     * @brief Access element at given index with bounds checking.
     * 
     * @param index Position of element.
     * @return Reference to element.
     * @throws std::out_of_range if index is invalid.
     */
    T& operator[](int index) {
        if (index < 0 || index >= size) throw std::out_of_range("Index out of bounds");
        return data[index];
    }

    /**
     * @brief Access element at given index with bounds checking (const version).
     * 
     * @param index Position of element.
     * @return Const reference to element.
     * @throws std::out_of_range if index is invalid.
     */
    const T& operator[](int index) const {
        if (index < 0 || index >= size) throw std::out_of_range("Index out of bounds");
        return data[index];
    }

    /**
     * @brief Returns the current number of elements in the array.
     * 
     * @return Number of elements.
     */
    int getSize() const { return size; }

    /**
     * @brief Returns the current capacity of the array.
     * 
     * @return Allocated capacity.
     */
    int getCapacity() const { return capacity; }

    /**
     * @brief Equality operator checks if two arrays contain the same elements.
     * 
     * @param other Array to compare with.
     * @return true if equal, false otherwise.
     */
    bool operator==(const Array& other) const {
        if (size != other.size) return false;
        for (int i = 0; i < size; ++i)
            if (data[i] != other.data[i]) return false;
        return true;
    }

    /**
     * @brief Inequality operator.
     * 
     * @param other Array to compare with.
     * @return true if not equal, false otherwise.
     */
    bool operator!=(const Array& other) const {
        return !(*this == other);
    }

    /**
     * @brief Appends an element to the end of the array, resizing if necessary.
     * 
     * @param value Element to add.
     */
    void push(const T& value) {
        ensureCapacity(size + 1);
        data[size++] = value;
    }

    /**
     * @brief Removes and returns the last element.
     * 
     * @return The removed element.
     * @throws std::out_of_range if array is empty.
     */
    T pop() {
        if (size == 0) throw std::out_of_range("Pop from empty array");
        return data[--size];
    }

    /**
     * @brief Inserts an element at the beginning of the array.
     * 
     * @param value Element to add.
     */
    void unshift(const T& value) {
        ensureCapacity(size + 1);
        for (int i = size; i > 0; --i)
            data[i] = data[i - 1];
        data[0] = value;
        ++size;
    }

    /**
     * @brief Removes and returns the first element.
     * 
     * @return The removed element.
     * @throws std::out_of_range if array is empty.
     */
    T shift() {
        if (size == 0) throw std::out_of_range("Shift from empty array");
        T value = data[0];
        for (int i = 1; i < size; ++i)
            data[i - 1] = data[i];
        --size;
        return value;
    }

    /**
     * @brief Finds the first element that satisfies the predicate.
     * 
     * @tparam Predicate Unary predicate type.
     * @param pred Predicate function or functor.
     * @return Pointer to the found element or nullptr if none matches.
     */
    template <typename Predicate>
    T* find(Predicate pred) const {
        for (int i = 0; i < size; ++i)
            if (pred(data[i])) return &data[i];
        return nullptr;
    }

    /**
     * @brief Finds the index of the first element that satisfies the predicate.
     * 
     * @tparam Predicate Unary predicate type.
     * @param pred Predicate function or functor.
     * @return Index of found element or -1 if none matches.
     */
    template <typename Predicate>
    int findIndex(Predicate pred) const {
        for (int i = 0; i < size; ++i)
            if (pred(data[i])) return i;
        return -1;
    }
};

#endif // ARRAY_H
