//  Yuya Oguchi
//  COEN12L Lab5
//  huffman(data compression)
//  3/10/2015
//  huffman.c

#include <stdio.h>
#include <ctype.h>
#include "tree.h"
#include "pack.h"

#define p(x) ((x-1)/2)
#define l(x) ((2*x)+1)
#define r(x) ((2*x)+2)

struct tree *leaves[257];
struct tree *heap[257];
int heapcount = 0;

void swapup(int root) { // rebalance the tree when leaves are added onto the tree
    if (root > 0){
        if (getData(heap[p(root)]) > getData(heap[root])) {
            struct tree *temp = heap[p(root)];
            heap[p(root)] = heap[root];
            heap[root] = temp;
            swapup(p(root)); //recursive calls
        }
    }
}

void swapdown(int root) { // rebalance the tree when leaves are removed at the top
    int parent = root;
    int minIndex;

    if(r(parent) >= heapcount){ // if the tree exist so can still be checked
        if (l(parent)>= heapcount){
            return;
        }
        else{ // checking for child node left
            minIndex = l(parent);
        }
    } else {
        if (getData(heap[l(parent)]) <= getData(heap[r(parent)])){ // if the left child should be moving up
            minIndex = l(parent);
        }else{ // right child should be moving up
            minIndex = r(parent);
        }
    }
    if(getData(heap[parent]) > getData(heap[minIndex])) // if the lower value of the two child is smaller than current, swap with current position.
    {
        struct tree *temp = heap[minIndex];
        heap[minIndex] = heap[parent];
        heap[parent] = temp;
        swapdown(minIndex); //recursive call
    }
}

void insertHeap(struct tree *new) { //insert the new leaf onto the tree
    heap[heapcount] = new;
    swapup(heapcount);
    heapcount++;
}

struct tree *removeMin() { //remove the very top of the tree
    struct tree *tmp = heap[0];
    heap[0] = heap[heapcount -1];
    heapcount--;
    if (heapcount >0){
        swapdown(0);
    }
    return tmp;
}

void printNode(struct tree *root) { //print huffman code part of the project
    struct tree *parent = getParent(root);
    if (parent!=NULL) {
        printNode(parent);

        if (getLeft(parent) == root){//this is the path of leaves in 1 and 0
            printf("1");
        }else{
            printf("0");
        }
    }
}

int main(int argc, char *argv[]) {
    int count[257];
    int i;
    for (i = 0; i <= 257; i++) //create location for different characters
        count[i] = 0;

    FILE *file;
    file = fopen("input.txt", "r"); //read in the file

    int c;
    while(c != EOF) {
        c = fgetc(file); //get each characters from the file
        count[c] += 1;
    }

    for (i = 0; i <= 257; i++)
    {
        if (count[i] != 0) {
            leaves[i] = createTree(count[i], NULL, NULL); //create leaves
            insertHeap(leaves[i]);
        } else {
            leaves[i] = NULL;
        }
    }

    leaves[256] = createTree(0, NULL, NULL); // set one empty leaf as specified
    insertHeap(leaves[256]);

    while (heapcount>1) {
        struct tree *a = removeMin(); // combine a
        struct tree *b = removeMin(); // combine b
        struct tree *c = createTree(getData(a) + getData(b), a, b); //actually combine the a and b
        insertHeap(c);
    }

    for (i = 0; i <= 257; i++)
    {
        if (leaves[i] != NULL) {
            if (isprint(i)) {
                printf("'%c': %i ", i, count[i]); //print out the character
            } else {
                printf("%03o: %i ", i, count[i]); //use at least 3 spaces for formatting
            }
            printNode(leaves[i]);
            printf("\n");
        }
    }

    pack("input.txt", "output.z", leaves); // create pack file
    return 0;
}
