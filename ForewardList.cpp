#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node* next; // crea un puntero a la siguiente direccion de memoria pq *next apunta a una estructura de tipo nodo
};

template <typename T>
class List
{
private:
    Node* head;
    // ver si tenemos que definir el head como un puntero a un nodo o como un nodo
public:
    // Constructor
    List(){
        head = NULL;
    }

    // T front();
    T front(){
        return head->data;
    }

    // T back();
    T back(){
        Node* temp = head;
        temp = temp->next;
        while(temp->next != NULL){
            temp = temp->next;            
        }
        return temp->data;
    }

    // void push_front(T value);
    void push_front(T value){
        Node* temp = new Node(); // creamos un nuevo nodo
        temp->data = value; // le asignamos el valor
        temp->next = head; // el siguiente nodo es el head
        head = temp; // el head es el nuevo nodo
    }

    // void push_back(T value);
    void push_back(T value){
        Node* temp = new Node();  // Este es un puntero a un nodo ya creado, si fuera Node* temp; es a un nodo que no existe aún
        // definimos como será nuestro temp
        temp->data = value;
        temp->next = NULL;
        while(head->next != NULL){
            // porque head es un puntero a un nodo en ese momento el cual puede ser o el primer o el segundo nodo, la cosa es que
            // es ese el que tomamos en ese momento y lo llamamos head
            head = head->next;
        }
        head->next = temp;
    }

    // T pop_front(); elimina el del comienzo
    T pop_front(){
        if (head == NULL){
            throw "No hay elementos en la lista";
        }
        Node* temp = head;
        head = head->next;
        // por si quieres recuperar el valor eliminado
        T value = temp->data;
        delete temp;

        return value;
    }

    /////////////////////////////////////////////////
    
    // T pop_back(); elimina el del final
    T pop_back(){
        if (head == NULL){
            throw "No hay elementos en la lista";
        }
        Node* temp = head;
        while(temp->next->next != NULL){
            temp = temp->next;
        }
        // por si quieres recuperar el valor eliminado
        T value = temp->next->data;
        delete temp->next;
        temp->next = NULL;
        return value;
    }

    // T operator[](int index); Retorna el elemento en la posición indicada
    T operator[](int index){
        Node* temp = head;
        for (int i = 0; i < index; i++){
            temp = temp->next;
        }
        return temp->data;
    }

    // bool empty(); Retorna true si la lista está vacía
    bool empty(){
        if (head == NULL){
            return true;
        }
        return false;
    }

    // int size(); Retorna el tamaño de la lista
    int size(){
        Node* temp = head;
        int size = 0;
        while(temp != NULL){
            size++;
            temp = temp->next;
        }
        return size;
    }

    // void clear(); Elimina todos los elementos de la lista
    void clear(){
        Node* temp = head;
        while(temp != NULL){
            head = head->next;
            delete temp;
            temp = head;
        }
    }

    // void sort(); Implemente un algoritmo de ordenacion con listas enlazadas !!!
    void sort(){
        Node* temp = head;
        Node* temp2 = head;
        int size = 0;
        while(temp != NULL){
            size++;
            temp = temp->next;
        }
        for (int i = 0; i < size; i++){
            temp = head;
            temp2 = head->next;
            for (int j = 0; j < size-1; j++){
                if (temp->data > temp2->data){
                    int aux = temp->data;
                    temp->data = temp2->data;
                    temp2->data = aux;
                }
                temp = temp->next;
                temp2 = temp2->next;
            }
        }
    }

    // void reverse(); Revierte la lista
    void reverse(){
        Node* temp = head;
        Node* temp2 = head;
        int size = 0;
        while(temp != NULL){
            size++;
            temp = temp->next;
        }
        for (int i = 0; i < size; i++){
            temp = head;
            temp2 = head->next;
            for (int j = 0; j < size-1; j++){
                if (temp->data < temp2->data){
                    int aux = temp->data;
                    temp->data = temp2->data;
                    temp2->data = aux;
                }
                temp = temp->next;
                temp2 = temp2->next;
            }
        }
    }
};


int main(){

    // try some methods
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    list.push_front(4);
    list.push_front(5);

    cout << endl << "front: " << list.front() << endl;
    cout << "back: " << list.back() << endl;
    cout << "pop_front: " << list.pop_front() << endl;
    cout << "pop_back: " << list.pop_back() << endl;
    cout << "operator[]: " << list[2] << endl;
    cout << "empty: " << list.empty() << endl;
    cout << "size: " << list.size() << endl;
    cout << "sort: ";
    list.sort();
    for (int i = 0; i < list.size(); i++){
        cout << list[i] << " ";
    }
    cout << endl << "reverse: ";
    list.reverse();
    for (int i = 0; i < list.size(); i++){
        cout << list[i] << " ";
    }
    cout << endl;

}