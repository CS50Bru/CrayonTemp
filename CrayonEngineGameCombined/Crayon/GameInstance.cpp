#include "GameInstance.h"
#include<algorithm>
#include<limits>
#include<filesystem>
#include<iostream>
#include<string>
#include<string_view>

#include"Core.h"
#include"PhysicsSystem.h"
#include"RendererSystem.h"
#include"AudioSystem.h"
#include"AnimationSystem.h"
#include"Audio/AudioPlayer.h"
#include"CollisionSystem.h"
#include"PlayerSystem.h"
#include"InvaderSystem.h"
#include"SoundComponent.h"
#include"Logger.h"
#include"Event.h"
#include"SparseSet.h"
#include"PagedArray.h"
#include"Profiler.h"
#include"DespawnProjectileSystem.h"
#include"UISpriteComponent.h"
#include"Bitset.h"
#include"QuadWithColor.h"
#include"Editor/ShaderManager.h"

namespace Crayon
{


	void GameInstance::init()
	{
		CRAYON_ASSERT( !s_instanceExists );
		s_instanceExists = true;

		//ToDo: add these to the editorSettings.config file... put them anywhere but here
		const std::string vulkanTargetVersion = "vulkan1.3";
		const std::string spvTargetVersion = "spv1.6";

		ShaderManager::compileSpirV( "Shaders", "Shaders/spvFiles", vulkanTargetVersion, spvTargetVersion, false);



		PROFILE_WRAP_START( windowCreation );
		m_window = std::make_unique<Window>();

		loadEditorSettings();

		bool fullScreen = false;
		
		if ( m_editorSettings.contains( "fullscreen" ) )
		{
			fullScreen = m_editorSettings["fullscreen"] == "true";
		}


		m_window->initWindowsWindow( fullScreen );
		
		
		PROFILE_WRAP_END( windowCreation )

		m_renderer = std::make_unique<Renderer>();
		m_renderer->init( m_window->getHandle(), m_window->getScreenExtent(), m_editorSettings );


		size_t spriteCount = 1000000;
		m_sprites.reserve( spriteCount );

		size_t texId= m_renderer->addTextureIfNew( "Textures/ice.png" );

		m_sprites = makeSpriteGrid( 0, 0, 3200, 3200, sqrt( spriteCount ), sqrt( spriteCount ), texId);

		m_renderer->copyViaStagingBuffer( m_sprites, m_renderer->m_spriteBuffer.stagingBuffer, m_renderer->m_spriteBuffer.gpuBuffer );

		m_audioPlayer = std::make_unique<AudioPlayer>();

		m_registry = std::make_unique<Registry>();
		m_registry->addSystem<PhysicsSystem>();
		m_registry->addSystem<RendererSystem<SpriteComponent>>();
		m_registry->addSystem<RendererSystem<UISpriteComponent>>();
		m_registry->addSystem<AudioSystem>();
		m_registry->addSystem<AnimationSystem>();
		m_registry->addSystem<CollisionSystem>();
		m_registry->addSystem<PlayerSystem>();
		m_registry->addSystem<InvaderSystem>();
		m_registry->addSystem<DespawnProjectileSystem>();


		m_guiManager.emplace( m_window.get()->getHandle(), *m_renderer );
		m_editor.emplace( *m_registry, *m_renderer );

		Logger::get().startWriteThread();
	}


	void GameInstance::updateRegistryAndSystems( double deltaTime )
	{
		glm::vec2 cursorScreenPos = m_renderer->getPixelsToNdcs( m_inputManager.getMousePosIntegerVersion());
		glm::vec2 cursorWorldPos = m_renderer.get()->getScreenToWorld( cursorScreenPos );
		

		m_totalPlayTime += deltaTime;
		//updateRegistryAndSystems

		m_registry->update( deltaTime );
		m_registry->getSystem<PhysicsSystem>().updateAndFollowCursor( deltaTime, static_cast<glm::vec2>(cursorWorldPos));
		m_registry->getSystem<AudioSystem>().update( deltaTime );
		m_registry->getSystem<AnimationSystem>().update( deltaTime );
		CollisionSystem& collisionSystem = m_registry->getSystem<CollisionSystem>();
		collisionSystem.clearCollisionEvents();
		collisionSystem.update( deltaTime );
		collisionSystem.processCollisionEvents();
		m_registry->getSystem<PlayerSystem>().updatePlayerMovement( deltaTime, m_inputManager, *m_registry.get(), *m_renderer.get(), *m_audioPlayer.get());
		m_registry->getSystem<InvaderSystem>().updateInvaderMovement( deltaTime, 0.f, m_renderer->getScreenWidth() );
		m_registry->getSystem<DespawnProjectileSystem>().update( deltaTime );
		m_registry->getSystem<DespawnProjectileSystem>().processProjectileCollisionEvents( collisionSystem.getProjectileHitEvents() );

		m_editor->displayFPS( deltaTime, &m_doBatchSpriteTest );

		m_editor->drawScenePanel();
		m_editor->drawInspectorPanel();
		m_editor->drawMainMenuBar();


	}

