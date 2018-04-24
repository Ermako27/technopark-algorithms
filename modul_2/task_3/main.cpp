#include <iostream>
#include <stack>
#include <vector>
#include <queue>

using namespace std;

template<typename T>
class Btree
{
public:

	Btree();
	~Btree();
	void insert(T elem);
	int getDeep();

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
    while (currentLeaf != nullptr || !tmp.empty()){
        if (currentLeaf != nullptr){
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
int Btree<T>::getDeep(){
    if (root == nullptr){
        return 0;
    }
    int maxDeep = 1;
    queue<pair<TreeNode*, int>> treeQ;

    treeQ.push(make_pair(root, 1));

    while (!treeQ.empty()){
        pair<TreeNode*, int> t = treeQ.front();
        TreeNode* currentLeaf = t.first;
        int currentDeep = t.second;	
        treeQ.pop();
        if (maxDeep < currentDeep)
            maxDeep = currentDeep;
        if (currentLeaf->left != nullptr){
        	// currentDeep += 1;
            treeQ.push(make_pair(currentLeaf->left, currentDeep + 1));
        }
        if (currentLeaf->right != nullptr){
        	// currentDeep += 1;
            treeQ.push(make_pair(currentLeaf->right, currentDeep + 1));
        }
    }

    return maxDeep;
}

//////////////////////////////////////   ДЕКАРТОВО ДЕРЕВО ////////////////////////////////////

template<typename T, typename K>
class Dtree
{
public:

	Dtree();
	// ~Dtree();
	void insert(T x, K y);
	int getDeep();

private:

	struct DecTreeNode{
		explicit DecTreeNode(T x, K y) : key(x), priority(y) {}
		T key;
		K priority;
		DecTreeNode *right = nullptr;
		DecTreeNode *left = nullptr;
	};

	void split(DecTreeNode *currentLeaf, DecTreeNode *&l, 
			DecTreeNode *&r, T key);

	DecTreeNode *root = nullptr;

};

template<typename T, typename K>
Dtree<T, K>::Dtree() {}

template<typename T, typename K>
void Dtree<T, K>::split(DecTreeNode *currentLeaf, DecTreeNode *&l, DecTreeNode *&r, T x){
	if (currentLeaf == nullptr){
		l = nullptr;
		r = nullptr;
	}
	else if (currentLeaf->key <= x){
		split(currentLeaf->right, currentLeaf->right, r, x);
		l = currentLeaf;
	}
	else{
		split(currentLeaf->left, l, currentLeaf->left, x);
		r = currentLeaf;
	}

}

// template<typename T, typename K>
// void Dtree<T, K>::insert(T x, K y){
// 	bool left_flag = false;
// 	bool right_flag = false;
// 	// cout << "1" << "\n";
// 	DecTreeNode *currentLeafParrent = nullptr;
// 	// cout << "2" << "\n";
// 	if (root == nullptr){
// 		root = new DecTreeNode(x, y);
// 		// cout << "3" << "\n";
// 	}
// 	else{
// 		DecTreeNode *currentLeafParrent = nullptr;
// 		DecTreeNode *newLeaf = new DecTreeNode(x, y);
// 		// cout << "4" << "\n";
// 		DecTreeNode *currentLeaf = root;
// 		// cout << "5" << "\n";
// 		while (true){
// 			if (currentLeaf == nullptr)
// 				break;

// 			if (currentLeaf->priority < y)
// 				break;


// 			// cout << "6" << "\n";
// 			// cout << "priority: " << currentLeaf->priority << "y " << y << "\n";
// 			// cout << "key: " << currentLeaf->key << "x " << x << "\n";
// 			if (x >= currentLeaf->key){
// 				// cout << "12" << "\n";
// 				currentLeafParrent = currentLeaf;
// 				// cout << "13" << "\n";
// 				currentLeaf = currentLeaf->right;
// 				// cout << "14" << "\n";
// 				right_flag = true;
// 				left_flag = false;
				
// 			}
// 			else{
// 				// cout << "20" << "\n";
// 				currentLeafParrent = currentLeaf;
// 				// cout << "21" << "\n";
// 				currentLeaf = currentLeaf->left;
// 				// cout << "22" << "\n";
// 				left_flag = true;
// 				right_flag = false;
// 			}
// 		}

// 		if (left_flag){
// 			// cout << "16" << "\n";
// 			// вставляем
// 			cout << "\n--------------------------\nleft\n";
// 			cout << "priority: " << newLeaf->priority << " y " << y << "\n";
// 			cout << "key: " << newLeaf->key << " x " << x << "\n";
// 			split(currentLeaf, newLeaf->left, newLeaf->right, x);
// 			// cout << "17" << "\n";
// 			currentLeafParrent->left = newLeaf;
// 			// cout << "18" << "\n";

// 		}
// 		if (right_flag){
// 			// вставляем
// 			// cout << "8" << "\n";
// 			cout << "\n--------------------------\nright\n";
// 			cout << "priority: " << newLeaf->priority << " y " << y << "\n";
// 			cout << "key: " << newLeaf->key << " x " << x << "\n";
// 			split(currentLeaf, newLeaf->left, newLeaf->right, x);
// 			// cout << "9" << "\n";
// 			currentLeafParrent->right = newLeaf;
// 			// cout << "10" << "\n";
// 		}
// 	}	
// }


template<typename T, typename K>
void Dtree<T, K>::insert(T x, K y) {
    if (root == nullptr) {
        root = new DecTreeNode(x, y);
    } else {
        DecTreeNode *currentLeafParent = nullptr;
        DecTreeNode* newLeaf = new DecTreeNode(x, y); // узел который хотим вставить
        bool is_left = false;
        bool is_right = false;
        DecTreeNode *currentLeaf = root;
        while (true) {
            if (currentLeaf == nullptr){
                break;
            }
            if (currentLeaf->priority < y){
                break;
            }
            if (x >= currentLeaf->key){
                currentLeafParent = currentLeaf;
                is_left = false;
                is_right = true;
                currentLeaf = currentLeaf->right;
            } 
            else{
                currentLeafParent = currentLeaf;
                is_left = true;
                is_right = false;
                currentLeaf = currentLeaf->left;
            }
        }

        split(currentLeaf, newLeaf->left, newLeaf->right, x);
        if (currentLeafParent){
            if (is_left) {
                // cout << "\n--------------------------\nleft\n";
                // cout << "priority: " << newLeaf->priority << " y " << y << "\n";
                // cout << "key: " << newLeaf->key << " x " << x << "\n";
                currentLeafParent->left = newLeaf;
            } 
            if (is_right){
                // cout << "\n--------------------------\nright\n";
                // cout << "priority: " << newLeaf->priority << " y " << y << "\n";
                // cout << "key: " << newLeaf->key << " x " << x << "\n";
                currentLeafParent->right = newLeaf;
            }
        } 
        else{
            root = newLeaf;
        }
    }
}


// template<typename T, typename K>
// void Dtree<T, K>::insert(T x, K y){
// 	bool left_flag = false;
// 	bool right_flag = false;
// 	if (root == nullptr){
// 		root = new DecTreeNode(x, y);
// 	}
// 	else{
// 		DecTreeNode *currentLeafParrent = nullptr;
// 		DecTreeNode *newLeaf = new DecTreeNode(x, y);
// 		DecTreeNode *currentLeaf = root;
// 		while (true){
// 			if (currentLeaf == nullptr)
// 				break;

// 			if (currentLeaf->priority < y)
// 				break;

// 			if (x >= currentLeaf->key){
// 				currentLeafParrent = currentLeaf;
// 				currentLeaf = currentLeaf->right;
// 				right_flag = true;
// 				left_flag = false;
				
// 			}
// 			else{
// 				currentLeafParrent = currentLeaf;
// 				currentLeaf = currentLeaf->left;
// 				left_flag = true;
// 				right_flag = false;
// 			}
// 		}

// 		if (currentLeafParrent){
// 			if (left_flag){
// 				split(currentLeaf, newLeaf->left, newLeaf->right, x);
// 				currentLeafParrent->left = newLeaf;
// 			}
// 			if (right_flag){
// 				split(currentLeaf, newLeaf->left, newLeaf->right, x);
// 				currentLeafParrent->right = newLeaf;
// 			}	
// 		}
// 		else{
// 			root = newLeaf;
// 		}
// 		// if (left_flag){
// 		// 	split(currentLeaf, newLeaf->left, newLeaf->right, x);
// 		// 	currentLeafParrent->left = newLeaf;
// 		// }
// 		// if (right_flag){
// 		// 	split(currentLeaf, newLeaf->left, newLeaf->right, x);
// 		// 	currentLeafParrent->right = newLeaf;
// 		// }
// 	}	
// }

template<typename T, typename K>
int Dtree<T, K>::getDeep(){
    if (root == nullptr){
        return 0;
    }

    int maxDeep = 1;
    queue<pair<DecTreeNode*, int>> treeQ;

    treeQ.push(make_pair(root, 1));

    while (!treeQ.empty()){
        pair<DecTreeNode*, int> t = treeQ.front();
        DecTreeNode* currentLeaf = t.first;
        int currentDeep = t.second;
        treeQ.pop();
        if (maxDeep < currentDeep)
            maxDeep = currentDeep;
        if (currentLeaf->left != nullptr){
        	// currentDeep += 1;
            treeQ.push(make_pair(currentLeaf->left, currentDeep + 1));
        }
        if (currentLeaf->right != nullptr){
        	// currentDeep += 1;
            treeQ.push(make_pair(currentLeaf->right, currentDeep + 1));
        }
    }

    return maxDeep;
}



int main() {
	int x, y;
	int result = 0;
    int n;
    cin >> n;

    Btree<int> bt;
    Dtree<int, int> dt;
    for (int i = 0; i < n; i++) {
        cin >> x;
        cin >> y;
        dt.insert(x, y);
        bt.insert(x);
    }

    result = bt.getDeep() - dt.getDeep();
    cout << result << endl;

    return 0;
}