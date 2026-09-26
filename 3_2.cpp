#include <iostream>
#include <memory>

int main() {
    int *a = new int(444);
    int size = 7;
    int *b = new int[size];

    for (int i=0; i<size; i++){
        b[i] = i*10;
        std::cout << b[i] << " ";
    }
    std::cout << "\n";

    int* vis_ptr = b;
    std::cout << "\n" << *vis_ptr << "\n";
    delete[] b; 
    b = nullptr;
    std::cout << "\n" << *vis_ptr << "\n";
    int newSize = size + 1;
    int* newArr = new int[newSize];
    int mid = size / 2;
    int newValue = 1234;
    for (int i = 0; i < mid; ++i) {
        newArr[i] = (i + 1) * 10;
    }
    newArr[mid] = newValue;
    for (int i = mid; i < size; ++i) {
        newArr[i + 1] = (i + 1) * 10;
    }
    b = newArr;
    size = newSize;

    std::cout << "New arr: ";
    for (int i = 0; i < size; ++i) {
        std::cout << b[i] << " ";
    }
    std::cout << "\n";

    delete a;
    a = nullptr;
    delete[] b;
    b = nullptr;
    std::cout << "Success";
}