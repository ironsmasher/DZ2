// G = (V, E)
// |V| = num_v
// |E| = num_e
#include <fstream>

bool used[100]; // ������������ � ������� �������� ���������
int num_v; // ���������� ������
int **g;

void dfs(int v) // �������� �� ���������
{
	if (used[v] == true) // ���� ������� ������������( �� � ��� ����) �� ������� �� ����� ������
		return;
	used[v] = true; // ������� ������������
	for (int i = 0; i < num_v; i++) // ������� ���� ������� ������� �������
		if (g[v][i] == 1) // ==1 ���� ���� ����� � ������� i
			dfs(i); //���������� ����� �� ����� �������
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
	
	int num_e; // ���������� �����

	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt");
	fin >> num_e; 
	fin >> num_v;

	// ��������� ������ ��� ������� ���������
	g = new int* [num_v]; 
	for (int i = 0; i < num_v; i++)
		g[i] = new int[num_v];
	
	// ��������� �������
	for (int i = 0; i < num_v; i++)
		for (int j = 0; j < num_v; j++)
			g[i][j] = 0;

	// ���� �����
	for (int i = 0; i < num_e; i++)
	{
		int v1, v2;
		fin >> v1 >> v2;
		v1--; v2--;
		g[v1][v2] = 1;
		g[v2][v1] = 1;
	}

	// ����� ������� ���������
	for (int i = 0; i < num_v; i++)
	{
		for (int j = 0; j < num_v; j++)
			fout << g[i][j] << " "; 
		fout << std::endl;
	}

	// ����� ������� ���������
	dfs(0);

	// �������� �� ���������
	int i;
	for (i = 0; i < num_v; i++)
		if (used[i] == false)
			break; // ������ �� ��� ������� ��������, ������ �� ������� ���� � i < num_v
	if (i >= num_v)
		fout << "Graph svyazan" << std::endl;
	else
		fout << "Graph ne svyazan" << std::endl;

	// �������� ������
	for (int i = 0; i < num_v; i++)
		delete[]g[i];
	delete[]g;
	// �������� ������
	fin.close();
	fout.close();

	return 0;
}