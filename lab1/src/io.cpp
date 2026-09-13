#include "lab1/io/io.hpp"

#include <iostream>
#include <limits>
#include <stdexcept>

namespace lab1::io {
    constexpr const char* commands_text =
        "1. Создать массив\t\t 2. Напечатать элемент\n"
        "3. Вставить элемент\t\t 4. Удалить элемент\n"
        "5. Изменить размер\t\t 6. Печать\n"
        "7. Сортировка подсчетом + количество чисел в [l, r]\n"
        "0. Выход";

    void PrintMenu() {
        std::cout << commands_text << std::endl;
    }

    bool ReadInt(int& x) {
        if (std::cin >> x) {
            return true;
        }
        std::cerr << "Ошибка ввода" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }

    bool ReadSize(std::size_t& x) {
        int value{};
        if (!ReadInt(value) || value < 0) {
            std::cerr << "Ошибка ввода" << std::endl;
            return false;
        }
        x = static_cast<std::size_t>(value);
        return true;
    }

    void ArrayPrint(const int* arr, const std::size_t size) {
        for (std::size_t i = 0; i < size; i++) {
            std::cout << arr[i] << ' ';
        }
        std::cout << std::endl;
    }

    void ArrayPrintElement(const int* arr, std::size_t size, std::size_t pos) {
        if (pos >= size) {
            throw std::out_of_range("Некорректный индекс");
        }
        std::cout << arr[pos] << std::endl;
    }
}  // namespace lab1::io
