#include "Task_Game.h"
void Game::Initialize()
{
	std::cout << "Game初期化" << std::endl;
	player.Initialize();
	back.Initialize();
	map.LoadMap("test.txt");


	// 当たり判定テスト
	for (auto& i : map.hitBase)
		for (auto& j : i)
			if (j.objectTag.length() > 0)
				cm.AddChild(&j);
	cm.AddChild(&player);
}

TaskFlag Game::UpDate()
{
	player.UpDate();
	cm.Run();
	TaskFlag nowtask = Task_Game;
	if (Input::KeyInputUp(Input::SPACE))
	{
		nowtask = Task_Title;
	}
	return nowtask;
}

void Game::Render2D()
{
	player.Render();
	map.MapRender();
	back.Render();
}

void Game::Finalize()
{
	std::cout << "Game解放" << std::endl;
	back.Finalize();
	map.Finalize();
	player.Finalize();
}