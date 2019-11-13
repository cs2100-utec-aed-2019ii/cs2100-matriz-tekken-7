#include <iostream>
#include <tuple>
#include "Matrix.h"
int main() {
	    Matrix<double> F;
		F << std::tuple<int,int,double>(1,3,3);
		F << std::tuple<int,int,double>(2,3,1);
		F << std::tuple<int,int,double>(5,6,5);
		F << std::tuple<int,int,double>(4,6,4);
		std::cout << F  << std::endl;
		return 0;
}