	void GameInstance::draw( double deltaTime )
	{
		//ProfilerTimer spriteGenTimer( "Sprite Generation" );
		PROFILE_WRAP_START( SpriteGeneration )
			std::vector<Sprite>& spriteVector = m_registry->getSystem<RendererSystem<SpriteComponent>>().generateSprites();
		PROFILE_WRAP_END( SpriteGeneration )


			PROFILE_WRAP_START( UISpriteGeneration )
			std::vector<Sprite> UISpriteVector = m_registry->getSystem<RendererSystem<UISpriteComponent>>().generateSprites();
		PROFILE_WRAP_END( UISpriteGeneration )

			m_renderer->updateCameraPosition();
		{
			PROFILE_SCOPE( StartDraw )
				m_renderer->startDrawFrame();
		}
		//m_renderer->beginRenderPass_main();
		m_renderer->beginRenderpass_main();

		{
			PROFILE_SCOPE( Draw Sprites )
				m_renderer->drawGameSprites( spriteVector );
		}

		if ( m_doBatchSpriteTest )
		{
			uint32_t offset = 0;
			uint32_t spriteCount = m_sprites.size() - offset;
			CRAYON_ASSERT( spriteCount > 0 );
			BufferRange bufferRange{.start=offset, .count =spriteCount};
			std::vector<BufferRange> bufferRangeVector = { bufferRange };

			uint32_t workgroupCount = (spriteCount * 4  - 1) / 256 + 1;


			m_renderer->draw<BufferRange>(m_renderer->m_spriteBatchPipeline, bufferRangeVector, workgroupCount );
		}
		
		{
			PROFILE_SCOPE( Draw Solid Shapes )
		}
		//DEBUG DEBUG DEBUG
		////////////////////////////////////////////////
		{//Debug Drawing

			Rect rect{ glm::vec2( 400.f, 400.f ), glm::vec2( 100.f, 100.f ) };
			std::vector<Rect> rects;
			rects.push_back( rect );

			//m_renderer->drawCircles( circleRects );
			//m_renderer->drawSolidShapes( rects );

		}
		//////////////////////////////////////////////////
		//DEBUG DEBUG DEBUG
		

		GUIManager::sumbitDrawData(m_renderer->getCurrentCommandBuffer());

		m_renderer->endRenderPass();


		m_renderer->beginRenderpass_postprocessing();

		m_renderer->drawColourCorrection();

		m_renderer->endRenderPass();

		m_renderer->endDrawFrame();

	}
	void GameInstance::startGameLoop()
	{
		Timer loopTimer{};
		double timeElapsed = 0.f;

		constexpr uint64_t minPhysicsFPS = 5;
		double maxDeltaTime = 1.0 / static_cast<double>(minPhysicsFPS);

		double deltaTime = 0.0;
		double uncappedDeltaTime = 0.0;

		

		while ( !m_window->getShouldClose() )
		{
			PROFILE_SCOPE( "Whole Loop" );
			{
				Profiler::get().reset();


				//process messages and input
				{
					//deal with timing stuff
					uncappedDeltaTime = loopTimer.getTimeSinceStart<Crayon::Seconds>();
					deltaTime = std::min<double>( uncappedDeltaTime, maxDeltaTime );
					loopTimer.reset();


					timeElapsed += deltaTime;
					{
						//ProfilerTimer windowResizeTimer( "Window resize handling" );
						PROFILE_SCOPE( Window Resize Handling )
							//resize the window if necessary
							if ( m_window->getResized() )
							{
								m_renderer->recreateSwapChainAndUpdateDependencies( m_window->getHandle() );
								m_window->setResized( false );
							}
					}

					//process Window messages, generate input events
					{
						PROFILE_SCOPE( WindowEvent Processing )
						//Get Input
						m_inputManager.resetForNewFrame();
						m_window->processMessages();
						m_inputManager.processInputMessages( m_window->getInputMessages() );
						m_window->clearInputMessages();
						m_inputManager.processIrregularInput();
						m_inputManager.organizeInputEventsIntoVector();
					}

					//hand input events to ImGui
					{
						PROFILE_SCOPE( Gui Event Handling )
						m_guiManager->prepForUpdate();
						m_guiManager->processInputEvents( m_inputManager.getMousePosIntegerVersion(), m_inputManager.getInputEvents() );
						m_guiManager->processChars( m_inputManager.getChars() );
					}
				}

				{
					//updateRegistryAndSystems
					PROFILE_SCOPE( Update )
					updateRegistryAndSystems( deltaTime );
					GUIManager::assembleDrawData();
				}

				{
					//draw
					PROFILE_SCOPE( Draw )
					draw( deltaTime );
				}

			}
			//to do: remove hard-coded keypress value
			if ( m_inputManager.getKeyIsDown( InputName::PrintScreen ) )
			{
				Profiler::get().startFileWriteThread("Results.json");
			}

			Logger::get().triggerWrite();
		}
	}


