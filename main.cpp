// G = (V, E)
// |V| = num_v
// |E| = num_e
#include <fstream>

bool used[100]; // используется в функции проверки связности
int num_v; // количество вершин
int **g;

void dfs(int v) // проверка на связность
{
	if (used[v] == true) // если вершина использована( мы в ней были) то выходим из этого вызова
		return;
	used[v] = true; // вершина использована
	for (int i = 0; i < num_v; i++) // смотрим всех соседей текущей вершины
		if (g[v][i] == 1) // ==1 если есть ребро в вершину i
			dfs(i); //рекурсиный вызов от новой вершины
}

int main()
{
	/*std::cout << "Input edges in format:"
		<< std::endl << "First line: number of edges"
		<< std::endl << "Second line: number of tops"
		<< std::endl << "Next lines: pair (Vi, Vj) - mean connection Vi with Vj"
		<< std::endl << "Example" 
		<< std::endl << "3" << std::endl << "4" << std::endl <<  "1 2" << std::endl << "4 3" << std::endl << "1 2"
		<< std::endl << "Lets start!" << std::endl;*/
	
	int num_e; // количество ребер

	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt");
	fin >> num_e; 
	fin >> num_v;

	// выделение памяти под матрицу смежности
	g = new int* [num_v]; 
	for (int i = 0; i < num_v; i++)
		g[i] = new int[num_v];
	
	// зануление матрицы
	for (int i = 0; i < num_v; i++)
		for (int j = 0; j < num_v; j++)
			g[i][j] = 0;

	// ввод графа
	for (int i = 0; i < num_e; i++)
	{
		int v1, v2;
		fin >> v1 >> v2;
		v1--; v2--;
		g[v1][v2] = 1;
		g[v2][v1] = 1;
	}

	// вывод матрицы смежности
	for (int i = 0; i < num_v; i++)
	{
		for (int j = 0; j < num_v; j++)
			fout << g[i][j] << " "; 
		fout << std::endl;
	}

	// вызов функции связности
	dfs(0);

	// проверка на связность
	int i;
	for (i = 0; i < num_v; i++)
		if (used[i] == false)
			break; // значит не все вершины пройдены, значит не связный граф и i < num_v
	if (i >= num_v)
		fout << "Graph svyazan" << std::endl;
	else
		fout << "Graph ne svyazan" << std::endl;

	// очищение памяти
	for (int i = 0; i < num_v; i++)
		delete[]g[i];
	delete[]g;
	// закрытие файлов
	fin.close();
	fout.close();

	return 0;
}