#pragma once

#include <array>
#include <vector>
#include <list>
#include <forward_list>
// implement linked lists
#include <queue>
#include <deque>
#include <stack>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <tuple>
// implement trees & graphs
#include <iostream>
#include <algorithm>
// other libraries
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <climits>
#include <string>
#include <sstream>


// simplify definitions for vectors and iterators
typedef std::vector<int> vect;
typedef std::vector<std::string> vectStr;
typedef std::vector<std::vector<int>> vect2d;
typedef std::vector<std::vector<int>>::iterator iter2d;
typedef std::vector<int>::iterator iter;

// ======================= Data structures ============================== //

// ======================= Lists + DLLists ============================== //

namespace Lists
{

    /** each element is accessed by the pointer of the previous element
     *
     */
    typedef struct node
    {
        int data;
        node* next;
    }*nodePtr;


    /** Doubly-Linked lists
     * Compared to linked lists, this type of data structures
     * has 2 tails one at the head and the one in the end
     */
    typedef struct nodeDll
    {
        nodeDll* next;
        nodeDll* prev;
        int data;
    }*nodePtrD;


    class List
    {
    private:
        typedef struct node
        {
            node* next;
            int value;
        }*nodePtr;

        nodePtr head;
        nodePtr curr;
        nodePtr temp;
    public:
        List() :
            head(nullptr),
            curr(nullptr),
            temp(nullptr)
        {
        }
        void AddNode(int value)
        {
            nodePtr n = new node;
            n->next = nullptr;
            n->value = value;

            if (head != nullptr)
            {
                curr = head;
                while (curr->next != nullptr)
                {
                    curr = curr->next;
                }
                curr->next = n;
            }
            else
            {
                head = n;
            }
        }
        void DeleteNode(int data)
        {
            nodePtr delPtr = nullptr;
            temp = head;
            curr = head;

            while (curr != nullptr && curr->value != data)
            {
                temp = curr;
                curr = curr->next;
            }
            if (curr == nullptr)
            {
                std::cout << data << " data was not found\n";
                delete delPtr;
            }
            else
            {
                delPtr = curr;
                curr = curr->next;
                temp->next = curr;
                if (delPtr == head)
                {
                    head = head->next;
                    temp = nullptr;
                }
                delete delPtr;
            }
        }
        void DeleteFromGivenNode(nodePtr n)
        {
            n->value = n->next->value;
            n->next = n->next->next;
        }
        void PrintList()
        {
            curr = head;
            while (curr != NULL)
            {
                std::cout << curr->value << " ";
                curr = curr->next;
            }
        }
        bool has_cycle(nodePtr head)
        {
            // Complete this function
            // Do not write the main method
            if (head == NULL)
                return false;

            nodePtr curr1 = head;
            nodePtr curr2 = head->next;
            while (curr1 != curr2)
            {
                if (curr1 == NULL || curr2 == NULL) return false;
                curr1 = curr1->next;
                curr2 = curr2->next->next;
            }
            return true;
        }
        nodePtr GetHead()
        {
            return head;
        }
    };


};


// =======================-------BSTs------============================== //

std::string repeatStr(int n, char s)
{
    std::stringstream buff;
    for (int i = 0; i < n; i++)
        buff << s;;
    return buff.str();
}

vectStr zip(vectStr a, vectStr b)
{
    std::unordered_map<int, std::string> z;
    int inc = 0;
    for (uint32_t i = 0, j = 0; j < b.size() || i < a.size(); j++, i++)
    {
        if (i < a.size())
        {
            if (i < a.size() && z.empty() != true)
                inc++;
            z.insert(std::pair<int, std::string>(inc, a.at(i)));
        }
        if (j < b.size())
        {
            if (j < b.size() && z.empty() != true)
                inc++;
            z.insert(std::pair<int, std::string>(inc, b.at(j)));
        }
    }
    vectStr ze;
    for (auto i : z)
        ze.push_back(i.second);
    return ze;
}

namespace BST
{
    
    typedef class Node              // simplify the type 
    {
    public:                         // provide secured access to BinaryTree class 
        int data;
        Node* left;
        Node* right;
    
        Node(int _data = 0) :      // constructor + initialization list for the attributes 
            data(_data),
            left(nullptr),
            right(nullptr)
        {}
    }*nodePtr;

    class BinaryTree : public Node
    {
    public:
        nodePtr root;
    
        BinaryTree() : root(nullptr) {};
        
        void insert(int data)
        {
            if (root == nullptr)
                root = new Node(data);
            else
                _insert(data, root);
        }

