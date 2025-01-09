#pragma once
#include "GamePlay/StickCollection/StickCollectionController.h"
#include "GamePlay/StickCollection/StickCollectionModel.h"
namespace GamePlay
{
	class GamePlayController;
	class StickCollectionController;
	enum SearchType;
	class GamePlayService
	{
	public:
		GamePlayService();
		~GamePlayService();

		void initialize();
		void update();
		void render();

		void searchElement(Collection::SearchType type);
		void reset();

		Collection::SearchType getCurrentSearch();
		int getNumberOfSticks();

	private:
		GamePlayController* gameplay_controller;
		Collection::StickCollectionController* stickcollection_controller;

		void initializeRandomSeed();

	};

}