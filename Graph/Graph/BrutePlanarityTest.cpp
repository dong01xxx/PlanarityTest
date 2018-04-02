#include "BrutePlanarityTest.h"


bool BrutePlanarityTest::checkPlanarity()
{
	const size_t vertexesCount = _graph.size();
	const size_t _cntEdges = _graph.edgesCount();
	if (vertexesCount < 5)
		return true;

	// Euler formula check.
	if (vertexesCount > 2 && _cntEdges > (3 * vertexesCount - 6)) 
	{
		return false;
	}

	return 0;
}

void BrutePlanarityTest::printAllCycles()
{
	vector<vector<int>> res = getVectorOfCycles();
	for (size_t i = 0; i < res.size(); i++)
	{
		for (size_t j = 0; j < res[i].size(); j++)
			cout << res[i][j] << " ";
		cout << "\n";
	}
}

vector<int> BrutePlanarityTest::getCycle(int begin, int end, vector<int>& cycle)
{
	vector<int> resCycle;
	int curEl = cycle.size() - 1;
	while (cycle[curEl] != begin)
	{
		resCycle.push_back(cycle[curEl]);
		curEl--;
	}
	resCycle.push_back(cycle[curEl]);
	return resCycle;
}



void BrutePlanarityTest::DFS(int v, int prev, bool *color, vector<int>& cycle, vector<vector<int>>& allCycles)
{
	color[v] = 1;
	for (size_t i = 0; i < _graph.getAdjacentVertexes(v).size(); i++)
	{
		int tmpV = _graph.getAdjacentVertexes(v)[i];
		if (color[tmpV] == 1)
		{
			if (prev != tmpV)
			{
				if (cycle.size() > 2)
				{
					vector<int> tmpCyc = getCycle(tmpV, v, cycle);
					bool checker = 1;
					for (auto finV = allCycles.begin(); finV != allCycles.end(); ++finV)
					{
						vector<int> tmpVC = (*finV);
						sort(tmpVC.begin(), tmpVC.end());
						sort(tmpCyc.begin(), tmpCyc.end());
						bool flag = 1;
						for (int elVec = 0; elVec < min(tmpVC.size(), tmpCyc.size()); elVec++)
						{
							if (tmpVC[elVec] != tmpCyc[elVec])
							{
								flag = 0;
								break;
							}
						}
						if (flag == 1)
						{
							checker = 0;
							break;
						}
					}
					if (checker == 1)
						allCycles.push_back(tmpCyc);
				}
			
			}

		}
		else
		{
			cycle.push_back(tmpV);
			//color[_graph.getAdjacentVertexes(v)[i]] = 1;
			DFS(tmpV, v, color, cycle, allCycles);
		}
	}
	color[v] = 0;
	cycle.pop_back();
}

vector< vector<int> > BrutePlanarityTest::getVectorOfCycles()
{
	vector<vector<int> > res;
	bool *color = new (bool[this->_graph.size()]);
	for (int i = 0; i < this->_graph.size(); i++)
		color[i] = 0;
	vector<int> curPath;
	curPath.push_back(0);
	DFS(0, 0, color, curPath, res);

	return res;
}