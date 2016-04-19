//  Yuya Oguchi
//  COEN12L Lab5
//  huffman(data compression)
//  3/10/2015
//  tree.c

#include <stdlib.h>
#include <assert.h>
#include "tree.h"

struct tree {
    int value; // this is the value of occurence
    struct tree *parent; // struct parent
    struct tree *leftchild; //struct left chid
    struct tree *rightchild; //struct right child
};

struct tree *createTree(int data, struct tree *left, struct tree *right) {
    struct tree *structtree = malloc(sizeof(struct tree));
    assert(structtree!=NULL); //check to make sure structtree exist
    structtree->value = data; //give value to the tree
    structtree->parent = NULL; //set parent
    setLeft(structtree, left); //set child
    setRight(structtree, right); //set child
    return structtree;
}

void destroyTree(struct tree *root) {
    if (root==NULL) return; //check to see if tree exist
    destroyTree(root->leftchild);//eliminate left child
    destroyTree(root->rightchild);//eliminate right child
    free(root);
}

int getData(struct tree *root) {
    return root->value; //return the value of the root
}

struct tree *getLeft(struct tree *root) {
    return root->leftchild;//get left child
}

struct tree *getRight(struct tree *root) {
    return root->rightchild;//get right child
}

struct tree *getParent(struct tree *root) {
    return root->parent;//get parent
}

void setLeft(struct tree *root, struct tree *left) { //set the left trees
    root->leftchild = left;
    if (left!=NULL)
        left->parent = root;
}

void setRight(struct tree *root, struct tree *right) { //set the right tree
    root->rightchild = right;
    if (right!=NULL)
        right->parent = root;
}
