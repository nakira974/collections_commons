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
 * @brief Private function that searches a key in a given node
 * @param value Value to search
 * @param pos Position of the searched value
 * @param node Node to inspect
 * @param compareTo User compare handle
 * @return true if the value was found, otherwise false
 */
static bool containsKey(void** value, int *pos, BTreeNode **node, BTreeNode **pNode, int (*compareTo)(const void* key1, const void* key2));
/**
 * @brief Private function that counts the number of nodes in the given branch
 * @param node BTree to count nodes
 * @return Node count of the given branch
 */
static int node_count(BTreeNode *node);

/**
 * @brief Private function that return the index of a given value
 * @param tree Tree where to find the value index
 * @param node Node where to start the search
 * @param child Value to search
 * @return Value's index
 */
static int find_index(BTree  *tree, BTreeNode* node, BTreeNode * child);

/**
 * @brief Private recursive function to remove a value from the B tree
 * @param tree BTree structure
 * @param node Current node being processed
 * @param value Value to be removed
 * @return Node after removal
 */
static void remove_helper(BTree* tree, BTreeNode* node, void* value);

/**
 * @brief Private function that returns the height of a given branch
 * @param node Root of the branch to be inspected
 * @return Branch's height
 */
static int height(BTreeNode *node);

/**
 * @brief Private function that returns the diameter of a given branch
 * @param node Root of the branch to be inspected
 * @param diameter Diameter pointer
 * @return Diameter of the given branch
 */
static int diameter_helper(BTreeNode *node, int *diameter);

/**
 * @brief Private function that balances a given branch in a given tree
 * @param node Node to balance
 * @param parent Parent node
 * @param tree Tree to be balanced
 */
static void node_balance(BTreeNode* node, BTreeNode* parent, BTree* tree);

/**
 * @brief Private function that redistributes the keys of a given node on a left sibling
 * @param node Node from where to redistribute the keys
 * @param left_sibling Left sibling where to redistribute the keys
 * @param parent_index Index of the parent of the given node
 * @param tree Tree where to compute the left redistribution of keys
 */
static void redistribute_keys_left(BTreeNode* node, BTreeNode* left_sibling, int parent_index, BTree* tree);

/**
 * @brief Private function that redistributes the keys of a given node on a right sibling
 * @param node Node from where to redistribute the keys
 * @param right_sibling Right sibling where to redistribute the keys
 * @param parent_index Index of the parent of the given node
 * @param tree Tree where to compute the right redistribution of keys
 */
static void redistribute_keys_right(BTreeNode* node, BTreeNode* right_sibling, int parent_index, BTree* tree);

/**
 * @brief Private function that merges two nodes
 * @param node Node to be merged
 * @param sibling Node to be merged
 * @param parent Parent node
 * @param tree BTree where to merge nodes
 * @return true if the sibling was destroy, otherwise false
 */
static bool merge_nodes(BTreeNode *node_left, BTreeNode *node_right, BTreeNode **parent, int parent_key_index, BTree *tree);

/**
 * @brief Private function that finds the parent of a given node
 * @param tree BTree where to find the parent of the given node
 * @param root Root node to find the parent
 * @param child Child node of the root node
 * @return Parent node of the root node
 */
static BTreeNode* find_parent(BTree *tree, BTreeNode* root, BTreeNode* child);

/**
 * @brief Private function that finds the child of a given node
 * @param node Node to find the successor
 * @param position Position of the given node
 * @return Node's child
 */
static BTreeNode* find_successor(BTreeNode* node, int* position);

/**
 * @brief Private function that removes a value from a given node at a specified index
 * @param node Node where to remove the value
 * @param position Index of the value to remove
 * @param value Removed value
 */
static void remove_key(BTreeNode* node, int position, void** value);

/**
 * @brief Private function that reorder void** arrays
 * @param values Array to be ordered
 * @param start Start index
 */
static void reorderValues(void **values, int start);

static BTreeNode * node_create(BTree *tree,BTreeNode *child, void *value){
    BTreeNode *newNode;
    if((newNode = (BTreeNode *)malloc(sizeof(BTreeNode))) == NULL) return NULL;
    for(int i=0; i<= BTREE_MAX_NODES; i++) newNode->values[i] = NULL;
    for(int i=0; i<= BTREE_MAX_NODES; i++) newNode->children[i] = NULL;

    newNode->values[1] = value;
    newNode->size = 1;
    newNode->children[0] = tree->root;
    newNode->children[1] = child;
    newNode->isLeaf = false;
    return newNode;
}

