#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <exception>    // std::out_of_range
#include <iostream>     // std::cout, std::endl
#include <memory>       // std::unique_ptr
#include <iterator>     // std::advance, std::begin(), std::end(), std::ostream_iterator
#include <algorithm>    // std::copy, std::equal, std::fill
#include <initializer_list> // std::initializer_list
#include <cassert>      // assert()
#include <limits>       // std::numeric_limits<T>
#include <cstddef>      // std::size_t

/// Sequence container namespace.
namespace sc {
    /// Implements tha infrastrcture to support a bidirectional iterator.
    template < class T >
    class MyForwardIterator : public std::iterator<std::bidirectional_iterator_tag, T>
    {
        public:
            typedef MyForwardIterator self_type;   //!< Alias to iterator.
            // Below we have the iterator_traits common interface
            typedef std::ptrdiff_t difference_type; //!< Difference type used to calculated distance between iterators.
            typedef T value_type;           //!< Value type the iterator points to.
            typedef T* pointer;             //!< Pointer to the value type.
            typedef T& reference;           //!< Reference to the value type.
            typedef const T& const_reference;           //!< Reference to the value type.
            typedef std::bidirectional_iterator_tag iterator_category; //!< Iterator category.

            // TODO: create all methods here.

            /**
             * @brief Construct a new MyForwardIterator object with an assigned or default value. 
             * 
             * @param ptr Initial Value for 'm_ptr' by default is nullptr
             */
            MyForwardIterator(value_type * ptr = nullptr){
                m_ptr = ptr;
            }

            /**
             * @brief Construct a new MyForwardIterator object as a copy of other MyForwardIterator object.
             * 
             * @param itr a MyForwardIterator object
             */
            MyForwardIterator(const MyForwardIterator& itr){
                m_ptr = itr.m_ptr;
            }

            /**
             * @brief Copy 'itr' to MyForwardIterator called,
             * 
             * @param itr A MyForwardIterator Object that will be copied.
             * @return MyForwardIterator& A reference to a MyforwardIterator object.
             */
            MyForwardIterator& operator=( const MyForwardIterator& itr){
                m_ptr = itr.m_ptr; 
                return *this;
            }

            /**
             * @brief Advances iterator to the next location within the vector.
             * 
             * @return MyForwardIterator& A reference to a MyforwardIterator object
             */
            MyForwardIterator& operator++(){
                m_ptr++;
                return *this;
            } // ++it;

            /**
             * @brief Advances iterator to the next location within the vector.
             * 
             * @return MyForwardIterator The MyForwardIterator object after operation.
             */
            MyForwardIterator operator++(int){
                MyForwardIterator retval{*this};
                m_ptr++;
                return retval;
            } // it++;
            
            /**
             * @brief Recedes iterator to the previous location within the vector.
             * 
             * @return MyForwardIterator& A reference to a MyforwardIterator object after operation.
             */
            MyForwardIterator& operator--(){
                m_ptr--;
                return *this;
            } // --it;

            /**
             * @brief Recedes iterator to the previous location within the vector.
             * 
             * @return MyForwardIterator The MyForwardIterator object after operation.
             */
            MyForwardIterator operator--(int){
                MyForwardIterator retval{*this};
                m_ptr--;
                return retval;
            } // it--;

            /**
             * @brief Return a reference to the object located at the position pointed by the iterator.
             * 
             * @return reference Value saved by the iterator.
             */
            reference operator*() const{
                return *m_ptr;
            }

            /**
             * @brief check if both MyForwardIterator are the same.
             * 
             * @param other Other MyForwardIterator object that will be compared.
             * @return true If both iterators refer to the same location within the vector.
             * @return false Otherwise.
             */
            bool operator==(const MyForwardIterator& other) const{
                return m_ptr == other.m_ptr;
            }

            /**
             * @brief check if both MyForwardIterator are different.
             * 
             * @param other Other MyForwardIterator object that will be compared.
             * @return true If both iterators refer to a different location within the vector.
             * @return false Otherwise
             */
            bool operator!=(const MyForwardIterator& other) const{
                return !(*this==other);
            }

