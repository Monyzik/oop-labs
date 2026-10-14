#pragma once
#include <cstddef>
#include <iosfwd>

namespace lab2 {
    class String {
    public:
        String();
        explicit String(const char* str);
        String(const String& str);
        String(String&& str) noexcept;
        ~String();

        String& operator=(String other);
        bool operator==(const String& other) const noexcept;

        void Swap(String& other) noexcept;

        std::size_t capacity() const noexcept;
        std::size_t size() const noexcept;
        const char* c_str() const noexcept;

        std::size_t Find(const char* substr) const;
        void WordHistogram(String* words, size_t* counts, size_t& out_size) const;

        void Append(const char* str);
        void Append(const String& str);
        void Append(char c);

    private:
        void IncreaseCapacity(std::size_t new_capacity);

        char* data_{nullptr};

        std::size_t capacity_{0};
        std::size_t size_{0};
    };

    std::ostream& operator<<(std::ostream& out, const String& s);

    std::istream& operator>>(std::istream& in, String& s);
}  // namespace lab2
