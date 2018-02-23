#pragma once
#ifndef SCENEMANAGEGER_H_
#define SCENEMANAGEGER_H_

// Additional includes

namespace cg3d {
	// Forward declaration
	class Engine;

	class Scene
	{
	protected:
		SceneID					    _ID;
		std::vector<int>			_keyConfig;
	public:
		virtual void Load() = 0;
		virtual void ProcessInput(std::vector<std::pair<int, int>>) = 0;
		virtual void Update(float delta) = 0;
		virtual void Redraw(float delta) = 0;
		virtual void Unload() = 0;

		std::vector<int> GetControlScheme() { return _keyConfig; }
	};

	class SceneManager
	{
		
	friend class Engine;
	private:
		Scene* _currentScene;		
		Scene* CreateScene(SceneID id, std::shared_ptr<Engine> delegate);
	public:
		SceneManager();
		~SceneManager();
		void ChangeScene(SceneID id, std::shared_ptr<Engine> delegate);
	};
}

#endif // !SCENEMANAGEGER_H_