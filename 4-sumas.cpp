#include <sdsl/bit_vectors.hpp>
#include <iostream>

using namespace std;
using namespace sdsl;

class SumasParciales{

    bit_vector bitmap;
    rank_support_v<0> rank0;
    rank_support_v<1> rank1;
    select_support_mcl<0> select0;
    select_support_mcl<1> select1;

    public:
    SumasParciales(int_vector<0> A){
        int j = 0;

        bitmap = bit_vector(get_bits(A));
        for(int i = 0; i < A.size(); i++){
            for(int k = 0; k < A[i]; k++){
                bitmap[j++] = 1;
            }
            bitmap[j++] = 0;
        }
        rank1 = rank_support_v<1>(&bitmap);
        rank0 = rank_support_v<0>(&bitmap);
        select0 = select_support_mcl<0>(&bitmap);
        select1 = select_support_mcl<1>(&bitmap);
    }

    int get_bits(int_vector<> A){
        int j = 0;
        for(int i = 0; i < A.size(); i++){
            j += A[i];
        };
        return j + A.size();
    }

    int sum(int i){
        return 1 + rank1(select0(i));
    }
    int search(int suma){
        return rank0(select1(suma));
    }

};

int main(){

    int_vector<> A = {1, 2, 6, 7, 8, 9, 10};

    SumasParciales sp(A);

    cout << "Busqueda por sumas" << endl;

    //pruebas
    cout << "Suma de los primeros 3 elementos: " << sp.sum(3) << endl;
    cout << "Suma de los primeros 4 elementos: " << sp.sum(4) << endl;
    cout << "Suma de los primeros 5 elementos: " << sp.sum(5) << endl;
    cout << "Suma de los primeros 6 elementos: " << sp.sum(6) << endl << endl;

    cout << "Busqueda por search" << endl;

    //pruebas 10 17 25 34
    cout << "Busqueda de suma 10, deberia ser 3: " << sp.search(sp.sum(3)) << endl;
    cout << "Busqueda de suma 17, deberia ser 4: " << sp.search(sp.sum(4)) << endl;
    cout << "Busqueda de suma 25, deberia ser 5: " << sp.search(sp.sum(5)) << endl;
    cout << "Busqueda de suma 34, deberia ser 6: " << sp.search(sp.sum(6)) << endl;

    return 0;
}