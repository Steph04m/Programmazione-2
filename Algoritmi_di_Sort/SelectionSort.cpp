//Implementazione del Selection Sort in C++
#include <iostream>

using namespace std;

void SelectionSort(int* array, int n)
{
    for(int i = 0; i < n - 1; i++){
        int min = i;
        for(int j = i + 1; j < n; j++){
            if(array[j] < array[min]){
                min = j;
            }
        }
        int temp = array[i];
        array[i] = array[min];
        array[min] = temp;
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

    SelectionSort(array, 12);
    cout << "Array dopo l'ordinamento: " << endl;
    printArray(array, 12);
}