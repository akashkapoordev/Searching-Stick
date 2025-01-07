#include "GamePlay/GamePlayController.h"
#include "GamePlay/GamePlayView.h"

namespace GamePlay
{
	GamePlayController::GamePlayController()
	{
		gameplay_view = new GamePlayView();
	}
	GamePlayController::~GamePlayController()
	{
		delete(gameplay_view);
	}
	void GamePlayController::intialize()
	{
		gameplay_view->initialize();
	}
	void GamePlayController::update()
	{
		gameplay_view->update();
	}
	void GamePlayController::render()
	{
		gameplay_view->render();
	}
	void GamePlayController::reset()
	{
	}
}