        void _insert(int data, nodePtr cur_node)
        {
            if (data < cur_node->data)
            {
                if (cur_node->left == nullptr)
                    cur_node->left = new Node(data);
                else
                    _insert(data, cur_node->left);
            }
            else if (data > cur_node->data)
            {
                if (cur_node->right == nullptr)
                    cur_node->right = new Node(data);
                else
                    _insert(data, cur_node->right);
            }
            else
                std::cout << "Value already present in tree" << std::endl;
        }

        void display(nodePtr cur_node)
        {
            auto [lines, width, height, middle] = _display(cur_node);
            for (auto line : lines)
                std::cout << line << std::endl;
        }

        std::tuple<vectStr, int, int, int> _display(nodePtr cur_node)
        {
            std::stringstream buff;
            vectStr shifted_lines, line;
            std::string first_line;
            std::string second_line;
            std::string s;

            if (cur_node->right == nullptr && cur_node->left == nullptr)
            {
                buff << cur_node->data;
                buff >> s;
                buff.str("");
                line.push_back(s);
                int width = s.length();
                s = "";
                int height = 1;
                int middle = width / 2;
                return { line , width, height, middle };
            }

            if (cur_node->right == nullptr)
            {
                auto [lines, n, p, x] = _display(cur_node->left);
                buff << cur_node->data;
                buff >> s;
                buff.str("");
                int u = s.length();
                first_line = repeatStr(x + 1, ' ') + repeatStr(n - x - 1, '_') + s;
                second_line = repeatStr(x, ' ') + '/' + repeatStr(n - x - 1 + u, ' ');
                s = "";
                for (uint32_t line = 0; line < lines.size(); line++)
                {
                    lines.at(line) += repeatStr(u, ' ');
                    shifted_lines.push_back(lines.at(line));
                }
                vectStr tLines;
                tLines.push_back(first_line);
                tLines.push_back(second_line);
                tLines.insert(tLines.end(), shifted_lines.begin(), shifted_lines.end());
                return { tLines, n + u, p + 2, n + u / 2 };
            }

            if (cur_node->left == nullptr)
            {
                auto [lines, n, p, x] = _display(cur_node->right);
                buff << cur_node->data;
                buff >> s;
                buff.str("");
                int u = s.length();
                first_line = s + repeatStr(x, '_') + repeatStr(n - x, ' ');
                second_line = repeatStr(u + x, ' ') + '\\' + repeatStr(n - x - 1, ' ');
                s = "";
                for (uint32_t line = 0; line < lines.size(); line++)
                {
                    lines.at(line) = repeatStr(u, ' ') + lines.at(line);
                    shifted_lines.push_back(lines.at(line));
                }
                vectStr tLines;
                tLines.push_back(first_line);
                tLines.push_back(second_line);
                tLines.insert(tLines.end(), shifted_lines.begin(), shifted_lines.end());
                return { tLines, n + u, p + 2, u / 2 };
            }
            auto [left, n, p, x] = _display(cur_node->left);
            auto [right, m, q, y] = _display(cur_node->right);
            buff << cur_node->data;
            buff >> s;
            buff.str("");
            int u = s.length();
            first_line = repeatStr(x + 1, ' ') + repeatStr(n - x - 1, '_') + s + repeatStr(y, '_') + repeatStr(m - y, ' ');
            second_line = repeatStr(x, ' ') + '/' + repeatStr(n - x - 1 + u + y, ' ') + '\\' + repeatStr(m - y - 1, ' ');

            if (p < q)
                for (int i = 0; i < (q - p); i++) left.push_back(repeatStr(n, ' '));
            else if (q < p)
                for (int i = 0; i < (p - q); i++) right.push_back(repeatStr(m, ' '));
            vectStr zipped_lines = zip(left, right);
            for (uint32_t a = 0, b = 1; a < zipped_lines.size(); )
            {
                if (a == b)
                    break;
                zipped_lines.at(a) = zipped_lines.at(a) + repeatStr(u, ' ') + zipped_lines.at(b);
                zipped_lines.erase(zipped_lines.begin() + b);
                a += 1;
                b = a;
                if (b < zipped_lines.size() - 1) b = (a + 1);
            }
            vectStr lines;
            lines.push_back(first_line);
            lines.push_back(second_line);
            lines.insert(lines.end(), zipped_lines.begin(), zipped_lines.end());
            return { lines, n + m + u, fmax(p, q) + 2, n + u / 2 };
        }
    };
}