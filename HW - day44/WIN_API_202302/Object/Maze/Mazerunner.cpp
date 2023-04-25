#include "framework.h"
#include "Mazerunner.h"

Mazerunner::Mazerunner(shared_ptr<Maze> maze)
	: _maze(maze)
	, _pos(maze->Start())
{
	//LeftHand();
	// DFS
	_visited = vector<vector<bool>>(maze->GetY(), vector<bool>(maze->GetX(), false));
	//DFS(_pos);
	_discovered = vector<vector<bool>>(maze->GetY(), vector<bool>(maze->GetX(), false));
	_parent = vector<vector<Vector2>>(maze->GetY(), vector<Vector2>(maze->GetX(), { -1,-1 }));

	//Dijkskra
	_best = vector<vector<int>>(_maze->GetY(), vector<int>(_maze->GetX(), INT_MAX));

	_diParent = vector<vector<Vector2>>(maze->GetY(), vector<Vector2>(maze->GetX(), { -1,-1 }));

	_diVisited = vector<vector<bool>>(maze->GetY(), vector<bool>(maze->GetX(), false));

	Astar();
}

Mazerunner::~Mazerunner()
{
	_maze = nullptr;
}

void Mazerunner::Update()
{
	if (_pathIndex >= _path.size())
	{
		_maze->CreateMazeByKruskal();
		_pos = _maze->Start();
		_pathIndex = 0;
		_path.clear();
		Astar();
		Vector2 end = _maze->End();
		//_maze->GetBlock(end.y, end.x)->GetType(MazeBlock::BlockType::END);

		return;
	}
	
	_time += 0.3f;
	//_maze->GetBlock((int)_pos.y, (int)_pos.x)->SetType(MazeBlock::BlockType::FOOTPRINT);

	if (_time > 1.0f)
	{
		_time = 0.0f;
		_pos = _path[_pathIndex];

		if (_pathIndex > 0)
		{
			_maze->GetBlock((int)_path[_pathIndex - 1].y, (int)_path[_pathIndex - 1].x)->SetType(MazeBlock::BlockType::FOOTPRINT);
		}

		_pathIndex++;
	}

	_maze->GetBlock((int)_pos.y, (int)_pos.x)->SetType(MazeBlock::BlockType::PLAYER);
}

void Mazerunner::LeftHand()
{
	Vector2 pos = _pos; // start point
	Vector2 endPos = _maze->End();
	_direction = Dir::DIR_UP;
	_path.push_back(pos);

	Vector2 frontPos[8] =
	{
		Vector2(1,1),
		Vector2(0,-1), // UP
		Vector2(1,0), // Right
		Vector2(0,1), // Down
		Vector2(-1,0), // Left
		Vector2(-1, 1),
		Vector2(1, -1),
		Vector2(-1, -1)
	};

	while (pos != endPos)
	{
		// ���� �ٶ󺸴� ���� �������� ���������� �� �� �ִ��� Ȯ��(�ݽð����)
		int newDir = (_direction - 1 + DIR_COUNT) % DIR_COUNT; // ������������ ����
		Vector2 oldDirVector2 = frontPos[_direction]; //���� ����
		Vector2 newDirVector2 = frontPos[newDir]; // ���� ¤�� ����

		// �޼� �������� ������ �� �ִ��� Ȯ��
		Vector2 newGo = pos + newDirVector2;
		Vector2 oldGo = pos + oldDirVector2;
		if (Cango(newGo.y, newGo.x))
		{
			_direction = static_cast<Dir>(newDir);
			pos += newDirVector2;
			_maze->GetBlock(pos.y, pos.x)->SetType(MazeBlock::BlockType::VISITED);
			_path.push_back(pos);
		}

		// ���� �ٶ󺸴� �������� ������ �� �ִ��� Ȯ��
		else if (Cango(oldGo.y, oldGo.x))
		{
			pos += oldDirVector2;
			_maze->GetBlock(pos.y, pos.x)->SetType(MazeBlock::BlockType::VISITED);
			_path.push_back(pos);
		}

		// ����, ���� �� �����ִٸ� �ð�������� ȸ��
		else
		{
			_direction = static_cast<Dir>((_direction + 1 + DIR_COUNT) % DIR_COUNT);
		}
	}
	stack<Vector2> s;

	for (int i = 0; i < _path.size() - 1; i++)
	{
		if (s.empty() == false && s.top() == _path[i + 1])
			s.pop();
		else
			s.push(_path[i]);
	}

	s.push(_path.back());
	_path.clear();

	while (true)
	{
		if (s.empty() == true)
			break;
		_path.push_back(s.top());
		s.pop();
	}

	std::reverse(_path.begin(), _path.end());
}

