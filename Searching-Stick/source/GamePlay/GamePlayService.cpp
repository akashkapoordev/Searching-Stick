#include "GamePlay/GamePlayService.h"
#include "GamePlay/GamePlayController.h"

namespace GamePlay
{
	GamePlayService::GamePlayService()
	{
		gameplay_controller = new GamePlayController();
	}
	GamePlayService::~GamePlayService()
	{
		delete(gameplay_controller);
	}
	void GamePlayService::initialize()
	{
		gameplay_controller->intialize();
	}
	void GamePlayService::update()
	{
		gameplay_controller->update();
	}
	void GamePlayService::render()
	{
		gameplay_controller->render();
	}
	void GamePlayService::reset()
	{
	}
}