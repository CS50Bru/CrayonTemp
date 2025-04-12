#pragma once

#include<bitset>
#include<vector>
#include<unordered_map>
#include<set>
#include<deque>
#include<typeindex>
#include<memory>
#include"ReflectionSystem.h"

#include"SparseSet.h"
#include"Core.h"
#include"Bitset.h"

//we need to know how many components an entity can have so that we know how long a Signature (a std::bitset where each
//bit represents a flag for that component type) needs to be
constexpr uint32_t MAX_COMPONENTS_PER_ENTITY = 32;

//this tells us how big each Pool needs to be (i.e. how many of a given component type we can have)
constexpr uint32_t MAX_COMPONENTS_PER_POOL = 2000;

//we'll use this to identify what components are involved with something: so, a system will demand a certain
//combination of components
using Signature = Crayon::Bitset<MAX_COMPONENTS_PER_ENTITY>;


//We want every ComponentIdentifier<ComponentType> to have the same id number: this  is the id of the component type, basically.
//So, the first time that ComponentIdentifier<ComponentType>'s static getID() function is called, it looks at its parent class's static
//"nextID" and uses that, storing that value in a local static variable so that it'll never change.

//So if ComponentIdentifier<Transform>::getID() is called first, it will forever more return 0, and then ComponentIdentifier<AI>::getID() will
//return 1 etc.
struct ComponentIdentifierBase
{
protected:
	static size_t nextId;
};

//You may notice that we don't actually then reference ComponentType anywhere in this class template.
//That's because our ComponentIdentifier<ComponentType> doesn't actually wrap around a ComponentType: instead, it's just a basically empty class that
//sits at the side and tells you what its id number is.
template <typename ComponentType>
class ComponentIdentifier : public ComponentIdentifierBase
{

public:
	static size_t getID()
	{
		static size_t id = nextId++;
		return id;
	}

};


//really an entity is just an int that's used as an INDEX into various vectors/arrays in the Registry.
//So, if you want to get a certain kind of component from myEntity, you'll look at the resgistry's pool for that ComponentType
//and go myPool[myEntity.id] etc.

//You could totally not even have an actual Entity class and just use ints, but we've set things up so that you can call removeComponent()
//from the actual Entity rather than always having to go myRegistry.removeComponent(myEntity) etc.
class Entity
{
private:
	
	size_t m_id;
public:
	Entity( size_t id );
	Entity( const Entity& other ) = default;

	operator size_t ()const { return m_id; }

	size_t getId() const;

	Entity& operator= ( const Entity& other );

	bool operator== ( const Entity& other ) const;
	bool operator!= ( const Entity& other ) const;

	bool operator<( const Entity& other ) const;
	bool operator> ( const Entity& other ) const;
	bool operator <= ( const Entity& other ) const;
	bool operator >= ( const Entity& other ) const;

	template<typename ComponentType, typename... CompConstructArgs>
	size_t addComponent( CompConstructArgs&& ...constructArgs );

	template<typename ComponentType>
	void removeComponent();

	template<typename ComponentType>
	bool hasComponent();

	template<typename ComponentType>
	ComponentType& getComponent();

	void kill();
};

//you need this (otherwise pointless) base class because the Pool class is TEMPLATED, so it can't serve as a base class itself.
class PoolBase
{
public:
	using DisplayFunction = Crayon::DisplayFunc;
	virtual ~PoolBase();

	virtual Crayon::ReflectedTypeInfoBase& getTypeInfo() = 0;

	virtual void* getComponentAsVoidPointer( size_t index ) = 0;

	virtual size_t getComponentId() = 0;

	virtual void clear() = 0;

};

template<typename ComponentType>
class Pool: public PoolBase
{
private:
	Crayon::SparseSet<ComponentType> m_components;

public:
	Pool (size_t size=MAX_COMPONENTS_PER_POOL)
	{
	}

	void* getComponentAsVoidPointer( size_t index ) override
	{
		auto component = m_components.get( index );
		CRAYON_ASSERT( component.has_value() );
		return reinterpret_cast<void*> (&component.value().get());
	}

	virtual ~Pool() override = default;

	bool empty() const
	{
		return m_components.empty();
	}

	size_t size() const
	{
		return m_components.size();
	}

	void resize( size_t newSize )
	{
	}

	ComponentType& get( size_t index )
	{
		auto component = m_components.get( index );
		CRAYON_ASSERT( component.has_value() );
		return component.value().get();
	}

	void set( ComponentType&& newComponent, size_t index )
	{
		m_components.set( index, std::forward<ComponentType>( newComponent ) );
	}

	ComponentType& operator[]( size_t index )
	{
		auto component = m_components.get(index);
		CRAYON_ASSERT( component.has_value() );
		return component.value().get();
	}

	Crayon::ReflectedTypeInfoBase& getTypeInfo() override
	{
		return Crayon::ReflectedTypeInfo<ComponentType>::get();
	}

	size_t getComponentId() override
	{
		return ComponentIdentifier<ComponentType>::getID();
	}

	void clear() override
	{
		m_components.clear();
	}

};

