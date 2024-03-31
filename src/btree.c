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
 */
static void merge_nodes(BTreeNode *node, BTreeNode *sibling, BTreeNode *parent);

/**
 * @brief Private function that finds the parent of a given node
 * @param root Root node to find the parent
 * @param child Child node of the root node
 * @return Parent node of the root node
 */
static BTreeNode* find_parent(BTreeNode* root, BTreeNode* child);

/**
 * @brief Private function that finds the child of a given node
 * @param node Node to find the successor
 * @param position Position of the given node
 * @return Node's child
 */
static BTreeNode* find_successor(BTreeNode* node, int position);

/**
 * @brief Private function that removes a value from a given node at a specified index
 * @param node Node where to remove the value
 * @param position Index of the value to remove
 * @param value Removed value
 */
static void remove_key(BTreeNode* node, int position, void** value);

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
    for(int i=0; i<= BTREE_MAX_NODES; i++) (*newNode)->values[i] = NULL;
    for(int i=0; i<= BTREE_MAX_NODES; i++) (*newNode)->children[i] = NULL;

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
    (*newNode)->children[1] = node->children[node->size] == NULL ? node : node->children[node->size];
    node->values[node->size] = NULL;
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

static void merge_nodes(BTreeNode *node, BTreeNode *sibling, BTreeNode *parent) {
    // Fusionner les clés et les enfants du nœud avec le frère
    int index = 0;

    // Ajouter la clé du parent au nœud actuel
    node->values[node->size] = parent->values[index];
    node->size++;

    // Déplacer les clés du frère vers le nœud actuel
    for (int i = 0; i < sibling->size; i++) {
        node->values[node->size] = sibling->values[i];
        node->size++;
    }

    // Déplacer les enfants du frère vers le nœud actuel
    for (int i = 0; i <= sibling->size; i++) {
        node->children[node->size] = sibling->children[i];
    }

    // Mettre à jour le parent en retirant la clé fusionnée
    for (int i = index; i < parent->size - 1; i++) {
        parent->values[i] = parent->values[i + 1];
    }
    parent->size--;

    // Supprimer le frère fusionné
    free(sibling);

    // Mettre à jour les liens dans le parent
    for (int i = index; i < parent->size; i++) {
        parent->children[i] = parent->children[i + 1];
    }
}

static void remove_key(BTreeNode* node, int position, void** value) {
    // Décaler les clés et les enfants à partir de la position donnée
    *value = node->values[position];

    for (int i = position; i < node->size - 1; i++) {
        node->values[i] = node->values[i + 1];
    }

    // Décaler les enfants si le nœud n'est pas une feuille
    if (!node->isLeaf) {
        for (int i = position + 1; i < node->size; i++) {
            node->children[i] = node->children[i + 1];
        }
    }

    // Mettre à jour la taille du nœud après la suppression
    node->size--;
}

static BTreeNode* find_successor(BTreeNode* node, int position) {
    BTreeNode* current = node->children[position + 1];

    // Trouver le nœud le plus à gauche à partir du nœud actuel
    while (!current->isLeaf) {
        current = current->children[0];
    }

    return current;
}

static BTreeNode* find_parent(BTreeNode* root, BTreeNode* child) {
    // Si le nœud donné est la racine, il n'a pas de parent
    if (root == child) {
        return NULL;
    }

    // Parcourir l'arbre pour trouver le parent du nœud donné
    BTreeNode* parent = NULL;
    BTreeNode* current = root;
    int i = 0;

    while (current != NULL && !current->isLeaf) {
        for (i = 0; i < current->size; i++) {
            if (current->children[i] == child) {
                parent = current;
                break;
            }
            if (current->values[i] > child->values[0]) {
                break;
            }
        }
        current = current->children[i];
    }

    return parent;
}

