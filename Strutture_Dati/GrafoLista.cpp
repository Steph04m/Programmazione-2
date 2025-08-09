//Implementazione di un Grafo con Liste di Adiacenza
#include <iostream>
#include <string>
#include <climits>

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
        Nodo* head;
        Nodo* tail;
        int size;

    public:
        Lista(): head(nullptr), tail(nullptr), size(0) {}
        ~Lista() {}

        Nodo* getHead() const {return head;}
        int getSize() const {return size;}

        bool isEmpty(){
            if(size == 0){
                return true;
            } else {
                return false;
            }
        }

        void InsertHead(int n)
        {
            Nodo* newnode = new Nodo(n, nullptr, nullptr);
            if(newnode == nullptr){
                cerr << "Errore: Impossibile allocare il nuovo nodo." << endl;
                exit(EXIT_FAILURE);
            }

            if(head == nullptr){
                tail = head = newnode;
            } else {
                head->setPrev(newnode);
                newnode->setNext(head);
                head = newnode;
            }
            size++;
        }

        void InsertTail(int n)
        {
            Nodo* newnode = new Nodo(n, nullptr, nullptr);
            if(newnode == nullptr){
                cerr << "Errore: Impossibile allocare il nuovo nodo." << endl;
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

        int RemoveHead()
        {
            if(isEmpty() == true){
                cerr << "La Lista è vuota" << endl;
                exit(EXIT_FAILURE);
            }

            Nodo* tmp = head;
            int value = head->getData();
            if(head == tail){
                head = tail = nullptr; 
            } else {
                head = head->getNext();    
                head->setPrev(nullptr);
            }
            delete tmp;
            size--;
            return value;
        }

        int RemoveTail()
        {
            if(isEmpty() == true){
                cerr << "La Lista è vuota" << endl;
                exit(EXIT_FAILURE);
            }

            Nodo* tmp = tail;
            int value = tail->getData();
            if(head == tail){
                head = tail = nullptr;
            } else {
                tail = tail->getPrev();
                tail->setNext(nullptr);
            }
            delete tmp;
            size--;
            return value;
        }

        void printList()
        {
            Nodo* tmp = head;
            while(tmp != nullptr){
                cout << tmp->getData() << " ";
                tmp = tmp->getNext();
            }
        }
};

class Coda : public Lista{

    public:
        ~Coda(){}

        bool isEmpty(){
            return Lista::isEmpty();
        }

        void EnQueue(int n){
            InsertTail(n);
        }

        int DeQueueHead(){
            return RemoveHead();
        }

        int DeQueueTail(){
            return RemoveTail();
        }
};

class GrafoLista{

    private:
        Lista* Adj; //array di liste
        int n; // elementi dell'array, ovvero il numero di nodi del grafo.
        enum coloriGrafo{white, gray, black}; // colori di un nodo in base alla visita
        coloriGrafo* colArr; // array di colori

        int time = 0;
        int* dist; // array con le distanze tra i nodi
        int* fine; // solo per DFS, indica il tempo di fine scoperta
        int* pred; // predecessore del nodo visitato nel grafo


    public:
        GrafoLista(int n) : n(n) {
            Adj = new Lista[n];
            colArr = new coloriGrafo[n];
            dist = new int[n];
            fine = new int[n];
            pred = new int[n];
        }
        ~GrafoLista(){
            delete[] Adj;
            delete[] dist;
            delete[] fine;
            delete[] pred;
            delete[] colArr;
        }

        int getN() const {return n;}
        Lista& getAdj(int v) const {return Adj[v];} //dato un arco (u,v), restituisco v.

        GrafoLista& AddEdge(int u, int v){ 
            Adj[u].InsertTail(v);
            Adj[v].InsertTail(u);
            return *this;
        }

        void BFS(int s) //prende in input il nodo sorgente
        {
            if (s < 0 || s >= n) {
                cerr << "Errore: Sorgente non valida" << endl;
                return;
            }   
            
            for(int i = 0; i < n; i++){ //coloro ogni nodo del grafo di bianco
                colArr[i] = white;
                dist[i] = INT_MAX;
                pred[i] = -1;
            }

            //coloro la sorgente del grafo
            colArr[s] = gray; 
            dist[s] = 0;
            Coda Queue; // creo la coda dove verranno inseriti i nodi grigi
            Queue.EnQueue(s); // inserisco la sorgente nella coda
            
            while(Queue.isEmpty() == false){
                int u = Queue.DeQueueHead(); //estraggo il nodo in testa memorizzando il suo dato
                const Nodo* p = Adj[u].getHead(); // e creo un nodo p per visionare i nodi con cui è connesso p

                while(p != nullptr){ 
                    int v = p->getData(); //copio il dato di p in v
                    if(colArr[v] == white){  // se il colore di v è bianco
                        colArr[v] = gray; // allora lo coloro di grigio
                        dist[v] = dist[u] + 1; // aumento la distanza tra il nodo tra v e u di 1
                        pred[v] = u; // imposto il predecessore
                        Queue.EnQueue(v); // inserisco il nodo grigio nella coda
                    }
                    p = p->getNext(); // scorro la lista
                }
                colArr[u] = black; // coloro il nodo di nero, quindi il nodo è visitato
            }
        }

        void DFS()
        {
            for(int i = 0; i < n; i++){
                colArr[i] = white;
                pred[i] = -1;
            }
            time = 0;
            for(int i = 0; i < n; i++){
                if(colArr[i] == white){
                    DFS_Visit(i);
                }
            }
        }

        void DFS_Visit(int u)
        {
            colArr[u] = gray;
            dist[u] = time++;
            
            const Nodo* p = Adj[u].getHead();
            while(p != nullptr){
                int v = p->getData();
                if(colArr[v] == white){
                    pred[v] = u;
                    DFS_Visit(v);
                }
                p = p->getNext();
            }
            colArr[u] = black;
            fine[u] = time++;
        }

        void printGrafo()
        {
            for(int i = 0; i < n; i++){
                cout << "Nodo " << i << " connesso a: ";
                Adj[i].printList();
                cout << endl;
            }
        }

        void printPath(int s, int v)
        {
            if(v == s){
                cout << s << " ";
            } else if(pred[v] == -1){
                cout << "Non c'è alcun cammino tra " << s << " a " << v;
            } else {
                printPath(s, pred[v]);
                cout << v << " ";
            }
            cout << endl;
        }
};

int main()
{
    int r=0, s=1, t=2, u=3, v=4, w=5,x=6,y=7;
    
    GrafoLista g(8);
    g.AddEdge(r, v).AddEdge(r, s).AddEdge(s, w).AddEdge(w, t).AddEdge(w, x).AddEdge(x, t).AddEdge(x, u).AddEdge(t, u).AddEdge(x, y).AddEdge(y, u);
    g.printGrafo();
    cout << endl;

    g.BFS(w);
    g.printPath(s, u);

}