            /**
             * @brief Return a iterator pointing to the other-th successor in the vector from it.
             * 
             * @param other The "jump" the iterator will take.
             * @return MyForwardIterator A iterator pointing to the other-th successor in the vector from it.
             */
            MyForwardIterator operator+(const difference_type other) const{ 
                return MyForwardIterator(m_ptr + other); 
            }

            /**
             * @brief Return a iterator pointing to the n -th predecessor in the vector from it .
             * 
             * @param other The "jump" the iterator will take back.
             * @return MyForwardIterator A iterator pointing to the n -th predecessor in the vector from it .
             */
            MyForwardIterator operator-(const difference_type other) const{ 
                return MyForwardIterator(m_ptr - other);
            }

            /**
             * @brief Return a iterator pointing to the n -th successor in the vector from it.

             * 
             * @param x The "jump" the iterator will take.
             * @param other The iterator that will be operated.
             * @return MyForwardIterator A iterator pointing to the n -th successor in the vector from it.
             */
            friend MyForwardIterator operator+(const difference_type x , const MyForwardIterator& other){
                return MyForwardIterator(x + other.m_ptr);
            }

            /**
             * @brief Return the difference between two iterators.
             * 
             * @param other The other iterator that will be operated.
             * @return difference_type The value of the difference between two iterators.
             */
            difference_type operator-(const MyForwardIterator& other) const{
                return std::distance(other.m_ptr,m_ptr);
            }

        private:
            pointer m_ptr; //!< The raw pointer.
    };

    /// This class implements the ADT list with dynamic array.
    /*!
     * sc::vector is a sequence container that encapsulates dynamic size arrays.
     *
     * The elements are stored contiguously, which means that elements can
     * be accessed not only through iterators, but also using offsets to
     * regular pointers to elements.
     * This means that a pointer to an element of a vector may be passed to
     * any function that expects a pointer to an element of an array.
     *
     * \tparam T The type of the elements.
     */
    template < typename T >
    class vector
    {
        //=== Aliases
        public:
            using size_type = unsigned long; //!< The size type.
            using value_type = T;            //!< The value type.
            using pointer = value_type*;     //!< Pointer to a value stored in the container.
            using reference = value_type&;   //!< Reference to a value stored in the container.
            using const_reference = const value_type&; //!< Const reference to a value stored in the container.

            using iterator = MyForwardIterator< value_type >; //!< The iterator, instantiated from a template class.
            using const_iterator = MyForwardIterator< const value_type >; //!< The const_iterator, instantiated from a template class.

        public:
            //=== [I] SPECIAL MEMBERS (6 OF THEM)

            /**
             * @brief Construct a new vector object with 'newCapacity' elements. Each element is a copy of newCapacity
             * 
             * @param newCapacity Initial vector capacity and size, by default is 0.
             */
            explicit vector( size_type newCapacity = 0){
                Realloc(newCapacity);
                for(size_t i{0};i<newCapacity;i++){
                    push_back(newCapacity);
                }
            } //(2)

            /**
             * @brief Destroy the vector object
             * 
             */
            virtual ~vector( void ){
               delete [] m_storage;
            } //(6)

            /**
             * @brief Construct a new vector object with a copy of each of the elements in 'other', in the same order.
             * 
             * @param other Another vector object of the same type.
             */
            vector( const vector & other){
                Realloc(other.m_capacity);

                for(size_t i{0};i<other.size();i++){
                    push_back(other[i]);
                }
            } //(4)

            /**
             * @brief Construct a new vector object with a copy of each of the elements in 'init', in the same order. 
             * 
             * @param init An initializer_list object.
             */
            vector( std::initializer_list<T> init){
                Realloc(init.size());
                for(auto i: init){
                    push_back(i);
                }
            } //(5)

            vector( vector && );

