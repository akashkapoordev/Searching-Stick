#pragma once
#include "Graphics/GraphicService.h"
#include "Event/EventService.h"
#include "UI/UIService.h"
#include "Sound/SoundService.h"
#include "GamePlay/GamePlayService.h"

namespace Global
{
    class ServiceLocator
    {
    private:
        Event::EventService* event_service;
        Graphics::GraphicService* graphic_service;
        Sound::SoundService* sound_service;
        UI::UIService* ui_service;
        GamePlay::GamePlayService* gameplay_service;

        ServiceLocator();
        ~ServiceLocator();

        void createServices();
        void clearAllServices();

    public:
        static ServiceLocator* getInstance();

        void initialize();
        void update();
        void render();

        Event::EventService* getEventService();
        Graphics::GraphicService* getGraphicService();
        Sound::SoundService* getSoundService();
        UI::UIService* getUIService();
        GamePlay::GamePlayService* getGamePlayService();
        
    };
}