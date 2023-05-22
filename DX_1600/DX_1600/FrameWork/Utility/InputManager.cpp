#include "framework.h"
#include "InputManager.h"

InputManager* InputManager::_instance = nullptr;

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

void InputManager::Update()
{
	memcpy(_oldState, _curState, sizeof(_oldState));

	GetKeyboardState(_curState);

	for (int i = 0; i < KEY_MAX; i++)
	{
		byte key = _curState[i] & 0x80;
		// 삼항조건연산자 -> ? 왼쪽에 있는것이 참이면 : 왼쪽을 반환, 거짓이면 : 오른쪽에 있는것 반환
		// a ? b : c 일 때 a가 true면 b 실행, 아니면 c 실행
		_curState[i] = (key ? 1 : 0);

		int old = _oldState[i];
		int cur = _curState[i];

		if (old == 0 && cur == 1)
		{
			_stateMap[i] = State::DOWN;
		}

		else if (old == 1 && cur == 0)
		{
			_stateMap[i] = State::UP;
		}

		else if (old == 1 && cur == 1)
		{
			_stateMap[i] = State::PRESS;
		}

		else
		{
			_stateMap[i] = State::NONE;
		}
	}
}
