#pragma once

namespace GamePlay
{
	class GamePlayController;
	class GamePlayService
	{
	public:
		GamePlayService();
		~GamePlayService();

		void initialize();
		void update();
		void render();


		void reset();

	private:
		GamePlayController* gameplay_controller;
	};

}