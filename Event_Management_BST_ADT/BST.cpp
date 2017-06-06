//BST.cpp for Program# 4 by Tejas Menon, CS163, last edited on 5/29.
//Purpose: This file contains the class implementation for the BST and is the highest level class
//         that only deals with the basic data type event.
#include "header.h"

//The constructor sets the root to NULL
BST::BST()
{
 root = NULL; 
}

//The destructor deallocates the root which then implicitly invokes
//the destructor in each node
BST::~BST()
{
 if (root) delete root;
}

//Returns the current height of the tree for effeciency evaluation
int BST::getHeight()
{
 return getHeight(root);
}

//Recursive secondary for the above function
int BST::getHeight(node* root) 
{
 int count = 0;
 if (root) count = 1+ max(getHeight(root->left),getHeight(root->right));
 return count;
} 
 
//This function removes the node with a matching title 
bool BST::remove(char *title)
{
 return remove(title,root); 
}

//Recursive secondary for the above function
bool BST::remove(char *title,node*& root)
{
 if (!root) return 0;
 if (strcmp(title,(root->an_event).title)<0) return remove(title,root->left);
 if (strcmp(title,(root->an_event).title)>0) return remove(title,root->right);
 node*hold = root->right;
 if (!hold) {
  hold = root->left;
  root->left = NULL;
 } if (!root->left) { 
  root->right = NULL;
  delete root;
  root = hold;
  return 1;
 }
 node*prev=root;
 while(hold->left) {
  prev = hold;
  hold = hold->left;
 }
 if(prev==root) prev->right = hold->right;
 else prev->left = hold->right;
 hold->right = NULL;
 (root->an_event).copy(hold->an_event);
 delete hold; 
 return 1;
}

//Remove all nodes in the BST containing the provided keyword.
bool BST::remove_key(char keyword[])
{
 return remove_key(root,keyword);
}  

bool BST::remove_key(node*&root,char keyword[])
{
 int check = 0;
 if (!root) return check;
 if (key_in_event(root->an_event,keyword)) {
  remove((root->an_event).title,root);
  return remove_key(root,keyword)+1;
 } 
 if (remove_key(root->left,keyword)) check =1;
 if (remove_key(root->right,keyword)) check =1;
 return check;
}

//This function adds into the BST an event at a leaf
bool BST::add(event&an_event)
{
 event temp; //temporarily points to the event to be added
 if(!temp.copy(an_event)) return 0;
 return add(root,temp);
}

//Recursive secondary for the above function
bool BST::add(node*&root,event&an_event)
{
 if(!root) {
  root = new node;
  (root->an_event).copy(an_event);
  root->right = root->left = NULL;
  return 1;
 }
 if (strcmp(an_event.title,(root->an_event).title)>0) return add(root->right,an_event);
 if (strcmp(an_event.title,(root->an_event).title)<0) return add(root->left,an_event);
 return 0; //exact match
} 
 
//This function retrieves from the BST the first event that has a matching title to the argument
bool BST::retrieve(char title[],event&an_event)
{
 return retrieve(root,title,an_event);
}

//This function is the recursive secondary of the above function
bool BST::retrieve(node*root,char *title,event&an_event)
{
 if (!root) return 0;
 if (!strcmp(title,(root->an_event).title)) {
  an_event.copy(root->an_event);
  return 1;
 }
 if (strcmp(title,(root->an_event).title)>0) return retrieve(root->right,title,an_event);
 return retrieve(root->left,title,an_event);
}
  
//This function checks within an event if it contains the keyword specified.
bool BST::key_in_event(event &an_event,char keyword[])
{
 bool check = false;
 for(int i=0;i<(an_event.num_key);++i) {
  if (!strcmp(keyword,(an_event.words[i]).word)) check = true;
 }
 return check;
}

//This function displays everything in the BST
bool BST::display_all()
{
 return display_all(root); 
} 

//This function is the recursive secondary for the function above
bool BST::display_all(node*root)
{
 if (!root) return 0;
 display_all(root->left);
 (root->an_event).display();
 display_all(root->right);
 return 1;
}