void Mazerunner::DFS(Vector2 here)
{
	if (_visited[(int)here.y][(int)here.x] == true)
		return;

	Vector2 endPos = _maze->End();

	if (_visited[endPos.y][endPos.x] == true)
		return;

	_visited[(int)here.y][(int)here.x] = true;
	_maze->GetBlock(here.y, here.x)->SetType(MazeBlock::BlockType::VISITED);
	_path.push_back(here);

	Vector2 frontPos[8] =
	{
		Vector2(1,1),
		Vector2(0,-1), // UP
		Vector2(1,0), // Right
		Vector2(0,1), // Down
		Vector2(-1,0), // Left
		Vector2(-1, 1),
		Vector2(1, -1),
		Vector2(-1, -1)
	};

	for (int i = 0; i < 8; i++)
	{
		Vector2 there = here + frontPos[i];

		if (_visited[there.y][there.x] == true)
			continue;

		if (Cango(there.y, there.x) == false)
			continue;

		DFS(there);
	}
}

void Mazerunner::BFS(Vector2 start)
{
	Vector2 endPos = _maze->End();

	if (_visited[endPos.y][endPos.x] == true)
		return;

	_parent[(int)start.y][(int)start.x] = start;

	_discovered[(int)start.y][(int)start.x] = true;

	queue<Vector2> _queue;

	_queue.push(start);

	Vector2 frontPos[8] =
	{
		Vector2(1,1),
		Vector2(0,-1), // UP
		Vector2(1,0), // Right
		Vector2(0,1), // Down
		Vector2(-1,0), // Left
		Vector2(-1, 1),
		Vector2(1, -1),
		Vector2(-1, -1)
	};

	while (!_queue.empty())
	{
		Vector2 here = _queue.front();

		_queue.pop();

		if (_discovered[endPos.y][endPos.x])
			break;

		for (int i = 0; i < 8; i++)
		{
			Vector2 there = here + frontPos[i];

			if (_discovered[there.y][there.x])
				continue;

			if (Cango(there.y, there.x) == false)
				continue;

			_queue.push(there);
			_discovered[there.y][there.x] = true;
			_parent[there.y][there.x] = here;
		}
	}

	Vector2 targetNode = endPos;

	list <Vector2> termPath;

	termPath.push_front(endPos);

	while (true)
	{
		if (_parent[targetNode.y][targetNode.x] == targetNode)
			break;

		targetNode = _parent[targetNode.y][targetNode.x];
		termPath.push_front(targetNode);
	}

	for (auto iter : termPath)
	{
		_path.push_back(iter);
	}
}

void Mazerunner::BFS_2()
{
	Vector2 frontPos[8] =
	{
		Vector2(0,-1), // UP
		Vector2(1,0), // Right
		Vector2(0,1), // Down
		Vector2(-1,0), // Left
		Vector2(1,1), // Rightup
		Vector2(-1, 1), // Rightdown
		Vector2(1, -1), // Leftup
		Vector2(-1, -1) // Leftdown
	};

	Vector2 startPos = _maze->Start();
	Vector2 endPos = _maze->End();

	_discovered = vector<vector<bool>>(_maze->GetY(), vector<bool>(_maze->GetX(), false));

	_parent = vector<vector<Vector2>>(_maze->GetY(), vector<Vector2>(_maze->GetX(), Vector2(-1, -1)));

	_best = vector<vector<int>>(_maze->GetY(), vector<int>(_maze->GetX(), -1));

	queue<Vector2> q;
	q.push(startPos);
	_discovered[startPos.y][startPos.x] = true;
	_parent[startPos.y][startPos.x] = startPos;

	while (true)
	{
		if (q.empty() == true)
			break;

		Vector2 here = q.front();

		

		if (_discovered[endPos.y][endPos.x] == true)
			break;

		q.pop();

		for (int i = 0; i < 8; i++)
		{
			Vector2 there = here + frontPos[i];

			if (_discovered[there.y][there.x] == true)
				continue;

			if (Cango(there.y, there.x) == false)
				continue;

			q.push(there);

			_discovered[there.y][there.x] = true;
			_parent[there.y][there.x] = here;
			_maze->GetBlock(there.y, there.x)->SetType(MazeBlock::BlockType::VISITED);

			//++weight;

			//_best[here.y][here.x] = weight;
		}
	}

	Vector2 pos = endPos;

	_path.push_back(endPos);

	while (true)
	{
		if (pos == startPos)
			break;

		pos = _parent[pos.y][pos.x];
		_path.push_back(pos);
	}

	std::reverse(_path.begin(), _path.end());

	for (int i = 0; i < _path.size(); i++)
	{
		_best[_path[i].y][_path[i].x] = i;
	}

	int last = _path.size() - 2;

	int endPosBest = _best[_path[last].y][_path[last].x];
}

