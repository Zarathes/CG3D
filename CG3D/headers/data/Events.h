#pragma once

namespace cg3d
{
	enum EventID
	{
		INVALID,
		EVENT_MOUSE_MOVE,
		EVENT_MOUSE_CLICK,
		EVENT_MOUSE_SCROLL,
		EVENT_KEYBOARD_INPUT,
		EVENT_WINDOW_RESIZE
	};

	struct Event
	{
		EventID _id = INVALID;
	};

	struct EventMouseMovement : public Event
	{
		glm::vec2 _position;

		EventMouseMovement(glm::vec2 position)
			: _position(position)			
		{
			_id = EVENT_MOUSE_MOVE;
		}
	};

	struct EventMouseClick : public Event
	{
		int _button;
		int _action;

		EventMouseClick(int button, int action)
			: _button(button)
			, _action(action)
		{
			_id = EVENT_MOUSE_CLICK;
		}
	};

	struct EventMouseScroll : public Event
	{
		glm::vec2 _offset;

		EventMouseScroll(glm::vec2 offset)
			: _offset(offset)
		{
			_id = EVENT_MOUSE_SCROLL;
		}
	};

	struct EventKeyboardInput : public Event
	{
		int _key;
		int _action;

		EventKeyboardInput(int key, int action)
			: _key(key)
			, _action(action)
		{
			_id = EVENT_KEYBOARD_INPUT;
		}
	};

	struct EventWindowResize : public Event
	{
		glm::vec2 _size;

		EventWindowResize(glm::vec2 size)
			: _size(size)
		{
			_id = EVENT_WINDOW_RESIZE;
		}
	};
}