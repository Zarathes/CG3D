#pragma once

// Additional includes
#include "utilities/Observer.h"
#include <map>

namespace cg3d {
	class Window;
	class Scene;

	class RenderSystem : public Observer
	{
	private:
		uint32_t _materialSSBO;

		Window * _activeWindow;
		glm::vec2 _windowSize;
	public:
		RenderSystem();
		~RenderSystem();
		
		void onNotify(Event& event);

		void initialize();
		void start();
		void redraw(Scene* scene);
		Window * getWindow() const;
	};
}
