#include "KillerPlantMovementComponent.h"
#include "GameEngine/GameEngineMain.h"

#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"

#include <SFML/Window/Keyboard.hpp>

using namespace Game;

KillerPlantMovementComponent::KillerPlantMovementComponent()
{

}

KillerPlantMovementComponent::~KillerPlantMovementComponent()
{

}

void KillerPlantMovementComponent::OnAddToWorld()
{
    Component::OnAddToWorld();
}

void KillerPlantMovementComponent::Update()
{
    Component::Update();

    // Animation
    GameEngine::AnimationComponent* animComponent = GetEntity()->GetComponent<GameEngine::AnimationComponent>();
    if (animComponent)
    {
        //animComponent->PlayAnim(GameEngine::EAnimationId::KillerPlantMove);
    }
}