            /**
             * @brief Construct a new vector object with the contents of the range [first, last).
             * 
             * @tparam InputItr Input iterator type
             * @param first Input iterator to the initial position in a range.
             * @param last Input iterator to the final position in a range.
             */
            template < typename InputItr >//(3)
            vector( InputItr first, InputItr last){
                Realloc(std::distance(first,last));
                size_t sz = std::distance(first,last);
                for(size_t i{0};i<sz;i++){
                    push_back(*first++);
                }
            }

            /**
             * @brief Copies all the elements from 'rhs' into the vector.
             * 
             * @param rhs A vector object of the same type.
             * @return vector& always returns *this enabling things like a = b = c.
             */
            vector & operator=( const vector & rhs){
                if(this != &rhs){
                    if(m_capacity != rhs.m_end){
                        //delete[] m_storage;
                        Realloc(rhs.m_capacity);
                    }
                    //mudar para begin e end dps dos iteradores
                    std::copy(rhs.m_storage, rhs.m_storage + rhs.m_end, m_storage);
                }
                //swap();
                m_capacity = rhs.m_end;
                m_end = rhs.m_end;
                return *this;
            } //(7)

            vector & operator=(vector &&); 

            /**
             * @brief Copies all the elements from 'init' into the vector.
             * 
             * @param init An initializer_list object.
             * @return vector& always returns *this enabling things like a = b = c.
             */
            vector & operator=(std::initializer_list<T> init){
                if(m_capacity != init.size()){
                    //delete[] m_storage;
                    Realloc(init.size());
                }
                //mudar para begin e end dps dos iteradores
                clear();
                for(auto i: init){
                    push_back(i);
                }
                m_capacity = init.size();
                m_end = init.size();
                return *this;
            } //(8)
            

            //=== [II] ITERATORS

            /**
             * @brief Returns an iterator pointing to the first item in the list.
             * 
             * @return iterator 
             */
            iterator begin( void ){
                return iterator{m_storage};
            }

            /**
             * @brief Returns an iterator pointing to the position just after the last element of the list.
             * 
             * @return iterator 
             */
            iterator end( void ){
                return iterator {m_storage + m_end};
            }

            /**
             * @brief  Returns a constant iterator pointing to the first item in the list.
             * 
             * @return const_iterator 
             */
            const_iterator cbegin( void ) const{
                return m_storage;
            }

            /**
             * @brief Returns a constant iterator pointing to the position just after the last element of the list.
             * 
             * @return const_iterator 
             */
            const_iterator cend( void ) const{
                return &m_storage[m_end];
            }

            // [III] Capacity

            /**
             * @brief  Return the number of elements in the container.
             * 
             * @return size_type 
             */
            size_type size( void ) const{
                return m_end;
            }
            
            /**
             * @brief Return the internal storage capacity of the array.
             * 
             * @return size_type 
             */
            size_type capacity( void ) const{
                return m_capacity;
            }

            /**
             * @brief Check if the vector is empty.
             * 
             * @return true If the vector contains no elements.
             * @return false If the vector contains elements.
             */
            bool empty( void ) const{
                return m_end == 0;
            }

            // [IV] Modifiers

            /**
             * @brief Remove all elements from the container.
             * 
             */
            void clear( void ){
                m_end = 0;
            }

            /**
             * @brief Inserts a new element at the beginning of the vector, right before its current first element.
             * 
             * @param value Value that will be placed at the beginning of the vector.
             */
            void push_front( const_reference value){
                if(m_end >= m_capacity){
                    Realloc(2*m_capacity);
                }
                for(size_t i{m_end};i>0;i--){
                    m_storage[i] = m_storage[i-1];
                }
                m_storage[0] = value;
                m_end += 1;
            }
            
            /**
             * @brief Adds a new element at the end of the vector, after its current last element.
             * 
             * @param value Value that will be placed in the vector.
             */
            void push_back( const_reference value){
                if(m_end >= m_capacity){
                    if(m_capacity == 0){
                        Realloc(1);
                    }else{
                        Realloc(2*m_capacity);
                    }
                }
                m_storage[m_end] = value;
                m_end++;
            }
            
