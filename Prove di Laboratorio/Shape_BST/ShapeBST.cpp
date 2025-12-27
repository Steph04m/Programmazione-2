#include <iostream>
#include <string>

using namespace std;

class Shape{

    protected:
        double area;

    public:
        Shape(double area)
        : area(area) {}
        virtual ~Shape() {}

        virtual double getArea() = 0;
        virtual void stampa(){
            cout << "Area della figura: " << area << endl;
        }
};

class Rettangolo : public Shape{

    public:
        Rettangolo(double area)
        : Shape(area) {}
        ~Rettangolo() {}

        double getArea() override {return area;}
        void setArea(double area){this->area = area;}

        void stampa() override {
            cout << "Figura: Rettangolo - Area: " << getArea() << endl;
        }
};

class Circonferenza : public Shape{

    public:
        Circonferenza(double area)
        : Shape(area) {}
        ~Circonferenza() {}

        double getArea() override {return area;}
        void setArea(double area){this->area = area;}
        
        void stampa() override {
            cout << "Figura: Circonferenza - Area: " << getArea() << endl;
        }
};

class Triangolo : public Shape{

    public:
        Triangolo(double area)
        : Shape(area) {}
        ~Triangolo() {}

        double getArea() override {return area;}
        void setArea(double area){this->area = area;}
        
        void stampa() override {
            cout << "Figura: Triangolo - Area: " << getArea() << endl;
        }
};

template <typename T>
class Nodo{

    private:
        T* data;
        Nodo<T>* parent;
        Nodo<T>* sx;
        Nodo<T>* dx;

    public:
        Nodo(T* data, Nodo<T>* parent, Nodo<T>* sx, Nodo<T>* dx)
        : data(data), parent(parent), sx(sx), dx(dx) {}
        ~Nodo() {}

        T* getData() const {return data;}
        Nodo<T>* getParent() const {return parent;}
        Nodo<T>* getSx() const {return sx;}
        Nodo<T>* getDx() const {return dx;}

        void setData(T* data){this->data = data;}
        void setParent(Nodo<T>* parent){this->parent = parent;}
        void setSx(Nodo<T>* sx){this->sx = sx;}
        void setDx(Nodo<T>* dx){this->dx = dx;}
};

template <typename T>
class BST{

    private:
        Nodo<T>* root;
        int size;

    public:
        BST() : root(nullptr), size(0) {}
        ~BST() {
            svuotaBST(root);
        }

        Nodo<T>* getRoot() const {return root;}
        int getSize() const {return size;}

        bool isEmpty(){
            if(size == 0){
                return true;
            } else {
                return false;
            }
        }

        void TreeInsert(T* n)
        {
            Nodo<T>* x = root;
            Nodo<T>* y = nullptr;
            while(x != nullptr){
                y = x;
                if(n->getArea() < x->getData()->getArea()){
                    x = x->getSx();
                } else {
                    x = x->getDx();
                }
            }

            Nodo<T>* newnode = new Nodo<T>(n, y, nullptr, nullptr);
            if(newnode == nullptr){
                cerr << "Errore: impossibile allocare il nuovo nodo." << endl;
                exit(EXIT_FAILURE);
            }

            if(y == nullptr){
                root = newnode;
            } else if(newnode->getData()->getArea() < y->getData()->getArea()){
                y->setSx(newnode);
            } else {
                y->setDx(newnode);
            }
            size++;
        }

        void inOrder(Nodo<T>* p)
        {
            if(p){
                inOrder(p->getSx());
                p->getData()->stampa();
                inOrder(p->getDx());
            }
        }

        Nodo<T>* TreeSearch(int n)
        {
            Nodo<T>* x = root;
            while(x != nullptr){
                if(x->getData()->getArea() == n){
                    return x;
                } else if(n < x->getData()->getArea()){
                    x = x->getSx();
                } else {
                    x = x->getDx();
                }
            }
            return nullptr;
        }

        Nodo<T>* TreeMinimum()
        {
            Nodo<T>* x = root;
            while(x->getSx() != nullptr){
                x = x->getSx();
            }
            return x;
        }

        void Transplant(Nodo<T>* u, Nodo<T>* v)
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

