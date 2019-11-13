#include <iostream>
#include <tuple>
#include <fstream>
#include "Matrix.h"
int main() {
    Matrix<double> F;
    Matrix<double> S;
    Matrix<double> J;
    Matrix<double> K = Matrix<double>::indentity(5);
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
    std::ofstream jj("kkkk.txt");
    jj << J;
    jj.close();
    std::cout << std::endl;
    std::cout << K << std::endl;
    Matrix<double> p = S.transpuesta();
    std::cout << S.transpuesta() << std::endl;
    std::cout << std::endl;
    std::cout << p << std::endl;
    p.erase(1,3);
    std::cout << std::endl;
    std::cout << p << std::endl;

    return 0;
}
