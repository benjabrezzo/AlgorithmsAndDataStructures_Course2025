#include "decisionTree.hpp"

DecisionTree::DecisionTree() {
    raiz = nullptr;
}



// Metodos publicos
void DecisionTree::insertar(const std::string& decision) {
    insertar(raiz, decision);
}

DecisionTree::~DecisionTree() {
    destruir(raiz);
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
