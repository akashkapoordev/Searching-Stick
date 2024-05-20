#include "Gameplay/GameplayService.h"
#include "Gameplay/GameplayController.h"
#include "Gameplay/GameplayModel.h"
#include "Global/ServiceLocator.h"

namespace Gameplay
{
	using namespace Global;

	GameplayService::GameplayService()
	{
		gameplay_controller = new GameplayController();
	}

	GameplayService::~GameplayService()
	{
		delete (gameplay_controller);
	}

	void GameplayService::initializeRandomSeed()		//helper function for random seed
	{
		std::srand(static_cast<unsigned int>(std::time(nullptr)));
	}

	void GameplayService::initialize()
	{
		gameplay_controller->initialize();
		initializeRandomSeed();		// calling helper function
	}

	void GameplayService::update()
	{
		gameplay_controller->update();
	}

	void GameplayService::render()
	{
		gameplay_controller->render();
	}

	void GameplayService::reset()
	{
		gameplay_controller->reset();
	}

	void GameplayService::searchElement(SearchType search_type)
	{
		gameplay_controller->searchElement(search_type);
	}

	SearchType GameplayService::getCurrentSearchType()
	{
		return gameplay_controller->getSearchType();
	}

	int GameplayService::getNumberOfComparisons()
	{
		return gameplay_controller->getNumberOfComparisons();
	}

	int GameplayService::getNumberOfArrayAccess()
	{
		return gameplay_controller->getNumberOfArrayAccess();
	}

	int GameplayService::getNumberOfSticks()
	{
		return gameplay_controller->getNumberOfSticks();
	}

	int GameplayService::getDelayMilliseconds()
	{
		return gameplay_controller->getDelayMilliseconds();
	}

	sf::String GameplayService::getTimeComplexity()
	{
		return gameplay_controller->getTimeComplexity();
	}
}