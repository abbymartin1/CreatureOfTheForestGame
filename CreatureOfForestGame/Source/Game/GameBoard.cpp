#include "GameBoard.h"

#include "GameEngine/GameEngineMain.h"
#include "Game/Components/PlayerMovementComponent.h"
#include "Game/Components/KillerPlantMovementComponent.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include "GameEngine/EntitySystem/Components/AnimationComponent.h"
#include "GameEngine/EntitySystem/Components/CollidablePhysicsComponent.h"
#include "GameEngine/EntitySystem/Components/CollidableComponent.h"
#include "GameEngine/EntitySystem/Components/PawnPhysicsComponent.h"
#include "GameEngine/EntitySystem/Components/PhysicsComponentBlock.h"
#include "Game/GameComponents/PlayerCameraComponent.h"

#include <iostream>
#include <ctime>
#include <unistd.h>

using namespace Game;

GameBoard::GameBoard()
	: m_player(nullptr)
	, m_killerPlant(nullptr)
	, m_isGameOver(false)
	, m_lastObstacleSpawnTimer(0.f)
{
	CreatePlayer();
	//CreateKillerPlant();
	CreateBackground();
	CreatePlatforms();
}

GameBoard::~GameBoard()
{

}

std::string getCurrentDateTime()
{
    time_t tt;
    struct tm *st;

    time(&tt);
    st = localtime(&tt);
    return asctime(st);
}

void GameBoard::CreatePlayer()
{
	m_player = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_player);

	m_player->SetPos(sf::Vector2f(50.f, 50.f));
	m_player->SetSize(sf::Vector2f(71.f, 63.f));

	// Render
	GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(m_player->AddComponent<GameEngine::SpriteRenderComponent>());

	render->SetFillColor(sf::Color::Transparent);
	render->SetTexture(GameEngine::eTexture::Player);

	// Movement
	m_player->AddComponent<PlayerMovementComponent>();
	m_player->AddComponent<GameEngine::AnimationComponent>();

	// Collision
	m_player->SetEntityTag("player");
	m_player->AddComponent<GameEngine::PawnPhysicsComponent>();

	// Camera
	m_player->AddComponent<PlayerCameraComponent>();
}

void GameBoard::CreateKillerPlant()
{
	m_killerPlant = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_killerPlant);

	m_killerPlant->SetPos(sf::Vector2f(120.f, 300.f));
	m_killerPlant->SetSize(sf::Vector2f(100.f, 100.f));

	// Render
	GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(m_killerPlant->AddComponent<GameEngine::SpriteRenderComponent>());

	render->SetFillColor(sf::Color::Transparent);
	render->SetTexture(GameEngine::eTexture::KillerPlant);

	// Movement
	m_killerPlant->AddComponent<KillerPlantMovementComponent>();
	m_killerPlant->AddComponent<GameEngine::AnimationComponent>();

	// Collision
	m_killerPlant->AddComponent<GameEngine::CollidablePhysicsComponent>();
}

void GameBoard::CreateBackground()
{
	GameEngine::Entity* background = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(background);

	background->SetPos(sf::Vector2f(250.f, 250.f));
	background->SetSize(sf::Vector2f(500.f, 500.f));

	// Render
	GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(background->AddComponent<GameEngine::SpriteRenderComponent>());

	render->SetFillColor(sf::Color::Transparent);
	render->SetTexture(GameEngine::eTexture::BG);
	render->SetZLevel(-1);
}

