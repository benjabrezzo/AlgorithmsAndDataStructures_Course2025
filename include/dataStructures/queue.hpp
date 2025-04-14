#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "list.hpp"

/**
* @brief Implementación de una cola (queue) usando una lista doblemente enlazada.
*
* @tparam TData Tipo de dato almacenado
*/
template <typename TData>
class Queue
{
private:
    DoublyLinkedList<TData> list;

public:
    /**
    * @brief Constructor por defecto
    */
    Queue() = default;

    /**
    * @brief Añade un elemento al final de la cola.
    * @param data Dato a agregar.
    */
    void enqueue(const TData& data)
    {
        list.push_back(data);
    }

    /**
    * @brief Remueve y retorna el prime elemento de la cola.
    * @return TData Valor removido.
    */
    TData dequeue()
    {
        if(is_empty())
        {
            throw std::runtime_error("Queue is empty");
        }
        
        auto head = list.get_head();
        TData value = head->data;
        list.remove_at(0);
        return value;
    }

    /**
     * @brief Consulta el primer elemento de la cola sin removerlo.
     *
     * @return TData Valor del primer elemento.
     */
    TData front() const
    {
        if(is_empty())
        {
            throw std::runtime_error("Queue is empty");
        }

        return list.get_head()->data;
    }

    /**
     * @brief Verifica si la cola está vacía
     *
     * @return true si está vacía, false en caso contrario
     */
    bool is_empty() const
    {
        return list.get_head() == nullptr;
    }

    /**
     * @brief Imprime los elementos de la cola
     */
    void print() const
    {
        list.print();
    }


};


#endif