	Renderer& GameInstance::getRenderer()
	{
		return *(m_renderer.get());
	}


	uint32_t GameInstance::getTextureIndex( const char* textureName )
	{
		return m_renderer->addTextureIfNew( textureName );
	}

	AudioPlayer& GameInstance::getAudioPlayer()
	{
		return *(m_audioPlayer.get());
	}

	void GameInstance::loadDefaultScene()
	{
		std::string sceneFilepath( defaultSceneFilepath );
		Editor::loadScene( sceneFilepath, *m_registry );
	}


	std::vector<Sprite> GameInstance::makeSpriteGrid( uint32_t startX, uint32_t startY, uint32_t endX, uint32_t endY, uint32_t columns, uint32_t rows, size_t textureId )
	{
		std::vector<Sprite>sprites;


		const glm::vec2 startPos = { startX, startY };

		const float rowHeight = (endX - startX) / static_cast<float>(rows);

		const float columnWidth = (endY - startY) / static_cast<float>(columns);

		for ( size_t row = 0; row < rows; row++ )
		{
			for ( size_t column = 0; column < columns; column++ )
			{
				Sprite sprite{};
				glm::vec2 offset = { column * columnWidth, row * rowHeight };
				sprite.position = startPos + offset;
				sprite.textureIndex = textureId;

				sprites.push_back( sprite );
			}
		}

		return sprites;
	}





	//ToDo:
	//I don't love what I've gone here.
	//---------------------------------------------------
	// Pseudocode:
	//open file into ifstream

	//	read from into a string line by line using getLine()

	//	use line.erase( ... ) to get rid of initial whitespace on line, then see if we encounter a //. If so then skip the line.

	//	if we haven't hit a //, then see if we can find a ' = '. If so, then create a string called 'key' and put everything before the ' = ' into it and everything after into another new string called 'value'.

	//		Use.erase() multiple times on key and value to trim whitespace from beginning and end.
	//-----------------------------------------------------

	//I feel like a more manual approach would be nicer: just read the whole file over (we know we want all of it) and move a cursor through it, ignoring whitespaces automatically instead of having to strip them after.

	void GameInstance::loadEditorSettings()
	{
		constexpr std::string_view configFilename = "./.editorconfig";
		namespace fs = std::filesystem;
		CRAYON_ASSERT( fs::exists(configFilename ));

		const fs::path configFilepath( configFilename );

		std::ifstream inStream( configFilepath, std::ios::in );
		
		std::string configFileAsString;

		if ( inStream )
		{
			std::string line;

			//getline accounts for differing line endings automatically
			//" \t" = space or tab
			while ( std::getline( inStream, line ) )
			{
				line.erase( 0, line.find_first_not_of( " \t" ) );
				if ( line.find( "//" ) == 0 )
				{
					continue;
				}
				else
				{
					size_t equalSignPos = line.find( "=" );
					if ( equalSignPos != std::string::npos )
					{
						const auto& stripWhitespaceFromFrontAndBack = []( std::string_view& view )
							{
								view.remove_prefix( view.find_first_not_of( " \t" ) );
								view.remove_suffix( view.size() - (view.find_last_not_of( " \t" ) + 1) );
							};
						//takes in startpos and count, not begin and end
						std::string_view key( line.data(), equalSignPos);
						stripWhitespaceFromFrontAndBack( key );
						std::string_view value( line.data() + equalSignPos + 1, line.size() - 1 - equalSignPos );
						stripWhitespaceFromFrontAndBack( value );
						
						if ( ! (key.empty() || value.empty()) )
						{
							m_editorSettings[std::string (key)] = std::string(value);
						}
					}
				}

			}

		}


	}



	GameInstance::~GameInstance()
	{
		m_guiManager->shutdown(m_renderer->getDevice());
	}

}