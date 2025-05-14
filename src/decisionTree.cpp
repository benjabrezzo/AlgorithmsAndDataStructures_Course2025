#include "decisionTree.hpp"

DecisionTree::DecisionTree() {
    raiz = nullptr;
}

DecisionTree::~DecisionTree() {
    destruir(raiz);
}


// Metodos publicos
void DecisionTree::insertar(const std::string& decision) {
    insertar(raiz, decision);
}

void DecisionTree::eliminar(const std::string& decision) {
    eliminarNodo(raiz, decision);
}

bool DecisionTree::buscar(const std::string& decision) const {
    return buscar(raiz, decision);
}

void DecisionTree::recorrerPreorden() const {
    recorrerPreorden(raiz);
}

bool DecisionTree::estaVacio() const {
    if(!raiz) return true;

    return false;
}


// Metodos privados
void DecisionTree::insertar(Nodo*& nodo, const std::string& decision) {
    // nodo va a ser la raiz del arbol

    if(nodo == nullptr) { 
        nodo = new Nodo(decision);
    }

    if(decision < nodo->decision) insertar(nodo->izquierda, decision);
    if(decision > nodo->decision) insertar(nodo->derecha, decision);
}


void DecisionTree::destruir(Nodo* nodo) {
    if(!nodo) return;
    destruir(nodo->izquierda);
    destruir(nodo->derecha);
    delete nodo;
}

void DecisionTree::eliminarNodo(Nodo*& nodo, const std::string& decision) {
    if(!nodo) return;

    if(decision < nodo->decision) {
        eliminarNodo(nodo->izquierda, decision);
    } else if (decision > nodo->decision) {
        eliminarNodo(nodo->derecha, decision);
    } else {
        // Caso 1: El nodo a eliminar NO tiene hijos
        if(!nodo->izquierda && !nodo->derecha) {
            delete nodo;
            nodo = nullptr;
        }

        // Caso 2: El nodo a eliminar tiene UN SOLO hijo
        else if(!nodo->izquierda) {
            Nodo* temp = nodo;
            nodo = nodo->derecha;
            delete temp;
        } else if(!nodo->derecha) {
            Nodo* temp = nodo;
            nodo = nodo->izquierda;
            delete temp;
        }

        // Caso 3: El nodo a eliminar tiene DOS hijos
        else {
            Nodo* sucesor = encontrarMinimo(nodo->derecha);
            nodo->decision = sucesor->decision;
            eliminarNodo(nodo->derecha, sucesor->decision);
        }

    }
}

Nodo* DecisionTree::encontrarMinimo(Nodo* nodo) {
    while(nodo && nodo->izquierda) {
        nodo = nodo->izquierda;
    }
    return nodo;
}

bool DecisionTree::buscar(Nodo* nodo, const std::string& decision) const {

    if(!nodo) {
        return false;
    }

    if(nodo->decision == decision) {
        return true;
    }

    return buscar(nodo->izquierda, decision) || buscar(nodo->derecha, decision);
}


void DecisionTree::recorrerPreorden(Nodo* nodo) const {
    if(!nodo) return;

    std::cout<<nodo->decision<<" ";
    recorrerPreorden(nodo->izquierda);
    recorrerPreorden(nodo->derecha);
}