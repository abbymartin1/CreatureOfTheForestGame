#include "PlayerMovementComponent.h"
#include "GameEngine/GameEngineMain.h"

#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include "GameEngine/EntitySystem/Components/PawnPhysicsComponent.h"

#include <SFML/Window/Keyboard.hpp>

using namespace Game;

PlayerMovementComponent::PlayerMovementComponent()
    : m_wasJumpButtonPressed(false)
    , m_moveLeftTimerDt(0.f)
    , m_moveRightTimerDt(0.f)
    , m_moveTimerMaxTime(2.f)
    , m_animComponent(nullptr)
{

}

PlayerMovementComponent::~PlayerMovementComponent()
{

}

void PlayerMovementComponent::OnAddToWorld()
{
    m_animComponent = GetEntity()->GetComponent<GameEngine::AnimationComponent>();
    Component::OnAddToWorld();
}

void PlayerMovementComponent::Update()
{
    Component::Update();

    // Pixels/s
    float playerVelocity = 0.1f;
    float jumpVelocity = 100.f;

    // Pixels/s
	sf::Vector2f wantedVel = sf::Vector2f(0.f, 0.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
        m_moveLeftTimerDt = m_moveTimerMaxTime;
        m_moveRightTimerDt = 0.f;
		wantedVel.x -= playerVelocity;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
        m_moveLeftTimerDt = 0.f;
        m_moveRightTimerDt = m_moveTimerMaxTime;
		wantedVel.x += playerVelocity;
	}
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		// This boolean flag makes sure we react to pressing up only once
        if (!m_wasLeafButtonPressed)
        {
            if (GameEngine::GameEngineMain::GetInstance()->GameEngineMain::GetNumberOfSeedsCollected() >= 2)
            {
                // remove 2 seeds from inventory
                GameEngine::GameEngineMain::GetInstance()->GameEngineMain::Use2SeedsToMakeLeaf();
            }
        }
	}
    else
    {
        m_wasLeafButtonPressed = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		// This boolean flag makes sure we react to pressing up only once
        if (!m_wasHeartButtonPressed)
        {
            if (GameEngine::GameEngineMain::GetInstance()->GameEngineMain::GetNumberOfLeafsCollected() >= 2)
            {
                // remove 2 leafs from inventory
                GameEngine::GameEngineMain::GetInstance()->GameEngineMain::Use2LeafsToMakeHeart();
            }
        }
	}
    else
    {
        m_wasHeartButtonPressed = false;
    }

    if (m_animComponent)
	{
		if (m_moveLeftTimerDt > 0.f)
		{
			if (m_animComponent->GetCurrentAnimation() != GameEngine::EAnimationId::MonkeyMoveLeft)
			{
                m_animComponent->PlayAnim(GameEngine::EAnimationId::MonkeyMoveLeft);
			}
		}
        else if (m_moveRightTimerDt > 0.f)
        {
		    if (m_animComponent->GetCurrentAnimation() != GameEngine::EAnimationId::MonkeyMoveRight)
		    {
			    m_animComponent->PlayAnim(GameEngine::EAnimationId::MonkeyMoveRight);
		    }
        }
	}
    
    GameEngine::PawnPhysicsComponent* pawnPhys = GetEntity()->GetComponent<GameEngine::PawnPhysicsComponent>();
    if (pawnPhys)
    {
        pawnPhys->SetVelocity(wantedVel);
    }

    // update the entity with the new velocity
    GetEntity()->SetPos(GetEntity()->GetPos() + wantedVel);
}
