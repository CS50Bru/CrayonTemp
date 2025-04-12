#pragma once
#include"ECS.h"
#include"GUI/GUIManager.h"
#include"Core.h"
#include"Audio/SoundAsset.h"
#include"TextureIdentifier.h"
#include"YAMLHelpers.h"

namespace Crayon
{
	//singleton-adjacent: you can only have 1 of it, but it isn't actually globally available: access to the static instance is private. We only have the static instance so that our injected function pointers in our reflection classes don't have to be those weird method-pointer things.
	class Editor
	{
	private:

		inline static bool s_instanceExists = false;
		inline static Editor* s_pEditor = nullptr;
		
		Registry& m_registry;
		Renderer& m_renderer;
		YAMLEmitterWrapper m_sceneOut;
		size_t m_selectedEntity = Core::InvalidSize;

		double m_timeSinceLastDebugInfoOutput = 0.0;
		const double m_debugInfoOutputFrequency = 1.0;
		double m_currentFrameRate = 0.0;

		static Editor& get() { return *s_pEditor; }

	public:

		Editor( Registry& registry, Renderer& renderer ) : m_registry(registry),m_renderer(renderer)
		{
			CRAYON_ASSERT( !s_instanceExists );
			s_instanceExists = true;
			s_pEditor = this;
		};

		Editor operator=( const Editor& ) = delete;
		Editor( const Editor& ) = delete;

		void drawScenePanel()
		{
			ImGui::SetNextWindowPos( ImVec2( 0, 20) );
			ImGui::SetNextWindowSize( ImVec2( 200, 400 ) );
			ImGui::Begin( "Scene Panel" );

			/////////////////////////////////////
			//draw the add and remove entity buttons
			if ( ImGui::Button( "Add Entity" ) )
			{
				m_registry.queueEntityForCreation();
			}
			ImGui::SameLine();
			if ( ImGui::Button( "Delete Selected Entity" ) )
			{
				if ( m_selectedEntity != Core::InvalidSize )
				{
					m_registry.queueEntityForKill( Entity( m_selectedEntity) );
				}
			}
			///////////////////////////////////

			SparseSet<Signature>& entitySignatures = m_registry.getAllSignatures();
			size_t entityCount = entitySignatures.size();
			ImGui::Text( "Total Entities: %d", entityCount );

			for ( auto it = entitySignatures.begin(); it != entitySignatures.end(); it++ )
			{
				std::string id = std::to_string( it.getIndex() );
				if ( ImGui::Button( id.c_str() ) )
				{
					m_selectedEntity = it.getIndex();
				}
			}
			ImGui::End();
		}


