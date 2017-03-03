//
//  main.cpp
//  questions
//
//  Created by Sergei Gringauze on 2/19/17.
//  Copyright © 2017 Sergei Gringauze. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <list>
#include <utility>
#include <vector>
#include <numeric>
#include <deque>
#include <cmath>

using namespace std;

template<typename Data>
struct tree_node
{
    tree_node *left;
    tree_node *right;
    Data data;
    int h;
    
    tree_node<Data>(tree_node* _left, tree_node *_right, Data _data)
    : left (_left), right (_right), data (_data) {}
    
};

typedef tree_node<int> int_node;

template<typename Data, typename Comp>
tree_node<Data>* treeLookup (tree_node<Data>* root, Data data, const Comp comparator)
{
    auto next = root;
    while (next != nullptr)
    {
        if (comparator(next->data, data) == 0)
            break;
        
        if (comparator(next->data, data) > 0)
            next = next->left;
        else
            next = next->right;
    }
    
    return next;
}

template<typename Callback>
void BFS(int_node *root, Callback cb)
{
    std::list<int_node*> node_list;

    if (!root)
        return;
    
    node_list.push_back(root);
    
    while (!node_list.empty())
    {
        auto list_head = node_list.front();
        if (list_head->left != nullptr)
        {
            node_list.push_back(list_head->left);
        }
        if (list_head->right != nullptr)
        {
            node_list.push_back(list_head->right);
        }
        cb(list_head->data);
        node_list.pop_front();
    }
}

template<typename Callback>
void DFS_recursive(int_node *root, Callback cb)
{
    if (!root)
        return;

    DFS_recursive(root->left, cb);
    cb(root->data);
    DFS_recursive(root->right, cb);
}

template<typename Callback>
void DFS(int_node *root, Callback cb)
{
    std::list<int_node*> node_list;
    
    auto current = root;
    
    while (!node_list.empty() || current != nullptr)
    {
        if (current != nullptr)
        {
            node_list.push_back(current);
            current = current->left;
        }
        else
        {
            if (!node_list.empty())
            {
                current = node_list.back();
                cb(current->data);
                current = current->right;
                node_list.pop_back();
            }
        }
    }
}

int calc_tree_height(int_node *root)
{
    if (!root)
        return 0;
    
    root->h = max (calc_tree_height(root->left), calc_tree_height(root->right)) + 1;
    return root->h;
}

list<int_node*> enlist_nodes_bfs(int_node *root)
{
    std::list<int_node*> node_list;
    
    if (!root)
        return {};
    
    node_list.push_back(root);
    auto cur = node_list.begin();
    while (cur != node_list.end())
    {
        if ((*cur)->left != nullptr)
        {
            node_list.push_back((*cur)->left);
        }
        if ((*cur)->right != nullptr)
        {
            node_list.push_back((*cur)->right);
        }
        cur++;
    }
    return node_list;
}

bool tree_eq(int_node *left, int_node *right)
{

    if (!left && !right)
        return true;
    
    return (left->h == right->h && left->data == right->data &&
            tree_eq(left->left, right->left) && tree_eq(left->right, right->right));
}

int count_eq_subtrees(int_node *root)
{
    if (!root)
        throw invalid_argument("Invalid argument - root can not be null");
    
    calc_tree_height(root);
    auto n_list = enlist_nodes_bfs(root);
    
    int count=0;
    for (auto cur=n_list.begin(); cur != n_list.end(); ++cur)
    {
        for (auto cur2=next(cur); cur2 != n_list.end(); ++cur2)
        {
            if (tree_eq(*cur, *cur2))
                count++;
        }
    }
    return count;
}




vector<int> stockPricesYesterday{10, 15, 5, 6, 7, 4};

pair<size_t, size_t> getMaxProfit(vector<int>& prices)
{
    auto best_profit = 0;
    pair<size_t, size_t> result { 0, 0};
    
    for (auto i=0; i < prices.size(); i++)
    {
        for (auto j=i; j < prices.size(); j++)
        {
            if ((prices[j] - prices[i]) > best_profit)
            {
                best_profit = prices[j] - prices[i];
                result = {i, j};
            }
        }
    }
    
    return result;
}

pair<size_t, size_t> getMaxProfitFast(vector<int>& prices)
{
    auto best_profit = 0;
    auto minPriceIdx = 0;
    pair<size_t, size_t> result { 0, 0};
    
    for (auto i=0; i < prices.size(); i++)
    {
        if (prices[i] < prices[minPriceIdx])
        {
            minPriceIdx = i;
        }
        if ((prices[i] - prices[minPriceIdx]) > best_profit)
        {
            best_profit = prices[i] - prices[minPriceIdx];
            result = {minPriceIdx, i};
        }
    }
    
    return result;
}

