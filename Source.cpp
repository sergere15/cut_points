#include <iostream>
#include <ctime>
#include <random>
#include <vector>
#include <algorithm>
#include <assert.h>



using namespace std;

void print_graph(bool** matrix, int n){

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

void Graph_gen(bool** matrix, int n_, int edges){
	
	int n = n_;

	
	if (edges < (n - 1)) assert("Wrong number of edges");
	//�������� ���������� �����, ������� ���������� �������������� 
	edges -= (n - 1);

	int tmp = 0;
	//int tmp2 = 0;

	//��������� ��� ������� ��������, ����� �� ������ ������ ���� ���� �� 1 ����� ����������
	
	//������ �������: ������� ������ 0 � 1 �������, ������ ����� ��������� � ��������������� �������,
	//����� ������� ������� ������ �������
	matrix[0][1] = true;
	matrix[1][0] = true;
	int half = n / 2;
	for (int i = 2; i < half; i++)
	{
		tmp = rand() % i;
		matrix[i][tmp] = true;
		matrix[tmp][i] = true;
	}

	//��������� �������������� �����, ����� �� ���� ������� ����� ����� ���������� 
	int tmp1 = 0;
	int tmp2 = 0;
	for (int i = 0; i < edges / 2; i++)
	{
		tmp1 = rand() % half;
		tmp2 = rand() % half;
		matrix[tmp1][tmp2] = true;
		matrix[tmp2][tmp1] = true;
	}

	//������ �������: ��������� ���������� �������, �� ������ �������
	//��������� ����� � ���� �������, ����� �������� ����� ���-�� 

	matrix[half][half+1] = true;
	matrix[half+1][half] = true;

	for (int i = half + 2; i < n; i++)
	{
		tmp = rand() % (i - half) + (half);
		matrix[i][tmp] = true;
		matrix[tmp][i] = true;
	}

	//��������� �������������� �����, ����� �� ���� ������� ����� ����� ���������� 
	for (int i = 0; i <edges - (edges / 2); i++)
	{
		tmp1 = rand() % (half) + (half);;
		tmp2 = rand() % (half) + (half);;
		matrix[tmp1][tmp2] = true;
		matrix[tmp2][tmp1] = true;
	}

	//��������� ��� ��������
	matrix[half][half-1] = true;
	matrix[half-1][half] = true;

	//if (n < 50) print_graph(matrix, n);

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

	if (n < 50) print_graph(list, n);
}

void IS_CUTPOINT(int v) {
	cout << "Cut point: " << v << endl;
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
			dfs( to,  p,  n, g,  timer,  used,  tin,  fup);
			fup[v] = min(fup[v], fup[to]);
			if (fup[to] >= tin[v] && p != -1)
				IS_CUTPOINT(v);
			++children;
		}
	}
	if (p == -1 && children > 1)
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
			if (fup[to] >= tin[v] && p != -1)//����������� ������� ���������
				IS_CUTPOINT(v);
			++children;
		}
	}
	if (p == -1 && children > 1) //�������� ��� �������, ��� ������� - ������
		IS_CUTPOINT(v);

}

int main()
{
	setlocale(LC_ALL, "Russian");

	int n = 0;
	int edges = 0;

	for (int i = 0; i < 5; i++) {
		for (int k = 0; k < 6; k++) {
			n = (i + 1) * 10; //��������� ���-�� ������
			edges = (n - 1) + floor(3.7 * k);//��������� ���-�� �����
			
			//�������� ��������, ����������� ��� ������ ���������
			bool** matrix = new bool*[n];
			for (int i = 0; i < n; i++) {
				matrix[i] = new bool[n];
				memset(matrix[i], false, n);
			}

			bool* used = new bool[n];
			memset(used, false, n);
			int timer = 0;
			int* tin = new int[n];
			int* fup = new int[n];
			vector<vector<int>> list;
			list.resize(n);
			list.shrink_to_fit();

			cout << "/////////////////////////////////////////////" << endl;
			cout << "Number of vertex: " << n << "  edges: " << edges << endl;

			//��������� ������� ������
			Graph_gen(matrix, n, edges);
			matrix_to_list(list, matrix, n); //Convert matrix to list and delete matrix from memory

			//dfs(0, -1, n, matrix, timer, used, tin, fup);

			
			size_t start = clock();

			//����� ������ ���������
			dfs_list(0, -1, n, list, timer, used, tin, fup);

			size_t end = clock();
			cout << "time of execution is " << start / 1000. << " s" << endl << endl;
			delete[] used;
			delete[] tin;
			delete[] fup;
		}
	}
 	system("pause");
	return 0;
}