#include "microtest.h"
#include "BBSolver.h"
#include "Matrix.h"

TEST(linkLibrary)
{
    BBSolver* solver = new BBSolver();
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
    m2.print();

}


TEST_MAIN();