vector<int> getProducts(vector<int> in)
{
    if (in.size() < 2)
        throw new invalid_argument("minimum 2 elements required");
    
    vector<int> res(in.size());
    int product = 1;
    
    for (size_t i=0; i<in.size(); i++)
    {
        res[i] = product;
        product *= in[i];
    }
    
    product = 1;
    for (long i=in.size()-1; i>=0; i--)
    {
        res[i] *= product;
        product *= in[i];
    }
    
    return res;
}

string look_and_say(uint n)
{
    if (n==1)
        return "1";
    
    auto prevLnS = look_and_say(n-1);
    
    ostringstream strBuilder;
    for (auto i=0; i < prevLnS.size();)
    {
        auto curC = prevLnS[i];
        int curCharCounter = 0;
        while (i < prevLnS.size() && curC == prevLnS[i])
        {
            i++;
            curCharCounter++;
        }
        
        strBuilder << curCharCounter << curC;
    }
    
    return strBuilder.str();
}

//////////////////////////////////
//
//  Lists
//

struct node
{
    node* next;
    int data;
    node (node* _next, int _data)
     : next(_next)
     , data (_data)
    {}
};

// Find middle
node* find_middle_node(node *head)
{
    auto cur = head;
    auto curSlow = head;
    
    while (cur && cur->next)
    {
        cur = cur->next->next;
        curSlow = curSlow->next;
    }
    
    return cur ? curSlow->next : curSlow;
}

// Print list
ostream& operator << (ostream& os, const node& head)
{
    auto ptr = &head;
    while (ptr)
    {
        os << ptr->data << "->";
        ptr = ptr->next;
    }
    return os << "X";
}

// Reverse list
node* reverse_list(node *head)
{
    if (!head)
        return nullptr;
    
    auto prev = head;
    auto cur = head->next;
    node* next;
    
    while (cur)
    {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    };

    head->next = nullptr;
    return prev;
}

// Zip-merge
void zip_merge(node* head1, node* head2)
{
    while (head1 && head2)
    {
        auto next1 = head1->next;
        head1->next = head2;
        auto next2 = head2->next;
        head2->next = next1;
        
        head1 = next1;
        head2 = next2;
    }
}

// Stacks
// 1,2,3,4,5,6,+,+,+,+,+
/*
1, 2, 3, 4, 5, +, +, +, +     | 6, +
1, 2, 3, 4, +, +, +      | 5, +
1, 2, 3, +, +    | 4, +
1, 2, + | 3, +
1 | 2, +


1, 2, *, 3, 4, +, +    (1*2 + 3) + 4
*/

struct op_unit
{
    char op;
    int num;
    
    bool is_num;
    
    op_unit(char ch) : op(ch), is_num(false) {};
    op_unit(int _num) : num(_num), is_num(true) {};
};

int ReversePolishNotation (list<op_unit> ops)
{
    list<op_unit> newOps;
    
    if (ops.empty())
        throw invalid_argument("invalid RPN");
    
    auto last = ops.back();
    ops.pop_back();
    
    while (!last.is_num && !ops.empty())
    {
        newOps.push_back(last);
        last = ops.back();
        ops.pop_back();
    }
    
    if (ops.empty())
    {
        if (!last.is_num)
            throw invalid_argument("invalid RPN");
        return last.num;
    }
    
    auto curOp = newOps.back().op;
    newOps.pop_back();
    
    while (!newOps.empty())
    {
        ops.push_back(newOps.back());
        newOps.pop_back();
    }
    
    switch (curOp) {
        case '+':
            return ReversePolishNotation(ops) + last.num;
            break;
        case '-':
            return ReversePolishNotation(ops) - last.num;
            break;
        case '*':
            return ReversePolishNotation(ops) * last.num;
            break;
        case '/':
            return ReversePolishNotation(ops) / last.num;
            break;
            
        default:
            throw invalid_argument("invalid operator");
    }
}

// water bodies

int calc_water_size(vector<vector<int>>& sqr, int i, int j)
{
    if (i<0 || i>=sqr.size() || j<0 || j>=sqr.size())
        return 0;
    
    if (sqr[i][j] != 0)
        return 0;
    
    auto result = 1;
    sqr[i][j] = 1;
    for (auto di=i-1; di <= i+1; di++ )
    {
        for (auto dj=j-1; dj <= j+1; dj++ )
        {
            result += calc_water_size(sqr, di, dj);
        }
    }
    return result;
}

void print_water_bodies(vector<vector<int>> sqr)
{
    list<int> bodies;
    
    for (auto i=0; i < sqr.size(); i++ )
    {
        for (auto j=0; j < sqr.size(); j++ )
        {
            auto body = calc_water_size(sqr, i, j);
            if (body > 0)
                bodies.push_back(body);
        }
    }
    
    bodies.sort();
    bodies.unique();
    
    for (auto body : bodies)
    {
        cout << body << endl;
    }
}



