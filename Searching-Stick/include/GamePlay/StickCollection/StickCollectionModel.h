#pragma once
#include <SFML/Graphics/Color.hpp>
#include <thread>

namespace GamePlay
{
	namespace Collection
	{
		enum SearchType
		{
			LINEAR,
			BINARY
		};

		class  StickCollectionModel
		{
		public:

			const float max_element_height = 820.f;
			float elements_spacing = 25.f;
			const float element_y_position = 1020.f;
			float space_percentage = 0.50f;

			const sf::Color element_color = sf::Color::White;
			const sf::Color search_element_color = sf::Color::Blue;
			const sf::Color found_element_color = sf::Color::Green;
			const sf::Color processing_element_color = sf::Color::Red;

			int linear_search_delay = 120;
			int number_of_elements = 100;
			int binary_search_delay = 120;
			

			StickCollectionModel();
			~StickCollectionModel();

			void initialize();
			void update();


			void setElementSpacing(float space);
			

		private:
		
		};

	}
}