void GameBoard::CreatePlatforms()
{
	// There will be 5 static platforms the orangutang must navigate.
	// Future iterations would include moving platforms, a larger map, and multiple levels

	// Platform 1 
	GameEngine::Entity* platform1 = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(platform1);
	platform1->SetPos(sf::Vector2f(100.f, 100.f));
	platform1->SetSize(sf::Vector2f(225.f, 72.f));
	// Render - Platform 1
	GameEngine::SpriteRenderComponent* render1 = static_cast<GameEngine::SpriteRenderComponent*>(platform1->AddComponent<GameEngine::SpriteRenderComponent>());
	render1->SetFillColor(sf::Color::Transparent);
	render1->SetTexture(GameEngine::eTexture::JunglePlatform);
	// Collision - Platform 1
	platform1->AddComponent<GameEngine::CollidablePhysicsComponent>();

  	// Platform 2 
	GameEngine::Entity* platform2 = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(platform2);
	platform2->SetPos(sf::Vector2f(400.f, 400.f));
	platform2->SetSize(sf::Vector2f(225.f, 72.f));
	// Render - Platform 2
	GameEngine::SpriteRenderComponent* render2 = static_cast<GameEngine::SpriteRenderComponent*>(platform2->AddComponent<GameEngine::SpriteRenderComponent>());
	render2->SetFillColor(sf::Color::Transparent);
	render2->SetTexture(GameEngine::eTexture::JunglePlatform);
	// Collision - Platform 2
	platform2->AddComponent<GameEngine::CollidablePhysicsComponent>();

	// Platform 3
	GameEngine::Entity* platform3 = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(platform3);
	platform3->SetPos(sf::Vector2f(120.f, 240.f));
	platform3->SetSize(sf::Vector2f(250.f, 63.f));
	// Render - Platform 3
	GameEngine::SpriteRenderComponent* render3 = static_cast<GameEngine::SpriteRenderComponent*>(platform3->AddComponent<GameEngine::SpriteRenderComponent>());
	render3->SetFillColor(sf::Color::Transparent);
	render3->SetTexture(GameEngine::eTexture::JunglePlatform2);
	// Collision - Platform 3
	platform3->AddComponent<GameEngine::CollidablePhysicsComponent>();

	// Platform 4
	GameEngine::Entity* platform4 = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(platform4);
	platform4->SetPos(sf::Vector2f(500.f, 200.f));
	platform4->SetSize(sf::Vector2f(225.f, 63.f));
	// Render - Platform 4
	GameEngine::SpriteRenderComponent* render4 = static_cast<GameEngine::SpriteRenderComponent*>(platform4->AddComponent<GameEngine::SpriteRenderComponent>());
	render4->SetFillColor(sf::Color::Transparent);
	render4->SetTexture(GameEngine::eTexture::JunglePlatform2);
	// Collision - Platform 4
	platform4->AddComponent<GameEngine::CollidablePhysicsComponent>();


	// Platform 5 
	GameEngine::Entity* platform5 = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(platform5);
	platform5->SetPos(sf::Vector2f(0.f, 450.f));
	platform5->SetSize(sf::Vector2f(225.f, 63.f));
	// Render - Platform 5
	GameEngine::SpriteRenderComponent* render5 = static_cast<GameEngine::SpriteRenderComponent*>(platform5->AddComponent<GameEngine::SpriteRenderComponent>());
	render5->SetFillColor(sf::Color::Transparent);
	render5->SetTexture(GameEngine::eTexture::JunglePlatform2);
	// Collision - Platform 5
	platform5->AddComponent<GameEngine::CollidablePhysicsComponent>();
}

void GameBoard::SpawnRandomSeedBlock()
{
	static float minNextSpawnTime = 2.f;
	static float maxNextSpawnTime = 4.f;

	static float minObstacleXPos = 100.f;
	static float maxObstacleXPos = 450.f;
	static float minObstacleYPos = 20.f;
	static float maxObstacleYPos = 30.f;

	sf::Vector2f pos = sf::Vector2f(RandomFloatRange(minObstacleXPos, maxObstacleXPos), RandomFloatRange(minObstacleYPos, maxObstacleYPos));

	CreateRandomSeedBlocks(pos);

	m_lastObstacleSpawnTimer = RandomFloatRange(minNextSpawnTime, maxNextSpawnTime);
}

