workspace "unknown"
    configurations { "Debug", "Release" }

    defines{"GRAPHICS_API_OPENGL_43"}
    includedirs { 
        "raylib/raylib/include"
    }
    buildoptions { 
        "-ggdb3",
        "-fPIC",
        "-Wall",
    }
    links { 
        "m",
        "raylib",
    }
    libdirs { 
        "raylib/raylib/",
    }
    language "C"
    kind "ConsoleApp"
    targetprefix ""
    targetdir "."
    symbols "On"

    project "de_ecs"
        buildoptions { 
            "-ggdb3",
            "-fsanitize=address",
        }
        linkoptions {
            "-fsanitize=address",
        }
        files { 
            "*.c",
        }

    
    filter "configurations:Debug"
        --defines { "DEBUG" }
        --symbols "On"
        --buildoptions { 
            --"-ggdb3"
        --}

    filter "configurations:Release"
        --buildoptions { 
            --"-O2"
        --}
        --symbols "On"
        --defines { "NDEBUG" }
        --optimize "On"

