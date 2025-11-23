# Sistema de Registro de Ciudadanos
## Estructura de Datos Avanzada - Árbol B

### Descripción del Proyecto
Sistema de gestión de registros de ciudadanos que utiliza un **Árbol B** como estructura de datos principal para almacenar y buscar eficientemente hasta **33 millones de registros** por DNI.

### Características Principales
* ✅ Búsqueda eficiente por DNI en $O(\log n)$
* ✅ Inserción y eliminación en $O(\log n)$
* ✅ Persistencia de datos en formato binario
* ✅ Soporte para 33+ millones de registros
* ✅ Generación automática de datos sintéticos
* ✅ Benchmark de rendimiento incluido
* ✅ Análisis de complejidad temporal y espacial

---

## Estructura de Datos: Árbol B

El Árbol B es una estructura de datos balanceada que mantiene los datos ordenados y permite búsquedas, inserciones y eliminaciones en tiempo logarítmico.

### Características del Árbol B implementado:
* **Grado mínimo (T):** 128
* **Claves por nodo:** 127 a 255
* Auto-balanceo automático
* Optimizado para grandes volúmenes de datos

### Complejidad Algorítmica:
| Operación | Complejidad Temporal | Complejidad Espacial |
| :--- | :--- | :--- |
| Búsqueda | $O(\log n)$ | $O(1)$ |
| Inserción | $O(\log n)$ | $O(\log n)$ |
| Eliminación | $O(\log n)$ | $O(\log n)$ |

Donde $n$ = número de registros totales.

---

## Requisitos y Compilación

### Requisitos
* **Compilador:** `g++` con soporte C++11 o superior
* **Sistema Operativo:** Linux, macOS, o Windows (con MinGW)
* **RAM recomendada:** 8GB+ para manejar 33M registros
* **Espacio en disco:** ~5GB para 33M registros


