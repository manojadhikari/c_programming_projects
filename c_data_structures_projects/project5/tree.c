/*
    Manoj Adhikari
	Monday 2:15
	Project #5, Tree

	This file includes functions that create a tree and perform operations related to adding, removing, and searching data in the tree. 
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct tree{
		int data;
		struct tree *left, *right, *parent;
};

void detach (struct tree * root);

/*
   This function creates a new DEQUE by using malloc and sets the counter to 0.  
 O(1)
 */
struct tree  *createTree (int data, struct tree *left, struct tree *right){
		struct tree *root;
		root=malloc (sizeof(struct tree));
		assert (root!=NULL);
		detach (left);
		detach (right);
		detach(root);

		root->parent=NULL;
		root->left=left;
		root->right=right;
		root->data=data;
		return root;
}

/*
   This function returns the data in the root of the subtree pointed to by root
   */
int getData (struct tree *root){
		return root->data;
}

/*
   This function returns the left subtree of the subtree pointed to by root
   */
struct tree *getLeft (struct tree *root){
		return root->left;
}

/*
   This function returns the right subtree of the subtree pointed to by root
   */
struct tree *getRight (struct tree *root){
		return root->right;
}

/*
   This function returns the parent tree of the subtree pointed to by root
   */
struct tree *getParent (struct tree *root){
		return root->parent;
}

/*
   This function updates the left subtree of the root
   */
void setLeft (struct tree *root, struct tree *left){
		assert (root!=NULL);
		detach (root);
		root->left=left;
		left->parent=root;
}
/*
   This function updates the right subtree of the root
   */
void setRight (struct tree *root, struct tree *right){
		assert(root!=NULL);
		detach (root);
		root->right=right;
		right->parent=root;
}

/*
   This function deallocates memory for the entire subtree pointed to by root
   */
void destroyTree (struct tree *root){
		if(root==NULL)
				return;
		destroyTree(root->left);
		destroyTree(root->right);
		free(root);
}

/*
   This is a detach function that is used if a root is pointed by two different pointers
   */
void detach(struct tree *root){
		if (root!=NULL && root->parent!=NULL){
				if (root==root->parent->right)//problem on this statement
						root->parent->right=NULL;
				if (root==root->parent->left)
						root->parent->left=NULL;

		}
		return;
}
