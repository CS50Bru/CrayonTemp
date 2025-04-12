#pragma once
#include<array>
#include<memory>
#include<vector>
#include<limits>
#include<algorithm>
#include"Core.h"

//to do: these only grow atm! Have got to do checks so that unused pages are deallocated etc.

//This class is a good way of having a sparse array, without allocating a huge amount of memory to an almost-empty array with a single element right at the end of it.

//It's made to be used as part of a SparseSet in an ECS, hence the need for an InavlidValue.

//You split the array into cache-friendly "Pages". At the moment, even the number of these pages isn't fixed, which means we're dealing with 2 layers of indirection: we have a vector of page pointers, so we're making 2 jumps across the heap.
//It might be better to have a fixed number of page pointers, but I'm not currently sure.
namespace Crayon
{
	//With the second parameter, I guess that this is a way of making sure that we've declared an InvalidSize for that type. We need that in the case that we're storing Entity IDs, which we don't want to just be 0 or garbage when not initialized. We could make this class more flexible by having it default to using a default parameter when no InvalidValue is declared. Actually, yeah, instead of InvalidValue we sh"ould rename it DefaultValue. And we shold get rid of the "=static_cast<T>(Core::InvalidSize)", too.
	template<typename T, T InvalidValue=static_cast<T>(Core::InvalidSize)>
	class PagedArray
	{
	private:

		//set this to a cache-friendly size
		static constexpr size_t pageSizeInBytes = 4096;
		static constexpr size_t elementsPerPage = pageSizeInBytes / sizeof( T );
		using Page = std::array<T, elementsPerPage>;


		std::vector<std::unique_ptr<Page>> m_pagePointers;

		//get page index
		size_t getPage( size_t index ) const
		{
			return index / elementsPerPage;
		}

		//get element index
		size_t getOffset( size_t index ) const
		{
			return index % elementsPerPage;
		}

	public:

		bool getElementExists( size_t index ) const
		{
			const size_t pageIndex = getPage( index );
			return getPagePointerExists( pageIndex );
		}

		void set( size_t index, const T& newValue )
		{
			forceElementExists( index ) = newValue;
		}

		//LEARN: it's std::reference_wrapper<const T>, not std::reference_wrapper<const T&>! std::reference_wrapper creates a wrapped reference to T: if you give it T&, it'll try to create a reference to a reference

		//to do: what on Earth was I doing here? why was I so desperate to use reference wrappers? this looks like a nightmare, need to redo this and make it simpler
		std::optional<std::reference_wrapper<const T>> get( size_t index ) const
		{
			const size_t pageIndex = getPage( index );
			if ( !getPagePointerExists(  pageIndex ) )
			{
				return std::nullopt;
			}
			const size_t elementOffset = getOffset(index);
			return std::cref( (*m_pagePointers[pageIndex])[elementOffset]);
		}

		std::optional<std::reference_wrapper<T>> get( size_t index )
		{
			const size_t pageIndex = getPage( index );
			if ( !getPagePointerExists( pageIndex ) )
			{
				return std::nullopt;
			}
			const size_t elementOffset = getOffset( index );
			return std::ref( (*m_pagePointers[pageIndex])[elementOffset] );
		}


		//creates a page if necessary and fills all the elements in it with InvalidValue.
		//This is particularly important when we're storing Entity IDs in our PagedArray: we can't have them default to '0', because that's a valid ID.
		T& forceElementExists( size_t index )
		{
			const size_t pageIndex = getPage( index );
			const size_t elementOffset = getOffset( index );
			//check if that element exists
			createPagePointerIfNecessary( pageIndex );
			//if the page is null, then create the page
			if ( !m_pagePointers[pageIndex] )
			{
				m_pagePointers[pageIndex] = std::make_unique<Page>();
				std::fill( m_pagePointers[pageIndex]->begin(), m_pagePointers[pageIndex]->end(), InvalidValue );
			}
			return(*m_pagePointers[pageIndex])[elementOffset];
		}




		void clear()
		{
			m_pagePointers.clear();
		}


	private:
		bool getPagePointerExists( size_t pageNumber ) const
		{
			return pageNumber < m_pagePointers.size();
		}

		std::unique_ptr<Page>& createPagePointerIfNecessary( size_t pageIndex )
		{
			if ( !getPagePointerExists( pageIndex ) )
			{
				m_pagePointers.resize( pageIndex + 1 );
				return m_pagePointers[pageIndex];
			}
			return m_pagePointers[pageIndex];
		}



	};
}