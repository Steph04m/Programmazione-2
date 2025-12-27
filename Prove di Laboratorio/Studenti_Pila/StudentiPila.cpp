#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Studente{
    
    private:
        int matricola;
        string nome;
        string cognome;
        float media;

    public:
        Studente(int matricola, string nome, string cognome, float media)
        : matricola(matricola), nome(nome), cognome(cognome), media(media) {}
        virtual ~Studente() {}

        int getMatricola(){return matricola;}
        string getNome(){return nome;}
        string getCognome(){return cognome;}
        float getMedia(){return media;}

        virtual void stampa(){
            cout << matricola << ": " << nome << " " << cognome << " - media " << media << endl;
        }
};

class BorsaDiStudio{

    private:
        float importo;
        int durata;

    public:
        BorsaDiStudio(float importo, int durata) : importo(importo), durata(durata) {}
        ~BorsaDiStudio() {}

        float getImporto(){return importo;}
        int getDurata(){return durata;}

        void setImporto(float importo){this->importo = importo;}
        void setDurata(int durata){this->durata = durata;}
};

class StudenteBorsista : public Studente{

    private:
        BorsaDiStudio* borsa;

    public:
        StudenteBorsista(int matricola, string nome, string cognome, float media, BorsaDiStudio* borsa)
        : Studente(matricola, nome, cognome, media), borsa(borsa) {}
        ~StudenteBorsista() {}

        BorsaDiStudio* getImportoBorsa(){return borsa;}

        void stampa() override{
            cout << getMatricola() << ": " << getNome() << " " << getCognome() << " - media " << getMedia() << " [borsa di " << getImportoBorsa() << " euro]" << endl;
        }
};

class Nodo{

    private:
        Studente data;
        Nodo* next;

    public:
        Nodo(Studente data, Nodo* next)
        : data(data), next(next) {}
        ~Nodo() {}

        Studente getData(){return data;}
        Nodo* getNext(){return next;}

        void setData(Studente data){this->data = data;}
        void setNext(Nodo* next){this->next = next;}
};

class Pila{

    private:
        Nodo* head;
        int size;

    public:
        Pila(): head(nullptr), size(0) {}
        ~Pila() {}

        bool isEmpty(){
            if(size == 0){
                return true;
            } else {
                return false;
            }
        }

        void push(Studente* data)
        {
            Nodo* newnode = new Nodo(*data, nullptr);
            if(newnode == nullptr){
                cerr << "Errore: Impossibile allocare il nodo." << endl;
                exit(EXIT_FAILURE);
            }

            if(head == nullptr){
                head = newnode;
            } else {
                newnode->setNext(head);
                head = newnode;
            }
            size++;
        }

        Studente* pop()
        {
            if(isEmpty() == true){
                cerr << "Errore: La pila è vuota." << endl;
                exit(EXIT_FAILURE);
            }

            Nodo* tmp = head;
            Studente* nodeData = tmp->getData();
            head = head->getNext();
            delete tmp;
            return nodeData;
            size--;
        }

        void printList()
        {
            Nodo* tmp = head;
            while(tmp != nullptr){
                tmp->getData().stampa();
                tmp = tmp->getNext();
            }
        }

        void checkList()
        {
            Nodo* tmp = head;
            int counter = 0;
            Pila tmpStack;
            while(tmp != nullptr && tmp->getData().getMedia() < 25){
                Studente* nodeValue = pop();
                tmpStack.push(nodeValue);
                tmp = tmp->getNext();
                counter++;
                size--;
            }

            Studente* rimosso = pop();
            rimosso->stampa();

            while(counter != 0){
                Studente* nodeValue = tmpStack.pop();
                push(nodeValue);
                size++;
                counter--;
            }
        }


};

void readFile(Pila &pila)
{
    ifstream inFile;

    inFile.open("input.txt");
    if(!inFile.is_open()){
        cerr << "Errore: Impossibile aprile il file" << endl;
        exit(EXIT_FAILURE);
    }

    int matricola;
    string nome;
    string cognome;
    float media;
    float importo;
    int durata;

    while(!inFile.eof()){
        inFile >> matricola >> nome >> cognome >> media >> importo >> durata;
        
        if(importo == 0){
            pila.push(new Studente(matricola, nome, cognome, media));
        } else {
            BorsaDiStudio* borsaStudente = new BorsaDiStudio(importo, 0);
            pila.push(new StudenteBorsista(matricola, nome, cognome, media, borsaStudente));
        }
    }
    
    inFile.close();
}

int main()
{
    Pila pila;
    readFile(pila);
    
    cout << "La Pila Originale contiene i seguenti Studenti:" << endl;
    pila.printList();

    cout << endl;
    pila.checkList();
}