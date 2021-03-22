#pragma once
#include <iostream>
using namespace std;

#define nullptr NULL

template <typename T>
class tnode{
private:
	T data;
	tnode<T>* link;
public:
	tnode(T);
	
	template <typename U> friend class bstree;
};

template <typename T>
tnode<T>::tnode(T d) : data(d), link(nullptr){
}
