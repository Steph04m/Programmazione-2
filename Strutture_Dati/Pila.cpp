//Pila di interi
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

class Pila{
    private:
        int size;
        Nodo* head;

    public:
        Pila() : size(0), head(nullptr) {}
        ~Pila() {
            clearStack();
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

        void Push(int n)
        {
            Nodo* newnode = new Nodo(n, nullptr);
            if(head == nullptr){
                head = newnode;
            } else {
                newnode->setNext(head);
                head = newnode;
            }
            size++;
        }

        void Pop()
        {
            if(isEmpty()){
                cerr << "Errore: La Pila è vuota." << endl;
                exit(EXIT_FAILURE);
            }
            Nodo* tmp = head;
            head = head->getNext();
            delete tmp;
            size--;
        }

        void printStack()
        {
            if(isEmpty()){
                cerr << "Errore: La pila è vuota, non c'è nulla stampare." << endl;
                exit(EXIT_FAILURE);
            }
            
            Nodo* tmp = head;
            while(tmp != nullptr){
                cout << tmp->getData() << " ";
                tmp = tmp->getNext();
            }
            cout << endl;
        }

        void clearStack()
        {
            while(!isEmpty()){
                Nodo* tmp = head;
                head = head->getNext();
                delete tmp;
                size--;
            }
            cout << "Pila eliminata al termine del programma." << endl;
        }
};

int main(int argc, char* argv[])
{
    Pila S;
    S.Push(1);
    S.Push(3);
    S.Push(5);
    S.Push(7);
    S.Push(9);
    S.Push(2);
    S.Push(4);
    S.Push(6);
    S.Push(8);

    cout << "Contenuto Pila: " << endl;
    S.printStack(); 

    S.Pop();
    S.Pop();

    cout << "Contenuto Pila dopo due Pop: " << endl;
    S.printStack();
}
