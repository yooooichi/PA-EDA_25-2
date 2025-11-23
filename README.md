Sistema de Registro de Ciudadanos
Estructura de Datos Avanzada - Árbol B
Descripción del Proyecto
Sistema de gestión de registros de ciudadanos que utiliza un Árbol B como estructura de datos principal para almacenar y buscar eficientemente hasta 33 millones de registros por DNI.

Características Principales
✅ Búsqueda eficiente por DNI en O(log n)
✅ Inserción y eliminación en O(log n)
✅ Persistencia de datos en formato binario
✅ Soporte para 33+ millones de registros
✅ Generación automática de datos sintéticos
✅ Benchmark de rendimiento incluido
✅ Análisis de complejidad temporal y espacial
Estructura de Datos: Árbol B
El Árbol B es una estructura de datos balanceada que mantiene los datos ordenados y permite búsquedas, inserciones y eliminaciones en tiempo logarítmico.

Características del Árbol B implementado:

Grado mínimo (T): 128
Claves por nodo: 127 a 255
Auto-balanceo automático
Optimizado para grandes volúmenes de datos
Complejidad Algorítmica:

Operación	Complejidad Temporal	Complejidad Espacial
Búsqueda	O(log n)	O(1)
Inserción	O(log n)	O(log n)
Eliminación	O(log n)	O(log n)
Donde n = número de registros totales

Estructura del Proyecto
proyecto/
├── include/
│   ├── persona.h           # Clase Persona
│   ├── generador_datos.h   # Generador de datos sintéticos
│   ├── persistencia.h      # Manejo de archivos
│   └── arbol_b.h           # Implementación del Árbol B
├── src/
│   ├── main.cpp            # Programa principal
│   ├── persona.cpp
│   ├── generador_datos.cpp
│   ├── persistencia.cpp
│   └── arbol_b.cpp
├── data/                   # Archivos de datos (se crea automáticamente)
├── bin/                    # Ejecutables (se crea automáticamente)
├── Makefile
└── README.md
Requisitos
Compilador: g++ con soporte C++11 o superior
Sistema Operativo: Linux, macOS, o Windows (con MinGW)
RAM recomendada: 8GB+ para manejar 33M registros
Espacio en disco: ~5GB para 33M registros
Instalación y Compilación
1. Clonar o descargar el proyecto
bash
cd proyecto/
2. Compilar el proyecto
bash
make
3. Ejecutar el programa
bash
make run
Uso del Sistema
Al ejecutar el programa, verás un menú interactivo:

========================================
              MENÚ PRINCIPAL
========================================
1. Generar nuevos registros
2. Buscar ciudadano por DNI
3. Insertar un registro manualmente
4. Eliminar un registro
5. Mostrar estadísticas del sistema
6. Realizar benchmark (pruebas de rendimiento)
7. Guardar y salir
========================================
Guía de Uso
Generar Registros (Opción 1)
Selecciona la cantidad de registros a generar
Recomendación: Genera en lotes de 100,000 - 1,000,000
El sistema guarda automáticamente después de cada generación
Para llegar a 33M registros, ejecuta varias veces
Buscar por DNI (Opción 2)
Ingresa un DNI de 8 dígitos
El sistema mostrará el tiempo de búsqueda en microsegundos
Si existe, mostrará todos los datos del ciudadano
Realizar Benchmark (Opción 6)
Ejecuta pruebas de rendimiento automáticas:

1000 búsquedas aleatorias
100 inserciones
100 eliminaciones
Muestra tiempos promedio y análisis de memoria
Persistencia de Datos
El sistema guarda automáticamente los datos en formato binario en:

data/registro_ciudadanos.bin
Ventajas del formato binario:

Carga y guardado más rápido que CSV
Menor tamaño de archivo
Preserva la estructura de datos exactamente
Al reiniciar el programa, los datos se cargan automáticamente desde disco.

Análisis de Complejidad
Complejidad Temporal
Para un árbol con grado mínimo T=128 y n registros:

Altura del árbol: h = log₁₂₈(n)
Para 33M registros: h ≈ 3.7 ≈ 4 niveles
Búsqueda: Máximo 4 accesos a nodos
Tiempo real: < 100 microsegundos
Complejidad Espacial
Por registro: ~200-300 bytes (objeto Persona)
Por nodo: ~20KB (arrays de claves y punteros)
33M registros: ~8-10 GB de RAM
Nodos internos: ~130,000 nodos × 20KB ≈ 2.5 GB
Benchmarking
El sistema incluye herramientas de benchmarking que miden:

Tiempo de búsqueda: Promedio en microsegundos
Tiempo de inserción: Promedio en microsegundos
Tiempo de eliminación: Promedio en microsegundos
Uso de memoria: Estimación en MB
Tasa de éxito: Búsquedas exitosas vs totales
Resultados esperados para 33M registros:

Búsqueda: 50-100 µs
Inserción: 100-200 µs
Eliminación: 100-200 µs
Comparación con Otras Estructuras
Estructura	Búsqueda	Inserción	Espacio	Persistencia
Array ordenado	O(log n)	O(n)	O(n)	Fácil
Lista enlazada	O(n)	O(1)	O(n)	Fácil
Árbol Binario	O(n)*	O(n)*	O(n)	Compleja
Hash Table	O(1)**	O(1)**	O(n)	Difícil
Árbol B	O(log n)	O(log n)	O(n)	Moderada
* Caso peor sin balanceo
** Promedio, peor caso O(n)

Ventajas del Árbol B para este proyecto:

Balanceo automático garantizado
Excelente para grandes volúmenes
Ordenamiento natural por clave
Persistencia relativamente simple
Escalable a más de 33M registros
Comandos Útiles
bash
# Compilar
make

# Ejecutar
make run

# Limpiar archivos compilados
make clean

# Limpiar todo (incluye datos)
make clean-all

# Compilar en modo debug
make debug

# Verificar memory leaks
make valgrind

# Ver información
make info
Solución de Problemas
Error: "No se pudo abrir el archivo"
Verifica que existe el directorio data/
Ejecuta: mkdir -p data
Error de memoria al cargar 33M registros
Incrementa la RAM disponible
Carga en lotes más pequeños
Reduce el grado T del árbol
Compilación lenta
Normal para archivos grandes
Usa -O2 flag (ya incluido en Makefile)
Primera compilación es más lenta
Trabajo Futuro
Posibles mejoras:

 Interfaz gráfica (GUI)
 Búsqueda por otros campos (nombre, ubicación)
 Índices secundarios
 Compresión de datos
 Paralelización de operaciones
 API REST para acceso remoto
Autores
Grupo [NÚMERO 4]

BORDA BERNAOLA, RONALD MELITON
CASO EGOAVIL, PEDRO YUICHI
CHANCA MELGAR, YAREL JOSHUA
FERNANDEZ TOTOCAYO, HENRY DANIEL
Curso: Estructura de Datos Avanzada
Institución: [USIL]
Año: 2025

Referencias
Cormen, T. H., et al. (2009). "Introduction to Algorithms" (3rd ed.). MIT Press.
Bayer, R., & McCreight, E. (1972). "Organization and Maintenance of Large Ordered Indices". Acta Informatica.
Knuth, D. E. (1998). "The Art of Computer Programming, Vol. 3: Sorting and Searching" (2nd ed.).
Licencia
Este proyecto es parte de un trabajo académico para el curso de Estructura de Datos Avanzada.

Nota: Este sistema está diseñado para fines educativos y de investigación. Para un sistema de producción real, considere usar bases de datos profesionales como PostgreSQL o MongoDB.

