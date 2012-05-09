# Mac OSX Makefile

EXECUTABLE    := OpenCLInvent

CCFILES = clutils.cpp main.cpp

CXX = g++ -O3

# opencl mac osx flag
OCLFLAG = -framework openCL

# Warning flags
CXXWARN_FLAGS := -W -Wall

all :
	@echo "+----- Compilation"
	$(CXX) $(CXXWARN_FLAGS) $(CCFILES) -o $(EXECUTABLE) $(OCLFLAG)
	@echo "+----- Execution"
	./$(EXECUTABLE)



