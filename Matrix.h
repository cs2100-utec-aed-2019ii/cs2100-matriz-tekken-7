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
            while((*row)) {
                if((*row)->down) {
                    if ((*row)->down->indice > std::get<0>(par)) {
                        IndexNodeR<T>* temporal = (*row)->down;
                        IndexNodeR<T>* in_index = new IndexNodeR<T>(std::get<0>(par));
                        (*row)->down = in_index;
                        in_index->down = temporal;
                        row = &in_index;
                        break;
                    }
                }
                if((*row)->indice == std::get<0>(par)) {
                    break;
                }
                row = &(*row)->down;
            }
            if(!(*row)) {
                (*row) = new IndexNodeR<T>(std::get<0>(par));
            }
            while((*column)) {
                if((*column)->next) {
                    if ((*column)->next->indice > std::get<1>(par)) {
                        IndexNodeC<T>* temporal = (*column)->next;
                        IndexNodeC<T>* in_index = new IndexNodeC<T>(std::get<1>(par));
                        (*column)->next = in_index;
                        in_index->next = temporal;
                        column = &in_index;
                        break;
                    }
                }
                if((*column)->indice == std::get<1>(par)) {
                    break;
                }
                column = &(*column)->next;
            }
            if(!(*column)) {
                (*column) = new IndexNodeC<T>(std::get<1>(par));
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
            r = p.root->down;
            c = p.root->next;
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
};
#endif 