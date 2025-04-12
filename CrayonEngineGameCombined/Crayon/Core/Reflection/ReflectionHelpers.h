#pragma once
#include"ReflectionSystem.h"
#include"ECS.h"
#include"Editor/Editor.h"

//. registering types: 
//REGISTER_CLASS defines an initializeClass() function within the class that's to be reflected. This function will add the relevant function pointers to the ReflectedTypeInfo<TypeToBeRegistered>.

//FINISH_REGISTRATION creates a dummy static variable within the class that is initialized using the initializeClass() function.This dummy static variable is guaranteed to be initialized during the static initialization phase, so the ReflectedTypeInfo<T> class is going to have its data filled out during this phase.
//
//.registering properties :
//
//EXPOSE_PROPERTY defines a type whose contsructor adds function pointer info the the matching Property in the relevant ReflectedTypeInfo.
//
//It then declareds an inline, static instance of this type, so that these things will be added during thes static initialization phase.
//
//Because the registration of the type, which sets up the ReflectedTypeInfo, and the registration of the property, which adds info.to that ReflectedTypeInfo, both happen during the static initialization phase in a 'random' order, the property registration also creates a dummy instance of the ReflectedTypeInfo, which triggers all of the static variables for that ReflectedTypeInfo class to be initialized.
namespace Crayon
{

//we create an instance of ReflectedTypeInfo<__CLASS__> so that any static member variables are initialized
#define REGISTER_CLASS(ClassName) using __CLASS__ = ClassName;\
static void initializeClass(){\
ReflectedTypeInfo<__CLASS__>::setDisplayFunc(&Editor::displayFromVoidPointer<__CLASS__>);\
ReflectedTypeInfo<__CLASS__>::setSerializeFunc(&Editor::serializeFromVoidPointer<__CLASS__>);\
ReflectedTypeInfo<__CLASS__>::setBuildFunc(&Registry::addComponentFromGivenRegistry<__CLASS__>);\
ReflectedTypeInfo<__CLASS__>::setDeserializeFunc(&Editor::deserializeFromVoidPointer<__CLASS__>);\
ReflectedTypeInfo<__CLASS__>::registerWithMap(#ClassName);\
ReflectedTypeInfo<__CLASS__>::setTypeIndex(ComponentIdentifier<__CLASS__>::getID()); }



#define CUSTOM_DISPLAY(lambda) customDisplayFunc = static_cast<void(*)(void*)>(lambda);
//A PropertyRestgistrar class is created for each property by the EXPOSE_PROPERTY macro. A static instance of this class is declared, the initialization of which will call the code that we're actually interested in, adding display, serialization and deserialization function (pointers) to the ReflectedTypeInfo class.
//In other words, if you add EXPOSE_PROPERTY to SimpleComponent's 'myInt' property, then a PropertyRegistrar_SimpleComponent_myInt class will be declared and a static instance of it added to SimpleComponent. When intialized, it will call code as part of its constructor such as:
//Crayon::PopertyHolder<SimpleComponent>::addProperty(&Editor::displayFromVoidPointer<int> etc.)
#define PROPERTY_REGISTRAR_NAME(ClassName, PropertyName) PropertyRegistrar_##ClassName##_##PropertyName

#define EXPOSE_PROPERTY( PropertyName, ...) \
			struct PROPERTY_REGISTRAR_NAME(__CLASS__, PropertyName) \
			{ \
				PROPERTY_REGISTRAR_NAME(__CLASS__, PropertyName) () { \
				DisplayFunc customDisplayFunc =nullptr;\
				__VA_ARGS__\
				DisplayFunc displayFunc = customDisplayFunc==nullptr ? &Editor::displayFromVoidPointer<decltype(__CLASS__::PropertyName)>: customDisplayFunc;\
				Crayon::ReflectedTypeInfo<__CLASS__>::addProperty(\
				offsetof(__CLASS__, PropertyName),\
				#PropertyName,\
				displayFunc,\
				&Editor::serializeFromVoidPointer<decltype(__CLASS__::PropertyName)>, \
				&Editor::deserializeFromVoidPointer<decltype(__CLASS__::PropertyName)>);\
			}\
			}; \
			inline static PROPERTY_REGISTRAR_NAME(__CLASS__, PropertyName) PROPERTY_REGISTRAR_NAME(__CLASS__, PropertyName)##_instance;


#define FINISH_REGISTRATION(ClassName) static inline bool __dummy = (initializeClass(), true);\
		}; template<>\
		struct is_reflected<ClassName>: std::true_type{}; namespace{\
		

}