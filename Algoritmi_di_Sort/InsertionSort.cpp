//Implementazione del Insertion Sort in C++
#include <iostream>

using namespace std;

void InsertionSort(int* array, int n)
{
    for(int i = 1; i < n; i++){
        int key = array[i];
        int j = i - 1;
        while(j >= 0 && array[j] > key){
            array[j+1] = array[j];
            j--;
        }
        array[j+1] = key;
    }
}

void printArray(int* array, int n)
{
    for(int i = 0; i < n; i++){
        cout << array[i] << " ";
    }
    cout << endl;
}

int main()
{
    int array[12] = {3,6,2,1,5,9,7,4,8,12,10,11};
    cout << "Array prima dell'ordinamento: " << endl;
    printArray(array, 12);

    InsertionSort(array, 12);
    cout << "Array dopo l'ordinamento: " << endl;
    printArray(array, 12);
}