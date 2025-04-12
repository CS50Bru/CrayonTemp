#pragma once

#include<vector>
#include"PagedArray.h"

namespace Crayon
{

	//Purpose: Contains a packed array of objects, and a parallel array of integers holding the indexes of their corresponding
	// objects, allowing for fast lookup within the array.

	//How it works: Let's say we want to find IUpdater 3.
	//We go over to element [3] in the integer array. The integer array is, as such, a sparse array, with the fast lookup that that entails.
	//Element [3] of the integer array contains the packedArrayIndex of IUpdater 3 in the packed array of actual IUpdaters, which could be anything
	//depending on what's been added and removed in that packed array.

	//Benefits: 
	// - Lookup retains the speed of a sparse array
	// - Iteration can just use the packed array
	// - When looking up a specific object, it's very fast to check if it's still present in the set:
	// if element[2] in the integer array no longer points to an IUpdater with an ID of 2, then  IUpdater 2 has been removed.
	// This is really useful for adding or removing objects safely (this last point is actually in some ways the biggest draw of
	// sparse sets and is why they're so useful in things like ECSs which involve a lot of asking "Does this thing have a mesh/light/etc.?)"


	//Costs: a bit elaborate?


	template<typename T>
	class SparseSet
	{
	private:

		struct ObjectWithIndex
		{
			T object;
			size_t entityId;
		};

		std::vector<ObjectWithIndex> m_packedContainer;

		//sparse array of indices
		PagedArray<size_t> m_sparseContainer;





	public:
		SparseSet() :
			 m_packedContainer()
			, m_sparseContainer() {}




		bool addMove(  const size_t entityId, T&& newObject )
		{

			//don't add if there's no room left or if an object at that packedArrayIndex has already been added
			if ( contains( entityId ) )
			{
				return false;
			}

			//add the new element to the end of the active part of the packed array
			m_packedContainer.push_back(ObjectWithIndex(std::move(newObject), entityId));

			//put the entityID used at your entityID holder
			m_sparseContainer.set(entityId, m_packedContainer.size() - 1);

			return true;
		}

		bool addCopy( const size_t entityId, const T& newObject )
		{
			//don't add if there's no room left or if an object at that packedArrayIndex has already been added
			if ( contains( entityId ) )
			{
				return false;
			}

			//add the new element to the end of the active part of the packed array
			m_packedContainer.push_back( ObjectWithIndex(  newObject, entityId ) );

			//put the entityID used at your entityID holder
			m_sparseContainer.set( entityId, m_packedContainer.size() - 1 );

			return true;
		}


		const std::vector<ObjectWithIndex>& getPackedContainer () const
		{
			return m_packedContainer;
		}

		bool remove( const size_t entityID )
		{
			//check that the object is actually there before you try to remove it
			if ( contains( entityID ) )
			{
				// get the packed array index of the object to remove
				size_t objectToRemovePackedArrayIndex = m_sparseContainer.get(entityID).value();

				//if the object you want to remove is already at the back of the packed array, you obviously don't want to swap it with the back etc.
				if ( objectToRemovePackedArrayIndex == m_packedContainer.size() - 1 )
				{
					m_packedContainer.pop_back();
					return true;
				}
				
				//move  last active element into the packedArrayIndex of the element you're removing
				std::swap( m_packedContainer[objectToRemovePackedArrayIndex], m_packedContainer.back() );
				m_packedContainer.pop_back();

				//now we update the sparse container pointer to our moved object so that it points where the deleted object used to be
				const size_t movedObjectId = m_packedContainer[objectToRemovePackedArrayIndex].entityId;

				auto packedArrayIndexHolder = m_sparseContainer.get( movedObjectId );
				if ( packedArrayIndexHolder.has_value() )
				{
					m_sparseContainer.set( movedObjectId, objectToRemovePackedArrayIndex );
					return true;
				}

			}
			return false;
		}


