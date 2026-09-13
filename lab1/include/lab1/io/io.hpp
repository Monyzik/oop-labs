#pragma once
#include <cstddef>

namespace lab1::io {
    void ArrayPrint(const int* arr, std::size_t size);

    void ArrayPrintElement(const int* arr, std::size_t size, std::size_t pos);

    bool ReadInt(int& x);

    bool ReadSize(std::size_t& x);

    void PrintMenu();
}  // namespace lab1::io
