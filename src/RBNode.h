#pragma once

//RBTNode.h
enum RBTColor { Black, Red };

template<class KeyType>
struct  RBTNode
{
	KeyType key;
	size_t occurenceFrequency = 0;
	RBTColor color;
	RBTNode<KeyType>* left;
	RBTNode<KeyType>* right;
	RBTNode<KeyType>* parent;
	RBTNode(KeyType k, RBTColor c, RBTNode* p, RBTNode* l, RBTNode* r) :
		key(k), color(c), parent(p), left(l), right(r) { };
};

