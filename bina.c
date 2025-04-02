#include <stdio.h>
#include <stdlib.h>
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;
TreeNode* createNode(int value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
TreeNode* insert(TreeNode* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
    
    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    }
    
    return root;
}
int search(TreeNode* root, int value) {
    if (root == NULL) {
        return 0;
    }
    if (root->data == value) {
        return 1;
    }
    if (value < root->data) {
        return search(root->left, value);
    }
    return search(root->right, value);
}
TreeNode* findMin(TreeNode* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}
TreeNode* delete(TreeNode* root, int value) {
    if (root == NULL) return root;
    
    if (value < root->data) {
        root->left = delete(root->left, value);
    } else if (value > root->data) {
        root->right = delete(root->right, value);
    } else {
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        }
        TreeNode* temp = findMin(root->right);
        root->data = temp->data;
        root->right = delete(root->right, temp->data);
    }
    return root;
}
void inorder(TreeNode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void preorder(TreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(TreeNode* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}
int height(TreeNode* root) {
    if (root == NULL) {
        return -1;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
}
int countNodes(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + countNodes(root->left) + countNodes(root->right);
}
int findMinValue(TreeNode* root) {
    if (root == NULL) {
        printf("Tree is empty!\n");
        return -1;
    }
    while (root->left != NULL) {
        root = root->left;
    }
    return root->data;
}
int findMaxValue(TreeNode* root) {
    if (root == NULL) {
        printf("Tree is empty!\n");
        return -1;
    }
    while (root->right != NULL) {
        root = root->right;
    }
    return root->data;
}
int main() {
    TreeNode* root = NULL;
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(values)/sizeof(values[0]);
    
    printf("Binary Tree Operations in C\n");
    printf("==========================\n\n");
    printf("1. Inserting values: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", values[i]);
        root = insert(root, values[i]);
    }
    printf("\n\n");
    printf("2. Tree Traversals:\n");
    printf("   Inorder:   ");
    inorder(root);
    printf("\n   Preorder:  ");
    preorder(root);
    printf("\n   Postorder: ");
    postorder(root);
    printf("\n\n");
    printf("3. Search Operations:\n");
    printf("   Is 40 in tree? %s\n", search(root, 40) ? "Yes" : "No");
    printf("   Is 90 in tree? %s\n\n", search(root, 90) ? "Yes" : "No");
   
    printf("4. Tree Properties:\n");
    printf("   Height: %d\n", height(root));
    printf("   Node count: %d\n", countNodes(root));
    printf("   Minimum value: %d\n", findMinValue(root));
    printf("   Maximum value: %d\n\n", findMaxValue(root));
   
    printf("5. Delete Operations:\n");
    printf("   Deleting 20 (leaf node)...\n");
    root = delete(root, 20);
    printf("   Inorder after deletion: ");
    inorder(root);
    printf("\n");
    
    printf("   Deleting 30 (node with one child)...\n");
    root = delete(root, 30);
    printf("   Inorder after deletion: ");
    inorder(root);
    printf("\n");
    
    printf("   Deleting 50 (node with two children)...\n");
    root = delete(root, 50);
    printf("   Inorder after deletion: ");
    inorder(root);
    printf("\n\n");
    printf("Final Tree State:\n");
    printf("   Inorder traversal: ");
    inorder(root);
    printf("\n   Height: %d\n", height(root));
    printf("   Node count: %d\n", countNodes(root));
    return 0;
}
