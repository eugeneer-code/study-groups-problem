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

TEST(matrixModify)
{
    Matrix m({
      {0, 1, 2},
      {10, 11, 12},
      {20, 21, 22},
      {30, 31, 32}
    });
    Matrix m1 = m;
    m1.removeRow(1);
    ASSERT_EQ(m1.rows(), 3);
    ASSERT_EQ(m1.columns(), 3);
    ASSERT_EQ(m1.get(1,0), 20);

    Matrix m2 = m;
    m2.removeColumn(1);
    ASSERT_EQ(m2.rows(), 4);
    ASSERT_EQ(m2.columns(), 2);
    ASSERT_EQ(m2.get(2,1), 22);
}

TEST(solving)
{
    Matrix m({
        {6, 20, 18, 12, 8},
        {5, 9, 14, 7, 11},
        {12, 18, 4, 6, 11},
        {11, 17, 11, 3, 12},
        {3, 5, 4, 5, 8}
    });
    SolveTree s(m);
    bool res = s.solve();
    ASSERT_TRUE(res);
}


TEST_MAIN();