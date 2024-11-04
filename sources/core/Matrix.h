#ifndef MATRIX_H
#define MATRIX_H
#include <initializer_list>
#include <iostream>

/**
 * Класс для описания матрицы
 */
template<typename T>
class Matrix {
public:
    // Конструктор по заданному размеру
    Matrix(int rows, int columns) :
        _rows(rows), _columns(columns) {
        if(rows <= 0 || columns <=0) return;
        allocateMemory(_rows, _columns);
    }

    // Конструктор со списком инициализации
    Matrix(std::initializer_list<std::initializer_list<T>> list) {
        if(list.size() == 0 || list.begin()->size() == 0) return;
        allocateMemory(list.size(), list.begin()->size());
        for(int row=0; row<_rows; row++){
            for(int col=0; col<_columns; col++){
                _data[row][col] = list.begin()[row].begin()[col];
            }
        }
    }

    // Конструктор копировния
    Matrix(const Matrix& other){
        allocateMemory(other._rows, other._columns);
        for(int r=0; r<_rows; r++){
            for(int c=0; c<_columns; c++){
                _data[r][c] = other._data[r][c];
            }
        }
    }

    // Деструктор
    ~Matrix(){
        freeMemory();
    }

    // Оператор присваивания
    Matrix& operator=(const Matrix& other){
        allocateMemory(other._rows, other._columns);
        for(int r=0; r<_rows; r++){
            for(int c=0; c<_columns; c++){
                _data[r][c] = other._data[r][c];
            }
        }
        return *this;
    }

    // Поэлементное сравнение матриц
    bool operator==(const Matrix& other){
        if(_rows != other._rows || _columns != other._columns) return false;
        for(int r=0; r<_rows; r++){
            for(int c=0; c<_columns; c++){
                if(_data[r][c] != other._data[r][c]) return false;
            }
        }
        return true;
    }

    // Количество строк
    int rows() const {
        if(_data == nullptr) return -1;
        return _rows;
    }

    // Количество колонок
    int columns() const {
        if(_data == nullptr) return -1;
        return _columns;
    }

    // Получение данных по заданному индексу
    T get(int row, int col) const {
        if(_data == nullptr) return {};
        if(row < 0 || row >= _rows) return {};
        if(col < 0 || col >= _columns) return {};
        return _data[row][col];
    }

    // Установка значения для заданного индекса
    void setData(int row, int col, const T& data){
        if(_data == nullptr) return;
        if(row < 0 || row >= _rows) return;
        if(col < 0 || col >= _columns) return;
        _data[row][col] = data;
    }

    // Вывод матрицы
    void print() const {
        if(_data == nullptr) std::cout << "null" << std::endl;
        for(int i=0; i<_rows; i++){
            for(int j=0; j<_columns; j++){
                if(_data[i][j] == std::numeric_limits<T>::max()) std::cout << "M ";
                else std::cout << _data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void removeRow(int row) {
        if(row < 0 || row >= _rows) return;
        delete[] _data[row];
        for(int i=row; i<_rows-1; i++){
            _data[i] = _data[i+1];
        }
        _rows--;
    }

    void removeColumn(int col) {
        if(col < 0 || col >= _columns) return;
        for(int row=0; row<_rows; row++){
            for(int i=col; i<_columns-1; i++){
                _data[row][i] = _data[row][i+1];
            }
        }
        _columns--;
    }

private:
    // Выделение памяти
    void allocateMemory(int rows, int cols){
        freeMemory();
        _rows = rows;
        _columns = cols;
        _data = new T*[_rows];
        for(int i=0; i<_rows; i++){
            _data[i] = new T[_columns];
        }
    }
    // Освобождение памяти
    void freeMemory() {
        if(!_data) return;
        if(_rows == 0 || _columns == 0) return;
        for(int i=0; i<_rows; i++) {
            delete[] _data[i];
        }
        delete[] _data;
        _data = nullptr;
    }

private:
    T** _data = nullptr;
    int _rows = 0;
    int _columns = 0;
};

#endif //MATRIX_H
