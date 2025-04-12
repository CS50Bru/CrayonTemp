#pragma once
#include"Game/Enums/CollisionType.h"
namespace Crayon
{
	enum class EventType{Input, Unspecified};
	class Event
	{
	public:
		Event() = default;
		virtual ~Event() = default;
		EventType m_eventType=EventType::Unspecified;
		bool m_handled = false;
	};


	/*class EventCallbackBase
	{
	public:
		EventCallbackBase() {}

		virtual void call( Event& event ) = 0;

		virtual ~EventCallbackBase() = default;
	};

	template<typename TEvent, typename TOwner>
	class EventCallback: public EventCallbackBase
	{
	public:
		using CallbackFunction = void (TOwner::*)(TEvent&);
		EventCallback(TOwner& owner, CallbackFunction callbackFunction ):
			m_owner(owner), m_callbackFunction(callbackFunction){ }

		TOwner& m_owner;

		CallbackFunction m_callbackFunction;

		void call( Event& event ) override
		{
			std::invoke( m_callbackFunction, m_owner, static_cast<TEvent&>( event) );
		}
	};

	class EventBus
	{
	public:
		template<typename TEvent, typename TOwner>
		EventCallback<TEvent, TOwner> createCallback( TOwner& owner, void (TOwner::*callback)(TEvent&) )
		{
			return EventCallback<TEvent, TOwner>( owner, callback );
		}

		template<typename T>
		void typeDeductionTest( T foo )
		{

		}

		using CallbackList = std::list<std::unique_ptr<EventCallbackBase>>;

		std::unordered_map <std::type_index, CallbackList > m_callbackLists;


		template <typename TEvent, typename TOwner>
		void subscribeToEvent(TOwner& owner, void (TOwner::* memberFunction)(TEvent&) )
		{
			using EventCallbackType = EventCallback<TEvent, TOwner>;
			EventCallbackType eventCallback{ owner, memberFunction };
			m_callbackLists[typeid(TEvent)].push_back(std::make_unique<EventCallbackType>(eventCallback) );
		}

		template <typename TEvent, typename ...TArgs>
		void emitEvent( TArgs&& ...args )
		{
			TEvent event =TEvent( std::forward<TArgs>( args )... );
			auto& callbacklist = m_callbackLists[typeid(TEvent)];
			for ( auto it = callbacklist.begin(); it != callbacklist.end(); it++ )
			{
				it->get()->call( event );
			}
		}
	};*/
}