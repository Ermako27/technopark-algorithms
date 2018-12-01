// Дано число N < 106 и последовательность пар целых чисел из [-231..231] длиной N.
// Построить декартово дерево из N узлов, характеризующихся парами чисел {Xi, Yi}.
// Каждая пара чисел {Xi, Yi} определяет ключ Xi и приоритет Yi в декартовом дереве.
// Добавление узла в декартово дерево выполняйте второй версией алгоритма, рассказанного на лекции:
// При добавлении узла (x, y) выполняйте спуск по ключу до узла P с меньшим приоритетом. Затем разбейте найденное поддерево по ключу x так, чтобы в первом поддереве все ключи меньше x, а во втором больше или равны x. Получившиеся два дерева сделайте дочерними для нового узла (x, y). Новый узел вставьте на место узла P.

// Построить также наивное дерево поиска по ключам Xi методом из задачи 2.






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
void Btree<T>::insert(T elem){ // вставка в бинарное дерево
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
int Btree<T>::getDeep(){ // Глубина
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
            treeQ.push(make_pair(currentLeaf->left, currentDeep + 1));
        }
        if (currentLeaf->right != nullptr){
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