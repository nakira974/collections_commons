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
static bool containsKey(void** value, int *pos, BTreeNode *node, int (*compareTo)(const void* key1, const void*key2));

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
 * @param value Value to search
 * @return Value's index
 */
static int find_index(BTree  *tree, BTreeNode* node, void* value);

/**
 * @brief Private recursive function to remove a value from the B tree
 * @param tree BTree structure
 * @param node Current node being processed
 * @param value Value to be removed
 * @return Node after removal
 */
static BTreeNode* remove_helper(BTree* tree, BTreeNode* node, void* value);

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
int diameter_helper(BTreeNode *node, int *diameter);

static BTreeNode * node_create(BTree *tree,BTreeNode *child, void *value){
    BTreeNode *newNode;
    if((newNode = (BTreeNode *)malloc(sizeof(BTreeNode))) == NULL) return NULL;
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
    if (child != NULL) {
        node->isLeaf = false; // S'il y a un enfant, le nœud n'est plus une feuille
    } else {
        node->isLeaf = true; // Sinon, le nœud est une feuille
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
            node->size++;
            return true;
        }
    }
    return false;
}

static bool containsKey(void** value, int *pos, BTreeNode *node, int (*compareTo)(const void* key1, const void*key2)){
    if(node == NULL) return false;

    if (compareTo(value, node->values[1]) < 0) {
        *pos = 0;
    } else {
        for (*pos = node->size;
             (compareTo(value , node->values[*pos]) < 0 && *pos > 1); (*pos)--)
            ;
        if (compareTo(value, node->values[*pos]) == 0) {
            *value = node->values[*pos];
            return true;
        }
    }
    containsKey(value, pos, node->children[*pos], compareTo);

    return false;
}

static int find_index(BTree  *tree, BTreeNode* node, void* value) {
    int index = 0;
    while (index < node->size && tree->compareTo(node->values[index], value) < 0) {
        index++;
    }
    return index;
}

static BTreeNode * remove_helper(BTree* tree, BTreeNode* node, void* value) {
    if (node == NULL) {
        return NULL;
    }

    int i = 0;
    while (i < node->size && tree->compareTo(value , node->values[i]) > 0) {
        i++;
    }

    if (i < node->size && tree->compareTo(value , node->values[i]) == 0) {
        if (node->isLeaf) {
            // Supprimer la clé du nœud s'il est une feuille
            for (int j = i; j < node->size - 1; j++) {
                node->values[j] = node->values[j + 1];
            }
            node->size--;
            tree->size--;

            return node;
        } else {
            // Ajuster les pointeurs des enfants s'il y en a
            for (int k = i; k < node->size; k++) {
                node->children[k] = node->children[k + 1];
            }
            node->children[node->size] = NULL;

            node->size--;
            tree->size--;

            // Continuer la recherche récursive dans le bon enfant
            return remove_helper(tree, node->children[i], value);
        }
    } else {
        // La valeur n'a pas été trouvée dans le nœud actuel ni dans ses enfants
        return node;
    }
}

static int height(BTreeNode *node) {
    if (node == NULL) {
        return 0;
    }
    int leftHeight = height(node->children[0]);
    int rightHeight = height(node->children[node->size]);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int btree_diameter_helper(BTreeNode *node, int *diameter) {
    if (node == NULL) {
        return 0;
    }

    int leftHeight = height(node->children[0]);
    int rightHeight = height(node->children[node->size]);

    int leftDiameter = btree_diameter_helper(node->children[0], diameter);
    int rightDiameter = btree_diameter_helper(node->children[node->size], diameter);

    *diameter = (*diameter > leftHeight + rightHeight + 1) ? *diameter : leftHeight + rightHeight + 1;

    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
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
    bool created;
    void * pValue;
    BTreeNode *child;

    created = node_set_value(tree, tree->root, &child, value, &pValue );
    if (created){
        tree->root = node_create(tree, child, pValue);
        tree->size++;
    }

}

bool btree_remove(BTree* tree, void** value) {
    if (tree == NULL || tree->root == NULL) {
        return false;
    }

    // Call the recursive removal function starting from the root node
    if(value == NULL) value = &tree->root->values[tree->root->size];

    tree->root = remove_helper(tree, tree->root, *value);
    if(tree->root == NULL) return false;

    // Adjust the root node if necessary
    if (tree->root->size == 0) {
        BTreeNode* oldRoot = tree->root;
        value = oldRoot->values;
        if (oldRoot->size == 1) {
            tree->root = oldRoot->children[0];
        } else {
            tree->root = oldRoot->children[1];
        }
        tree->destroy(oldRoot);
    }

    return true;
}

bool btree_containsKey(BTree *tree, int* pos, void** value){
    return containsKey(value, pos, tree->root, tree->compareTo);
}

int btree_diameter(BTree *tree){
    if (tree == NULL || tree->root == NULL) {
        return 0;
    }

    int diameter = 0;
    btree_diameter_helper(tree->root, &diameter);

    return diameter;
}

int btree_height(BTree *tree){
    return height(tree->root);
}

