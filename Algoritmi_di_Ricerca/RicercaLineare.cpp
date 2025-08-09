#include <iostream>

using namespace std;

int RicercaLineare(int* array, int n, int r)
{
    for(int i = 0; i < n; i++){
        if(array[i] == r){
            return i;
        }
    }
    return -1;
}

void printArray(int* array, int n)
{
    for(int i = 0; i < n; i++){
        cout << array[i] << " ";
    }
    cout << endl;
}

int main(int argc, char* argv[])
{
    int array[] = {3,8,5,2,1,7,0,4,9,6};
    cout << "Contenuto dell'array:" << endl;
    printArray(array, 10);

    int n;
    cout << "Inserisci l'elemento da ricercare nell'array:" << endl;
    cin >> n;

    int r = RicercaLineare(array, 10, n);
    if(r != -1){
        cout << "L'elemento cercato si trova qui: array[" << r << "] = " << n << endl;
    } else {
        cout << "Elemento non trovato." << endl;
    }
}