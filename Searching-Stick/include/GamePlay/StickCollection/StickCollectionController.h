#pragma once
#include <vector>

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
			int numberOfElements();

			void reset();

		private:
			StickCollectionModel* collection_model;
			StickCollectionView* collection_view;
			std::vector<Stick*> sticks;
			SearchType search_type;

		

			void initializeStick();
			float calculateStickWidth();
			void updatePosition();
			void resetStickColor();
			void initializeStickArray();
			float calculateStickHeight(int array_position);

		};

	}
}