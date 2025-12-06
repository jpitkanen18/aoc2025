CFLAGS=-O3 -Wall --std=c++23 -fopenmp 
#-fsanitize=address
INCLUDE=-I/opt/homebrew/Cellar/libomp/21.1.7/include

CC=/opt/homebrew/opt/llvm@21/bin/clang++ $(CFLAGS) $(INCLUDE)

all: main.cpp
	@echo "Compiling main.cpp"
	@ $(CC) main.cpp -o x.out
	@chmod +x x.out
	@echo "main.cpp compiled successfully"

clean:
	@echo "Cleaning..."
	@rm x.out a.out
	@echo "Clean done"
