#include "GamePlay/GamePlayController.h"
#include "GamePlay/GamePlayView.h"


namespace GamePlay
{
	GamePlayController::GamePlayController()
	{
		gameplay_view = new GamePlayView();
		//collection_controller = new Collection::StickCollectionController();
	}
	GamePlayController::~GamePlayController()
	{
		delete(gameplay_view);
		//delete(collection_controller);
	}
	void GamePlayController::intialize()
	{
		gameplay_view->initialize();
		//collection_controller->initialize();
	}
	void GamePlayController::update()
	{
		gameplay_view->update();
		//collection_controller->update();
	}
	void GamePlayController::render()
	{
		gameplay_view->render();
		//collection_controller->render();
	}
	void GamePlayController::reset()
	{
	}
}