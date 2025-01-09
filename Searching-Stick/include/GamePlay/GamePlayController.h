#pragma once
#include "GamePlay/StickCollection/StickCollectionController.h"
namespace GamePlay
{
	class GamePlayView;

	class GamePlayController
	{
	public:
		GamePlayController();
		~GamePlayController();

		void intialize();
		void update();
		void render();


		void reset();

	private:
		GamePlayView* gameplay_view;
		Collection::StickCollectionController* collection_controller;
	};
}