//
// Created by maxim on 29/03/2024.
//

#include <string.h>
#include "btree.h"

/**
 * @brief Private function that creates a BTreeNode with its default values
 * @param tree Tree where to create the node
 * @param child New node child
 * @param value Value to be set in the node
 * @return A new BTreeNode
 */
static BTreeNode * node_create(BTree *tree,BTreeNode *child, void *value);

/**
 * @brief Private function that inserts a child BTreeNode in a given BTreeNode at a specified position
 * @param index Index where to insert the child node
 * @param node Parent node
 * @param child Child node
 * @param value Key to be inserted
 */
static void node_add(int index, BTreeNode *node, BTreeNode *child, void* value);

/**
 * @brief Private function that splits a node to maintain the balance of the tree
 * @param index Position to split
 * @param node Node to be split
 * @param child Child node of the new node
 * @param newNode New node where the value is deported
 * @param value Value to be insert somewhere else
 * @param pValue Pointer to the new value
 */
static void node_split(int index, BTreeNode *node,
                     BTreeNode *child, BTreeNode **newNode, void* value, void **pValue);


/**
 * @brief Private function that sets a given value into a given node
 * @param tree Tree where to set the value
 * @param node Node where to set a new value
 * @param child Returned child node in case of split
 * @param value Value to be inserted
 * @param pValue Pointer on the inserted value in case of split
 * @return
 */
static bool node_set_value(BTree *tree, BTreeNode *node, BTreeNode **child , void* value, void **pValue);

/**
 * @brief Private function that counts the number of nodes in the given branch
 * @param node BTree to count nodes
 * @return Node count of the given branch
 */
static int node_count(BTreeNode *node);

static BTreeNode * node_create(BTree *tree,BTreeNode *child, void *value){
    BTreeNode *newNode;
    if((newNode = (BTreeNode *)malloc(sizeof(BTreeNode))) == NULL) return NULL;
    newNode->values[1] = value;
    newNode->size = 1;
    newNode->children[0] = tree->root;
    newNode->children[1] = child;
    return newNode;
}

static void node_add(int index, BTreeNode *node, BTreeNode *child, void* value){
    int j = node->size;
    while (j > index) {
        node->values[j + 1] = node->values[j];
        node->children[j + 1] = node->values[j];
        j--;
    }
    node->values[j + 1] = value;
    node->children[j + 1] = child;
    node->size++;
}

static void node_split(int index, BTreeNode *node,
                       BTreeNode *child, BTreeNode **newNode, void* value, void **pValue){
    int median, j;

    if (index > BTREE_MIN_NODES)
        median = BTREE_MIN_NODES + 1;
    else
        median = BTREE_MIN_NODES;

    if((*newNode = (BTreeNode *)malloc(sizeof(BTreeNode))) == NULL) return;
    j = median + 1;
    while (j <= BTREE_MAX_NODES) {
        (*newNode)->values[j - median] = node->values[j];
        (*newNode)->children[j - median] = node->children[j];
        j++;
    }
    node->size = median;
    (*newNode)->size = BTREE_MAX_NODES - median;

    if (index <= BTREE_MIN_NODES) node_add(index , node, child, value);
    else node_add(index - median, *newNode, child, value);

    *pValue = node->values[node->size];
    (*newNode)->children[0] = node->children[node->size];
    node->size--;
}

static bool node_set_value(BTree  *tree, BTreeNode *node, BTreeNode **child , void* value, void **pValue){
    int pos;
    if (!node) {
        *pValue = value;
        *child = NULL;
        return 1;
    }

    if (tree->compareTo(value, node->values[1]) < 0) {
        pos = 0;
    } else {
        for (pos = node->size;
             (value < node->values[pos] && pos > 1); pos--);

        if (tree->compareTo(value, node->values[pos]) == 0) {
            // Duplicates are not permitted
            return false;
        }
    }
    if (node_set_value(tree, node->children[pos], child,value, pValue)) {
        if (node->size < BTREE_MAX_NODES) {
            node_add(pos, node, *child, *pValue);
        } else {
            node_split(pos, node, *child, child, *pValue, pValue);
            return true;
        }
    }
    return false;
}

void btree_create(BTree *tree, int (*compare)(const void* key1, const void* key2), void(*destroy) (void* value)){
    tree->compareTo = compare;
    tree->size = 0;
    tree->destroy = destroy;
    tree->root = NULL;
}

void btree_destroy(BTree *tree){
    while(tree->size != 0){
        btree_remove(tree, NULL);
    }

    memset(tree, 0 , sizeof(BTree));
}

void btree_add(BTree *tree, void* value){
    int flag;
    void * pValue;
    BTreeNode *child;

    flag = node_set_value(tree, tree->root, &child, value, &pValue );
    if (flag)
        tree->root = node_create(tree, child, pValue);
}

bool btree_remove(BTree * tree, const void * value){
    //TODO create remove
}

bool btree_containsKey(BTree tree, void** value){
    //TODO create containsKey
}

int btree_diameter(BTree *tree){
    //TODO create diameter
}

int btree_height(BTree *root, int *diameter){
    //TODO create height
}
