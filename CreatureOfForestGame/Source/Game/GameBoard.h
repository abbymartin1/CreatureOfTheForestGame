#pragma once
#include "GameEngine/EntitySystem/Entity.h"

#include <SFML/System/Vector2.hpp>
#include <vector>

namespace Game
{
	//Used for storing and controlling all game related entities, as well as providing an entry point for the "game" side of application	
	class PlayerEntity;	

	class GameBoard
	{
	public:
		GameBoard();
		virtual ~GameBoard();

		void Update();		
		bool IsGameOver() { return false; }
	private:
		void CreatePlayer();
		void CreateKillerPlant();
		void CreateBackground();
		void CreatePlatforms();
		void CreateRandomSeedBlocks(const sf::Vector2f& pos);
		void CreateRandomLeafBlocks(const sf::Vector2f& pos);
		void CreateRandomHearts(const sf::Vector2f& pos);
		void SpawnRandomSeedBlock();
		void SpawnRandomLeafBlock();
		void SpawnRandomHeartBlock();

		GameEngine::Entity* m_player;
		GameEngine::Entity* m_killerPlant;
	
	protected:
		float RandomFloatRange(float a, float b)
		{
			return ((b - a) * ((float)rand() / RAND_MAX)) + a;
		}

		float m_lastObstacleSpawnTimer;
	};
}

