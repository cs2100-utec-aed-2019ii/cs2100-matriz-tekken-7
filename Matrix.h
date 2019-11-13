#ifndef SPARSEMATRIX_MATRIX_H
#define SPARSEMATRIX_MATRIX_H

#include "Node.h"
#include <tuple>
#include <fstream>
#include <iostream>
template<typename T>
class Matrix{
private:
    Node<T>* root;
public:
    Matrix() {
        root = new Node<T>();
    }

    friend void operator <<( Matrix<T>& F, std::tuple<int, int,T> par) {
        ValNode<T>* ins = new ValNode<T>((par));
        if(!F.root->down && !F.root->next) {
            IndexNodeR<T>* IR = new IndexNodeR<T>(std::get<0>(par));
            IndexNodeC<T>* IC = new IndexNodeC<T>(std::get<1>(par));
            F.root->down = IR;
            F.root->next = IC;
            IC->down = ins;
            IR->next = ins;
            return;
        }
       else {
            IndexNodeC<T>** column = &F.root->next;
            IndexNodeR<T>** row = &F.root->down;
            if((*row)->indice > std::get<0>(par)) {
                IndexNodeR<T> *in_index = new IndexNodeR<T>(std::get<0>(par));
                in_index->down = (*row);
                (*row) = in_index;
            }
            else if((*row)->indice == std::get<0>(par)) {

            }
            else {
                while ((*row)) {
                    if ((*row)->down) {
                        if ((*row)->down->indice > std::get<0>(par)) {
                            IndexNodeR<T> *temporal = (*row)->down;
                            IndexNodeR<T> *in_index = new IndexNodeR<T>(std::get<0>(par));
                            (*row)->down = in_index;
                            in_index->down = temporal;
                            row = &in_index;
                            break;
                        }
                    }
                    if ((*row)->indice == std::get<0>(par)) {
                        break;
                    }
                    row = &(*row)->down;
                }
                if (!(*row)) {
                    (*row) = new IndexNodeR<T>(std::get<0>(par));
                }
            }
            if((*column)->indice > std::get<1>(par)) {
                IndexNodeC<T>* in_index = new IndexNodeC<T>(std::get<1>(par));
                in_index->next = (*column);
                (*column) = in_index;
            }
            else if((*column)->indice == std::get<1>(par)){

            }
            else {
                while ((*column)) {
                    if ((*column)->next) {
                        if ((*column)->next->indice > std::get<1>(par)) {
                            IndexNodeC<T> *temporal = (*column)->next;
                            IndexNodeC<T> *in_index = new IndexNodeC<T>(std::get<1>(par));
                            (*column)->next = in_index;
                            in_index->next = temporal;
                            column = &in_index;
                            break;
                        }
                    }
                    if ((*column)->indice == std::get<1>(par)) {
                        break;
                    }
                    column = &(*column)->next;
                }
                if (!(*column)) {
                    (*column) = new IndexNodeC<T>(std::get<1>(par));
                }
            }

            ValNode<T>** row2 = &(*row)->next;
            ValNode<T>** column2 = &(*column)->down;
            while((*row2)) {
                    if ((*row2)->x > std::get<1>(par)) {
                        ValNode<T>*temporal = (*row2);
                        (*row2) = ins;
                        ins->next = temporal;
                        break;
                    }
                row2 = &(*row2)->next;
            }
            if(!(*row2)) {
                (*row2) = ins;
            }

            while((*column2)) {
                if ((*column2)->y > std::get<0>(par)) {
                    ValNode<T> *temporal = (*column2);
                    (*column2) = ins;
                    ins->down = temporal;
                    break;
                }
                column2 = &(*column2)->down;
            }
            if(!(*column2)) {
                (*column2) = ins;
            }
       }
    }

    friend std::ostream& operator <<(std::ostream& os, Matrix<T>& p) {
        if(!p.root->down) {
            os << "No hay valores en la matriz.\n";
            return os;
        }
        else {
            IndexNodeR<T>* r = p.root->down;
            IndexNodeC<T>* c = p.root->next;
            ValNode<T>* data = r->next;
            int indexc = p.get_dimensiones().second;
            int indexr = p.get_dimensiones().first;
            for(int i = 0; i < indexr+1; i++) {
                for(int j = 0; j < indexc+1; j++) {
                    if(r->indice != i) {
                        os << "0" << " ";
                    }
                    else {
                        if(data) {
                            if(data->x != j) {
                                os << "0" << " ";
                            }
                            else if (data->x == j) {
                                os << data->value << " ";
                                data = data->next;
                            }
                        } else {
                            os << "0 ";
                        }
                    }
                }
                if(r->indice == i) {
                    r = r->down;
                    if(!r)
                        break;
                    data = r->next;
                }
                os << std::endl;
            }
        }
        return os;
    }

