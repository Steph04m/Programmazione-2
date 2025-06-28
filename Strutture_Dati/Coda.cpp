//Coda di interi
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

class Coda{
    private:
        int size;
        Nodo* head;
        Nodo* tail;

    public:
        Coda() : size(0), head(nullptr), tail(nullptr) {}
        ~Coda(){
            clearQueue();
        }

        int getSize() const {return size;}
        Nodo* getHead() const {return head;}
        Nodo* getTail() const {return tail;}

        bool isEmpty(){
            if(size == 0){
                return true;
            } else {
                return false;
            }
        }

        void EnQueue(int n)
        {
            Nodo* newnode = new Nodo(n, nullptr);
            if(tail == nullptr){
                head = tail = newnode;
            } else {
                tail->setNext(newnode);
                tail = newnode;
            }
            size++;
        }

        void DeQueue()
        {
            if(isEmpty()){
                cerr << "Errore: la Coda è vuota." << endl;
                exit(EXIT_FAILURE);
            }

            Nodo* tmp = head;
            if(head == tail){
                head = tail = nullptr;
            } else {
                head = head->getNext();
            }
            delete tmp;
            size--;
        }

        void printQueue()
        {
            if(isEmpty()){
                cerr << "Errore: La coda è vuota, non c'è nulla stampare." << endl;
                exit(EXIT_FAILURE);
            }
            
            Nodo* tmp = head;
            while(tmp != nullptr){
                cout << tmp->getData() << " ";
                tmp = tmp->getNext();
            }   
            cout << endl;
        }

        void clearQueue()
        {
            while(!isEmpty()){
                Nodo* tmp = head;
                head = head->getNext();
                delete tmp;
                size--;
            }
            cout << "Coda eliminata al termine del programma." << endl;
        }
};



int main(int argc, char* argv[])
{
    Coda Q;
    Q.EnQueue(2);
    Q.EnQueue(4);
    Q.EnQueue(6);
    Q.EnQueue(8);
    Q.EnQueue(1);
    Q.EnQueue(3);
    Q.EnQueue(5);
    Q.EnQueue(7);
    Q.EnQueue(9);

    cout << "Contenuto Coda: " << endl;
    Q.printQueue();

    Q.DeQueue();
    Q.DeQueue();

    cout << "Contenuto Coda dopo due DeQueue: " << endl;
    Q.printQueue();
}
