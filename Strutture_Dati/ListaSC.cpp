//Lista Singolarmente Concatenata di interi
#include <iostream>
#include <string>

using namespace std;

class Nodo{

    private:
        int data;
        Nodo* next;

    public:
        Nodo(int data, Nodo* next)
        : data(data), next(next) {}
        ~Nodo(){}

        int getData() const {return data;}
        Nodo* getNext() const {return next;}

        void setData(int data){this->data = data;}
        void setNext(Nodo* next){this->next = next;}
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
            Nodo* newnode = new Nodo(n, nullptr);
            if(head == nullptr){
                head = newnode;
            } else if(newnode->getData() <= head->getData()){
                newnode->setNext(head);
                head = newnode;
            } else {
                Nodo* current = head;
                while(current->getNext() != nullptr && newnode->getData() > current->getNext()->getData()){
                    current = current->getNext();
                }
                newnode->setNext(current->getNext());
                current->setNext(newnode);
            }
            size++;
        }
        
        void Remove(int n)
        {
            if(isEmpty()){
                cerr << "Errore: La lista è vuota, impossibile rimuovere " << n << endl;
                exit(EXIT_FAILURE);
            }

            Nodo* current = head;
            Nodo* prev = nullptr;

            while(current != nullptr && n != current->getData()){
                prev = current;
                current = current->getNext();
            }

            if(current == nullptr){
                cout << "Elemento non presente nella lista." << endl;
                exit(EXIT_SUCCESS);
            } 

            if(prev == nullptr){
                head = head->getNext();
            } else {
                prev->setNext(current->getNext());
            }
            delete current;
            size--;
        }

        void printList()
        {
            if(isEmpty()){
                cerr << "Errore: La lista è vuota, non c'è nulla stampare." << endl;
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
            while(!isEmpty()){
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
    list.Insert(4);
    list.Insert(8);
    list.Insert(1);
    list.Insert(5);
    list.Insert(3);
    list.Insert(9);
    list.Insert(7);

    cout << "Contenuto della Lista: " << endl;
    list.printList();

    int n;
    cout << "Inserisci un numero da eliminare: ";
    cin >> n;
    cout << endl;
    list.Remove(n);

    cout << "Contenuto della lista dopo l'eliminazione: " << endl;
    list.printList();
}