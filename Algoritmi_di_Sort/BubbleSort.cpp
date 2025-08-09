//Implementazione del Bubble Sort in C++
#include <iostream>

using namespace std;

void BubbleSort(int* array, int n)
{
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n-1; j++){
            if(array[j] > array[j+1]){
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
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

    BubbleSort(array, 12);
    cout << "Array dopo l'ordinamento: " << endl;
    printArray(array, 12);
}