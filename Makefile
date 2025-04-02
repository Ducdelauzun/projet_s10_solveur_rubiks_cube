CXX = g++
CXXFLAGS = -std=c++17 -O3 -Iinclude -Iinclude/kociemba

SRCDIR = src/kociemba
BINDIR = bin

SRC_SOLVER = src/test_solver.cpp \
      $(SRCDIR)/CubeParser.cpp \
      $(SRCDIR)/FaceletCube.cpp \
      $(SRCDIR)/Solver.cpp \
      $(SRCDIR)/RubiksCube.cpp \
      $(SRCDIR)/Cube.cpp \
      $(SRCDIR)/Combinatorics.cpp \
      $(SRCDIR)/Vector.cpp \
      $(SRCDIR)/MoveTable.cpp \
      $(SRCDIR)/PruningTable.cpp \

TARGET_SOLVER = $(BINDIR)/test_solver

all: $(TARGET_SOLVER)

test_solver: $(TARGET_SOLVER)

$(TARGET_SOLVER): $(SRC_SOLVER)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(TARGET_SOLVER)