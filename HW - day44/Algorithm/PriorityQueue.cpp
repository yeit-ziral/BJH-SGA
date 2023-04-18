#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>
#include <concurrent_priority_queue.h> // #include<queue> �� �־ ��� ����

using namespace std;

class Priority_Queue
{
public:
	// �θ� �ε��� n�� ��
	// �ڽ��� n * 2 + 1, n * 2 + 2 �̴�.

	Priority_Queue() {}
	Priority_Queue(vector<int> container) : container(container) {}
	~Priority_Queue() {}

	void push(const int& value) {}

	void pop() {}

	const int& top() { return 0; }

	unsigned int size() { return 0; }

	bool empty() { return false; }

private:
	vector<int> container;
};

int main()
{
	// priority_queue�� ��������Ʈ���� �����Ǿ��ִ�.
	// ��������Ʈ���� �迭�� �̿��Ͽ� ���� �� �ִ�.
	//

	priority_queue<int> pq; // heap->���� ���� Ʈ���� ����

	pq.push(10);
	pq.push(20);
	pq.push(7);
	pq.push(4);
	pq.push(11);

	cout << pq.top() << endl;
	pq.pop();	// �� �Ʒ��� �����ʰ� root�� �ٲٰ� �� leaf�� ���� -> ��ĭ�� ��ܼ� root�� ���� �Ʒ� ���� root�� ����
				// vector�� ������ ��, �� ������ ó������ �ٲ۴��� �� �ڸ� ������ -> ó������ �ڽĵ��� ���ؼ� �� ū���� �ڸ��� �ٲ۴�. -> �̰��� �ݺ�

	cout << pq.top() << endl;
	pq.pop();

	cout << pq.top() << endl;
	pq.pop();

	return 0;
}