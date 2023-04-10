project "Glad"
	kind "StaticLib"
	language "C"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-itm/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"include/glad/glad.h",
		"include/KHR/khrplatform.h",
		"src/glad.c"
	}

	includedirs{
		"include"
	}

	systemversion "latest"
	staticruntime "On"
	
	
	filter "configurations:Release"
		buildoptions "/MT"