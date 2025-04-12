#pragma once
#include<cstddef>
#include<typeinfo>
#include<map>
#include<yaml-cpp/yaml.h>
#include"Core.h"

namespace Crayon
{

	using DisplayFunc = void(*)(void*);
	using SerializeFunc = void(*)(void*, const char*);
	using BuildFunc = size_t( * )(size_t entityID);
	using DeserializeFunc = void(*)(void*, const char*, const YAML::Node&);
	/*How reflection works in Crayon : (31 / 10 / 2024)

		You're the Editor class. Let's say you want to serialize out an Entity and all of its components.

		You get the entity id, and then you get its ComponentSignature.For each component, you go to the Pool, which gives you a static ReflectedTypeInfo for that component type.

		The ReflectedTypeInfo combines a bunch of function pointers that tell you how to serialize, deserialize, display etc.that type, and a vector of Properties. Properties are also a collection of the same function pointers, but these are specific to that actual variable, rather than the type of the variable. So, a ReflectedTypeInfo<Foo> tells you how to display a Foo, and a Property<Foo> tells you how to display this specific Foo member variable.

		We need to be able to loop through all of our ReflectedTypeInfos, so when a ReflectedTypeInfo<T> is constructed it adds itself to a map, with the name of T as the key.

		The REGISTER_CLASS macro defines a function that adds the right function pointers to the ReflectedTypeInfo for that class.

		FINISH_REGISTRATION creates a static dummy variable that's initialized using that function, which ensures that it's called during the static initialization phase.

		------------------------ -
		
		*/


	class ReflectedTypeInfoBase
	{

	protected:
		using TypeInfoMap = std::map<std::string, ReflectedTypeInfoBase*>;
		inline static TypeInfoMap s_typeMap;

	
	public:
		static TypeInfoMap& getTypeMap()
		{
			return s_typeMap;
		}

		static void addTypeToMap( ReflectedTypeInfoBase& reflectedTypeInfoBase )
		{
			if ( !s_typeMap.contains( reflectedTypeInfoBase.m_typeName ) )
			{
				s_typeMap[reflectedTypeInfoBase.m_typeName] = &reflectedTypeInfoBase;
			}
		}

		DisplayFunc m_displayFunc = nullptr;
		SerializeFunc m_serializeFunc = nullptr;
		BuildFunc m_buildFunc = nullptr;
		DeserializeFunc m_deserializeFunc = nullptr;;

		const char* m_typeName = "Unnamed";
		size_t m_typeIndex = Core::InvalidSize;
	};




	//has a lot in commont with TypeInfo. However, this is the reflection info. for a specific member variable, rather than the type of that variable as a whole: this lets us add code that's specific to a certain variable. We can also have a Property for a variable that isn't an actual reflected type, like an int.

	class Property
	{
	public:
		const size_t m_offset;
		const char* m_name;

		DisplayFunc m_displayFunc;
		SerializeFunc m_serializeFunc;
		DeserializeFunc m_deserializeFunc;

		Property( size_t offset, const char* name, DisplayFunc displayFunc, SerializeFunc serializeFunc, DeserializeFunc deserializeFunc= nullptr):
			m_offset( offset ), m_name( name ), m_displayFunc(displayFunc), m_serializeFunc(serializeFunc), m_deserializeFunc(deserializeFunc) {}


	};


	//our FINISH_REGISTRATION macro then goes struct is_reflected<TypeWe'reRegistering>: std::true_type{}; (so, we use template specialization to say 'But if it's is_reflected<BarOrWhatever> then have it instead be a true_type).
	//This coding pattern is called a 'trait'
	template<typename T>
	struct is_reflected: std::false_type{};

	//container checks:
	//declval: return what WOULD be returned if you did run some code (but doesn't run the code)
	//decltype: gives you the type of whatever follows it.
	//value_type: when you define a container class, there's a bunch of stuff like this that you should do: using value_type = T; etc.


	//let's say we go: is_container<int>. The compiler sees this base template, with its default 'void' second parameter, and creates a template instance of: is_container<int, void>.
	//is_container<int,void> matches the parameters of our template specialization, which tirggers std::void_t to evaluate the types we hand it. If they're valid, the specialization will be used, in they're not, this template will fail and we'll fall back on the base template.
	template<typename T, typename = void>
	struct is_container : std::false_type{};

	template<typename T>
	struct is_container
		<
			T, 
			std::void_t<typename T::value_type,typename T::size_type,typename T::iterator ,decltype(std::declval<T>().begin()), decltype(std::declval<T>().end()), decltype(std::declval<T>().size())
		>
		>:std::true_type{};

	template<typename T>
	T& getFromOffset(void* pOwningObject, size_t offset)
	{
		char* object = reinterpret_cast<char*>(pOwningObject) + offset;
		return reinterpret_cast<T&>(*object);
	}

	template <typename ComponentType>
	class ReflectedTypeInfo: public ReflectedTypeInfoBase
	{
	private:
		std::vector<Property> m_properties;

	public:

		static void registerWithMap( const char* name )
		{
			if ( !s_typeMap.contains( get().m_typeName ) )
			{
				get().m_typeName = name;
				s_typeMap[get().m_typeName] = &get();
			}
		}

		static ReflectedTypeInfo<ComponentType>& get()
		{
			static ReflectedTypeInfo<ComponentType> s_reflectedTypeInfo;
			return s_reflectedTypeInfo;
		}

		static void addProperty( size_t offset, const char* name, DisplayFunc displayFunc, SerializeFunc serializeFunc, DeserializeFunc deserializeFunc )
		{
			ReflectedTypeInfo<ComponentType>::get().m_properties.emplace_back( offset, name, displayFunc, serializeFunc, deserializeFunc);
		}

		static std::vector<Property>& getProperties()
		{
			return ReflectedTypeInfo<ComponentType>::get().m_properties;
		}

		static void setDisplayFunc( DisplayFunc displayFunc )
		{
			ReflectedTypeInfo<ComponentType>::get().m_displayFunc = displayFunc;
		}

		static void setTypeIndex(size_t index)
		{
			ReflectedTypeInfo<ComponentType>::get().m_typeIndex = index;
		}

		static void setBuildFunc( BuildFunc buildFunc )
		{
			ReflectedTypeInfo<ComponentType>::get().m_buildFunc = buildFunc;
		}

		static BuildFunc getBuildFunc()
		{
			return ReflectedTypeInfo<ComponentType>::get().m_buildFunc;
		}

		static void setSerializeFunc( SerializeFunc serializeFunc )
		{
			ReflectedTypeInfo<ComponentType>::get().m_serializeFunc = serializeFunc;
		}

		static void setDeserializeFunc( DeserializeFunc deserializeFunc )
		{
			ReflectedTypeInfo<ComponentType>::get().m_deserializeFunc = deserializeFunc;
		}

		static DisplayFunc getDisplayFunc()
		{
			return ReflectedTypeInfo<ComponentType>::get().m_displayFunc;
		}

		static void setTypeName( const char* typeName )
		{
			ReflectedTypeInfo<ComponentType>::get().m_typeName = typeName;
		}

		static const char* getTypeName()
		{
			return ReflectedTypeInfo<ComponentType>::get().m_typeName;
		}

	};


	
	

}
