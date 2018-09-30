#pragma once

#include "utilities/Observer.h"

namespace cg3d
{	
	class Window;

	class EditorOverlay : public Observer
	{
	public:
		static EditorOverlay& get()
		{
			static EditorOverlay _instance;
			return _instance;
		}
	private:
		bool _isVisible;
		bool _showCursor;

		EditorOverlay();
	public:
		~EditorOverlay();

		EditorOverlay(const EditorOverlay&) = delete;
		EditorOverlay& operator=(const EditorOverlay&) = delete;

		void onNotify(Event& event);

		void start(Window* window);
		void update();

		void begin();
		void redraw();
		void end();
	};
}