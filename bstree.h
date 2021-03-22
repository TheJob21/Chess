#pragma once
#include "tnode.h"
template <typename T>
class bstree{
private:
	tnode<T>* rootp;
	tnode<T>* insert(tnode<T>*, int);
	void inorder(tnode<T>*, void(*)(int));
	void preorder(tnode<T>*, void(*)(int));
	void postorder(tnode<T>*, void(*)(int));
	int find_min(tnode<T>*);
	int leaf_count(tnode<T>*);
	int node_count(tnode<T>*);
	int layer_count(tnode<T>*);
	tnode<T>* erase(tnode<T>*, int);
public:
	bstree();
	~bstree();
	void insert(int);
	void traverse_breadth();
	void inorder(void(*)(int));
	void preorder(void(*)(int));
	void postorder(void(*)(int));
	int find_min();
	int leaf_count();
	int node_count();
	int layer_count();
	int height();
	void erase(int);	
};