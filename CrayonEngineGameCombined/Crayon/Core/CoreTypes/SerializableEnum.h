#pragma once
#include<unordered_map>
#include<string>
#include"Core.h"

//to do: I think we can just ditch this: I don't think we ever used it. Just use short char arrays instead and maybe try to do some slightly fancy stuff to make comparisons with those fast
namespace Crayon
{

#define ADD_ENUM_MEMBER(Name) inline static const size_t Name = getIndex(#Name);

	
#define INIT_SERIALIZABLE_ENUM(ClassName)\
	ClassName():SerializableEnum(){}\
	ClassName(const ClassName& other): SerializableEnum(other.getString()){}\
	ClassName( const std::string& name ) : SerializableEnum( name ) {}\
	bool operator==( const ClassName& other ) { return m_index == other.m_index; }\
	bool operator!=( const ClassName& other ) { return m_index != other.m_index; }\
	bool operator==( const size_t otherIndex ) { return m_index == otherIndex; }\
	bool operator!=( const  size_t otherIndex ) { return m_index != otherIndex; }\
	const ClassName& operator=(const ClassName& other){ m_index = other.m_index; return *this; }


	//at runtime, a SerializableEnum is just an index. At the static member level, it has a map that lets you get an id from a string, and another that does the reverse.
	//the YAML strings that you've saved are used to populate those maps when you load a scene.

	//It is fast to compare 2 SerializableEnums, or to plug one into a switch statement.
	class SerializableEnum
	{
	protected:
		inline static std::unordered_map<std::string, size_t> s_stringToId;
		inline static std::unordered_map<size_t, std::string> s_idToString;;
		inline static size_t nextIndex = 0;


		inline static size_t getIndex( const char* nameAsString ) 
		{
			//if we can't find a matching id in the string to id map
			auto it = s_stringToId.find( nameAsString );
			if ( it == s_stringToId.end() )
			{
				s_stringToId[nameAsString] = nextIndex; 
				s_idToString[nextIndex] = nameAsString;
				return nextIndex++; 
			}
			else
			{
				return s_stringToId[nameAsString];
			}
		}

		inline static std::string nameNotFound = "Name not found in idToStringMap";

		inline static const std::string& getName (size_t id)
		{
			auto it = s_idToString.find( id );
			if ( it == s_idToString.end() )
			{
				return nameNotFound;
			}
			return s_idToString[id];
		}

		// per instance
		size_t m_index;

	public:

		SerializableEnum( const std::string& name= "Default") : m_index(getIndex(name.c_str()))
		{}

		bool operator==( const SerializableEnum& other ) { return m_index == other.m_index; }
		bool operator!=( const SerializableEnum& other ) { return m_index != other.m_index; }

		bool operator==( const size_t otherIndex ) { return m_index == otherIndex; }
		bool operator!=( const  size_t otherIndex ) { return m_index != otherIndex; }

		size_t getIndex() const { return m_index; }
		const std::string& getString() const { return getName(m_index); }
		
	};
}