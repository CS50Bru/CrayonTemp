#pragma once
#include<filesystem>
#include<algorithm>
#include"Libraries/imgui/imgui_impl_vulkan.h"
#include"Libraries/imgui/imgui_impl_win32.h"
#include"Rendering/Renderer.h"
#include"Core.h"
#include"WindowAndInput/InputEvent.h"

//Sets up ImGui and takes care of ImGui events. It piggybacks off of the Renderer to do this (ImGui needs the VkDevice in the Renderer)

//You have to call shutdown() to have it clear its Vulkan resources, and you have to do it while the Renderer is still alive so that the resources to cleanup those resources are still around.

//You can only have 1 instance of GUIManager, but it's not a singleton (that 1 instance isn't globally available)

namespace Crayon
{
	class GUIManager
	{

	private:
        inline static bool s_instanceAlreadyExists = false;

        VkDescriptorPool m_descriptorPool;
        bool m_shutdownCalled = false;

	public:
		GUIManager( HWND windowHandle, Renderer& renderer )
		{
            CRAYON_ASSERT( !s_instanceAlreadyExists );
            s_instanceAlreadyExists = true;

			IMGUI_CHECKVERSION();
			ImGui::CreateContext();

			ImGui_ImplWin32_Init( windowHandle );

			m_descriptorPool = createIMGUIDescriptorPool( renderer );

            //we need this 'rendering create info' because we're not using an actual Renderpass object on the Vulkan side (because we're using dynamic rendering), so we have to provide info about the format etc. another way
            VkFormat colorAttachmentFormat = renderer.getUiRenderpassInfo().mainAttachmentFormat;
            VkFormat depthAttachmentFormat = renderer.getUiRenderpassInfo().depthBufferFormat;

            VkPipelineRenderingCreateInfoKHR renderingCreateInfo = {};
            renderingCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO_KHR;
            renderingCreateInfo.colorAttachmentCount = 1;
            renderingCreateInfo.pColorAttachmentFormats = &colorAttachmentFormat;
            renderingCreateInfo.depthAttachmentFormat = depthAttachmentFormat;
            renderingCreateInfo.pNext = nullptr;

			ImGui_ImplVulkan_InitInfo init_info = {};
            init_info.PipelineRenderingCreateInfo = renderingCreateInfo;
			init_info.Instance = renderer.getInstance();
			init_info.PhysicalDevice = renderer.getPhysicalDevice();
			init_info.Device = renderer.getDevice();
			init_info.QueueFamily = static_cast<uint32_t>(renderer.getGraphicsQueueFamilyIndex());
			init_info.Queue = renderer.getGraphicsQueue();
			init_info.PipelineCache = VK_NULL_HANDLE;
			init_info.DescriptorPool = m_descriptorPool;
            init_info.RenderPass = VK_NULL_HANDLE;
			init_info.Subpass = 0;
			init_info.MinImageCount = 2;
			init_info.ImageCount = static_cast<uint32_t>(renderer.getSwapChainImageCount());
			init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
			init_info.Allocator = nullptr;
			init_info.CheckVkResultFn = nullptr;
            init_info.UseDynamicRendering = true;
           
            init_info.PipelineRenderingCreateInfo.viewMask = 0;

			// Fill init_info with your Vulkan setup
			ImGui_ImplVulkan_Init( &init_info );

			// Upload Fonts
			ImGui_ImplVulkan_CreateFontsTexture();

#ifdef DEBUG
            ImGui::GetIO().IniFilename = nullptr;
#else
            //ToDo: decide where the ini file should actually go, and then actually set the release version to use it
            ImGui::GetIO().IniFilename = nullptr;//INTERMEDIATE_DIRECTORY_PATH "imgui.ini";
#endif
		}

		GUIManager( const GUIManager& other ) = delete;
        GUIManager& operator=( const GUIManager& ) = delete;

