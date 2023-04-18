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

	void push(const int& value) 
	{
		container.push_back(value);

		int child = container.size() - 1;

		while (child > 0)
		{
			int parent = (child - 1) / 2;

			if (container[parent] < container[child]) // ���⼭ ���� �߻�
			{
				swap(container[parent], container[child]);
				child = parent;
			}
			else
				break;
		}
	}

	void pop() 
	{
		if (container.empty())
			return;

		swap(container[0], container.back());
		container.pop_back();

		int parent = 0;
		int child = (parent * 2) + 1;

		while (child < container.size())
		{
			if (child + 1 < container.size() && container[child] < container[child + 1])
				child++;

			if (container[child] > container[parent])
			{
				swap(container[child], container[parent]);
				parent = child;
				child = (child * 2) + 1;
			}
			else
				break;
		}
	}

	const int& top() { return container[0]; }

	unsigned int size() { return container.size(); }

	bool empty() { return container.empty(); }

private:
	vector<int> container;
};

int main()
{
	// priority_queue�� ��������Ʈ���� �����Ǿ��ִ�.
	// ��������Ʈ���� �迭�� �̿��Ͽ� ���� �� �ִ�.
	//

	priority_queue<int> pq; // heap->���� ���� Ʈ���� ����

	Priority_Queue Pq;

	pq.push(10);
	pq.push(20);
	pq.push(7);
	pq.push(4);
	pq.push(11);

	Pq.push(10);
	Pq.push(20);
	Pq.push(7);
	Pq.push(4);
	Pq.push(11);

	cout << pq.top() << endl;
	pq.pop();	// �� �Ʒ��� �����ʰ� root�� �ٲٰ� �� leaf�� ���� -> ��ĭ�� ��ܼ� root�� ���� �Ʒ� ���� root�� ����
				// vector�� ������ ��, �� ������ ó������ �ٲ۴��� �� �ڸ� ������ -> ó������ �ڽĵ��� ���ؼ� �� ū���� �ڸ��� �ٲ۴�. -> �̰��� �ݺ�

	cout << pq.top() << endl;
	pq.pop();

	cout << pq.top() << endl;
	pq.pop();

	cout << Pq.top() << endl;
	Pq.pop();

	cout << Pq.top() << endl;
	Pq.pop();

	cout << Pq.top() << endl;
	Pq.pop();

	return 0;
}