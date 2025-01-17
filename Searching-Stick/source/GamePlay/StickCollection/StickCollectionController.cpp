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
			if (search_thread.joinable()) search_thread.join();
			for (int i = 0; i < sticks.size(); i++)
			{
				delete(sticks[i]);
			}
			sticks.clear();

			delete(collection_model);
			delete(collection_view);
		}
		void StickCollectionController::initialize()
		{
			collection_model->initialize();
			initializeStick();
			reset();
			time_complexity = "ABC";
		}
		void StickCollectionController::update()
		{
			processThreadState();
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
			this->search_type = search_type;
			switch (search_type)
			{
			case GamePlay::Collection::LINEAR:
				time_complexity = "O(n)";
				current_operation_dealy = collection_model->linear_search_delay;
				search_thread = std::thread(&StickCollectionController::processLinearSearch, this);
				break;
			case GamePlay::Collection::BINARY:
				sortElements();
				time_complexity = "O(log n)";
				current_operation_dealy = collection_model->binary_search_delay;
				search_thread = std::thread(&StickCollectionController::processBinarySearch, this);
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
			current_operation_dealy = 0;

		}
		int StickCollectionController::getNumberOfComparisons()
		{
			return number_of_comparisons;
		}
		int StickCollectionController::getNumberOFArrayAccess()
		{
			return number_of_array_access;
		}
		int StickCollectionController::getDelayMilliSeconds()
		{
			return current_operation_dealy;
		}
		sf::String StickCollectionController::getTimeComplexity()
		{
			return time_complexity;
		}
		void  StickCollectionController::joinThread()
		{
			search_thread.join();
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
					std::this_thread::sleep_for(std::chrono::milliseconds(current_operation_dealy));
					sticks[i]->stick_view->setFillColor(collection_model->element_color);
				}
			}
		}
		void StickCollectionController::processBinarySearch()
		{
			int left = 0;
			int right = sticks.size();

			while (left < right)
			{
				int mid = (left+right)/2;
				number_of_array_access += 2;
				number_of_comparisons++;
				ServiceLocator::getInstance()->getSoundService()->playSound(Sound::SoundType::COMPARE_SFX);

				if(sticks[mid] == stick_to_search)
				{
					stick_to_search->stick_view->setFillColor(collection_model->found_element_color);
					stick_to_search = nullptr;
					delete(stick_to_search);
					return;
				}

				sticks[mid]->stick_view->setFillColor(collection_model->processing_element_color);
				std::this_thread::sleep_for(std::chrono::milliseconds(current_operation_dealy));
				sticks[mid]->stick_view->setFillColor(collection_model->element_color);

				number_of_array_access++;

				if (sticks[mid]->data <= stick_to_search->data)
				{
					left = mid;
				}
				else
				{
					right = mid;
				}
			}
		}

		void StickCollectionController::resetVariables()
		{
			number_of_comparisons = 0;
			number_of_array_access = 0;
		}
		void StickCollectionController::processThreadState()
		{
			if (search_thread.joinable() && stick_to_search == nullptr)
			{
				joinThread();
			}
		}
		void StickCollectionController::sortElements()
		{
			std::sort(sticks.begin(), sticks.end(), [this](const Stick* a, const Stick* b) {return compareElements(a, b); });

			updatePosition();
		}
		bool StickCollectionController::compareElements(const Stick* a, const Stick* b) const
		{
			return a->data < b->data;
		}

	}
}