//it's tempting to think of a system as 'owning' Entities, but that's not how it works, given that an Entity can be used by multiple
//different systems. Instead, the std::vector<Entity> that the System has is used to get the actual components etc. that belong to 
//a given Entity from the REGISTRY (which keeps the components in a bunch of Pools).
class System
{
protected:
	Signature m_componentSignagure;
	Crayon::SparseSet<size_t> m_entityIds;


public:
	System() = default;
	virtual ~System() = default;

	bool getIsInitialized() const;



	template <typename ComponentType>
	void requireComponent();

	void addEntityToSystem( Entity entity );
	virtual void onEntityAdded( Entity entity );
	virtual void onEntityRemoved( Entity entity );
	void removeEntityFromSystem( Entity entity );

	Crayon::SparseSet<size_t>& getSystemEntities();

	const Signature& getComponentSignature() const;

	virtual void update( double deltaTime ) {};

	void clear()
	{
		m_entityIds.clear();
	}

};

template<typename ComponentType>
void System::requireComponent()
{
	const auto componentId = ComponentIdentifier<ComponentType>::getID();
	m_componentSignagure.set( componentId, true );
}



class Registry
{
private:
	std::size_t m_entityCount = 0;

	inline static Registry* s_pRegistry = nullptr;

	//vector of Component pools
	//each pool contains all of the Components of a certain type
	// The component id tells you which pool to go to, and the entity id tells you which component it is within the
	// pool
	//So: vector[0][2] entity no.2's component of the first type
	//std::vector<PoolBase*> m_componentPoolPointers;
	std::vector<std::shared_ptr<PoolBase>> m_componentPoolPointers;

	//Map of active systems
	std::unordered_map<std::type_index, std::shared_ptr<System> > m_systemMap;


	//vector of entities' component signatures
	//The Signature lets us know which components an entity has.
	//vector index = entity id
	//So, we have one of these per entity, basically, so this is our 'master list' of all the entities in our game
	Crayon::SparseSet<Signature> m_entityComponentSignatures;

	std::set<Entity> m_modifiedEntities;

	std::set<Entity> m_entitiesToBeKilled;

	std::deque<size_t> m_freedEntityIDs;

	//this is a bit different to what I was expecting. Instead of specifiying which systems you want an entity to be added
	//to, you just look at the Entity's component flags and you add it to various systems based on that.
	void addEntityToAllRelevantSystems( Entity entity );

	void removeEntityFromAllSystems( Entity entity );

public:
	Registry() {
		
		static bool registryExists = false;

		if ( !registryExists )
		{
			s_pRegistry = this; 
			registryExists = true;
		}
	
	}
	virtual ~Registry() = default;

	static Registry& getRegistry() { return *s_pRegistry; }


	Entity queueEntityForCreation();

	void queueEntityForKill( Entity entity )
	{
		m_entitiesToBeKilled.insert( entity );
	}
	void update( double deltaTime );

	Crayon::SparseSet<Signature>& getAllSignatures()
	{
		return m_entityComponentSignatures;
	}

	PoolBase& getPool( size_t index )
	{
		return *m_componentPoolPointers[index];
	}

	Signature getComponentSignature( size_t index )
	{
		auto signature = m_entityComponentSignatures.get( index );
		CRAYON_ASSERT( signature.has_value() );
		return signature.value();
	}

	template<typename ComponentType, typename ...ArgPack>
	static void addComponentToEntity( Registry& registry, Entity& entity, ArgPack&& ...argPack )
	{
		registry.addComponentToEntity<ComponentType>( entity, std::forward(argPack)... );
	}

	//"let me create a Component of whatever type, giving that Component as many constructor arguments as it needs"
	template<typename ComponentType, typename ...ArgPack>
	void addComponentToEntity( Entity entity, ArgPack&& ...argPack )
	{
		//get the type of component you're adding
		size_t componentId= ComponentIdentifier<ComponentType>::getID();
		//get the id for the new entity
		size_t entityId = entity.getId();

		//let's say that we're adding a TransformComponent: the index for TransformComponent might be 4, but pools
		//1, 2 and 3 might not actually exist yet: so we can't just "add 1 pool", we have to resize the the vector and add our
		//pool in at the correct index.
		if ( componentId >= m_componentPoolPointers.size() )
		{
			m_componentPoolPointers.resize( componentId + 1, nullptr );
		}

		//if there's no actual pool yet at that index (as in, the block of code above has just run) then create
		//a pool
		if ( !m_componentPoolPointers[componentId] )
		{
			m_componentPoolPointers[componentId] = std::make_shared<Pool<ComponentType>>();
		}

		Pool<ComponentType>* componentPool = static_cast<Pool<ComponentType>*> (m_componentPoolPointers[componentId].get() );


		if ( entityId >= componentPool->size() )
		{
			componentPool->resize( m_entityCount );
		}

		componentPool->set( ComponentType( std::forward<ArgPack>( argPack )... ), entityId );

		auto entitySignature = m_entityComponentSignatures.get( entityId );
		CRAYON_ASSERT( entitySignature.has_value() );
		entitySignature.value().get().set( componentId );
		//m_entityComponentSignatures[entityId].set( componentId );

		m_modifiedEntities.insert( entity );

	}

