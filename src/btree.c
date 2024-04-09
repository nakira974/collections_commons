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

/**
 * @brief Private function that get the non null elements count of an object
 * @param obj Object to be inspected
 * @param count Result pointer
 */
static void node_remain(void** obj, int* count);

/**
 * @brief Private function that redistribute the children of an empty node to its pChild before being destroyed
 * @param pParent Parent to be destroyed
 * @param pChild Child node from where redistribute the children of the pParent
 * @param tree Tree where to redistribute the children
 * @param childPtr Base pChild pointer
 */
static void redistribute_children(BTreeNode** pParent, BTreeNode* pChild, BTree * tree, BTreeNode** childPtr);

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
    node->size--;
    (*newNode)->children[0] =  node->children[node->size];
    node->children[node->size] = NULL;
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

// Trouve le frère gauche d'un nœud
static BTreeNode* find_left_sibling(BTreeNode* node, BTree* tree) {
    BTreeNode* parent = find_parent(tree, tree->root, node); // utilise votre fonction find_parent
    int index;
    for (index = 0; index <= BTREE_MAX_NODES; ++index) {
        if (parent->children[index] == node) {
            break;
        }
    }
    // si le nœud est le premier enfant, il n'a pas de frère gauche
    if (index == 0) {
        return NULL;
    } else {
        return parent->children[index - 1];
    }
}

// Trouve le frère droit d'un nœud
static BTreeNode* find_right_sibling(BTreeNode* node, BTree* tree) {
    BTreeNode* parent = find_parent(tree, tree->root, node); // utilise votre fonction find_parent
    int index;
    for (index = 0; index <= parent->size; ++index) {
        if (parent->children[index] == node) {
            break;
        }
    }
    // si le nœud est le dernier enfant, il n'a pas de frère droit
    if (index == parent->size) {
        return NULL;
    } else {
        return parent->children[index + 1];
    }
}





static BTreeNode* find_successor(BTreeNode* node, int* position) {
    BTreeNode* current = node->children[*position];

    if(current == NULL) return NULL;
    // Trouver le nœud le plus à gauche à partir du nœud actuel
    while (!current->isLeaf) {
        current = current->children[*position];
        *position = *position+1;
    }

    return current;
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

static bool copySuccessor(BTreeNode *node, int pos) {
    BTreeNode *copy = node->children[pos];

    while (copy->children[1] != NULL) {
        copy = copy->children[1];
    }

    // Assuming node->values[1] was the spot to clear
    node->values[pos] = copy->values[1];
    return true;
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

static bool leftShift(BTreeNode *node, int pos) {
    if(pos < 1 || pos > node->size)
        return false;

    for(int i = pos; i < node->size; i++) {
        node->values[i] = node->values[i+1];
        node->values[i+1] = NULL;
        node->children[i] = node->children[i+1];
        node->children[i+1] = NULL;
    }
    node->values[node->size] = NULL;
    node->children[node->size] = NULL;
    node->size--;

    return true;
}

static bool rightShift(BTree *bTree, BTreeNode *node, int pos) {
    // Cannot adjust first element of array, or an empty node
    if(pos < 2 || pos > node->size) {
        return false;
    }

    BTreeNode *x = node->children[pos];

    // Ensure shifting within bounds
    if(x->size == BTREE_MAX_NODES)
        return false;

    // Do right shift
    for(int j = x->size; j > 0; j--) {
        x->values[j+2] = x->values[j+1];
        x->values[j+1] = NULL;
        x->children[j+2] = x->children[j+1];
        x->children[j+1] = NULL;
    }

    x->children[2] = x->children[1];
    x->values[2] = node->values[pos];
    x->size++;

    BTreeNode *y = node->children[pos-1];
    node->children[pos] = y->children[y->size];
    node->values[pos] = y->values[y->size+1];
    y->values[y->size+1] = NULL;
    y->children[y->size+1] = NULL;
    y->size--;

    return true;
}



static bool mergeNodes(BTree *bTree, BTreeNode *node, int pos) {
    if(pos < 2 || pos > node->size)
        return false;

    BTreeNode *child1 = node->children[pos];
    BTreeNode *child2 = node->children[pos-1];

    if(child2->size + child1->size >= BTREE_MAX_NODES + 1)
        return false;

    child2->values[child2->size+2] = node->values[pos];

    for(int i = 1; i <= child1->size; i++) {
        child2->values[child2->size + i + 2] = child1->values[i];
        child1->values[i] = NULL;
        child2->children[child2->size + i + 2] = child1->children[i];
        child1->children[i] = NULL;
    }

    child2->children[child2->size + child1->size + 2] = child1->children[child1->size + 1];
    child2->size = child2->size + child1->size + 1;

    // shift left node values and children to fill deleted spot
    leftShift(node, pos);

    bTree->destroy(child1);
    bTree->size--;

    return true;
}

void adjustNode(BTree *tree, BTreeNode *node, int pos) {
    if (pos == 1) {
        if (node->children[2]->size > BTREE_MIN_NODES) {
            leftShift(node, 2);
        } else {
            mergeNodes(tree, node, 2);
        }
    } else {
        if (pos != node->size) {
            if (node->children[pos - 1]->size > BTREE_MIN_NODES) {
                rightShift(tree, node, pos);
            } else {
                if (pos != node->size && node->children[pos + 1]->size > BTREE_MIN_NODES) {
                    leftShift(node, pos + 1);
                } else {
                    mergeNodes(tree, node, pos);
                }
            }
        } else {
            if (node->children[pos - 1]->size > BTREE_MIN_NODES) {
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
                copySuccessor(node, pos);
                flag = delValFromNode(tree, &node->values[pos], node->children[pos]);
                if (flag == false) {
                    return false;
                }
            } else {
                removeVal(node, pos);
            }
        } else {
            flag = delValFromNode(tree, key, node->children[pos]);
        }
        if (node->children[pos]) {
            if (node->children[pos]->size < BTREE_MIN_NODES)
                adjustNode(tree, node, pos);
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
    containsKey(key, &pos, &tree->root, &pNode, tree->compareTo);
    bool result = delValFromNode(tree, key, pNode);
    if(result && tree->root->size == 0 && !tree->root->isLeaf) {
        BTreeNode *old_root = tree->root;
        tree->root = tree->root->children[1];
        tree->destroy(old_root);
        tree->size--;
    }

    return result;
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

