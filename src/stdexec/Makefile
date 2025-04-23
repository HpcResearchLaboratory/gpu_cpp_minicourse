CXX = nvc++
CXXFLAGS = -std=c++20 -stdpar=gpu --experimental-stdpar

LDFLAGS = -lcudart

TARGET = stdexec_example

SRC = main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
