CFLAGS=-03 -Wall --std=c++23

CC=/opt/homebrew/opt/llvm@21/bin/clang++

all: main.cpp
	@echo "Compiling main.cpp"
	@ $(CC) main.cpp -o x.out
	@chmod +x x.out
	@echo "main.cpp compiled successfully"

clean:
	@echo "Cleaning..."
	@rm x.out a.out
	@echo "Clean done"