static void node_add(int index, BTreeNode *node, BTreeNode *child, void* value) {
    int j = node->size;
    while (j > index) {
        node->values[j + 1] = node->values[j];
        node->children[j + 1] = node->children[j];
        j--;
    }
    node->values[j + 1] = value;
    node->children[j + 1] = child;
    node->size++;

    // Vérifier si le nœud est une feuille après l'ajout
    node->isLeaf = true;
    for(int i =1;i<BTREE_MAX_NODES;i++){
        if(node->children[i] != NULL){
            node->isLeaf = false;
            break;
        }
    }
}

static void node_split(int index, BTreeNode *node,
                       BTreeNode *child, BTreeNode **newNode, void* value, void **pValue){
    int median, j;

    if (index > BTREE_MIN_NODES)
        median = BTREE_MIN_NODES + 1;
    else
        median = BTREE_MIN_NODES;

    if((*newNode = (BTreeNode *)malloc(sizeof(BTreeNode))) == NULL) return;
    for(int i=0; i<= BTREE_MAX_NODES; i++) (*newNode)->values[i] = NULL;
    for(int i=0; i<= BTREE_MAX_NODES; i++) (*newNode)->children[i] = NULL;

    j = median + 1;
    while (j <= BTREE_MAX_NODES) {
        (*newNode)->values[j - median] = node->values[j];
        node->values[j] = NULL;
        (*newNode)->children[j - median] = node->children[j];
        node->children[j] = NULL;
        node->size--;
        j++;
    }

    reorderValues((void**)node->children,0);
    reorderValues(node->values, 1);

    node->size = median;
    (*newNode)->size = BTREE_MAX_NODES - median;

    if (index <= BTREE_MIN_NODES) node_add(index , node, child, value);
    else node_add(index - median, *newNode, child, value);


    *pValue = node->values[node->size];
    node->values[node->size]=NULL;
    (*newNode)->children[0] =  node->children[node->size];
    node->children[node->size] = NULL;
    node->size--;
    reorderValues((void**) node->children, 0);
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
             (tree->compareTo(value, node->values[pos]) < 0 && pos > 1); pos--);

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
            tree->size++;
            return true;
        }
    }
    return false;
}

static bool containsKey(void** value, int *pos, BTreeNode **node, BTreeNode **pNode, int (*compareTo)(const void* key1, const void* key2)) {
    if (*node == NULL) {
        return false;
    }

    bool found = false;
    int position = 1;

    while (position <= (*node)->size && compareTo(*value, (*node)->values[position]) < 0) {
        position++;
    }

    if (position <= (*node)->size && compareTo(*value, (*node)->values[position]) == 0) {
        *pos = position;
        if(pNode == NULL || *pNode == NULL){
            if((pNode=(BTreeNode**) malloc(1* sizeof (BTreeNode*))) == NULL) return false;
        }
        *pNode = *node;
        return true;
    }

    for (int i = 0; i <=  BTREE_MAX_NODES; i++) {
        if ((*node)->children[i] != NULL) {
            BTreeNode ** newNode = &(*node)->children[i];
            found = containsKey(value, pos,newNode, pNode , compareTo);
            if (found){
                break;
            }
        }
    }

    return found;
}

static int find_index(BTree  *tree, BTreeNode* node, BTreeNode * child) {
    int index = BTREE_MAX_NODES;
    while (index > 0 && child != node->children[index]) {
        index--;
    }
    return index;
}

static BTreeNode* find_parent_recursive(BTree* tree, BTreeNode* root, BTreeNode** pChild) {
    // Check if the root or child node is NULL
    if (root == NULL || *pChild == NULL) {
        return NULL;
    }

    // If the given child node is the root, it has no parent
    if (root == *pChild) {
        return root;
    }

    BTreeNode * result = NULL;

    // Check each child of the current node
    for (int i = 0; i <= BTREE_MAX_NODES; i++) {
        // If the child is found in the current node's children, return the current node
        if (root->children[i] == *pChild) {
            return root;
        }else if(root->children[i] != NULL)
            result =  find_parent_recursive(tree, root->children[i], pChild);
            if(result != NULL) break;
    }

    // If the child is not found in the current node's children, return NULL
    return result;
}

static BTreeNode* find_parent(BTree* tree, BTreeNode* root, BTreeNode* child) {
    return find_parent_recursive(tree, root, &child);
}

