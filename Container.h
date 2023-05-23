#pragma once
#include < cassert >
#include < functional >
#include < algorithm >


template < typename T > class Container
{
public:
    Container() {} // the implementation can be removed, yes. the constructor itself if removed VS does not build
    Container( Container const &  origin ) : Container(  ) {
        * this = origin;
    }
    Container &  operator =( Container const &  origin ) {
        if ( this ==  & origin ) {
            return *this;
        }
        clear(  );
        origin.forEach( 
            [this]( T const &  elem ) {addm_last( elem ); }
         );
        return *this;
    }
    ~Container(  )
    {
        clear(  );
    }
    void push_front( T const &  m_value )
    {
        Node< T> * temp = new Node< T >( m_value );
        if ( is_empty(  ) ) {
            assert( m_last == nullptr );
            m_last = temp;
        }
        else{
            m_first->m_prev = temp;
        }
        temp->m_next = m_first;
        m_first = temp;
        ++m_size;
    }
    void push_back( T const &  m_value )
    {
        Node< T > * temp = new Node< T>( m_value );
        if ( is_empty(  ) ) {
            assert( m_first == nullptr );
            m_first = temp;
        }
        else{
            m_last->m_next = temp;
        }
        temp->m_prev = m_last;
        m_last = temp;
        ++m_size;
    }

    void pop_front(  )
    {
        if ( is_empty(  ) ) {
            throw std::out_of_range("Container is empty. Nothing to delete.");
        }
        Node< T > * remove;
        remove = m_first;
        m_first = remove->m_next;
        if ( m_first != nullptr ) {
            m_first->m_prev = nullptr;
        }
        else{
            m_last = nullptr;
        }
        delete remove;
        --m_size;
    }

    void reverse_list(  )
    {
        auto head = m_first;
        if ( m_first == nullptr ) {
            m_last->m_next = m_first;
            return;
        }
        auto cur = head;
        Node< T > * m_prev = nullptr;
        while ( cur != nullptr ) {
            auto temp = cur->m_next;
            cur->m_next = m_prev;
            m_prev = cur;
            cur = temp;
        }
        m_first = m_prev;
        return;
    }

    void pop_back(  )
    {
        if ( is_empty(  ) ) {
            throw std::out_of_range("Container is empty. Nothing to delete.");
        }
        Node< T > * remove;
        remove = m_last;
        m_last = remove->m_prev;
        if ( m_last != nullptr ) {
            m_last->m_next = nullptr;
        }
        else{
            m_first = nullptr;
        }
        delete remove;
        --m_size;
    }
    T& pop(  ) { // task 3 point 4, they want me to pop() to throw the task and execute it from the outside, and above pop_back() to remove the object from the container
        if ( is_empty(  ) ) {
            throw std::out_of_range("Container is empty. Nothing to delete.");
        }
        Node< T > * remove;
        remove = m_last;
        m_last = remove->m_prev;
        if ( m_last != nullptr ) {
            m_last->m_next = nullptr;
        }
        else{
            m_first = nullptr;
        }
        //delete remove;
        --m_size;
        return remove->m_value;
    }
    T& get_first(  ) const {
        if ( is_empty(  ) ) {
            throw std::out_of_range("Container is empty. Nothing to delete.");
        }
        return m_first->m_value;
    }
    T& get_last(  ) const {
        if ( is_empty(  ) ) {
            throw std::out_of_range("Container is empty. Nothing to delete.");
        }
        return m_last->m_value;
    }
    unsigned int get_count(  ) const {
        return m_size;
    }
    bool is_empty(  ) const {
        return ( this->get_count(  ) == 0 );
    }
    void clear(  ) {
        while ( !is_empty(  ) )
        {
            pop_front(  );
        }
    }
    void forEach( std::function< void( T &  ) > func ) {
        Node< T > * elem = m_first;
        while ( elem != nullptr ) {
            func( elem->m_value );
            elem = elem->m_next;
        }
    }
    void forEach( std::function< void( T const &  ) > func ) const {
        Node< T > * elem = m_first;
        while ( elem != nullptr ) {
            func( elem->m_value );
            elem = elem->m_next;
        }
    } // task 3 point 5, run through the content and touch each element in a loop
private:
    template < typename T > class Node
    {
    public:
        Node(T const & m_value)
            : m_value(m_value)
            , m_prev(nullptr)
            , m_next(nullptr)
        {}
        T m_value;
        Node< T >* m_prev;
        Node< T >* m_next;
    };
    unsigned int m_size;
    Node< T > * m_first;
    Node< T > * m_last;
};