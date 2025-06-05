#include <iostream>

/**
 * El nodo representa un puesto de avanzada. Los puestos de avanzada existen en el mundo postapocaliptico del Refugio 33, y se
 * encuentran distribuidos a lo largo del mapa.
 * 
 * outpostId: Es el identificador único del puesto de avanzada.
 * prority: Cada puesto de avanzada tiene una prioridad estratégica basada en diversos factores. 
 */
struct Nodo {
    int outpostId;
    int priority;
    Nodo* izq;
    Nodo* der;

    Nodo(int id) : outpostId(id), priority(1), izq(nullptr), der(nullptr) {}
};

class AVLTree {
    public:
        AVLTree();
        ~AVLTree();

        void insert(int outpostId);
        bool contains(int outpostId);
        void remove(int outpostId);

    private:
        Nodo* raiz; // Cuando se instancia, raiz = nullptr (declarado en el constructor)
        
        /**
         * @brief Este método se encarga de insertar un nuevo puesto de avanzada (nodo) al Arbol AVL, estructura donde 
         * se hace el control de los puestos de avanzada.
         *
         * @param nodo Para insertar un nuevo nodo al arbol se le debe pasar cual será su nodo padre. Normalmente se le pasará
         * la raíz como este parámetro, aunque si se está usando en un caso de recursión nodo puedo ser algun sub-hijo.
         *
         * @param outpostId Es el identificador único del puesto de avanzada que se va a insertar al Arbol AVL. 
         *
         * */
        Nodo* insert(Nodo*& nodo, int outpostId);
        void liberar(Nodo* nodo);
        bool contains(Nodo* raiz, int outpostId);
        void remove(Nodo* raiz, int outpostId);
        
        // Métodos auxiliares
        int max(int n1, int n2) { return n1 > n2 ? n1 : n2; }
        void actualizarAltura(Nodo* nodo);
        int priority(Nodo* nodo);
        int balance(Nodo* nodo);
        Nodo* rotarDerecha(Nodo* nodo);
        Nodo* rotarIzquierda(Nodo* nodo);

       
};




