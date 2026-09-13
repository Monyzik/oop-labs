#include <iostream>
#include <ostream>

#include "lab1/array_ops.hpp"
#include "lab1/io/io.hpp"

signed main() {
    int* array{nullptr};
    std::size_t size{0};
    bool ok{true};

    while (ok) {
        lab1::io::PrintMenu();
        int command;
        if (!lab1::io::ReadInt(command)) {
            continue;
        }
        try {
            switch (command) {
                case 1: {
                    std::cout << "Введите размер массива: ";
                    if (!lab1::io::ReadSize(size)) {
                        break;
                    }
                    int* new_array = lab1::ArrayCreate(size);
                    lab1::ArrayDelete(array);
                    array = new_array;
                    break;
                }
                case 2: {
                    std::cout << "Введите индекс элемента: ";
                    std::size_t pos;
                    if (!lab1::io::ReadSize(pos)) {
                        break;
                    }
                    lab1::io::ArrayPrintElement(array, size, pos);
                    break;
                }
                case 3: {
                    std::cout << "Введите индекс и значение: ";
                    std::size_t index;
                    if (!lab1::io::ReadSize(index)) {
                        break;
                    }
                    int value;
                    if (!lab1::io::ReadInt(value)) {
                        break;
                    }
                    array = lab1::ArrayInsert(array, size, index, value);
                    break;
                }
                case 4: {
                    std::cout << "Введите индекс элемента для удаления: ";
                    std::size_t index;
                    if (!lab1::io::ReadSize(index)) {
                        break;
                    }
                    array = lab1::ArrayRemove(array, size, index);
                    break;
                }
                case 5: {
                    std::cout << "Введите новый размер массива: ";
                    std::size_t new_size;
                    if (!lab1::io::ReadSize(new_size)) {
                        break;
                    }
                    array = lab1::ArrayResize(array, size, new_size);
                    size = new_size;
                    break;
                }
                case 6: {
                    lab1::io::ArrayPrint(array, size);
                    break;
                }
                case 7: {
                    array = lab1::CountingSort(array, size);
                    std::cout << "Введите диапазон [l, r]: ";
                    int l;
                    if (!lab1::io::ReadInt(l)) {
                        break;
                    }
                    int r;
                    if (!lab1::io::ReadInt(r)) {
                        break;
                    }
                    std::cout
                        << "Количество чисел в диапазоне [" << l << ", " << r
                        << "]: " << lab1::ArrayRangeCount(array, size, l, r) << std::endl;
                    break;
                }
                case 0:
                    ok = false;
                    break;
            }
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
    lab1::ArrayDelete(array);
    return 0;
}
