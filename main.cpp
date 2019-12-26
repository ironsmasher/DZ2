// G = (V, E)
// |V| = num_v
// |E| = num_e
#include <fstream>

bool used[100]; 
int num_v; 
int **g;

void dfs(int v) 
{
	if (used[v] == true) 
		return;
	used[v] = true; 
	for (int i = 0; i < num_v; i++) 
		if (g[v][i] == 1)
			dfs(i); 
}

int main()
{
	int num_e;

	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt");
	fin >> num_e; 
	fin >> num_v;

	g = new int* [num_v]; 
	for (int i = 0; i < num_v; i++)
		g[i] = new int[num_v];
	
	for (int i = 0; i < num_v; i++)
		for (int j = 0; j < num_v; j++)
			g[i][j] = 0;

	for (int i = 0; i < num_e; i++)
	{
		int v1, v2;
		fin >> v1 >> v2;
		v1--; v2--;
		g[v1][v2] = 1;
		g[v2][v1] = 1;
	}

	for (int i = 0; i < num_v; i++)
	{
		for (int j = 0; j < num_v; j++)
			fout << g[i][j] << " "; 
		fout << std::endl;
	}

	dfs(0);

	int i;
	for (i = 0; i < num_v; i++)
		if (used[i] == false)
			break;
	if (i >= num_v)
		fout << "Graph svyazan" << std::endl;
	else
		fout << "Graph ne svyazan" << std::endl;
	 FILE* f = fopen("graph.txt", "w");
	fprintf(f, "graph {\n    {1");
	for (int i = 1; i < num_v; i++) fprintf(f, ", %d", i+1);
	fprintf(f, "}\n");
	for (int i = 0; i < num_v; i++) {
        for (int j = i+1; j < num_v; j++) {
            if (g[i][j] == 1) fprintf(f, "    %d -- %d;\n", i+1, j+1);
        }
    }
	fprintf(f, "}");
	fclose(f);
	system("dot -Tpng graph.txt -o graph.png");
	system("graph.png");
	system("pause");

	for (int i = 0; i < num_v; i++)
		delete[]g[i];
	delete[]g;
	fin.close();
	fout.close();

	return 0;
}
