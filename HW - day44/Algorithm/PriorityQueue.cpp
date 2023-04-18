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
	// priority_queue는 완전이진트리로 구성되어있다.
	// 완전이진트리는 배열을 이용하여 구할 수 있다.
	//

	priority_queue<int> pq; // heap->완전 이진 트리랑 같다

	pq.push(10);
	pq.push(20);
	pq.push(7);
	pq.push(4);
	pq.push(11);

	cout << pq.top() << endl;
	pq.pop();	// 맨 아래의 오른쪽과 root를 바꾸고 그 leaf를 날림 -> 한칸씩 당겨서 root의 왼쪽 아래 값을 root로 보냄
				// vector로 생각할 때, 맨 끝값과 처음값을 바꾼다음 맨 뒤를 날린다 -> 처음값의 자식들을 비교해서 더 큰값과 자리를 바꾼다. -> 이것을 반복

	cout << pq.top() << endl;
	pq.pop();

	cout << pq.top() << endl;
	pq.pop();

	return 0;
}