static void reorderValues(void **values, int start) {
    int nonNullIndex = start;
    int nullIndex = BTREE_MAX_NODES;
    for (int i = start; i <= BTREE_MAX_NODES; i++) {
        if (values[i] != NULL) {
            values[nonNullIndex++] = values[i];
        }
    }

    while (nonNullIndex <= nullIndex) {
        values[nonNullIndex++] = NULL;
    }
}

static void copySuccessor(BTreeNode *node, int pos, BTreeNode **successor) {
    BTreeNode *copy = node->children[pos];
    if(copy == NULL){
        copy=node->children[pos-1];
        if(copy == NULL) return;
    }

    while (copy->children[0] != NULL) {
        copy = copy->children[0];
    }

    // Assuming node->values[1] was the spot to clear
    node->values[pos] = copy->values[1];
    *successor = copy;
}


// Remove the value
void removeVal(BTreeNode *node, int pos) {
    int i = pos + 1;
    while (i <= node->size) {
        node->values[i - 1] = node->values[i];
        node->values[i] = NULL;
        node->children[i - 1] = node->children[i];
        node->children[i] = NULL;
        i++;
    }
    node->size--;
}

static void leftShift(BTreeNode *node, int pos) {
    int j = 1;
    BTreeNode *x = node->children[pos - 1];

    x->size++;
    x->values[x->size] = node->values[pos];
    x->children[x->size] = node->children[pos]->children[0];

    x = node->children[pos];
    node->values[pos] = x->values[1];
    x->children[0] = x->children[1];
    x->size--;

    while (j <= x->size) {
        x->values[j] = x->values[j + 1];
        x->children[j] = x->children[j + 1];
        j++;
    }
}

static void rightShift(BTree *bTree, BTreeNode *node, int pos) {
    BTreeNode *x = node->children[pos];
    int j = x->size;

    while (j > 0) {
        x->values[j + 1] = x->values[j];
        x->children[j + 1] = x->children[j];
    }
    x->values[1] = node->values[pos];
    x->children[1] = x->children[0];
    x->size++;

    x = node->children[pos - 1];
    node->values[pos] = x->values[x->size];
    node->children[pos] = x->children[x->size];
    x->size--;
}



static void mergeNodes(BTree *bTree, BTreeNode *node, int pos) {

    int j = 1;
    BTreeNode *x1 = node->children[pos], *x2 = node->children[pos - 1];

    x2->size++;
    x2->values[x2->size] = node->values[pos];
    x2->children[x2->size] = node->children[0];
    if(x2 ==  node->children[0]) x2->children[x2->size] = NULL;
    while (j < x1->size) {
        x2->size++;
        x2->values[x2->size] = x1->values[j];
        x1->values[j]=NULL;
        x2->children[x2->size] = x1->children[j];
        x1->size--;
        j++;
    }

    j = pos;
    while (j < node->size) {
        node->values[j] = node->values[j + 1];
        node->values[j + 1] = NULL;
        node->children[j] = node->children[j + 1];
        node->children[j + 1]=NULL;
        j++;
    }
    node->size--;
    if(x1->size > 0){
        j=x1->size;
        while(j<=BTREE_MAX_NODES){
            if(x1->values[j] != NULL){
                node->size++;
                node->values[node->size] = x1->values[j];
                x1->values[j] = NULL;
                node->children[node->size] = x1->children[j];
                x1->children[j] = NULL;
                x1->size--;
            }
            j++;
        }
    }
    BTreeNode *x1Parent =((BTreeNode*) find_parent(bTree, bTree->root, x1));
    if(x1Parent != NULL){
        x1Parent->children[find_index(bTree, x1Parent, x1)] = NULL;
        reorderValues((void**)x1Parent->children, 0);
    }
    bTree->destroy(x1);
    bTree->size--;
    reorderValues((void**)node->children, 0);
}

void adjustNode(BTree *tree, BTreeNode *node, int pos) {
    if (!pos) {
        if (node->children[1]->size > BTREE_MIN_NODES) {
            leftShift(node, 1);
        } else {
            mergeNodes(tree, node, 1);
        }
    } else {
        if (pos != node->size) {
            if (node->children[pos - 1] != NULL && node->children[pos - 1]->size > BTREE_MIN_NODES) {
                rightShift(tree, node, pos);
            } else {
                if (node->children[pos + 1] != NULL && pos != node->size && node->children[pos + 1]->size > BTREE_MIN_NODES) {
                    leftShift(node, pos + 1);
                } else {
                    mergeNodes(tree, node, pos);
                }
            }
        } else {
            if (node->children[pos - 1] != NULL && node->children[pos - 1]->size > BTREE_MIN_NODES) {
                rightShift(tree, node, pos);
            } else {
                mergeNodes(tree, node, pos);
            }
        }
    }
}

