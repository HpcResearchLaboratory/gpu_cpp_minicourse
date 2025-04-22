CXX = nvc++

CXXFLAGS = -std=c++11 -Wall
OACC_FLAGS = -acc -gpu=cc70 -Minfo=accel
OMP_FLAGS = -mp -Minfo=mp
OPT_FLAGS = -O3

TARGETS = saxpy_serial saxpy_oacc saxpy_omp

all: $(TARGETS)

saxpy_serial: saxpy_serial.cpp
	$(CXX) $(CXXFLAGS) $(OPT_FLAGS) -o $@ $^

saxpy_oacc: saxpy_oacc.cpp
	$(CXX) $(CXXFLAGS) $(OACC_FLAGS) $(OPT_FLAGS) -o $@ $^

saxpy_omp: saxpy_omp.cpp
	$(CXX) $(CXXFLAGS) $(OMP_FLAGS) $(OPT_FLAGS) -o $@ $^

clean:
	rm -f $(TARGETS)

.PHONY: all clean
