#include <iostream>
#include <string>
#include <vector>

struct node {
    node* l = nullptr;
    node* r = nullptr;
    int key;
    node(int k) : key(k) {}
};

class tree {
public:
    node* head = nullptr;
    tree() {
        std::string input;
        std::getline(std::cin, input);
        std::string read;
        for (int c = 0; c < input.size(); ++c) {
            if (input[c] == ' ')
                continue;

            if (input[c] != '(') {
                read += input[c];
                continue;
            }
            head = new node(std::stoi(read));
            ++c;
            fill_tree(head, input, c);
            break;
        }
    }

    void nlr() {
        nlr_recursion(head);
    }
    void lnr() {
        lnr_recursion(head);
    }
    void lrn() {
        lrn_recursion(head);
    }

    void nlr_loop() {
        std::vector<node*> stack;
        stack.emplace_back(head);

        while (true) {
            if (stack.size() == 0)
                break;

            node* current = stack[stack.size() - 1];
            if (current) {
                stack.pop_back();
                std::cout << current->key << " ";
                stack.emplace_back(current->r);
                stack.emplace_back(current->l);
            }
            else {
                stack.pop_back();
            }
        }
    }

    node* search(node* current, int key) {
        if (!current || current->key == key)
            return current;
        if (key < current->key)
            return search(current->l, key);
        return search(current->r, key);
    }

private:
    void fill_tree(node* current, const std::string& input, int& pos) {
        std::string read = "";
        char target = 0;
        for (; pos < input.size(); ++pos) {
            if (input[pos] == ' ')
                continue;
            if (input[pos] == ',' || input[pos] == ')' || input[pos] == '(') {
                if (read.size() > 0)
                    switch (target) {
                    case 0: current->l = new node(std::stoi(read)); read = ""; break;
                    case 1: current->r = new node(std::stoi(read)); read = ""; break;
                    }
                
                if (input[pos] == ',') {
                    target = 1;
                    continue;
                }

                if (input[pos] == '(') {
                    ++pos;
                    switch (target) {
                    case 0: fill_tree(current->l, input, pos); break;
                    case 1: fill_tree(current->r, input, pos); break;
                    }
                    continue;
                }
                if (input[pos] == ')')
                    return;
            }
            read += input[pos];
        }
    }
    void nlr_recursion(node* current) {
        if (!current)
            return;

        std::cout << current->key << " ";
        nlr_recursion(current->l);
        nlr_recursion(current->r);

    }
    void lnr_recursion(node* current) {
        if (!current)
            return;

        lnr_recursion(current->l);
        std::cout << current->key << " ";
        lnr_recursion(current->r);

    }
    void lrn_recursion(node* current) {
        if (!current)
            return;

        lrn_recursion(current->l);
        lrn_recursion(current->r);
        std::cout << current->key << " ";

    }
};

int main()
{
    auto x = tree();
    x.nlr();
    std::cout << std::endl << std::endl;
    x.lnr();
    std::cout << std::endl << std::endl;
    x.lrn();
    std::cout << std::endl << std::endl;
}
