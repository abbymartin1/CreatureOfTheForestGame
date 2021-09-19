#pragma once
#include "GameEngine/EntitySystem/Components/CollidableComponent.h"

namespace GameEngine
{
	//This one allows for movement and obstacle detection, 
	class CollidablePhysicsComponent : public CollidableComponent
	{
	public:
		CollidablePhysicsComponent();
		virtual ~CollidablePhysicsComponent();

		virtual void OnAddToWorld() override;
		virtual void OnRemoveFromWorld() override;

		virtual void Update() override;
	
	private:
		virtual void DidCollideWithEntity(CollidableComponent* collidables);
		int m_numOfSeedsInCollision;
		int m_numOfLeavesInCollision;
		int m_numOfHeartsInCollision;
	};
}

