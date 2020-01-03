#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void print(vector<int> &x){
    vector<int>::iterator i;
    for (i = x.begin(); i < x.end(); i++)
        cout<<*i<<" ";
    cout<<endl;
}

void mergeVectors(vector<int> &v, vector<int>::iterator mid){
    vector<int>::iterator i,j;
    vector<int> L, R;

    for (i = v.begin(); i < mid; i++){
        L.push_back(*i);
    }
    for (j = mid; j < v.end(); j++){
        R.push_back(*j);
    }

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

        mergeVectors(v, mid);
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
    print(x);
    return 0;
}
