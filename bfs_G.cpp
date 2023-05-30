#include <iostream>
#include <stdlib.h>
#include <queue>
#include <vector>

class node {
public:
    node *left, *right;
    int data;
};

class Breadthfs {
public:
    node *insert(node *, int);
    void bfs(node *);
};

node *insert(node *root, int data) {
    if (!root) {
        root = new node;
        root->left = NULL;
        root->right = NULL;
        root->data = data;
        return root;
    }

    std::queue<node *> q;
    q.push(root);

    while (!q.empty()) {
        node *temp = q.front();
        q.pop();

        if (temp->left == NULL) {
            temp->left = new node;
            temp->left->left = NULL;
            temp->left->right = NULL;
            temp->left->data = data;
            return root;
        }
        else {
            q.push(temp->left);
        }

        if (temp->right == NULL) {
            temp->right = new node;
            temp->right->left = NULL;
            temp->right->right = NULL;
            temp->right->data = data;
            return root;
        }
        else {
            q.push(temp->right);
        }
    }
}

void printGraph(node *root) {
    if (!root)
        return;

    std::queue<node *> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();

        for (int i = 0; i < levelSize; i++) {
            node *temp = q.front();
            q.pop();

            if (temp->left)
                q.push(temp->left);

            if (temp->right)
                q.push(temp->right);

            std::cout << temp->data << " ";

            if (i < levelSize - 1)
                std::cout << "-> ";
        }

        std::cout << std::endl;
    }
}

void bfs(node *head) {
    std::queue<node *> q;
    std::vector<int> bfsTraversal;

    if (head)
        q.push(head);

    while (!q.empty()) {
        node *currNode = q.front();
        q.pop();
        bfsTraversal.push_back(currNode->data);

        if (currNode->left)
            q.push(currNode->left);

        if (currNode->right)
            q.push(currNode->right);
    }

    std::cout << "BFS Traversal: ";
    for (int i = 0; i < bfsTraversal.size(); i++) {
        std::cout << bfsTraversal[i];
        if (i < bfsTraversal.size() - 1)
            std::cout << " -> ";
    }
    std::cout << std::endl;
}

int main() {
    node *root = NULL;
    int data;
    char ans;

    do {
        std::cout << "\nEnter data: ";
        std::cin >> data;
        root = insert(root, data);

        std::cout << "Do you want to insert one more node? (y/n): ";
        std::cin >> ans;
    } while (ans == 'y' || ans == 'Y');

    std::cout << "\nGraph Structure:\n";
    printGraph(root);

    bfs(root);

    return 0;
}

