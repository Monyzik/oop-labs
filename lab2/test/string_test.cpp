#include "string.hpp"

#include "gtest/gtest.h"

TEST(StringTest, CreateEmptyString) {
    lab2::String value;

    EXPECT_EQ(value.size(), 0);
    EXPECT_EQ(value.capacity(), 1);
    EXPECT_STREQ(value.c_str(), "");
}

TEST(StringTest, CopyConstructor) {
    const lab2::String value{"abc"};
    lab2::String copy{value};

    EXPECT_NE(copy.c_str(), value.c_str());

    copy.Append('d');

    EXPECT_STREQ(value.c_str(), "abc");
    EXPECT_STREQ(copy.c_str(), "abcd");
}

TEST(StringTest, MoveConstructor) {
    lab2::String value{"abc"};
    const char* old_data = value.c_str();
    lab2::String moved{std::move(value)};

    EXPECT_EQ(value.size(), 0);
    EXPECT_EQ(value.capacity(), 0);
    EXPECT_EQ(value.c_str(), nullptr);

    EXPECT_STREQ(moved.c_str(), "abc");
    EXPECT_EQ(moved.c_str(), old_data);

    value.Append('x');

    ASSERT_NE(value.c_str(), nullptr);
    EXPECT_EQ(value.size(), 1);
    EXPECT_STREQ(value.c_str(), "x");
    EXPECT_STREQ(moved.c_str(), "abc");
}

TEST(StringTest, CopyAssignment) {
    lab2::String value{"abc"};
    lab2::String copy;
    copy = value;

    EXPECT_NE(copy.c_str(), value.c_str());

    copy.Append('d');

    EXPECT_STREQ(value.c_str(), "abc");
    EXPECT_STREQ(copy.c_str(), "abcd");
}

TEST(StringTest, MoveAssignment) {
    lab2::String value{"abc"};
    const char* old_data = value.c_str();
    lab2::String moved;
    moved = std::move(value);

    EXPECT_EQ(value.size(), 0);
    EXPECT_EQ(value.capacity(), 0);
    EXPECT_EQ(value.c_str(), nullptr);

    EXPECT_STREQ(moved.c_str(), "abc");
    EXPECT_EQ(moved.c_str(), old_data);
}

TEST(StringTest, SelfAssignment) {
    lab2::String value{"abc"};
    const lab2::String& same = value;
    value = same;

    EXPECT_EQ(value.size(), 3);
    EXPECT_STREQ(value.c_str(), "abc");
}

TEST(StringTest, AppendWithDoubledCapacity) {
    lab2::String value{"abc"};
    const std::size_t old_capacity = value.capacity();
    value.Append("def");

    EXPECT_GT(value.capacity(), old_capacity);
    EXPECT_STREQ(value.c_str(), "abcdef");
}

TEST(StringTest, AppendSelf) {
    lab2::String value{"abc"};
    value.Append(value);

    EXPECT_EQ(value.size(), 6);
    EXPECT_STREQ(value.c_str(), "abcabc");
}

TEST(StringTest, FindSubstringSuccess) {
    const lab2::String value{"abcabc"};
    EXPECT_EQ(value.Find("abc"), 0);
    EXPECT_EQ(value.Find("bca"), 1);
    EXPECT_EQ(value.Find("cab"), 2);
}

TEST(StringTest, FindSubstringNotFound) {
    const lab2::String value{"abcabc"};
    EXPECT_EQ(value.Find("xyz"), value.size());
    EXPECT_EQ(value.Find("abcd"), value.size());
    EXPECT_EQ(value.Find("abcabc"), 0);
    EXPECT_EQ(value.Find("cabc"), 2);
}

TEST(StringTest, FindSubstringEmpty) {
    const lab2::String value{"abcabc"};
    EXPECT_EQ(value.Find(""), 0);
}

TEST(StringTest, HistogramMatching) {
    const lab2::String text{"a bb a c a"};
    lab2::String words[10];
    std::size_t counts[10];
    std::size_t out_size{0};

    text.WordHistogram(words, counts, out_size);

    ASSERT_EQ(out_size, 3);

    EXPECT_STREQ(words[0].c_str(), "a");
    EXPECT_EQ(counts[0], 3);

    EXPECT_STREQ(words[1].c_str(), "bb");
    EXPECT_EQ(counts[1], 1);

    EXPECT_STREQ(words[2].c_str(), "c");
    EXPECT_EQ(counts[2], 1);

    EXPECT_STREQ(text.c_str(), "a bb a c a");
}

TEST(StringTest, EmptyHistogram) {
    const lab2::String text;
    lab2::String words[10];
    std::size_t counts[10];
    std::size_t out_size{0};

    text.WordHistogram(words, counts, out_size);

    EXPECT_EQ(out_size, 0);
}

TEST(StringTest, HistogramWithSeparators) {
    const lab2::String text{"a, bb! a? c; a"};
    lab2::String words[10];
    std::size_t counts[10];
    std::size_t out_size{0};

    text.WordHistogram(words, counts, out_size);

    ASSERT_EQ(out_size, 3);

    EXPECT_STREQ(words[0].c_str(), "a");
    EXPECT_EQ(counts[0], 3);

    EXPECT_STREQ(words[1].c_str(), "bb");
    EXPECT_EQ(counts[1], 1);

    EXPECT_STREQ(words[2].c_str(), "c");
    EXPECT_EQ(counts[2], 1);
}

TEST(StringTest_Throw, NullPointerArgument) {
    EXPECT_THROW(lab2::String{nullptr}, std::invalid_argument);

    lab2::String value{"abcd"};
    EXPECT_THROW(value.Append(nullptr), std::invalid_argument);
    EXPECT_STREQ(value.c_str(), "abcd");

    EXPECT_THROW(value.Find(nullptr), std::invalid_argument);

    lab2::String words[1];
    std::size_t counts[1]{};
    std::size_t out_size{10};

    EXPECT_THROW(value.WordHistogram(nullptr, counts, out_size), std::invalid_argument);
    EXPECT_EQ(out_size, 0);
}
