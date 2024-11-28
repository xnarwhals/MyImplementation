#include <iostream>
#include <vector>
#include <map>

class pQueue {
    private:
        int heapSize = 0; // current elements inside the heap
        bool isMaxHeap = true;
        std::vector<int> heap; // dynamic array

        // start from the first parent
        void buildMinHeap() {
            int startIndex = (heapSize/2) - 1; // we know all leafs dont violate heap properties 

            for (int i = startIndex; i >= 0; i--) {
                minHeapify(i);
            }
        }

        void buildMaxheap() {
            int startIndex = (heapSize/2) - 1; // we know all leafs dont violate heap properties 
            for (int i = startIndex; i >= 0; i--) {
                maxHeapify(i);
            }
        }

        void minHeapify(int i) {

            int l = left(i);
            int r = right(i);
            int min = i;

            
            std::cout << "L is " << left(i) << " R is " << right(i) << " i is " << i << std::endl;

            if (l < heapSize && heap[l] < heap[i]) {
                min = l;
            }

            if (r < heapSize && heap[r] < heap[min]) {
                min = r;
            }

            if (min != i) {
                std::swap(heap[i], heap[min]);
                minHeapify(min);
            }
        } 

        // key for maintaining logn operations 
        // heapify the max each time 
        void maxHeapify(int i) {

            int l = left(i); // left child
            int r = right(i); // right child
            int max = i;

            // last element in array 
            if (l < heapSize && heap[l] > heap[i]) { // is the root less than left child
                max = l;
            } 

            if (r < heapSize && heap[r] > heap[max]) { // is the right child bigger than current max
                max = r;
            }

            if (max != i) { // root is not largest start recurssion 
                std::swap(heap[i], heap[max]);
                maxHeapify(max);
            }
        }

        void swimUp(int i) {
            int p = parent(i);

            if (isMaxHeap) {
                if (i < 0 || heap[p] > heap[i] ) {
                    return;
                } else {
                    std::swap(heap[i], heap[p]);
                    swimUp(p);
                }
            } else {
                if (i < 0 || heap[p] < heap[i]) {
                    return;
                } else {
                    std::swap(heap[i], heap[p]);
                    swimUp(p);
                }
            }

        }
     

    public:
        // initialize with array build max heap in O(n) time
        pQueue(const std::vector<int> &vec) {
            heap = vec;
            heapSize = heap.size();
            buildMaxheap();
        }
        
        bool poll() {
            if (heapSize == 0) return false;

            std::swap(heap[0], heap[heapSize - 1]);
            heap.pop_back(); // actually remove the element 
            heapSize--;
            maxHeapify(0);
            return true;
        }

        void insert(int key) {
            heap.push_back(key);
            heapSize++;
            swimUp(heapSize - 1);

        }

        // returns either the min or max value
        int peek() {
            return heap[0];
        }

        int size () {
            return heapSize;
        }

        bool isEmpty() {
            if (heapSize == 0) {
                return true;
            }
            return false;
        }

        void printHeap() {
            for (int i = 0; i < heapSize; i++) {
                std::cout << heap[i] << " ";
            }
            printf("\n");
        }

        int parent(int index) {
            return (index - 1) / 2;
        }

        int left(int index) {
            return index * 2 + 1;
        }

        int right(int index) {
            return index * 2 + 2;
        }

        void convertHeap() {
            if (isMaxHeap) {
                buildMinHeap();
                isMaxHeap = false;
            } else {
                buildMaxheap();
                isMaxHeap = true;
            }
        }

        std::vector<int> heapSort() {
            std::vector<int> result; 
            
            while (!isEmpty()) {
                result.push_back(peek());
                poll();
            }

            std::reverse(result.begin(), result.end());

            return result;
        }


};


int main() {
    std::vector<int> vector = {2, 4, 6, 3, 12, 43};
    pQueue p(vector);
    // pQueue pQ(std::vector<int>({1, 2, 3, 4, 5, 6}));
    // pQueue pQ2(std::vector<int>({90,23,12,321,30,21,3,44,56,12,93}));

    // p.poll();
    // p.insert(50);
    // std::cout << p.size() << std::endl;

    std::vector<int> sorted = p.heapSort();
    for (int i = 0; i < sorted.size(); i++) {
        std::cout << sorted[i] << " ";
    }

    sorted.empty();

    printf("\n");


    // pQ2.printHeap();

    // p.printHeap();


}