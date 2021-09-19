#include "PhysicsComponentBlock.h"

#include "GameEngine/EntitySystem/Entity.h"
#include "GameEngine/GameEngineMain.h"

using namespace GameEngine;

PhysicsComponentBlock::PhysicsComponentBlock()
    : m_wantedVelocity(0.f, 0.f)
    , m_velocity(0.f, 0.f)
    , m_lastPos(0.f, 0.f)
{

}

PhysicsComponentBlock::~PhysicsComponentBlock()
{

}

void PhysicsComponentBlock::OnAddToWorld()
{
    CollidablePhysicsComponent::OnAddToWorld();
}

void PhysicsComponentBlock::OnRemoveFromWorld()
{
	CollidablePhysicsComponent::OnRemoveFromWorld();
}

void PhysicsComponentBlock::Update()
{
    // Get delta time from previous frame
    float dt = GameEngineMain::GetInstance()->GetTimeDelta();

    // log the current Y position before anything happens
    float currentY = GetEntity()->GetPos().y;

    // Acceleration A = DV/ Dt 
    float gForce = 10.f;

    if (dt > 0.f)
    {
        float lerpTime = 5.2f;
        // Set the current velocity of as a lerp of the last one, towards wanted. 
        // Lerp time is multiplied by DT, since we apply the given change in dt, sae as velocity.
        m_velocity.x = Lerp(m_wantedVelocity.x, m_wantedVelocity.x, lerpTime * dt);
        m_velocity.y += m_wantedVelocity.y;

        // Accelerate Y of our velocity by gravity in time
        m_velocity.y += gForce * dt;

        // V = Dx/Dt => Dx = V * Dt
        sf::Vector2f deltaVelocity = dt * m_velocity;
        GetEntity()->SetPos(GetEntity()->GetPos() + deltaVelocity);
    }

    CollidablePhysicsComponent::Update();

    // Determine deltY AFTER the collision update so it indicates the actual distance the entity travelled
    float deltaY = GetEntity()->GetPos().y - currentY;
    if (dt > 0.f)
    {
        // Our actual velocity is that position difference in time
        m_velocity.y = deltaY / dt;
    }
}

float PhysicsComponentBlock::Lerp(float a, float b, float f)
{
    return (a * (1.0f - f)) + (b * f);
}
