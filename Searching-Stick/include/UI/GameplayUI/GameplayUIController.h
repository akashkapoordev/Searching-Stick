#pragma once
#include "UI/Interface/IUIController.h"
#include "UI/UIElement/ButtonView.h"
#include "UI/UIElement/ImageView.h"
#include "UI/UIElement/TextView.h"
#include "GamePlay/GamePlayService.h"

namespace UI
{
	namespace GamePlayUI
	{
		class GameplayUIController:public UI::Interface::IUIController
		{
		public:
			GameplayUIController();
			~GameplayUIController();

			float x_position = 0.f;
			float y_position = 30.f;

			float text_width = 100.f;
			float text_height = 100.f;

			float button_width = 100.f;
			float button_height = 50.f;

			float button_x = 1800.f;
			int font_size = 35;

			int space_between_x = 700.f;
			int space_between_y = 30.f;

			void initialize() override;
			void update() override;
			void render() override;
			void show() override;


		private:
			UIElement::ButtonView* menu_button;
			UIElement::TextView* search_type;
			UIElement::TextView* number_of_comparisons;
			UIElement::TextView* number_of_array_access;
			UIElement::TextView* number_of_sticks;
			UIElement::TextView* delay;
			UIElement::TextView* time_complexity;


			void createService();
			void initializeButton();
			void initializeText();
			void updateText();
			void destroy();

			void registerCallBack();
			void mainMenuCallBack();
		};
	}
}