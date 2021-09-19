#include "PlayerMovementComponent.h"
#include "GameEngine/GameEngineMain.h"

#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include "GameEngine/EntitySystem/Components/PawnPhysicsComponent.h"

#include <SFML/Window/Keyboard.hpp>

using namespace Game;

PlayerMovementComponent::PlayerMovementComponent()
    : m_wasJumpButtonPressed(false)
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

    // Pixels/s
    float playerVelocity = 0.1f;
    float jumpVelocity = 90.f;

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
		wantedVel.x -= playerVelocity;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		wantedVel.x += playerVelocity;
	}
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		// This boolean flag makes sure we react to pressing up only once, instead of applying this velocity 
        // for as long as button is pressed 
        if (!m_wasJumpButtonPressed)
        {
            wantedVel.y -= jumpVelocity;
            m_wasJumpButtonPressed = true;
        }
	}
    else
    {
        m_wasJumpButtonPressed = false;
    }

    GameEngine::PawnPhysicsComponent* pawnPhys = GetEntity()->GetComponent<GameEngine::PawnPhysicsComponent>();
    if (pawnPhys)
    {
        pawnPhys->SetVelocity(wantedVel);
    }

    // update the entity with the new velocity
    GetEntity()->SetPos(GetEntity()->GetPos() + wantedVel);
}
