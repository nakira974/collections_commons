//
// Created by maxim on 8/03/2024.
//
#include <memory.h>
#include "bitree.h"
#include "queue.h"

bool bitree_isMirror(bool (*equals)(const void *value1, const void* value2), BinaryTreeNode* left, BinaryTreeNode* right){
 if (left == NULL && right == NULL)
        return true;
    if (left == NULL || right == NULL)
        return false;
    return (equals(left->value , right->value) && bitree_isMirror(equals, left->right, right->left) &&
            bitree_isMirror(equals, left->left, right->right));
}

BinaryTreeNode * bitree_invertBranch(BinaryTreeNode* root) {
    if (root == NULL)
        return NULL;
    BinaryTreeNode* temp = root->left;
    root->left = bitree_invertBranch(root->right);
    root->right = bitree_invertBranch(temp);
    return root;
}

bool bitree_isSameTree(bool (*equals)(const void *value1, const void* value2), BinaryTreeNode* left, BinaryTreeNode* right){
    if (left == NULL && right == NULL)
        return true;
    if (left == NULL || right == NULL)
        return false;
    if (!equals(left->value , right->value))
        return false;
    return bitree_isSameTree(equals, left->left, right->left) && bitree_isSameTree(equals, left->right, right->right);
}
int bitree_maxDepthBranch(BinaryTreeNode * root){
 if (root == NULL)
        return 0;
    int left_depth = bitree_maxDepthBranch(root->left);
    int right_depth = bitree_maxDepthBranch(root->right);
    return (left_depth > right_depth ? left_depth : right_depth) + 1;
}

int bitree_maxDepth(BinaryTree * tree){
     if (tree == NULL || tree->root == NULL)
        return 0;
    return bitree_maxDepthBranch(tree->root);
}

bool bitree_invert(BinaryTree *out, BinaryTree * tree){
    if(tree == NULL || tree->root == NULL) return false;
    if((out = (BinaryTree*) malloc(sizeof (BinaryTree))) == NULL) return false;
    memcpy(out, tree, sizeof (BinaryTree));
    out->root = bitree_invertBranch(out->root);

    return true;
}

void bitree_create(BinaryTree *tree, void(*destroy)(void* value)){
    tree->size = 0;
    tree->destroy = destroy;
    tree->root = NULL;
}

void bitree_destroy(BinaryTree *tree){
    // Remove all the node from the tree
    bitree_removeLeft(tree, NULL);
    // Erase the memory
    memset(tree, 0, sizeof (BinaryTreeNode));
}

bool bitree_addLeft(BinaryTree *tree, BinaryTreeNode *node, const void *value){
    BinaryTreeNode  *new_node, **position;

    // Determine where to insert the new node

    if(node == NULL){
        // For empty trees, we insert as root
        if(bitree_size(tree) > 0) return false;
        position = &tree->root;
    }else{
        // Normally inserted at the end of a branch
        if(bitree_left(node) != NULL) return false;
        position = &node->left;
    }

    // Allocate the new node
    if((new_node = (BinaryTreeNode*) malloc(sizeof(BinaryTreeNode))) == NULL){
        free(position);
        return false;
    }

    // Insert the node in the tree
    new_node->value = (void*) value;
    new_node->left = NULL;
    new_node->right = NULL;
    *position = new_node;

    tree->size++;
    return true;
}

bool bitree_addRight(BinaryTree *tree, BinaryTreeNode *node, const void *value){
    BinaryTreeNode *new_node, **position;

    if(node == NULL){
        if(bitree_size(tree)>0) return false;
        tree->root = node;
    }else{
        // Normally inserted at the end of a branch
        if(bitree_right(node) != NULL) return false;
        position = &node->right;
    }

    // Allocate the new node
    if((new_node = (BinaryTreeNode*) malloc(sizeof(BinaryTreeNode))) == NULL){
        free(position);
        return false;
    }

    // Insert the node in the tree
    new_node->value = (void*) value;
    new_node->left = NULL;
    new_node->right = NULL;
    *position = new_node;

    tree->size++;
    return true;
}

void bitree_removeLeft(BinaryTree *tree, BinaryTreeNode *node){
    BinaryTreeNode **position;

    // If the tree is empty
    if(bitree_size(tree) == 0) return;

    // Determine where to remove the node
    if(node == NULL)
        position = &tree->root;
    else
        position = &node->left;

    if(*position != NULL){
        bitree_removeLeft(tree, *position);
        bitree_removeRight(tree, *position);
        if(tree->destroy != NULL){
            tree->destroy((*position)->value);
        }

        free(*position);
        *position = NULL;

        tree->size--;
    }
}
void bitree_removeRight(BinaryTree *tree, BinaryTreeNode *node){
    BinaryTreeNode **position;
    // If the tree is empty
    if(bitree_size(tree) == 0) return;

    // Determine where to remove the node
    if(node == NULL)
        position = &tree->root;
    else
        position = &node->right;

    if(*position != NULL){
        bitree_removeLeft(tree, *position);
        bitree_removeRight(tree, *position);
        if(tree->destroy != NULL){
            tree->destroy((*position)->value);
        }

        free(*position);
        *position = NULL;

        tree->size--;
    }

}

