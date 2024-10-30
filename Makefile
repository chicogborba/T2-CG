PROG = Basico3D

SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
BIN_DIR = bin

# Usando wildcard para selecionar todos os arquivos .cpp na pasta src
FONTES = $(wildcard $(SRC_DIR)/*.cpp)
OBJETOS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(FONTES))

CPPFLAGS = -g -O3 -DGL_SILENCE_DEPRECATION -Wno-write-strings -Wno-narrowing -I$(INC_DIR)

UNAME = $(shell uname)

all: $(BIN_DIR)/$(PROG)

$(BIN_DIR)/$(PROG): $(OBJETOS)
	@mkdir -p $(BIN_DIR)
ifeq ($(UNAME), Darwin)
	g++ $(OBJETOS) -O3 -framework OpenGL -framework Cocoa -framework GLUT -lm -o $(BIN_DIR)/$(PROG)
else
	g++ $(OBJETOS) -O3 -lGL -lGLU -lglut -lm -o $(BIN_DIR)/$(PROG)
endif

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	g++ $(CPPFLAGS) -c $< -o $@

test: all
	@$(BIN_DIR)/$(PROG)

clean:
	-@rm -f $(OBJETOS) $(BIN_DIR)/$(PROG)
	-@rm -rf $(BUILD_DIR) $(BIN_DIR)

vpath %.h $(INC_DIR)
