#include "microtest.h"
#include "BBSolver.h"

TEST(linkLibrary)
{
    BBSolver* solver = new BBSolver();
    ASSERT_TRUE(solver != nullptr);
    delete solver;
}


TEST_MAIN();