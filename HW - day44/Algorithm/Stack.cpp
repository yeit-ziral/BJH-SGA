#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <stack>

using namespace std;

// 1. MazeRunner가 발자취 남기게 하기 (발자취 색은 아무거나, 플레이어 색과는 다르게)
// 2. stack(후입선출), queue(선입선출)에 대해 조사하기
//     팬케이크         줄서기
//

template <typename T>
class Mystack
{
public:
    void push(const T& value)
    {
        a.push_back(value);
    }

    void pop()
    {
        for (int i = 0; i < (a.size() - 1); i++)
        {
            a[i] = a[i + 1];
        }
        a.pop_back();
    }

    const int& top()
    {
        return a.back();
    }

    bool empty()
    {
        if (a.size() == 0)
            return true;
        return false;
    }

private:
    vector<T> a;
};

int Stack()
{
    deque<int> d; // 

    stack<int> s;

    s.push(5);
    s.push(4);
    s.push(3);
    s.push(2);
    s.push(1);

    while (true)
    {
        if (s.empty() == true)
            break;

        int value = s.top(); // 생성자 호출이 가벼울 때 => vector<Player*>
        s.emplace(); // 생성자 호출이 버거운 놈들 부를 때 => vector<Player>
        cout << value << endl;
        s.pop();
    }

    return 0;
}

