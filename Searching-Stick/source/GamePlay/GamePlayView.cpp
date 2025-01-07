#include "GamePlay/GamePlayView.h"
#include "Global/Config.h";
#include "Global/ServiceLocator.h"

namespace GamePlay
{
	using namespace UI::UIElement;
	using namespace Global;

	GamePlayView::GamePlayView()
	{
		background_image = nullptr;
		createImage();
	}
	GamePlayView::~GamePlayView()
	{
		destroy();
	}
	void GamePlayView::initialize()
	{
		initializeBackgroundImage();
	}
	void GamePlayView::update()
	{
		background_image->update();
	}
	void GamePlayView::render()
	{
		background_image->render();
	}
	void GamePlayView::createImage()
	{
		background_image = new ImageView();
	}
	void GamePlayView::initializeBackgroundImage()
	{
		sf::RenderWindow* game_window = ServiceLocator::getInstance()->getGraphicService()->getGameWindow();
		background_image->initialize(Config::background_texture_path, game_window->getSize().x, game_window->getSize().y, sf::Vector2f(0, 0));
		background_image->setImageAlpha(background_alpha);
	}
	void GamePlayView::destroy()
	{
		delete(background_image);
	}
}