            /**
             * @brief Removes the object at the end of the list.
             * 
             */
            void pop_back( void ){
                if(m_end > 0){
                    m_end--;
                }else{
                    throw std::length_error ("[vector::pop_back()]: não posso remover um elemento de um vector vazio.");
                }
            }

            /**
             * @brief Removes the first element in the vector.
             * 
             */
            void pop_front( void ){
                if(m_end > 0){
                    erase(begin());
                }
            }

            /**
             * @brief The vector is extended by inserting new elements before the element at the specified position.
             * 
             * @param pos_ Position in the vector where the new elements are inserted.
             * @param value_ Value to be copied to the inserted elements.
             * @return iterator An iterator that points to the first of the newly inserted elements.
             */
            iterator insert( iterator pos_ , const_reference value_ ){
                size_t index = pos_ - begin();
                if(m_end >= m_capacity){
                    if(m_capacity == 0){ 
                        if(pos_!=begin()){
                            throw std::length_error ("[vector::insert()]: não posso inserir em um vector vazio sem ser no começo.");
                        }else{
                            Realloc(1);
                        }
                    }else{
                        Realloc(2*m_capacity);
                    }
                }
                for(size_t i{m_end-1}; i >= index ;i--){
                    m_storage[i+1] = m_storage[i]; 
                    if(i+1 == 0){
                        break;
                    }
                }
                m_storage[index] = value_;
                m_end++;
                return &m_storage[pos_ - m_storage];
            }

            /**
             * @brief The vector is extended by inserting new elements before the element at the specified position.
             * 
             * @param pos_ Position in the vector where the new elements are inserted.
             * @param value_ Value to be copied to the inserted elements.
             * @return iterator An iterator that points to the first of the newly inserted elements.
             */
            iterator insert( const_iterator pos_ , const_reference value_ ){
                size_t index = pos_ - begin();
                if(m_end >= m_capacity){
                    if(m_capacity == 0){ 
                        if(pos_!=begin()){
                            throw std::length_error ("[vector::insert()]: não posso inserir em um vector vazio sem ser no começo.");
                        }else{
                            Realloc(1);
                        }
                    }else{
                        Realloc(2*m_capacity);
                    }
                }
                for(size_t i{m_end-1}; i >= index ;i--){
                    m_storage[i+1] = m_storage[i]; 
                    if(i+1 == 0){
                        break;
                    }
                }
                m_storage[index] = value_;
                m_end++;
                return &m_storage[pos_ - m_storage];
            }

            /**
             * @brief Inserts elements from the range [first; last) before pos .
             * 
             * @tparam InputItr Input iterator type
             * @param pos_ Position in the vector where the new elements are inserted.
             * @param first_ Input iterator to the initial position in a range.
             * @param last_ Input iterator to the final position in a range.
             * @return iterator An iterator that points to the first of the newly inserted elements.
             */
            template < typename InputItr >
            iterator insert( iterator pos_ , InputItr first_, InputItr last_ ){
                size_t position = pos_ - begin();
                size_t tam = last_ - first_;
                if(m_end >= m_capacity){
                    if(m_capacity == 0){ 
                        if(pos_!=begin()){
                            throw std::length_error ("[vector::insert()]: não posso inserir em um vector vazio sem ser no começo.");
                        }else{
                            Realloc(1);
                        }
                    }else{
                        Realloc(2*m_capacity);
                    }
                }

                T* newBlock = new T[m_end + tam];
                
                //colocando todos antes da posição
                int aux1{0};
                int backupFim = 0;
                for(size_t i{0}; i<position; i++){
                    newBlock[aux1] = m_storage[i];
                    aux1++;
                    backupFim++;
                }

                //colocando todos do meio
                size_t trocas1 = 0;
                size_t backup = aux1;
                for(size_t i{(size_t)aux1};i<tam+backup;i++){
                    newBlock[aux1] = *first_+trocas1;
                    aux1++;
                    trocas1++;
                }

                //colocando todos do final
                for(size_t i{(size_t)aux1};i<m_end + tam;i++){
                    newBlock[aux1] = m_storage[backupFim];
                    aux1++;
                    backupFim++;
                }

                delete[] m_storage;
                m_storage = newBlock;
                m_capacity = tam+m_end;
                m_end = m_capacity;

                return &m_storage[first_ - m_storage];
            }

