#include "pch.h"

#define BITFIELD_TESTS
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

#include "set.h"

TEST(TestSet, TestMaxPowerConstructor) {
    Set one(10);
    EXPECT_EQ(one.max_power(), 32);
    Set two(60);
    EXPECT_EQ(two.max_power(), 64);
}

TEST(TestSet, TestListConstructor) {
    Set one = { 1,2,3 };
    EXPECT_EQ(one.max_power(), 32);
    Set two = {1,2,60};
    EXPECT_EQ(two.max_power(), 64);
}

TEST(TestSet, TestCopyConstructor) {
    Set one(10);
    one.insert(5);

    Set two(one);
    EXPECT_EQ(two.max_power(), 32);
    Bitfield b1 = static_cast<Bitfield>(one);
    Bitfield b2 = static_cast<Bitfield>(two);
    EXPECT_EQ(b1, b2);
}

TEST(TestSet, TestMoveConstructor) {
    Set one(10);
    one.insert(3);
    Set two(std::move(one));
    EXPECT_EQ(two.max_power(),32);
    Bitfield b2 = static_cast<Bitfield>(two);
    EXPECT_TRUE(b2.get_bit(2));
}

TEST(TestSet, TestOperatorBitfield) {
    Set one(5);
    one.insert(1);
    Bitfield b = static_cast<Bitfield>(one);
    EXPECT_TRUE(b.get_bit(0));
}

TEST(TestSet, TestInsert) {
    Set one(10);
    one.insert(5);
    one.insert(10);
    one.insert(32);
    one.insert(1);

    Bitfield b = static_cast<Bitfield>(one);
    EXPECT_TRUE(b.get_bit(4));
    EXPECT_TRUE(b.get_bit(9));
    EXPECT_TRUE(b.get_bit(31));
    EXPECT_TRUE(b.get_bit(0));
}

TEST(TestSet, TestErase) {
    Set one(10);
    one.insert(5);
    one.insert(10);
    one.insert(32);
    one.insert(1);

    one.erase(5);
    one.erase(1);

    Bitfield b = static_cast<Bitfield>(one);
    EXPECT_FALSE(b.get_bit(4));
    EXPECT_TRUE(b.get_bit(9));
    EXPECT_TRUE(b.get_bit(31));
    EXPECT_FALSE(b.get_bit(0));
}
TEST(TestSet, TestThrowOutOfRangeInsertAndErase) {
    Set one(10);
    EXPECT_THROW(one.insert(0), std::out_of_range);
    EXPECT_THROW(one.insert(33), std::out_of_range);

    EXPECT_THROW(one.erase(0), std::out_of_range);
    EXPECT_THROW(one.erase(33), std::out_of_range);
}

TEST(TestSet, TestSumWithElem) {
    Set one(10);
    Set two = one + 5;

    Bitfield b1 = static_cast<Bitfield>(one);
    Bitfield b2 = static_cast<Bitfield>(two);

    EXPECT_FALSE(b1.get_bit(4));
    EXPECT_TRUE(b2.get_bit(4));
}

TEST(TestSet, TestSubWithElem) {
    Set one(10);
    one.insert(5);
    Set two = one - 5;

    Bitfield b1 = static_cast<Bitfield>(one);
    Bitfield b2 = static_cast<Bitfield>(two);
    EXPECT_TRUE(b1.get_bit(4));
    EXPECT_FALSE(b2.get_bit(4));
}

TEST(TestSet, TestOperationsWithEqualsByElem) {
    Set one(10);
    one += 5;
    Bitfield b1 = static_cast<Bitfield>(one);
    EXPECT_TRUE(b1.get_bit(4));

    one -= 5;
    Bitfield b2 = static_cast<Bitfield>(one);
    EXPECT_FALSE(b2.get_bit(4));
}

TEST(TestSet, TestSumWithSet) {
    Set one(10); one.insert(1);
    Set two(10); two.insert(2);

    Set res = one + two;
    Bitfield b = static_cast<Bitfield>(res);
    EXPECT_TRUE(b.get_bit(0));
    EXPECT_TRUE(b.get_bit(1));
}

TEST(TestSet, TestSubWithSet) {
    Set one(10); one.insert(1); one.insert(2);
    Set two(10); two.insert(2);

    Set res = one - two;
    Bitfield b = static_cast<Bitfield>(res);
    EXPECT_TRUE(b.get_bit(0));
    EXPECT_FALSE(b.get_bit(1));
}

TEST(TestSet, TestMultWithSet) {
    Set one(10); one.insert(1); one.insert(2);
    Set two(10); two.insert(2); two.insert(3);

    Set res = one * two;
    Bitfield b = static_cast<Bitfield>(res);
    EXPECT_FALSE(b.get_bit(0));
    EXPECT_TRUE(b.get_bit(1));
    EXPECT_FALSE(b.get_bit(2));
}


TEST(TestSet, TestOperationsWithEqualsBySet) {
    Set one(10); one.insert(1);
    Set two(10); two.insert(2);

    one += two;
    EXPECT_TRUE(one == (Set(10) + 1 + 2));

    one -= two;
    EXPECT_TRUE(one == (Set(10) + 1));

    one *= two;
    Bitfield b = static_cast<Bitfield>(one);
    EXPECT_FALSE(b.get_bit(0));
}

TEST(TestSet, TestAssigment) {
    Set one(10);
    one.insert(7);
    Set two(60);

    two = one;
    EXPECT_EQ(two.max_power(), 32);
    EXPECT_TRUE(one == two);
}

TEST(TestSet, TestAssigmentMove) {
    Set one(10);
    one.insert(8);
    Set two(60);

    two = std::move(one);
    EXPECT_EQ(two.max_power(), 32);
    Bitfield b = static_cast<Bitfield>(two);
    EXPECT_TRUE(b.get_bit(7));
}

#endif