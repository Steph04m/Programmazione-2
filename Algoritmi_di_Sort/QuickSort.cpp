//Implementazione del Quick Sort in C++
#include <iostream>

using namespace std;

int Partition(int* array, int min, int max)
{
    int pivot = array[max];
    int i = min -1;
    for(int j = min; j < max; j++){
        if(array[j] <= pivot){
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    int temp = array[i+1];
    array[i+1] = array[max];
    array[max] = temp;
    return i+1;
}

void QuickSort(int* array, int min, int max)
{
    if(min < max){
        int mid = Partition(array, min, max);
        QuickSort(array, min, mid - 1);
        QuickSort(array, mid + 1, max);
    } else {
        return;
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

    QuickSort(array, 0, 11);
    cout << "Array dopo l'ordinamento: " << endl;
    printArray(array, 12);
}