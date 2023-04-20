#pragma once
class Mazerunner
{
public:
	Mazerunner(shared_ptr<Maze> maze);
	~Mazerunner();

	void Update();

	void LeftHand();
	void DFS(Vector2 here);

	void BFS(Vector2 start);

	void BFS_2();

	void Dijkstra();

	bool Cango(int y, int x);

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
	struct Vertex
	{
		Vertex(Vector2 pos, int g) : vertexPos(pos), g(g) { }

		bool operator<(const Vertex& other) const
		{
			return g < other.g;
		}

		bool operator>(const Vertex& other) const
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

