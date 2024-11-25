PROG = Basico3D

SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
BIN_DIR = bin
LIB_DIR = lib
SOIL_DIR = $(LIB_DIR)/SOIL

# Usando wildcard para selecionar todos os arquivos .cpp na pasta src
FONTES_CPP = $(wildcard $(SRC_DIR)/*.cpp)
FONTES_C = $(wildcard $(SOIL_DIR)/*.c)

# Objetos correspondentes
OBJETOS_CPP = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(FONTES_CPP))
OBJETOS_C = $(patsubst $(SOIL_DIR)/%.c, $(BUILD_DIR)/%.o, $(FONTES_C))
OBJETOS = $(OBJETOS_CPP) $(OBJETOS_C)

# Flags comuns para ambos compiladores
COMMON_FLAGS = -g -O3 -DGL_SILENCE_DEPRECATION -Wno-write-strings -Wno-narrowing -I$(INC_DIR) -I$(SOIL_DIR)

# Flags específicas para C++
CPPFLAGS = $(COMMON_FLAGS) -std=c++17

# Flags específicas para C
CFLAGS = $(COMMON_FLAGS)

UNAME = $(shell uname)

all: $(BIN_DIR)/$(PROG)

$(BIN_DIR)/$(PROG): $(OBJETOS)
	@mkdir -p $(BIN_DIR)
ifeq ($(UNAME), Darwin)
	g++ $(OBJETOS) -O3 -framework OpenGL -framework Cocoa -framework GLUT -lm -o $(BIN_DIR)/$(PROG)
else
	g++ $(OBJETOS) -O3 -lGL -lGLU -lglut -lm -o $(BIN_DIR)/$(PROG)
endif

# Regra para compilar arquivos .c
$(BUILD_DIR)/%.o: $(SOIL_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	gcc $(CFLAGS) -c $< -o $@

# Regra para compilar arquivos .cpp
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	g++ $(CPPFLAGS) -c $< -o $@

test: all
	@$(BIN_DIR)/$(PROG)

clean:
	-@rm -f $(OBJETOS) $(BIN_DIR)/$(PROG)
	-@rm -rf $(BUILD_DIR) $(BIN_DIR)

vpath %.h $(INC_DIR) $(SOIL_DIR)