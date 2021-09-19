#pragma once
#include <vector>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

namespace GameEngine
{
	//TODO - if needed, move out of Engine part to some sort of loader on the game side of things
	namespace eTexture
	{
		enum type
		{
			None = -1,
			Player = 0,
			BG,
			KillerPlant,
			Platform, 
			JunglePlatform,
			JunglePlatform2,
			Seed,
			Leaf,
			Heart,
			Count,
		};
	}	

	inline const char* GetPath(eTexture::type texture)
	{
		switch (texture)
		{
		case eTexture::Player:    return "monkey_runs.png";
		case eTexture::BG:		  return "bg2.png";
		case eTexture::KillerPlant: return "killer_plants.png";
		case eTexture::JunglePlatform: return "jungle_platform.png";
		case eTexture::JunglePlatform2: return "jungle_platform_2.png";
		case eTexture::Platform: return "platform.png";
		case eTexture::Seed: return "seed_block.png";
		case eTexture::Leaf: return "leaf_block.png";
		case eTexture::Heart: return "heart.png";
		default:       return "UnknownTexType";
		}
	}

	class TextureManager
	{
	public:
		static TextureManager* GetInstance() { if (!sm_instance) sm_instance = new TextureManager(); return sm_instance; }
		~TextureManager();

		void LoadTextures();
		void UnLoadTextures();

		sf::Texture* GetTexture(eTexture::type texture) const { return m_textures[(int)texture]; }

	private:
		TextureManager();
		static TextureManager* sm_instance;

		sf::Texture* m_textures[eTexture::Count];
	};
}

namespace TextureHelper
{
	sf::Vector2f GetTextureTileSize(GameEngine::eTexture::type texture);
}

