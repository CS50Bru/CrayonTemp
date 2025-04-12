#include "ECS.h"
#include "Logger.h"

size_t ComponentIdentifierBase::nextId = 0;


Entity::Entity( size_t id ):
	m_id(id){}

size_t Entity::getId() const
{
	return m_id;
}

Entity& Entity::operator=( const Entity& other )
{
	Crayon::Logger::get().log( "Entity assignment is happening" );
	m_id = other.getId();
	return *this;
}

bool Entity::operator==( const Entity& other ) const
{
	return m_id == other.getId();
}

bool Entity::operator!=( const Entity& other ) const
{
	return m_id != other.getId();
}

bool Entity::operator<( const Entity& other ) const
{
	return m_id < other.getId();
}

bool Entity::operator>( const Entity& other ) const
{
	return m_id>other.getId();
}

bool Entity::operator<=( const Entity& other ) const
{
	return m_id<=other.getId();
}

bool Entity::operator>=( const Entity& other ) const
{
	return m_id>=other.getId();
}

void Entity::kill()
{
	Registry::getRegistry().queueEntityForKill(*this);
}


void System::addEntityToSystem(Entity entity)
{
	m_entityIds.addCopy( entity.getId(), Entity(entity) );
}

void System::onEntityAdded( Entity entity )
{
}

void System::onEntityRemoved( Entity entity )
{
}

//we need to change this so that entities are only removed if they are present in the system
void System::removeEntityFromSystem( Entity entity )
{

	if ( !m_entityIds.contains( entity.getId() ) )
	{
		return;
	}
	
	m_entityIds.remove( entity.getId() );
	onEntityRemoved( entity );
}



Crayon::SparseSet<size_t>& System::getSystemEntities()
{
	return m_entityIds;
}

const Signature& System::getComponentSignature() const
{
	return m_componentSignagure;
}

//if we have a usable entity ID, then use that.
Entity Registry::queueEntityForCreation()
{
	size_t entityId = 0;
	if ( !m_freedEntityIDs.empty() )
	{
		entityId = m_freedEntityIDs.front();
		m_freedEntityIDs.pop_front();
	}
	else
	{
		entityId = m_entityCount++;
	}

	Entity newEntity( entityId );
	m_modifiedEntities.insert( newEntity );
	if ( !m_entityComponentSignatures.contains( newEntity ) )
	{
		m_entityComponentSignatures.addMove(entityId, Signature());
	}
	return newEntity;
}

void Registry::update( double deltaTime )
{
	//add any entities that need to be added
	for ( auto entity : m_modifiedEntities )
	{
		addEntityToAllRelevantSystems( entity );
	}
	m_modifiedEntities.clear();

	//NB KEEP THIS ORDER: if, for some reason, an entity is going to be created and killed in the same
	//frame, you want to make sure that it has been fully created before it is destroyed
	for ( auto entity : m_entitiesToBeKilled )
	{
		removeEntityFromAllSystems( entity );
		m_entityComponentSignatures.remove( entity.getId() );
		m_freedEntityIDs.push_back( entity.getId() );
	}
	m_entitiesToBeKilled.clear();
}

//for each system: if the entity's component signature has all the necessary set bits, add it to the sytem.

//new version: for each system, add the component if it matches and remove it if it doesnt
void Registry::addEntityToAllRelevantSystems( Entity entity )
{
	auto signature = m_entityComponentSignatures.get( entity );
	CRAYON_ASSERT( signature.has_value() );


	const Signature& entityComponentSignature =  signature.value();

	for ( auto& systemKeyValuePair : m_systemMap )
	{
		const Signature& systemComponentSignature = systemKeyValuePair.second->getComponentSignature();

		//NB you can't just go entityComponentSignature==systemComponentSignature here, because what we want is for
		//the entity to contain at least the bitflags that the sytem wants, but it can also have MORE. 
		if ( (entityComponentSignature & systemComponentSignature) == systemComponentSignature )
		{
			systemKeyValuePair.second->addEntityToSystem( entity );
		}
		else
		{
			systemKeyValuePair.second->removeEntityFromSystem( entity );
		}
	}
}

void Registry::removeEntityFromAllSystems( Entity entity )
{
	auto signature = m_entityComponentSignatures.get( entity );
	CRAYON_ASSERT( signature.has_value() );

	const Signature& entityComponentSignature = signature.value();

	for ( auto& systemKeyValuePair : m_systemMap )
	{
		const Signature& systemComponentSignature = systemKeyValuePair.second->getComponentSignature();

		//NB you can't just go entityComponentSignature==systemComponentSignature here, because what we want is for
		//the entity to contain at least the bitflags that the sytem wants, but it can also have MORE. 
		if ( (entityComponentSignature & systemComponentSignature) == systemComponentSignature )
		{
			systemKeyValuePair.second->removeEntityFromSystem( entity );
		}
	}
}

PoolBase::~PoolBase()
{
}
