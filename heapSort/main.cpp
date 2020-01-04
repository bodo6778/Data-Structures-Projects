#include <iostream>

using namespace std;

void heaping(int arr[], int n, int i)
{
    int large = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if (l < n && arr[l] > arr[large])
        large = l;

    if (r < n && arr[r] > arr[large])
        large = r;

    if (large != i)
    {
        swap(arr[i], arr[large]);
        heaping(arr, n, large);
    }
}

void heapSort(int arr[], int n){
    for (int i = n / 2 - 1; i >= 0; i--)
        heaping(arr, n, i);

    for (int i = n - 1; i >= 0; i--){
        swap (arr[0], arr[i]);
        heaping(arr, i, 0);
    }
}

void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        cout<<arr[i]<<" ";
    cout<<endl;
}

int main()
{
    int n;
    cin >> n;
    int arr[n];
    for(int i = 0; i < n; i++)
        cin >> arr[i];
    heapSort(arr,n);
    printArray(arr, n);
    return 0;
}
