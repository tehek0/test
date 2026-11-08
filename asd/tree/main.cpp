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
    node* search_parent(node* current, node* child) {
        if (!current || current->l == child || current->r == child)
            return current;
        if (child->key < current->key)
            return search_parent(current->l, child);
        return search_parent(current->r, child);
    }
    void insert(int k) {
        node* current = head;
        while (true) {
            if (current->key == k)
                return;
            if (k > current->key) {
                if (current->r) {
                    current = current->r;
                    continue;
                }
                current->r = new node(k);
                return;
            }
            if (k < current->key) {
                if (current->l) {
                    current = current->l;
                    continue;
                }
                current->l = new node(k);
                return;
            }
        }
    }
    void remove(int k) {
        node* to_remove = search(head, k);
        if (to_remove) {
            node* parent = to_remove;
            if (to_remove->l) {
                node* pred = parent->l;
                node* pred_l = nullptr;
                while (pred->r) {
                    parent = pred;
                    pred = pred->r;
                    pred_l = pred->l;
                }
                parent->r = pred_l;
                to_remove->key = pred->key;
                delete pred;
                return;
            }
            if (to_remove->r) {
                node* succ = parent->r;
                node* succ_r = nullptr;
                while (succ->l) {
                    parent = succ;
                    succ = succ->l;
                    succ_r = succ->r;
                }
                parent->r = succ_r;
                to_remove->key = succ->key;
                delete succ;
                return;
            }
            parent = search_parent(head, to_remove);
            if (parent->r == to_remove)
                parent->r = nullptr;
            if (parent->l == to_remove)
                parent->l = nullptr;
            if (!parent)
                head = nullptr;
            delete to_remove;
        }
    }

    void print() {
        print_recursion(head);
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
    void print_recursion(node* current) {
        if (!current)
            return;

        std::cout << current->key;

        if (!current->l && !current->r)
            return;

        std::cout << "(";
        print_recursion(current->l);
        std::cout << ", ";
        print_recursion(current->r);
        std::cout << ")";

    }
};

int main()
{
    std::setlocale(LC_ALL, "Russian");

    auto tr = tree();

    bool exit = false;
    while (!exit) {
        std::cout
            << std::endl
            << "1. Добавить вершину" << std::endl
            << "2. Удалить вершину" << std::endl
            << "3. Найти вершину" << std::endl
            << "4. Выйти" << std::endl 
            << std::endl;

        int input;
        std::cin >> input;
        switch (input) {
        case 1: {
            std::cout << "Значение: ";
            int key;
            std::cin >> key;
            tr.insert(key);
            break;
        }
        case 2: {
            std::cout << "Значение: ";
            int key;
            std::cin >> key;
            tr.remove(key);
            break;
        }
        case 3: {
            std::cout << "Значение: ";
            int key;
            std::cin >> key;
            node* n = tr.search(tr.head, key);
            if (n) {
                std::cout << "Найдено, адрес: " << n;
            }
            else {
                std::cout << "Не найдено";
            }
            std::cout << std::endl;
            break;
        }
        case 4: {
            exit = true;
            break;
        }
        default: break;
        }
    }
    tr.print();
    
}
