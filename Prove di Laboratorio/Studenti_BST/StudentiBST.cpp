//Primo tentativo di Studenti BST
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Studente{
    
    private:
        int matricola;
        string nome;
        string cognome;
        float media;

    public:
        Studente(int matricola, string nome, string cognome, float media){
            this->matricola = matricola;
            this->nome = nome;
            this->cognome = cognome;
            this->media = media;
        }
        ~Studente() {}

        int getMatricola(){return matricola;}
        string getNome(){return nome;}
        string getCognome(){return cognome;}
        float getMedia(){return media;}

        void setMatricola(int matricola){this->matricola = matricola;}
        void setNome(string nome){this->nome = nome;}
        void setCognome(string cognome){this->cognome = cognome;}
        void setMedia(float media){this->media = media;}

        void stampa(){
            cout << matricola << " - " << nome << " " << cognome << " media: " << media << endl;
        }
};

class Nodo{
    
    private:
        Studente* data;
        Nodo* parent;
        Nodo* sx;
        Nodo* dx;

    public:
        Nodo(Studente* data, Nodo* parent, Nodo* sx, Nodo* dx)
        : data(data), parent(parent), sx(sx), dx(dx) {}
        ~Nodo() {}

        Studente* getData(){return data;}
        Nodo* getParent(){return parent;}
        Nodo* getSx(){return sx;}
        Nodo* getDx(){return dx;}

        void setData(Studente* data){this->data = data;}
        void setParent(Nodo* parent){this->parent = parent;}
        void setSx(Nodo* sx){this->sx = sx;}
        void setDx(Nodo* dx){this->dx = dx;}
};

class BST{
    
    private:
        Nodo* root;
        int size;

    public:
        BST(): root(nullptr), size(0) {}
        ~BST() {}

        Nodo* getRoot(){return root;}

        void TreeInsert(Studente* value)
        {
            Nodo* x = root;
            Nodo* y = nullptr;

            while(x != nullptr){
                y = x;
                if(value->getMatricola() < x->getData()->getMatricola()){
                    x = x->getSx();
                } else {
                    x = x->getDx();
                }
            }

            Nodo* newnode = new Nodo(value, y, nullptr, nullptr);
            if(y == nullptr){
                root = newnode;
            } else if(newnode->getData()->getMatricola() < y->getData()->getMatricola()){
                y->setSx(newnode);
            } else {
                y->setDx(newnode);
            }
            size++;
        }

        void TreeSearch(int m)
        {
            Nodo* tmp = root;
            while(tmp != nullptr && m != root->getData()->getMatricola()){
                if(m < tmp->getData()->getMatricola()){
                    cout << "Sono a sinistra" << endl;
                    tmp = tmp->getSx();
                } else if(m >= tmp->getData()->getMatricola()){
                    cout << "Sono a destra" << endl;
                    tmp = tmp->getDx();
                }
            }
            tmp->getData()->stampa(); 
        }

        void inOrder(Nodo* p)
        {
            if(p){
                inOrder(p->getSx());
                p->getData()->stampa();
                inOrder(p->getDx());
            }
        }

};

void readFile(BST &tree)
{
    ifstream inFile;
    inFile.open("input.txt");
    if(!inFile.is_open()){
        cerr << "Errore: Impossibile aprire il file." << endl;
        exit(EXIT_FAILURE);
    }

    int matricola;
    string nome;
    string cognome;
    float media;

    while(!inFile.eof()){
        string buffer;

        getline(inFile, buffer, ',');
        matricola = stoi(buffer);
        getline(inFile, buffer, ',');
        nome = buffer;
        getline(inFile, buffer, ',');
        cognome = buffer;
        getline(inFile, buffer);
        media = stof(buffer);

        Studente* stud = new Studente(matricola, nome, cognome, media);
        tree.TreeInsert(stud);

    }
    inFile.close();
}

int main(int argc, char* argv[])
{
    BST tree;
    readFile(tree);

    int n;
    cout << "Inserisci un numero di matricola da cercare e stampare: " << endl;
    cin >> n;
    tree.TreeSearch(n);

    cout << endl;
    cout << "BST di studenti:" << endl;
    tree.inOrder(tree.getRoot());
}