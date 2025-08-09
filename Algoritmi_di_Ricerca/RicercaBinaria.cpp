#include <iostream>

using namespace std;

int RicercaBinaria(int* array, int n, int low, int high)
{
    while(low <= high){
        int mid = low + (high - low)/2;
        if(array[mid] == n){
            return mid;
        }

        if(array[mid] < n){
            low = mid + 1;
        }

        if(array[mid] > n){
            high = mid - 1;
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
    int array[] = {1,2,3,4,5,6,7,8,9,10};
    cout << "Contenuto dell'array:" << endl;
    printArray(array, 10);

    int n;
    cout << "Inserisci l'elemento da ricercare nell'array:" << endl;
    cin >> n;

    int r = RicercaBinaria(array, n, 0, 10);
    if(r != -1){
        cout << "L'elemento cercato si trova qui: array[" << r << "] = " << n << endl;
    } else {
        cout << "Elemento non trovato." << endl;
    }
}