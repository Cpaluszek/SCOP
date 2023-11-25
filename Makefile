NAME			:= SCOP

SRC_DIR			:=	src
SRC_FILES		:=	main.cpp \
					Camera.cpp \
					Input.cpp \
					Material.cpp \
					Mesh.cpp \
					Model.cpp \
					MtlParser.cpp \
					ObjParser.cpp \
					Renderer.cpp \
					Shader.cpp \
					Texture.cpp \
					Window.cpp \
					program_options.cpp \
					utils.cpp \
					math/Vec3f.cpp \
					math/Mat4f.cpp \
					stb_image.cpp

SRCS			:= $(addprefix $(SRC_DIR)/, $(SRC_FILES))

BUILD_DIR		:=	build
OBJS			:=	$(SRC_FILES:%.cpp=$(BUILD_DIR)/%.o)
DEPS			:=  $(SRC_FILES:%.cpp=$(BUILD_DIR)/%.d)
CXX_DEFS		:=	NAME=\"$(NAME)\"

CXX				:=	g++

CXX_FLAGS		:= -Wextra -Werror -Wall -std=c++17 -O2 -g3
CXX_LINKS		:= -L./lib
CXX_LIBS		:= -lglfw -lGLEW -lGL -ldl -lX11 -lpthread -lXrandr -lXi

CXX_HEADERS		:= -I./lib/GLEW/include -I./lib/GLFW/include -I./inc -I./inc/math


CXX_DEPS_FLAGS	:=	-MP -MMD
CXX_DEFS_FLAGS	:=	$(foreach def,$(CXX_DEFS),-D $(def))

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXX_FLAGS) $(CXX_HEADERS) $(CXX_LINKS) $(OBJS) $(CXX_LIBS) -o $@

-include $(DEPS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) $(CXX_DEPS_FLAGS) $(CXX_DEFS_FLAGS) $(CXX_HEADERS) -c $< -o $@

42:  all
	./$(NAME) resources/42.obj

teapot: all
	./$(NAME) resources/teapot.obj

clean:
	@rm -rf $(BUILD_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re 42 teapot
