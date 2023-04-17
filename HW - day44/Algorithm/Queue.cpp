#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

template <typename T, typename Container = deque<T>>
class Queue
{
public:
    void push(const T& value)
    {
        a.push_back(value);
    }

    void pop()
    {
        a.pop_front();

    }

    const T& front()
    {
        return a.front();
    }

    bool empty()
    {
        return a.size() == 0;
    }

private:
    Container a;
};

int Queue()
{
    queue<int> q;
    q.push(5);
    q.push(4);
    q.push(3);
    q.push(2);
    q.push(1);

    while (true)
    {
        if (q.empty() == true)
            break;

        int value = q.front();
        cout << value << endl;
        q.pop();
    }

    return 0;
}
