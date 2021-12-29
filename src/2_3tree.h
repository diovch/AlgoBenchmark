#pragma once 
#include <vector>

namespace tree2_3 
{
	// ����� � ������ � �������� 
	template<class T>
	class FrequncyField
	{
	public:
		FrequncyField(T& _key) : key(_key), frequency(1) {}
		FrequncyField<T>(T& _key, int _frequency) : key(_key), frequency(_frequency) {}

		bool operator<(FrequncyField& rhs) { return this->key < rhs.key; }
		bool operator==(FrequncyField& rhs) { return this->key == rhs.key; }

	public:
		T key;
		int frequency;
	};

	// ����� ���� ������ � 2�� ������ FrequncyField, 3�� ��������� � ���������
	template<class T>
	class Node
	{
	public:

		Node(T& _key): parent(NULL)
		{
			nodeData.push_back(FrequncyField<T>(_key, 1)); // 
		}

		void insert(Node* new_node)
		{
			// ���� ����(��� ��������), �� �������� � ������� ����
			if (this->isLeaf())
				this->add(new_node);

				// ������� ����
			else if (new_node->nodeData[0].key > this->nodeData.back().key) // ���� ������� ������ ������ �������� ����� � ����
				this->children.back()->insert(new_node);  // ���������� ������� ���� � ������� ����
			else
			{
				for(int i = 0; i < this->nodeData.size(); i++)
					if (new_node->nodeData[0].key < this->nodeData[i].key)  // ������ � ���� ���� 1, ���� 2
					{
						this->children[i]->insert(new_node);  // ���������� � ����� ��������� ������ ����� �������
						break;
					}
			}
		}

		bool isLeaf()
		{
			return children.size() == 0;
		}

		void add(Node* new_node)
		{
			// �������� ����� ����� ���� � ����
			for (auto& child : new_node->children)  // ���� � ���� ���� ����
				child->parent = this;  // �� ������ �� �������� �� ��� ����, � ������� �������� ��������

			this->nodeData.push_back(FrequncyField<T>(new_node->nodeData[0].key));  //  ��������� ���� � ����
			std::sort(this->nodeData.begin(), this->nodeData.end());  //  ��������� ����� � ����
			
			for (auto& child : new_node->children)
				this->children.push_back(child); // ��������� �������� ����� �����
			
			if (this->children.size() > 1)
				std::sort(this->children.begin(), this->children.end(), 
					[](Node<T>* lhs, Node<T>* rhs) {return lhs->nodeData[0] < rhs->nodeData[0]; });  // ���� �������� ���������, �� ����������� �� �� ������ ������

			if (this->nodeData.size() > 2)  //  ���� � ���� �������� 3� ����, �� ��������� ���� �� ������
				this->split();
		}

		// 3 ����� � ����, ��������� �� ��������� � ����� ������
		void split()
		{
			auto left_child = new Node<T>(this->nodeData[0].key);  // ������� ���� � ������ data[0] - ������� ����
			auto right_child = new Node<T>(this->nodeData[2].key);   // ������� ���� � ������ data[2] - ������� ����
			
			if (this->children.size() != 0)  // ���� � ���� � 3 ������� ���� �������, �� �� ����� 4 ����� � ������� add
			{
				this->children[0]->parent = left_child;  // � ������ ���� �������� �������� ����� � ������� �����
				this->children[1]->parent = left_child;
				this->children[2]->parent = right_child;  // � ���� ��������� �������� ����� � ������� �����
				this->children[3]->parent = right_child;

				left_child->children.push_back(this->children[0]);  // �� �� �����,
				left_child->children.push_back(this->children[1]);
				
				right_child->children.push_back(this->children[2]);  // ������ ������������ ���������
				right_child->children.push_back(this->children[3]);
			}

			// ���������� ���� � 3 ������� �� ������
			this->children = std::vector<Node<T>*>{ left_child }; // ���������� ��� ���� ������ �������
			this->children.push_back(right_child);  // ���������� ��� ���� �������(> ������) �������
			this->nodeData = std::vector<FrequncyField<T>>{ FrequncyField<T>(this->nodeData[1].key) }; // ������� �� �������� ���� ���������� ����� ������(�� ���� ��� �� � ������)

			
			// ������ � ��� ���� ����������� ��������� ������ ������ ����
			if (this->parent)  // ���� � ������������ ��������� ���� ��������
			{
				for (int i = 0; i < this->parent->children.size(); i++)
				{
					if (this->parent->children[i] == this)  // �� ������� � ���� �������, ������� ���� ����� ������
					{
						auto toRemoveIt = this->parent->children.begin() + i;  
						this->parent->children.erase(toRemoveIt);

						this->parent->add(this);  // ��������� ����� ������ � ��������
						break;
					}
				}
			}
			else
			{
				left_child->parent = this;  // ���������� ������ � ������������ �����
				right_child->parent = this;
			}
		}

		FrequncyField<T>* find(T& _key)
		{
			for (int i = 0; i < this->nodeData.size(); i++)
				if (this->nodeData[i].key == _key)
					return &this->nodeData[i];  // � ���� ���� ���� ��� ����


			if (this->isLeaf()) // ���� ����, �� ������ ������ �����
				return NULL;
			else if (_key > this->nodeData.back().key) // ���� ������� ������ ������ �������� ����� � ����
				return this->children.back()->find(_key); // ���� � ��������� �������
			else
			{
				for (int i = 0; i < this->nodeData.size(); i++)
					if (_key < this->nodeData[i].key)  // ������ � ���� ���� 1, ���� 2
						return this->children[i]->find(_key);  // ���������� � ����� ��������� ������ ����
			}
		}

		void destroy()
		{
			if (this->isLeaf())
			{
				if (this->parent)
				{
					for (int i = 0; i < this->parent->children.size(); i++)
					{
						if (this->parent->children[i] == this)  // �� ������� � ���� �������, ������� ���� ����� ������
						{
							auto toRemoveIt = this->parent->children.begin() + i;
							this->parent->children.erase(toRemoveIt);
							break;
						}
					}
				}
				delete this;
			}
			else
			{
				std::vector<Node<T>*> tempChildren = this->children;
				for (auto child : tempChildren)
				{
					child->destroy();
				}
				this->destroy();
			}

		}

	public:
		std::vector<FrequncyField<T>> nodeData;
		std::vector<Node<T>*> children;
		Node<T>* parent;
	};

	template<class T>
	class Tree
	{
	public:
		Tree(): root(NULL){ }
		
		bool insert(T& _key)
		{
			if (root == NULL)
				root = new Node<T>(_key);  // ������� ������
			else
			{
				auto new_node = new Node<T>(_key);
				root->insert(new_node);
				delete new_node; // ��� ������ ��� ��������
				
				while (this->root->parent)
					this->root = this->root->parent; // � ������ ��� ������ ��������� ������
			}

			return true;
		}

		FrequncyField<T>* find(T& _key)
		{
			if (root)
				return root->find(_key);
			else
				return NULL;
		}

		~Tree()
		{
			if (root)
			{
				root->destroy();
				root = NULL;
			}
		}

	private:
		Node<T>* root;
	};

}