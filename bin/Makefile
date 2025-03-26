# Platform detection
ifeq ($(OS),Windows_NT)
    # Windows settings
    LIBS = -lglfw3dll -lopengl32
    EXE  = main.exe
    RUN  = .\$(EXE)
else
    # Linux / Unix-like settings
    LIBS = -lglfw -lGL -ldl
    EXE  = main
    RUN  = ./$(EXE)
endif

all:
	g++ -g -std=c++17 -I../headers -I../include -L../lib ../src/*.cpp ../src/glad.c $(LIBS) -o $(EXE)
	$(RUN)