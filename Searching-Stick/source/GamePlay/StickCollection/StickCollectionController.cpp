#include "GamePlay/StickCollection/StickCollectionController.h"
#include "GamePlay/StickCollection/StickCollectionModel.h"
#include "GamePlay/StickCollection/StickCollectionView.h"
#include <SFML/System/Vector2.hpp>
#include "GamePlay/StickCollection/Stick.h"
#include "Global/ServiceLocator.h"
#include <random>

namespace GamePlay
{
	namespace Collection
	{
		using namespace Global;

		StickCollectionController::StickCollectionController()
		{
			collection_model = new StickCollectionModel();
			collection_view = new StickCollectionView();
			initializeStickArray();
		}
		StickCollectionController::~StickCollectionController()
		{
			for (int i = 0; i < sticks.size(); i++)
			{
				delete(sticks[i]);
			}

			delete(collection_model);
			delete(collection_view);
		}
		void StickCollectionController::initialize()
		{
			initializeStick();
			reset();
		}
		void StickCollectionController::update()
		{
			for (int i = 0; i < sticks.size(); i++)
			{
				sticks[i]->stick_view->update();
			}
		}
		void StickCollectionController::render()
		{
			for (int i = 0; i < sticks.size(); i++)
			{
				sticks[i]->stick_view->render();
			}
		}
		void StickCollectionController::searchElement(SearchType search_type)
		{
			//this->search_type = search_type;
			switch (search_type)
			{
			case GamePlay::Collection::LINEAR:
				processLinearSearch();
				break;
			case GamePlay::Collection::BINARY:
				break;
			default:
				break;
			}
		}
		SearchType StickCollectionController::getSearchType()
		{
			return search_type;
		}
		int StickCollectionController::getNumberOfElements()
		{
			return collection_model->number_of_elements;
		}
		void StickCollectionController::reset()
		{
			shuffleStick();
			updatePosition();
			resetStickColor();
			resetSearchStick();
			resetVariables();

		}
		int StickCollectionController::getNumberOfComparisons()
		{
			return number_of_comparisons;
		}
		int StickCollectionController::getNumberOFArrayAccess()
		{
			return number_of_array_access;
		}
		void StickCollectionController::initializeStick()
		{
			float rectangle_width = calculateStickWidth();

			for (int i = 0; i < collection_model->number_of_elements; i++)
			{
				float rectangle_height = calculateStickHeight(i);

				sf::Vector2f rectangle_size = sf::Vector2f(rectangle_width, rectangle_height);

				sticks[i]->stick_view->initialize(rectangle_size, sf::Vector2f(0, 0), 0, collection_model->element_color);

			}
		}
		float StickCollectionController::calculateStickWidth()
		{
			float total_space = static_cast<float>(ServiceLocator::getInstance()->getGraphicService()->getGameWindow()->getSize().x);

			float total_spacing = collection_model->space_percentage * total_space;

			float space_between = total_spacing / (collection_model->number_of_elements - 1);
			collection_model->setElementSpacing(space_between);

			float remaining_space = total_space - total_spacing;

			float rectangle_width = remaining_space / collection_model->number_of_elements;

			return rectangle_width;
		}
		void StickCollectionController::updatePosition()
		{
			for (int i = 0; i < sticks.size(); i++)
			{
				float x_position = (i * sticks[i]->stick_view->getSize().x + (i + 1) * collection_model->elements_spacing);
				float y_position = collection_model->element_y_position - sticks[i]->stick_view->getSize().y;

				sticks[i]->stick_view->setPosition(sf::Vector2f(x_position, y_position));
			}
		}
		void StickCollectionController::resetStickColor()
		{
			for (int i = 0; i < sticks.size(); i++)
			{
				sticks[i]->stick_view->setFillColor(collection_model->element_color);
			}
		}
		void StickCollectionController::initializeStickArray()
		{
			for (int i = 0; i < collection_model->number_of_elements; i++)
			{
				sticks.push_back(new Stick(i));
			}
		}
		float StickCollectionController::calculateStickHeight(int array_position)
		{

			return static_cast<float>(array_position+1)/collection_model->number_of_elements *  collection_model->max_element_height;
		}
		void StickCollectionController::shuffleStick()
		{
			std::random_device device;
			std::mt19937 random_engine(device());

			std::shuffle(sticks.begin(), sticks.end(), random_engine);
		}
		void StickCollectionController::resetSearchStick()
		{
			stick_to_search = sticks[std::rand() % sticks.size()];
			stick_to_search->stick_view->setFillColor(collection_model->search_element_color);
		}
		void StickCollectionController::processLinearSearch()
		{
			for (int i = 0; i < sticks.size(); i++)
			{
				number_of_comparisons++;
				number_of_array_access++;

				ServiceLocator::getInstance()->getSoundService()->playSound(Sound::SoundType::COMPARE_SFX);

				if (sticks[i] == stick_to_search)
				{
					stick_to_search->stick_view->setFillColor(collection_model->found_element_color);
					stick_to_search = nullptr;
					delete(stick_to_search);
					return;
				}
				else
				{
					sticks[i]->stick_view->setFillColor(collection_model->processing_element_color);
					sticks[i]->stick_view->setFillColor(collection_model->element_color);
				}
			}
		}
		void StickCollectionController::resetVariables()
		{
			number_of_comparisons = 0;
			number_of_array_access = 0;
		}
	}
}


