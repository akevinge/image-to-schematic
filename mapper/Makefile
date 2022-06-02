CCPP = g++-11
CCPP_FLAGS = -std=c++20 -g -O3
CCPP_FLAGS += -Ilib
CPP_SRC = $(wildcard src/*.cpp) $(wildcard src/**/*.cpp)

OBJS_DIR = objs
CPP_OBJ_FILES= $(foreach path, $(CPP_SRC:.cpp=.o), $(OBJS_DIR)/$(path))

BIN = bin

$(BIN):
	mkdir -p ./$(BIN)

$(OBJS_DIR)/%.o: %.cpp
	mkdir -p $(@D)
	$(CCPP) -c $< -o $@ $(CCPP_FLAGS)

build: $(BIN) $(CPP_OBJ_FILES)
	$(CCPP) -o $(BIN)/main $(CPP_OBJ_FILES) $(CCPP_FLAGS) 

run:
	$(BIN)/main

clean:
	rm -dfr $(OBJS_DIR) && rm -dfr $(BIN)

all: clean build run
