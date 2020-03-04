COMPILER = g++ # use g++ by default, switch to em++ for emscripten
SRC_DIR := ./
OBJ_DIR := ./obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
LDFLAGS :=
CPPFLAGS := -Wall --std=c++17
CXXFLAGS := 
EXECUTABLE := $(OBJ_DIR)/main.out

all: $(EXECUTABLE) run

em: COMPILER=em++
em: $(EXECUTABLE)

$(OBJ_DIR)/main.out: $(OBJ_FILES)
	$(COMPILER) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p obj
	$(COMPILER) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -r obj

.PHONY: run
run:
	@echo "\nRunning program:\n"
	@$(OBJ_DIR)/main.out

CXXFLAGS += -MMD
-include $(OBJ_FILES:.o=.d)