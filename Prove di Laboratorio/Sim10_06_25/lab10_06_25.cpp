#include <iostream>
#include <string>

using namespace std;

class Nodo{

    private:
        int data;
        Nodo* parent;
        Nodo* sx;
        Nodo* dx;

    public:
        Nodo(int data, Nodo* parent, Nodo* sx, Nodo* dx)
        : data(data), parent(parent), sx(sx), dx(dx) {}
        ~Nodo() {}

        int getData() {return data;}
        Nodo* getSx() {return sx;}
        Nodo* getDx() {return dx;}
        Nodo* getParent() const {return parent;}

        void setData(int data){this->data = data;}
        void setSx(Nodo* sx){this->sx = sx;}
        void setDx(Nodo* dx){this->dx = dx;}
        void setParent(Nodo* parent){this->parent = parent;}
};

class BST{

    private:
        int size;
        Nodo* root;

    public:
        BST() : size(0), root(nullptr) {}
        ~BST(){
            svuotaBST(root);
        }

        int getSize() const {return size;}
        Nodo* getRoot() const {return root;}

        bool isEmpty(){
            if(size == 0){
                return true;
            } else {
                return false;
            }
        }

        void TreeInsert(int n)
        {
            Nodo* x = root;
            Nodo* y = nullptr;

            while(x != nullptr){
                y = x;
                if(n < x->getData()){
                    x = x->getSx();
                } else {
                    x = x->getDx();
                }
            }

            Nodo* newnode = new Nodo(n, y, nullptr, nullptr);
            if(y == nullptr){
                root = newnode;
            } else if(newnode->getData() < y->getData()){
                y->setSx(newnode);
            } else {
                y->setDx(newnode);
            }
            size++;
        }

        void InOrder(Nodo* x)
        {
            if(x){
                InOrder(x->getSx());
                cout << x->getData() << " ";
                InOrder(x->getDx());
            }
        }

        Nodo* TreeMinimum(Nodo* x)
        {
            if(isEmpty() == true){
                cout << "Il BST è vuoto." << endl;
                exit(EXIT_FAILURE);
            }
            
            x = root;
            while(x->getSx() != nullptr){
                x = x->getSx();
            }
            return x;
        }

        Nodo* TreeMaximum(Nodo* x)
        {
            if(isEmpty() == true){
                cout << "Il BST è vuoto." << endl;
                exit(EXIT_FAILURE);
            }
            
            x = root;
            while(x->getDx() != nullptr){
                x = x->getDx();
            }
            return x;
        }

        Nodo* TreeSearch(int n)
        {
            Nodo* x = root;
            while(x != nullptr){
                if(x->getData() == n){
                    return x;
                } else if(n < x->getData()){
                    x = x->getSx();
                } else {
                    x = x->getDx();
                }
            }
            return nullptr;
        }

        void Transplant(Nodo* u, Nodo* v)
        {
            if(u->getParent() == nullptr){
                root = v;
            } else if(u == u->getParent()->getSx()){
                u->getParent()->setSx(v);
            } else {
                u->getParent()->setDx(v);
            }
            if(v != nullptr){
                v->setParent(u->getParent());
            }
        }

        void TreeDelete(Nodo* z)
        {
            if(isEmpty() == true){
                cout << "Il BST è vuoto." << endl;
                exit(EXIT_FAILURE);
            }

            if(z->getSx() == nullptr){
                Transplant(z, z->getDx());
            } else if(z->getDx() == nullptr){
                Transplant(z, z->getSx());
            } else {
                Nodo* y = TreeMinimum(z->getDx());
                if(y->getParent() != z){
                    Transplant(y, y->getDx());
                    y->setDx(z->getDx());
                    if(y->getDx() != nullptr){
                        y->getDx()->setParent(y);
                    }
                }
                Transplant(z, y);
                y->setSx(z->getSx());
                if(y->getSx() != nullptr){
                    y->getSx()->setParent(y);
                }
            }

            delete z;
            size--;
        }

        void svuotaBST(Nodo* x)
        {
            if(x != nullptr){
                svuotaBST(x->getSx());
                svuotaBST(x->getDx());
                delete x;
                x = nullptr;
                size--;
            } else {
                return;
            }
        }
};

int main(int argc, char* argv[])
{
    BST Tree;

    while(1){
        int n;
        cout << "Inserisci un numero intero positivo da inserire nell'albero (-1 per terminare): "  << endl;
        cin >> n;
        if(n != -1){
            Tree.TreeInsert(n);   
        } else{
            break;
        }
    }
    
    cout << "Elementi dell'albero in ordine crescente:" << endl;
    Tree.InOrder(Tree.getRoot());
    cout << endl;
    cout << endl;

    Nodo* Nmin = Tree.TreeMinimum(Tree.getRoot());
    int min = Nmin->getData();
    cout << "Valore minimo nell'albero: " << min << endl;
    cout << endl;
    Nodo* Nmax = Tree.TreeMaximum(Tree.getRoot());
    int max = Nmax->getData();
    cout << "Valore massimo nell'albero: " << max << endl;
    cout << endl;

    while(1){
        int n;
        cout << "Inserisci un valore da cercare nell'albero: " << endl;
        cin >> n;
        Nodo* x = Tree.TreeSearch(n);
        if(x != nullptr){
            cout << "Il valore " << n << " è presente nell'albero." << endl;
            char c;
            cout << "Vuoi cancellare il nodo? Inserisci y o n" << endl;
            cin >> c;
            if(c == 'y'){
                Tree.TreeDelete(x);
                cout << "Ristampa del BST: " << endl;
                Tree.InOrder(Tree.getRoot());
                cout << endl;
            } else if(c == 'n'){
                exit(EXIT_SUCCESS);
            }
        } else {
            cout << "Il valore " << n << " NON è presente nell'albero." << endl;
            break;
        }
    }
}