void GameBoard::SpawnRandomLeafBlock()
{
	static float minObstacleXPos = 100.f;
	static float maxObstacleXPos = 450.f;
	static float minObstacleYPos = 20.f;
	static float maxObstacleYPos = 30.f;

	sf::Vector2f pos = sf::Vector2f(RandomFloatRange(minObstacleXPos, maxObstacleXPos), RandomFloatRange(minObstacleYPos, maxObstacleYPos));

	CreateRandomLeafBlocks(pos);
}

void GameBoard::SpawnRandomHeartBlock()
{
	static float minObstacleXPos = 100.f;
	static float maxObstacleXPos = 200.f;
	static float minObstacleYPos = 20.f;
	static float maxObstacleYPos = 30.f;

	sf::Vector2f pos = sf::Vector2f(RandomFloatRange(minObstacleXPos, maxObstacleXPos), RandomFloatRange(minObstacleYPos, maxObstacleYPos));

	CreateRandomHearts(pos);
}

void GameBoard::CreateRandomSeedBlocks(const sf::Vector2f& pos)
{
	GameEngine::Entity* seedBlock = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(seedBlock);

	seedBlock->SetPos(sf::Vector2f(pos.x, pos.y));
	seedBlock->SetSize(sf::Vector2f(20.f, 20.f));

	// Render
	GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(seedBlock->AddComponent<GameEngine::SpriteRenderComponent>());

	render->SetFillColor(sf::Color::Transparent);
	render->SetTexture(GameEngine::eTexture::Seed);

	// Collision
	seedBlock->SetEntityTag("seed");
	seedBlock->AddComponent<GameEngine::PhysicsComponentBlock>();
}

void GameBoard::CreateRandomLeafBlocks(const sf::Vector2f& pos)
{
	GameEngine::Entity* leafBlock = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(leafBlock);

	leafBlock->SetPos(sf::Vector2f(pos.x, pos.y));
	leafBlock->SetSize(sf::Vector2f(30.f, 30.f));

	// Render
	GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(leafBlock->AddComponent<GameEngine::SpriteRenderComponent>());

	render->SetFillColor(sf::Color::Transparent);
	render->SetTexture(GameEngine::eTexture::Leaf);

	// Collision
	leafBlock->SetEntityTag("leaf");
	leafBlock->AddComponent<GameEngine::PhysicsComponentBlock>();
}

void GameBoard::CreateRandomHearts(const sf::Vector2f& pos)
{
	GameEngine::Entity* heart = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(heart);

	heart->SetPos(sf::Vector2f(pos.x, pos.y));
	heart->SetSize(sf::Vector2f(20.f, 20.f));

	// Render
	GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(heart->AddComponent<GameEngine::SpriteRenderComponent>());

	render->SetFillColor(sf::Color::Transparent);
	render->SetTexture(GameEngine::eTexture::Heart);

	// Collision
	heart->SetEntityTag("heart");
	heart->AddComponent<GameEngine::PhysicsComponentBlock>();
}

void GameBoard::Update()
{	
	float dt = GameEngine::GameEngineMain::GetInstance()->GetTimeDelta();
	m_lastObstacleSpawnTimer -= dt;
	if (m_lastObstacleSpawnTimer <= 0.f)
	{
		SpawnRandomSeedBlock();
	}

	if (m_isGameOver)
	{
		GameOver();
	}
}

void GameBoard::GameOver()
{
	GameEngine::Entity* backgroundGameOver = new GameEngine::Entity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(backgroundGameOver);

	backgroundGameOver->SetPos(sf::Vector2f(250.f, 250.f));
	backgroundGameOver->SetSize(sf::Vector2f(500.f, 500.f));

	// Render
	GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(backgroundGameOver->AddComponent<GameEngine::SpriteRenderComponent>());

	render->SetFillColor(sf::Color::Transparent);
	render->SetTexture(GameEngine::eTexture::BGGameOver);
	render->SetZLevel(4);
}