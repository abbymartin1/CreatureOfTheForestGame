//#pragma once
#include "GameEngine/EntitySystem/Component.h"

namespace Game
{
    class KillerPlantMovementComponent : public GameEngine::Component
    {
    public:
        KillerPlantMovementComponent();
        ~KillerPlantMovementComponent();

        virtual void Update() override;
        virtual void OnAddToWorld() override;
    };
}