bool delValFromNode(BTree *tree, void **key, BTreeNode *node) {
    int pos = 0;
    bool flag = false;
    if (node != NULL) {
        if (tree->compareTo(*key,node->values[1]) > 0) {
            pos = 0;
            flag = false;
        } else {
            for (pos = node->size; (tree->compareTo(*key,node->values[pos]) < 0 && pos > 1); pos--)
                ;
            if (tree->compareTo(*key,node->values[pos]) == 0) {
                flag = true;
            } else {
                flag = false;
            }
        }
        if (flag) {
            if (node->children[pos - 1]) {
                BTreeNode *child = NULL;
                copySuccessor(node, pos, &child);
                flag = delValFromNode(tree, &node->values[pos], child);
                if (flag == false) {
                    return false;
                }
            } else {
                removeVal(node, pos);
            }
        } else {
            flag = delValFromNode(tree, key, node->children[pos]);
        }
        if (node->children[pos] != NULL) {
            if (node->children[pos]->size < BTREE_MIN_NODES)
                adjustNode(tree, node, pos);
        }
        else if (node->size == 0) {
            BTreeNode * parent = find_parent(tree, tree->root, node);
            parent->children[find_index(tree, parent, node)] = NULL;
            reorderValues((void**)parent->children, 0);
            tree->destroy(node);
            tree->size--;
            node = NULL;
        }
    }
    return flag;
}

static int height(BTreeNode *node) {
    if (node == NULL) {
        return 0;
    }
    int leftHeight = height(node->children[0]);
    int rightHeight = height(node->children[node->size]);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

static int diameter_helper(BTreeNode *node, int *diameter) {
    if (node == NULL) {
        return 0;
    }

    int leftHeight = height(node->children[0]);
    int rightHeight = height(node->children[node->size]);

    int leftDiameter = diameter_helper(node->children[0], diameter);
    int rightDiameter = diameter_helper(node->children[node->size], diameter);

    *diameter = (*diameter > leftHeight + rightHeight + 1) ? *diameter : leftHeight + rightHeight + 1;

    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

static void node_remain(void** obj, int* count){
    *count = 0;
    for(int i=0; i<= BTREE_MAX_NODES; i++) if(obj[i] != NULL) *count = *count + 1;
}


void btree_create(BTree *tree, int (*compare)(const void* key1, const void* key2), void(*destroy) (void* value)){
    tree->compareTo = compare;
    tree->size = 0;
    tree->destroy = destroy;
    tree->root = NULL;
}

void btree_destroy(BTree *tree){
    while(tree->size > 0){
        btree_remove(tree, NULL);
    }

    memset(tree, 0 , sizeof(BTree));
}

void btree_add(BTree *tree, void* value){
    bool created;
    void * pValue;
    BTreeNode *child;

    created = node_set_value(tree, tree->root, &child, value, &pValue );
    if(child != NULL){
        child->isLeaf = true;
        for(int i =1; i<= BTREE_MAX_NODES; i++){
            if(child->children[i] != NULL){
                child->isLeaf = false;
                break;
            }
        }
    }
    if (created){
        tree->root =  node_create(tree, child, pValue);
        tree->size++;
    }

}

bool btree_remove(BTree *tree, void **key) {
    if(!tree || !tree->root || !key)
        return false;

    BTreeNode *pNode = (BTreeNode*)malloc(sizeof (BTreeNode));
    if(pNode == NULL) return false;
    int pos = 0;
    if(containsKey(key, &pos, &tree->root, &pNode, tree->compareTo)){
        return delValFromNode(tree, key, pNode);
    }

    return false;
}

bool btree_containsKey(BTree *tree, int* pos, void** value){
    return containsKey(value, pos, &tree->root, NULL, tree->compareTo);
}

int btree_diameter(BTree *tree){
    if (tree == NULL || tree->root == NULL) {
        return 0;
    }

    int diameter = 0;
    diameter_helper(tree->root, &diameter);

    return diameter;
}

int btree_height(BTree *tree){
    return height(tree->root);
}