		void drawMainMenuBar()
		{
			ImGui::BeginMainMenuBar();

			if ( ImGui::BeginMenu( "File" ) )
			{
				if ( ImGui::MenuItem( "Save Scene" ) )
				{
					serializeScene();
				}

				if ( ImGui::MenuItem( "Reload Current Scene" ) )
				{
					reloadScene();
				}
				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();

		}

		void displayFPS( double deltaTime, bool* doTest )
		{
			ImGui::SetNextWindowPos( ImVec2(400,400), ImGuiCond_Once, ImVec2( 0.f, 0.f ) );
			ImGui::Begin( "Mesh Shader Batch Test" );
			ImGui::Text( "This is going to look like a solid colour but it's acutally a million sprites. It's not a good test because sometimes it goes off the screen etc. but you get the general idea: if it runs at all decently then it's better than trying to do it without the mesh shader." );
			m_timeSinceLastDebugInfoOutput += deltaTime;
			if ( m_timeSinceLastDebugInfoOutput > m_debugInfoOutputFrequency )
			{
				m_currentFrameRate = 1.0 / deltaTime;
				m_timeSinceLastDebugInfoOutput = 0.0;
			}
			ImGui::Text( "FPS: %f", m_currentFrameRate );
			ImGui::Checkbox( "Do test?", doTest );

			ImGui::End();
		}

		void drawInspectorPanel()
		{
			ImVec2 displaySize = ImGui::GetIO().DisplaySize;
			ImGui::SetNextWindowPos( ImVec2( displaySize.x, 20), ImGuiCond_Once, ImVec2( 1.f, 0.f ) );
			ImGui::SetNextWindowSize( ImVec2( 300, displaySize.y ) );
			ImGui::Begin( "Inspector" );
			if ( m_selectedEntity != Core::InvalidSize && m_registry.getEntityAlive( m_selectedEntity ))
			{
				ImGui::Text( "Entity: %d", static_cast<int>(m_selectedEntity) );

				Signature sig = m_registry.getComponentSignature( m_selectedEntity );

				ImGui::Separator();
				for ( auto it = sig.begin(); it != sig.end(); it++ )
				{
					 
					PoolBase& pool = m_registry.getPool( *it );
					DisplayFunc displayFunc =  pool.getTypeInfo().m_displayFunc;
					ImGui::Text( pool.getTypeInfo().m_typeName );
					ImGui::Indent();
					ImGui::PushID( pool.getTypeInfo().m_typeName);
					displayFunc( pool.getComponentAsVoidPointer( m_selectedEntity ));

					if ( ImGui::Button( "Remove Component" ) )
					{
						m_registry.removeComponentFromEntity_componentIdVersion( m_selectedEntity, pool.getComponentId() );
					}
					ImGui::PopID();
					ImGui::Separator();

					ImGui::Unindent();
				}

				ImGui::Text( "Components that you can add:" );
				
				std::map<std::string, ReflectedTypeInfoBase*> typeInfoMap = ReflectedTypeInfoBase::getTypeMap();
				for ( auto pair : typeInfoMap )
				{
					//for each component type
					if (!m_registry.entityHasComponentByComponentId(m_selectedEntity, pair.second->m_typeIndex))
					{
						if ( ImGui::Button( pair.first.c_str() ) )
						{
							pair.second->m_buildFunc( m_selectedEntity );
						}
					}
				}
			}
			else 
			{
				ImGui::Text( "No entity selected" );
			}
			ImGui::End();
		}


		void reloadScene()
		{
			m_registry.clear();
			std::string defaultSceneFilepath = "defaultScene.scn";
			loadScene( defaultSceneFilepath, m_registry );
		}


	//The basic idea behind serialization and deserialization in Crayon:
	//within the callee's serialize() function, you wrap everything in a map (unless it's a primitive type like an int.This map is the VALUE : the callee just outputs this value.The CALLER is in charge of outputting the key.The reason for this is, sometimes we just want the value( if we're, say, creating a sequence as opposed to a map).
		void serializeScene( const char* sceneFilePath = defaultSceneFilepath.data() )
		{
			SparseSet<Signature>& entitySignatures = m_registry.getAllSignatures();

			using SerializationFunction = void(*)(void*, const char*);

			m_sceneOut << YAML::BeginSeq;

			//for each Entity('s signature)...
			for ( auto it = entitySignatures.begin(); it != entitySignatures.end(); it++ )
			{
				size_t entityIndex = it.getIndex();
				Signature sig = *it;

				startSerializingEntity( entityIndex );

				//for each set bit in that signature (i.e. for each component the Entity has)...
				for ( auto componentIt = sig.begin(); componentIt != sig.end(); componentIt++ )
				{
					PoolBase& pool = m_registry.getPool( *componentIt );
					SerializationFunction serFunc = pool.getTypeInfo().m_serializeFunc;
					if ( serFunc != nullptr )
					{
						m_sceneOut << YAML::Key << pool.getTypeInfo().m_typeName;
						serFunc( pool.getComponentAsVoidPointer( entityIndex ), "Unnamed" );
					}
				}
				stopSerializingEntity();
			}

			m_sceneOut << YAML::EndSeq;
			saveSceneToFile();
		}



		bool saveSceneToFile( const char* sceneFilePath = defaultSceneFilepath.data() )
		{
			//with truncate mode, if the file exists its contents are discarded when you open it
			std::ofstream fout( sceneFilePath, std::ios::out|std::ios::trunc);
			if ( !fout.is_open() )
			{
				return false;
			}
			fout << m_sceneOut.c_str();
			fout.close();

			m_sceneOut.reset();
			return true;
		}


			
		void startSerializingEntity( size_t entityIndex )
		{
			m_sceneOut << YAML::Value;
			m_sceneOut << YAML::BeginMap;
		}

		void stopSerializingEntity()
		{
			m_sceneOut << YAML::EndMap;
		}


		static void loadScene( std::string& sceneFilePath, Registry& registry )
		{
			YAML::Node sceneData = YAML::LoadFile( sceneFilePath );

			//the entities are not key-map pairs at the moment: we don't give them identifiers or anything. I'm guessing this will change, though, for
			//merging purposes or whatever, but we'll see
			for ( const auto& entity : sceneData )
			{
				Entity newEntity = registry.queueEntityForCreation();

				if ( entity.IsMap() )
				{
					//...the components, on the other hand, do have names, & as such are key-map pairs
					for ( const auto& componentPair : entity )
					{
						std::string componentName = componentPair.first.as<std::string>();

						const auto& componentData = componentPair.second;
						if ( componentData.IsMap() )
						{
							std::map<std::string, ReflectedTypeInfoBase*>& propMap = ReflectedTypeInfoBase::getTypeMap();
							BuildFunc buildFunc = ReflectedTypeInfoBase::getTypeMap()[componentName]->m_buildFunc;
							DeserializeFunc deserializeFunc = ReflectedTypeInfoBase::getTypeMap()[componentName]->m_deserializeFunc;
							if ( buildFunc && deserializeFunc )
							{
								size_t componentPoolId = buildFunc( newEntity.getId() );
								void* pComponent = registry.getPool( componentPoolId ).getComponentAsVoidPointer( newEntity.getId() );
								deserializeFunc( pComponent, componentName.c_str(), componentData );
							}
						}
					}
				}
			}
		}




		static std::vector<std::string> getAllFilesWithExtension( const std::string& directory, const std::string& desiredExtension )
		{
		std::vector<std::string> files;

		//constexpr std::string_view desiredExtension = "png";
		const size_t extensionSize = desiredExtension.size();

		for ( const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator( directory ) )
		{
	        if ( entry.is_regular_file() )
	        {
	            std::string path = entry.path().string();
	            //compare paramters: where to compare from in base string, how much to compare, what to compare against.
	            //returns 0 if no difference.
	            if ( path.size() > extensionSize && (path.compare(path.size() - extensionSize, extensionSize, desiredExtension) ==0))
	            {
	                files.push_back( entry.path().string() );
	            }
	        }
		}
		std::sort( files.begin(), files.end() );

		return files;
	}




	   //A combo box is a drop-down menu
	   template<typename AssetType>
	   static std::optional<std::string> generateComboBox( AssetType* pAssetType, const std::string& directory, const std::string& extension )
	   {
		   int currentItemIndex = 0;
		   std::vector<std::string> assetFilePaths = getAllFilesWithExtension( directory, extension );
		   std::vector<const char*> items;

		   for ( const auto& path : assetFilePaths )
		   {
			   if ( path == pAssetType->assetPath )
			   {
				   currentItemIndex = static_cast<int>(items.size());
			   }
			   items.push_back( path.c_str() );
		   }

		   //Todo: change this!!!
		   if ( ImGui::Combo( "##Texture Filepaths", &currentItemIndex, items.data(), static_cast<int>(items.size()) ) )
		   {
			   return items[currentItemIndex];
		   }
		   else return std::nullopt;
	   }




	   ///////////////////////////////////////////////////////////////////////////////////////////////
	   ///////////////////////////////////////////////////////////////////////////////////////////////
	   //INJECTION CODE(stuff to be put in the DisplayFunc etc. function pointers of Properties and TypeInfoObjects
	   /////////////////////////////////////////////////////////////////////////////////////////////// 
	   ///////////////////////////////////////////////////////////////////////////////////////////////

	   ////////////////////////////////////
		//DISPLAY LOGIC
		////////////////////////////////////

	   //////////
	   //branch display methods
	   //////////
	   template<typename T>
	   static void displayFromVoidPointer( void* pVoid )
	   {
		   T* pObject = reinterpret_cast<T*>(pVoid);
		   Editor::get().display( pObject );
	   }

	   template <typename T>
	   void display( T* pObject )
	   {
		   ImGui::PushID( pObject );
		   if constexpr ( is_reflected<T>::value )
		   {
			   {
				   std::vector<Property>& properties = ReflectedTypeInfo<T>::getProperties();

				   for ( auto& property : properties )
				   {
					   ImGui::Text( property.m_name );
					   sameLine();
					   ImGui::PushID( property.m_name );
					   void* pProperty = reinterpret_cast<void*> (reinterpret_cast<char*>(pObject) + property.m_offset);
					   property.m_displayFunc( pProperty );
					   ImGui::PopID();
				   }
			   }
		   }

		   else if constexpr ( is_container<T>::value )
		   {
			   using ElementType = T::value_type;

			   size_t index = 0;
			   for ( ElementType& element : *pObject )
			   {
				   display( &element );
				   index++;
			   }
		   }

		   else
		   {
			   ImGui::Text( "I don't know how to display this" );
		   }

		   ImGui::PopID();
	   }

	   //////
	   //end of branch display methods
	   //////


	   //Leaf "Display" methods
	   void display( bool* inBool )
	   {
		   ImGui::Checkbox( "##bool", inBool );
	   }
	   void display( int* inInt )
	   {
		   ImGui::InputInt( "##int", inInt );
	   }
	   void display( float* inFloat )
	   {
		   ImGui::InputFloat( "##float", inFloat );
	   }
	   void display( double* inDouble )
	   {
		   ImGui::InputDouble( "##double", inDouble );
	   }
	   void display( uint32_t* uint32t )
	   {
		   ImGui::InputScalar( "##uint32_t", ImGuiDataType_U32, uint32t );
	   }
	   void display( size_t* size )
	   {
		   ImGui::InputScalar( "##size_t", ImGuiDataType_U64, size );
	   }
	   void display( glm::vec2* inVec )
	   {
		   ImGui::NewLine();
		   ImGui::Indent();
		   ImGui::PushID( "x: " );
		   ImGui::Text( "x: " );
		   sameLine();
		   display( &inVec->x );
		   ImGui::PopID();

		   ImGui::PushID( "y: " );
		   ImGui::Text( "y: " );
		   sameLine();
		   display( &inVec->y );
		   ImGui::PopID();
		   ImGui::Unindent();
	   }
	   void display( Rect* pRect, const char* name = "Unnamed Rect" )
	   {
		   ImGui::NewLine();
		   ImGui::Indent();
		   ImGui::PushID( "origin" );
		   ImGui::Text( "origin" );
		   display( &pRect->origin );
		   ImGui::PopID();


		   ImGui::PushID( "extent" );
		   ImGui::Text( "extent" );
		   display( &pRect->extent );
		   ImGui::PopID();
		   ImGui::Unindent();
	   }
	   //get all textures in a directory, make a vector of const char*s out of them and hand that into an ImGui::Combo (a dropdown list)
	   void display( TextureIdentifier* pTexId )
	   {
		   ImGui::NewLine();
		   ImGui::Indent();

		   if ( std::optional<std::string> textureName = generateComboBox( pTexId, "Textures", "png" ); textureName.has_value() )
		   {
			   pTexId->assetPath = textureName.value();
			   pTexId->textureIndex = m_renderer.addTextureIfNew( pTexId->assetPath.c_str() );
		   }
		   ImGui::Unindent();
	   }

	   void display( SoundAsset* pSoundAsset )
	   {
		   ImGui::NewLine();
		   ImGui::Indent();

		   if ( std::optional<std::string> soundName = generateComboBox( pSoundAsset, "SoundFiles", "wav" ); soundName.has_value() )
		   {
			   pSoundAsset->assetPath = soundName.value();
		   }
		   ImGui::Unindent();
	   }
	   ///////////
	   //end of leaf "display" methods
	   ///////////
	   
	   
	   
	   ///////////
	   // branch serialize and deserialize methods
	   ///////////
	   
	   template<typename T>
	   static void serializeFromVoidPointer( void* pObject, const char* name = "Unnamed Field" )
	   {
		   T* pCastedObject = reinterpret_cast<T*>(pObject);
		   Editor::get().serialize( pCastedObject, name );
	   }


	   template<typename T>
	   void serialize( T* pObject, const char* name = "Unnamed" )
	   {
		   //if it's a reflected type (some kind of class/struct)
		   if constexpr ( is_reflected<T>::value )
		   {
			   m_sceneOut << YAML::Value << YAML::BeginMap;
			   std::vector<Property>& properties = ReflectedTypeInfo<T>::getProperties();

			   for ( auto property : properties )
			   {
				   void* pVoidpointer = reinterpret_cast<void*>(reinterpret_cast<char*>(pObject) + property.m_offset);
				   m_sceneOut << YAML::Key << property.m_name;
				   property.m_serializeFunc( pVoidpointer, property.m_name );
			   }
			   m_sceneOut << YAML::EndMap;
		   }

		   //if it's a container, like a vector or whaever
		   else if constexpr ( is_container<T>::value )
		   {
			   //s_sceneOut << YAML::Key << name;
			   m_sceneOut << YAML::Flow << YAML::BeginSeq;
			   for ( auto element : *pObject )
			   {
				   serialize( &element );
			   }
			   m_sceneOut << YAML::EndSeq;
		   }

		   else
		   {
			   //??? if you wrap this up in a map, it won't work. Maybe you can't wrap a map in another map directly: maybe it needs to go: beginmap->key->map ...
			   //s_sceneOut << YAML::Key << name;
			   m_sceneOut << YAML::Value << *pObject;
		   }
	   }

	   template <typename T>
	   static void deserializeFromVoidPointer( void* pObject, const char* name, const YAML::Node& node )
	   {
		   T* pCastedObject = reinterpret_cast<T*>(pObject);
		   get().deserialize( pCastedObject, name, node );
	   }


	   template<typename T>
	   void deserialize( T* pObject, const char* name, const YAML::Node& node )
	   {
		   if constexpr ( is_reflected<T>::value )
		   {
			   std::vector<Property>& properties = ReflectedTypeInfo<T>::getProperties();

			   for ( auto property : properties )
			   {
				   if ( node[property.m_name].IsDefined() )
				   {
					   void* pVoidpointer = reinterpret_cast<void*>(reinterpret_cast<char*>(pObject) + property.m_offset);
					   property.m_deserializeFunc( pVoidpointer, property.m_name, node );
				   }
			   }
		   }

		   else if constexpr ( is_container<T>::value )
		   {
			   //for ( auto element : *pObject )
			   //{
			   //	serialize( &element );
			   //}
			   //s_sceneOut << YAML::EndSeq;
		   }

		   else if constexpr ( std::is_pointer_v<T> )
		   {
			   Logger::log( "Ooph you shouldn't be trying to deserialize a pointer m8" );
		   }

		   else
		   {
			   if ( node[name].IsDefined() )
			   {
				   *pObject = node[name].as<T>();
			   }
		   }

	   }

	   ////////
	   //end of branch serialize and deserialize methods
	   ////////

	   /////////
	   //leaf seralize and deserialize methods
	   ////////
	   void serialize( glm::vec2* pVec2, const char* name = "Unnamed Vec 2" )
	   {
		   m_sceneOut << YAML::BeginMap;
		   m_sceneOut << YAML::Key << "x" << YAML::Value << pVec2->x << YAML::Key << "y" << YAML::Value << pVec2->y;
		   m_sceneOut << YAML::EndMap;
	   }
	   void deserialize( glm::vec2* pVec2, const char* name, const YAML::Node& node )
	   {
		   pVec2->x = node[name]["x"].as<float>();
		   pVec2->y = node[name]["y"].as<float>();
	   }
	   void serialize( Rect* pRect, const char* name = "Unnamed Rect" )
	   {
		   m_sceneOut << YAML::BeginMap;
		   m_sceneOut << YAML::Key << "origin";
		   serialize( &pRect->origin );
		   m_sceneOut << YAML::Key << "extent";
		   serialize( &pRect->extent );
		   m_sceneOut << YAML::EndMap;
	   }
	   void deserialize( Rect* pRect, const char* name, const YAML::Node& node )
	   {
		   const YAML::Node& subNode = node[name];
		   deserialize( &pRect->origin, "origin", subNode );
		   deserialize( &pRect->extent, "extent", subNode );
	   }
	   void serialize( TextureIdentifier* pTexId, const char* name = "Unnamed Tex ID" )
	   {
		   m_sceneOut << YAML::BeginMap;
		   m_sceneOut << YAML::Key << "TexturePath" << YAML::Value << pTexId->assetPath;
		   m_sceneOut << YAML::EndMap;
	   }
	   void deserialize( TextureIdentifier* pTexId, const char* name, const YAML::Node& node )
	   {
		   pTexId->assetPath = node[name]["TexturePath"].as<std::string>();
		   pTexId->textureIndex = m_renderer.addTextureIfNew( pTexId->assetPath.c_str() );
	   }
	   void serialize( SoundAsset* pSoundAsset, const char* name = "Unnamed Sound Asset" )
	   {
		   m_sceneOut << YAML::BeginMap;
		   m_sceneOut << YAML::Key << "AssetPath" << YAML::Value << pSoundAsset->assetPath;
		   m_sceneOut << YAML::EndMap;
	   }
	   void deserialize( SoundAsset* pSoundAsset, const char* name, const YAML::Node& node )
	   {
		   pSoundAsset->assetPath = node[name]["AssetPath"].as<std::string>();
	   }
	   //////
	   //end of leaf serialize and deserialize methods
	   ///////
	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////
	//End of Injection Code
	/////////////////////////////////////////////////////////////////////////////////////////////// 
	///////////////////////////////////////////////////////////////////////////////////////////////

		//Helper functions


		static void sameLine()
		{
			ImGui::SameLine( 0, 20 );
		}

	};
}