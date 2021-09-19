#pragma once
#include "GameEngine/EntitySystem/Component.h"
#include "GameEngine/EntitySystem/Components/AnimationComponent.h"

namespace Game
{
    class PlayerMovementComponent : public GameEngine::Component
    {
    public:
        PlayerMovementComponent();
        ~PlayerMovementComponent();

        virtual void Update() override;
        virtual void OnAddToWorld() override;
    private:
        bool m_wasJumpButtonPressed;
        bool m_wasLeafButtonPressed;
        bool m_wasHeartButtonPressed;
        float m_moveLeftTimerDt;
        float m_moveRightTimerDt;
        float m_moveTimerMaxTime;
        GameEngine::AnimationComponent* m_animComponent;
    };
}