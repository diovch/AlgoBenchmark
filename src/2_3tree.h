#pragma once 
#include <vector>

namespace tree2_3 
{
	// класс с ключом и частотой 
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

	// класс узла дерева с 2мя полями FrequncyField, 3мя потомками в максимуме
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
			// Если лист(нет потомков), то добавить в текущий узел
			if (this->isLeaf())
				this->add(new_node);

				// Потомки есть
			else if (new_node->nodeData[0].key > this->nodeData.back().key) // Ключ вставки больше самого большого ключа в узле
				this->children.back()->insert(new_node);  // Рекурсивно вливаем ключ в больший узел
			else
			{
				for(int i = 0; i < this->nodeData.size(); i++)
					if (new_node->nodeData[0].key < this->nodeData[i].key)  // ключей в узле либо 1, либо 2
					{
						this->children[i]->insert(new_node);  // определяем в каком поддереве искать место вставки
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
			// Пытаемся влить новый ключ в узел
			for (auto& child : new_node->children)  // Если у узла есть дети
				child->parent = this;  // то меняем их родителя на тот узел, в который пытаемся добавить

			this->nodeData.push_back(FrequncyField<T>(new_node->nodeData[0].key));  //  Добавляем ключ в узел
			std::sort(this->nodeData.begin(), this->nodeData.end());  //  Сортируем ключи в узле
			
			for (auto& child : new_node->children)
				this->children.push_back(child); // Добавляем родителю новых детей
			
			if (this->children.size() > 1)
				std::sort(this->children.begin(), this->children.end(), 
					[](Node<T>* lhs, Node<T>* rhs) {return lhs->nodeData[0] < rhs->nodeData[0]; });  // Если потомков несколько, то отсортируем их по первым ключам

			if (this->nodeData.size() > 2)  //  Если в узел добавили 3й ключ, то разделяем узел на дерево
				this->split();
		}

		// 3 ключа в узле, разделяем на поддерево и новый корень
		void split()
		{
			auto left_child = new Node<T>(this->nodeData[0].key);  // создаем узел с ключом data[0] - меньший ключ
			auto right_child = new Node<T>(this->nodeData[2].key);   // создаем узел с ключом data[2] - больший ключ
			
			if (this->children.size() != 0)  // Если у узла с 3 ключами есть потомки, то их стало 4 штуки в функции add
			{
				this->children[0]->parent = left_child;  // у первых двух потомков родитель будет с меньшим узлом
				this->children[1]->parent = left_child;
				this->children[2]->parent = right_child;  // у двух последних родитель будет с большим узлом
				this->children[3]->parent = right_child;

				left_child->children.push_back(this->children[0]);  // то же самое,
				left_child->children.push_back(this->children[1]);
				
				right_child->children.push_back(this->children[2]);  // только относительно родителей
				right_child->children.push_back(this->children[3]);
			}

			// Разделение узла с 3 ключами на дерево
			this->children = std::vector<Node<T>*>{ left_child }; // определяем для узла левого потомка
			this->children.push_back(right_child);  // определяем для узла правого(> левого) потомка
			this->nodeData = std::vector<FrequncyField<T>>{ FrequncyField<T>(this->nodeData[1].key) }; // средний по величине ключ становится НОВЫМ корнем(но узел тот же в памяти)

			
			// Теперь у нас есть разделенное поддерево вместо одного узла
			if (this->parent)  // Если у разделенного поддерева есть родитель
			{
				for (int i = 0; i < this->parent->children.size(); i++)
				{
					if (this->parent->children[i] == this)  // то удаляем у него потомка, который стал новым корнем
					{
						auto toRemoveIt = this->parent->children.begin() + i;  
						this->parent->children.erase(toRemoveIt);

						this->parent->add(this);  // Добавляем новый корень к родителю
						break;
					}
				}
			}
			else
			{
				left_child->parent = this;  // Определяем корень у опустившихся узлов
				right_child->parent = this;
			}
		}

		FrequncyField<T>* find(T& _key)
		{
			for (int i = 0; i < this->nodeData.size(); i++)
				if (this->nodeData[i].key == _key)
					return &this->nodeData[i];  // в этом узле есть наш ключ


			if (this->isLeaf()) // Если лист, то искать больше негде
				return NULL;
			else if (_key > this->nodeData.back().key) // Ключ вставки больше самого большого ключа в узле
				return this->children.back()->find(_key); // ищем в последнем потомке
			else
			{
				for (int i = 0; i < this->nodeData.size(); i++)
					if (_key < this->nodeData[i].key)  // ключей в узле либо 1, либо 2
						return this->children[i]->find(_key);  // определяем в каком поддереве искать ключ
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
						if (this->parent->children[i] == this)  // то удаляем у него потомка, который стал новым корнем
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
				root = new Node<T>(_key);  // Создаем корень
			else
			{
				auto new_node = new Node<T>(_key);
				root->insert(new_node);
				delete new_node; // тут дерево уже изменено
				
				while (this->root->parent)
					this->root = this->root->parent; // у дерева как целого изменился корень
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