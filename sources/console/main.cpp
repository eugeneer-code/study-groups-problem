#include <iostream>
#include "SolveTree.h"
#include "Generator.h"

using std::cin, std::cout, std::endl;

int main()
{
    Generator gen;
    int N, M;
    cout << "Enter number of people: ";
    cin >> N;
    cout << "Enter number of disciplines: ";
    cin >> M;
    if(M > N) {
        cout << "Too much disciplines";
        return 0;
    }
    // Количество обучающихся по направлениям
    std::vector<int> disciplinesList;
    cout << "Number of people on disciplines: ";
    for(int i=0; i<M; i++){
        int cnt = N/M;
        if(i < N%M) cnt++;
        for(int j=0; j<cnt; j++) disciplinesList.push_back(i);
        cout << cnt << " ";
    }
    cout << endl;

    // Важность направлений
    cout << "Importance of disciplines: ";
    std::vector<float> importance;
    for(int i=0; i<M; i++){
        auto imp = gen.generateImportance();
        importance.push_back(imp);
        cout << imp << " ";
    }
    cout << endl;

    // Оценки людей по направлениям
    Matrix<int> marks(N, M);
    cout << "Marks: " << endl;
    for(int row=0; row<marks.rows(); row++){
        for(int col=0; col<marks.columns(); col++){
            marks.setData(row, col, gen.generateMark());
        }
    }
    marks.print();

    /**
     * Получение индекса направления по индексу человека
     * M = 3, N = 10
     * index 0 1 2 3 4 5 6 7 8 9
     * res   0 0 0 0 1 1 1 3 3 3
     */
    auto getDiscByIndex = [N, M](int index){
        return index * M / N;
    };

    // Подготовка матрицы для решения задачи
    Matrix<int> initMatrix(N, N);
    for(int row=0; row<N; row++){
        for(int col=0; col<N; col++){
            int discIndex = getDiscByIndex(col);
            int imp = importance.at(discIndex) * 10;
            int init = imp * (5 - marks.get(row, discIndex));
            initMatrix.setData(row, col, init);
        }
    }
    cout << "Cost matrix for minimization: " << endl;
    initMatrix.print();

    SolveTree solve(initMatrix);
    solve.solve();
    auto res = solve.solution();
    cout << "Solution: " << endl;
    res.print();

    return 0;
}
