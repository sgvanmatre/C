#include <iostream>
#include "gtest/gtest.h"
#include "square.h"


class SquareTest : public testing::Test {
    protected:
        Square mySquare;
        void setSideLength(int length){
            ASSERT_EQ(0, mySquare.getLength());
            mySquare.setLength(length);
            ASSERT_EQ(length, mySquare.getLength());
        };
};


TEST_F(SquareTest, whenLengthIsOne_PeremeterIsFourAreaIsOne){
    setSideLength(1);
    ASSERT_EQ(4, mySquare.getPeremeter());
    ASSERT_EQ(1, mySquare.getArea());
}

TEST_F(SquareTest, whenLengthIsTwo_PeremeterIsEightAreaIsFour){
    setSideLength(2);
    ASSERT_EQ(8, mySquare.getPeremeter());
    ASSERT_EQ(4, mySquare.getArea());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}