            /**
             * @brief Inserts elements from the range [first; last) before pos .
             * 
             * @tparam InputItr Input iterator type
             * @param pos_ Position in the vector where the new elements are inserted.
             * @param first_ Input iterator to the initial position in a range.
             * @param last_ Input iterator to the final position in a range.
             * @return iterator An iterator that points to the first of the newly inserted elements.
             */
            template < typename InputItr >
            iterator insert( const_iterator pos_ , InputItr first_, InputItr last_ ){
                size_t position = pos_ - begin();
                size_t tam = last_ - first_;
                if(m_end >= m_capacity){
                    if(m_capacity == 0){ 
                        if(pos_!=begin()){
                            throw std::length_error ("[vector::insert()]: não posso inserir em um vector vazio sem ser no começo.");
                        }else{
                            Realloc(1);
                        }
                    }else{
                        Realloc(2*m_capacity);
                    }
                }

                T* newBlock = new T[m_end + tam];
                
                //colocando todos antes da posição
                int aux1{0};
                int backupFim = 0;
                for(size_t i{0}; i<position; i++){
                    newBlock[aux1] = m_storage[i];
                    aux1++;
                    backupFim++;
                }

                //colocando todos do meio
                size_t trocas1 = 0;
                size_t backup = aux1;
                for(size_t i{aux1};i<tam+backup;i++){
                    newBlock[aux1] = *first_+trocas1;
                    aux1++;
                    trocas1++;
                }

                //colocando todos do final
                for(size_t i{aux1};i<m_end + tam;i++){
                    newBlock[aux1] = m_storage[backupFim];
                    aux1++;
                    backupFim++;
                }

                delete[] m_storage;
                m_storage = newBlock;
                m_capacity = tam+m_end;
                m_end = m_capacity;

                return &m_storage[first_ - m_storage];
            }
            
            /**
             * @brief Inserts elements from the initializer list 'ilist_' before 'pos_'.
             * 
             * @param pos_ Position in the vector where the new elements are inserted.
             * @param ilist_ A initializer list that will be inserted.
             * @return iterator An iterator that points to the first of the newly inserted elements.
             */
            iterator insert( iterator pos_, const std::initializer_list< value_type >& ilist_ ){
                size_t position = pos_ - begin();
                size_t tam = ilist_.size();
                if(m_end >= m_capacity){
                    if(m_capacity == 0){ 
                        if(pos_!=begin()){
                            throw std::length_error ("[vector::insert()]: não posso inserir em um vector vazio sem ser no começo.");
                        }else{
                            Realloc(1);
                        }
                    }else{
                        Realloc(2*m_capacity);
                    }
                }
                T* newBlock = new T[m_end + tam];
                
                //colocando todos antes da posição
                int aux1{0};
                int backupFim = 0;
                for(size_t i{0}; i<position; i++){
                    newBlock[aux1] = m_storage[i];
                    aux1++;
                    backupFim++;
                }

                //colocando todos do meio
                size_t trocas1 = 0;
                //size_t backup = aux1;
                for(auto i: ilist_){
                    newBlock[aux1] = i;
                    aux1++;
                    trocas1++;
                }

                //colocando todos do final
                for(size_t i{(size_t)aux1};i<m_end + tam;i++){
                    newBlock[aux1] = m_storage[backupFim];
                    aux1++;
                    backupFim++;
                }

                delete[] m_storage;
                m_storage = newBlock;
                m_capacity = m_end + tam;
                m_end = m_capacity;

                return &m_storage[pos_ - m_storage];
            }

