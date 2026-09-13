#include "lab1/array_ops.hpp"

#include <algorithm>
#include <cstddef>
#include <stdexcept>

namespace lab1 {
    int* ArrayCreate(const std::size_t size) {
        if (size == 0) {
            return nullptr;
        }
        return new int[size]{};
    }

    void ArrayDelete(int*& arr) {
        delete[] arr;
        arr = nullptr;
    }

    int* ArrayResize(int* arr, const std::size_t size, const std::size_t new_size) {
        int* new_arr = ArrayCreate(new_size);
        for (std::size_t i = 0; i < std::min(size, new_size); i++) {
            new_arr[i] = arr[i];
        }
        ArrayDelete(arr);
        return new_arr;
    }

    int* ArrayInsert(int* arr, std::size_t& size, const std::size_t index, const int value) {
        if (index > size) {
            throw std::out_of_range("Некорректный индекс");
        }
        int* new_arr = ArrayCreate(size + 1);
        for (std::size_t i = 0; i < index; i++) {
            new_arr[i] = arr[i];
        }
        new_arr[index] = value;
        for (std::size_t i = index; i < size; i++) {
            new_arr[i + 1] = arr[i];
        }
        ArrayDelete(arr);
        size++;
        return new_arr;
    }

    int* ArrayRemove(int* arr, std::size_t& size, const std::size_t pos) {
        if (pos >= size) {
            throw std::out_of_range("Некорректный индекс");
        }
        int* new_arr = ArrayCreate(size - 1);
        for (std::size_t i = 0; i < pos; i++) {
            new_arr[i] = arr[i];
        }
        for (std::size_t i = pos; i < size - 1; i++) {
            new_arr[i] = arr[i + 1];
        }
        ArrayDelete(arr);
        size--;
        return new_arr;
    }

    int* CountingSort(int* arr, std::size_t size) {
        if (size == 0) {
            return nullptr;
        }
        int minimum = arr[0], maximum = arr[0];
        for (std::size_t i = 1; i < size; i++) {
            minimum = std::min(minimum, arr[i]);
            maximum = std::max(maximum, arr[i]);
        }
        if (minimum < 0 or maximum > 1023) {
            throw std::invalid_argument("Значения элементов массива выходят за пределы допустимого диапазона");
        }
        for (std::size_t i = 0; i < size; i++) {
            arr[i] -= minimum;
        }
        maximum -= minimum;
        int* count = new int[maximum + 1]{};
        for (std::size_t i = 0; i < size; i++) {
            count[arr[i]]++;
        }
        for (int i = 1; i <= maximum; i++) {
            count[i] += count[i - 1];
        }
        int* sorted_arr = new int[size];
        while (size--) {
            sorted_arr[--count[arr[size]]] = arr[size] + minimum;
        }
        ArrayDelete(arr);
        ArrayDelete(count);
        return sorted_arr;
    }

    std::size_t ArrayRangeCount(const int* arr, const std::size_t size, const int lo, const int hi) {
        if (lo > hi) {
            throw std::invalid_argument("Некорректный диапазон");
        }
        int l = -1, r = static_cast<int>(size);
        while (r - l > 1) {
            int mid = (l + r) / 2;
            if (arr[mid] < lo) {
                l = mid;
            } else {
                r = mid;
            }
        }
        std::size_t left = r;
        l = -1, r = static_cast<int>(size);
        while (r - l > 1) {
            int mid = (l + r) / 2;
            if (arr[mid] <= hi) {
                l = mid;
            } else {
                r = mid;
            }
        }
        std::size_t right = r;
        return right - left;
    }
}  // namespace lab1
