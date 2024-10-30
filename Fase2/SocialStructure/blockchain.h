/* #ifndef BLOCKCHAIN_H
 #define BLOCKCHAIN_H
 #include <Qstring>

     int block_id = 0;

 class Block{
 public:
     int index;
     int nonce;
     Qstring timeslamp;
     Qstring previous_hash;
     Qstring root_merkle;
     Qstring hash;
     Block* next;
     ABB* ramas;
     Block(int index, int nonce_, Qstring timeslamp_);
 };

 class chainer{
    Block* head;
    Block* tail;
 };

 #endif // BLOCKCHAIN_H 
*/