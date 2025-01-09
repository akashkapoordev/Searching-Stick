#include "GamePlay/GamePlayService.h"
#include "GamePlay/GamePlayController.h"
#include <ctime>

namespace GamePlay
{
	GamePlayService::GamePlayService()
	{
		gameplay_controller = new GamePlayController();
		stickcollection_controller = new Collection::StickCollectionController();
	}
	GamePlayService::~GamePlayService()
	{
		delete(gameplay_controller);
		delete(stickcollection_controller);
	}
	void GamePlayService::initialize()
	{
		initializeRandomSeed();
		
		gameplay_controller->intialize();
		stickcollection_controller->initialize();
	}
	void GamePlayService::update()
	{
		gameplay_controller->update();
		stickcollection_controller->update();
	}
	void GamePlayService::render()
	{
		gameplay_controller->render();
		stickcollection_controller->render();
	}
	void GamePlayService::searchElement(Collection::SearchType type)
	{
		stickcollection_controller->searchElement(type);
	}
	void GamePlayService::reset()
	{
		stickcollection_controller->reset();
	}
	Collection::SearchType GamePlayService::getCurrentSearch()
	{
		return stickcollection_controller->getSearchType();
	}
	int GamePlayService::getNumberOfSticks()
	{
		return stickcollection_controller->getNumberOfElements();
	}
	int GamePlayService::getNumberOfComaprison()
	{
		return stickcollection_controller->getNumberOfComparisons();
	}
	int GamePlayService::getDelay()
	{
		return stickcollection_controller->getDelayMilliSeconds();
	}
	int GamePlayService::getNumberOfArrayAccess()
	{
		return stickcollection_controller->getNumberOFArrayAccess();
	}
	sf::String GamePlayService::getTimeComplexity()
	{
		return stickcollection_controller->getTimeComplexity();
	}
	void GamePlayService::initializeRandomSeed()
	{
		std::srand(static_cast<unsigned int>(std::time(nullptr)));
	}
}