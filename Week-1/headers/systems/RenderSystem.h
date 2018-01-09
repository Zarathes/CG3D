#pragma once
#ifndef RENDERSYSTEM_H_
#define RENDERSYSTEM_H_

#include <map>

namespace cg3d {
	class Engine;
	class ShaderProgram;

	class RenderSystem
	{
		friend class Engine;
	private:
		std::map<std::string, std::shared_ptr<ShaderProgram>> _programList;
	public:
		RenderSystem();
		~RenderSystem();

		void Initialize();

		void Begin();
		void End();
	};
}

#endif // !RENDERSYSTEM_H_
