#include <iostream>
#include <string>
#include <sdsl/suffix_trees.hpp>

using namespace std;
using namespace sdsl;

struct oNode {
    string data;
    int nChildren;
    struct oNode *fChild;
    struct oNode *nextSib;
    struct oNode *prevSib;
    struct oNode *parent;
};


oNode* getTree(){

    oNode* node1 = new oNode;
    oNode* node2 = new oNode;
    oNode* node3 = new oNode;
    oNode* node4 = new oNode;
    oNode* node5 = new oNode;
    oNode* node6 = new oNode;
    oNode* node7 = new oNode;
    oNode* node8 = new oNode;
    oNode* node9 = new oNode;
    oNode* node10 = new oNode;
    oNode* node11 = new oNode;
    oNode* node12 = new oNode;
    oNode* node13 = new oNode;
    oNode* node14 = new oNode;
    oNode* node15 = new oNode;
    oNode* node16 = new oNode;
    oNode* node17 = new oNode;
    oNode* node18 = new oNode;
    oNode* node19 = new oNode;
    oNode* node20 = new oNode;

    node1->data = "1";
    node1->nChildren = 3;
    node1->fChild = node2;
    node1->nextSib = NULL;
    node1->prevSib = NULL;
    node1->parent = NULL;

    node2->data = "2";
    node2->nChildren = 2;
    node2->fChild = node5;
    node2->nextSib = node3;
    node2->prevSib = NULL;
    node2->parent = node1;

    node3->data = "3";
    node3->nChildren = 2;
    node3->fChild = node7;
    node3->nextSib = node4;
    node3->prevSib = node2;
    node3->parent = node1;

    node4->data = "4";
    node4->nChildren = 0;
    node4->fChild = NULL;
    node4->nextSib = NULL;
    node4->prevSib = node3;
    node4->parent = node1;

    node5->data = "5";
    node5->nChildren = 0;
    node5->fChild = NULL;
    node5->nextSib = node6;
    node5->prevSib = NULL;
    node5->parent = node2;

    node6->data = "6";
    node6->nChildren = 0;
    node6->fChild = NULL;
    node6->nextSib = NULL;
    node6->prevSib = node5;
    node6->parent = node2;

    node7->data = "7";
    node7->nChildren = 2;
    node7->fChild = node9;
    node7->nextSib = node8;
    node7->prevSib = NULL;
    node7->parent = node3;

    node8->data = "8";
    node8->nChildren = 1;
    node8->fChild = node11;
    node8->nextSib = NULL;
    node8->prevSib = node7;
    node8->parent = node3;

    node9->data = "9";
    node9->nChildren = 1;
    node9->fChild = node12;
    node9->nextSib = node10;
    node9->prevSib = NULL;
    node9->parent = node7;

    node10->data = "10";
    node10->nChildren = 0;
    node10->fChild = NULL;
    node10->nextSib = NULL;
    node10->prevSib = node9;
    node10->parent = node7;

    node11->data = "11";
    node11->nChildren = 4;
    node11->fChild = node13;
    node11->nextSib = NULL;
    node11->prevSib = NULL;
    node11->parent = node8;

    node12->data = "12";
    node12->nChildren = 3;
    node12->fChild = node17;
    node12->nextSib = NULL;
    node12->prevSib = NULL;
    node12->parent = node9;

    node13->data = "13";
    node13->nChildren = 0;
    node13->fChild = NULL;
    node13->nextSib = node14;
    node13->prevSib = NULL;
    node13->parent = node11;

    node14->data = "14";
    node14->nChildren = 1;
    node14->fChild = node20;
    node14->nextSib = node15;
    node14->prevSib = node13;
    node14->parent = node11;

    node15->data = "15";
    node15->nChildren = 0;
    node15->fChild = NULL;
    node15->nextSib = node16;
    node15->prevSib = node14;
    node15->parent = node11;

    node16->data = "16";
    node16->nChildren = 0;
    node16->fChild = NULL;
    node16->nextSib = NULL;
    node16->prevSib = node15;
    node16->parent = node11;

    node17->data = "17";
    node17->nChildren = 0;
    node17->fChild = NULL;
    node17->nextSib = node18;
    node17->prevSib = NULL;
    node17->parent = node12;

    node18->data = "18";
    node18->nChildren = 0;
    node18->fChild = NULL;
    node18->nextSib = node19;
    node18->prevSib = node17;
    node18->parent = node12;

    node19->data = "19";
    node19->nChildren = 0;
    node19->fChild = NULL;
    node19->nextSib = NULL;
    node19->prevSib = node18;
    node19->parent = node12;

    node20->data = "20";
    node20->nChildren = 0;
    node20->fChild = NULL;
    node20->nextSib = NULL;
    node20->prevSib = NULL;
    node20->parent = node14;

    return node1;
}