        void shutdown( VkDevice logicalDevice )
        {
            ImGui_ImplVulkan_Shutdown();
            ImGui_ImplWin32_Shutdown();
            ImGui::DestroyContext();

            //Now it's safe to destroy our descriptor pool
            if ( m_descriptorPool != VK_NULL_HANDLE )
            {
                vkDestroyDescriptorPool( logicalDevice, m_descriptorPool, nullptr );
            }
            m_shutdownCalled = true;
        }

		~GUIManager()
		{
            CRAYON_ASSERT( m_shutdownCalled );
		}



		VkDescriptorPool createIMGUIDescriptorPool( Renderer& renderer ) const
		{
			VkDescriptorPoolSize pool_sizes[] =
			{
				{ VK_DESCRIPTOR_TYPE_SAMPLER, 1000 },
				{ VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
				{ VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000 },
				{ VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000 },
				{ VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000 },
				{ VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000 },
				{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000 },
				{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000 },
				{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
				{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
				{ VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000 }
			};

			VkDescriptorPoolCreateInfo pool_info = {};
			pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
			pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
			pool_info.maxSets = 1000 * IM_ARRAYSIZE( pool_sizes );
			pool_info.poolSizeCount = (uint32_t)IM_ARRAYSIZE( pool_sizes );
			pool_info.pPoolSizes = pool_sizes;

			VkDescriptorPool descriptorPool;
			vkCreateDescriptorPool( renderer.getDevice(), &pool_info, nullptr, &descriptorPool );
			return descriptorPool;
		}

        void prepForUpdate()
        {
            //Get IMGUI to generate all the info it needs to create a bunch of Vulkan draw commands

            //Handles any state updates etc. that have happened: I guess this is where ImGui would deal with window resize events etc. , for example
            ImGui_ImplVulkan_NewFrame();


            //if you set up your Windows window to forward messages to ImGui, then this is where ImGui will go through those messages and therefore where it will
            //handle input-related stuff. We don't do that and instead we plug input-related stuff into ImGui ourselves using a different function, but there's
            //still stuff it needs to do here like getting timing-related info etc.
            ImGui_ImplWin32_NewFrame();


            //this is where ImGui handles things like mouse hovering etc.: it's really like ImGui's update() function
            ImGui::NewFrame();  

        }



        static void assembleDrawData() { ImGui::Render(); }

        static void sumbitDrawData( VkCommandBuffer& commandBuffer ) 
        { 
            ImGui_ImplVulkan_RenderDrawData( ImGui::GetDrawData(), commandBuffer );
        }


        void processChars( const std::vector<unicode_char>& chars )
        {
            ImGuiIO& io = ImGui::GetIO();
            for ( auto character : chars )
            {
                io.AddInputCharacter( character );
            }
        }

		void processInputEvents(glm::ivec2 cursorPos, std::vector<InputEvent>& inputEvents )
		{
			ImGuiIO& io = ImGui::GetIO();

            //this doesn't actually seem to be used for much: to actually get mouse wheel scrolling working you use io.AddMouseWheelEvent.
            //but it feels weird not to set it, so here I go.
            io.MouseWheel = 0.f;

			for ( auto& event : inputEvents )
			{
				if ( event.m_keyCode == InputName::MouseMove )
				{

				}

				else if ( event.m_keyCode == InputName::MouseLeft )
				{
                    processMouseButtonEvent( event, 0, io );
				}

                else if (event.m_keyCode==InputName::MouseWheel )
                { 
                    io.MouseWheel  =event.scrollValue;
                    io.AddMouseWheelEvent( 0.f, event.scrollValue);
                }

                else
                {
                    int imguiKey = MapKeyCodeToImGuiKey( event.m_keyCode );

                    if ( imguiKey != 0 )
                    {
                        io.KeysDown[imguiKey] = event.getActive();
                        io.AddKeyEvent( static_cast<ImGuiKey>(imguiKey), event.getActive() );
                    }
                }
			}
            ///NB You have to update the mouse position AFTER everything else or you will break clicking and dragging
            io.MousePos = ImVec2( cursorPos.x, cursorPos.y );
		}

        void processMouseButtonEvent( InputEvent inputEvent, size_t buttonNumber, ImGuiIO& io )
        {
            io.MouseDown[buttonNumber] = inputEvent.getActive();
            glm::vec2 mousePos = inputEvent.screenPosition;
            io.MousePos= ImVec2( static_cast<float>(mousePos.x), static_cast<float>(mousePos.y) );
            io.AddMouseButtonEvent( static_cast<int>(buttonNumber), inputEvent.getActive() );
        }

        int MapKeyCodeToImGuiKey( InputName key )
        {
            switch ( key )
            {
            case InputName::Backspace: return ImGuiKey_Backspace;
            case InputName::Tab: return ImGuiKey_Tab;
            case InputName::Clear: return ImGuiKey_None;
            case InputName::Enter: return ImGuiKey_Enter;
            case InputName::Shift: return ImGuiKey_ModShift;
            case InputName::Control: return ImGuiKey_ModCtrl;
            case InputName::Alt: return ImGuiKey_ModAlt;
            case InputName::Pause: return ImGuiKey_Pause;
            case InputName::CapsLock: return ImGuiKey_CapsLock;
            case InputName::Escape: return ImGuiKey_Escape;
            case InputName::Space: return ImGuiKey_Space;
            case InputName::PageUp: return ImGuiKey_PageUp;
            case InputName::PageDown: return ImGuiKey_PageDown;
            case InputName::End: return ImGuiKey_End;
            case InputName::Home: return ImGuiKey_Home;
            case InputName::Left: return ImGuiKey_LeftArrow;
            case InputName::Up: return ImGuiKey_UpArrow;
            case InputName::Right: return ImGuiKey_RightArrow;
            case InputName::Down: return ImGuiKey_DownArrow;
            case InputName::Select: return ImGuiKey_None; // No direct ImGui equivalent
            case InputName::Print: return ImGuiKey_PrintScreen;
            case InputName::Execute: return ImGuiKey_None; // No direct ImGui equivalent
            case InputName::PrintScreen: return ImGuiKey_PrintScreen;
            case InputName::Insert: return ImGuiKey_Insert;
            case InputName::Delete: return ImGuiKey_Delete;
            case InputName::Help: return ImGuiKey_None; // No direct ImGui equivalent
            case InputName::Zero: return ImGuiKey_0;
            case InputName::One: return ImGuiKey_1;
            case InputName::Two: return ImGuiKey_2;
            case InputName::Three: return ImGuiKey_3;
            case InputName::Four: return ImGuiKey_4;
            case InputName::Five: return ImGuiKey_5;
            case InputName::Six: return ImGuiKey_6;
            case InputName::Seven: return ImGuiKey_7;
            case InputName::Eight: return ImGuiKey_8;
            case InputName::Nine: return ImGuiKey_9;
            case InputName::A: return ImGuiKey_A;
            case InputName::B: return ImGuiKey_B;
            case InputName::C: return ImGuiKey_C;
            case InputName::D: return ImGuiKey_D;
            case InputName::E: return ImGuiKey_E;
            case InputName::F: return ImGuiKey_F;
            case InputName::G: return ImGuiKey_G;
            case InputName::H: return ImGuiKey_H;
            case InputName::I: return ImGuiKey_I;
            case InputName::J: return ImGuiKey_J;
            case InputName::K: return ImGuiKey_K;
            case InputName::L: return ImGuiKey_L;
            case InputName::M: return ImGuiKey_M;
            case InputName::N: return ImGuiKey_N;
            case InputName::O: return ImGuiKey_O;
            case InputName::P: return ImGuiKey_P;
            case InputName::Q: return ImGuiKey_Q;
            case InputName::R: return ImGuiKey_R;
            case InputName::S: return ImGuiKey_S;
            case InputName::T: return ImGuiKey_T;
            case InputName::U: return ImGuiKey_U;
            case InputName::V: return ImGuiKey_V;
            case InputName::W: return ImGuiKey_W;
            case InputName::X: return ImGuiKey_X;
            case InputName::Y: return ImGuiKey_Y;
            case InputName::Z: return ImGuiKey_Z;
            case InputName::LeftWindowsKey: return ImGuiKey_LeftSuper;
            case InputName::RightWindowsKey: return ImGuiKey_RightSuper;
            case InputName::ApplicationsKey: return ImGuiKey_Menu;
            case InputName::Sleep: return ImGuiKey_None; // No direct ImGui equivalent
            case InputName::NumPad0: return ImGuiKey_Keypad0;
            case InputName::NumPad1: return ImGuiKey_Keypad1;
            case InputName::NumPad2: return ImGuiKey_Keypad2;
            case InputName::NumPad3: return ImGuiKey_Keypad3;
            case InputName::NumPad4: return ImGuiKey_Keypad4;
            case InputName::NumPad5: return ImGuiKey_Keypad5;
            case InputName::NumPad6: return ImGuiKey_Keypad6;
            case InputName::NumPad7: return ImGuiKey_Keypad7;
            case InputName::NumPad8: return ImGuiKey_Keypad8;
            case InputName::NumPad9: return ImGuiKey_Keypad9;
            case InputName::Multiply: return ImGuiKey_KeypadMultiply;
            case InputName::Add: return ImGuiKey_KeypadAdd;
            case InputName::Separator: return ImGuiKey_KeypadEnter;
            case InputName::Subtract: return ImGuiKey_KeypadSubtract;
            case InputName::Decimal: return ImGuiKey_KeypadDecimal;
            case InputName::Divide: return ImGuiKey_KeypadDivide;
            case InputName::F1: return ImGuiKey_F1;
            case InputName::F2: return ImGuiKey_F2;
            case InputName::F3: return ImGuiKey_F3;
            case InputName::F4: return ImGuiKey_F4;
            case InputName::F5: return ImGuiKey_F5;
            case InputName::F6: return ImGuiKey_F6;
            case InputName::F7: return ImGuiKey_F7;
            case InputName::F8: return ImGuiKey_F8;
            case InputName::F9: return ImGuiKey_F9;
            case InputName::F10: return ImGuiKey_F10;
            case InputName::F11: return ImGuiKey_F11;
            case InputName::F12: return ImGuiKey_F12;
            case InputName::F13: return ImGuiKey_F13;
            case InputName::F14: return ImGuiKey_F14;
            case InputName::F15: return ImGuiKey_F15;
            case InputName::F16: return ImGuiKey_F16;
            case InputName::F17: return ImGuiKey_F17;
            case InputName::F18: return ImGuiKey_F18;
            case InputName::F19: return ImGuiKey_F19;
            case InputName::F20: return ImGuiKey_F20;
            case InputName::F21: return ImGuiKey_F21;
            case InputName::F22: return ImGuiKey_F22;
            case InputName::F23: return ImGuiKey_F23;
            case InputName::F24: return ImGuiKey_F24;
            case InputName::Numlock: return ImGuiKey_NumLock;
            case InputName::ScrollLock: return ImGuiKey_ScrollLock;
            case InputName::LeftShift: return ImGuiKey_LeftShift;
            case InputName::RightShift: return ImGuiKey_RightShift;
            case InputName::LeftControl: return ImGuiKey_LeftCtrl;
            case InputName::RightControl: return ImGuiKey_RightCtrl;
            case InputName::LeftMenu: return ImGuiKey_LeftAlt;
            case InputName::RightMenu: return ImGuiKey_RightAlt;
            case InputName::BrowserBack: return ImGuiKey_None; // No direct ImGui equivalent
            case InputName::BrowserForward: return ImGuiKey_None; // No direct ImGui equivalent
            case InputName::BrowserRefresh: return ImGuiKey_None; // No direct ImGui equivalent
            case InputName::BrowserStop: return ImGuiKey_None; // No direct ImGui equivalent
            case InputName::BrowserSearch: return ImGuiKey_None; // No direct ImGui equivalent
            case InputName::BrowserFavorites: return ImGuiKey_None; // No direct ImGui equivalent
            case InputName::BrowserHome: return ImGuiKey_None; // No direct ImGui equivalent
            case InputName::VolumeMute: return ImGuiKey_None; // No direct ImGui equivalent
            case InputName::VolumeDown: return ImGuiKey_None; // No direct ImGui equivalent
            case InputName::VolumeUp: return ImGuiKey_None; // No direct ImGui equivalent
            case InputName::NextTrack: return ImGuiKey_None; // No direct ImGui equivalent
            case InputName::PreviousTrack: return ImGuiKey_None; // No direct ImGui equivalent
            case InputName::StopMedia: return ImGuiKey_None; // No direct ImGui equivalent
            case InputName::PlayPause: return ImGuiKey_None; // No direct ImGui equivalent
            case InputName::LaunchMail: return ImGuiKey_None; // No direct ImGui equivalent
            case InputName::SelectMedia: return ImGuiKey_None; // No direct ImGui equivalent
            case InputName::LaunchApp1: return ImGuiKey_None; // No direct ImGui equivalent
            case InputName::LaunchApp2: return ImGuiKey_None; // No direct ImGui equivalent
            case InputName::OEM1: return ImGuiKey_Semicolon; // Assuming this is the semicolon key
            case InputName::OEMPlus: return ImGuiKey_Equal;
            case InputName::OEMComma: return ImGuiKey_Comma;
            case InputName::OEMMinus: return ImGuiKey_Minus;
            case InputName::OEMPeriod: return ImGuiKey_Period;
            case InputName::OEM2: return ImGuiKey_Slash; // Assuming this is the forward slash key
            case InputName::OEM3: return ImGuiKey_GraveAccent;
            case InputName::OEM4: return ImGuiKey_LeftBracket;
            case InputName::OEM5: return ImGuiKey_Backslash;
            case InputName::OEM6: return ImGuiKey_RightBracket;
            case InputName::OEM7: return ImGuiKey_Apostrophe;
            case InputName::OEM8: return ImGuiKey_None; // No direct ImGui equivalent
            case InputName::OEM102: return ImGuiKey_None; // No direct ImGui equivalent
            case InputName::Process: return ImGuiKey_None; // No direct ImGui equivalent
            case InputName::Packet: return ImGuiKey_None; // No direct ImGui equivalent
            case InputName::Attn: return ImGuiKey_None; // No direct ImGui equivalent
            case InputName::CrSel: return ImGuiKey_None; // No direct ImGui equivalent
            case InputName::ExSel: return ImGuiKey_None; // No direct ImGui equivalent
            case InputName::EraseEOF: return ImGuiKey_None; // No direct ImGui equivalent
            case InputName::Play: return ImGuiKey_None; // No direct ImGui equivalent
            case InputName::Zoom: return ImGuiKey_None; // No direct ImGui equivalent
            case InputName::PA1: return ImGuiKey_None; // No direct ImGui equivalent
            case InputName::OEMClear: return ImGuiKey_None; // No direct ImGui equivalent
            case InputName::MouseLeft: return ImGuiMouseButton_Left;
            case InputName::MouseRight: return ImGuiMouseButton_Right;
            case InputName::MouseMiddle: return ImGuiMouseButton_Middle;
            case InputName::MouseMove: return ImGuiKey_None; // Mouse movement is handled differently in ImGui
            case InputName::InvalidValue: return ImGuiKey_None;
            case InputName::MouseWheel: return ImGuiKey_None;
            default: return ImGuiKey_None;
            }
        }

	};

}