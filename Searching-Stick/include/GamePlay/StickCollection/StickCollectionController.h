#pragma once
#include <vector>
#include <thread>>

namespace GamePlay
{
	namespace Collection
	{
		class StickCollectionModel;
		class StickCollectionView;
		struct Stick;
		enum SearchType;

		class StickCollectionController
		{
		public:
			StickCollectionController();
			~StickCollectionController();


			void initialize();
			void update();
			void render();

			void searchElement(SearchType type);

			SearchType getSearchType();
			int getNumberOfElements();

			void reset();

			int getNumberOfComparisons();
			int getNumberOFArrayAccess();

			int current_operation_dealy;
			int getDelayMilliSeconds();
			sf::String getTimeComplexity();

		private:
			StickCollectionModel* collection_model;
			StickCollectionView* collection_view;
			std::vector<Stick*> sticks;
			SearchType search_type;
			Stick* stick_to_search;
			std::thread search_thread;
			void joinThread();

		

			void initializeStick();
			float calculateStickWidth();
			void updatePosition();
			void resetStickColor();
			void initializeStickArray();
			float calculateStickHeight(int array_position);
			void shuffleStick();
			void resetSearchStick();
			void processLinearSearch();

			int number_of_comparisons;
			int number_of_array_access;

			void resetVariables();

			void processThreadState();

			sf::String time_complexity;

		};

	}
}