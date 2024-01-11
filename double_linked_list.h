#include <iostream>

using namespace std;

template<typename T>
struct Node {
    int data;
    Node* next;
    Node* prev;
    Node():next(nullptr), prev(nullptr), data(INT_MIN){}
};

template<typename T>
class List {
    private:
        Node<T>* head;
        Node<T>* tail;
    public:
        List():head(nullptr), tail(nullptr){}
        T front(); // Retorna el elemento al comienzo
        T back(); // Retorna el elemento al final
        void push_front(T); // Agrega un elemento al comienzo
        void push_back(T); // Agrega un elemento al final
        T pop_front(); // Remueve el elemento al comienzo
        T pop_back(); // Remueve el elemento al final
        void insert(T, int); // Inserta en cualquier posición
        void remove(int); // Remueve en cualquier posicion
        T operator[ ](int); // Retorna el elemento en la posición indicada
        bool empty(); // Retorna si la lista está vacía o no
        int size(); // Retorna el tamaño de la lista
        void clear(); // Elimina todos los elementos de la lista
        void reverse(); // Revierte la lista
};

template<typename T>
T List<T>::front(){
    return head->data;
}

template<typename T>
T List<T>::back(){
    return tail->data;
}

template<typename T>
void List<T>::push_front(T value){
    if(this->empty()){
        Node<T>* newNode = new Node<T>;
        newNode->data = value;
        newNode->next = nullptr;
        newNode->prev = nullptr;
        
        head = newNode;    
        tail = newNode;
        return;
    }
    Node<T>* newNode = new Node<T>;
    newNode->data = value;
    newNode->next = head;
    newNode->prev = nullptr;
    
    head->prev = newNode;
    head = newNode;
}

template<typename T>
void List<T>::push_back(T value){
    if(this->empty()){
        Node<T>* newNode = new Node<T>;
        newNode->data = value;
        newNode->next = nullptr;
        newNode->prev = nullptr;

        tail = newNode;        
        head = newNode;    
        return;
    }
    Node<T>* newNode = new Node<T>;
    newNode->data = value;
    newNode->next = nullptr;
    newNode->prev = tail;
    
    tail->next = newNode;
    tail = newNode;
}


template<typename T>
T List<T>::pop_front(){
    if(this->empty()){
        throw("The list is already empty");
    }
    if(this->size() == 1){
        T value = head->data;
        delete head;
        head = nullptr;
        tail = nullptr;
        return value;
    }
    T value = head->data;

    Node<T>* newHead = head->next;
    newHead->prev = nullptr;
    delete head;

    head = newHead;
    return value;
}

template<typename T>
T List<T>::pop_back(){
    if(this->empty()){
        throw("The list is already empty");
    }
    if(this->size() == 1){
        T value = tail->data;
        delete tail;
        head = nullptr;
        tail = nullptr;
        return value;
    }
    T value = tail->data;

    Node<T>* newTail = tail->prev;
    newTail->next = nullptr;
    delete tail;

    tail = newTail;
    return value;
}

template<typename T>
void List<T>:: insert(T value, int index){
    if(index >= this->size() - 1){
        this->push_back(value);
        return;
    }
    if(index <= 0){
        this->push_front(value);
        return;
    }

    Node<T>* MoveNode = head;
    while(index--){
        MoveNode = MoveNode->next;
    }
    
    Node<T>* newNode = new Node<T>;
    newNode->data = value;
    newNode->prev = MoveNode->prev;
    newNode->next = MoveNode;

    MoveNode->prev->next = newNode;
    MoveNode->prev = newNode;
}

template<typename T>
void List<T>:: remove(int index){
    if(this->empty()){
        throw("The list is already empty");
    }
    if(index < 0 || index >= this->size()){
        throw("The index is out of range");
    }
    if(!index){
        this->pop_front();
        return;
    }
    if(index == this->size() - 1){
        this->pop_back();
        return;
    }

    Node<T>* DeleteNode = head;
    while(index--){
        DeleteNode = DeleteNode->next;
    }
    DeleteNode->prev->next = DeleteNode->next;
    DeleteNode->next->prev = DeleteNode->prev;

    delete DeleteNode;
    DeleteNode = nullptr;
}

template<typename T>
T List<T>:: operator[ ](int index){
    if(this->empty()){
        throw("No available values");
    }
    if(index < 0 || index >= this->size()){
        throw("The index is out of range");
    }
    Node<T>* AccessNode = head;
    while(index--){
        AccessNode = AccessNode->next;
    }
    return AccessNode->data;
}

template<typename T>
bool List<T>::empty(){
    return head == nullptr;
}

template<typename T>
int List<T>::size(){
    Node<T>* CountNode = head;
    int length = 0;
    while(CountNode != nullptr){
        length+= 1;
        CountNode = CountNode->next;
    }
    return length;

}

template<typename T>
void List<T>::clear(){
    while(head != nullptr){
        Node<T>*temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
}

template<typename T>
void List<T>::reverse(){
    Node<T>* ReverserNode = head;
    Node<T>* temp = nullptr;
    while(ReverserNode != nullptr){
        temp = ReverserNode->prev;
        ReverserNode->prev = ReverserNode->next;
        ReverserNode->next = temp;
        
        ReverserNode = ReverserNode->prev;
    }

    temp = head;
    head = tail;
    tail = temp;
}
template<typename T>
void testList() {
    List<T> myList;

    // Prueba de push_back y push_front
    myList.push_back(1);
    myList.push_back(2);
    myList.push_front(0);

    // Prueba de front y back
    cout << "Front: " << myList.front() << ", Back: " << myList.back() << endl;

    // Prueba de size y empty
    cout << "Size: " << myList.size() << ", Empty: " << (myList.empty() ? "true" : "false") << endl;

    // Prueba de operador[]
    cout << "Element at index 1: " << myList[1] << endl;

    // Prueba de insert
    myList.insert(10, 1);
    cout << "Element at index 1 after insert: " << myList[1] << endl;

    // Prueba de remove
    myList.remove(1);
    cout << "Element at index 1 after remove: " << myList[1] << endl;

    // Prueba de pop_back y pop_front
    myList.pop_back();
    myList.pop_front();
    cout << "Size after pop_back and pop_front: " << myList.size() << endl;

    // Prueba de clear
    myList.clear();
    cout << "Size after clear: " << myList.size() << endl;

    // Prueba de reverse
    myList.push_back(1);
    myList.push_back(2);
    myList.push_back(3);
    cout << "Original List: " << myList[0] << " " << myList[1] << " " << myList[2] << endl;
    myList.reverse();
    cout << "Reversed List: " << myList[0] << " " << myList[1] << " " << myList[2] << endl;
}
