CXX = g++
CXXFLAGS = -std=c++11 -Iinclude
TARGET = bin/programa
SOURCES = src/main.cpp src/persona.cpp src/generador_datos.cpp src/persistencia.cpp

$(TARGET):
	mkdir -p bin data
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)
	rm -f data/datos.csv

run: $(TARGET)
	./$(TARGET)

.PHONY: clean run