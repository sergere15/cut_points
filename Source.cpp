﻿#include <iostream>
#include <ctime>
#include <random>
#include <vector>
#include <algorithm>
#include <assert.h>


bool print = true;
using namespace std;

void print_graph(bool** matrix, int n) {

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << matrix[i][j] << " ";

		}
		cout << endl;
	}
}

void print_graph(vector<vector<int>>& x, int n) {

	for (int i = 0; i < n; i++) {
		cout << i << ": ";
		for (int j = 0; j < x[i].size(); j++) {
			cout << x[i][j] << " ";

		}
		cout << endl;
	}

}

void Graph_gen(bool** matrix, int n_, int edges) {

	int n = n_;


	if (edges < (n - 1)) assert("Wrong number of edges");
	//Задается количество ребер, которые необходимо догенерировать 
	edges -= (n - 1);

	int tmp = 0;
	//int tmp2 = 0;

	//Создаются два связных подграфа, чтобы на выходе всегда была хотя бы 1 точка сочленения

	//Первый подграф: сначала свяжем 0 и 1 вершину, дальше будем связывать с псевдослучайной вершины,
	//номер которой меньшей номера текущей
	matrix[0][1] = true;
	matrix[1][0] = true;
	int half = n / 2;
	for (int i = 2; i < half; i++)
	{
		tmp = rand() % i;
		matrix[i][tmp] = true;
		matrix[tmp][i] = true;
	}

	//Добавляем дополнительные ребра, чтобы не было слишком много точек сочленения 
	int tmp1 = 0;
	int tmp2 = 0;
	for (int i = 0; i < edges / 2; i++)
	{
		tmp1 = rand() % half;
		tmp2 = rand() % half;
		if (tmp1 == tmp2)
		{
			i--;
			continue;
		}
		matrix[tmp1][tmp2] = true;
		matrix[tmp2][tmp1] = true;
	}

	//Второй подграф: генерация аналогична первому, но другие границы
	//Добавляем ребра в этот подграф, чтобы получить нужно кол-во 

	matrix[half][half + 1] = true;
	matrix[half + 1][half] = true;

	for (int i = half + 2; i < n; i++)
	{
		tmp = rand() % (i - half) + (half);
		matrix[i][tmp] = true;
		matrix[tmp][i] = true;
	}

	//Добавляем дополнительные ребра, чтобы не было слишком много точек сочленения 
	for (int i = 0; i <edges - (edges / 2); i++)
	{
		tmp1 = rand() % (half)+(half);
		tmp2 = rand() % (half)+(half);
		if (tmp1 == tmp2)
		{
			i--;
			continue;
		}
		matrix[tmp1][tmp2] = true;
		matrix[tmp2][tmp1] = true;
	}

	//Соединяем два подграфа
	matrix[half][half - 1] = true;
	matrix[half - 1][half] = true;

	

}

void matrix_to_list(vector<vector<int>>& list, bool** matrix, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i != j && matrix[i][j]) {
				list[i].push_back(j);
			}
		}
	}

	for (int p = 0; p < n; p++) {
		delete[] matrix[p];
	}
}

void IS_CUTPOINT(int v) {
		//cout << "Cut point: " << v << endl; //Выввод в поток сильно влияет на время
}

void dfs(int v, int p, int n, bool** g, int timer, bool* used, int* tin, int* fup) {

	used[v] = true;
	tin[v] = fup[v] = timer++;
	int children = 0;

	for (size_t i = 0; i < n; ++i) {
		int to = 0;
		if (g[v][i])
			to = i;
		else
			continue;

		if (to == p || i == v)  continue;
		if (used[to])
			fup[v] = min(fup[v], tin[to]);
		else {
			dfs(to, p, n, g, timer, used, tin, fup);
			fup[v] = min(fup[v], fup[to]);
			if (fup[to] >= tin[v] && p != -1)//Стандартное условие алгоритма
				IS_CUTPOINT(v);
			++children;
		}
	}
	if (p == -1 && children > 1)//Проверка при условии, что вершина - корень
		IS_CUTPOINT(v);
}

void dfs_list(int v, int p, int n, vector<vector<int>>& g, int timer, bool* used, int* tin, int* fup) {

	used[v] = true;
	timer++;
	tin[v] = fup[v] = timer;
	int children = 0;
	for (size_t i = 0; i<g[v].size(); ++i) {
		int to = g[v][i];
		if (to == p)  continue;
		if (used[to])
			fup[v] = min(fup[v], tin[to]);
		else {
			dfs_list(to, p, n, g, timer, used, tin, fup);
			fup[v] = min(fup[v], fup[to]);
			if (fup[to] >= tin[v] && p != -1)//Стандартное условие алгоритма
				IS_CUTPOINT(v);
			++children;
		}
	}
	if (p == -1 && children > 1) //Проверка при условии, что вершина - корень
		IS_CUTPOINT(v);	

}

