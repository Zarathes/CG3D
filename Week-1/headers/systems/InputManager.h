#pragma once
#ifndef INPUTMANAGER_H_ 

// Additional includes

#include <map>

namespace cg3d {
	class InputManager
	{
	private:
		std::map<int, int>	_keyMap;
		std::vector<int>	_keyConfig;
	public:

		InputManager();
		~InputManager();

		void ChangeControlScheme(std::vector<int> keyConfig);
		std::vector<std::pair<int, int>> ProcessRawInput(std::vector<KeyStroke> data);
	};
}

#endif // !INPUTMANAGER_H_ 