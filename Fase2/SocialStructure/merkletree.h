// #ifndef MERKLETREE_H
// #define MERKLETREE_H

// class DataNode{
// public:
//     //int value; se modificara a la clase necesaria
//     DataNode *next;
//     DataNode(int value_) : value(value_), next(nullptr) {}
// };

// class HashNode{
// public:
//     //int hash; pendiente verificar clase
//     HashNode *left;
//     HashNode *right;
//     DataNode *down;
//     HashNode(int hash_), left(nullptr), right(nullptr), down(nullptr) {}
// }

// class MerkleTree
// {
// public:

//     HashNode *tophash;
//     DataNode **datablock;
//     std:: string dot
//     int max;
//     int index;
//     MerkleTree(int max_) : tophash(nullptr), max(max_), index(0) {dataBlock = new DataNode*[max]}
//     /*void add(int value); pendiente verificacion
        /*void createTree(int exp);
        void createTree(HashNode *tmp, int exp);
        void genHash(HashNode *tmp, int n);
        void preorder(HashNode *tmp);
        void auth();
        void show();
        void dotgen(HashNode *tmp);*/
//     */
// };

// #endif // MERKLETREE_H
