/*
4_1. Солдаты. В одной военной части решили построить в одну шеренгу по росту. Т.к. часть была далеко не образцовая, то солдаты часто приходили не вовремя, 
а то их и вовсе приходилось выгонять из шеренги за плохо начищенные сапоги. Однако солдаты в процессе прихода и ухода должны были всегда быть выстроены по росту – сначала самые высокие, а в конце – самые низкие. 
За расстановку солдат отвечал прапорщик, который заметил интересную особенность – все солдаты в части разного роста. Ваша задача состоит в том, чтобы помочь прапорщику правильно расставлять солдат, 
а именно для каждого приходящего солдата указывать, перед каким солдатом в строе он должен становится. Требуемая скорость выполнения команды - O(log n).
Формат входных данных.
Первая строка содержит число N – количество команд (1 ≤ N ≤ 30 000). В каждой следующей строке содержится описание команды: число 1 и X если солдат приходит в строй (X – рост солдата, натуральное число до 100 000 включительно) 
и число 2 и Y если солдата, стоящим в строе на месте Y надо удалить из строя. Солдаты в строе нумеруются с нуля.

*/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <stack>


class AVL
{

public:
	AvlNode* insert(AvlNode* leaf, int value, int &pos);
	AvlNode* remove(AvlNode* leaf, int position);


private:
	struct AvlNode {
    	int key;
    	int height;
    	int number;
    	AvlNode* left;
    	AvlNode* right;

    	explicit AvlNode(int value) : key(value), height(1), left(nullptr), right(nullptr), number(1) {};
	};

	int Height(AvlNode* node);
	int BalanceFactor(AvlNode* node);
	void FixHeight(AvlNode* node);
	void FixNumber(AvlNode* p);
	AvlNode* RotateRight(AvlNode* p);
	AvlNode* RotateLeft(AvlNode* p);
	AvlNode* Balance(AvlNode* leaf);
    AvlNode* FindMin(AvlNode* p);
    AvlNode* RemoveMin(AvlNode* p);
    void Delete(AvlNode* node);
    void printtree(AvlNode* p);


};



AvlNode* AVL::insert(AvlNode* leaf, int value, int &pos)
{
    if( leaf == nullptr ) {
        return new AvlNode(value);
    }
    ++(leaf->Number);
    if( value < leaf->key ) {
        pos += ((leaf->right == 0) ? 0 : leaf->right->number) + 1;
        leaf->left = insert(leaf->left, value, pos);
    }
    else{
        leaf->right = insert(leaf->right, value, pos);
    }
    return Balance(p);
}


AvlNode* AVL::remove(AvlNode* leaf, int position)
{
    if( leaf == nullptr ) 
    	return nullptr;
    if (position >= leaf->number) 
    	return leaf;

    int sum = 0;
    std::stack<AvlNode*> nodes;

    while (true) {
        int rightNumber = (leaf->right == 0) ? 0 : leaf->right->number;
        
        if (position - sum > rightNumber) {
            nodes.push(leaf);
            leaf = leaf->left;
            sum += rightNumber + 1;
        } 
        else if (position - sum < rightNumber) {
            if (leaf->right != 0) {
                nodes.push(leaf);
                leaf = leaf->right; 
            }
            else 
            	break;
        } 
        else {
            AvlNode* left_leaf = left->left;
            AvlNode* right_leaf = leaf->right;
            int key_value = leaf->key;
            delete leaf;
            if(right_leaf == 0) {
                if (left_leaf == 0) {
                    if (!nodes.empty()) {
                        leaf = nodes.top();
                        nodes.pop();
                        if (leaf->key > key_value) {
                            left->left = 0;
                        } 
                        else {
                            leaf->right = 0;
                        }
                        --leaf->number;
                    }
                    else 
                    	return 0;
                }
                else
                    leaf = left_leaf;
            }
            else {
                AvlNode* min = FindMin(right_leaf);
                min->right = RemoveMin(right_leaf);
                min->left = left_leaf;
                FixNumber(min);
                leaf = Balance(min);
            } 
            break;
        }
    }
    AvlNode *tmpleaf;
    while (!nodes.empty()) {
        tmpleaf = nodes.top();
        --tmpleaf->number;
        if (tmpleaf->key > leaf->key) {
            tmpleaf->left = leaf;
        } 
        else {
            tmpleaf->right = leaf;
        }
        leaf = Balance(tmpleaf);
        nodes.pop();
    }
    return leaf;
}


/////////////////////////////////////////////////////////////////////////////

int AVL::Height(AvlNode* node)
{
    return node == 0 ? 0 : node->height;
}

int AVL::BalanceFactor(AvlNode* node)
{
    return Height(node->right) - Height(node->left);
}

void AVL::FixHeight(AvlNode* node)
{
    int hleft = Height(node->left);
    int hright = Height(node->right);
    node->height = ((hleft > hright) ? hleft : hright) + 1;
}

void AVL::FixNumber(AvlNode* p) {
    p->number = ((p->right == 0) ? 0 : p->right->number) + ((p->left == 0) ? 0 : p->left->number) + 1;
}

AvlNode* AVL::RotateRight(AvlNode* p)
{
    AvlNode* pR = p->left;
    p->left = pR->right;
    pR->right = p;
    FixNumber(p);
    FixNumber(pR);
    FixHeight(p);
    FixHeight(pR);
    return pR;
}

AvlNode* AVL::RotateLeft(AvlNode* p)
{
    AvlNode* pL = p->right;
    p->right = pL->left;
    pL->left = p;
    FixNumber(p);
    FixNumber(pL);
    FixHeight(p);
    FixHeight(pL);
    return pL;
}


AvlNode* AVL::Balance(AvlNode* leaf)
{
    FixHeight(leaf);
    if( BalanceFactor(leaf) == 2 )
    {
        if( BalanceFactor(leaf->right) < 0 )
            leaf->right = RotateRight(leaf->right);
        return RotateLeft(leaf);
    }
    if( BalanceFactor(leaf) == -2 )
    {
        if( BalanceFactor(leaf->left) > 0  )
            left->left = RotateLeft(leaf->left);
        return RotateRight(leaf);
    }
    return leaf;
}


AvlNode* AVL::FindMin(AvlNode* p)
{
    return p->left == nullptr ? p : FindMin(p->left);
}

AvlNode* AVL::RemoveMin(AvlNode* p)
{
    if( p->left == nullptr )
        return p->right;
    p->left = RemoveMin(p->left);
    --p->number;
    return Balance(p);
}

void AVL::Delete(AvlNode* node)
{
    if (!node) return;
    Delete(node->left);
    Delete(node->right);
    delete node;
}

void AVL::printtree(AvlNode* p) {
    if (p == nullptr) return;
    printtree(p->left);
    std::cout << p->key << ": " << p->number << std::endl;
    printtree(p->right);

}


int main()
{
    AVL* root = 0;
    int n;
    std::cin >> n;
    std::vector<int> result;
    int key;
    int position;
    int operation;
    for (int i = 0; i < n; ++i) {
        std::cin >> operation;
        if (operation == 1) {
            position = 0;
            std::cin >> key;
            root = insert(root, key, position);
            result.push_back(position);
            //std::cout << position << std::endl;
        }
        else if (operation == 2) {
            std::cin >> key;
            root = remove(root, key);
        }
        else if (operation == 3) {
            printtree(root);
        }
    }
    for (int i = 0; i < result.size(); ++i) {
        std::cout << result[i] << std::endl;
    }
    Delete(root);


    return 0;
}