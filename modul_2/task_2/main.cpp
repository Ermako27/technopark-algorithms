/*

Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
Требуется построить бинарное дерево, заданное наивным порядком вставки.
Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
Рекурсия запрещена.

2_1. Выведите элементы в порядке in-order (слева направо).

*/


#include <iostream>
#include <vector>
#include <stack>

using namespace std;

template<typename T>
class Btree
{
public:

	Btree();
	~Btree();
	void insert(T elem);
	vector<T> inOrderTraverse();

private:

	struct TreeNode{
		explicit TreeNode(T elem) : value(elem) {}
		T value;
		TreeNode *right = nullptr;
		TreeNode *left = nullptr;
	};

	TreeNode *root = nullptr;

	vector<TreeNode*> _inOrderTraverse();
};


template<typename T>
Btree<T>::Btree() {}

template<typename T>
Btree<T>::~Btree(){
    vector<TreeNode*> tmp = _inOrderTraverse();
    for (TreeNode* x : tmp){
        delete x;
    }
}


template<typename T>
void Btree<T>::insert(T elem){
	if( root == nullptr) {
		root = new TreeNode( elem );
	}
	else {
		TreeNode *currentLeaf = root;
		while ( true ){
			if (elem >= currentLeaf->value){
				if (currentLeaf->right == nullptr){
					currentLeaf->right = new TreeNode(elem);
					break;
				}
				else{
					currentLeaf = currentLeaf->right;
				}
			}
			else{
				if (currentLeaf->left == nullptr){
					currentLeaf->left = new TreeNode(elem);
					break;
				}
				else{
					currentLeaf = currentLeaf->left;
				}
			}
		}
	}
}

template<typename T>
vector<typename Btree<T>::TreeNode*> Btree<T>::_inOrderTraverse(){
    vector<TreeNode*> result;

    TreeNode* currentLeaf = root;
    stack<TreeNode*> tmp;
    while (!tmp.empty() || currentLeaf != nullptr) {
        if (currentLeaf != nullptr) {
            tmp.push(currentLeaf);
            currentLeaf = currentLeaf->left;
        } else {
            currentLeaf = tmp.top();
            tmp.pop();
            result.push_back(currentLeaf);
            currentLeaf = currentLeaf->right;
        }
    }

    // for (TreeNode* x : result){
    // 	cout << x << ' ';
    // }
    return result;
}

template<typename T>
vector<T> Btree<T>::inOrderTraverse() {
    vector<T> result;

    vector<TreeNode*> tmp = _inOrderTraverse();
    // result.reserve(inOrderEntryTraverse.size());
    for (TreeNode* x : tmp) {
        result.push_back(x->value);
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

	vector<int> node = tree.inOrderTraverse();
	for (int x : node){
		cout << x << " ";
	}

	return 0;
}

