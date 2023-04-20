#pragma once
class Mazerunner
{
public:
	struct Vertex2_Dijkstra
	{
		Vector2 pos;
		int g;

		bool operator < (const Vertex2_Dijkstra& other) const
		{
			return this->g < other.g;
		}

		bool operator > (const Vertex2_Dijkstra& other) const
		{
			return this->g > other.g;
		}
	};

	struct Vertex
	{
		Vector2 pos;
		int g = 0;
		int h = 0;
		int f = 0;

		bool operator < (const Vertex& other) const
		{
			return this->f < other.f;
		}

		bool operator > (const Vertex& other) const
		{
			return this->f > other.f;
		}
	};

	Mazerunner(shared_ptr<Maze> maze);
	~Mazerunner();

	void Update();

	void LeftHand();
	void DFS(Vector2 here);

	void BFS(Vector2 start);

	void BFS_2();

	void Dijkstra();

	void Dijkstra2();

	bool Cango(int y, int x);

	void Astar();

	int endPosBest = 0;

private:
	shared_ptr<Maze> _maze;

	Vector2 _pos;
	Dir _direction = Dir::DIR_UP;

	vector<Vector2> _path;

	// DFS
	vector<vector<bool>> _visited;

	// BFS
	vector<vector<bool>> _discovered;
	vector<vector<Vector2>> _parent;

	// Dijkstra
	struct Vertex2
	{
		Vertex2(Vector2 pos, int g) : vertexPos(pos), g(g) { }

		bool operator<(const Vertex2& other) const
		{
			return g < other.g;
		}

		bool operator>(const Vertex2& other) const
		{
			return g > other.g;
		}

		Vector2 vertexPos;
		int g; 
	};
	vector<vector<int>> _best;
	vector<vector<Vector2>> _diParent;
	vector<vector<bool>> _diVisited;

	int _pathIndex = 0;
	float _time = 0.0f;
};

