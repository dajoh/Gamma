solution "Gamma"
	language "C++"
	location "Projects"
	targetdir "Binaries"
	includedirs "Include"
	configurations { "Debug", "Release" }
	
	configuration "windows"
		defines { "GLEW_STATIC", "GAMMA_PLATFORM_WIN32", "_CRT_SECURE_NO_WARNINGS" }
	
	configuration "linux"
		defines { "GLEW_STATIC", "GAMMA_PLATFORM_LINUX" }
	
	configuration "Debug"
		defines { "GAMMA_DEBUG" }
		flags { "StaticRuntime", "Symbols" }
	
	configuration "Release"
		defines { "GAMMA_RELEASE" }
		flags { "StaticRuntime" }
	
	vpaths
	{
		["Headers"] = "**.h",
		["Sources"] = "**.cpp"
	}
	
	project "Utilities"
		kind "StaticLib"
		files { "Source/Utilities/**.cpp", "Source/Utilities/**.h" }
		defines { "GAMMA_UTILITIES_INTERNAL" }
	
	project "Renderer"
		kind "SharedLib"
		files { "Source/Renderer/**.cpp", "Source/Renderer/**.h" }
		links { "Utilities" }
		defines { "GAMMA_RENDERER_INTERNAL" }
		
		configuration "windows"
			links { "opengl32", "../Libraries/glew32s" }
			excludes { "Source/Renderer/Linux/**" }
		
		configuration "linux"
			links { "X11", "GL", "GLEW" }
			excludes { "Source/Renderer/Win32/**" }
	
	project "Audio"
		kind "SharedLib"
		files { "Source/Audio/**.cpp", "Source/Audio/**.h" }
		links { "Utilities" }
		defines { "GAMMA_AUDIO_INTERNAL" }
		
		configuration "windows"
			links { "../Libraries/fmodex_vc" }
		configuration "linux"
			links { "fmod" }
	
	project "Engine"
		kind "SharedLib"
		files { "Source/Engine/**.cpp", "Source/Engine/**.h" }
		links { "Utilities", "Renderer", "Audio" }
		defines { "GAMMA_ENGINE_INTERNAL" }