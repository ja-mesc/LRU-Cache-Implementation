#include <unordered_map>

struct Node {
    int key;
    int value; 
    Node* next;
    Node* previous; //nodes contain two pointers plus a key-value pair.

    Node(int k, int v) ;
    };

class LRUCache {
    int capacity;
    std::unordered_map<int, Node*> cacheMap; //hash map couples nodes with key-value pairs to an iterator for O(1) operations

    Node* head;
    Node* tail; //class contains pointers to head and tail of the linked list.

    //then we need member functions to add at tail, delete at head, etc. All the juicy stuff.
    //helper functions
    void removeNode(Node* node); //remove LRU node by unlinking from list
    void addNodeToTail(Node* node); //add MRU node to tail
    void moveToTail(Node* node); //unlink from current position and make it MRU by attaching to tail.

public:

    LRUCache(int cap); //constructor for a cache of one node to be created with a fixed size (cap).
    int get(int key); //retrieve the value attached to key
    void put(int key, int value); //insert or update a key value pair.
};