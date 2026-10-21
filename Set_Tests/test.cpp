#include "pch.h"

//#define BITFIELD_TESTS
#define SET_TESTS

#ifdef BITFIELD_TESTS

#include "bitfield.h"

TEST(TestBitfield, TestDefaultConstructor) {
    Bitfield one;
    EXPECT_EQ(one.get_power(), 0);
    EXPECT_EQ(one.get_size(), 0);
    EXPECT_THROW(one.get_bit(1),std::out_of_range);
}

TEST(TestBitfield, TestMaxPowerConstructor) {
    Bitfield one(20);
    EXPECT_EQ(one.get_power(), 32);
    EXPECT_EQ(one.get_size(), 1);

    Bitfield two(60);
    EXPECT_EQ(two.get_power(), 64);
    EXPECT_EQ(two.get_size(), 2);
}

TEST(TestBitfield, TestInitListConstructor) {
    std::initializer_list<unsigned int> list = { 1,2 };
    Bitfield one(list);

    EXPECT_EQ(one.get_power(), 64);
    EXPECT_EQ(one.get_size(), 2);
    EXPECT_EQ(one.get_bit(31), 1);
    EXPECT_EQ(one.get_bit(62), 1);
}

TEST(TestBitfield, TestCopyConstructor) {
    Bitfield one(20);
    one.set_bit(0);
    EXPECT_EQ(one.get_bit(0), 1);
    Bitfield two(one);
    EXPECT_EQ(two.get_bit(0), 1);
}

TEST(TestBitfield, TestGetBit) {
    std::initializer_list<unsigned int> list = {128,256,1024 };
    Bitfield one(list);

    EXPECT_EQ(one.get_bit(24), 1);
    EXPECT_EQ(one.get_bit(23+32), 1);
    EXPECT_EQ(one.get_bit(21+32+32), 1);
}

TEST(TestBitfield, TestResetBit) {
    std::initializer_list<unsigned int> list = { 128,256,1024 };
    Bitfield one(list);

    EXPECT_EQ(one.get_bit(24), 1);
    EXPECT_EQ(one.get_bit(23 + 32), 1);
    EXPECT_EQ(one.get_bit(21 + 32 + 32), 1);

    one.reset_bit(24);
    one.reset_bit(23 + 32);
    one.reset_bit(21 + 32 + 32);

    EXPECT_NE(one.get_bit(24), 1);
    EXPECT_NE(one.get_bit(23 + 32), 1);
    EXPECT_NE(one.get_bit(21 + 32 + 32), 1);
}

TEST(TestBitfield, TestSetbit) {
    Bitfield one(30);
    EXPECT_EQ(one.get_bit(0), 0);
    EXPECT_EQ(one.get_bit(1), 0);
    EXPECT_EQ(one.get_bit(2), 0);
    one.set_bit(0);one.set_bit(1);one.set_bit(2);
    EXPECT_EQ(one.get_bit(0), 1);
    EXPECT_EQ(one.get_bit(1), 1);
    EXPECT_EQ(one.get_bit(2), 1);
}

TEST(TestBitfield, TestEqualsOperator) {
    Bitfield one = { 256,512,1024 };
    Bitfield two = { 256,512,1024 };
    EXPECT_TRUE(one == two);
    Bitfield tree = { 512,256,1024 };
    EXPECT_TRUE(tree != two);
    EXPECT_FALSE(tree == one);
}

TEST(TestBitfield, TestAssignment) {
    Bitfield one = { 256,512,1024 };
    Bitfield two = one;
    Bitfield tree = two;
    EXPECT_TRUE(one == two);
    EXPECT_TRUE(tree == two);
    EXPECT_TRUE(one == tree);
}

TEST(TestBitfield, TestAssignmentSemantic) {
    Bitfield one = { 256,512,1024 };
    Bitfield two = { 1,2,3 };
    two = one;
    EXPECT_EQ(two, one);
}

TEST(TestBitfield, TestOperatorAND) {
    Bitfield one = {256};
    Bitfield two = {1024};
    Bitfield tree = one & two;
    Bitfield ans = { 0 };
    EXPECT_EQ(tree, ans);
}

TEST(TestBitfield, TestOperatorOR) {
    Bitfield one = { 256 };
    Bitfield two = { 1024 };
    Bitfield tree = one | two;

    EXPECT_EQ(tree.get_bit(31-8), 1);
    EXPECT_EQ(tree.get_bit(31 - 10), 1);
    Bitfield ans = { 1280 };
    EXPECT_EQ(tree, ans);
}

TEST(TestBitfield, TestOperatorNOT) {
    Bitfield one = { 256 };
    Bitfield two = { 1024 };
    Bitfield tree = ~one;
    Bitfield ans = { 4294967039 };
    EXPECT_EQ(ans, tree);
    tree = ~two;
    ans = { 4294966271 };
    EXPECT_EQ(ans, tree);
}

TEST(TestBitfield, TestOperatorWithEquals) {
    Bitfield one = { 256 };
    Bitfield two = { 1024 };
    one &= two;
    Bitfield ans = { 0 };
    EXPECT_EQ(one, ans);

    one = { 256 };
    two = { 1024 };
    one |= two;
    EXPECT_EQ(one.get_bit(31 - 8), 1);
    EXPECT_EQ(one.get_bit(31 - 10), 1);
    ans = { 1280 };
    EXPECT_EQ(one, ans);
}
 
TEST(TestBitfield, TestThrowsOutfRange) {
    Bitfield one(20);
    EXPECT_THROW(one.get_bit(40), std::out_of_range);
    EXPECT_THROW(one.set_bit(40), std::out_of_range);
    EXPECT_THROW(one.reset_bit(40), std::out_of_range);
}

TEST(TestBitfield, TestThrowsDifferentDimension) {
    Bitfield one = { 1,2 };
    Bitfield two = { 1,2,3 };
    EXPECT_THROW(one & two, std::logic_error);
    EXPECT_THROW(one | two, std::logic_error);
    EXPECT_THROW(one &= two, std::logic_error);
    EXPECT_THROW(one |= two, std::logic_error);
}

#endif

#ifdef SET_TESTS

TEST(TestSet, TestMaxPowerConstructor) {

}

TEST(TestSet, TestCopyConstructor) {

}

TEST(TestSet, TestMoveConstructor) {

}

TEST(TestSet, TestOperatorBitfield) {

}

TEST(TestSet, TestInsert) {

}

TEST(TestSet, TestThrowOutOfRangeInsertAndErase) {

}

TEST(TestSet, TestSumWithElem) {

}

TEST(TestSet, TestSubWithElem) {

}

TEST(TestSet, TestOperationsWithEqualsByElem) {

}

TEST(TestSet, TestSumWithSet) {

}

TEST(TestSet, TestSubWithSet) {

}

TEST(TestSet, TestMultWithSet) {

}

TEST(TestSet, TestOperationsWithEqualsBySet) {

}

TEST(TestSet, TestAssigment) {

}

TEST(TestSet, TestAssigmentMove) {

}




#endif