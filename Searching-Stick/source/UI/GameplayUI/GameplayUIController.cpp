#include "UI/GameplayUI/GameplayUIController.h"
#include "Global/Config.h";
#include "Global/ServiceLocator.h"
#include "GamePlay/StickCollection/StickCollectionModel.h"
#include "Main/GameService.h"

namespace UI
{
	namespace GamePlayUI
	{
		using namespace UIElement;
		using namespace Global;
		using namespace GamePlay::Collection;
		using namespace Main;

		GameplayUIController::GameplayUIController()
		{
			createService();
		}
		GameplayUIController::~GameplayUIController()
		{
			destroy();
		}
		void GameplayUIController::initialize()
		{
			initializeButton();
			initializeText();
			registerCallBack();
		}
		void GameplayUIController::update()
		{
			updateText();
			menu_button->update();
			search_type->update();
			number_of_sticks->update();
			number_of_comparisons->update();
			delay->update();
			number_of_array_access->update();
			time_complexity->update();
		}
		void GameplayUIController::render()
		{
			menu_button->render();
			search_type->render();
			number_of_sticks->render();
			number_of_comparisons->render();
			delay->render();
			number_of_array_access->render();
			time_complexity->render();
		}
		void GameplayUIController::show()
		{
			menu_button->show();
			search_type->show();
			number_of_sticks->show();
			number_of_comparisons->show();
			delay->show();
			number_of_array_access->show();
			time_complexity->show();
		}
		void GameplayUIController::createService()
		{
			menu_button = new ButtonView();

			search_type = new TextView();
			number_of_comparisons = new TextView();
			number_of_array_access = new TextView();
			number_of_sticks = new TextView();
			delay = new TextView();
			time_complexity = new TextView();
		}
		void GameplayUIController::initializeButton()
		{
			menu_button->initialize("Menu Button", Config::quit_button_texture_path, button_width, button_height, sf::Vector2f(button_x, 0));
		}
		void GameplayUIController::initializeText()
		{
			search_type->initialize("ABC", sf::Vector2f(x_position+30, y_position), FontType::BUBBLE_BOBBLE, font_size, sf::Color::White);
			number_of_sticks->initialize("0", sf::Vector2f(x_position+30, y_position + space_between_y), FontType::BUBBLE_BOBBLE, font_size, sf::Color::White);
			number_of_comparisons->initialize("0", sf::Vector2f(x_position+space_between_x, y_position), FontType::BUBBLE_BOBBLE, font_size, sf::Color::White);
			delay->initialize("0", sf::Vector2f(x_position + space_between_x, y_position+space_between_y), FontType::BUBBLE_BOBBLE, font_size, sf::Color::White);
			number_of_array_access->initialize("0", sf::Vector2f(x_position + space_between_x*2, y_position), FontType::BUBBLE_BOBBLE, font_size, sf::Color::White);
			time_complexity->initialize("0", sf::Vector2f(x_position + space_between_x*2, y_position+space_between_y), FontType::BUBBLE_BOBBLE, font_size, sf::Color::White);



		}
		void GameplayUIController::updateText()
		{
			// Type Search
			sf::String updatedText;
			switch (ServiceLocator::getInstance()->getGamePlayService()->getCurrentSearch())
			{
			case SearchType::LINEAR:
				updatedText = "Linear";
				break;
			case SearchType::BINARY:
				updatedText = "Binary";
				break;
			default:
					updatedText = "ABC";
			}

			search_type->setText(updatedText);

			//Number Of Sticks
			sf::String updated_sticks;
            updated_sticks = "Number of Sticks : " + sf::String(std::to_string(ServiceLocator::getInstance()->getGamePlayService()->getNumberOfSticks()));
			number_of_sticks->setText(updated_sticks);

			//Number of Comparisons
			sf::String upadted_comaprisons;
			upadted_comaprisons = "Comaprison : " + sf::String(std::to_string(ServiceLocator::getInstance()->getGamePlayService()->getNumberOfComaprison()));
			number_of_comparisons->setText(upadted_comaprisons);

			//Updated Delay
			sf::String updated_delay;
			updated_delay = "Delay(ms) : " + sf::String(std::to_string(ServiceLocator::getInstance()->getGamePlayService()->getDelay()));
			delay->setText(updated_delay);

			//Upadted ArrayAccess
			sf::String updated_Array_access;
			updated_Array_access = "Number of Array Access : " + sf::String(std::to_string(ServiceLocator::getInstance()->getGamePlayService()->getNumberOfArrayAccess()));
			number_of_array_access->setText(updated_Array_access);

			//Updated Time Compliexity
			sf::String updated_time_complexity;
			updated_time_complexity = "Time Complexity : " + ServiceLocator::getInstance()->getGamePlayService()->getTimeComplexity();
			time_complexity->setText(updated_time_complexity);



		}
		void GameplayUIController::destroy()
		{
			delete(menu_button);
			delete(search_type);
			delete(number_of_sticks);
			delete(number_of_comparisons);
			delete(delay);
			delete(number_of_array_access);
			delete(time_complexity);
		}
		void GameplayUIController::registerCallBack()
		{
			menu_button->registerCallbackFuntion(std::bind(&GameplayUIController::mainMenuCallBack, this));

		}
		void GameplayUIController::mainMenuCallBack()
		{
			GameService::setGameState(GameState::MAIN_MENU);
			ServiceLocator::getInstance()->getGamePlayService()->reset();
			ServiceLocator::getInstance()->getSoundService()->playSound(Sound::SoundType::BUTTON_CLICK);
		}
	}
}