            /**
             * @brief Inserts elements from the initializer list 'ilist_' before 'pos_'.
             * 
             * @param pos_ Position in the vector where the new elements are inserted.
             * @param ilist_ A initializer list that will be inserted.
             * @return iterator An iterator that points to the first of the newly inserted elements.
             */
            iterator insert( const_iterator pos_, const std::initializer_list< value_type >& ilist_ ){
                size_t position = pos_ - begin();
                size_t tam = ilist_.size();
                if(m_end >= m_capacity){
                    if(m_capacity == 0){ 
                        if(pos_!=begin()){
                            throw std::length_error ("[vector::insert()]: não posso inserir em um vector vazio sem ser no começo.");
                        }else{
                            Realloc(1);
                        }
                    }else{
                        Realloc(2*m_capacity);
                    }
                }
                T* newBlock = new T[m_end + tam];
                
                //colocando todos antes da posição
                int aux1{0};
                int backupFim = 0;
                for(size_t i{0}; i<position; i++){
                    newBlock[aux1] = m_storage[i];
                    aux1++;
                    backupFim++;
                }

                //colocando todos do meio
                size_t trocas1 = 0;
                size_t backup = aux1;
                for(auto i: ilist_){
                    newBlock[aux1] = i;
                    aux1++;
                    trocas1++;
                }

                //colocando todos do final
                for(size_t i{aux1};i<m_end + tam;i++){
                    newBlock[aux1] = m_storage[backupFim];
                    aux1++;
                    backupFim++;
                }

                delete[] m_storage;
                m_storage = newBlock;
                m_capacity = m_end + tam;
                m_end = m_capacity;

                return &m_storage[pos_ - m_storage];
            }

            /**
             * @brief Requests that the vector capacity be at least enough to contain 'x' elements.
             * 
             * @param x Minimum capacity for the vector.
             */
            void reserve( size_type x){
                if(x>m_capacity){
                    m_capacity = x;
                    Realloc(m_capacity);
                }
            }

            /**
             * @brief Requests the vector to reduce its capacity to fit its size.
             * 
             */
            void shrink_to_fit( void ){
                m_capacity = m_end;
                Realloc(m_capacity);
            }

            /**
             * @brief The new contents is 'count_' elements, each initialized to a copy of 'value_'.
             * 
             */
            void assign( value_type /*size_type*/ count_, /*const_reference*/value_type value_ ){
                if((long unsigned int)count_>m_capacity){
                    Realloc(count_);
                }
                for(size_t i{0};i<(size_t)count_;i++){
                    m_storage[i] = value_;
                }
                m_end = count_;
            }   

            /**
             * @brief The new contents are copies of the values passed as initializer list, in the same order.
             * 
             * @param ilist An initializer_list object.
             */
            void assign( const std::initializer_list<T>& ilist ){
                size_t sz = ilist.size();
                if(sz>m_capacity){
                    Realloc(sz);
                }
                int index = 0;
                for (auto i : ilist){
                    m_storage[index] = i;
                    index++;
                }
                m_end = sz;
            }

            /**
             * @brief The new contents are elements constructed from each of the elements in the range between first and last, in the same order.
             * 
             * @tparam InputItr Input iterator type
             * @param first Input iterator to the initial position in a range.
             * @param last Input iterator to the final position in a range.
             */
            template < typename InputItr >
            void assign( InputItr first, InputItr last ){
                size_t tam = last - first;
                size_t inicio = first - begin();
                size_t fim = last - begin();

                T* newBlock = new T[tam];

                int aux{0};
                for(size_t i{inicio};i<fim;i++){
                    newBlock[aux] = m_storage[i];
                    aux++;
                }

                delete[] m_storage;
                m_storage = newBlock;
                m_capacity = tam;
                m_end = tam;
            }

            /**
             * @brief Removes from the vector a range of elements [first,last).
             * 
             * @param first Iterator pointing to the first element that will be removed.
             * @param last Iterator pointing to the successor of the last element that will be removed.
             * @return iterator An iterator pointing to the new location of the element that followed the last element erased by the function call.
             */
            iterator erase( iterator first, iterator last ){
                size_t index_pos = std::distance(first,last);
                size_t inicio = first - begin();
                size_t aux{0};
                for(size_t i{inicio}; aux < index_pos ;aux++){
                    for(size_t j{i};j<m_end;j++){
                        m_storage[j] = m_storage[j+1];
                    }
                    m_end-=1;
                }
                return &m_storage[first - m_storage];
            }   

