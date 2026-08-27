cmake_minimum_required(VERSION 4.2.3)
project(NewSharpboyCore)

add_executable(NewSharpboyCore)
target_sources(NewSharpboyCore
	PRIVATE 
		src/main.cpp
		src/core.cpp
        src/loader.cpp
		src/emu.cpp
		src/cpu.cpp
		src/bus.cpp

	PUBLIC 
		FILE_SET coreHeaders
		TYPE HEADERS
		BASE_DIRS include	
		FILES
            include/core.h
			include/common.h
            include/loader.h
            include/emu.h
            include/cpu.h
			include/registers.h
			include/bus.h
			include/io.h
			include/instructions.h
)
set_property(TARGET NewSharpboyCore PROPERTY CXX_STANDARD 20)