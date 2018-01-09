#include "systems/InputManager.h"

using namespace cg3d;

// Additional includes

InputManager::InputManager()
{
}
InputManager::~InputManager()
{
}

void InputManager::ChangeControlScheme(std::vector<int> keyConfig)
{
	_keyConfig = keyConfig;
}

std::vector<std::pair<int, int>> InputManager::ProcessRawInput(std::vector<KeyStroke> rawInput)
{
	if (!rawInput.empty())
	{
		for (size_t i = 0; i < rawInput.size(); i++)
		{	
			_keyMap[rawInput.at(i)._key] = rawInput.at(i)._action;
		}
	}

	std::vector<std::pair<int, int>> keyInput;
	for each (int key in _keyConfig)
	{
		keyInput.push_back(std::make_pair(key, _keyMap[key]));
	}

	return keyInput;
}
