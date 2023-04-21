#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>
#include <concurrent_priority_queue.h> // #include<queue> �� �־ ��� ����

// ���� ���� Ʈ��
// map�� ���� Ʈ�� (���� ���� Ʈ���� �ƴ�)

using namespace std;

template<typename T = int, typename Container = vector<int>, typename Pred = less<T>>
class Priority_Queue
{
public:
	// �θ� �ε��� n�� ��
	// �ڽ��� n * 2 + 1, n * 2 + 2 �̴�.

	Priority_Queue() {}
	Priority_Queue(Container container) : container(container) {}
	~Priority_Queue() {}

	void push(const T& value) 
	{
		container.push_back(value);

		int nowIndex = static_cast<int> (container.size() - 1);

		while (true)
		{
			if (nowIndex <= 0)
			{
				return;
			}

			int parent = (nowIndex - 1) / 2;

			Pred p;
			if (!p(container[parent], container[nowIndex]))
				break;

			if (container[parent] >= container[nowIndex])
			{
				break;
			}
			
			std::swap(container[parent], container[nowIndex]);

			nowIndex = parent;
		}
	}

	void pop() 
	{
		if (container.empty())
			return;

		std::swap(container[0], container.back());

		container.pop_back();

		int nowIndex = 0;

		while (true)
		{
			int leftChild = nowIndex * 2 + 1;
			int rightChild = nowIndex * 2 + 2;

			// Child ��ü�� ����.
			if (leftChild >= (int)container.size())
				break;

			int nextIndex = nowIndex;

			Pred p;

			if (p(container[nextIndex], container[leftChild]))
				nextIndex = leftChild;

			/*if (container[nextIndex] < container[leftChild]) // ���� �Լ��� ����
			{
				nextIndex = leftChild;
			}*/

			if (rightChild < (int)container.size() && container[nextIndex] < container[rightChild])
			{
				nextIndex = rightChild;
			}

			if (nextIndex == nowIndex)
				break;

			std::swap(container[nowIndex], container[nextIndex]);

			nowIndex = nextIndex;
		}
	}

	const T& top() { return container[0]; }

	unsigned int size() { return container.size(); }

	bool empty() { return container.empty(); }

private:
	Container container;
};

int Priority_queue()
{
	// priority_queue�� ��������Ʈ���� �����Ǿ��ִ�.
	// ��������Ʈ���� �迭�� �̿��Ͽ� ���� �� �ִ�.
	//

	priority_queue<int> pq; // heap->���� ���� Ʈ���� ����

	Priority_Queue<> Pq;

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