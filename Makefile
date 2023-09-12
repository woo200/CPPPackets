# Variables
CXX = g++
# leave debug symbols 
CXXFLAGS = -std=c++11 -Wall -Wextra -O2 
LDFLAGS = 
OBJ_DIR = obj
HEADER_DIR = include
BIN = packets
SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

TEST_SRC = $(wildcard test/*.cpp)
TEST_OBJ = $(TEST_SRC:test/%.cpp=$(OBJ_DIR)/%.o)

lib: directories $(OBJ) headers
	$(CXX) $(OBJ) -shared -o lib$(BIN).so $(LDFLAGS)

test: lib $(BIN)
directories: $(OBJ_DIR) $(HEADER_DIR)

headers:
	cp src/*.hpp $(HEADER_DIR)

install:
	cp lib$(BIN).so /usr/local/lib
	cp $(HEADER_DIR)/*.hpp /usr/local/include

uninstall:
	rm -rf /usr/local/lib/lib$(BIN).so

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
$(HEADER_DIR):
	mkdir -p $(HEADER_DIR)

$(BIN): $(TEST_OBJ)
	$(CXX) $(TEST_OBJ) -o $(BIN) $(LDFLAGS) -L. -l$(BIN)

$(OBJ_DIR)/%.o: test/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(BIN) $(HEADER_DIR) lib$(BIN).so
