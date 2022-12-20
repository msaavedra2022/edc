#include <sdsl/bit_vectors.hpp>
#include <iostream>

using namespace std;
using namespace sdsl;

//hasing perfecto

class Hashing{
    public:
    bit_vector bitmap;
    int_vector<> A;

    //rank 1
    rank_support_v<1> rank;

    Hashing(int_vector<> A){
        this->A = A;
        bitmap = bit_vector(A.size());
        for(int i = 0; i < A.size(); i++){
            bitmap[A[i]] = 1;
        }
        rank = rank_support_v<1>(&bitmap);
    }

    bool search(int x){
        return bitmap[x];
    }


    //dado un i devuelve el elemento en la posicion i
    int access(int i){
        if(bitmap[i] == 0) return -1;
        return A[rank(i)];
    }
};

int main(){

    int_vector<> A = {1, 2, 6, 7, 8, 9, 10};

    Hashing h(A);

    //pruebas de busqueda
    cout << "Busqueda por claves" << endl;
    cout << "clave 1: " << h.access(1) << endl;
    cout << "clave 2: " << h.access(2) << endl;
    cout << "clave 3: " << h.access(3) << endl;
    cout << "clave 4: " << h.access(4) << endl;
    cout << "clave 5: " << h.access(5) << endl;
    cout << "clave 6: " << h.access(6) << endl;
    cout << "clave 7: " << h.access(7) << endl;
    cout << "clave 8: " << h.access(8) << endl;
    cout << "clave 9: " << h.access(9) << endl;
    cout << "clave 10: " << h.access(10) << endl;
    cout << "clave 11: " << h.access(11) << endl;

    return 0;
}