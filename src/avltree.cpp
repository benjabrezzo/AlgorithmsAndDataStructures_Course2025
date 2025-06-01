#include "avltree.hpp"

// Constructor y destructor
AVLTree::AVLTree() {
    raiz = nullptr;
}

// Para implementar el destructor primero se debe implementar un metodo que elimine Nodos del Arbol AVL


// Métodos públicos
void AVLTree::insert(int& outpostId) {
    // Llamamos al método privado, se le pasa la raiz.
    raiz = insert(raiz, outpostId);
}


// Métodos privados
Nodo* AVLTree::insert(Nodo*& nodo, int& outpostId) {
    // Este if se ejecutará en el caso de que sea el primer nodo a insertar (raiz == null), o en algún llamado de recursión
    // cuando se llega a la posición de un nodo hijo que sea null y que en el se pueda insertar el nuevo nodo.
    if(!nodo) {
        return new Nodo(outpostId);
    }

    // Sino, se evalúa el valor del ID para insertarlo en el sub-arbol izq. o der.
    if(outpostId < nodo->outpostId) {
        // Si es menor, se agrega a la izquierda, en este caso, el parámetro nodo es el puntero al nodo izquierdo de la raíz
        nodo->izq = insert(nodo->izq, outpostId);
    } else if(outpostId > nodo->outpostId) {
        // Si es mayor, se agrega a la derecha, en este caso, el parámetro nodo es el puntero al nodo der. de la raíz
        nodo->der = insert(nodo->der, outpostId);
    } else {
        // Sino es ni mayor ni meno quiere decir que es igual, pero no puede haber identificadores 
        // repetidos, entonces no se agrega. Se retorna el mismo valor de nodo que vino por parametro, dando a entender
        // que si era la raiz, esta permanece igual, o si era un nodo padre de algun sub arbol, el nodo padre tampoco 
        // cambiara
        return nodo;
    }

    // Una vez agregado un nuevo nodo al arbol AVL se debe calcular la nueva altura de este, y si esta fuera del 
    // rango [-1, 1] se debe balancear el arbol...
    // La altura en este arbol es representada por la priority
    actualizarAltura(nodo);
    
    // Ahora verificaremos si se encuentra en el rango [-1, 1], y si está fuera se debe balancear
    
    int balanceDelNodo = balance(nodo); 
    
    // Desbalanceo Left-Left: Hay un desbalance hacia la izquierda "doble".
    if (balanceDelNodo > 1 && outpostId < nodo->izq->outpostId) {
        // Retorna la nueva raiz que queda al hacer la rotacion
        return rotarDerecha(nodo); 
    } 

    // Desbalanceo Right-Right: Hay un desbalance hacia la derecha "doble".
    if(balanceDelNodo < -1 && outpostId > nodo->der->outpostId) {
        return rotarIzquierda(nodo);
    }
    
    // Desbalanceo Left-Right: La raiz esta desbalanceada a la izquierda, y el sub arbol izq esta desbalanceado a la derecha 
    if(balanceDelNodo > 1 && outpostId > nodo->izq->outpostId) {
        nodo->izq = rotarIzquierda(nodo->izq);
        return rotarDerecha(nodo);
    }
   
    // Desbalanceo Right-Left: La raíz está desbalanceada a la derecha, y el sub arbol der está desbalanceado a la izquierda 
    if(balanceDelNodo < -1 && outpostId < nodo->der->outpostId) {
        nodo->der = rotarDerecha(nodo->der);
        return rotarIzquierda(nodo);
    }

    // Si el balance esta dentro de [-1, 1] no hay que hacer ninguna rotacion, se devuelve el nodo que llego como parametro
    // que en ocasiones sera la raiz o un nodo padre en algun caso de recursion 
    return nodo;
}


// Métodos auxiliares
Nodo* AVLTree::rotarDerecha(Nodo* nodo) {
    // Para razonar y comprender el metodo supongamos que el nodo es la raiz, es el caso de una raiz con un sub-arbol izquierdo
    // y se agrego otro dato menor que el sub-arbol izquierdo, por ejemplo, raiz 50, sub nodo 40 y se agrego el 20
    
    // El nodo que llega como parametro tiene que convertirse en el sub nodo der de su sub nodo izq 
    // Y el sub nodo izquierdo del nodo que llego va a ser la nueva raiz o nodo padre
    
    Nodo* nuevoPR = nodo->izq; // nuevoPR = nuevoPadreRaiz para indicar que es el nuevo padre o raiz 
    
    // El sub nodo derecho, del sub nodo izquierdo del nodo que llego como parametro (es decir, el sub nodo derecho
    // de la nueva raiz o nodo padre) va a ser el sub nodo izquierdo del nodo que llego, que el nodo que llego ahora es
    // el sub arbol derecho de su nodo izquierdo (que ahora es el nuevo nodo padre o raiz)
    Nodo* nuevoIzqDer = nuevoPR->der; // nuevoIzqDer = nuevo nodo izquierdo del nuevo nodo derecho (que es el nodo que llego como parametro)
    
    // A la derecha de la nueva raiz va el nodo que llego... 
    nuevoPR->der = nodo;

    // ... pero hay que quitarle los nodos hijos al que llego, pq sino estariamos como copiando una rama del arbol...
    nodo->izq = nuevoIzqDer; // A la izquierda se quitan el 40 y 20 (en este ejemplo) y se agrega lo que estaba a la derecha
                             // del nuevo nodo padre o raiz

    actualizarAltura(nodo);
    actualizarAltura(nuevoPR);

    return nuevoPR; 

}

Nodo* AVLTree::rotarIzquierda(Nodo* nodo) {
    Nodo* nuevoPR = nodo->der;
    Nodo* nuevoDerIzq = nuevoPR->izq;

    nuevoPR->izq = nodo;
    nodo->der = nuevoDerIzq;

    actualizarAltura(nodo);
    actualizarAltura(nuevoPR);

    return nuevoPR;
}

void AVLTree::actualizarAltura(Nodo* nodo) {
    if(!nodo) return;
    
    nodo->priority = 1 + max(priority(nodo->izq), priority(nodo->der));
    
    // Siempre que se agregue un nodo, este va a tener altura 1. Entonces el valor de altura que se actuliza es el de
    // la raiz o algún sub-nodo si estamos en un caso de recursión.
    // Por ejemplo luego de agregar un segundo elemento (ya tenemos la raíz con priority 1), la altura (o priority) de 
    // la raiz va a ser 1 + la altura del nodo recien agregado que tambien es 1, por lo tanto la raiz queda con una priority 
    // (o altura) de 2. Y el nodo recién agregado queda con altura 1.
}

int AVLTree::priority(Nodo* nodo) {
    if(!nodo) return 0;

    return nodo->priority;
}

int AVLTree::balance(Nodo* nodo) {
    if(!nodo) return 0;

    return priority(nodo->izq) - priority(nodo->der);
}
