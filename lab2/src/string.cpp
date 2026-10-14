#include "string.hpp"

#include <cmath>
#include <cstring>
#include <istream>
#include <ostream>
#include <stdexcept>

namespace lab2 {
    String::String() : data_(new char[2]{}), capacity_(1), size_(0) {
    }

    String::String(const char* str) : String() {
        if (str == nullptr) {
            throw std::invalid_argument("Строка не может быть nullptr");
        }
        const std::size_t size = std::strlen(str);
        IncreaseCapacity(size);
        std::memcpy(data_, str, size + 1);
        size_ = size;
    }

    String::String(const String& str) : String() {
        Append(str);
    }

    String::String(String&& str) noexcept : data_{str.data_}, capacity_{str.capacity_}, size_{str.size_} {
        str.data_ = nullptr;
        str.size_ = 0;
        str.capacity_ = 0;
    }

    String::~String() {
        delete[] data_;
    }

    std::size_t String::capacity() const noexcept {
        return capacity_;
    }

    std::size_t String::size() const noexcept {
        return size_;
    }

    const char* String::c_str() const noexcept {
        return data_;
    }

    void String::Swap(String& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);\
    }

    String& String::operator=(String other) {
        Swap(other);
        return *this;
    }

    bool String::operator==(const String& other) const noexcept {
        if (size_ != other.size_) {
            return false;
        }
        for (std::size_t i = 0; i < size_; ++i) {
            if (data_[i] != other.data_[i]) {
                return false;
            }
        }
        return true;
    }

    void String::IncreaseCapacity(std::size_t need_capacity) {
        if (need_capacity <= capacity_) {
            return;
        }

        std::size_t new_capacity = capacity_ == 0 ? 1 : capacity_;
        while (new_capacity < need_capacity) {
            new_capacity *= 2;
        }

        char* new_data = new char[new_capacity + 1];
        if (size_ != 0) {
            std::memcpy(new_data, data_, size_);
        }
        new_data[size_] = '\0';
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

    void String::Append(char c) {
        IncreaseCapacity(size_ + 1);
        data_[size_] = c;
        ++size_;
        data_[size_] = '\0';
    }

    void String::Append(const char* str) {
        const String suffix{str};
        Append(suffix);
    }

    void String::Append(const String& str) {
        const std::size_t suf_size = str.size();
        if (suf_size == 0) return;
        IncreaseCapacity(size_ + suf_size);
        std::memmove(data_ + size_, str.data_, suf_size);
        size_ += suf_size;
        data_[size_] = '\0';
    }

    std::size_t String::Find(const char* substr) const {
        if (substr == nullptr) {
            throw std::invalid_argument("Подстрока не может быть nullptr");
        }
        const std::size_t size = std::strlen(substr);
        if (size_ == 0 || size > size_) {
            return size_;
        }
        for (std::size_t i = 0; i <= size_ - size; ++i) {
            if (memcmp(data_ + i, substr, size) == 0) {
                return i;
            }
        }
        return size_;
    }

    void String::WordHistogram(String* words, size_t* counts, size_t& out_size) const {
        out_size = 0;
        if (size_ != 0 and (words == nullptr or counts == nullptr)) {
            throw std::invalid_argument("Массивы слов и счетчиков не могут быть nullptr");
        }

        auto IsSeparator = [](char c) {
            return std::isspace(c) or std::ispunct(c);
        };

        std::size_t position{0};
        while (position < size_) {
            while (position < size_ and IsSeparator(data_[position])) {
                ++position;
            }
            if (position == size_) {
                break;
            }
            String word;
            while (position < size_ and !IsSeparator(data_[position])) {
                word.Append(data_[position]);
                ++position;
            }

            std::size_t index{0};
            while (index < out_size and !(words[index] == word)) {
                ++index;
            }
            if (index < out_size) {
                ++counts[index];
            } else {
                words[out_size] = word;
                counts[out_size] = 1;
                ++out_size;
            }
        }
    }


    std::ostream& operator<<(std::ostream& out, const String& s) {
        return out.write(s.c_str(), static_cast<std::streamsize>(s.size()));
    }

    std::istream& operator>>(std::istream& in, String& s) {
        const std::istream::sentry sentry{in};
        if (!sentry) {
            return in;
        }

        String word;
        while (true) {
            const auto next = in.peek();
            if (next == std::char_traits<char>::eof()) {
                break;
            }
            if (std::isspace(next)) {
                break;
            }
            word.Append(static_cast<char>(in.get()));
        }

        if (word.size() == 0) {
            in.setstate(std::ios_base::failbit);
        } else if (!in.fail()) {
            s.Swap(word);
        }

        return in;
    }
}