void main_part(int i_, int k_) {
	int n = 0;
	int edges = 0;

	// Проверка на указанных входных данных
	for (int i = i_; i <= i_ + 3 ; i++) {
		n = (i + 1) * 113; //Генерация кол-ва вершин

						   //Создание массивов, необходимых для работы алгоритма
		bool* used = new bool[n];
		memset(used, false, n);
		int timer = 0;
		int* tin = new int[n];
		int* fup = new int[n];

		for (int k = k_; k <= k_ + 4; k++) {

			edges = (n - 1) + floor(3.7 * k * k);//Генерация кол-ва ребер

												 //Обнуление массивов, которые заполнялись на предыдущей итерации
			memset(used, false, n);
			timer = 0;


			cout << "/////////////////////////////////////////////" << endl;
			cout << "Number of vertex: " << n << "  edges: " << edges << endl;

			bool** matrix = new bool*[n];
			for (int i1 = 0; i1 < n; i1++) {
				matrix[i1] = new bool[n];
				memset(matrix[i1], false, n);
			}

			vector<vector<int>> list;
			list.resize(n);
			list.shrink_to_fit();
			//Генерация входных данных
			Graph_gen(matrix, n, edges);
			matrix_to_list(list, matrix, n); //Convert matrix to list and delete matrix from memory
			if (n < 15) print_graph(list, n);//вывод полученного графа
											 //dfs(0, -1, n, matrix, timer, used, tin, fup);

			unsigned long long sum = 0;

			for (int t = 0; t < 10; t++) {
				//if (t == 0) print_graph(list, n);

				memset(used, false, n);
				timer = 0;

				size_t start = clock();

				//Вызов самого алгоритма
				dfs_list(0, -1, n, list, timer, used, tin, fup);

				size_t end = clock();
				sum += (end - start);
				print = false;
			}
			cout << "time of execution is " << (sum / 10000.) << " s" << endl << endl;
			print = true;
		}
		delete[] used;
		delete[] tin;
		delete[] fup;

	}
}

void main_part_double(int i_, int k_) {
	int n = 0;
	int edges = 0;

	// Проверка на указанных входных данных
	for (int i = i_; i <= i_ + 3; i++) {
		n = (i + 1) * 113 * 2; //Генерация кол-ва вершин

						   //Создание массивов, необходимых для работы алгоритма
		bool* used = new bool[n];
		memset(used, false, n);
		int timer = 0;
		int* tin = new int[n];
		int* fup = new int[n];

		for (int k = k_; k <= k_ + 4; k++) {

			edges = (((n - 1) / 2) + floor(3.7 * k * k)) * 2;//Генерация кол-ва ребер

												 //Обнуление массивов, которые заполнялись на предыдущей итерации
			memset(used, false, n);
			timer = 0;


			cout << "/////////////////////////////////////////////" << endl;
			cout << "Number of vertex: " << n << "  edges: " << edges << endl;

			bool** matrix = new bool*[n];
			for (int i1 = 0; i1 < n; i1++) {
				matrix[i1] = new bool[n];
				memset(matrix[i1], false, n);
			}

			vector<vector<int>> list;
			list.resize(n);
			list.shrink_to_fit();
			//Генерация входных данных
			Graph_gen(matrix, n, edges);
			matrix_to_list(list, matrix, n); //Convert matrix to list and delete matrix from memory
			if (n < 15) print_graph(list, n);//вывод полученного графа
											 //dfs(0, -1, n, matrix, timer, used, tin, fup);

			unsigned long long sum = 0;

			for (int t = 0; t < 10; t++) {
				//if (t == 0) print_graph(list, n);

				memset(used, false, n);
				timer = 0;

				size_t start = clock();

				//Вызов самого алгоритма
				dfs_list(0, -1, n, list, timer, used, tin, fup);

				size_t end = clock();
				sum += (end - start);
				print = false;
			}
			cout << "time of execution is " << (sum / 10000.) << " s" << endl << endl;
			print = true;
		}
		delete[] used;
		delete[] tin;
		delete[] fup;

	}
}

int main()
{

	cout << "Standart input: " << endl;
	main_part(1, 13);// запускается на изначальных входных данных
	cout << endl << endl << endl;
	cout << "Input doubled: " << endl;
	main_part_double(1, 13);// запускается на удвоенных данных
	
	system("pause");
	return 0;
}