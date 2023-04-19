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

	bool Cango(int y, int x);

	int GetEndPosBest() { return endPosBest; }

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

	// Djikstra
	vector<vector<int>> _best;

	int endPosBest = 0;

	int _pathIndex = 0;
	float _time = 0.0f;
};

