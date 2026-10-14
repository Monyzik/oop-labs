#include "string.hpp"

#include <exception>
#include <iostream>

int main() {
    lab2::String* words{nullptr};
    std::size_t* counts{nullptr};

    try {
        lab2::String text;
        char ch{};

        std::cout << "Введите строку:\n";
        while (std::cin.get(ch) && ch != '\n') {
            text.Append(ch);
        }

        if (std::cin.bad()) {
            throw std::runtime_error("Ошибка ввода");
        }

        words = new lab2::String[text.size()];
        counts = new std::size_t[text.size()];
        std::size_t out_size{0};

        text.WordHistogram(words, counts, out_size);
        std::cout << "Уникальных слов: " << out_size << '\n';
        for (std::size_t i = 0; i < out_size; i++) {
            std::cout << words[i] << ": " << counts[i] << '\n';
        }
    } catch (const std::exception& e) {
        delete [] counts;
        delete [] words;
        std::cerr << e.what() << '\n';
        return 1;
    }
    delete [] counts;
    delete [] words;
    return 0;
}