//funcion para imprimir arbol por profundidad
void printTreeDepth(oNode *root, int depth){
    if(root == NULL){
        return;
    }

    for(int i = 0; i < depth; i++){
        cout << " ";
    }

    cout << root->data << endl;

    printTreeDepth(root->fChild, depth + 1);
    printTreeDepth(root->nextSib, depth);
}

//funcion para imprimir arbol por anchura
void printTreeBreadth(oNode *root){
    if(root == NULL){
        return;
    }

    vector<oNode*> queue;
    queue.push_back(root);

    while (queue.size() > 0){
        oNode *node = queue[0];
        queue.erase(queue.begin());

        while (node != NULL){
            cout << node->data << " ";

            if(node->fChild != NULL){
                queue.push_back(node->fChild);
            }
            node = node->nextSib;
        }
    }

    cout << endl;
    
}

//funcion para contruir bit_vector y data de arbol
pair<bit_vector, vector<string>> buildBitAndDataVector(oNode *root){
    if(root == NULL){
        return make_pair(bit_vector(), vector<string>());
    }
    //vector para almacenar los datos
    vector<string> data;
    //vector para representar arbol
    vector<bool> bitVector;
    // add 10 iniciales
    bitVector.push_back(1);
    bitVector.push_back(0);

    vector<oNode*> queue;
    queue.push_back(root);

    while (queue.size() > 0){
        oNode *node = queue[0];
        queue.erase(queue.begin());

        while (node != NULL){
            //guardando data
            data.push_back(node->data);

            //añadiendo 1s por cada hijo
            for(int i = 0; i < node->nChildren; i++){
                bitVector.push_back(1);
            }
            bitVector.push_back(0);

            if(node->fChild != NULL){
                queue.push_back(node->fChild);
            }
            node = node->nextSib;
        }
    }
    
    cout << "bitVector: ";
    for(int i = 0; i < bitVector.size(); i++){
        cout << bitVector[i];
    }
    cout << endl;

    //convertir a bit_vector
    bit_vector bv(bitVector.size());
    for(int i = 0; i < bitVector.size(); i++){
        bv[i] = bitVector[i];
    }

    return pair<bit_vector, vector<string>>(bv, data);
}

//funcion para obtener indice en el array dado un string
int getIndex(vector<string> data, string s){
    for(int i = 0; i < data.size(); i++){
        if(data[i] == s){
            return i;
        }
    }
    return -1;
}



bool esJefe2(string nodo, bit_vector l, vector<string> data, string jefe){
    
    //creo que rank y select recibe el indice del array desde 1 pero retorna posicion desde 0
    rank_support_v<0> rank0 = rank_support_v<0>(&l);
    rank_support_v<1> rank1 = rank_support_v<1>(&l);
    select_support_mcl<0> select0 = select_support_mcl<0>(&l);
    select_support_mcl<1> select1 = select_support_mcl<1>(&l);
    //posicion en array (comenzando en 1)
    int indexHijo = getIndex(data, nodo) + 1;

    if(indexHijo == 1){
        return false;
    }
    
    int indexBitHijo = select0(indexHijo)+1;
    
    int j = select1(rank0(indexBitHijo));
    int parent = select0(rank0(j)) + 1;

    //obtener index en el array data
    int indexParent = rank0(parent);


    if (data[indexParent-1] != jefe){
        esJefe2(data[indexParent-1], l, data, jefe);
    }

    return true;
}

