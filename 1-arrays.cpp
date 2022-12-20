#include <sdsl/bit_vectors.hpp>
#include <iostream>

using namespace std;
using namespace sdsl;

 
int ceiling(float a){
    return (int) a + ((a - (int) a )> 0);
}

int floor2(float a){
    return (int) a;
}

class Array {
    public:
        int_vector<> W;
        int l;
        int w;
        Array(int_vector<> A, int l, int w){
            this->l = l;
            this->w = w;

            int_vector<> W(ceiling(A.size()*l/w), 0, w);
            this->W = W;

            for (int i = 0; i < A.size(); i++) {
                bitswrite((i-1)*l + 1, i*l, A[i]);
            }
            cout << "W: " << W.size() << endl;

        }

        int bitsread(int j_prima, int j){
            if(j_prima > j) return 0;

            //r = ((j-1) mod w) + 1))
            int r = ((j-1) % w) + 1;
            
            if(ceiling((float) j/w) == ceiling((float) j_prima/w)){
                //print bits
                return (int) floor2((float) W[ceiling((float) j/w)] / pow(2, w-r)) % (int) pow(2, j - j_prima + 1);
            }

            int r_prima = ((j_prima-1) % w);

            return floor2(W[ceiling((float) j/w)] / pow(2, w-r)) + (W[ceiling((float) j_prima/w)] % (int)pow(2, w-r_prima))*pow(2, r);
        }

        void bitswrite(int j_prima, int j, int x){
            if(j_prima > j) return;

            //r = ((j-1) mod w) + 1))
            int r = ((j-1) % w) + 1;


            if(ceiling((float) j/w) == ceiling((float) j_prima/w)){
                W[ceiling((float) j/w)] = W[ceiling((float) j/w)] - floor2(W[ceiling((float) j/w)] / pow(2, w-r)) % (int)pow(2, j - j_prima + 1);
                W[ceiling((float) j/w)] = W[ceiling((float) j/w)] + x*pow(2, w-r);
            }else{
                int r_prima = ((j_prima-1) % w);
                W[ceiling((float) j/w)] = W[ceiling((float) j/w)] % (int)pow(2, w-r) + (x % (int)pow(2, r))*pow(2, w-r);
                W[ceiling((float) j_prima/w)] = W[ceiling((float) j_prima/w)] - (W[ceiling((float) j_prima/w)] % (int)pow(2, w-r_prima)) + floor2(x / pow(2, r));
            }

        }

        int read(int i){
            int result = bitsread((i-1)*l + 1, i*l);
            return result;
        }

        void write(int i, int x){
            bitswrite((i-1)*l + 1, i*l, x);
        }
};

int main()
{
    int_vector<> A = { 0, 8, 7, 6, 5, 4, 0, 2, 1 };
    int l = 5;
    int w = 32;

    Array a = Array(A, l, w);


    for (int i = 0; i < A.size(); i++) {
        cout << "A[" << i << "]: " << a.read(i) << endl;
    }

    return 0;
}