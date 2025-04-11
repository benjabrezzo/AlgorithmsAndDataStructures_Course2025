#ifndef STACK_HPP
#define STACK_HPP

#include "list.hpp"

/**
 * @brief Implementación de una pila (stack) usando una lista simplemente enlazada.
 *
 * @tparam TData Tipo de dato almacenado.
 */
template<typename TData>
class Stack
{
private:
    LinkedList<TData> list;

public:
    /**
     * @brief Constructor por defecto.
     */
    Stack() = default;
    
    /**
     * @brief Añade un elemento a la cima de la pila.
     *
     * @param data Valor a añadir.
     */
    void push(const TData& data)
    {
        list.push_front(data);
    }

    /**
     * @brief Remueve y retorna el elemento del tope de la pila.
     * @return TData Valor removido.
     */
    TData pop()
    {
        if(list.get_head() == nullptr)
        {
            throw std::runtime_error("Stack is empty");
        }   
        auto head = list.get_head();
        TData value = head->data;
        list.remove_at(0);
        return value;
    }

    /**
     * @brief Consulta el elemento del tope de la pila sin removerlo
     *
     * @return TData Valor del tope
     * @throw std::runtime_error si la pila está vacía
     */
    TData top() const
    {
        if (is_empty())
        {
            throw std::runtime_error("Stack is empty");
        }

        return list.get_head()->data;
    }

    /**
     * @brief Verifica si la pila está vacía
     *
     * @return true si está vacía, false en caso contrario
     */
    bool is_empty() const
    {
        return list.get_head() == nullptr;
    }

}

#endif // STACK_HPP
