#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>
#include <concurrent_priority_queue.h> // #include<queue> 만 있어도 사용 가능

// 완전 이진 트리
// map도 이진 트리 (완전 이진 트리는 아님)

using namespace std;

template<typename T = int, typename Container = vector<int>, typename Pred = less<T>>
class Priority_Queue
{
public:
	// 부모가 인덱스 n일 때
	// 자식은 n * 2 + 1, n * 2 + 2 이다.

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

			// Child 자체가 없다.
			if (leftChild >= (int)container.size())
				break;

			int nextIndex = nowIndex;

			Pred p;

			if (p(container[nextIndex], container[leftChild]))
				nextIndex = leftChild;

			/*if (container[nextIndex] < container[leftChild]) // 위의 함수와 같음
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
	// priority_queue는 완전이진트리로 구성되어있다.
	// 완전이진트리는 배열을 이용하여 구할 수 있다.
	//

	priority_queue<int> pq; // heap->완전 이진 트리랑 같다

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