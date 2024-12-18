#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int value;
    struct node* left;
    struct node* right;
};

void dfs_traverse(struct node* root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root->value);
    dfs_traverse(root->left);
    dfs_traverse(root->right);
}