	bool getEntityAlive( size_t entityID)
	{
		return m_entityComponentSignatures.contains( entityID );
	}


	template<typename T>
	static size_t addComponentFromGivenRegistry( size_t entityID )
	{
		Entity entity( entityID );
		entity.addComponent<T>();
		return ComponentIdentifier<T>::getID();
	}

	//ToDo: uh, this doesn't seem right... don't you also need to remove it from the relevant SYSTEMS? What is this?
	//Do you think we could just add the entity to the modifiedEntities vector?
	template <typename ComponentType>
	void removeComponentFromEntity( Entity entity )

	{
		const size_t componentId = ComponentIdentifier<ComponentType>::getID();
		const size_t entityId = entity.getId();

		m_entityComponentSignatures[entityId].set( componentId, false );
		m_modifiedEntities.insert( entity );
	}

	void removeComponentFromEntity_componentIdVersion( size_t entityId, size_t componentId )
	{
		auto signature = m_entityComponentSignatures.get( entityId );
		CRAYON_ASSERT( signature.has_value() );
		signature.value().get().set( componentId, false );
		//signature.set( componentId, false );
		m_modifiedEntities.insert( Entity(entityId) );
	}

	template <typename ComponentType>
	inline bool entityHasComponent( Entity entity )
	{
		auto signature = m_entityComponentSignatures.get( entity );
		CRAYON_ASSERT( signature.has_value() );
		return signature.value().get().test( ComponentIdentifier<ComponentType>::getID() );
	}

	 bool entityHasComponentByComponentId( size_t entityId, size_t componentId )
	{
		 auto signature = m_entityComponentSignatures.get( entityId );
		 CRAYON_ASSERT( signature.has_value() );
		 return signature.value().get().test( componentId );
	}

	//componentType: TransformComponent
	//ComponentIdentifier<ComponentType>=> ComponentIdentifier<TransformComponent>
	template <typename ComponentType>
	inline ComponentType& getComponentFromEntity( Entity entity )
	{
		const size_t componentId = ComponentIdentifier<ComponentType>::getID();
		const size_t entityId = entity.getId();

		//unique pointer to 
		 PoolBase* poolBase=m_componentPoolPointers[componentId].get();
		 Pool<ComponentType>* castedPool = static_cast<Pool<ComponentType>*> (poolBase);
		 return ( castedPool->get(entityId)  );
	}


	//System management
	template <typename SystemType, typename... ArgPack>
	void addSystem( ArgPack&&... argPack);

	template <typename SystemType>
	void removeSystem();

	template <typename SystemType>
	bool hasSystem() const;

	template <typename SystemType>
	SystemType& getSystem() const;

	void clear()
	{
		m_modifiedEntities.clear();
		m_entitiesToBeKilled.clear();
		m_entityComponentSignatures.clear();
		m_freedEntityIDs.clear();
		m_entityCount = 0;

		//clear component pools
		for ( auto& componentPool : m_componentPoolPointers )
		{
			if ( componentPool )
			{
				componentPool->clear();
			}
		}
		//clear systems
		for ( auto& [_, system] : m_systemMap )
		{
			if ( system )
			{
				system->clear();
			}
		}
	}
};

template<typename SystemType, typename ...ArgPack>
inline void Registry::addSystem( ArgPack && ...argPack )
{
	std::shared_ptr<SystemType> newSystem = std::make_shared<SystemType> ( std::forward<ArgPack>( argPack )... );

	m_systemMap.insert( std::make_pair( std::type_index( typeid(SystemType) ), newSystem));
}

template<typename SystemType>
inline void Registry::removeSystem()
{
	const std::type_index typeIndex( typeid( SystemType ));

	m_systemMap.erase( typeIndex );
}

template<typename SystemType>
inline bool Registry::hasSystem() const
{
	const std::type_index typeIndex( typeid(SystemType) );

	return (m_systemMap.find( typeIndex )!=m_systemMap.end());
}



template<typename SystemType>
inline SystemType& Registry::getSystem() const
{
	const std::type_index typeIndex( typeid(SystemType) );
	return *(static_pointer_cast<SystemType>( m_systemMap.find( typeIndex )->second) );
}


template<typename ComponentType, typename... CompConstructArgs>
inline size_t Entity::addComponent( CompConstructArgs&& ...constructArgs )
{
	Registry::getRegistry().addComponentToEntity<ComponentType>( *this, std::forward<CompConstructArgs>( constructArgs )... );
	return ComponentIdentifier<ComponentType>::getID();
}

template<typename ComponentType>
void Entity::removeComponent()
{
	Registry::getRegistry().removeComponentFromEntity<ComponentType>( *this );
}

template<typename ComponentType>
bool Entity::hasComponent()
{
	return Registry::getRegistry().entityHasComponent<ComponentType>( *this );
}

template<typename ComponentType>
ComponentType& Entity::getComponent()
{
	return	Registry::getRegistry().getComponentFromEntity<ComponentType>( *this );
}
