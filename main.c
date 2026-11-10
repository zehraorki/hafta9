#include <stdio.h>
#include <stdlib.h>

typedef struct AvlNode {
    int data,high;
    struct AvlNode *left, *right;
}AvlNode;

int max(int a,int b ) {
    return (a>b) ?a :b;
}
int h(AvlNode*d) {
    return (d==NULL)? -1: d->high;
}
int getBalanced(AvlNode* d) {
    return (d==NULL) ? 0: h(d->left)-h(d->right);
}
AvlNode* rightRotate(AvlNode *d) {
    AvlNode* x=d->left;
    AvlNode* T2=x->right;
    x->right=d;
    d->left=T2;
    d->high=1+max(h(d->left),h(d->right));
    x->high=1+max(h(x->left),h(x->right));
    return x;
}
AvlNode* leftRotate(AvlNode *d) {
    AvlNode* y=d->right;
    AvlNode* T2=y->left;
    y->left=d;
    d->right=T2;
    d->high=1+max(h(d->left),h(d->right));
    y->high=1+max(h(y->left),h(y->right));
    return y;
}
AvlNode* AvlAdd(AvlNode* node, int key) {
    if (node==NULL) {
        AvlNode *n=(AvlNode*)malloc(sizeof(AvlNode));
        n->data=key; n->high=0; n->left=n->right=NULL;
        return n;
    }
    if (key < node->data) node->left=AvlAdd(node->left,key);
    if (key > node->data) node->right=AvlAdd(node->right,key);
    else return node;
    node->high=1+max(h(node->left),h(node->right));
    int balance=getBalanced(node);
    if (balance>1 && key < node->left->data) return rightRotate(node);
    if (balance<-1 && key >node->right->data) return leftRotate(node);
    if (balance>1 && key>node->left->data) {
        node->left=leftRotate(node->left); return rightRotate(node);
    }
    if (balance<-1 && key<node->right->data) {
        node->right=rightRotate(node->right); return leftRotate(node);
    }
    return node;

}

void printInOrder(AvlNode* root) {
    if (root != NULL) {
        printInOrder(root->left);
        printf("Data: %d\n",root->data);
        printInOrder(root->right);
    }
}
void printPreOrder(AvlNode* root) {
    if (root != NULL) {
        printf("Data: %d\n",root->data);
        printPreOrder(root->left);
        printPreOrder(root->right);
    }
}
void printPostOrder(AvlNode* root) {
    if (root != NULL) {
        printPostOrder(root->left);
        printPostOrder(root->right);
        printf("Data: %d\n",root->data);
    }
}

int main(void) {
    AvlNode* root=NULL;
    for(int i=0;i<10;i++) {
        root=AvlAdd(root,rand()%100);
    }
    printInOrder(root);
    printf("\n*************\n");
    printPreOrder(root);
    printf("\n*************\n");
    printPostOrder(root);
    printf("\n*************\n");
    return 0;
}
