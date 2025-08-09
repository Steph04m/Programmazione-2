//Implementazione del Merge Sort in C++
#include <iostream>
#include <climits>

using namespace std;

void Merge(int* array, int min, int mid, int max)
{    
    int n1 = mid - min + 1;
    int n2 = max - mid;
    int* leftSubArray = new int[n1 + 1];
    int* rightSubArray = new int[n2 + 1];

    for(int i = 0; i < n1; i++){
        leftSubArray[i] = array[min + i];
    }
    for(int j = 0; j < n2; j++){
        rightSubArray[j] = array[mid + j + 1];
    }  

    leftSubArray[n1] = INT_MAX;
    rightSubArray[n2] = INT_MAX;

    int i = 0;
    int j = 0;
    for(int k = min; k <= max; k++){
        if(leftSubArray[i] <= rightSubArray[j]){
            array[k] = leftSubArray[i];
            i++;
        } else {
            array[k] = rightSubArray[j];
            j++;
        }
    }

    delete[] rightSubArray;
    delete[] leftSubArray;
}

void MergeSort(int* array, int min, int max)
{
    if(min < max){
        int mid = (min + max)/2;
        MergeSort(array, min, mid);
        MergeSort(array, mid + 1, max);
        Merge(array, min, mid, max);
    } else {
        return;
    }
}

void printArray(int* array, int n)
{
    cout << "Contenuto dell'array ordinato: " << endl;
    for(int i = 0; i < n; i++){
        cout << array[i] << " ";
    }
    cout << endl;
}

int main()
{
    int array[12] = {3,6,2,1,5,9,7,4,8,12,10,11};
    MergeSort(array, 0, 11);
    printArray(array, 12);
}