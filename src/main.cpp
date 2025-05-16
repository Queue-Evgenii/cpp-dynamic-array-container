#include <iostream>
#include "array.h"

void printArray(const Array<int>& arr) {
    for (int i = 0; i < arr.getSize(); ++i) {
        std::cout << arr[i] << "\t";
    }
    std::cout << "\n";
}

int main() {
    Array<int> arr(5);

    std::cout << "Initial size: " << arr.getSize() << "\n";
    std::cout << "Initial capacity: " << arr.getCapacity() << "\n";

    arr.push(1);
    arr.push(2);
    arr.push(3);

    std::cout << "Size after adding 3 elements: " << arr.getSize() << "\n";
    std::cout << "Capacity after adding 3 elements: " << arr.getCapacity() << "\n";

    arr.push(4);
    arr.push(5);
    arr.push(6);

    std::cout << "Size after adding 6 elements: " << arr.getSize() << "\n";
    std::cout << "Capacity after expansion: " << arr.getCapacity() << "\n";

    arr.push(1);
    arr.push(2);
    arr.push(3);
    arr.unshift(0);

    printArray(arr);

    arr.pop();
    arr.shift();

    printArray(arr);

    int index = arr.findIndex([](int x) { return x == 2; });
    std::cout << "Index of 2: " << index << "\n";

    int* found = arr.find([](int x) { return x > 3; });
    if (found) std::cout << "Found: " << *found << "\n";

    return 0;
}
