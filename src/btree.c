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
            if (found) break;
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

static bool merge_nodes(BTreeNode *node_left, BTreeNode *node_right, BTreeNode **parent, int parent_key_index, BTree *tree) {
    // Insérer la clé du parent dans le nœud de gauche
    node_left->values[node_left->size + 1] = (*parent)->values[parent_key_index];
    node_left->size += 1;

    // Copier tous les enfants du nœud de droite dans le nœud de gauche
    for (int i = 1; i <= node_right->size; i++) {
        node_left->values[node_left->size + 1] = node_right->values[i];
        node_left->children[node_left->size + 1] = node_right->children[i];
        node_left->size += 1;
    }
    node_left->children[node_left->size + 1] = node_right->children[node_right->size + 1];

    // Supprimer la clé du parent et le nœud de droite
    (*parent)->values[parent_key_index+1] = (*parent)->values[parent_key_index + 1];
    (*parent)->children[parent_key_index] = (*parent)->children[parent_key_index + 1];
    for (int i = parent_key_index + 1; i <= (*parent)->size; i++) {
        (*parent)->values[i] = (*parent)->values[i + 1];
        (*parent)->children[i] = (*parent)->children[i + 1];
    }
    (*parent)->size -= 1;

    // Libérer le nœud de droite
    tree->destroy(node_right);

    reorderValues(node_left->values, 1);
    reorderValues((void**)node_left->children, 0);
    return true;
}

