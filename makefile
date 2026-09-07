CXX = g++
CXXFLAGS = -std=c++11 -Wall -Iinclude
TARGET = taskforge
SRC = $(wildcard src/*.cpp)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
	clear
	@echo "Cleaned.🌞"

run: $(TARGET)
	./$(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)