bool bitree_merge(BinaryTree *out, BinaryTree *left, BinaryTree *right, const void *value){
    bitree_create(out, left->destroy);

    // Insert value at out's root
    if(!bitree_addLeft(out, NULL, value)){
        bitree_destroy(out);
        return false;
    }

    // Fusion two trees
    bitree_root(out)->left = bitree_root(left);
    bitree_root(out)->right = bitree_root(right);

    // Adjust the size of the fusion binary tree

    out->size = out->size + bitree_size(left) + bitree_size(right);

    // Original trees MUST not access to fusion nodes
    left->root = NULL;
    left->size = 0;
    right->root = NULL;
    right->size = 0;

    return true;
}

void **bitree_levelOrder(BinaryTree *tree, int *returnSize, int **returnColumnSizes) {
    if (tree == NULL || tree->root) {
        // Si l'arbre est vide, fixe la taille de retour à 0 et retourne NULL
        *returnSize = 0;
        return NULL;
    }

    void **result;

    // Crée une file pour stocker les nœuds
    Queue *queue,*nextQueue;
    if ((queue = (Queue *) malloc(sizeof(Queue))) == NULL) return NULL;
    queue_create(queue, tree->destroy);
    // Ajoute la racine à la file
    queue_enqueue(queue, tree->root);

    // Initialisation des tableaux de résultats
    int maxLevelNodes = bitree_maxDepth(tree);

    // Alloue de l'espace mémoire pour le tableau de résultats et le tableau des tailles de colonnes
    if((result = (void **) malloc(maxLevelNodes * sizeof(void *)))){
        queue_destroy(queue);
    }

    *returnColumnSizes = (int *) malloc(maxLevelNodes * sizeof(int));

    int levelIndex = 0; // Indice du niveau actuel

    // On instancie une autre file pour stocker les noeuds du prochain niveau
    if((nextQueue = (Queue *) malloc(sizeof(Queue))) == NULL){
        queue_destroy(queue);
        memset(result,0, sizeof (void*));
    }

    while (list_first(queue) != NULL) {
        // Taille arbitraire pour le tableau du niveau actuel
        void **currentLevel;
        if((currentLevel = malloc(maxLevelNodes * sizeof(void*))) ==NULL){
            queue_destroy(queue);
            queue_destroy(nextQueue);
            memset(result,0, sizeof (void*));
        }
        int count = 0; // Compteur pour les nœuds dans chaque niveau

        // Parcourt le niveau actuel jusqu'à ce que la file soit vide
        while (list_first(queue) != NULL) {
            // Récupère le nœud en tête de file
            BinaryTreeNode *currNode;
            queue_dequeue(queue, &currNode);
            // Ajoute la valeur du nœud au tableau du niveau actuel
            currentLevel[count++] = currNode->value;

            // Ajoute les enfants du nœud au prochain niveau s'ils existent
            if (currNode->left != NULL)
                queue_enqueue(nextQueue, currNode->left);
            if (currNode->right != NULL)
                queue_enqueue(nextQueue, currNode->right);
        }

        // Ajuste la taille du tableau du niveau actuel et l'ajoute au résultat
        if (levelIndex >= maxLevelNodes) {
            // Double la taille du tableau
            maxLevelNodes *= 2;
            result = (void **) realloc(result, maxLevelNodes * sizeof(void *));
            *returnColumnSizes =
                    (int *) realloc(*returnColumnSizes, maxLevelNodes * sizeof(int));
        }
        currentLevel = (void*) realloc(currentLevel, count * sizeof(void*));
        if(result != NULL){
            result[levelIndex] = currentLevel;
            (*returnColumnSizes)[levelIndex++] = count;
        }

        // Passe au prochain niveau en échangeant les files
        queue_destroy(queue);
        queue = nextQueue;
        queue_create(nextQueue, tree->destroy);
    }

    return result;
}


BinaryTreeNode * bitree_buildBranch(void** preorder, int preorder_size, void** inorder, int inorder_size){
    if (preorder_size == 0) {
        return NULL;
    }

    BinaryTreeNode * root;
    if((root = malloc(sizeof(struct BinaryTreeNode)))== NULL) return NULL;
    root->value = preorder[0];

    /*
     * We know root exists in our inorder array, so we can find the size of the
     * left subtree by searching for it
     */
    int left_size = 0;
    while (inorder[left_size] != root->value) {
        left_size++;
    }
    int right_size = preorder_size - left_size - 1;

    /*
     * So we can find our left subtree:
     *      (preorder[0], preorder[left_size]]
     *      [inorder[0], inorder[left_size])
     * and our right subtree:
     *      (preorder[left_size], preorder[preorder_size])
     *      (inorder[left_size], inorder[inorder_size])
     */
    root->left = bitree_buildBranch(preorder + 1, left_size, inorder, left_size);
    root->right = bitree_buildBranch(preorder + left_size + 1, right_size,
                                     inorder + left_size + 1, right_size);

    return root;
}

BinaryTree * bitree_build(void** preorder, int preorder_size, void** inorder, int inorder_size, void(*destroy)(void* value)){
    BinaryTree  *result;
    if((result = (BinaryTree*) malloc(sizeof (BinaryTree))) == NULL) return NULL;
    bitree_create(result, destroy);
    result->root = bitree_buildBranch(preorder, preorder_size, inorder, inorder_size);
    return result;
}