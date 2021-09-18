#include "PlayerMovementComponent.h"

#include "GameEngine/GameEngineMain.h"
#include <SFML/Window/Keyboard.hpp>

using namespace Game;

PlayerMovementComponent::PlayerMovementComponent()
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

    // get amount of time that passed since last update() call 
    float dt = GameEngine::GameEngineMain::GetTimeDelta();

    // by default the wanted velocity is 0
    sf::Vector2f wantedVelocity = sf::Vector2f(0.f, 0.f);

    //player velocity is applied when we have some input (for the time being we will make it 10 pixels/sec)
    float playerVelocity = 100.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        wantedVelocity.x -= playerVelocity * dt;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        wantedVelocity.x += playerVelocity * dt;
    }

    // Update the entity position with the new velocity
    GetEntity()->SetPos(GetEntity()->GetPos() + wantedVelocity);
}