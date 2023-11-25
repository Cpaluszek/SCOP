cmake_minimum_required(VERSION 3.15)

project(MyProject)

include_directories(inc inc/math lib/GLEW/include lib/GLFW/include)

add_executable(SCOP ./src/ObjParser.cpp ./src/MtlParser.cpp ./src/Model.cpp ./src/program_options.cpp ./src/utils.cpp  ./src/math/Vec3f.cpp ./src/math/Mat4f.cpp ./src/Window.cpp ./src/Shader.cpp ./src/stb_image.cpp ./src/Mesh.cpp ./src/Input.cpp ./src/Texture.cpp ./src/Renderer.cpp ./src/Camera.cpp ./src/main.cpp ./src/Material.cpp)
