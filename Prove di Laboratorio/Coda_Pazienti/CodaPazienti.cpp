#include <iostream>
#include <string>
#include <cstring>

using namespace std;

class Patient{

    private:
        int id;
        string name;
        bool condition;

    public:
        Patient(int id, string name, bool condition)
        : id(id), name(name), condition(condition) {}
        ~Patient() {}

        int getId(){return id;}
        string getName(){return name;}
        bool getCondition(){return condition;}

        void setId(int id){this->id = id;}
        void setName(string name){this->name = name;}
        void setCondition(bool condition){this->condition = condition;}

        void stampa(){
            cout << id << " - " << name << " - " << condition << endl;
        }
};

template <typename T>
class Nodo{
    
    private:
        T data;
        Nodo<T>* next;
        Nodo<T>* prev;

    public:
        Nodo(T data, Nodo<T>* next, Nodo<T>* prev) : data(data), next(next), prev(prev) {}
        ~Nodo() {}

        T getData() const {return data;}
        Nodo<T>* getNext() const {return next;}
        Nodo<T>* getPrev() const {return prev;}

        void setData(const T& data){this->data = data;}
        void setNext(Nodo<T>* next){this->next = next;}
        void setPrev(Nodo<T>* prev){this->prev = prev;}
};

template <typename T>
class Coda{ //Implementato come Coda Doppia!

    private:
        Nodo<T>* head;
        Nodo<T>* tail;
        int size;

    public:
        Coda() : head(nullptr), tail(nullptr), size(0) {}
        ~Coda(){
            svuotaCoda();
        }

        bool isEmpty(){
            if(size == 0){
                return true;
            } else {
                return false;
            }
        }

        void enqueue(T data)
        {
            Nodo<T>* newnode = new Nodo<T>(data, nullptr, nullptr);
            if(newnode == nullptr){
                cerr << "Errore: Impossibile allocare il nodo." << endl;
                exit(EXIT_FAILURE);
            }

            if(tail == nullptr){
                tail = head = newnode;
            } else {
                tail->setNext(newnode);
                newnode->setPrev(tail);
                tail = newnode;
            }
            size++;
        }

        T dequeueHead()
        {
            if(isEmpty() == true){
                cerr << "Errore: La coda è vuota." << endl;
                exit(EXIT_FAILURE);
            }

            Nodo<T>* tmp = head;
            T nodeData = tmp->getData();
            if(head == tail){
                head = tail = nullptr;
            } else {
                head = head->getNext();
                head->setPrev(nullptr);
            }
            delete tmp;
            size--;
            return nodeData;
        }

        T dequeueTail()
        {
            if(isEmpty() == true){
                //cerr << "Errore: La coda è vuota." << endl;
                //exit(EXIT_FAILURE);
                throw runtime_error("Errore: La coda è vuota.");
            }

            Nodo<T>* tmp = tail;
            T nodeData = tmp->getData();
            if(head == tail){
                head = tail = nullptr;
            } else {
                tail = tail->getPrev();
                tail->setNext(nullptr);
            }
            delete tmp;
            size--;
            return nodeData;
        }

        void enQueuePriority(T data)
        {
            if(isEmpty() == true){
                enqueue(data);
            }

            int counter = 0;
            Coda<Patient> TmpQ;
            while(tail != nullptr && counter < 3){
                T nodeValue = dequeueTail();
                TmpQ.enqueue(nodeValue);
                counter++;
            }

            enqueue(data);
            while(counter != 0){
                T nodeValue = TmpQ.dequeueTail();
                enqueue(nodeValue);
                counter--;
            }
        }

        void printQueue()
        {
            Nodo<T>* tmp = head;
            while(tmp != nullptr){
                tmp->getData().stampa();
                tmp = tmp->getNext();
            }
        }

        void svuotaCoda()
        {   
            while(head != nullptr){
                Nodo<T>* tmp = head;
                head = head->getNext();
                delete tmp;
            }
            tail = nullptr;
            size = 0;
        }
};

int main(int argc, char* argv[])
{
    Patient paziente1(1, "Stefano", false);
    Patient paziente2(2, "Elena", false);
    Patient paziente3(3, "Alessandro", false);
    Patient paziente4(4, "Gianluca", false);
    Patient paziente5(5, "Gabriella", true);
    Patient paziente6(6, "Giulia", false);
    Patient paziente7(7, "Vincenzo", true);

    Coda<Patient> Queue;

    Queue.enqueue(paziente1);
    Queue.enqueue(paziente2);
    Queue.enqueue(paziente3);
    Queue.enqueue(paziente4);
    Queue.enQueuePriority(paziente5);
    Queue.enqueue(paziente6);
    Queue.enQueuePriority(paziente7);

    cout << "Coda di Pazienti:" << endl;
    Queue.printQueue();
}
