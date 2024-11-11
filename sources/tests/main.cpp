#include "microtest.h"
#include "SolveTree.h"
#include "Matrix.h"
#include <random>
#include <chrono>

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
        {5, 6, 4, 8, 4},
        {18, 17, 28, 27, 9},
        {22, 0, 12, 17, 5},
        {24, 5, 10, 7, 25},
        {17, 7, 2, 22, 0}
    });
    SolveTree s(m);
    bool res = s.solve();
    ASSERT_TRUE(res);

    Matrix m2({
        {6, 6, 6, 6, 6},
        {6, 6, 6, 6, 6},
        {6, 6, 6, 6, 6},
        {6, 6, 6, 6, 6},
        {6, 6, 6, 6, 6}
    });
    SolveTree s2(m2);
    bool res2 = s2.solve();
    ASSERT_TRUE(res2);
}

TEST(randomMatrix)
{
    // init random
    std::random_device rd;
    std::mt19937::result_type seed = rd() ^ (
            (std::mt19937::result_type)
            std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::system_clock::now().time_since_epoch()
                ).count() +
            (std::mt19937::result_type)
            std::chrono::duration_cast<std::chrono::microseconds>(
                std::chrono::high_resolution_clock::now().time_since_epoch()
                ).count() );
    std::mt19937 gen(seed);
    std::uniform_int_distribution<unsigned> indexDistrib(4, 12);
    std::uniform_int_distribution<unsigned> numDistrib(5, 30);

    // generate matrix
    int size = indexDistrib(gen);
    Matrix<int> m(size, size);
    for(int row=0; row<m.rows(); row++){
        for(int col=0; col<m.columns(); col++){
            m.setData(row, col, numDistrib(gen));
        }
    }
    SolveTree s(m);
    bool res = s.solve();
    ASSERT_TRUE(res);
    auto S = s.solution();
    // Проверка, что распределение 1 единственное в стоке и столбце
    for(int i=0; i<S.rows(); i++){
        int sum = 0;
        for(int j=0; j<S.columns(); j++) sum += S.get(i, j);
        ASSERT_EQ(sum, 1);
    }
    for(int j=0; j<S.columns(); j++){
        int sum = 0;
        for(int i=0; i<S.rows(); i++) sum += S.get(i, j);
        ASSERT_EQ(sum, 1);
    }
}

TEST_MAIN();