#include "TextureManager.h"

using namespace GameEngine;

TextureManager* TextureManager::sm_instance = nullptr;

TextureManager::TextureManager()
{
	for (int a = 0; a < (int)eTexture::Count; ++a)
	{
		m_textures[a] = nullptr;
	}
}


TextureManager::~TextureManager()
{
	UnLoadTextures();
}


void TextureManager::LoadTextures()
{
	for (int a = 0; a < (int)eTexture::Count; ++a)
	{
		sf::Texture* texture = new sf::Texture();
		std::string filePath;
		filePath.append("Resources/img/");
		filePath.append(GetPath((eTexture::type)a));
		texture->loadFromFile(filePath);

		m_textures[a] = texture;
	}
}


void TextureManager::UnLoadTextures()
{
	for (int a = 0; a < (int)eTexture::Count; ++a)
	{
		delete m_textures[a];
		m_textures[a] = nullptr;
	}
}

namespace TextureHelper
{
    sf::Vector2f GetTextureTileSize(GameEngine::eTexture::type texture)
    {
        switch (texture)
        {
        	case  GameEngine::eTexture::Player:  			return sf::Vector2f(710.f, 628.f);
			case  GameEngine::eTexture::BG:	     			return sf::Vector2f(500.f, 500.f);
			case  GameEngine::eTexture::BGGameOver:	     	return sf::Vector2f(500.f, 500.f);
			case GameEngine::eTexture::KillerPlant: 		return sf::Vector2f(1080.f, 1080.f);
			case  GameEngine::eTexture::Platform:  			return sf::Vector2f(81.f, 30.f);
			case  GameEngine::eTexture::JunglePlatform:  	return sf::Vector2f(75.f, 24.f);
			case  GameEngine::eTexture::JunglePlatform2:  	return sf::Vector2f(75.f, 21.f);
			case  GameEngine::eTexture::Seed:	     		return sf::Vector2f(209.f, 209.f);
			case GameEngine::eTexture::Leaf: 				return sf::Vector2f(397.f, 397.f);
			case  GameEngine::eTexture::Heart:  			return sf::Vector2f(1020.f, 886.f);
			default: 										return sf::Vector2f(-1.f, -1.f);
        }
    }
}