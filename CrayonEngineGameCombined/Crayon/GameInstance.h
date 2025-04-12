//This includes the window, renderer, audio player, and ECS registry.
//Ties together everything that needs to endure for the whole duration of a play session

#pragma once

#include<memory>

#include"WindowAndInput/Window.h"
#include"Renderer.h"
#include"Audio/AudioPlayer.h"
#include"Timing/Timer.h"
#include"ECS.h"
#include"Event.h"
#include"WindowAndInput/InputManager.h"
#include"GUI/GUIManager.h"
#include"ReflectionSystem.h"
#include"Editor/Editor.h"

namespace Crayon
{
	//Not a singleton (not globally available) but you are limited to making one instance because we don't want multiple AudioPlayers etc. washing around.
	class GameInstance
	{
	private:

		InputManager m_inputManager;
		std::shared_ptr<Window> m_window;
		std::shared_ptr<Renderer> m_renderer;
		std::shared_ptr<AudioPlayer> m_audioPlayer;
		std::shared_ptr<Registry> m_registry;
		//used optionals here because the initialization logic is a bit complex and you can't have multiple copies of these (so you can't reassign etc. if you don't set these up in the intializer list)
		std::optional<GUIManager> m_guiManager;
		std::optional<Editor> m_editor;

		std::unordered_map<std::string, std::string> m_editorSettings;

		double m_totalPlayTime = 0.f;

		inline static bool s_instanceExists = false;

		bool m_doBatchSpriteTest = false;


	public:
		GameInstance() = default;
		GameInstance& operator=( const GameInstance& ) = delete;
		GameInstance( const GameInstance& ) = delete;
		virtual ~GameInstance();

		void loadDefaultScene();

		void loadEditorSettings();

		void init();

		//To do: remove! hack for sprite drawing stress test
		std::vector<Sprite> makeSpriteGrid( uint32_t startX, uint32_t startY, uint32_t endX, uint32_t endY, uint32_t columns, uint32_t rows, size_t textureId );
		std::vector<Sprite> m_sprites;

		void updateRegistryAndSystems( double deltaTime );

		void draw( double deltaTime );

		void startGameLoop();

		Renderer& getRenderer();

		uint32_t getTextureIndex( const char* textureName );

		AudioPlayer& getAudioPlayer();
	};
}
