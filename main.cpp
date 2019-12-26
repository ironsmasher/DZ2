// G = (V, E)
// |V| = num_v
// |E| = num_e
#include <fstream>

bool used[100]; // èñïîëüçóåòñÿ â ôóíêöèè ïðîâåðêè ñâÿçíîñòè
int num_v; // êîëè÷åñòâî âåðøèí
int **g;

void dfs(int v) // ïðîâåðêà íà ñâÿçíîñòü
{
	if (used[v] == true) // åñëè âåðøèíà èñïîëüçîâàíà( ìû â íåé áûëè) òî âûõîäèì èç ýòîãî âûçîâà
		return;
	used[v] = true; // âåðøèíà èñïîëüçîâàíà
	for (int i = 0; i < num_v; i++) // ñìîòðèì âñåõ ñîñåäåé òåêóùåé âåðøèíû
		if (g[v][i] == 1) // ==1 åñëè åñòü ðåáðî â âåðøèíó i
			dfs(i); //ðåêóðñèíûé âûçîâ îò íîâîé âåðøèíû
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
	
	int num_e; // êîëè÷åñòâî ðåáåð

	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt");
	fin >> num_e; 
	fin >> num_v;

	// âûäåëåíèå ïàìÿòè ïîä ìàòðèöó ñìåæíîñòè
	g = new int* [num_v]; 
	for (int i = 0; i < num_v; i++)
		g[i] = new int[num_v];
	
	// çàíóëåíèå ìàòðèöû
	for (int i = 0; i < num_v; i++)
		for (int j = 0; j < num_v; j++)
			g[i][j] = 0;

	// ââîä ãðàôà
	for (int i = 0; i < num_e; i++)
	{
		int v1, v2;
		fin >> v1 >> v2;
		v1--; v2--;
		g[v1][v2] = 1;
		g[v2][v1] = 1;
	}

	// âûâîä ìàòðèöû ñìåæíîñòè
	for (int i = 0; i < num_v; i++)
	{
		for (int j = 0; j < num_v; j++)
			fout << g[i][j] << " "; 
		fout << std::endl;
	}

	// âûçîâ ôóíêöèè ñâÿçíîñòè
	dfs(0);

	// ïðîâåðêà íà ñâÿçíîñòü
	int i;
	for (i = 0; i < num_v; i++)
		if (used[i] == false)
			break; // çíà÷èò íå âñå âåðøèíû ïðîéäåíû, çíà÷èò íå ñâÿçíûé ãðàô è i < num_v
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

	// î÷èùåíèå ïàìÿòè
	for (int i = 0; i < num_v; i++)
		delete[]g[i];
	delete[]g;
	// çàêðûòèå ôàéëîâ
	fin.close();
	fout.close();

	return 0;
}
