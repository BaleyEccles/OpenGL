cmake_minimum_required(VERSION 3.15)

project(OpenGL)

find_package(OpenGL REQUIRED)


set(GLFW_SRC_PATH OpenGL2/include/glfw)
set(GLFW_INCLUDE_PATH OpenGL2/include/glfw/include)

set(GLM_INCLUDE_PATH OpenGL2/include/glm)

set(GLAD_INCLUDE_PATH OpenGL2/include/glad)

set(INCLUDE_PATH OpenGL2/src OpenGL2/include)


set(HEADERS OpenGL2/src/item.h
	    OpenGL2/src/Object.h
	    OpenGL2/src/Shader.h
	    OpenGL2/src/VertexArray.h
	    OpenGL2/include/glad/glad.h
)


set(SOURCES OpenGL2/src/main.cpp
	    OpenGL2/src/item.cpp
	    OpenGL2/src/Object.cpp
	    OpenGL2/src/Shader.cpp
	    OpenGL2/src/VertexArray.cpp
	    OpenGL2/src/glad.c
)

include_directories(
	${INCLUDE_PATH}
	${GLFW_INCLUDE_PATH}
	${GLM_INCLUDE_PATH}
	${GLAD_INCLUDE_PATH}
)

add_executable(main
	${HEADERS}
	${SOURCES}
)

target_link_libraries(main
	${OPENGL_LIBRARY}
	glfw ${GLFW_LIBRARY}
	${GLEW_LIBRARY}
)

#target_compile_options(main PRIVATE
#			    -O3
#			    -march=native	    
#			    -flto
#			    -funroll-loops
#			    -ftree-vectorize	    
#)