		bool contains(  size_t entityId ) const
		{
			auto indexIntoPackedContainer = m_sparseContainer.get( entityId );
			if (  indexIntoPackedContainer.has_value() )
			{
				if ( indexIntoPackedContainer.value() < m_packedContainer.size() )
				{
					return m_packedContainer[indexIntoPackedContainer.value()].entityId == entityId;
				}
			}
			return false;
		}

		size_t size() const
		{
			return m_packedContainer.size();
		}

		template<typename... TArgs>
		void emplace(size_t index, TArgs&&... args )
		{
			if ( !contains( index ) )
			{
				m_packedContainer.emplace_back(std::forward<TArgs>(args)..., index);
				m_sparseContainer.set(index, m_packedContainer.size() - 1);
			}
			return;
		}




		void set( size_t entityId, const T& newValue )
		{
			if ( !contains( entityId ) )
			{
				addCopy( entityId, newValue );
				return;
			}
			size_t packedContainerIndex = m_sparseContainer.get( entityId ).value();
			m_packedContainer[packedContainerIndex] = ObjectWithIndex(newValue, entityId);
		}




		std::optional<std::reference_wrapper<const T>> get( size_t entityId ) const
		{
			if ( !contains( entityId ) )
			{
				return std::nullopt;
			}
			return std::cref( m_packedContainer[m_sparseContainer.get(entityId).value()].object);
		}

		std::optional<std::reference_wrapper<T>> get( size_t entityId )
		{
			if ( !contains( entityId ) )
			{
				return std::nullopt;
			}
			return std::ref( m_packedContainer[m_sparseContainer.get(entityId).value()].object);
		}


		

		void clear()
		{
			m_sparseContainer.clear();
			m_packedContainer.clear();
		}

		bool empty()
		{
			return m_packedContainer.empty();
		}



		class iterator
		{
		private:
			SparseSet* m_pSparseSet;
			size_t m_index;

		public:
			iterator( SparseSet* inSet, size_t inIndex ):
				m_pSparseSet(inSet)
				,m_index(inIndex){}


			//NB any custom -> operator has to return something else that you can call -> on. Therefore it CANNOT return a reference: it must
			//return either something that implements its own -> operator, or an actual raw pointer.
			//Yes, in the case of an actual raw pointer, it kind of does return a reference: so in Foo* pFoo; pFoo->doSomething(), it's LIKE
			//-> is returning a reference, but it's not that simple: the built-in raw poiner -> operator doesn't actually return anything, 
			//it's a weird, syntactic sugar thing.
			T* operator->() { return &(m_pSparseSet->m_packedContainer[m_index].object); }

			//returns the EntityID (i.e. the index for the SPARSE set)
			size_t getIndex() { return (m_pSparseSet->m_packedContainer[m_index].entityId); }

			T& operator*() { return (m_pSparseSet->m_packedContainer[m_index].object); }

			//this is the pre-increment operator
			iterator& operator++ ()
			{
				++m_index;
				return *this; 
			}

			//this is the post-increment operator. The int is a "dummy argument", and only exists to differentiate this from the
			//pre-increment operator.
			//I hate these names: so by post-increment, we mean it WILL increment, POST this statement (I mean, honestly!)
			//Anyway, the difference here is we won't return this actual iterator: we'll have to make a copy of it in its original state
			//and hand that copy over.
			iterator operator++( int ) 
			{ 
				iterator temp = *this;
				m_index++;
				return temp;
			}

			bool operator==( const iterator& other) const { return m_index == other.m_index; }
			bool operator!=( const iterator& other) const { return m_index != other.m_index; }

		};

		//"iterator" isn't a keyword in C++, but begin() and end() kind of are (having "begin" and "end" is a set pattern, and C++ calls this
		// kind of thing a "protocol": anyway, they're what the C++ compiler looks for when you've got
		//a statement like for (auto thing: things) or whatever, and then the compiler checks that the type returned has these !=, ++ functions
		//etc.
		iterator begin() 
		{ 
			return iterator( this, 0 ); 
		}

		iterator end()
		{
			//NB NOT m_packedArray.size()-1!!!
			return iterator( this, m_packedContainer.size() );
		}


	};
}