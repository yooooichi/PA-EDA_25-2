#include <iostream>

const int T = 3; // Grado mínimo del árbol B

/**
 * BTree
 * Implementa un Árbol-B (B-Tree) de grado T.
 *
 * Esta clase actúa como la interfaz pública y el manejador principal
 * del Árbol-B. Gestiona el puntero a la raíz y orquesta las
 * operaciones de inserción y eliminación. La lógica recursiva
 * principal se delega en la clase anidada privada BTreeNode.
 */
class BTree {
private:

    /**
     * BTreeNode
     * Representa un solo nodo dentro del Árbol-B.
     *
     * Esta clase anidada privada contiene la lógica recursiva para
     * todas las operaciones del árbol (inserción, borrado, recorrido).
     * Un nodo puede ser una hoja o un nodo interno.
     */
    class BTreeNode { //ahora BtreeNode es una clase anidada dentro de BTree
    public:

        // Puntero a un array de claves. Tamaño máximo es (2*T - 1)
        int *keys;

        // Puntero a un array de punteros a nodos hijos. Tamaño máximo es (2*T)
        BTreeNode **C;

        // Número *actual* de claves almacenadas en este nodo.
        // (Debe estar entre T-1 y 2*T-1, salvo para la raíz).
        int n;

        // Es true si este nodo es una hoja, false si es un nodo interno
        bool leaf;

        /**
         * Constructor de BTreeNode.
         * param _leaf Verdadero si el nodo a crear es una hoja.
         */
        BTreeNode(bool _leaf);

        /**
         * Destructor de BTreeNode.
         * Libera la memoria de los arrays 'keys' y 'C', y llama
         * recursivamente al destructor de todos sus hijos.
         */
        ~BTreeNode();

        // Declaraciones de Métodos
        void traverse();
        void insertNonFull(int k);
        void splitChild(int i, BTreeNode *y);
        void remove(int k);
        int findKey(int k);
        void removeFromLeaf(int idx);
        void removeFromNonLeaf(int idx);
        int getPred(int idx);
        int getSucc(int idx);
        void fill(int idx);
        void borrowFromPrev(int idx);
        void borrowFromNext(int idx);
        void merge(int idx);

    };

    // Puntero al nodo raíz del árbol.
    BTreeNode *root;

    // Grado mínimo del Árbol-B
    int t;

public:

    /**
     * Constructor de BTree.
     * Inicializa un árbol vacío.
     */
    BTree() {
        root = nullptr;
        t = T;
    }

    /**
     * Destructor de BTree.
     * Inicia la destrucción recursiva del árbol llamando al
     * destructor del nodo raíz.
     */
    ~BTree() {
        if(root != nullptr)
            delete root; // inicia la destrucción recursiva
    }

    // Declaraciones de Métodos Públicos
    void traverse() {
        if (root != nullptr) root->traverse();
    }

    void insert(int k);
    void remove(int k);
};

// ------------------ Métodos de BTreeNode ------------------
// se agrega el prefijo 'BTree::' para indicar que BTreeNode es una clase anidada dentro de BTree
BTree::BTreeNode::BTreeNode(bool _leaf) {
    leaf = _leaf;
    keys = new int[2 * T - 1];
    C = new BTreeNode *[2 * T];
    n = 0;
}

// destructor de BTreeNode
BTree::BTreeNode::~BTreeNode() {
    // se libera la memoria de los nodos hijos recursivamente
    if (!leaf) {
        for (int i = 0; i <= n; i++) {
            // C[i] es un puntero a otro BTreeNode
            // al hacer 'delete', se llamará a su propio destructor.
            delete C[i];
        }
    }
    // liberar la memoria de los arrays de este nodo
    delete[] keys;
    delete[] C;
}

// BTree::BTreeNode::traverse
/**
 * Recorre (imprime) el subárbol en orden (in-order).
 *
 * Para un nodo, visita recursivamente el hijo izquierdo, luego
 * imprime la clave, y luego visita recursivamente el hijo derecho.
 */
void BTree::BTreeNode::traverse() {
    int i;
    // 1. recorrer los primeros 'n' hijos
    for (i = 0; i < n; i++) {
        // Si no es hoja, visitar el subárbol C[i] antes de imprimir keys[i]
        if (!leaf)
            C[i]->traverse();
            
        // Imprimir la clave    
        std::cout << " " << keys[i];
    }

    // 2. recorrer el último hijo (C[n])
    if (!leaf)
        C[n]->traverse();
}

