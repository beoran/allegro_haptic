--
-- Premake 4.x build configuration script for allegro_haptic
-- 

--
-- Define the project. Put the release configuration first so it will be the
-- default when folks build using the makefile. That way they don't have to 
-- worry about the /scripts argument and all that.
--

	solution "allegro_haptic"
		configurations { "Debug", "Release", "Static" }
	
	project "allegro_haptic"
		targetname  "allegro_haptic"
		language    "C"
		kind        "SharedLib"
		flags       { "ExtraWarnings"}
		
		includedirs { "include", "include/allegro5",                   
                  "/usr/local/include"    , "/usr/local/include/allegro5" ,                  
                  "/usr/include"          , "/usr/include/allegro5",
                  "./include"
                }

		libdirs     { "/usr/lib/i386-linux-gnu" }
		links       { "allegro" }		
    files {      
      "include/allegro5/allegro_haptic.h",
      "include/allegro5/internal/aintern_haptic.h",
      "haptic.c", 
    }


--[[		
		if      os.is("linux") then
      files {
        "include/allegro5/allegro_haptic.h", "src/haptic.c" "src/linux_haptic.c"
      }
		else if os.is("windows") then
		 "include/allegro5/allegro_haptic.h", "src/haptic.c" "src/window_haptic.c"
		else if os.is("macosx")  then
      "include/allegro5/allegro_haptic.h", "src/haptic.c" "src/macosx_haptic.c"
    else
      "include/allegro5/allegro_haptic.h", "src/haptic.c" "src/dummy_haptic.c"
		end
]]		

		configuration "Debug"
			targetdir   "lib"
			defines     "CONFIG_DEBUG"
			flags       { "Symbols" }
			
		configuration "Release"
			targetdir   "lib"
			defines     "NDEBUG"
			flags       { "OptimizeSize" }
			
		configuration "Static"
		  flags       { "StaticRuntime" }
		  

    configuration "linux"
      files {
       "linux_haptic.c"
      }     

		configuration "macosx"
      files {
       "macosx_haptic.c"
      }

		configuration "windows"
      files {
       "windows_haptic.c"
      }


--
-- A more thorough cleanup.
--
	if _ACTION == "clean" then
		os.rmdir("bin")
		os.rmdir("build")
	end
	
