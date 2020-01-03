#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void mergeVectors(vector<int> &v, vector<int>::iterator left, vector<int>::iterator mid, vector<int>::iterator right){
    vector<int>::iterator i,j;

    vector<int> L, R;

    for (i = left; i < mid; i++)
        L.push_back(*i);
    for (j = mid; j < right; j++)
        R.push_back(*j);

    i = L.begin();
    j = R.begin();

    v.clear();

    while (i < L.end() && j < R.end()){
        if (*i < *j){
            v.push_back(*i);
            i++;
        }
        else {
            v.push_back(*j);
            j++;
        }
    }

    while (i < L.end()){
        v.push_back(*i);
        i++;
    }

    while (j < R.end()){
        v.push_back(*j);
        j++;
    }


}

void mergeSort(vector<int> &v, vector<int>::iterator left, vector<int>::iterator right){
    if (left < right){
        vector<int>::iterator mid = left + (right - left)/2;

        mergeSort(v, left, mid);
        mergeSort(v, mid+1, right);

        mergeVectors(v, left, mid, right);
    }
}

int main()
{
    vector<int> x;
    vector<int>::iterator ptr;
    int n, i, aux;
    cin >> n;
    for (i = 1; i <= n; i++){
        cin >> aux;
        x.push_back(aux);
    }
    mergeSort(x, x.begin(), x.end());
    for (ptr = x.begin(); ptr < x.end(); ptr++)
        cout << *ptr << " ";
    return 0;
}
