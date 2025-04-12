#pragma once

#include<vector>
#include<array>

#include"ECS.h"
#include"SpriteComponent.h"
#include"TransformComponent.h"
#include"Sprite.h"

// takes the TransformComponent and SpritableType of each of its Entities and creates a vector of Sprites that
//can then be fed into the Renderer proper.

//a SpritableType is anything that can give you a texture index, drawIndex (layer index) and a uvRect specifying what part of the texture to use

namespace Crayon
{

	template< typename SpritableType>
	class RendererSystem : public System
	{
	private:
		static inline constexpr size_t numberOfLayers = 5;

		std::vector<Sprite> m_sprites;
		std::array<size_t, numberOfLayers> m_layerPopulations;


	public:
		RendererSystem() : m_sprites(), m_layerPopulations()
		{
			requireComponent<TransformComponent>();
			requireComponent<SpritableType>();
		}

		RendererSystem( RendererSystem& other ) = delete;
		RendererSystem operator=( RendererSystem& other ) = delete;



		std::vector<Sprite>& generateSprites()
		{
			m_sprites.clear();
			m_sprites.resize( m_entityIds.size() );
			
		//we already know the number of Sprites we've got in each layer: the 'layer populations' (we keep track of this using the onEntityAdded and onEntityRemoved functions)

		//so we can work out from that our 'layer placement positions': where in our big vector of Sprites we should add in our Sprites for a given layer.
		//So, if we have 3 things in layer 0 and 1 thing in layer 1, our layerPlacementPosition for layer 2 will be 4.
			
			std::array<size_t, numberOfLayers> layerPlacementPositions{};

			for ( size_t i = 0; i < layerPlacementPositions.size(); i++ )
			{
				int lowerLayersPopulationSum = 0;
				for ( size_t j = 0; j < i; j++ )
				{
					lowerLayersPopulationSum += static_cast<int>(m_layerPopulations[j]);
				}
				layerPlacementPositions[i] = lowerLayersPopulationSum;
			}


			//we create Sprites out of Transform and SpritableType components.
			//We add Sprites in at their layer placement positions, which we then increment.
			for ( Entity entity : m_entityIds )
			{
				const TransformComponent& transform = entity.getComponent<TransformComponent>();
				const SpritableType& spriteInfo = entity.getComponent<SpritableType>();

				size_t placementPosition = layerPlacementPositions[spriteInfo.drawIndex]++;

				m_sprites[placementPosition] = Sprite( transform.location, transform.rotation, transform.scale, spriteInfo.textureIndex, spriteInfo.uvRect );
			}

			return m_sprites;
			
		}

		void onEntityAdded( Entity entity ) override
		{
			size_t layerNumber = entity.getComponent<SpritableType>().drawIndex;
			CRAYON_ASSERT(layerNumber < m_layerPopulations.size());
			m_layerPopulations[layerNumber]++;
		}
		
		
		void onEntityRemoved( Entity entity ) override
		{
			size_t layerNumber = entity.getComponent<SpritableType>().drawIndex;
			CRAYON_ASSERT( layerNumber < m_layerPopulations.size() );
			m_layerPopulations[layerNumber]--;
		}

	};

}
