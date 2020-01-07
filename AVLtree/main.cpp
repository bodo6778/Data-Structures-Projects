#include <iostream>
#include <algorithm>
using namespace std;

struct nod{
        int info;
        nod *st, *dr;
    };

nod *newNod(int x){
    nod *tmp = new nod;
    tmp->info = x;
    tmp->st = tmp->dr = NULL;
    return tmp;
}

int cautare(nod *rad, int x){
    if (rad == NULL)
        return 0;
    if (rad->info == x)
        return 1;
    if (rad->info < x)
        return cautare(rad->dr, x);

    return cautare(rad->st, x);
}

int maxim(nod *rad){
    if(rad == NULL)
        return 0;
    if(rad->dr == NULL)
        return rad->info;
    return maxim(rad->dr);
}

int inaltime(nod *rad){
    if (rad == NULL){
        return 0;
    }
    else{
        int inaltime_stanga = inaltime(rad->st);
        int inaltime_dreapta = inaltime(rad->dr);
        if (inaltime_stanga > inaltime_dreapta)
            return (inaltime_stanga + 1);
        else return (inaltime_dreapta + 1);
    }
}

int diferenta(nod *rad){

        int inaltime_stanga = inaltime(rad->st);
        int inaltime_dreapta = inaltime(rad->dr);
        int dif = inaltime_stanga - inaltime_dreapta;
        return dif;

}

nod* rotire_dd(nod *rad){
    nod *tmp;
    tmp = rad->dr;
    rad->dr = tmp->st;
    tmp->st = rad;
    cout<<"Right-Right Rotation" << endl;
    return tmp;
}


nod* rotire_ss(nod *rad){
    nod *tmp;
    tmp = rad -> st;
    rad->st = tmp->dr;
    tmp->dr = rad;
    cout<<"Left-Left Rotation" << endl;
    return tmp;
}

nod* rotire_sd(nod *rad){
    nod *tmp;
    tmp = rad->st;
    rad->st = rotire_dd(tmp);
    cout<<"Left-Right Rotation" << endl;
    return rotire_ss(rad);
}

nod* rotire_ds(nod *rad){
    nod *tmp;
    tmp = rad->dr;
    rad->dr = rotire_ss(tmp);
    cout<<"Right-Left Rotation" << endl;
    return rotire_dd(rad);
}

nod *echilibrare(nod *rad){
    int factor = diferenta(rad);
    if(factor > 1){
        if (diferenta(rad->st)>0)
            rad = rotire_ss(rad);
        else
            rad = rotire_sd(rad);
    } else if (diferenta(rad) < -1){
        if (diferenta(rad->dr) > 0)
            rad = rotire_ds(rad);
        else
            rad = rotire_dd(rad);
    }
    return rad;
}


nod* insert(nod *n, int x){
    if (n == NULL)
        return newNod(x);

    if (x < n->info){
        n->st = insert(n->st, x);
        n = echilibrare(n);
    }
    else if (x > n->info){
        n->dr = insert(n->dr, x);
        n = echilibrare(n);
    }
    return n;
}

nod* insert_avl(nod *rad, int x){
    if(rad == NULL){
        rad = new nod;
        rad->info = x;
        rad->st = NULL;
        rad->dr = NULL;
        return rad;
    } else if (x < rad->info){
        rad->st = insert(rad->st, x);
        rad = echilibrare(rad);
    } else if (x >= rad->info){
        rad->dr = insert(rad->dr, x);
        rad = echilibrare(rad);
    }
    return rad;
}



nod* minValueNode(nod* n)
{
    nod* current = new nod;
    current = n;

    /* loop down to find the stmost leaf */
    while (current && current->st != NULL)
        current = current->st;

    return current;
}

nod* sterge(nod *rad, int x){
    if (rad == NULL) return rad;

    if (x < rad->info)
        rad->st = sterge(rad->st, x);
    else if (x > rad->info)
        rad->dr = sterge(rad->dr, x);
    else{
        if (rad->st == NULL){
            nod *tmp = new nod;
            tmp = rad->dr;
            delete rad;
            return tmp;
        } else if (rad->dr == NULL){
            nod *tmp = new nod;
            tmp = rad->st;
            delete rad;
            return tmp;
        }

        nod *tmp = new nod;
        tmp = minValueNode(rad->dr);

        rad->info  = tmp->info;
        rad->dr = sterge(rad->dr, tmp->info);
    }

    return rad;
}

void rsd(nod *rad){
    if (rad != NULL){
        cout<<rad->info << " ";
        rsd(rad->st);
        rsd(rad->dr);
    }
}

//inordine
void srd(nod *rad){
    if (rad != NULL){
        srd(rad->st);
        cout<<rad->info << " ";
        srd(rad->dr);
    }
}

void sdr(nod *rad){
    if (rad != NULL){
        sdr(rad->st);
        sdr(rad->dr);
        cout<<rad->info << " ";
    }
}

void store(nod *rad, int arr[], int &i){
    if (rad != NULL){
        store(rad->st, arr, i);
        arr[i++] = rad->info;
        store(rad->dr, arr, i);
    }
}

void treeSort(int arr[], int n){
    nod *rad = NULL;
    rad = insert(rad, arr[0]);
    for(int i = 1; i < n; i++)
        rad = insert(rad, arr[i]);
    int i = 0;
    store(rad, arr, i);
}

int main(){
    nod *rad = NULL;
    int playing = 1, caz;
    while (playing){
        cout<<"------\n1 - Inserare nod AVL\n2 - Cauta nod\n3 - Cauta maxim\n4 - RSD\n5 - SRD\n6 - SDR\n7 - Sterge nod\n8 - Sortare vector\n0 - Stop\n-------\n";
        cin>>caz;
        switch (caz)
        {
        case 1:
            int x;
            cout<<"Adauga valoarea: "; cin >> x;

            if (rad == NULL)
                rad = insert(rad, x);
            else
                rad = insert(rad, x);

            cout<<endl;
            break;

        case 2:
            cout<<"Cauta valoarea: "; cin >> x;

            cout << cautare(rad, x) << endl;
            break;

        case 3:
            cout << "Maximul este " << maxim(rad) << endl;
            break;

        case 4:
            cout << "RSD: ";
            rsd(rad);
            cout << endl;
            break;

        case 5:
            cout << "SRD: ";
            srd(rad);
            cout << endl;
            break;

        case 6:
            cout << "SDR: ";
            sdr(rad);
            cout << endl;
            break;

        case 7:
            cout<<"Sterge valoarea: "; cin >> x;

            sterge(rad, x);
            cout << endl;
            break;

        case 8:
            int i,n;
            cout << "Numar elemente: "; cin >> n;
            int arr[100];
            cout << "Citeste elementele: ";
            for (i = 0; i < n; i++){
                cin >> arr[i];
            }
            treeSort(arr,n);
            cout << "Vector sortat: ";
            for (i = 0; i < n; i++){
                cout << arr[i] << " ";
            }
            cout << endl;
            break;

        case 0:
            playing = 0;
            break;

        default:
            break;
        }
    }
    return 0;
}