// BTree::insert
/**
 * Método público para insertar una clave en el árbol.
 *
 * Esta función maneja los dos casos especiales para la raíz:
 * 1. Si el árbol está vacío (root es null), crea una nueva raíz.
 * 2. Si la raíz está llena, divide la raíz y crea una nueva raíz
 * antes de llamar a insertNonFull.
 *
 * En todos los demás casos, delega el trabajo a BTreeNode::insertNonFull.
 * parametro: k La clave a insertar.
 */
void BTree::insert(int k) {
    // Caso 1: El árbol está vacío.
    if (root == nullptr) {
        // Crear un nuevo nodo raíz (que es una hoja)
        root = new BTreeNode(true);
        root->keys[0] = k; // Insertar la clave
        root->n = 1;       // Tiene 1 clave
    } else {
        // Caso 2: La raíz está llena (2*T - 1 claves)
        if (root->n == 2 * t - 1) {
            // La raíz debe dividirse. La altura del árbol crecerá en 1

            // 1. Crear una nueva raíz 's' (que no es una hoja)
            BTreeNode *s = new BTreeNode(false);

            // 2. 's' se convierte en el padre de la antigua raíz 'root'
            s->C[0] = root;

            // 3. Dividir la antigua raíz 'root' y mover la clave mediana a 's'
            s->splitChild(0, root);

            // 4. Decidir a cuál de los dos hijos de 's' debe descender
            //    la nueva clave 'k'
            int i = 0;
            if (s->keys[0] < k)
                i++; // Descender al hijo C[1]
            s->C[i]->insertNonFull(k);

            // 5. Actualizar el puntero 'root' del árbol
            root = s;
        } else{
            // Caso 3: La raíz no está llena.
            // Llamar a la función recursiva para insertar.
            root->insertNonFull(k);
        }
    }
}

// BTree::BTreeNode::insertNonFull
/**
 * Inserta una clave 'k' en un nodo que *no* está lleno.
 *
 * Esta es la función recursiva principal para la inserción.
 * se asume que el nodo actual no está lleno
 *
 * parametro: k La clave a insertar.
 */
void BTree::BTreeNode::insertNonFull(int k) {
    // 1. Encontrar la posición correcta para la clave
    int i = n - 1; // Empezar desde la clave más a la derecha

    // Caso A: Este nodo es una HOJA
    if (leaf) { 
        // 2a. Desplazar todas las claves mayores que 'k' una posición a la derecha
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }
        // 3a. Insertar la nueva clave 'k' en la posición encontrada
        keys[i + 1] = k;
        n++; // Incrementar el contador de claves
    } 
    // Caso B: Este nodo es INTERNO
    else {
        // 2b. Encontrar el hijo (C[i+1]) al que debemos descender
        while (i >= 0 && keys[i] > k)
            i--;
        // 3b. (ESTA ES LA CLAVE) Verificar si el hijo C[i+1] está lleno
        if (C[i + 1]->n == 2 * T - 1) {
            // 4b. Si el hijo está lleno, dividirlo (Split)
            splitChild(i + 1, C[i + 1]);
            // 5b. Después del split, la clave mediana subió al nodo actual.
            //     Debemos decidir de nuevo a cuál de los dos nuevos hijos
            //     descender (el original o el nuevo)
            if (keys[i + 1] < k)
                i++;
        }
        // 6b. Descender recursivamente al hijo apropiado (que ahora
        //     sabemos que *no* está lleno).
        C[i + 1]->insertNonFull(k);
    }
}

// BTree::BTreeNode::splitChild
/**
 * Divide el hijo 'y' (que está lleno) de este nodo.
 *
 * 'this' es el nodo padre (que no está lleno).
 * 'y' (en C[i]) es el hijo que sí está lleno.
 * La operación mueve la clave mediana de 'y' a 'this' y divide
 * 'y' en dos nodos (el 'y' original y uno nuevo 'z').
 *
 * parametro i: Índice del hijo 'y' en el array C (es decir, C[i] == y).
 * parametro y: Puntero al nodo hijo (en C[i]) que debe ser dividido.
 */
