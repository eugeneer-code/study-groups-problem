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
    Matrix(int rows, int columns) :
        _rows(rows), _columns(columns) {
        if(rows <= 0 || columns <=0) return;
        allocateData(_rows, _columns);
    }

    Matrix(std::initializer_list<std::initializer_list<T>> list) {
        if(list.size() == 0 || list.begin()->size() == 0) return;
        allocateData(list.size(), list.begin()->size());
        for(int row=0; row<_rows; row++){
            for(int col=0; col<_columns; col++){
                _data[row][col] = list.begin()[row].begin()[col];
            }
        }
    }

    Matrix(const Matrix& other){
        allocateData(other._rows, other._columns);
        for(int r=0; r<_rows; r++){
            for(int c=0; c<_columns; c++){
                _data[r][c] = other._data[r][c];
            }
        }
    }

    Matrix& operator=(const Matrix& other){
        allocateData(other._rows, other._columns);
        for(int r=0; r<_rows; r++){
            for(int c=0; c<_columns; c++){
                _data[r][c] = other._data[r][c];
            }
        }
        return *this;
    }

    bool operator==(const Matrix& other){
        if(_rows != other._rows || _columns != other._columns) return false;
        for(int r=0; r<_rows; r++){
            for(int c=0; c<_columns; c++){
                if(_data[r][c] != other._data[r][c]) return false;
            }
        }
        return true;
    }

    int rows() {
        if(_data == nullptr) return -1;
        return _rows;
    }

    int columns() {
        if(_data == nullptr) return -1;
        return _columns;
    }

    T get(int row, int col){
        if(_data == nullptr) return {};
        if(row < 0 || row >= _rows) return {};
        if(col < 0 || col >= _columns) return {};
        return _data[row][col];
    }

    void setData(int row, int col, const T& data){
        if(_data == nullptr) return;
        if(row < 0 || row >= _rows) return;
        if(col < 0 || col >= _columns) return;
        _data[row][col] = data;
    }

    void print(){
        if(_data == nullptr) std::cout << "null";
        for(int i=0; i<_rows; i++){
            for(int j=0; j<_columns; j++){
                std::cout << _data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

private:
    void allocateData(int rows, int cols){
        _rows = rows;
        _columns = cols;
        _data = new T*[_rows];
        for(int i=0; i<_rows; i++){
            _data[i] = new T[_columns];
        }
    }

private:
    T** _data = nullptr;
    int _rows;
    int _columns;
};

#endif //MATRIX_H