            /**
             * @brief Removes from the vector a range of elements [first,last).
             * 
             * @param first Iterator pointing to the first element that will be removed.
             * @param last Iterator pointing to the successor of the last element that will be removed.
             * @return iterator An iterator pointing to the new location of the element that followed the last element erased by the function call.
             */
            iterator erase( const_iterator first, const_iterator last ){
                size_t index_pos = std::distance(first,last);
                size_t inicio = first - begin();
                size_t aux{0};
                for(size_t i{inicio}; aux < index_pos ;aux++){
                    for(size_t j{i};j<m_end;j++){
                        m_storage[j] = m_storage[j+1];
                    }
                    m_end-=1;
                }
                return &m_storage[first - m_storage];
            }

            /**
             * @brief Removes the object at position 'pos'.
             * 
             * @param pos Position of the element that will be removed.
             * @return iterator Iterator to the element that follows pos before the call.
             */
            iterator erase( const_iterator pos ){
                size_t index = pos - begin();
                for(size_t i{index}; ;++i){
                    m_storage[i] = m_storage[i+1];
                }
                m_end--;
                return &m_storage[pos - m_storage];
            }   

            /**
             * @brief Removes the object at position 'pos'.
             * 
             * @param pos Position of the element that will be removed.
             * @return iterator Iterator to the element that follows pos before the call.
             */
            iterator erase( iterator pos ){
                size_t index = pos - begin();
                for(size_t i{index}; i < m_end;++i){
                    m_storage[i] = m_storage[i+1];
                }
                m_end--;
                return &m_storage[pos - m_storage];
            }

            // [V] Element access

            /**
             * @brief Returns the object at the end of the list.
             * 
             * @return const_reference A constant reference to the last element in the vector.
             */
            const_reference back( void ) const{
                if(empty()){
                    throw std::length_error ("[vector::back()]: vector vazio.");
                }
                return m_storage[m_end-1];
            }

            /**
             * @brief Returns a constant reference to the first element in the vector.
             * 
             * @return const_reference A constant reference to the first element in the vector container.
             */
            const_reference front( void ) const{
                if(empty()){
                    throw std::length_error ("[vector::front()]: vector vazio.");
                }
                return m_storage[0];
            }
            
            /**
             * @brief Returns the object at the end of the list.
             * 
             * @return reference A reference to the last element in the vector.
             */
            reference back( void ){
                if(empty()){
                    throw std::length_error ("[vector::back()]: vector vazio.");
                }
                return m_storage[m_end-1];
            }

            /**
             * @brief Returns a reference to the first element in the vector.
             * 
             * @return reference A reference to the first element in the vector.
             */
            reference front( void ){
                if(empty()){
                    throw std::length_error ("[vector::front()]: vector vazio.");
                }
                return m_storage[0];
            }

            /**
             * @brief Returns a constant reference to the element at position 'index in the vector.
             * 
             * @param index Position of an element in the vector.
             * @return const_reference A constant reference to the element at the specified position in the vector.
             */
            const_reference operator[]( size_type index) const{
                //if(index >= m_end){
                    //error?
                //}
                return m_storage[index];
            }

            /**
             * @brief Returns a reference to the element at position 'index in the vector.
             * 
             * @param index Position of an element in the vector.
             * @return reference A reference to the element at the specified position in the vector.
             */
            reference operator[]( size_type index){
                //if(index >= m_end){
                    //error?
                //}
                return m_storage[index];
            }

            /**
             * @brief Returns a constant reference to the element at position 'position' in the vector.
             * 
             * @param position Position of an element in the vector.
             * @return const_reference A constant reference to the element at the specified position in the container.
             */
            const_reference at( size_type position) const{
                if(position < m_end){
                    return m_storage[position];
                }
                throw std::out_of_range{"Posição Acessada Fora do Range"};
            }

