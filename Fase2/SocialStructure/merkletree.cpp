// #include "merkletree.h"

/*
    void MerkleTree::add(int value){
        datablock[value++] = new DataNode(value);
    }

    void MerkleTree::createTree(int exp){
        tophash = new HashNode(0);
        createTree(tophash, exp )
    }

    void MerkleTree::createTree(HashNode *tmp, int exp){
        if (exp > 0){
            tmp->left = new HashNode(0);
            tmp->right = new HashNode(0);
            createTree(tmp->left, exp - 1);
            createTree(tmp->right, exp - 1);
        }
    }

    void MerkleTree::genHash(HashNode *tmp, int n){
         if (tmp != nullptr) {
            genHash(tmp->left, n);
            genHash(tmp->right, n);
            
            if (tmp->left == nullptr && tmp->right == nullptr) {
                tmp->down = datablock[n-index];
                index--;
                tmp->hash = tmp->down->value*10;
            } else {
                tmp->hash = (tmp->left->hash + tmp->right->hash)*10;
            }
        }
    }

    void MerkleTree::preorder(HashNode *tmp){
        if (tmp != nullptr) {
            cout << tmp->hash << ' ';
            preorder(tmp->left);
            preorder(tmp->right);
        }
    }

    void MerkleTree::auth(){
         int exp = 1;
        while (pow(2, exp) < (index + 1)) {
            exp += 1;
        }
        for (int i = index  ; i < pow(2, exp); i++) {
            datablock[index++] = new DataNode(i*100);
        }
        for (int i = 0; i < index; i++) {
            cout << datablock[i]->value << endl;
        }
        //index = pow(2, exp);
        createTree(exp);
        genHash(tophash, index);
        preorder(tophash);
    }

    void MerkleTree::show(){
        for (int i = 0; i < (index + 1); i++) {
            cout << datablock[i]->value << ' ';
        }
    }

    void MerkleTree::dotgen(){
        if (tmp != nullptr) {
            dot += to_string(tmp->hash) + " [label=\"" + to_string(tmp->hash) + "\"];";
            if (tmp->left != nullptr) {
                dot += to_string(tmp->hash) + "--" + to_string(tmp->left->hash) + ";";           
            }
            if (tmp->right != nullptr) {
                dot += to_string(tmp->hash) + "--" + to_string(tmp->right->hash) + ";";           
            }
            dotgen(tmp->left);
            dotgen(tmp->right);
            if (tmp->left == nullptr && tmp->right == nullptr && tmp->down != nullptr) {
                dot += to_string(tmp->down->value) + " [label=\"" + to_string(tmp->down->value) + "\" shape=rect];";
                dot += to_string(tmp->hash) + "--" + to_string(tmp->down->value) + ";";
            }
        }

    }
    

*/

// MerkleTree::MerkleTree() {}
