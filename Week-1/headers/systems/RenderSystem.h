#pragma once
#ifndef RENDERSYSTEM_H_
#define RENDERSYSTEM_H_

#include <map>

namespace cg3d {
	class Window;
	class Engine;
	class ShaderProgram;

	class RenderSystem
	{
		friend class Engine;
	private:
		int _viewWidth;
		int _viewHeight;
		float _viewAspect;

		glm::mat4			_proj;
		glm::mat4			_view;

		std::map<std::string, std::shared_ptr<ShaderProgram>> _programList;
		std::shared_ptr<Window> _activeWindow;
	public:
		RenderSystem();
		~RenderSystem();

		void Initialize();

		void Begin();
		void End();

		void ChangeFrustrum(int width, int height);
	};
}

#endif // !RENDERSYSTEM_H_
