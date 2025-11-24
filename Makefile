# Makefile para el Sistema de Registro de Ciudadanos
# Estructura de Datos Avanzada - Árbol B

CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2 -Iinclude
TARGET = bin/registro_ciudadanos
SOURCES = src/main.cpp src/persona.cpp src/generador_datos.cpp src/persistencia.cpp src/ArbolB.cpp

# Regla principal
all: $(TARGET)

# Compilar el programa
$(TARGET): $(SOURCES)
	@echo "Compilando Sistema de Registro..."
	@mkdir -p bin data
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)
	@echo "✓ Compilación exitosa!"
	@echo "Ejecutar con: make run"

# Limpiar archivos compilados
clean:
	@echo "Limpiando archivos compilados..."
	rm -f $(TARGET)
	rm -f bin/*.o
	@echo "✓ Limpieza completada"

# Limpiar también los datos
clean-all: clean
	@echo "Eliminando archivos de datos..."
	rm -f data/*.csv
	rm -f data/*.bin
	rm -f data/*.dat
	@echo "✓ Datos eliminados"

# Ejecutar el programa
run: $(TARGET)
	@echo "Iniciando Sistema de Registro..."
	@echo ""
	./$(TARGET)

# Ejecutar con valgrind para detectar memory leaks
valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

# Compilar con información de debug
debug: CXXFLAGS += -g -DDEBUG
debug: clean $(TARGET)
	@echo "✓ Compilado en modo debug"

# Información del proyecto
info:
	@echo "========================================="
	@echo "  Sistema de Registro de Ciudadanos"
	@echo "  Estructura: Árbol B"
	@echo "========================================="
	@echo "Comandos disponibles:"
	@echo "  make         - Compilar el proyecto"
	@echo "  make run     - Compilar y ejecutar"
	@echo "  make clean   - Limpiar archivos compilados"
	@echo "  make clean-all - Limpiar todo (incluye datos)"
	@echo "  make debug   - Compilar en modo debug"
	@echo "  make valgrind - Verificar memory leaks"
	@echo "========================================="

.PHONY: all clean clean-all run valgrind debug info