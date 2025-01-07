#pragma once
#include "UI/UIElement/ImageView.h"

namespace GamePlay
{
	class GamePlayController;

	class GamePlayView
	{
	public:
		GamePlayView();
		~GamePlayView();


		void initialize();
		void update();
		void render();

	private:
		float background_alpha = 55;
		GamePlayController* gameplay_controller;
		UI::UIElement::ImageView* background_image;

		void createImage();
		void initializeBackgroundImage();
		void destroy();
	};

}