        void TreeDelete(Nodo<T>* z)
        {
            if(isEmpty() == true){
                cerr << "Errore: Il BST è vuoto." << endl;
                exit(EXIT_FAILURE);
            }

            if(z->getSx() == nullptr){
                Transplant(z, z->getDx());
            } else if(z->getDx() == nullptr){
                Transplant(z, z->getSx());
            } else {
                Nodo<T>* y = TreeMinimum();
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
            delete z->getData();
            delete z;
            size--;
        }

        void checkTree(double n)
        {
            Nodo<T>* x = root;
            while(x != nullptr){
                Nodo<T>* tmp = TreeMinimum();
                if(tmp->getData()->getArea() < n){
                    TreeDelete(tmp);
                    x = root;
                } else {
                    x = x->getDx();
                }
            }
        }

        void svuotaBST(Nodo<T>* x)
        {
            if(x != nullptr){
                svuotaBST(x->getSx());
                svuotaBST(x->getDx());
                delete x;
                x = nullptr;
            } else {
                return;
            }
        }
};

template <typename T, typename S>
void mergeBST(BST<T>& tree, Nodo<S>* x)
{
    if(x != nullptr){
        tree.TreeInsert(static_cast<T*>(x->getData()));
        mergeBST(tree, x->getSx());
        mergeBST(tree, x->getDx());
    }
}

int main(int argc, char* argv[])
{
    Rettangolo* rettangolo1 = new Rettangolo(30);
    Rettangolo* rettangolo2 = new Rettangolo(40);
    Rettangolo* rettangolo3 = new Rettangolo(50);
    Rettangolo* rettangolo4 = new Rettangolo(20);
    Circonferenza* circonferenza1 = new Circonferenza(35);
    Circonferenza* circonferenza2 = new Circonferenza(45);
    Circonferenza* circonferenza3 = new Circonferenza(65);
    Circonferenza* circonferenza4 = new Circonferenza(15);
    Triangolo* triangolo1 = new Triangolo(25);
    Triangolo* triangolo2 = new Triangolo(55);
    Triangolo* triangolo3 = new Triangolo(45);
    Triangolo* triangolo4 = new Triangolo(85);
    
    BST<Rettangolo> Rtree;
    BST<Circonferenza> Ctree;
    BST<Triangolo> Ttree;

    Rtree.TreeInsert(rettangolo1);
    Rtree.TreeInsert(rettangolo2);
    Rtree.TreeInsert(rettangolo3);
    Rtree.TreeInsert(rettangolo4);

    Ctree.TreeInsert(circonferenza1);
    Ctree.TreeInsert(circonferenza2);
    Ctree.TreeInsert(circonferenza3);
    Ctree.TreeInsert(circonferenza4);

    Ttree.TreeInsert(triangolo1);
    Ttree.TreeInsert(triangolo2);
    Ttree.TreeInsert(triangolo3);
    Ttree.TreeInsert(triangolo4);

    cout << "BST di Rettangoli: " << endl;
    Rtree.inOrder(Rtree.getRoot());
    cout << endl;

    cout << "BST di Circoferenze: " << endl;
    Ctree.inOrder(Ctree.getRoot());
    cout << endl;

    cout << "BST di Triangoli: " << endl;
    Ttree.inOrder(Ttree.getRoot());
    cout << endl;

    double n;
    cout << "Inserisci un'area. Le figure con un'area inferiore verranno eliminate." << endl;
    cin >> n;
    Rtree.checkTree(n);
    Ctree.checkTree(n);
    Ttree.checkTree(n);

    cout << "BST di Rettangoli dopo l'eliminazione: " << endl;
    Rtree.inOrder(Rtree.getRoot());
    cout << endl;

    cout << "BST di Circoferenze dopo l'eliminazione: " << endl;
    Ctree.inOrder(Ctree.getRoot());
    cout << endl;

    cout << "BST di Triangoli dopo l'eliminazione: " << endl;
    Ttree.inOrder(Ttree.getRoot());
    cout << endl;

    BST<Shape> Stree;

    mergeBST(Stree, Rtree.getRoot());
    mergeBST(Stree, Ctree.getRoot());
    mergeBST(Stree, Ttree.getRoot());
    cout << "BST con tutte le figure rimaste: " << endl;
    Stree.inOrder(Stree.getRoot());
    cout << endl;
}