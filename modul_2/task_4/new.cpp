#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <stack>


struct AvlNode {
    AvlNode(int value) : value(value), height(1), Left(nullptr), Right(nullptr), number(1) {}
    int value;
    int height;
    int number;
    AvlNode* Left;
    AvlNode* Right;

};

int height(AvlNode* leaf)
{
    if (leaf == nullptr)
        return 0;
    else
        return leaf->height;
}

int difference(AvlNode* leaf)
{
    return height(leaf->Right) - height(leaf->Left);
}

void heightFix(AvlNode* leaf)
{
    int left_height = height(leaf->Left);
    int right_height = height(leaf->Right);
    if (left_height > right_height)
        leaf->height = left_height + 1;
    else
        leaf->height = right_height + 1;
}

void numberFix(AvlNode* leaf) {

    int left_num;
    int right_num;
    if (leaf->Right == nullptr)
        right_num = 0;
    else
        right_num = leaf->Right->number;

    if (leaf->Left == nullptr)
        left_num = 0;
    else
        left_num = leaf->Left->number;


    leaf->number = right_num + left_num;

} 


AvlNode* Right_rotate(AvlNode* leaf)
{
    AvlNode* rotateLeaf = leaf->Left;
    leaf->Left = rotateLeaf->Right;
    rotateLeaf->Right = leaf;
    numberFix(leaf);
    numberFix(rotateLeaf);
    heightFix(leaf);
    heightFix(rotateLeaf);
    return rotateLeaf;
}

AvlNode* Left_rotate(AvlNode* leaf)
{
    AvlNode* left_leaf = leaf->Right;
    leaf->Right = left_leaf->Left;
    left_leaf->Left = leaf;
    numberFix(leaf);
    numberFix(left_leaf);
    heightFix(leaf);
    heightFix(left_leaf);
    return left_leaf;
}

AvlNode* Balance(AvlNode* leaf)
{
    heightFix(leaf);
    if( difference(leaf) == 2 )
    {
        if( difference(leaf->Right) < 0 )
            leaf->Right = Right_rotate(leaf->Right);
        return Left_rotate(leaf);
    }
    if( difference(leaf) == -2 )
    {
        if( difference(leaf->Left) > 0  )
            leaf->Left = Left_rotate(leaf->Left);
        return Right_rotate(leaf);
    }
    return leaf;
}


AvlNode* minFind(AvlNode* leaf)
{
    if (leaf->Left == nullptr)
        return leaf;
    else
        return minFind(leaf->Left);
}

AvlNode* DeleteMin(AvlNode* leaf)
{
    if( leaf->Left == nullptr )
        return leaf->Right;
    leaf->Left = DeleteMin(leaf->Left);
    --leaf->number;
    return Balance(leaf);
}



AvlNode* Insert(AvlNode* leaf, int value, int &pos)
{
    if( leaf == nullptr ) {
        return new AvlNode(value);
    }
    ++(leaf->number);
    if( value < leaf->value ) {
        if (leaf->Right == nullptr)
            pos += 1;
        else
            pos += leaf->Right->number + 1;

        leaf->Left = Insert(leaf->Left, value, pos);
    }
    else{
        leaf->Right = Insert(leaf->Right, value, pos);
    }
    return Balance(leaf);
}

AvlNode* Remove(AvlNode* leaf, int position)
{
    if( leaf == nullptr ) 
        return nullptr;
    if (position >= leaf->number) 
        return leaf;
    int sum = 0;
    std::stack<AvlNode*> tmpLeaves;

    int rightnumber;
    while (true) {

        if (leaf->Right == nullptr)
            rightnumber = 0;
        else
            rightnumber = leaf->Right->number;
        
        if (position - sum > rightnumber) {
            tmpLeaves.push(leaf);
            leaf = leaf->Left;
            sum += rightnumber + 1;
        } 
        else if (position - sum < rightnumber) {
            if (leaf->Right != nullptr) {
                tmpLeaves.push(leaf);
                leaf = leaf->Right; 
            }
            else 
                break;
        } 
        else {
            AvlNode* left = leaf->Left;
            AvlNode* right = leaf->Right;
            int value = leaf->value;
            delete leaf;
            if(right == nullptr) {
                if (left == nullptr) {
                    if (!tmpLeaves.empty()) {
                        leaf = tmpLeaves.top();
                        tmpLeaves.pop();
                        if (leaf->value > value) {
                            leaf->Left = nullptr;
                        } 
                        else {
                            leaf->Right = nullptr;
                        }
                        --leaf->number;
                    }
                    else 
                        return nullptr;
                }
                else
                    leaf = left;
            }
            else {
                AvlNode* min = minFind(right);
                min->Right = DeleteMin(right);
                min->Left = left;
                numberFix(min);
                leaf = Balance(min);
            } 
            break;
        }
    }
    AvlNode *tmpLeaf;
    while (!tmpLeaves.empty()) {
        tmpLeaf = tmpLeaves.top();
        --tmpLeaf->number;
        if (tmpLeaf->value > tmpLeaf->value) {
            tmpLeaf->Left = tmpLeaf;
        } 
        else {
            tmpLeaf->Right = tmpLeaf;
        }
        leaf = Balance(tmpLeaf);
        tmpLeaves.pop();
    }
    return leaf;
}


int main()
{
    AvlNode* root = nullptr;
    int n;
    std::cin >> n;
    std::vector<int> result;
    int value;
    int position;
    int operation;

    for (int i = 0; i < n; ++i) {
        std::cin >> operation;
        switch (operation){
            case 1: {
                position = 0;
                std::cin >> value;
                root = Insert(root, value, position);
                result.push_back(position);
                break;
            }
            case 2: {
                std::cin >> value;
                root = Remove(root, value);
                break;
            }
            default: break;
        }
    }
    for (int i = 0; i < result.size(); ++i) {
        std::cout << result[i] << std::endl;
    }
    return 0;
}