void BTree::BTreeNode::splitChild(int i, BTreeNode *y) {
    // 1. Crear un nuevo nodo 'z'. Será el "hermano derecho" de 'y'.
    //    Tendrá la misma propiedad 'leaf' que 'y'
    BTreeNode *z = new BTreeNode(y->leaf);
    z->n = T - 1; // El nuevo nodo 'z' tendrá T-1 claves

    // 2. Copiar las (T-1) claves "superiores" de 'y' al nuevo nodo 'z'
    for (int j = 0; j < T - 1; j++)
        z->keys[j] = y->keys[j + T]; // Claves desde la posición T en adelante

    // 3. Si 'y' no es una hoja, copiar los 'T' hijos "superiores" de 'y' a 'z'
    if (!y->leaf) {
        for (int j = 0; j < T; j++)
            z->C[j] = y->C[j + T]; // Hijos desde la posición T en adelante
    }

    // 4. Actualizar el contador de claves de 'y'. Ahora solo tiene T-1 claves
    y->n = T - 1;

    // 5. Desplazar los punteros a hijos en 'this' (el nodo padre)
    //    para hacer espacio para el nuevo hijo 'z'
    for (int j = n; j >= i + 1; j--)
        C[j + 1] = C[j];

    // 6. Conectar 'z' como el nuevo hijo en la posición i+1
    C[i + 1] = z;

    // 7. Desplazar las claves en 'this' (el nodo padre) para
    //    hacer espacio para la clave mediana de 'y'
    for (int j = n - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    // 8. Copiar la clave mediana de 'y' (la clave en T-1) a 'this'
    keys[i] = y->keys[T - 1];

    // 9. Incrementar el contador de claves en 'this'
    n++;
}

// ------------------ Eliminación ------------------

// BTree::remove
/**
 * Método público para eliminar una clave del árbol.
 *
 * Esta función es el punto de entrada. Maneja el caso de un
 * árbol vacío y el caso especial post-eliminación donde la raíz
 * queda vacía (encogimiento del árbol).
 *
 * parametro k: La clave a eliminar.
 */
void BTree::remove(int k) {
    if (!root) {
        std::cout << "Árbol vacío\n";
        return;
    }

    // 1. Iniciar la eliminación recursiva desde la raíz.
    root->remove(k);

    // 2. (Caso Especial) Manejar el encogimiento de la raíz.
    // Si la raíz 'root' se quedó sin claves (n==0) después de la
    // eliminación (probablemente por un 'merge' de sus hijos)
    if (root->n == 0) {
        BTreeNode *tmp = root;
        // 2a. Si la raíz era una hoja, el árbol está vacío.
        if (root->leaf){
            root = nullptr;
        }
        // 2b. Si la raíz era interna, su único hijo (C[0])
        //     se convierte en la nueva raíz. La altura del árbol
        //     disminuye en 1
        else {
            root = root->C[0];
        }

        // se desconecta el hijo C[0] de la antigua raíz 'tmp'
        // para evitar que el destructor de 'tmp' lo borre.
        if (!tmp->leaf)
            tmp->C[0] = nullptr;

        // 3. se borra la antigua raíz vacía
        delete tmp;
    }
}

// BTree::BTreeNode::remove
/**
 * Método recursivo principal para eliminar una clave 'k'.
 *
 * Esta función implementa la lógica principal de eliminación,
 * dividida en 3 casos basados en la ubicación de 'k'.
 *
 * parametro k: La clave a eliminar.
 */
void BTree::BTreeNode::remove(int k) {
    // 1. Encontrar el índice 'idx' de la clave 'k' o del
    //    subárbol donde 'k' debería estar.
    int idx = findKey(k);

    // --- CASO 1: La clave 'k' se encuentra en ESTE nodo ---
    if (idx < n && keys[idx] == k) {
        if (leaf)
            // Caso 1a: El nodo es una HOJA
            removeFromLeaf(idx);
        else
            // Caso 1b: El nodo es INTERNO
            removeFromNonLeaf(idx);
    } 
    // --- CASO 2: La clave 'k' NO se encuentra en este nodo ---
    else {
        // Caso 2a: Este nodo es una HOJA.
        // Si la clave no está aquí y es una hoja, no existe.
        if (leaf) {
            std::cout << "La clave " << k << " no existe\n";
            return;
        }

        // Caso 2b: Este nodo es INTERNO.
        // La clave 'k' puede estar en el subárbol C[idx].

        // se guarda si 'k' está en el último hijo (C[n]).
        // Esto es importante si C[idx] se fusiona (merge).
        bool flag = (idx == n);

        // 3. Antes de descender al hijo C[idx], se asegura de que
        //    C[idx] tenga al menos 'T' claves
        if (C[idx]->n < T)
            fill(idx);

        // 4. Si 'flag' era true, 'idx' era 'n'.
        //    Si 'fill(idx)' provocó un 'merge(idx-1)', 'n'
        //    se decrementó. 'idx' ahora es > 'n'.
        //    Debemos descender al nodo fusionado C[idx-1].
        if (flag && idx > n)
            C[idx - 1]->remove(k);
        // 5. De lo contrario, descender al hijo C[idx] (que ahora
        //    sabemos que tiene al menos T claves)
        else
            C[idx]->remove(k);
    }
}

// --- En BTree::BTreeNode::findKey ---
/**
 * Encuentra el índice de la primera clave >= k.
 *
 * Realiza una búsqueda lineal en el array de claves.
 *
 * parametro k: La clave a buscar.
 * retorna int: El índice 'idx' tal que 'idx' es el primer
 * índice donde keys[idx] >= k, o 'n' si k > todas las claves.
 */
int BTree::BTreeNode::findKey(int k) {
    int idx = 0;
    // Incrementar 'idx' mientras la clave en 'idx' sea menor que 'k'
    while (idx < n && keys[idx] < k)
        ++idx;
    return idx;
}

void BTree::BTreeNode::removeFromLeaf(int idx) {
    for (int i = idx + 1; i < n; ++i)
        keys[i - 1] = keys[i];
    n--;
}

void BTree::BTreeNode::removeFromNonLeaf(int idx) {
    int k = keys[idx];

    if (C[idx]->n >= T) {
        int pred = getPred(idx);
        keys[idx] = pred;
        C[idx]->remove(pred);
    } else if (C[idx + 1]->n >= T) {
        int succ = getSucc(idx);
        keys[idx] = succ;
        C[idx + 1]->remove(succ);
    } else {
        merge(idx);
        C[idx]->remove(k);
    }
}

int BTree::BTreeNode::getPred(int idx) {
    BTreeNode *cur = C[idx];
    while (!cur->leaf)
        cur = cur->C[cur->n];
    return cur->keys[cur->n - 1];
}

int BTree::BTreeNode::getSucc(int idx) {
    BTreeNode *cur = C[idx + 1];
    while (!cur->leaf)
        cur = cur->C[0];
    return cur->keys[0];
}

void BTree::BTreeNode::fill(int idx) {
    if (idx != 0 && C[idx - 1]->n >= T)
        borrowFromPrev(idx);
    else if (idx != n && C[idx + 1]->n >= T)
        borrowFromNext(idx);
    else {
        if (idx != n)
            merge(idx);
        else
            merge(idx - 1);
    }
}

void BTree::BTreeNode::borrowFromPrev(int idx) {
    BTreeNode *child = C[idx];
    BTreeNode *sibling = C[idx - 1];

    for (int i = child->n - 1; i >= 0; --i)
        child->keys[i + 1] = child->keys[i];

    if (!child->leaf) {
        for (int i = child->n; i >= 0; --i)
            child->C[i + 1] = child->C[i];
    }

    child->keys[0] = keys[idx - 1];

    if (!child->leaf)
        child->C[0] = sibling->C[sibling->n];

    keys[idx - 1] = sibling->keys[sibling->n - 1];

    child->n += 1;
    sibling->n -= 1;
}

void BTree::BTreeNode::borrowFromNext(int idx) {
    BTreeNode *child = C[idx];
    BTreeNode *sibling = C[idx + 1];

    child->keys[child->n] = keys[idx];

    if (!(child->leaf))
        child->C[child->n + 1] = sibling->C[0];

    keys[idx] = sibling->keys[0];

    for (int i = 1; i < sibling->n; ++i)
        sibling->keys[i - 1] = sibling->keys[i];

    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->n; ++i)
            sibling->C[i - 1] = sibling->C[i];
    }

    child->n += 1;
    sibling->n -= 1;
}

