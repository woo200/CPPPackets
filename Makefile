# Variables
CXX = g++
# leave debug symbols 
CXXFLAGS = -std=c++11 -Wall -Wextra -O2 
LDFLAGS = 
OBJ_DIR = obj
BIN = tests
SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Rules
build: directories $(OBJ)
lib: directories $(OBJ)
	$(CXX) $(OBJ) -shared -o lib$(BIN).so $(LDFLAGS)

test: build $(BIN)

directories: $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN): $(OBJ)
	$(CXX) $(OBJ) -o $(BIN) $(LDFLAGS)

$(OBJ_DIR)/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(BIN)
