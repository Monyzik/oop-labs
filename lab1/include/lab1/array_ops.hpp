#pragma once
#include <cstddef>

namespace lab1 {
    int* ArrayCreate(std::size_t size);

    void ArrayDelete(int*& arr);
    int* ArrayResize(int* arr, std::size_t size, std::size_t new_size);

    int* ArrayInsert(int* arr, std::size_t& size, std::size_t index, int value);

    int* ArrayRemove(int* arr, std::size_t& size, std::size_t pos);

    int* CountingSort(int* arr, std::size_t size);

    std::size_t ArrayRangeCount(const int* arr, std::size_t size, int lo, int hi);
}  // namespace lab1