void Mazerunner::Dijkstra()
{
	Vector2 frontPos[8] =
	{
		Vector2(0,-1), // UP
		Vector2(1,0), // Right
		Vector2(0,1), // Down
		Vector2(-1,0), // Left
		Vector2(1,1), // Rightup
		Vector2(-1, 1), // Rightdown
		Vector2(1, -1), // Leftup
		Vector2(-1, -1) // Leftdown
	};

	Vector2 startPos = _maze->Start();

	Vector2 endPos = _maze->End();

	priority_queue<Vertex2, vector<Vertex2>, greater<Vertex2>> pq;

	Vertex2 startV = Vertex2(_maze->Start(), 0);

	pq.push(startV);

	_best[startV.vertexPos.y][startV.vertexPos.x] = 0;

	_diVisited[startV.vertexPos.y][startV.vertexPos.x] = true;

	_diParent[startV.vertexPos.y][startV.vertexPos.x] = startV.vertexPos;

	while (true)
	{
		if (pq.empty() == true)
			break;

		int cost = pq.top().g;

		int temp = 0;

		Vector2 here = pq.top().vertexPos;

		pq.pop();

		for (int i = 0; i < 8; i++)
		{
			Vector2 there = here + frontPos[i];

			if (here == there)
				continue;

			if (Cango(there.y, there.x) == false)
				continue;

			int nextCost = _best[here.y][here.x];
			
			if(i < 4)
				int nextCost = _best[here.y][here.x] + 10;
			if(i >= 4)
				int nextCost = _best[here.y][here.x] + 14;

			if (nextCost >= _best[there.y][there.x])
				continue;

			Vertex2 v = Vertex2(there, nextCost);

			pq.push(v);

			_best[there.y][there.x] = nextCost;

			_diVisited[there.y][there.x] = true;
			
			_diParent[there.y][there.x] = here;
			
			_maze->GetBlock(there.y, there.x)->SetType(MazeBlock::BlockType::VISITED);
		}

		if (_diVisited[endPos.y][endPos.x] == true)
		{
			break;
		}
	}

	Vector2 targetPos = endPos;

	endPosBest = _best[endPos.y][endPos.x];

	while (true)
	{
		if (_diParent[targetPos.y][targetPos.x] == targetPos)
			break;

		targetPos = _diParent[targetPos.y][targetPos.x];

		_path.push_back(targetPos);
	}

	reverse(_path.begin(), _path.end());

	_path.push_back(endPos);
}

