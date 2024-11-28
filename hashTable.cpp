#include <iostream>
#include <list>
using namespace std;

// via seperate chaining linked lists
// memory overhead and possible linked list degradation if all keys are put into one bucket
class chainedHashTable {
    private:
        int size; 
        int numBuckets;
        list<int>* table;

        int hashFunction(int key) {
            return key % numBuckets;
        }

        void resize() {
            int oldNumBuckets = numBuckets;
            numBuckets *= 2;
            list<int>* oldTable = table;
            
            table = new list<int>[numBuckets];
            size = 0;

            for (int i = 0; i < oldNumBuckets; i++) {
                for (int key : oldTable[i]) {
                    int index = hashFunction(key);
                    table[index].push_back(key);
                    size++;
                }
            }

            delete[] oldTable;
        }

    public:
        chainedHashTable() {
            numBuckets = 1;
            table = new list<int>[numBuckets];
            size = 0;
        }

        chainedHashTable(int initSize) { // constructor
            numBuckets = initSize;
            table = new list<int>[numBuckets];
            size = 0;
        }

        ~chainedHashTable() {
            delete[] table;
        }

        void printTable() {
            for (int i = 0; i < numBuckets; i++) {
                cout << "Bucket " << i << ": ";
                for (int key : table[i]) {
                    cout << key << " ";
                }
                cout << endl;
            }
        }

        void insert(int key) {
            while ((float)size / numBuckets > 0.7) { // while because we might add more than twice the hash table keys
                resize();
            }

            int index = hashFunction(key);
            table[index].push_back(key);
            size++;
        }

        bool search(int key) {
            int index = hashFunction(key);
            for (int x : table[index]) {
                if (x == key)
                    return true;
            }

            return false;
        }

        void remove(int key) {
            int index = hashFunction(key);
            table[index].remove(key);
            size--;
        }

        int getSize() {
            return size;
        }

        int getNumBuckets() {
            return numBuckets;
        }
        
}; 

// via open adressing 
// needs load factor
class openHashTable{
    private:
        int* table; 
        int size; // current size
        int capacity; // max size
        const int EMPTY = -1;
        const int DELETED = -2;

        int hashFunction(int key) {
            return key % capacity; // ensure bounds 
        }

        void reHash() {
            int oldCapacity = capacity;
            capacity *= 2;
            int* oldTable = table;
            table = new int[capacity];

            for (int i = 0; i < capacity; i++) {
                table[i] = EMPTY;
            }

            size = 0;

            for (int i = 0; i < oldCapacity; i++) {
                if (oldTable[i] != EMPTY && oldTable[i] != DELETED) {
                    insert(oldTable[i]);
                }
            }

            delete[] oldTable;
        }

    public:
        openHashTable() {
            capacity = 1;
            size = 0;
            table = new int[capacity];
            table[0] = EMPTY;
        }

        openHashTable(int maxSize) {
            capacity = maxSize;
            size = 0;
            table = new int[capacity];
            for (int i = 0; i < capacity; i++) {
                table[i] = EMPTY;
            }
        }

        ~openHashTable() {
            delete[] table;
        }

        void printTable() {
            for (int i = 0; i < capacity; i++) {
                if (table[i] != EMPTY && table[i] != DELETED) {
                    cout << "Index " << i << ": " << table[i] << endl;
                }
            } 
        }

        void insert(int key) {
            if (size >= capacity * 0.7) { // load factor | 70% full
                reHash();
            }

            int index = hashFunction(key);
            while (table[index] != EMPTY && table[index] != DELETED) {
                index = (index + 1) % capacity; // linear probing
            }

            table[index] = key;
            size++;
        }   

        bool search(int key) {
            int index = hashFunction(key);
            int start = index;

            while (table[index] != EMPTY) {
                if (table[index] == key) {
                    return true;
                }
                index = (index + 1) % capacity; // next

                if (index == start) {
                    break; // done searching 
                }
            }
            return false;
        }

        void remove(int key) {
            int index = hashFunction(key);
            int start = index;

            while (table[index] != EMPTY) {
                if (table[index] == key) {
                    table[index] = DELETED; // this does not actually delete the element from memory 
                    size--;
                    return;
                }
                index = (index + 1) % capacity; // next
                if (index == start) {
                    break; // key no found
                }
            }

            cout << "Key Not Found\n";
        }

        int getSize() {
            return size;
        }

        int getCapacity() {
            return capacity;
        }
};


// testing 
int main() {
    chainedHashTable hashTableA(2);
    openHashTable hashTableB(2);

    hashTableA.insert(10);
    hashTableA.insert(93);
    hashTableA.insert(342);
    hashTableA.insert(23);
    hashTableA.insert(43);
    hashTableA.insert(1);


    // hashTableB.insert(20);
    // hashTableB.insert(1);
    // hashTableB.insert(9);

    // hashTableA.remove(10);
    // hashTableB.remove(20);

    hashTableA.printTable();
    // hashTableB.printTable(); 

    // cout << hashTableA.getSize() << endl;
    // cout << hashTableB.getSize() << endl;
    // cout << hashTableA.getNumBuckets() << endl;
    // cout << hashTableB.getCapacity() << endl;



}