// TODO

// heap, LRU cache
// topological sorting
// more trees (r-b, etc)
// threadpool, synchronization
// dynamic programming!
// design patterns!

/* 
 
 Quesitons:
 1. Books (cracking, EPI, Skiena?)
 2. Websites - careercup, hackerrank(?), glassdoor
 3. Design questions, domain knowledge - c++, video processing, REST API, web services
 
*/

void all_subsets(deque<int> all, deque<deque<int>> &allSubs)
{
    if (all.empty())
    {
        allSubs.push_back(deque<int>());
        return;
    }
    
    auto next = all.front();
    all.pop_front();
    all_subsets(all, allSubs);
    deque<deque<int>> moreSubs(allSubs);
    for (auto i=0; i<moreSubs.size();i++)
    {
        moreSubs[i].push_front(next);
    }
    copy(moreSubs.begin(), moreSubs.end(), back_inserter(allSubs));
}

deque<string> all_perms(string instr)
{
    if (instr.length()==1)
        return {instr};
    
    auto perms = all_perms(instr.substr(1));

    deque<string> result;
    for (auto perm : perms)
    {
        for (auto chIdx=0; chIdx < perm.length(); chIdx++)
        {
            string newPerm(perm.substr(0, chIdx));
            newPerm.append(instr.substr(0,1));
            newPerm.append(perm.substr(chIdx, perm.length()));
            result.push_back(newPerm);
        }
    }
    
    return result;
}



// Duplicate subtrees


// min sqrs
int min_sqrs(int A, int B)
{
    int res;
    while (A != 0 && B != 0)
    {
        int mone = max (A, B);
        int mehane = min (A, B);
        
        auto sqrs = floor (mone/mehane);
        A = mone - sqrs * mehane;
        B = mehane;
        res += sqrs;
    }
    return res;
}

int main()
{
    
    int_node node1 (nullptr, nullptr, 1);
    int_node node3 (nullptr, nullptr, 1);
    int_node node2 (&node1, &node3, 2);
    int_node node5 (nullptr, nullptr, 5);
    int_node node7 (nullptr, nullptr, 7);
    int_node node6 (&node5, &node7, 6);
    int_node node4 (&node2, &node6, 4);
 
    cout << count_eq_subtrees(&node4) << endl;
    
    
    /*
    auto found_node = treeLookup(&node4, 7, [] (int a, int b){ return a-b; });
    if (found_node != nullptr)
        cout << "Found node: " << found_node->data << endl;
    
    auto print_int = [] (int a) { cout << a << ", "; };
    BFS(&node4, print_int);
    cout << endl;
    DFS_recursive(&node4, print_int);
    cout << endl;
    DFS(&node4, print_int);
    cout << endl;
    
    auto profit = getMaxProfit(stockPricesYesterday);
    cout << "Best profit: [" << profit.first << ", " << profit.second << "]" << endl;
    profit = getMaxProfitFast(stockPricesYesterday);
    cout << "Best profit fast: [" << profit.first << ", " << profit.second << "]" << endl;

    auto res = getProducts({1, 2, 3, 4, 5});
    for (auto num : res) cout << num << ", ";
    
    
    cout << look_and_say(8) << endl;
    
    node n5(nullptr, 5);
    node n4(&n5, 4);
    node n3(&n4, 3);
    node n2(&n3, 2);
    node n1(nullptr, 1);
    
    cout << n1 << endl;

    auto mn = find_middle_node(&n1);
    cout << *mn << endl;
    
    for (auto node = &n1; node != nullptr; node = node->next)
    {
        if (node->next == mn)
            node->next = nullptr;
    }

    cout << n1 << endl;
    
    auto rl = reverse_list(mn);
    
    if (rl)
        cout << *rl << endl;
    
    zip_merge(&n1, rl);
    cout << n1 << endl;

    // cout << ReversePolishNotation({3, 5, '+', 7, 2, '-', '*'}) << endl;
    
    vector<vector<int>> sqr = {{0,1,1,0},
                               {0,0,1,0},
                               {0,1,0,1},
                               {1,1,1,0}};
    print_water_bodies(sqr);
     
    
    deque<deque<int> > allSubs;
    all_subsets({1, 2, 3, 4, 5}, allSubs);
    
    for (auto perm : all_perms("zhopa"))
        cout << perm << endl;
    
    cout << min_sqrs(10,9) << endl;
    cout << min_sqrs(13,29) << endl;
    cout << min_sqrs(4,5) << endl;
    
    */
    
    return 0;
}
