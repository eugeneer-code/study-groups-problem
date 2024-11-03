#include "microtest.h"
#include "SolveTree.h"
#include "Matrix.h"

TEST(linkLibrary)
{
    SolveTree* solver = new SolveTree({});
    ASSERT_NOTNULL(solver);
    delete solver;
}

TEST(matrixCreate)
{
    Matrix<int> m(4,3);
    m.setData(1,0,10);
    m.setData(2,2,20);
    ASSERT_EQ(m.rows(), 4);
    ASSERT_EQ(m.columns(), 3);
    ASSERT_EQ(m.get(1,0), 10);
    ASSERT_EQ(m.get(2,2), 20);

    Matrix m2({
        {9, 20},
        {-5, 0},
        {56, 12},
        {8, 9}
    });
    ASSERT_EQ(m2.rows(), 4);
    ASSERT_EQ(m2.columns(), 2);
    ASSERT_EQ(m2.get(1,0), -5);
    ASSERT_EQ(m2.get(2,1), 12);

    m2 = m;
    ASSERT_EQ(m2.rows(), 4);
    ASSERT_EQ(m2.columns(), 3);
    ASSERT_EQ(m2.get(1,0), 10);
    ASSERT_EQ(m2.get(2,2), 20);

    Matrix m3(m2);
    ASSERT_EQ(m3.rows(), 4);
    ASSERT_EQ(m3.columns(), 3);
    ASSERT_EQ(m3.get(1,0), 10);
    ASSERT_EQ(m3.get(2,2), 20);

    ASSERT(m3 == m2);
    m3.setData(1,0, 5);
    ASSERT_FALSE(m3 == m2);
}

TEST(solving)
{
    Matrix m({
        {1000, 20, 18, 12, 8},
        {5, 1000, 14, 7, 11},
        {12, 18, 1000, 6, 11},
        {11, 17, 11, 1000, 12},
        {5, 5, 5, 5, 1000}
    });
    SolveTree s(m);
    s.nextStep();
}


TEST_MAIN();