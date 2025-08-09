#include <iostream>
#include <string>

using namespace std;

class GrafoMatrice{

    private:
        int** Adj;
        int n;
        enum coloriGrafo{white, gray, black}; // colori di un nodo in base alla visita
        coloriGrafo* colArr; // array di colori

        int* dist; // array con le distanze tra i nodi
        int* pred; // predecessore del nodo visitato nel grafo

    public:
        GrafoMatrice(int n) : n(n){
            Adj = new int*[n];
            for(int i = 0; i < n; i++){
                Adj[i] = new int[n];
                for(int j = 0; j < n; j++){
                    Adj[i][j] = 0;
                }
            }
        }

        ~GrafoMatrice(){
            for(int i = 0; i < n; i++){
                delete[] Adj[i];
            }
            delete[] Adj;
        }

        int getN() const {return n;}

        int getAdj(int u, int v) const {return Adj[u][v];}

        GrafoMatrice& AddEdge(int u, int v){
            Adj[u][v] = 1;
            Adj[v][u] = 1;
            return *this;
        }

        void printGrafo()
        {
            for(int i = 0; i < n; i++){
                cout << endl;
                for(int j = 0; j < n; j++){
                    cout << Adj[i][j] << " ";
                }
            }
            cout << endl;
        }
};

int main()
{
    int r=0, s=1, t=2, u=3, v=4, w=5,x=6,y=7;
    
    GrafoMatrice g(8);
    g.AddEdge(r, v).AddEdge(r, s).AddEdge(s, w).AddEdge(w, t).AddEdge(w, x).AddEdge(x, t).AddEdge(x, u).AddEdge(t, u).AddEdge(x, y).AddEdge(y, u);
    cout << "Grafo rappresentato con Matrice d'Adiacenza:" << endl;
    g.printGrafo();
    cout << endl;

}