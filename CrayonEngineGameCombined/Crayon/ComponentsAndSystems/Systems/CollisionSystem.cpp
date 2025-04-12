#include "CollisionSystem.h"
#include"Logger.h"
#include"Game/Enums/CollisionType.h"


namespace Crayon
{
	struct RectWithId
	{
		RectWithId(const Rect& inRect, const size_t& inId, CollisionType inType): rect(inRect), id(inId), collisionType(inType) {}
		Rect rect = {};
		size_t id = Core::InvalidSize;
		CollisionType collisionType;
	};




	void Crayon::CollisionSystem::update( double deltaTime )
	{

		auto generateRectWithIdHelper = []( size_t entityIndex )->RectWithId
		{
			Registry& registry = Registry::getRegistry();
			const BoxCollider& boxCollider = registry.getComponentFromEntity<BoxCollider>( entityIndex );
			const TransformComponent& transform = registry.getComponentFromEntity<TransformComponent>( entityIndex );

			const RectWithId rectWithId( Rect( boxCollider.offset + transform.location, boxCollider.extent * transform.scale ), entityIndex, boxCollider.collisionType );

			return rectWithId;
		};

		const auto& entityIdVector = m_entityIds.getPackedContainer();

		for ( size_t i = 0; i < entityIdVector.size(); i++ )
		{
			RectWithId rectA = generateRectWithIdHelper( entityIdVector[i].object );
			for ( size_t j = i + 1; j < entityIdVector.size(); j++ )
			{
				RectWithId rectB = generateRectWithIdHelper( entityIdVector[j].object );

				if ( rectA.rect.getMaxXRaw() >= rectB.rect.getMinXRaw()
												&& rectA.rect.getMinXRaw() <= rectB.rect.getMaxXRaw()
												&& rectA.rect.getMaxYRaw() >= rectB.rect.getMinYRaw()
												&& rectA.rect.getMinYRaw() <= rectB.rect.getMaxYRaw())
				{
					m_collisionEvents.push_back( CollisionEvent(rectA.id, rectB.id, rectA.collisionType, rectB.collisionType ) );
				}

			}

		}
	}

	void Crayon::CollisionSystem::generateCollisionRects()
	{
	}

	void Crayon::CollisionSystem::processCollisionEvents()
	{
		m_projectileHitEvents.clear();
		for ( auto& collisionEvent : m_collisionEvents )
		{
			if ( collisionEvent.collisionTypeA == CollisionType::Projectile )
			{
				m_projectileHitEvents.emplace_back(collisionEvent.a, collisionEvent.b );
			}
			if ( collisionEvent.collisionTypeA == CollisionType::Projectile )
			{
				m_projectileHitEvents.emplace_back( collisionEvent.b, collisionEvent.a );
			}
		}
	}

	void CollisionSystem::clearCollisionEvents()
	{
		m_collisionEvents.clear();
	}


	const std::vector<Rect>& CollisionSystem::getRects() const
	{
		return m_colliderRects;
	}
}