//#pragma once
//struct TwoThreeNode {
//public:
//	size_t occurenceFrequency;
//	int size;      // ���������� ������� ������
//	int key[3];
//	TwoThreeNode* children[3];
//	//TwoThreeNode* first;   // *first <= key[0];
//	//TwoThreeNode* second;  // key[0] <= *second < key[1];
//	//TwoThreeNode* third;   // key[1] <= *third < key[2];
//	//TwoThreeNode* fourth;  // key[2] <= *fourth.
//	TwoThreeNode* parent; //��������� �� �������� ����� ��� ����, ������ ��� ����� ����� ����� �������� ��� ��������
//
//	bool find(int k) { // ���� ����� ���������� true, ���� ���� k ��������� � �������, ����� false.
//		for (int i = 0; i < size; ++i)
//			if (key[i] == k) return true;
//		return false;
//	}
//
//	void swap(int& x, int& y) {
//		int r = x;
//		x = y;
//		y = r;
//	}
//
//	void sort2(int& x, int& y) {
//		if (x > y) swap(x, y);
//	}
//
//	void sort3(int& x, int& y, int& z) {
//		if (x > y) swap(x, y);
//		if (x > z) swap(x, z);
//		if (y > z) swap(y, z);
//	}
//
//	void sort() { // ����� � �������� ������ ���� �������������
//		if (size == 1) 
//			return;
//		if (size == 2) 
//			sort2(key[0], key[1]);
//		if (size == 3) 
//			sort3(key[0], key[1], key[2]);
//	}
//
//	void insert_to_node(int k) {  // ��������� ���� k � ������� (�� � ������)
//		key[size] = k;
//		size++;
//		sort();
//	}
//
//	void remove_from_node(int k) { // ������� ���� k �� ������� (�� �� ������)
//		if (size >= 1 && key[0] == k) {
//			key[0] = key[1];
//			key[1] = key[2];
//			size--;
//		}
//		else if (size == 2 && key[1] == k) {
//			key[1] = key[2];
//			size--;
//		}
//	}
//
//	void become_node2(int k, TwoThreeNode* first_, TwoThreeNode* second_) {  // ������������� � 2-�������.
//		key[0] = k;
//		size = 1;
//
//		children[0] = first_;
//		children[1] = second_;
//		children[2] = nullptr;
//		//first = first_;
//		//second = second_;
//		//third = nullptr;
//		//fourth = nullptr;
//		parent = nullptr;
//	}
//
//	bool is_leaf() { // �������� �� ���� ������; �������� ������������ ��� ������� � ��������.
//		//return (first == nullptr) && (second == nullptr) && (third == nullptr);
//		return (children[0] == nullptr) && (children[1] == nullptr) && (children[2] == nullptr);
//	}
//
//public:
//	// ��������� ������ ����� ������� ������ � ����� ������
//	//TwoThreeNode(int k) : occurenceFrequency(1), size(1), key{ k, 0, 0 }, first(nullptr), second(nullptr),
//	//	third(nullptr), fourth(nullptr), parent(nullptr) {}
//
//	//TwoThreeNode(int k, TwoThreeNode* first_, TwoThreeNode* second_, TwoThreeNode* third_, TwoThreeNode* fourth_, TwoThreeNode* parent_) :
//	//	occurenceFrequency(1), size(1), key{ k, 0, 0 }, first(first_), second(second_),
//	//	third(third_), fourth(fourth_), parent(parent_) {}
//
//	TwoThreeNode(int k) : occurenceFrequency(1), size(1), key{ k, 0, 0 }, first(nullptr), second(nullptr),
//		third(nullptr), parent(nullptr) {}
//
//	TwoThreeNode(int k, TwoThreeNode* first_, TwoThreeNode* second_, TwoThreeNode* third_, TwoThreeNode* parent_) :
//		occurenceFrequency(1), size(1), key{ k, 0, 0 }, first(first_), second(second_),
//		third(third_), parent(parent_) {}
//
//	//friend TwoThreeNode* split(TwoThreeNode* item); // ����� ��� ���������� ������� ��� ������������;
//	friend TwoThreeNode* insert(TwoThreeNode* p, int k); // ������� � ������;
//	//friend TwoThreeNode* search(TwoThreeNode* p, int k); // ����� � ������;
//	//friend TwoThreeNode* search_min(TwoThreeNode* p); // ����� ������������ �������� � ���������; 
//	//friend TwoThreeNode* merge(TwoThreeNode* leaf); // ������� ������������ ��� ��������;
//	//friend TwoThreeNode* redistribute(TwoThreeNode* leaf); // ����������������� ����� ������������ ��� ��������;
//	//friend TwoThreeNode* fix(TwoThreeNode* leaf); // ������������ ����� �������� ��� ����������� ������� ������ (���������� merge ��� redistribute) 
//	//friend TwoThreeNode* remove(TwoThreeNode* p, int k); // ����������, �� �������� �������;
//	//friend void removeAll(TwoThreeNode* p); 
//};
//
//TwoThreeNode*redistribute(TwoThreeNode*leaf) {
//    TwoThreeNode *parent = leaf->parent;
//    TwoThreeNode *first = parent->first;
//    TwoThreeNode *second = parent->second;
//    TwoThreeNode *third = parent->third;
//
//    if ((parent->size == 2) && (first->size < 2) && (second->size < 2) && (third->size < 2)) {
//        if (first == leaf) {
//            parent->first = parent->second;
//            parent->second = parent->third;
//            parent->third = nullptr;
//            parent->first->insert_to_node(parent->key[0]);
//            parent->first->third = parent->first->second;
//            parent->first->second = parent->first->first;
//
//            if (leaf->first != nullptr) parent->first->first = leaf->first;
//            else if (leaf->second != nullptr) parent->first->first = leaf->second;
//
//            if (parent->first->first != nullptr) parent->first->first->parent = parent->first;
//
//            parent->remove_from_node(parent->key[0]);
//            delete first;
//        } else if (second == leaf) {
//            first->insert_to_node(parent->key[0]);
//            parent->remove_from_node(parent->key[0]);
//            if (leaf->first != nullptr) first->third = leaf->first;
//            else if (leaf->second != nullptr) first->third = leaf->second;
//
//            if (first->third != nullptr) first->third->parent = first;
//
//            parent->second = parent->third;
//            parent->third = nullptr;
//
//            delete second;
//        } else if (third == leaf) {
//            second->insert_to_node(parent->key[1]);
//            parent->third = nullptr;
//            parent->remove_from_node(parent->key[1]);
//            if (leaf->first != nullptr) second->third = leaf->first;
//            else if (leaf->second != nullptr) second->third = leaf->second;
//
//            if (second->third != nullptr)  second->third->parent = second;
//
//            delete third;
//        }
//    } else if ((parent->size == 2) && ((first->size == 2) || (second->size == 2) || (third->size == 2))) {
//        if (third == leaf) {
//            if (leaf->first != nullptr) {
//                leaf->second = leaf->first;
//                leaf->first = nullptr;
//            }
//
//            leaf->insert_to_node(parent->key[1]);
//            if (second->size == 2) {
//                parent->key[1] = second->key[1];
//                second->remove_from_node(second->key[1]);
//                leaf->first = second->third;
//                second->third = nullptr;
//                if (leaf->first != nullptr) leaf->first->parent = leaf;
//            } else if (first->size == 2) {
//                parent->key[1] = second->key[0];
//                leaf->first = second->second;
//                second->second = second->first;
//                if (leaf->first != nullptr) leaf->first->parent = leaf;
//
//                second->key[0] = parent->key[0];
//                parent->key[0] = first->key[1];
//                first->remove_from_node(first->key[1]);
//                second->first = first->third;
//                if (second->first != nullptr) second->first->parent = second;
//                first->third = nullptr;
//            }
//        } else if (second == leaf) {
//            if (third->size == 2) {
//                if (leaf->first == nullptr) {
//                    leaf->first = leaf->second;
//                    leaf->second = nullptr;
//                }
//                second->insert_to_node(parent->key[1]);
//                parent->key[1] = third->key[0];
//                third->remove_from_node(third->key[0]);
//                second->second = third->first;
//                if (second->second != nullptr) second->second->parent = second;
//                third->first = third->second;
//                third->second = third->third;
//                third->third = nullptr;
//            } else if (first->size == 2) {
//                if (leaf->second == nullptr) {
//                    leaf->second = leaf->first;
//                    leaf->first = nullptr;
//                }
//                second->insert_to_node(parent->key[0]);
//                parent->key[0] = first->key[1];
//                first->remove_from_node(first->key[1]);
//                second->first = first->third;
//                if (second->first != nullptr) second->first->parent = second;
//                first->third = nullptr;
//            }
//        } else if (first == leaf) {
//            if (leaf->first == nullptr) {
//                leaf->first = leaf->second;
//                leaf->second = nullptr;
//            }
//            first->insert_to_node(parent->key[0]);
//            if (second->size == 2) {
//                parent->key[0] = second->key[0];
//                second->remove_from_node(second->key[0]);
//                first->second = second->first;
//                if (first->second != nullptr) first->second->parent = first;
//                second->first = second->second;
//                second->second = second->third;
//                second->third = nullptr;
//            } else if (third->size == 2) {
//                parent->key[0] = second->key[0];
//                second->key[0] = parent->key[1];
//                parent->key[1] = third->key[0];
//                third->remove_from_node(third->key[0]);
//                first->second = second->first;
//                if (first->second != nullptr) first->second->parent = first;
//                second->first = second->second;
//                second->second = third->first;
//                if (second->second != nullptr) second->second->parent = second;
//                third->first = third->second;
//                third->second = third->third;
//                third->third = nullptr;
//            }
//        }
//    } else if (parent->size == 1) {
//        leaf->insert_to_node(parent->key[0]);
//
//        if (first == leaf && second->size == 2) {
//            parent->key[0] = second->key[0];
//            second->remove_from_node(second->key[0]);
//
//            if (leaf->first == nullptr) leaf->first = leaf->second;
//
//            leaf->second = second->first;
//            second->first = second->second;
//            second->second = second->third;
//            second->third = nullptr;
//            if (leaf->second != nullptr) leaf->second->parent = leaf;
//        } else if (second == leaf && first->size == 2) {
//            parent->key[0] = first->key[1];
//            first->remove_from_node(first->key[1]);
//
//            if (leaf->second == nullptr) leaf->second = leaf->first;
//
//            leaf->first = first->third;
//            first->third = nullptr;
//            if (leaf->first != nullptr) leaf->first->parent = leaf;
//        }
//    }
//    return parent;
//}
//
//
//TwoThreeNode* merge(TwoThreeNode* leaf) {
//	TwoThreeNode* parent = leaf->parent;
//
//	if (parent->first == leaf) {
//		parent->second->insert_to_node(parent->key[0]);
//		parent->second->third = parent->second->second;
//		parent->second->second = parent->second->first;
//
//		if (leaf->first != nullptr) parent->second->first = leaf->first;
//		else if (leaf->second != nullptr) parent->second->first = leaf->second;
//
//		if (parent->second->first != nullptr) parent->second->first->parent = parent->second;
//
//		parent->remove_from_node(parent->key[0]);
//		delete parent->first;
//		parent->first = nullptr;
//	}
//	else if (parent->second == leaf) {
//		parent->first->insert_to_node(parent->key[0]);
//
//		if (leaf->first != nullptr) parent->first->third = leaf->first;
//		else if (leaf->second != nullptr) parent->first->third = leaf->second;
//
//		if (parent->first->third != nullptr) parent->first->third->parent = parent->first;
//
//		parent->remove_from_node(parent->key[0]);
//		delete parent->second;
//		parent->second = nullptr;
//	}
//
//	if (parent->parent == nullptr) {
//		TwoThreeNode* tmp = nullptr;
//		if (parent->first != nullptr) tmp = parent->first;
//		else tmp = parent->second;
//		tmp->parent = nullptr;
//		delete parent;
//		return tmp;
//	}
//	return parent;
//}
//
//TwoThreeNode* fix(TwoThreeNode* leaf) {
//	if (leaf->size == 0 && leaf->parent == nullptr) { // ������ 0, ����� ������� ������������ ���� � ������
//		delete leaf;
//		return nullptr;
//	}
//	if (leaf->size != 0) { // ������ 1, ����� �������, � ������� ������� ����, ����� ��� �����
//		if (leaf->parent) return fix(leaf->parent);
//		else return leaf;
//	}
//
//	TwoThreeNode* parent = leaf->parent;
//	if (parent->first->size == 2 || parent->second->size == 2 || parent->size == 2) leaf = redistribute(leaf); // ������ 2, ����� ���������� ���������������� ����� � ������
//	else if (parent->size == 2 && parent->third->size == 2) leaf = redistribute(leaf); // ����������
//	else leaf = merge(leaf); // ������ 3, ����� ����� ���������� ���������� � �������� ����� �� ������ ��� ������� �� ��� ���� �������
//
//	return fix(leaf);
//}
//
//TwoThreeNode* search_min(TwoThreeNode* p) { // ����� ���� � ����������� ��������� � 2-3-������ � ������ p.
//	if (!p) return p;
//	if (!(p->first)) return p;
//	else return search_min(p->first);
//}
//
////TwoThreeNode* remove(TwoThreeNode* p, int k) { // �������� ����� k � 2-3-������ � ������ p.
////	TwoThreeNode* item = search(p, k); // ���� ����, ��� ��������� ���� k
////
////	if (!item) return p;
////
////	TwoThreeNode* min = nullptr;
////	if (item->key[0] == k) min = search_min(item->second); // ���� ������������� ����
////	else min = search_min(item->third);
////
////	if (min) { // ������ ����� �������
////		int& z = (k == item->key[0] ? item->key[0] : item->key[1]);
////		item->swap(z, min->key[0]);
////		item = min; // ���������� ��������� �� ����, �.�. min - ������ ����
////	}
////
////	item->remove_from_node(k); // � ������� ��������� ���� �� �����
////	return fix(item); // �������� ������� ��� �������������� ������� ������.
////}
//
//void removeAll(TwoThreeNode* p)
//{
//    if (p != nullptr)
//    {
//        removeAll(p->first);
//        removeAll(p->second);
//        removeAll(p->third);
//        delete(p);
//    }
//}
//
//TwoThreeNode* insert(TwoThreeNode* p, int k) { // ������� ����� k � ������ � ������ p; ������ ���������� ������ ������, �.�. �� ����� ��������
//	if (!p) 
//		return new TwoThreeNode(k); // ���� ������ �����, �� ������� ������ 2-3-������� (������)
//
//	if (p->is_leaf()) // ���� ����, �� ���������
//		p->insert_to_node(k);
//
//	else if (k <= p->key[0]) // ����������, � ����� ��������� ��������� ����
//		insert(p->first, k);
//
//	else if ((p->size == 1) || ((p->size == 2) && k <= p->key[1])) 
//		insert(p->second, k);
//
//	else 
//		insert(p->third, k);
//
//	if(p->size > 2)
//	{
//		//TwoThreeNode(key, first, second, third, fourth, parent)
//		//TwoThreeNode* left = new TwoThreeNode(p->key[0], p->first, p->second, nullptr, nullptr, p->parent); // ������� ��� ����� �������,
//		//TwoThreeNode* right = new TwoThreeNode(p->key[2], p->third, p->fourth, nullptr, nullptr, p->parent);  // ������� ����� ������ �� ��������, ��� � ������������� �������.
//
//		//TwoThreeNode(key, first, second, third, parent)
//		TwoThreeNode* left = new TwoThreeNode(p->key[0], p->first, nullptr, nullptr, p->parent);
//		TwoThreeNode* right = new TwoThreeNode(p->key[2], p->third, nullptr, nullptr, p->parent);
//
//		if (left->first)
//			left->first->parent = left;
//
//		if (left->second)
//			left->second->parent = left;   // ���� � ���� � 3�� ������� ���� �������, �� ������ �� ��������� 
//
//		if (right->first)
//			right->first->parent = right;
//
//		if (right->second)
//			right->second->parent = right;
//
//		if (p->parent) {
//			p->parent->insert_to_node(p->key[1]); // ��������� � �������� ������� �� �������� ����
//
//			if (p->parent->first == p)
//				p->parent->first = nullptr;
//			else if (p->parent->second == p) // ���������� ���� �� ������
//				p->parent->second = nullptr;
//			else if (p->parent->third == p)
//				p->parent->third = nullptr;
//
//			// ���������� �������� � ����������� �� ����, ������ ������� ��������� �� ���������
//			if (p->parent->first == nullptr) {
//				//p->parent->fourth = p->parent->third; // ���� fourth, third �������� ���������� ��������, ������ � item->parent 3 �����
//				p->parent->third = p->parent->second;
//				p->parent->second = right; // ������� ������� ��������� � ������� ������
//				p->parent->first = left;  // ������� ������� ��������� � ������� ������
//			}
//			else if (p->parent->second == nullptr) {
//				//p->parent->fourth = p->parent->third;
//				p->parent->second = left;  // ���� fourth, third �������� ���������� ��������, ������ � item->parent 3 �����
//				p->parent->third = right;
//			}
//			else {
//				//p->parent->fourth = right;
//				p->parent->third = left;
//			}
//
//			TwoThreeNode* tmp = p->parent;
//			delete p; // ������� ���� ������� ���������
//			return tmp;
//		}
//		else {
//			left->parent = p;   // ��� ��� � ��� ����� �������� ������ ������,
//			right->parent = p;   // �� �� "���������" ����� ������ ������ ������������� �������.
//			p->become_node2(p->key[1], left, right);
//			return p;
//		}
//	}
//
//	//return split(p);
//}
//
////TwoThreeNode* split(TwoThreeNode* p) {
////	if (p->size < 3) 
////		return p;
////						//TwoThreeNode(key, first, second, third, fourth, parent)
////	TwoThreeNode* x = new TwoThreeNode(p->key[0], p->first, p->second, nullptr, nullptr, p->parent); // ������� ��� ����� �������,
////	TwoThreeNode* y = new TwoThreeNode(p->key[2], p->third, p->fourth, nullptr, nullptr, p->parent);  // ������� ����� ������ �� ��������, ��� � ������������� �������.
////	
////	if (x->first)  
////		x->first->parent = x;    
////
////	if (x->second) 
////		x->second->parent = x;   // ���� � ���� � 3�� ������� ���� �������, �� ������ �� ��������� 
////
////	if (y->first)  
////		y->first->parent = y;    
////
////	if (y->second) 
////		y->second->parent = y;
////
////	if (p->parent) {
////		p->parent->insert_to_node(p->key[1]); // ��������� � �������� ������� �� �������� ����
////
////		if (p->parent->first == p) 
////			p->parent->first = nullptr;
////		else if (p->parent->second == p) // ���������� ���� �� ������
////			p->parent->second = nullptr;
////		else if (p->parent->third == p) 
////			p->parent->third = nullptr;
////
////		// ���������� �������� � ����������� �� ����, ������ ������� ��������� �� ���������
////		if (p->parent->first == nullptr) {
////			p->parent->fourth = p->parent->third; // ���� fourth, third �������� ���������� ��������, ������ � item->parent 3 �����
////			p->parent->third = p->parent->second;
////			p->parent->second = y; // ������� ������� ��������� � ������� ������
////			p->parent->first = x;  // ������� ������� ��������� � ������� ������
////		}
////		else if (p->parent->second == nullptr) {
////			p->parent->fourth = p->parent->third;
////			p->parent->second = x;  // ���� fourth, third �������� ���������� ��������, ������ � item->parent 3 �����
////			p->parent->third = y;
////		}
////		else { 
////			p->parent->fourth = y;
////			p->parent->third = x;
////		}
////
////		TwoThreeNode* tmp = p->parent;
////		delete p; // ������� ���� ������� ���������
////		return tmp;
////	}
////	else {
////		x->parent = p;   // ��� ��� � ��� ����� �������� ������ ������,
////		y->parent = p;   // �� �� "���������" ����� ������ ������ ������������� �������.
////		p->become_node2(p->key[1], x, y);
////		return p;
////	}
////}
////
////TwoThreeNode* search(TwoThreeNode* p, int k) { // ����� ����� k � 2-3 ������ � ������ p.
////	if (!p) 
////		return nullptr;
////
////	if (p->find(k)) 
////		return p;
////	else if (k < p->key[0]) 
////		return search(p->first, k);
////	else if ((p->size == 2) && (k < p->key[1]) || (p->size == 1)) 
////		return search(p->second, k);
////	else if (p->size == 2) 
////		return search(p->third, k);
////}
