CXX       := emcc

BIN     := bin
SRC     := src
INCLUDE := include

LIBRARIES   :=
EXECUTABLE  := main


all: $(BIN)/$(EXECUTABLE)
	
run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*/*.cpp  bindings.cpp
					  $(CXX) $(CXX_FLAGS) --bind -I$(INCLUDE) $^ $(LIBRARIES) -O3 -s WASM=1 -s MODULARIZE=1 -s ALLOW_MEMORY_GROWTH=1 -o wasm/output.js

clean:
	-rm $(BIN)/*