static void remove_key(BTreeNode* node, int position, void** value) {
    // Décaler les clés et les enfants à partir de la position donnée
    *value = node->values[position];
    node->values[position] = NULL;
    reorderValues(node->values,1);


    // Décaler les enfants si le nœud n'est pas une feuille
    if (!node->isLeaf) {
        for (int i = position; i < BTREE_MAX_NODES; i++) {
            node->children[i] = node->children[i + 1];
            node->children[i + 1] = NULL;
        }
    }

    // Mettre à jour la taille du nœud après la suppression
    node->size--;
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

static void remove_helper(BTree* tree, BTreeNode* node, void* value) {
    // Vérifier si le nœud est NULL
    if (node == NULL) {
        return;
    }

    // Trouver la position de la clé dans le nœud
    int position = 1;
    BTreeNode *pNode;
    containsKey(&value, &position, &node, &pNode, tree->compareTo);
    // Si la clé est présente dans le nœud actuel
    if (tree->compareTo((pNode)->values[position], value) == 0) {
        // Si le nœud est une feuille
        if ((pNode)->isLeaf) {
            // Supprimer la clé du nœud
            (pNode)->values[position] = NULL;
            (pNode)->size--;
            if(pNode->size == 0){
                // Remove the successor
                BTreeNode *parent = find_parent(tree, tree->root, pNode);
                if(parent!=NULL ){
                    int pos = find_index(tree, parent,pNode);
                    // Leaf destruction
                    tree->destroy(pNode);
                    pNode = NULL;
                    (parent)->children[pos] = NULL;
                    reorderValues((void**) (parent)->children,0);
                    pNode = parent;
                    tree->size--;
                    return;
                }
            }
            reorderValues((pNode)->values,1);
            return;
        } else {
            // Remplacer la clé par la clé suivante dans le successeur
            int successorIndex = 0;
            BTreeNode* successor =(pNode)->children[0];
            // Supprimer la clé du nœud
            (pNode)->values[position] = successor == NULL ? NULL : successor->values[1];
            if(successor != NULL && successor->values[1] == NULL){
                (pNode)->size--;
                reorderValues((pNode)->values,1);
            }
            else if(successor != NULL){
                // Supprimer la clé du succésseur
                successor->values[1] = NULL;
                successor->size--;
                reorderValues(successor->values,1);
            }
            // Appeler récursivement remove_helper sur le successeur
            if(successor != NULL && successor->size == 0){

                if(successor->children[0] == NULL) {
                    tree->destroy(successor);
                    (pNode)->children[0] = NULL;
                    reorderValues((void**) (pNode)->children,0);
                }
                successor = NULL;
                tree->size--;
                (pNode)->isLeaf = true;
                for(int i=0; i<BTREE_MIN_NODES; i++) if((pNode)->children[i] != NULL) (pNode)->isLeaf = false;
            }
        }
    } else {
        value = NULL;
        return;
    }

    // Appeler node_balance pour équilibrer les nœuds
    BTreeNode *parent = find_parent(tree, tree->root, (pNode));

    node_balance((pNode), parent, tree);

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

static void redistribute_keys_right(BTreeNode* node, BTreeNode* right_sibling, int parent_index, BTree* tree) {
    // Déplacer la clé du parent vers le nœud actuel
    node->values[node->size+1] = tree->root->values[parent_index];
    node->size++;

    // Déplacer la clé du voisin de droite vers le parent
    tree->root->values[parent_index] = right_sibling->values[right_sibling->size];
    right_sibling->values[right_sibling->size] = NULL;
    right_sibling->size--;
    // Déplacer le premier enfant du voisin de droite vers le nœud actuel
    node->children[node->size] = right_sibling->children[right_sibling->size];
    right_sibling->children[right_sibling->size] = NULL;

    // Réorganiser les clés du voisin de droite
    reorderValues(right_sibling->values,1);
    // Réorganiser les enfants du voisin de droite
    reorderValues((void**) right_sibling->children,0);
}

static void redistribute_keys_left(BTreeNode* node, BTreeNode* left_sibling, int parent_index, BTree* tree) {
    // Déplacer la clé du parent vers le nœud actuel
    node->values[node->size+1] = tree->root->values[parent_index];
    if( tree->root->values[parent_index] != NULL)
        node->size++;

    // Déplacer la clé du voisin de gauche vers le parent
    tree->root->values[parent_index] = left_sibling->values[left_sibling->size];
    left_sibling->values[left_sibling->size] = NULL;
    left_sibling->size--;
    // Déplacer le dernier enfant du voisin de gauche vers le nœud actuel
    node->children[node->size] = left_sibling->children[left_sibling->size];
    left_sibling->children[left_sibling->size] = NULL;
    reorderValues(left_sibling->values,1);
    reorderValues((void**) left_sibling->children, 0);
}

static void node_remain(void** obj, int* count){
    *count = 0;
    for(int i=0; i<= BTREE_MAX_NODES; i++) if(obj[i] != NULL) *count = *count + 1;
}

static void redistribute_children(BTreeNode** pParent, BTreeNode* pChild, BTree * tree, BTreeNode** childPtr){
    if(pParent == NULL || pChild == NULL) return;
    int remain;
    node_remain((void **) (*pParent)->children, &remain);
    reorderValues((void**) (*pParent)->children, 0);
    if(remain <= 0) return;
    if(pChild->isLeaf) pChild->isLeaf = false;
    for(int i =0; i<= BTREE_MAX_NODES; i++){
        for(int j=0; j<=BTREE_MAX_NODES; j++){
            if(pChild->children[i] == NULL && (*pParent)->children[j] != NULL && (*pParent)->children[j] != *childPtr){
                pChild->children[i] = (*pParent)->children[j];
                (*pParent)->children[j] = NULL;
                remain--;
                break;
            }else if(remain <= 0) break;
        }
    }
    if(remain > 0){

        reorderValues((void**) (pChild)->children, 0);
        redistribute_children(pParent, pChild->children[0], tree, childPtr);
        return;
    }

    BTreeNode * grand_parent = find_parent(tree, tree->root, *pParent);

    // Is root
    if(grand_parent == *pParent){
        tree->root = *childPtr;
    }

    // Remove the pParent from the grandparent
    tree->destroy(*pParent);
    tree->size--;
    (*pParent) = NULL; // ensure that we won't accidentally use pParent

    if (*childPtr != NULL){
        (*childPtr)->isLeaf = true;
        for(int i=0;i<=BTREE_MAX_NODES; i++){
            if((*childPtr)->children[i] != NULL){
                (*childPtr)->isLeaf = false;
                break;
            }
        }
    }
}


static void node_balance(BTreeNode* node, BTreeNode* parent, BTree* tree) {
    if(node == NULL || parent == NULL || node->isLeaf) return;

    reorderValues(node->values, 1);
    if (node->size < BTREE_MIN_NODES) {
        // Trouver les frères gauche et droit du nœud
        BTreeNode* left_sibling = NULL;
        BTreeNode* right_sibling = NULL;
        int position = -1;

        for (int i = 1; i <= BTREE_MAX_NODES; i++) {
            if (parent->children[i] == node) {
                position = i;
                if (i > 0) {
                    left_sibling = parent->children[i - 1];
                }
                if (i < parent->size) {
                    right_sibling = parent->children[i + 1];
                }
                break;
            }
        }

        if (left_sibling && left_sibling->size > BTREE_MIN_NODES) {
            // Redistribution des clés avec le frère gauche
            redistribute_keys_left(node, left_sibling, position, tree);
            int count = 0;
            for(int i =1; i<=BTREE_MAX_NODES; i++){
                if(left_sibling->values[i] != NULL) count++;
            }
            left_sibling->size = count;
        } else if (right_sibling && right_sibling->size > BTREE_MIN_NODES) {
            // Redistribution des clés avec le frère droit
            redistribute_keys_right(node, right_sibling, position, tree);
            int count = 0;
            for(int i =1; i<=BTREE_MAX_NODES; i++){
                if(right_sibling->values[i] != NULL) count++;
            }
            right_sibling->size = count;
        } else if (left_sibling) {
            // Fusionner avec le frère gauche
            merge_nodes(node, left_sibling, &parent, find_index(tree, node, parent), tree);

        } else if (right_sibling) {
            // Fusionner avec le frère droit
            merge_nodes(node, right_sibling, &parent, find_index(tree, node, parent), tree);
        }

    }

    int count = 0;
    for(int i =1; i<=BTREE_MAX_NODES; i++){
        if(node->values[i] != NULL) count++;
    }
    node->size = count;
    if(parent == NULL) return;
    count = 0;
    for(int i =1; i<=BTREE_MAX_NODES; i++){
        if(parent->values[i] != NULL) count++;
    }
    parent->size = count;
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

bool btree_remove(BTree* tree, void** value) {
    if (tree == NULL || tree->root == NULL) {
        return false;
    }

    // Call the recursive removal function starting from the root node
    if(value == NULL) value = &tree->root->values[tree->root->size];

    remove_helper(tree, tree->root, *value);
    if(*value == NULL) return false;

    if(tree->root == NULL){
        tree->size = 0;
        return true;
    }

    return true;
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

