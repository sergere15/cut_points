#include <iostream>
#include <ctime>
#include <random>
#include <vector>
#include <algorithm>
using namespace std;

void Graph_gen(bool** matrix, int n_)
{
	
	int n = n_;

	

	//Задается количество ребер, которые необходимо сгенерировать 
	int num_of_edjes = ceil(n*1.8);

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
	for (int i = 0; i < n / 4; i++)
	{
		tmp1 = rand() % half;
		tmp2 = rand() % half;
		matrix[tmp1][tmp2] = true;
		matrix[tmp2][tmp1] = true;
	}

	//Второй подграф: генерация аналогична первому, но другие границы
	//Добавляем ребра в этот подграф, чтобы получить нужно кол-во 

	matrix[half][half+1] = true;
	matrix[half+1][half] = true;

	for (int i = half + 2; i < n; i++)
	{
		tmp = rand() % (i - half) + (half);
		matrix[i][tmp] = true;
		matrix[tmp][i] = true;
	}

	//Добавляем дополнительные ребра, чтобы не было слишком много точек сочленения 
	for (int i = 0; i < n / 4; i++)
	{
		tmp1 = rand() % (half) + (half);;
		tmp2 = rand() % (half) + (half);;
		matrix[tmp1][tmp2] = true;
		matrix[tmp2][tmp1] = true;
	}

	//Соединяем два подграфа
	matrix[half][half-1] = true;
	matrix[half-1][half] = true;

	/*for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << matrix[i][j] << " ";
			
		}
		cout << endl;
	}*/

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



int main()
{
	int n;
	cin >> n;

	bool** matrix = new bool*[n];
	for (int i = 0; i < n; i++) {
		matrix[i] = new bool[n];
		memset(matrix[i], false, n);
	}

	Graph_gen(matrix, n);

	cout << "Dfs begins!!!!!!!!!!" << endl;

	bool* used = new bool[n];
	memset(used, false, n);
	int timer = 0;
	int* tin = new int[n];
	int* fup = new int[n];
	dfs(0, -1, n, matrix, timer, used, tin, fup);
	//cut_point(0, n, matrix);


	system("pause");
	return 0;
}