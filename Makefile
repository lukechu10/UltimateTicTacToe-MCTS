SRC_DIR := ./
OBJ_DIR := ./obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
LDFLAGS :=
CPPFLAGS := -Wall -g -Ofast
CXXFLAGS := 
EXECUTABLE := $(OBJ_DIR)/main.out

all: $(EXECUTABLE)

$(OBJ_DIR)/main.out: $(OBJ_FILES)
	g++ $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p obj
	g++ $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -r obj

.PHONY: run
run:
	@echo "\nRunning program:\n"
	@$(OBJ_DIR)/main.out

CXXFLAGS += -MMD
-include $(OBJ_FILES:.o=.d)