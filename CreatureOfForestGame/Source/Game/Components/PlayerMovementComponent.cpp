#include "PlayerMovementComponent.h"
#include "GameEngine/GameEngineMain.h"

#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"

#include <SFML/Window/Keyboard.hpp>

using namespace Game;

PlayerMovementComponent::PlayerMovementComponent()
    : m_lastPlayerSpriteIndex(0)
{

}

PlayerMovementComponent::~PlayerMovementComponent()
{

}

void PlayerMovementComponent::OnAddToWorld()
{
    Component::OnAddToWorld();
}

void PlayerMovementComponent::Update()
{
    Component::Update();

    // grab the time that has passed since the last Update() call 
	float dt = GameEngine::GameEngineMain::GetTimeDelta();

    // Pixels/s
	static float playerVel = 100.f; 

    // Pixels/s
	sf::Vector2f wantedVel = sf::Vector2f(0.f, 0.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
        // Animation
        GameEngine::AnimationComponent* animComponent = GetEntity()->GetComponent<GameEngine::AnimationComponent>();
        if (animComponent)
        {
            animComponent->PlayAnim(GameEngine::EAnimationId::MonkeyMoveLeft);
        }

        // Movement
		wantedVel.x -= playerVel * dt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		wantedVel.x += playerVel * dt;
	}

    // int numAnimationFrames = 4;
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
    // {
    //      m_lastPlayerSpriteIndex++;

    //      if (m_lastPlayerSpriteIndex >= numAnimationFrames)
    //          m_lastPlayerSpriteIndex = 0;
        
    //     // GameEngine::SpriteRenderComponent* spriteRender = GetEntity()->GetComponent<GameEngine::SpriteRenderComponent>();
    //     // if (spriteRender)
    //     //  {
    //     //      spriteRender->SetTileIndex(sf::Vector2i(m_lastPlayerSpriteIndex, 0));
    //     //  }

    //     GameEngine::AnimationComponent* animComponent = GetEntity()->GetComponent<GameEngine::AnimationComponent>();
    //     if (animComponent)
    //     {
    //         animComponent->PlayAnim(GameEngine::EAnimationId::MonkeyMoveLeft);
    //     }
    // }

    // update the entity with the new velocity
    GetEntity()->SetPos(GetEntity()->GetPos() + wantedVel);
}
