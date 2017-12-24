#pragma once
#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#ifndef __SCENEMANAGEGER_H_
	#include "systems/SceneManager.h"
#endif // !__SCENEMANAGEGER_H_

namespace cg3d 
{
	class GameScene : public Scene
	{
	private:
	public:
		GameScene();
		~GameScene();
	};
}

#endif // !_GAMESCENE_H_