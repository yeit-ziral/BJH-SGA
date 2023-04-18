#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>
#include <concurrent_priority_queue.h> // #include<queue> 만 있어도 사용 가능

using namespace std;

class Priority_Queue
{
public:
	// 부모가 인덱스 n일 때
	// 자식은 n * 2 + 1, n * 2 + 2 이다.

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

			if (container[parent] < container[child]) // 여기서 에러 발생
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
	// priority_queue는 완전이진트리로 구성되어있다.
	// 완전이진트리는 배열을 이용하여 구할 수 있다.
	//

	priority_queue<int> pq; // heap->완전 이진 트리랑 같다

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
	pq.pop();	// 맨 아래의 오른쪽과 root를 바꾸고 그 leaf를 날림 -> 한칸씩 당겨서 root의 왼쪽 아래 값을 root로 보냄
				// vector로 생각할 때, 맨 끝값과 처음값을 바꾼다음 맨 뒤를 날린다 -> 처음값의 자식들을 비교해서 더 큰값과 자리를 바꾼다. -> 이것을 반복

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