//funcion esJefe iterativa
bool esJefe(string nodo, bit_vector l, vector<string> data, string jefe){
    //creo que rank y select recibe el indice del array desde 1 pero retorna posicion desde 0
    rank_support_v<0> rank0 = rank_support_v<0>(&l);
    rank_support_v<1> rank1 = rank_support_v<1>(&l);
    select_support_mcl<0> select0 = select_support_mcl<0>(&l);
    select_support_mcl<1> select1 = select_support_mcl<1>(&l);
    //posicion en array (comenzando en 1)
    int indexHijo = getIndex(data, nodo) + 1;

    if(indexHijo == 1){
        return false;
    }
    
    int indexBitHijo = select0(indexHijo)+1;
    
    int j = select1(rank0(indexBitHijo));
    int parent = select0(rank0(j)) + 1;

    //obtener index en el array data
    int indexParent = rank0(parent);

    while (data[indexParent-1] != jefe){
        indexHijo = indexParent;
        indexBitHijo = select0(indexHijo)+1;
        j = select1(rank0(indexBitHijo));
        parent = select0(rank0(j)) + 1;
        indexParent = rank0(parent);
    }

    return true;
}



class loudsTree{
    private:
        bit_vector l;
        vector<string> data;

        rank_support_v<0> rank0;
        rank_support_v<1> rank1;
        select_support_mcl<0> select0;
        select_support_mcl<1> select1;

    public:
        loudsTree(bit_vector b, vector<string> data){
            this->l = b;
            this->data = data;
            this->rank0 = rank_support_v<0>(&l);
            this->rank1 = rank_support_v<1>(&l);
            this->select0 = select_support_mcl<0>(&l);
            this->select1 = select_support_mcl<1>(&l);
        }

        bool esJefe(string nodo, string jefe){
            return ::esJefe(nodo, this->l, this->data, jefe);
        }

        //metodo getSubordinados iterativo con pila
        vector<string> getSub2(string nodo){
            vector<string> subordinados;
            stack<string> pila;
            pila.push(nodo);

            while(!pila.empty()){
                string nodo = pila.top();
                pila.pop();

                //obtener index en el array data
                int indexNodo = getIndex(this->data, nodo) + 1;

                int v = select0(indexNodo)+1;
                //si no tiene hijos
                if(l[v] == 0){
                    continue;
                }

                //sucesor de 0 
                int succs0 = select0(rank0(v)+1);

                int children = succs0 - v;

                for(int i = 1; i <= children; i++){
                    int child = select0(rank1(v - 1 + i)) + 1;
                    int indexChild = rank0(child);

                    subordinados.push_back(this->data[indexChild]);
                    pila.push(this->data[indexChild]);
                }
            }
            
            return subordinados;
        }
};




int main(){
    //estructura de nodos sin comprimir
    oNode *root = getTree();


    pair<bit_vector, vector<string>> data = buildBitAndDataVector(root);

    loudsTree tree(data.first, data.second);

    bool result = tree.esJefe("19", "1");


    if(result){
        cout << "1 es jefe de 19" << endl;
    }else{
        cout << "1 no es jefe de 19" << endl;
    }

    cout << endl << endl;

    //obtener subordinados de 1
    vector<string> subordinados = tree.getSub2("3");


    cout << "Subordinados de 3: " << endl;
    for(int i = 0; i < subordinados.size(); i++){
        cout << subordinados[i] << " ";
    }

    cout << endl;

    return 0;
}

