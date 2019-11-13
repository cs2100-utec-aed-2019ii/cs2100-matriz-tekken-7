#include <iostream>
#include <tuple>
#include "Matrix.h"
int main() {
    Matrix<double> F;
    Matrix<double> S;
    Matrix<double> J;
    S << std::tuple<int,int,double>(1,3,3);
    S << std::tuple<int,int,double>(2,3,1);
    S << std::tuple<int,int,double>(5,6,5);
    S << std::tuple<int,int,double>(4,6,4);
    S << std::tuple<int,int,double>(0,2,7);


    F << std::tuple<int,int,double>(1,3,3);
    F << std::tuple<int,int,double>(2,3,1);
    F << std::tuple<int,int,double>(5,6,5);
    F << std::tuple<int,int,double>(4,6,4);
    F << std::tuple<int,int,double>(0,3,4);
    F << std::tuple<int,int,double>(0,5,9);
    std::cout << F  << std::endl;
    std::cout << std::endl;
    std::cout << S << std::endl;
    J = F+S;
    std::cout << std::endl;
    std::cout << J << std::endl;
    return 0;
}
