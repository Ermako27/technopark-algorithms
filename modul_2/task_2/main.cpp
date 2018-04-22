/*

Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
Требуется построить бинарное дерево, заданное наивным порядком вставки.
Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
Рекурсия запрещена.

2_1. Выведите элементы в порядке in-order (слева направо).

*/


#include <iostream>
#include <stack>
#include <vector>

using namespace std;

template<typename T>
class Btree
{
public:

	Btree();
	~Btree();
	void insert(T elem);
	vector<T> inOrder();

private:

	struct TreeNode{
		explicit TreeNode(T elem) : value(elem) {}
		T value;
		TreeNode *right = nullptr;
		TreeNode *left = nullptr;
	};

	TreeNode *root = nullptr;

};


template<typename T>
Btree<T>::Btree() {}

template<typename T>
Btree<T>::~Btree(){
    vector<TreeNode*> result;

    TreeNode* currentLeaf = root;
    stack<TreeNode*> tmp;
    while (currentLeaf != nullptr || !tmp.empty()) {
        if (currentLeaf != nullptr) {
            tmp.push(currentLeaf);
            currentLeaf = currentLeaf->left;
        } 
        else {
            currentLeaf = tmp.top();
            tmp.pop();
            result.push_back(currentLeaf);
            currentLeaf = currentLeaf->right;
        }
    }

    for (TreeNode* x : result){
    	delete x;
    }
}


template<typename T>
void Btree<T>::insert(T elem){
	bool done = false;
	if( root == nullptr) {
		root = new TreeNode( elem );
	}
	else {
		TreeNode *currentLeaf = root;
		while ( !done ){
			if (elem >= currentLeaf->value){
				if (currentLeaf->right == nullptr){
					currentLeaf->right = new TreeNode(elem);
					done = true;
				}
				else{
					currentLeaf = currentLeaf->right;
				}
			}
			else{
				if (currentLeaf->left == nullptr){
					currentLeaf->left = new TreeNode(elem);
					done = true;
				}
				else{
					currentLeaf = currentLeaf->left;
				}
			}
		}
	}
}

template<typename T>
vector<T> Btree<T>::inOrder(){
    vector<T> result;
    TreeNode* currentLeaf = root;
    stack<TreeNode*> tmp;
    while (currentLeaf != nullptr || !tmp.empty()) {
        if (currentLeaf != nullptr) {
            tmp.push(currentLeaf);
            currentLeaf = currentLeaf->left;
        } 
        else {
            currentLeaf = tmp.top();
            tmp.pop();
            result.push_back(currentLeaf->value);
            currentLeaf = currentLeaf->right;
        }
    }
    return result;
}


int main()
{
	int n;
	cin >> n;
	int elem;
	
	Btree<int> tree;
	for (int i = 0; i < n; i++){
		cin >> elem;
		tree.insert(elem);
	}

	vector<int> node = tree.inOrder();
	for (int x : node){
		cout << x << " ";
	}

	return 0;
}