void BTree::BTreeNode::merge(int idx) {
    BTreeNode *child = C[idx];
    BTreeNode *sibling = C[idx + 1];

    child->keys[T - 1] = keys[idx];

    for (int i = 0; i < sibling->n; ++i)
        child->keys[i + T] = sibling->keys[i];

    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; ++i){
            child->C[i + T] = sibling->C[i]; //'child' adopta al hijo C[i] de 'sibling'

            // se 'desconecta' al hijo de 'sibling'
            // para que el destructor de 'sibling' no lo borre
            sibling->C[i] = nullptr; 
        }
    }

    for (int i = idx + 1; i < n; ++i)
        keys[i - 1] = keys[i];

    for (int i = idx + 2; i <= n; ++i)
        C[i - 1] = C[i];

    child->n += sibling->n + 1;
    n--;

    delete sibling;
}

int main(){
    BTree w;

    w.insert(30);
    w.insert(60);
    w.insert(10);
    w.insert(20);
    w.insert(40);
    w.insert(50);
    w.insert(70);
    w.insert(80);
    w.insert(1);
    w.insert(5);
    w.insert(11);
    w.insert(15);
    w.insert(21);
    w.insert(25);
    w.insert(31);
    w.insert(35);
    w.insert(41);
    w.insert(45);
    w.insert(51);
    w.insert(55);
    w.insert(61);
    w.insert(65);
    w.insert(71);
    w.insert(75);
    w.insert(81);
    w.insert(85);
    w.remove(10);
    
    w.traverse();
}

