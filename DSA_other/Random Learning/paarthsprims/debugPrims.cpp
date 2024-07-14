#include <iostream>
#include <vector>
#include <algorithm>

struct connection
{
	int vA;
	int vB;
	float weight;
	int id;
};

std::vector<connection> MST;
std::vector<char> vertices = { 'A','B','C','D','E','F','G' };

bool isInList(std::vector<int>& visited, int node)
{
	for (int v : visited)
	{
		if (v == node)
			return true;
	};
}

int getIndexByID(std::vector<connection>& c, int id)
{
	for (int i = 0; i < c.size(); i++)
	{
		if (c[i].id == id)
			return i;
	}
}
void cc(std::vector<connection>& c, int vAindex, int vBindex, float weight, int id) // create connection
{
	connection cn;
	cn.vA = vAindex;
	cn.vB = vBindex;
	cn.weight = weight;
	cn.id = id;
	c.push_back(cn);
}

void findConnection(std::vector<int>& idlist, std::vector<connection>& c, int node)
{
	for (connection i : c)
	{
		if (i.vA == node)
			idlist.push_back(i.id);
		if (i.vB == node)
		{
			int temp = i.vA;
			i.vA = i.vB;
			i.vB = temp;
			idlist.push_back(i.id);
		}

	};
}

void prims(std::vector<connection>& c, int start_node)
{
	std::vector<int> visited;
	visited.push_back(start_node);
	std::vector<int> ids;
	bool a = true;
	while (a)
	{
		for (int i = 0; i < visited.size(); i++)
		{

			findConnection(ids, c, i);
			connection rC = c[getIndexByID(c, ids[0])];
			if (isInList(visited, rC.vB))
			{
				i++;
			}
			for (int id : ids)
			{
				connection& temp = c[getIndexByID(c, id)];
				if (!isInList(visited, temp.vB))
				{
					if (temp.weight < rC.weight)
						rC = temp;
				}
			};

			cc(MST, i, rC.vB, rC.weight, rC.id);
			visited.push_back(rC.vB);

			if (visited.size() == vertices.size())
				a = false;

		};
	}

}

void printGraph(std::vector<connection>& c)
{
	for (connection cn : c)
	{
		std::cout << vertices[cn.vA] << "->" << cn.weight << "->" << vertices[cn.vB] << std::endl;
	};
}

int main()
{

	std::vector<connection> connections;

	cc(connections, 0, 1, 2.0f, 0);
	cc(connections, 0, 2, 3.0f, 1);
	cc(connections, 0, 3, 3.0f, 2);
	cc(connections, 2, 3, 5.0f, 3);
	cc(connections, 1, 2, 4.0f, 4);
	cc(connections, 1, 4, 3.0f, 5);
	cc(connections, 2, 4, 1.0f, 6);
	cc(connections, 2, 5, 6.0f, 7);
	cc(connections, 3, 5, 7.0f, 8);
	cc(connections, 4, 5, 8.0f, 9);
	cc(connections, 5, 6, 7.0f, 10);
	prims(connections, 0);
	printGraph(MST);
	return 0;
}