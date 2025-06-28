//Implementazione di un Albero Binario di Ricerca (BST) di Interi 
#include <iostream>
#include <string>

using namespace std;

class Nodo{

    private:
        int data;
        Nodo* parent;
        Nodo* dx;
        Nodo* sx;

    public:
        Nodo(int data, Nodo* parent, Nodo* dx, Nodo* sx)
        : data(data), parent(parent), dx(dx), sx(sx) {}
        ~Nodo() {}

        int getData(){return data;}
        Nodo* getParent(){return parent;}
        Nodo* getDx(){return dx;}
        Nodo* getSx(){return sx;}

        void setData(int data){this->data = data;}
        void setParent(Nodo* parent){this->parent = parent;}
        void setDx(Nodo* dx){this->dx = dx;}
        void setSx(Nodo* sx){this->sx = sx;}
};

class BST{

    private:
        Nodo* root;
        int size;

    public:
        BST() : root(nullptr), size(0) {}
        ~BST() {}

        Nodo* getRoot(){return root;}

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

        void PreOrder(Nodo* p)
        {
            if(p){
                cout << p->getData() << " "; // visita la radice
                PreOrder(p->getSx());    // visita il sottoalbero sinistro
                PreOrder(p->getDx());      // visita il sottoalbero destro
            }
        }

        void InOrder(Nodo *p)
        {
            if (p){
                InOrder(p->getSx());     // visita il sottoalbero sinistro
                cout << p->getData() << " ";  // visita la radice
                InOrder(p->getDx());       // visita il sottoalbero destro
            }
        }

        void PostOrder(Nodo *p)
        {
            if(p){
                PostOrder(p ->getSx());   // visita il sottoalbero sinistro
                PostOrder(p ->getDx());     // visita il sottoalbero destro
                cout << p ->getData() << " ";     // visita la radice
            }
        }   

        Nodo* TreeSearch(Nodo* tmp, int n) //Versione Ricorsiva
        {
            if(root == nullptr || n == root->getData()){
                return root;
            } else if(n < root->getData()){
                tmp = root;
                TreeSearch(tmp->getSx(), n);
            } else {
                tmp = root;
                TreeSearch(tmp->getDx(), n);
            }
        }

        Nodo* IterativeTreeSearch(int n)
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

        Nodo* TreeMaximum(Nodo* x)
        {
            x = root;
            while(x->getDx() != nullptr){
                x = x->getDx();
            }
            return x;
        }

        Nodo* TreeMinimum(Nodo* x)
        {
            x = root;
            while(x->getSx() != nullptr){
                x = x->getSx();
            }
            return x;
        }

        Nodo* TreeSuccessor(Nodo* x)
        {
            if(x->getDx() != nullptr){
                return TreeMinimum(x->getDx());
            }
            
            Nodo* y = x->getParent();
            while(y != nullptr && x == y->getDx()){
                x = y;
                y = y->getParent();
            }
            return y;
        }

        Nodo* TreePredecessor(Nodo* x)
        {
            if(x->getSx() != nullptr){
                return TreeMaximum(x->getSx());
            }
        
            Nodo* y = x->getParent();
            while(y != nullptr && x == y->getSx()){
                x = y;
                y = y->getParent();
            }
            return y;
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
};

int main()
{
    BST Tree;
    Tree.TreeInsert(5);
    Tree.TreeInsert(2);
    Tree.TreeInsert(6);
    Tree.TreeInsert(7);
    Tree.TreeInsert(4);
    Tree.TreeInsert(1);
    Tree.TreeInsert(9);
    Tree.TreeInsert(3);
    Tree.TreeInsert(8);

    cout << "Contenuto BST (InOrder): " << endl;
    Tree.InOrder(Tree.getRoot());
    cout << endl;
    cout << "Contenuto BST (PreOrder): " << endl;
    Tree.PreOrder(Tree.getRoot());
    cout << endl;
    cout << "Contenuto BST (PostOrder): " << endl;
    Tree.PostOrder(Tree.getRoot());
    cout << endl;

        while(1){
        int n;
        cout << "Inserisci un valore da cercare nell'albero: " << endl;
        cin >> n;
        Nodo* x = Tree.IterativeTreeSearch(n);
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