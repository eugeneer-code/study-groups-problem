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
    cout << endl << "Number of people on disciplines: ";
    for(int i=0; i<M; i++){
        int cnt = N/M;
        if(i < N%M) cnt++;
        for(int j=0; j<cnt; j++) disciplinesList.push_back(i);
        cout << cnt << " ";
    }
    cout << endl;

    // Важность направлений
    cout << endl << "Importance of disciplines: ";
    std::vector<float> importance;
    for(int i=0; i<M; i++){
        auto imp = gen.generateImportance();
        importance.push_back(imp);
        cout << imp << " ";
    }
    cout << endl;

    // Оценки людей по направлениям
    Matrix<int> grades(N, M);
    cout << endl << "Grades: " << endl;
    for(int row=0; row<grades.rows(); row++){
        for(int col=0; col<grades.columns(); col++){
            grades.setData(row, col, gen.generateMark());
        }
    }
    grades.print();

    /**
     * Получение индекса направления по индексу человека
     * M = 3, N = 10
     * index 0 1 2 3 4 5 6 7 8 9
     * res   0 0 0 0 1 1 1 2 2 2
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
            // Необходимо минимизировать отставание (5 - оценка)
            int init = imp * (5 - grades.get(row, discIndex));
            initMatrix.setData(row, col, init);
        }
    }
    cout << endl << "Cost matrix for minimization: " << endl;
    initMatrix.print();

    // Минимизация
    SolveTree solve(initMatrix);
    solve.solve();
    auto solution = solve.solution();


    // Распределение по предметам
    Matrix<int> res(N, M);
    res.fill(0);
    int totalGrades = 0;
    for(int row=0; row<N; row++) {
        for(int col=0; col<N; col++) {
            int s = solution.get(row, col);
            if(s == 0) continue;
            int discIndex = getDiscByIndex(col);
            res.setData(row, discIndex, s);
            totalGrades += grades.get(row, discIndex);
        }
    }
    cout << endl << "Solution: " << endl;
    res.print();

    cout << endl << "Total grades loss: " << 5*N - totalGrades;
    cout << endl << "Grades loss per human: " << 5.0 - totalGrades*1.0/N << endl;

    return 0;
}
