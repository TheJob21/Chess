#include "tnode.h"
#include "bstree.h"
#include <iostream>
#include <queue>
#include <cassert>
using namespace std;

template <typename T>
bstree<T>::bstree() : rootp(NULL){}

template <typename T>
bstree<T>::~bstree(){
	if (rootp == NULL){
		return;
	}
	
	queue<tnode*> q;
	q.push(rootp);
	while (!q.empty()) {
		tnode* r = q.front();
		q.pop();
		if (r->left != NULL){
			q.push(r->left);
		}
		if (r->right != NULL){
			q.push(r->right);
		}
		delete r;
	}
}

template <typename T>
void bstree<T>::insert(int data){
	rootp = insert(rootp, data);
}

//private implementation
template <typename T>
tnode<T>* bstree<T>::insert(tnode<T>* r, int data){
	if (r == NULL){
		r = new tnode(data);
	}
	else if (r->data < data){
		r->right = insert(r->right, data);
	}
	else if (r->data > data){
		r->left = insert(r->left, data);
	}
	return r;
}

template <typename T>
void bstree<T>::traverse_breadth(){
	if (rootp == NULL){
		cout << "[null]" << endl;
	}
	
	queue<tnode*> q;
	q.push(rootp);
	while (!q.empty()) {
		tnode* r = q.front();
		q.pop();
		cout << r->data << " (left.right)=> ";
		if (r->left != NULL){
			q.push(r->left);
			cout << r->left->data << " ";
		}
		else{
			cout << "null ";
		}
		if (r->right != NULL){
			q.push(r->right);
			cout << r->right->data << " ";
		}
		else{
			cout << "null ";
		}
		cout << endl;
	}
}

template <typename T>
void bstree<T>::inorder(void (*f)(int)){
	inorder(rootp, f);
}

//Private implementation
template <typename T>
void bstree<T>::inorder(tnode<T>* r, void (*f)(int)){
	if (r == NULL)
		return;
	inorder(r->left, f);
	(*f)(r->data);
	inorder(r->right, f);
}

template <typename T>
void bstree<T>::preorder(void(*f)(int)){
	preorder(rootp, f);
}

//Private implementation
template <typename T>
void bstree<T>::preorder(tnode<T>* r, void(*f)(int)){
	if (r == NULL)
		return;
	(*f)(r->data);
	preorder(r->left, f);
	preorder(r->right, f);
}

template <typename T>
void bstree<T>::postorder(void(*f)(int)){
	postorder(rootp, f);
}
	
//Private implementation
template <typename T>
void bstree<T>::postorder(tnode<T>* r, void(*f)(int)){
	if (r == NULL)
		return;
	postorder(r->left, f);
	postorder(r->right, f);
	(*f)(r->data);
}

template <typename T>
int bstree<T>::find_min(){
	find_min(rootp);
}

//Private implementation
template <typename T>
int bstree<T>::find_min(tnode<T>* r){
	assert(r != NULL);
	if(r->left == NULL)
		return r->data;
	else
		return find_min(r->left);
}

template <typename T>
int bstree<T>::leaf_count(){
	return leaf_count(rootp);
}

//Private implementation
template <typename T>
int bstree<T>::leaf_count(tnode<T>* r){
	if (r == NULL)
		return 0;
	else if (r->left == NULL && r->right == NULL)
		return 1;
	else
		return leaf_count(r->left) + leaf_count(r->right);
}

template <typename T>
int bstree<T>::node_count(){
	return node_count(rootp);
}

//Private implementation
template <typename T>
int bstree<T>::node_count(tnode<T>* r){
	if (r == NULL)
		return 0;
	else return node_count(r->left) + node_count(r->right) + 1;
}

template <typename T>
int bstree<T>::layer_count(){
	return layer_count(rootp);
}

//Private implementation
template <typename T>
int bstree<T>::layer_count(tnode<T> * r){
	if (r == NULL)
		return 0;
	else if (r->left == NULL && r->right == NULL)
		return 1;
	else{
		 int ll = layer_count(r->left);
		 int lr = layer_count(r->right);
		 return ll > lr ? ll + 1 : lr + 1;
	}
}

template <typename T>
int bstree<T>::height(){
	assert(rootp != NULL);
	return layer_count(rootp) - 1;
}

template <typename T>
void bstree<T>::erase(int data){
	assert(rootp != NULL);
	rootp = erase(rootp, data);
}

//Private Implementation
template <typename T>
tnode<T>* bstree<T>:: erase(tnode<T>* r, int data){
	if (r == NULL)
		return NULL;
	if (data < r->data)
		r->left = erase(r->left, data);
	else if (data > r->data)
		r->right = erase(r->right, data);
	else{
		//Data == r->data
		if (r->left != NULL && r->right != NULL){
			// both L and R subtree exist
			int mindata = find_min(r->right);
			r->data = mindata;
			r->right = erase(r->right, mindata);
		}
		else{
			// only one subtree exists or no subtree
			tnode* discard = r;
			r = (r->left != NULL) ? r->left : r->right;
			delete discard;
		}
	}
	return r;
}