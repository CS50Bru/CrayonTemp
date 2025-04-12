#pragma once

#include<unordered_set>

//The big question here is: to what extent is all of this info 'part of' the gpu resource itself, and should we instead create a 'Resource' class that holds this data (or just straight-up rename our DescriptorSlot class?)

//We need to think about what's information on how you're using the resource in a specific context vs. what's an intrinsic part of the resource.

//For example, perhaps we don't want to bake the 'owning set' into the resource, but the VkDescriptorType feels like something that describes fundamentally what the resource *is*, rather than simply how we're using it at a given point in time: as far as I know, once something's a StorageBuffer, it's a StorageBuffer forever and that's that.
//I think the same goes for the Vma allocation information.

//My current instinct is to just put each descriptor slot in its own set for now, and automatically add everything to the same superset. That would let the user trivially add new resources etc.

//I also think we need to start splitting the Rendering up into different layers of abstraction: pick the really nasty bits of Vulkan (of which descriptor sets etc. are definitely a part) and abstract those away, then do all of the actual 'hey here's how you put together a sprite-drawing pipeline' up in a layer above that: it feels like the former is part of creating a rendering framework where the latter is more part of the engine



namespace Crayon
{
	//This is basically a VkDescriptorSetLayoutBinding, with a bit of extra info on the size of the info being pointed to, + offsets (if used) etc.

	//It's important to keep this info around, because you need to enter this info multiple times during the descriptor set setup process alone, and trying to keep it all synchronized without this is very tricky.

	//You'd have one of these per gpu resource that you're accessing through descriptors: so you'd have one of these to access your camera buffer, and another to access your texture buffer.

	class DescriptorSet;

	struct DescriptorSlot
	{
		DescriptorSlot() = default;
		DescriptorSlot( const DescriptorSlot& ) = delete;
		DescriptorSlot& operator=( const DescriptorSlot& ) = delete;

		DescriptorSet* owningSet= nullptr;

		std::string name="Uninitialized";
		size_t slotIndexWithinSet = 0;
		VkDescriptorType descriptorType{};
		size_t descriptorCount = 0;

		

		bool usesDynamicAligment = false;
		uint32_t baseTypeSize = 0;//only used with dynamic buffers: the size of each 'element'
		size_t dynamicAlignment = 0;//only used with dynamic buffers: the actual alignment of the 'elements'
		size_t currentIndex = 0;
		
		bool isBindless = false;
		VkDescriptorBindingFlags bindingFlags{};
		VkShaderStageFlags stageFlags{};
		bool initialized = false;

	};

	//a CrayDescriptorSet belongs to a CrayDescriptorSuperset: it has an index within that set.
	//at the moment we only have a single, "global" superset that every shader uses, so there's no need to actually store a pointer to the owning superset from within the set.
	class DescriptorSet
	{

		DescriptorSet( const DescriptorSet& ) = delete;
		DescriptorSet& operator=( const DescriptorSet& ) = delete;

	public:
		size_t m_indexWithinSuperset = 0;
		std::unordered_map<std::string, std::shared_ptr<DescriptorSlot>> m_slots;
		DescriptorSet() = default;
		std::string m_name = "Unnamed";
		VkDescriptorSetLayout m_descriptorSetLayout =VK_NULL_HANDLE;
		VkDescriptorSet m_descriptorSet = VK_NULL_HANDLE;


		void addDescriptorSlot( std::shared_ptr<DescriptorSlot> slot )
		{
			CRAYON_ASSERT( !m_slots.contains( slot->name ) );
			if ( !m_slots.contains( slot->name ) )
			{
				slot->slotIndexWithinSet=m_slots.size();
				slot->owningSet = this;
				m_slots.emplace( slot->name, slot );
			}
		}

		DescriptorSlot& getSlot( const std::string& name )
		{
			CRAYON_ASSERT( m_slots.contains( name ) );
			return *m_slots[name];
		}

		size_t getSlotIndex( const std::string& name )
		{
			CRAYON_ASSERT( m_slots.contains( name ) );
			return m_slots[name]->slotIndexWithinSet;
		}

		bool slotWasAdded( const std::string& name )
		{
			return m_slots.contains( name );
		}

	};

	class DescriptorSuperset
	{
		DescriptorSuperset( const DescriptorSuperset&  ) = delete;
		DescriptorSuperset& operator=( const DescriptorSuperset& ) = delete;



	public:
		DescriptorSuperset() = default;

		using DescriptorPointer = std::shared_ptr<DescriptorSet>;
		std::vector<DescriptorPointer> m_sets;
		
		std::unordered_set<std::string> m_setNames;

		
		void addDescriptorSet( std::shared_ptr<DescriptorSet> newSet )
		{
			CRAYON_ASSERT( !m_setNames.contains( newSet->m_name ) );
			if ( !m_setNames.contains( newSet->m_name ) )
			{
				m_setNames.insert( newSet->m_name );
				newSet->m_indexWithinSuperset = m_sets.size();
				m_sets.push_back( newSet );
			}
		}


		bool setWasAdded( const std::string& name )
		{
			return m_setNames.contains( name );
		}

		size_t getDynamicOffsetCount()
		{
			size_t dynamicOffsetCount = 0;
			for ( const auto& set : m_sets )
			{
				for ( const auto& slot :std::views::values( set->m_slots) )
				{
					if ( slot->usesDynamicAligment )
					{
						dynamicOffsetCount++;
					}
				}
			}

			return dynamicOffsetCount;
		}
	};



}
