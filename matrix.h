#ifndef MATRIX_H
#define MATRIX_H

#include "node.h"

using namespace std;

template <typename T>
class Matrix {
    private:
        Node<T>* hRows;
        Node<T>* hColumns;
        int columns;
        int rows;

    public:
        Matrix(){
            hRows = hColumns = nullptr;
            columns = rows = 0;
        };
        Matrix(int sizeX, int sizeY){
            columns = sizeX;
            rows = sizeY;
            hRows = new Node<T>(0);
            Node<T>* temp = hRows;
            for (int i = 1; i < rows; i++){
                Node<T>* current = new Node<T>(i);
                temp -> down = current;
                temp = current;
            }
            hColumns = new Node<T>(0);
            temp = hColumns;
            for (int i = 1; i < columns; i++){
                Node<T>* current = new Node<T>(i);
                temp -> next = current;
                temp = current;
            }
        };

        void set(int x, int y, T data){
            if (x+1 <= columns && x >= 0 && y >= 0 && y+1 <= rows){
                Node<T>* Tmpx = hColumns;
                for (int i = 0; i < x; i++)
                    Tmpx = Tmpx -> next;
                Node<T>* Tmpy = hRows;
                for (int i = 0; i < x; i++)
                    Tmpy = Tmpy -> down;
                bool exists = 0;
                while (Tmpx -> down){
                    if (Tmpx -> down -> y < y)
                        Tmpx = Tmpx -> down;
                    else if (Tmpx -> down -> y == y){
                        exists = 1;
                        break;
                    }
                    else
                        break;
                }
                if (!exists){
                    if (data != 0) {
                        while (Tmpy -> next) {
                            if (Tmpy -> next -> x < x)
                                Tmpy = Tmpy -> next;
                            else
                                break;
                        }
                        Node<T> *temp = new Node<T>(x, y, data);
                        temp -> next = Tmpy -> next;
                        Tmpy -> next = temp;
                        temp -> down = Tmpx -> down;
                        Tmpx -> down = temp;
                    }
                }
                else{
                    if (data != 0)
                        Tmpx -> down -> data = data;
                    else {
                        while (Tmpy -> next -> x < x)
                            Tmpy = Tmpy -> next;
                        Node<T>* temp = Tmpx -> down;
                        Tmpx -> down = temp -> down;
                        Tmpy -> next = temp -> next;
                        delete temp;
                    }
                }
            }
            else
                throw ("NO");
        };
        T operator()(int x, int y){
            if (x+1 <= columns && x >= 0 && y >= 0 && y+1 <= rows) {
                Node<T> *current = hColumns;
                for (int i = 0; i < x; i++)
                    current = current->next;
                while (current->down) {
                    if (current->down->y < y)
                        current = current->down;
                    else if (current->down->y == y)
                        return current->down->data;
                    else
                        return 0;
                }
            }
            else
                throw ("NO");
        };
        Matrix<T> operator*(Matrix<T> other){
            if (columns == other.rows){
                Matrix<T>* col = new Matrix(other.columns,rows);
                for (int i = 0; i < col->columns; i++){
                    for (int j = 0; j < col->rows; j++){
                        T value = 0;
                        for (int r = 0; r < columns; r++)
                            value += this->operator()(r, i) * other(j, r);
                        c->set(i, j, value);
                    }

                }
                return *col;
            }
            else
                throw ("NO");
        };
        Matrix<T> operator*(T scalar){
            Node<T>* Tmpx = hColumns;
            while (Tmpx){
                Node<T>* Tmpy = Tmpx -> down;
                while (Tmpy){
                    Tmpy -> data *= scalar;
                    Tmpy = Tmpy -> down;
                }
                Tmpx = Tmpx -> next;
            }
            return *this;
        };
        Matrix<T> operator+(Matrix<T> other){
            if (columns == other.columns && rows == other.rows){
                for (int i = 0; i < columns; i++){
                    for (int j = 0; j < rows; j++)
                        this -> set(i, j, (other(i, j) + this->operator()(i,j)));
                }
                return *this;
            }
            else
                throw ("NO");
        };
        Matrix<T> operator-(Matrix<T> other){
            if (columns == other.columns && rows == other.rows){
                for (int i = 0; i < columns; i++){
                    for (int j = 0; j < rows; j++)
                        this -> set(i, j, (this->operator()(i,j) - other(i, j)));
                }
                return *this;
            }
            else
                throw ("NO");
        };
        Matrix<T> transposed(){};
        Matrix<T> operator=(Matrix<T> other){
            if (columns == other.columns && rows == other.rows){
                for (int i = 0; i < columns; i++){
                    for (int j = 0; j < rows; j++)
                        this -> set(i, j, other(i, j));
                }
                return *this;
            }
            else
                throw ("NO");
        };
        //~Matrix(){};
};

#endif
