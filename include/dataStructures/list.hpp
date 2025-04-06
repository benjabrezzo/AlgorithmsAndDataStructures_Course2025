#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>

/**
 * @brief Nodo de lista simplemente enlazada
 *
 * @tparam TData Tipo de dato almacenado
 */
template<typename TData>
struct ListNode
{
    TData data;
    ListNode* next;

    explicit ListNode(const TData& value)
        : data(value)
        , next(nullptr)
    {
    }
};

/**
 * @brief Implementación de una lista simplemente enlazada
 *
 * @tparam TData Tipo de dato almacenado
 */
template<typename TData>
class LinkedList
{
private:
    ListNode<TData>* head;

public:
    LinkedList()
        : head(nullptr)
    {
    }

    ~LinkedList()
    {
        while(head != nullptr)
        {
            auto temporalNode = head;
            head = head->next;
            delete temporalNode;
        }
    }

    /**
     * @brief Inserta un nuevo elemento al inicio de la lista
     *
     * @param value Valor a insertar
     */
    void push_front(const TData& value)
    {
        auto nuevo = new ListNode<TData>(value);
        nuevo->next = head;
        head = nuevo;
    }

    /**
    * @brief Remueve un elemento de la lista dada su posición
    *
    * @param position Posición del elemento a remover
    */
    void remove_at(size_t position)
    {
        if (head == nullptr)
        {
            return;
        }

        if (position == 0)
        {
            auto temp = head;
            head = head->next;
            delete temp;
            return;
        }

        // Para cualquier otra posicion necesitamos mantener un puntero al nodo anterior
        auto prev = head;
        auto current = head->next;
        size_t current_position = 1;

        // Avanzamos hasta encontrar la posicion o llegar al final de la lista
        while (current != nullptr && current_position < position)
        {
            prev = current;
            current = current->next;
            current_position++;
        }

        // Si current es nullptr quiere decir que la posicion especifica es mas grande que la lista,
        // no se encuentra la posicion
        if (current == nullptr) return;

        // Hacemos que el nodo anterior apunte al nodo siguiente actual
        prev->next = current->next;

        delete current;
    }

    /**
    * @brief Crea una lista nueva de n elementos a partir de una posición dada
    *
    */
    ListNode<TData>* take(size_t startPosition, size_t nElements)
    {
        // Si la lista esta vacia retornamos nullptr
        if (head == nullptr)
        {
            return nullptr;
        }

        // Buscamos el nodo de inicio
        ListNode<TData>* current = head;
        size_t current_position = 0;

        // Avanzamos hasta la posicion de inicio
        while (current != nullptr && current_position < startPosition)
        {
            current = current->next;
            current_position++;
        }

        // Si current es nullptr, la posicion esta fuera de rango
        if (current == nullptr) return nullptr;

        // Creamos el primer nodo de la nueva lista
        ListNode<TData>* new_head = new ListNode<TData>(current->data);
        ListNode<TData>* new_current = new_head;

        // Avanzamos al siguiente nodo en la lista original
        current = current->next;

        // Copiamos los siguientes mElements-1 nodos (ya copiamos 1)
        for (size_t i = 1; i < nElements && current != nullptr; i++)
        {
            // Creamos un nuevo nodo con el valor actual
            new_current->next = new ListNode<TData>(current->data);

            // Avanzamos en ambas listas
            new_current = new_current->next;
            current = current->next;
        }

        return new_head;
    }

    /**
     * @brief Imprime todos los elementos de la lista
     */
    void print() const
    {
        ListNode<TData>* current = head;
        while (current != nullptr)
        {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "nullptr" << std::endl;
    }

    /**
     * @return Devuelve el primer elemento de la lista
     */
    ListNode<TData>* get_head() const
    {
        return head;
    }
};

/**
 * @brief Nodo de lista doblemente enlazada
 *
 * @tparam TData Tipo de dato almacenado
 */
template<typename TData>
struct DoublyListNode
{
    TData data;
    DoublyListNode* next;
    DoublyListNode* prev;

