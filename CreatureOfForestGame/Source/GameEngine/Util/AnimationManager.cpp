#include "AnimationManager.h"


using namespace GameEngine;

AnimationManager* AnimationManager::sm_instance = nullptr;

AnimationManager::AnimationManager()
{

}


AnimationManager::~AnimationManager()
{

}

void AnimationManager::InitStaticGameAnimations()
{
	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::MonkeyMoveLeft,
			eTexture::Player,
			sf::Vector2i(0, 0),
			4,
			3)
	);

	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::MonkeyPickUpObject,
			eTexture::Player,
			sf::Vector2i(0, 1),
			4,
			3)
	);

	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::KillerPlantMove,
			eTexture::KillerPlant,
			sf::Vector2i(0, 2),
			2,
			3)
	);
}

void AnimationManager::ReleaseStaticGameAnimations()
{
	m_animDefinitions.clear();
}


const SAnimationDefinition* AnimationManager::GetAnimDefinition(EAnimationId::type animId) const
{
	for (int a = 0; a < m_animDefinitions.size(); ++a)
	{
		if (m_animDefinitions[a].m_animId == animId)
			return &m_animDefinitions[a];
	}

	return nullptr;
}
