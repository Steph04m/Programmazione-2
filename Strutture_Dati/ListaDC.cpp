//Lista Doppiamente Concatenata di interi
#include <iostream>
#include <string>

using namespace std;

class Nodo{
    private:
        int data;
        Nodo* next;
        Nodo* prev;

    public:
        Nodo(int data, Nodo* next, Nodo* prev)
        : data(data), next(next), prev(prev) {}
        ~Nodo() {}

        int getData() const {return data;}
        Nodo* getNext() const {return next;}
        Nodo* getPrev() const {return prev;}

        void setData(int data){this->data = data;}
        void setNext(Nodo* next){this->next = next;}
        void setPrev(Nodo* prev){this->prev = prev;}
};

class Lista{
    private:
        int size;
        Nodo* head;

    public:
        Lista() : size(0), head(nullptr) {}
        ~Lista() {
            clearList();
        }

        int getSize() const {return size;}
        Nodo* getHead() const {return head;}

        bool isEmpty(){
            if(size == 0){
                return true;
            } else {
                return false;
            }
        }

        void Insert(int n)
        {
            Nodo* newnode = new Nodo(n, nullptr, nullptr);
            if(head == nullptr){
                head = newnode;
            } else if(newnode->getData() <= head->getData()){
                head->setPrev(newnode);
                newnode->setNext(head);
                head = newnode;
            } else {
                Nodo* current = head;
                while(current->getNext() != nullptr && newnode->getData() > current->getNext()->getData()){
                    current = current->getNext();
                }
                
                newnode->setPrev(current);
                newnode->setNext(current->getNext());
                current->setNext(newnode);
                if(newnode->getNext() != nullptr){
                    newnode->getNext()->setPrev(newnode);
                }
            }
            size++;
        }

        void Remove(int n)
        {
            if(isEmpty()){
                cerr << "Errore: La lista è vuota." << endl;
                exit(EXIT_FAILURE);
            }

            if(head->getData() == n){
                Nodo* tmp = head;
                head = head->getNext();
                if(head != nullptr){
                    head->setPrev(nullptr);
                }
                delete tmp;
                size--;
                return;
            }

            Nodo* current = head;
            while(current->getNext() != nullptr && current->getData() != n){
                current = current->getNext();
            }

            if(current == nullptr){
                cerr << "Errore: elemento non presente nella lista." << endl;
                exit(EXIT_FAILURE);
            }

            if(current->getPrev() != nullptr){
                current->getPrev()->setNext(current->getNext());
            }

            if(current->getNext() != nullptr){
                current->getNext()->setPrev(current->getPrev());
            }
            delete current;
            size--;
        }

        void printList()
        {
            if(isEmpty()){
                cerr << "Errore: La lista è vuota." << endl;
                exit(EXIT_FAILURE);
            }
            
            Nodo* tmp = head;
            while(tmp != nullptr){
                cout << tmp->getData() << " ";
                tmp = tmp->getNext();
            }
            cout << endl;
        }

        void clearList()
        {
            while(head != nullptr){
                Nodo* tmp = head;
                head = head->getNext();
                delete tmp;
                size--;
            }
            cout << "Lista eliminata al termine del programma." << endl;
        }
};

int main(int argc, char* argv[])
{
    Lista list;

    list.Insert(2);
    list.Insert(6);
    list.Insert(8);
    list.Insert(4);
    list.Insert(7);
    list.Insert(1);
    list.Insert(5);
    list.Insert(9);
    list.Insert(3);

    cout << "Contenuto della Lista: " << endl;
    list.printList();

    int n;
    cout << "Inserisci un elemento da eliminare: " << endl;
    cin >> n;
    list.Remove(n);

    cout << "Contenuto della Lista dopo l'eliminazione: " << endl;
    list.printList();
}