    explicit DoublyListNode(const TData& value)
        : data(value)
        , next(nullptr)
        , prev(nullptr)
    {
    }
};

/**
 * @brief Implementación de una lista doblemente enlazada
 *
 * @tparam TData Tipo de dato almacenado
 */
template<typename TData>
class DoublyLinkedList
{
private:
    DoublyListNode<TData>* head;

public:
    DoublyLinkedList()
        : head(nullptr)
    {
    }

    ~DoublyLinkedList()
    {
        while(head != nullptr)
        {
            auto temporalNode = head;
            head = head->next;
            delete temporalNode;
        }
    }

    /**
     * @brief Retorna el primer elemento de la lista
     *
     * @return Primer elemento de la lista
     */
    DoublyListNode<TData>* get_head() const
    {
        return head;
    }

    /**
     * @brief Inserta un nuevo elemento al inicio de la lista
     *
     * @param value Valor a insertar
     */
    void push_front(const TData& value)
    {
        auto nuevo = new DoublyListNode<TData>(value);
        nuevo->next = head;
        head = nuevo;
    }

    /**
     * @brief Inserta un nuevo elemento al final de la lista
     *
     * @param value Valor a insertar
     */
    void push_back(const TData& value)
    {
        auto nuevo = new DoublyListNode<TData>(value);
        // nuevo->next = nullptr; No haria falta pq cuando se crea un DoublyListNode next y prev se inicilizan en nullptr

        // Si la lista esta vacia
        if (!head)
        {
            head = nuevo;
        }
        else
        {
            // Si la lista tiene elementos, recorrer hasta el ultimo nodo
            // DoublyListNode<TData>* temp = get_head();
            auto temp = get_head();
            while (temp->next != nullptr) // Buscamos el ultimo nodo
            {
                temp = temp->next;
            }

            // temp es el ultimo nodo, se conecta con el nuevo ultimo nodo
            temp->next = nuevo;
            nuevo->prev = temp; // El prev de nuevo apunta al antiguo ultimo nodo, osea temp
        }
    }

    /**
    * @brief Remueve un elemento de la lista dada su posición
    *
    * @param position Posición del elemento a remover
    */
    void remove_at(size_t position)
    {
        // Si la lista esta vacia no hay nada que eliminar
        if (head == nullptr)
        {
            return;
        }

        // Caso que el nodo a eliminar sea el primero (nodo 0)
        if (position == 0)
        {
            DoublyListNode<TData>* temp = head;
            head = head->next;

            // Si hay mas nodos despues del primero actualizamos el prev del nuevo head
            if (head != nullptr)
            {
                head->prev = nullptr;
            }

            delete temp;
            return;
        }

        // Para cualquier otra posicion recorremos la lista, hacemos un contador para llevar track de
        // la posicion en la lista
        DoublyListNode<TData>* current = head;
        size_t current_position = 0;

        while (current != nullptr && current_position < position)
        {
            current = current->next;
            current_position++;
        }

        // Si current es nullptr quiere decir que la posicion especifica es mas grande que la lista,
        // no se encuentra la posicion
        if (current == nullptr) return;

        // current es el nodo que queremos eliminar, conectamos sus
        // nodos adyacentes
        if (current->prev != nullptr)
        {
            current->prev->next = current->next;
        }

        if (current->next != nullptr)
        {
            current->next->prev = current->prev;
        }

        delete current;

    }

    /**
    * @brief Copia los elementos de otra lista
    *
    * @param other Lista de la cual copiar los elementos
    */
    void copy_list(const DoublyLinkedList& other)
    {
        // PREGUNTAR: Borramos los nodos actuales?
        while (head != nullptr)
        {
            auto temporalNode = head;
            head = head->next;
            delete temporalNode;
        }

        // Copiamos los nodos de la otra lista con push_bakc()
        auto current = other.get_head();
        while (current != nullptr)
        {
            push_back(current->data);
            current = current->next;
        }
    }

    /**
     * @brief Imprime todos los elementos de la lista
     */
    void print() const
    {
        DoublyListNode<TData>* current = head;
        while (current != nullptr)
        {
            std::cout << current->data << " <-> ";
            current = current->next;
        }
        std::cout << "nullptr" << std::endl;
    }
};

#endif // LIST_HPP
