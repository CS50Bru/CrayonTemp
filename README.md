# Crayon

## What Crayon Is

.currently an editor/engine/game mashed into one: really just an experiment with rendering etc. rather than an actual engine. It's a learning project.

It uses Vulkan for rendering (and ImGui for UI rendering), XAudio2 for audio, and it sets up the actual window (and gets user input) using the Win32 API.

## Target Platform

Windows only.


## How to Build It

Crayon uses Premake.

Run Setup-Windows.bat to run Premake and generate the project files.

## Dependencies

You need the **Vulkan SDK** downloaded on your system. Crayon then looks for its location in your **environment variables**, which it should have been added to automatically as part of the installation process.

Regarding the version of the SDK, as long as it supports **Vulkan 1.3** and **spv 1.6**, it should work. The specific version of the Vulkan SDK that Crayon is being developed with is **1.4.304.0**.
(Crayon uses a lot of relatively recent features such as dynamic rendering (where you don't have to create actual Renderpass objects), so that's why it needs a new-ish version of the SDK)

If you're using Visual Studio then I'm pretty sure that XAudio2 and the rest of the Microsoft-specific stuff gets packed in by default.

## System Requirements

The renderer is 2d only but it relies on mesh shaders, so your graphics card has to support that. Also, I haven't tested this on laptops with integrated GPUs: basically, Crayon expects you to have a relatively recent, discrete GPU.

It has only been tested on Windows 10.