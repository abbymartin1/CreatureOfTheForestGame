
#pragma once
#include "GameEngine/EntitySystem/Components/CollidablePhysicsComponent.h"

namespace GameEngine
{
	//This one allows for movement and obstacle detection, 
	class PhysicsComponentBlock : public CollidablePhysicsComponent
	{
	public:
        PhysicsComponentBlock();
		~PhysicsComponentBlock();

		virtual void OnAddToWorld() override;
        virtual void OnRemoveFromWorld() override;
		virtual void Update() override;

        void SetVelocity(sf::Vector2f vel) { m_wantedVelocity = vel; }

    private:
        float Lerp(float a, float b, float f);
        // Velocity that the pawn wants to have
        sf::Vector2f m_wantedVelocity;
        // Current Pawn Velocity
        sf::Vector2f m_velocity;
        // Position of the pawn in the last frame
        sf::Vector2f m_lastPos;
	};
}