void Mazerunner::Dijkstra2()
{
	Vector2 frontPos[8] =
	{
		Vector2(0,-1), // UP
		Vector2(1,0), // Right
		Vector2(0,1), // Down
		Vector2(-1,0), // Left
		Vector2(1,1), // Rightup
		Vector2(-1, 1), // Rightdown
		Vector2(1, -1), // Leftup
		Vector2(-1, -1) // Leftdown
	};

	int Dijkstra_Dis[8] =
	{
		10,
		10,
		10,
		10,
		14,
		14,
		14,
		14
	};

	Vector2 startPos = _maze->Start();
	Vector2 endPos = _maze->End();

	_best = vector<vector<int>>(_maze->GetY(), vector<int>(_maze->GetX(), INT_MAX));

	_parent = vector<vector<Vector2>>(_maze->GetY(), vector<Vector2>(_maze->GetX(), Vector2(-1, -1)));

	priority_queue<Vertex2_Dijkstra, vector<Vertex2_Dijkstra>, greater<Vertex2_Dijkstra>> pq;

	Vertex2_Dijkstra start;

	start.pos = _maze->Start();
	start.g = 0;
	pq.push(start);

	_best[start.pos.y][start.pos.x] = start.g;
	_parent[start.pos.y][start.pos.x] = start.pos;

	while (true)
	{
		if (pq.empty())
			break;

		Vector2 here = pq.top().pos;

		int cost = pq.top().g;

		pq.pop();

		if (here == endPos)
			break;

		for (int i = 0; i < 8; i++)
		{
			Vector2 there = here + frontPos[i];

			if (here == there)
				continue;

			if (Cango(there.y, there.x) == false)
				continue;

			int newCost = cost + Dijkstra_Dis[i];

			if (_best[there.y][there.x] < newCost)
				continue;

			Vertex2_Dijkstra thereV;
			thereV.pos = there;
			thereV.g = newCost;

			pq.push(thereV);
			_best[there.y][there.x] = newCost;
			_parent[there.y][there.x] = here;

			_maze->GetBlock(there.y, there.x)->SetType(MazeBlock::BlockType::VISITED);
		}
	}

	Vector2 pos = endPos;
	_path.push_back(endPos);
	while (true)
	{
		if (pos == startPos)
			break;

		pos = _parent[pos.y][pos.x];
		_path.push_back(pos);
	}

	std::reverse(_path.begin(), _path.end());
}

void Mazerunner::Astar()
{
	Vector2 frontPos[8] =
	{
		Vector2(0,-1), // UP
		Vector2(1,0), // Right
		Vector2(0,1), // Down
		Vector2(-1,0), // Left
		Vector2(1,1), // Rightup
		Vector2(-1, 1), // Rightdown
		Vector2(1, -1), // Leftup
		Vector2(-1, -1) // Leftdown
	};

	int Astar_Dis[8] =
	{
		10,
		10,
		10,
		10,
		14,
		14,
		14,
		14
	};

	Vector2 start = _maze->Start();
	Vector2 end = _maze->End();

	Vertex v;
	v.pos = start;
	v.g = 0;
	v.h = start.ManhattanDistance(end) * 10;
	v.f = v.g + v.h;

	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> pq;

	pq.push(v);

	_best[v.pos.y][v.pos.x] = v.f;
	_parent[v.pos.y][v.pos.x] = v.pos;

	while (true)
	{
		if (pq.empty())
			break;

		Vector2 here = pq.top().pos;

		int g = pq.top().g;
		int h = pq.top().h;
		int f = pq.top().f;

		int cost = f;

		pq.pop();

		if (here == end)
		{
			_maze->GetBlock(end.y, end.x)->SetType(MazeBlock::BlockType::END);
			break;
		}

		if (_best[here.y][here.x] < f)
			continue;

		for (int i = 0; i < 8; i++)
		{
			Vector2 there = here + frontPos[i];

			if (here == there)
				continue;

			if (Cango(there.y, there.x) == false)
				continue;

			int newG = g + Astar_Dis[i];
			int newH = there.ManhattanDistance(end) * 10;
			int newCost = newG + newH;

			if (_best[there.y][there.x] < newCost) // �湮���� ������ INT_MAX�� ���� ���� ũ�� ������ �湮�Ѵ�.
				continue;

			Vertex thereV;
			thereV.pos = there;
			thereV.g = newG;
			thereV.h = newH;
			thereV.f = newCost;

			pq.push(thereV);
			_best[there.y][there.x] = newCost;
			_parent[there.y][there.x] = here;

			_maze->GetBlock(there.y, there.x)->SetType(MazeBlock::BlockType::VISITED);
		}
	}

	Vector2 pos = end;
	_path.push_back(end);
	while (true)
	{
		if (pos == start)
			break;

		pos = _parent[pos.y][pos.x];
		_path.push_back(pos);
	}

	std::reverse(_path.begin(), _path.end());
}

bool Mazerunner::Cango(int y, int x)
{
	if (_maze->GetBlockType(y, x) == MazeBlock::BlockType::DISABLE ||
		_maze->GetBlockType(y, x) == MazeBlock::BlockType::NONE)
	{
		return false;
	}
	return true;
}