static BTreeNode* remove_helper(BTree* tree, BTreeNode* node, void* value) {
    // Vérifier si le nœud est NULL
    if (node == NULL) {
        return NULL;
    }

    // Trouver la position de la clé dans le nœud
    int position = find_index(tree, node, value);

    // Si la clé est présente dans le nœud actuel
    if (position < node->size && tree->compareTo(node->values[position], value) == 0) {
        // Si le nœud est une feuille
        if (node->isLeaf) {
            // Supprimer la clé du nœud
            remove_key(node, position, &value);
        } else {
            // Remplacer la clé par la clé suivante dans le successeur
            BTreeNode* successor = find_successor(node, position);
            node->values[position] = successor->values[0];
            // Supprimer la clé du successeur
            remove_key(successor, 0, &value);
            // Appeler récursivement remove_helper sur le successeur
            node = remove_helper(tree, successor, value);
        }
    } else {
        // Appeler récursivement remove_helper sur le nœud approprié
        node = remove_helper(tree, node->children[position], value);
    }

    // Appeler node_balance pour équilibrer les nœuds
    if (node != NULL && node != tree->root) {
        node_balance(node, find_parent(tree->root, node), tree);
    }

    // Gérer le cas du nœud racine
    if (node != NULL && node == tree->root && node->size == 0) {
        // Si le nœud racine est vide, le remplacer par son unique enfant
        tree->root = node->children[0];
        tree->destroy(node);
    }

    return node;
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
    node->values[node->size] = tree->root->values[parent_index];
    node->size++;

    // Déplacer la clé du voisin de droite vers le parent
    tree->root->values[parent_index] = right_sibling->values[0];

    // Déplacer le premier enfant du voisin de droite vers le nœud actuel
    node->children[node->size] = right_sibling->children[0];

    // Réorganiser les clés et les enfants du voisin de droite
    for (int i = 0; i < right_sibling->size - 1; i++) {
        right_sibling->values[i] = right_sibling->values[i + 1];
        right_sibling->children[i] = right_sibling->children[i + 1];
    }

    // Mettre à jour les tailles des nœuds
    right_sibling->size--;
    node->size++;
}

static void redistribute_keys_left(BTreeNode* node, BTreeNode* left_sibling, int parent_index, BTree* tree) {
    // Déplacer la clé du parent vers le nœud actuel
    node->values[node->size] = tree->root->values[parent_index];
    node->size++;

    // Déplacer la clé du voisin de gauche vers le parent
    tree->root->values[parent_index] = left_sibling->values[left_sibling->size - 1];

    // Déplacer le dernier enfant du voisin de gauche vers le nœud actuel
    node->children[node->size] = left_sibling->children[left_sibling->size];

    // Mettre à jour les tailles des nœuds
    left_sibling->size--;
    node->size++;
}

static void node_balance(BTreeNode* node, BTreeNode* parent, BTree* tree) {
    if (node->size < BTREE_MIN_NODES) {
        // Trouver les frères gauche et droit du nœud
        BTreeNode* left_sibling = NULL;
        BTreeNode* right_sibling = NULL;
        int position = -1;

        for (int i = 0; i <= parent->size; i++) {
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
        } else if (right_sibling && right_sibling->size > BTREE_MIN_NODES) {
            // Redistribution des clés avec le frère droit
            redistribute_keys_right(node, right_sibling, position, tree);
        } else if (left_sibling) {
            // Fusionner avec le frère gauche
            merge_nodes(node, left_sibling, parent);
        } else if (right_sibling) {
            // Fusionner avec le frère droit
            merge_nodes(node, right_sibling, parent);
        }
    }
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
    if(child != NULL){
        for(int i =0; i< BTREE_MAX_NODES; i++){
            if(child->children[i] != NULL){
                child->isLeaf = false;
                break;
            }
        }
    }
    if (created){
        tree->root = tree->root == NULL ? node_create(tree, child, pValue) : child;
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

    if(tree->root == NULL){
        tree->size = 0;
        return true;
    }


    tree->size--;
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
    diameter_helper(tree->root, &diameter);

    return diameter;
}

int btree_height(BTree *tree){
    return height(tree->root);
}

