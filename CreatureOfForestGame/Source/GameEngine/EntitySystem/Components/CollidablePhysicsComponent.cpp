#include "CollidablePhysicsComponent.h"
#include "GameEngine/GameEngineMain.h"

#include "GameEngine/Util/CollisionManager.h"
#include "GameEngine/EntitySystem/Entity.h"

#include <vector>

using namespace GameEngine;

CollidablePhysicsComponent::CollidablePhysicsComponent()
	: m_numOfSeedsInCollision(0)
	, m_numOfLeavesInCollision(0)
	, m_numOfHeartsInCollision(0)
{

}

CollidablePhysicsComponent::~CollidablePhysicsComponent()
{

}


void CollidablePhysicsComponent::OnAddToWorld()
{
	CollidableComponent::OnAddToWorld();
}


void CollidablePhysicsComponent::OnRemoveFromWorld()
{
	CollidableComponent::OnRemoveFromWorld();
}


void CollidablePhysicsComponent::Update()
{
	//For the time being just a simple intersection check that moves the entity out of all potential intersect boxes
	std::vector<CollidableComponent*>& collidables = CollisionManager::GetInstance()->GetCollidables();

	for (int a = 0; a < collidables.size(); ++a)
	{
		CollidableComponent* colComponent = collidables[a];
		if (colComponent == this)
			continue;

		AABBRect intersection;
		AABBRect myBox = GetWorldAABB();
		AABBRect colideBox = colComponent->GetWorldAABB();
		if (myBox.intersects(colideBox, intersection))
		{
			sf::Vector2f pos = GetEntity()->GetPos();
			if (intersection.width < intersection.height)
			{
				if (myBox.left < colideBox.left)
					pos.x -= intersection.width;
				else
					pos.x += intersection.width;
			}
			else
			{
				if (myBox.top < colideBox.top)
					pos.y -= intersection.height;
				else
					pos.y += intersection.height;
			}

			GetEntity()->SetPos(pos);
			DidCollideWithEntity(colComponent);
		}
	}
	// reset values
	m_numOfSeedsInCollision = 0;
	m_numOfLeavesInCollision = 0;
	m_numOfHeartsInCollision = 0;
}

void CollidablePhysicsComponent::DidCollideWithEntity(CollidableComponent* collidable)
{
	// we want to see which components collided together to determine if we make something new. 
	// 2 seed blocks = 1 leaf block 
	// 2 leaf blocks = 1 heart 
	// 1 heart -> helps to save the orangutangs habitat
	std::string entityTag = collidable->GetEntity()->GetEntityTag();
	if (entityTag == "seed")
	{
		m_numOfSeedsInCollision++;
	} 
	else if (entityTag == "leaf")
	{
		m_numOfLeavesInCollision++;
	} 
	else if (entityTag == "heart")
	{
		m_numOfHeartsInCollision++;
	}

	if (m_numOfSeedsInCollision > 0)
	{
		GameEngine::GameEngineMain::GetInstance()->GameEngineMain::AddAnotherSeedCollected();
		// "destroy" the seeds 
		collidable->GetEntity()->SetPos(sf::Vector2f(1000.f, 1000.f));
	}
	if (m_numOfLeavesInCollision > 0)
	{
		GameEngine::GameEngineMain::GetInstance()->GameEngineMain::AddAnotherLeafCollected();
		// "destroy" the leaf
		collidable->GetEntity()->SetPos(sf::Vector2f(1000.f, 1000.f));
	}
	if (m_numOfHeartsInCollision > 0)
	{
		// "destroy" the heart
		collidable->GetEntity()->SetPos(sf::Vector2f(1000.f, 1000.f));
		
		// Restart the count down (back to 60 sec)
		GameEngine::GameEngineMain::GetInstance()->GameEngineMain::RestartGameClock();
	}
}