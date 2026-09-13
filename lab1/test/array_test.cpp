#include <cstddef>

#include <gtest/gtest.h>

#include "lab1/array_ops.hpp"

TEST(CreateArrayTest, CreateAndInsertArray) {
    std::size_t size{10};
    int* array = lab1::ArrayCreate(size);
    for (int i = 0; i < 10; i++) {
        array[i] = i;
    }
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(i, array[i]);
    }
    lab1::ArrayDelete(array);
}

TEST(ArrayDeleteArrayTest, DeleteArray) {
    std::size_t size{5};
    int* array = lab1::ArrayCreate(size);
    lab1::ArrayDelete(array);
    EXPECT_EQ(array, nullptr);
}

TEST(ArrayInsertTest, InsertElement) {
    std::size_t size{5};
    int* array = lab1::ArrayCreate(size);
    for (int i = 0; i < 5; i++) {
        array[i] = i;
    }
    array = lab1::ArrayInsert(array, size, 2, 10);
    EXPECT_EQ(size, 6);
    EXPECT_EQ(array[1], 1);
    EXPECT_EQ(array[2], 10);
    EXPECT_EQ(array[3], 2);
    lab1::ArrayDelete(array);
}

TEST(InsertArrayTest_Throw, OutOfRangeInsert) {
    std::size_t size{0};
    int* array = lab1::ArrayCreate(size);
    EXPECT_THROW(lab1::ArrayInsert(array, size, 1, 10), std::out_of_range);
    lab1::ArrayDelete(array);
}

TEST(ArrayResizeTest, ResizeArrayMoreThenBefore) {
    std::size_t size{5};
    int* array = lab1::ArrayCreate(size);
    for (int i = 0; i < 5; i++) {
        array[i] = i;
    }
    array = lab1::ArrayResize(array, size, 10);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(i, array[i]);
    }
    EXPECT_EQ(array[9], 0);
    lab1::ArrayDelete(array);
}

TEST(ArrayResizeTest, ResizeArrayLessThanBefore) {
    std::size_t size{5};
    int* array = lab1::ArrayCreate(size);
    for (int i = 0; i < 5; i++) {
        array[i] = i;
    }
    array = lab1::ArrayResize(array, size, 3);
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(i, array[i]);
    }
    lab1::ArrayDelete(array);
}

TEST(ArrayRemoveTest, RemoveElement) {
    std::size_t size{5};
    int* array = lab1::ArrayCreate(size);
    for (int i = 0; i < 5; i++) {
        array[i] = i;
    }
    array = lab1::ArrayRemove(array, size, 2);
    EXPECT_EQ(size, 4);
    EXPECT_EQ(array[0], 0);
    EXPECT_EQ(array[1], 1);
    EXPECT_EQ(array[2], 3);
    EXPECT_EQ(array[3], 4);
    lab1::ArrayDelete(array);
}

TEST(ArrayRemoveTest_Throw, RemoveElementOutOfRange) {
    std::size_t size{0};
    int* array = lab1::ArrayCreate(size);
    EXPECT_THROW(lab1::ArrayRemove(array, size, 1), std::out_of_range);
    lab1::ArrayDelete(array);
}

TEST(ArrayCountingSortTest, SortArray) {
    std::size_t size{5};
    int* array = lab1::ArrayCreate(size);
    array[0] = 3;
    array[1] = 1;
    array[2] = 4;
    array[3] = 2;
    array[4] = 0;
    array = lab1::CountingSort(array, size);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(i, array[i]);
    }
    lab1::ArrayDelete(array);
}

TEST(ArrayCountingSortTest, SortEmptyArray) {
    std::size_t size{0};
    int* array = lab1::ArrayCreate(size);
    array = lab1::CountingSort(array, size);
    EXPECT_EQ(array, nullptr);
    lab1::ArrayDelete(array);
}

TEST(ArrayCountingSortTest_Throw, SortArrayInvalidArgument) {
    std::size_t size{2};
    int* array = lab1::ArrayCreate(size);
    array[0] = 10000;
    array[1] = -1;
    EXPECT_THROW(lab1::CountingSort(array, size), std::invalid_argument);
    lab1::ArrayDelete(array);
}

TEST(ArrayRangeCountTest, RangeCount) {
    std::size_t size{5};
    int* array = lab1::ArrayCreate(size);
    for (int i = 0; i < 5; i++) {
        array[i] = i;
    }
    EXPECT_EQ(lab1::ArrayRangeCount(array, size, 1, 3), 3);
    EXPECT_EQ(lab1::ArrayRangeCount(array, size, 0, 4), 5);
    EXPECT_EQ(lab1::ArrayRangeCount(array, size, 5, 10), 0);
    EXPECT_EQ(lab1::ArrayRangeCount(array, size, -10, -1), 0);
    lab1::ArrayDelete(array);
}

TEST(ArrayRangeCountTest, RangeCountOfEmptyArray) {
    std::size_t size{0};
    int* array = lab1::ArrayCreate(size);
    EXPECT_EQ(lab1::ArrayRangeCount(array, size, 0, 10), 0);
    lab1::ArrayDelete(array);
}

TEST(ArrayRangeCountTest_Throw, InvalidArgumentForLR) {
    std::size_t size{5};
    int* array = lab1::ArrayCreate(size);
    for (int i = 0; i < 5; i++) {
        array[i] = i;
    }
    EXPECT_THROW(lab1::ArrayRangeCount(array, size, 3, 1), std::invalid_argument);
    lab1::ArrayDelete(array);
}
