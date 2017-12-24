#pragma once
#ifndef __SCENEMANAGEGER_H_
#define __SCENEMANAGEGER_H_

namespace cg3d {
	// Enumerations
	enum class SceneID {
		BASE = 000,
		GAME = 001,
	};

	// Forward declaration
	class Engine;

	class Scene
	{
	public:
		virtual void Load() = 0;
		virtual void Update(float delta) = 0;
		virtual void Redraw() = 0;
		virtual void Unload() = 0;
	};

	class SceneManager
	{
		
	friend class Engine;
	private:
		Scene* _currentScene;
		
		SceneManager();
		Scene* CreateScene(SceneID id);
	public:
		~SceneManager();
		void ChangeScene(SceneID id);
	};
}

#endif // __SCENEMANAGEGER_H_