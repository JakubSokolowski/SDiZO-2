// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "IncidenceMatrix.h"
#include "AdjacencyList.h"
#include "Vector.h"
#include <cstdio>
#include <vector>
#include <utility>
#include <ctime>

class test {
public:
	int a, b, c;
	test() {}
	test(int & _a, int & _b, int & _c) : a(_a), b(_b), c(_c) {}
	test(int && _a, int && _b, int && _c) : a(std::move(_a)), b(std::move(_b)), c(std::move(_c)) {}

	void print() {
		printf(" %d %d %d\n", a, b, c);
	}
};

using namespace sdizo;
int main()
{
	IncidenceMatrix matr = IncidenceMatrix(4, 5);
	matr.AddEdge(0, 3, 6);
	matr.AddEdge(1, 0, 5);
	matr.AddEdge(1, 3, 7);
	matr.AddEdge(1, 2, 24);
	matr.AddEdge(2, 0, 9);
	matr.DisplayMatrix();
	matr.DisplayWeights();

	vector <int> vec =  vector<int>(25);
	vec.PushBack(12);
	vec.PushBack(10);
	vec.PushBack(1);
	vec.PushBack(123);
	vec[1] = 200;
	//std::cout << vec.at(1) << " " << vec.size() << " " << vec.capacity();
	vec.Display();
	//vec.shrink_to_fit();
	//std::cout << vec.at(0) << " " << vec.size() << " " << vec.capacity();
	getchar();
    return 0;

}

