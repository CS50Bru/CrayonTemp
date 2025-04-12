#pragma once
#include<memory>
#include<yaml-cpp/yaml.h>

//Note on YAMLEmitterWrapper
//you can't reset a YAML::Emitter, which I find baffling, so here's a wrapper class that lets you delete and recreate one.
class YAMLEmitterWrapper
{
	//Note on YAML::Emitter
	//YAML::Emitter is basically like a wrapper around an ostream. It lets you write YAML more easily, without having to worry about manually adding every colon, or keeping track of your current indentation level.

	std::unique_ptr<YAML::Emitter> m_pEmitter;
public:

	YAMLEmitterWrapper() : m_pEmitter( new YAML::Emitter ) {}

	template <typename T>
	YAMLEmitterWrapper& operator<<( const T& value )
	{
		*m_pEmitter << value;
		return *this;
	}

	const char* c_str()
	{
		return m_pEmitter->c_str();
	}

	void reset()
	{
		m_pEmitter = std::make_unique<YAML::Emitter>();
	}
};