            /**
             * @brief Returns a reference to the element at position 'position' in the vector.
             * 
             * @param position Position of an element in the vector.
             * @return reference A reference to the element at the specified position in the container.
             */
            reference at( size_type position){
                if(position < m_end){
                    return m_storage[position];
                }
                throw std::out_of_range{"Posição Acessada Fora do Range"};
            }

            /**
             * @brief Returns a direct pointer to the memory array used internally by the vector to store its owned elements.
             * 
             * @return pointer A pointer to the first element in the array used internally by the vector.
             */
            pointer data( void ){
                return m_storage;
            }
            
            /**
             * @brief Returns a direct pointer to the memory array used internally by the vector to store its owned elements.
             * 
             * @return const_reference A constant reference to the first element in the array used internally by the vector.
             */
            const_reference data( void ) const{
                return m_storage;
            }

            // [VII] Friend functions.
            friend std::ostream & operator<<( std::ostream & os_, const vector<T> & v_ )
            {
                // O que eu quero imprimir???
                os_ << "{ ";
                for( auto i{0u} ; i < v_.m_capacity ; ++i )
                {
                    if ( i == v_.m_end ) os_ << "| ";
                    os_ << v_.m_storage[ i ] << " ";
                }
                os_ << "}, m_end=" << v_.m_end << ", m_capacity=" << v_.m_capacity;

                return os_;
            }

            friend void swap( vector<T> & first_, vector<T> & second_ )
            {
                // enable ADL
                using std::swap;

                // Swap each member of the class.
                swap( first_.m_end,      second_.m_end      );
                swap( first_.m_capacity, second_.m_capacity );
                swap( first_.m_storage,  second_.m_storage  );
            }

            template <typename X>
            friend bool operator==( const vector<X> & lhs, const vector<X>& rhs);
            template <typename X>
            friend bool operator!=( const vector<X> & lhs, const vector<X>& rhs);

        private:

            /**
             * @brief Check if the vector is full.
             * 
             * @return true If the vector is full.
             * @return false Otherwise.
             */
            bool full( void ) const{
                return m_end == m_capacity;
            }

            /**
             * @brief Reallocates a vector using 'newCapacity' as its capacity.
             * 
             * @param newCapacity New vector capacity
             */
            void Realloc(size_type newCapacity){
                T* newBlock = new T[newCapacity];

                if(newCapacity < m_end){
                    m_end = newCapacity;
                }

                for(size_t i{0}; i < m_end; i++){
                    newBlock[i] = m_storage[i];
                }
                
                delete[] m_storage;
                m_storage = newBlock;
                m_capacity = newCapacity;
            }
            size_type m_end = 0;                //!< The list's current size (or index past-last valid element).
            size_type m_capacity = 0;           //!< The list's storage capacity.
            // std::unique_ptr<T[]> m_storage; //!< The list's data storage area.
            T *m_storage = nullptr;                   //!< The list's data storage area.
    };

    // [VI] Operators

    /**
     * @brief Checks if the contents of lhs and rhs are equal.
     * 
     * @tparam T Type of vector.
     * @param lhs Left vector to be compared.
     * @param rhs Right vector to be compared.
     * @return true If the contents of lhs and rhs are equal.
     * @return false Otherwise.
     */
    template <typename T>
    bool operator==( const vector<T> & lhs, const vector<T>& rhs){
        if(lhs.size() != rhs.size()){
            return false;
        }
        for(size_t i{0};i<rhs.size();i++){
            if(lhs.m_storage[i]!=rhs.m_storage[i]){
                return false;
            }
        }
        return true;
    }

    /**
     * @brief Checks if the contents of lhs and rhs are different.
     * 
     * @tparam T Type of vector.
     * @param lhs Left vector to be compared.
     * @param rhs Right vector to be compared. 
     * @return true If the contents of lhs and rhs are different.
     * @return false Otherwise. 
     */
    template <typename T>
    bool operator!=( const vector<T> & lhs, const vector<T>& rhs){
        return !(lhs==rhs);
    }

} // namespace sc.
#endif