    std::pair<int,int> get_dimensiones() {
        IndexNodeR<T>* a = root->down;
        IndexNodeC<T>* b = root->next;
        int row = 0;
        int col = 0;
        std::pair<int,int> dimensiones(0,0);

        if(!a) {
            std::cout << "No hay valores en la matriz.\n";
            return dimensiones;
        }
        else {
            while(a) {
                row = a->indice;
                a = a->down;
            }
            while(b) {
                col = b->indice;
                b = b->next;
            }
            dimensiones.first = row;
            dimensiones.second = col;
            return dimensiones;
        }
    }

    /*void print_matrix() {
        IndexNodeR<T>* r = root->down;
        IndexNodeC<T>* c = root->next;
        ValNode<T>* data = r->next;
        int indexc = 0;
        int indexr = 0;
        while(r) {
            indexr = r->indice;
            r = r->down;
        }
        while(c) {
            indexc = c->indice;
            c = c->next;
        }
        r = root->down;
        c = root->next;
        for(int i = 0; i < indexr+1; i++) {
            for(int j = 0; j < indexc+1; j++) {
                if(r->indice != i) {
                    std::cout << "0" << " ";
                }
                else {
                    if(data) {
                        if(data->x != j) {
                            std::cout << "0" << " ";
                        }
                        else if (data->x == j) {
                            std::cout << data->value << " ";
                            data = data->next;
                        }
                    } else {
                        std::cout << "0 ";
                    }
                }
            }
            if(r->indice == i) {
                r = r->down;
                if(!r)
                    break;
                data = r->next;
            }
            std::cout << std::endl;
        }
    }*/

    std::ostream& operator<<(std::ofstream& jj) {

    }

    void operator = (Matrix<T> F) {
        root = F.root;
    }

    Matrix<T> operator+(Matrix<T>& A) {
        Matrix<T> c;
        int rowa = A.get_dimensiones().first;
        int columna = A.get_dimensiones().second;
        int rowb = get_dimensiones().first;
        int columnb = get_dimensiones().second;
        if(rowa == rowb && columna == columnb) {
            IndexNodeR<T>* a = A.root->down;
            IndexNodeR<T>* b = root->down;
            ValNode<T>* vala = a->next;
            ValNode<T>* valb = b->next;
            int decision = 0;

            for(int i = 0; i < rowa+1; i++) {
                for(int j = 0; j < columna+1; j++) {
                    if(a->indice != i && b->indice != i) {
                        decision = 0;
                        break;
                    }
                    else if(a->indice == i && b->indice != i) {
                        decision = 1;
                        if(vala) {
                            if(vala->x == j) {
                                c << std::make_tuple(vala->y,vala->x,vala->value);
                                vala = vala->next;
                            }
                        }
                    }
                    else if(b->indice == i && a->indice != i) {
                        decision = 2;
                        if(valb) {
                            if(valb->x == j) {
                                c << std::make_tuple(valb->y,valb->x,valb->value);
                                valb = valb->next;
                            }
                        }
                    }
                    else if(a->indice == i && b->indice == i) {
                        decision = 3;
                        if(vala || valb) {
                            if(vala && !valb) {
                                c << std::make_tuple(vala->y,vala->x,vala->value);
                                vala = vala->next;
                            }
                            else if(valb && !vala) {
                                c << std::make_tuple(valb->y,valb->x,valb->value);
                                valb = valb->next;
                            }
                            else if(!vala && !valb) {
                                break;
                            }
                            else if(valb->x < vala->x) {
                                c << std::make_tuple(valb->y,vala->x,valb->value);
                                valb = valb->next;
                            }
                            else if(vala->x < valb->x) {
                                c << std::make_tuple(valb->y,vala->x,vala->value);
                                vala = vala->next;
                            }
                            else if(vala->x == valb->x) {
                                T suma = vala->value + valb->value;
                                c << std::make_tuple(vala->y,vala->x, suma);
                                vala = vala->next;
                                valb = valb->next;
                            }
                        }
                    }
                }
                if(decision == 0){

                }
                else if(decision == 1) {
                    a = a->down;
                    if(!a) {
                        break;
                    }
                    vala = a->next;
                }
                else if(decision == 2) {
                    b = b->down;
                    valb = b->next;
                }
                else if(decision == 3) {
                    a = a->down;
                    b = b->down;
                    if(!a) {
                        break;
                    }
                    vala = a->next;
                    valb = b->next;
                }
            }
            return c;
        }
        else {
            std::cout << "Estas matrices no se pueden sumar.\n";
        }
    }
};
#endif
