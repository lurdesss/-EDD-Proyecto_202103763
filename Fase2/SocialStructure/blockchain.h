/* #ifndef BLOCKCHAIN_H
 #define BLOCKCHAIN_H
 #include <Qstring>

     int block_id = 0;

 class Block{
 public:
        int index;
        int nonce;
        std::String timeslamp;
        int nodoInicio;
        int nodoFinal;
        int costo;
        std::string previous_hash = "0000";
        std::string root_merkle = "0000";
        std::string hash = "0000";
        std::shared_ptr<Block> next = nullptr;
        std::shared_ptr<ABB> ramas = nullptr;

        Block();

    void generate_block(std::shared_ptr<ABB> newRamas, int idE, int idS, int costo);
    void print_data() const;

private:
    static int block_id;
 };

 class chainer{
    std::shared_ptr<Block> head = nullptr;
    std::shared_ptr<Block> tail = nullptr;

    void add_block(std::shared_ptr<Block> new_block);
    void print_chain() const;
    void genJson() const;
 };

 #endif // BLOCKCHAIN_H 
*/