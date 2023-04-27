#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class AVL {
public:
    AVL() : root(nullptr) {}

    bool insert(string name, int id);
    void inOrder() const {inOrder(root);}
    void preOrder() const {preOrder(root);}
    void postOrder() const {postOrder(root);}
    void searchID(int id) {searchID(root, id);}
    void searchName(string name) {searchName(root, name);}
    void printLevel() { printLevelCount(root);}
    void removeID_1(int id){remove_1(root, id);}
    bool remove(int id){return remove(root, id);}
    bool removeInorder(int n){return removeInorder(root, n);}

private:
    struct Node {
        std::string name;
        int id;
        Node *left, *right;

        Node(std::string name, int id) : name(name), id(id), left(nullptr), right(nullptr) {}
    };

    int getHeight(Node *node) const;
    int getBalance(Node *node) const;
    Node *rightRotate(Node *node);
    Node *leftRotate(Node *node);
    Node *balanceTree(Node *node);
    void inOrderHelper(Node* root, vector<Node*> &nodes) const;
    void preOrderHelper(Node* root, vector<Node*> &nodes) const;
    void postOrderHelper(Node* root, vector<Node*> &nodes) const;
    void inOrder(Node *node) const;
    void preOrder(Node *node) const;
    void postOrder(Node *node) const;
    void printLevelCount(Node *root);
    void searchID(Node *node, int id);
    void searchName(Node *node, string name);
    void remove_1(Node *&node, int id);
    Node *successor(Node *node);
    bool removeInorder(Node *node, int n);
    bool remove(Node *&node, int id);


    Node *root;
};

int AVL::getHeight(Node *node) const {
    if (node == nullptr) {
        return 0;
    }
    return std::max(getHeight(node->left), getHeight(node->right)) + 1;
}

void AVL::printLevelCount(Node *root) {
    cout << getHeight(root) << endl;
}

void AVL::searchID(Node *node, int id){
    vector<Node*> nodes;
    inOrderHelper(root, nodes);
    bool found = false;
    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i]->id == id) {
            cout << nodes[i]->name << endl;
            found = true;
            break;
        }
    }
    if (!found){
        cout << "unsuccessful" << endl;
    }
}

void AVL::searchName(Node *node, string name){
    // check if the name is only made up of alphabets or spaces
    for (const char &c : name) {
        if (!isalpha(c) && c != ' ') {
            cout << "unsuccessful" << endl;
            return;
        }
    }
    vector<Node*> nodes;
    preOrderHelper(root, nodes);
    bool found = false;
    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i]->name == name) {
            if(nodes[i]->id < 10000000)
            {
                // setfill is ' ' and width is set as 8
                cout << setfill(' ') << setw(8);

                cout << nodes[i]->id << endl;
            }
            else{
                cout << nodes[i]->id << endl;
            }
            found = true;
        }
    }
    if (!found){
        cout << "unsuccessful" << endl;
    }
}

int AVL::getBalance(Node *node) const {
    if (node == nullptr) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

AVL::Node *AVL::rightRotate(Node *node) {
    Node *x = node->left;
    Node *T2 = x->right;

    x->right = node;
    node->left = T2;

    return x;
}

AVL::Node *AVL::leftRotate(Node *node) {
    Node *x = node->right;
    Node *T2 = x->left;

    x->left = node;
    node->right = T2;

    return x;
}

AVL::Node *AVL::balanceTree(Node *node) {
    int balance = getBalance(node);
    if (balance > 1 && getBalance(node->left) >= 0) {
        return rightRotate(node);
    }
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && getBalance(node->right) <= 0) {
        return leftRotate(node);
    }
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

bool AVL::insert(std::string name, int id) {

    // check if the name is only made up of alphabets or spaces
    for (const char &c : name) {
        if (!isalpha(c) && c != ' ') {
            return false;
        }
    }
    if (root == nullptr) {
        root = new Node(name, id);
        return true;
    }
    Node *node = root, *parent = nullptr;
    while (node != nullptr) {
        parent = node;
        if (id < node->id) {
            node = node->left;
        } else if (id > node->id)
        {
            node = node->right;
        } else {
            return false;
        }
    }

    Node *newNode = new Node(name, id);
    if (id < parent->id) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    root = balanceTree(root);

    return true;
}

void AVL::inOrderHelper(Node* root, vector<Node*> &nodes) const
{
    if (root == nullptr)
        return;
    inOrderHelper(root->left, nodes);
    nodes.push_back(root);
    inOrderHelper(root->right, nodes);
}
void AVL::preOrderHelper(Node* root, vector<Node*> &nodes) const
{
    if (root == nullptr)
        return;
    nodes.push_back(root);
    preOrderHelper(root->left, nodes);
    preOrderHelper(root->right, nodes);
}
void AVL::postOrderHelper(Node* root, vector<Node*> &nodes) const
{
    if (root == nullptr)
        return;
    postOrderHelper(root->left, nodes);
    postOrderHelper(root->right, nodes);
    nodes.push_back(root);
}

void AVL::inOrder(Node *node) const {
    vector<Node*> nodes;
    inOrderHelper(root, nodes);
    for (int i = 0; i < nodes.size(); i++) {
        if (i != nodes.size() - 1)
            cout << nodes[i]->name << ", ";
        else
            cout << nodes[i]->name << endl;

    }
}
void AVL::preOrder(Node *node) const {
    vector<Node*> nodes;
    preOrderHelper(root, nodes);
    for (int i = 0; i < nodes.size(); i++) {
        if (i != nodes.size() - 1)
            cout << nodes[i]->name << ", ";
        else
            cout << nodes[i]->name <<endl;

    }
}
void AVL::postOrder(Node *node) const {
    vector<Node*> nodes;
    postOrderHelper(root, nodes);
    for (int i = 0; i < nodes.size(); i++) {
        if (i != nodes.size() - 1)
            cout << nodes[i]->name << ", ";
        else
            cout << nodes[i]->name << endl;

    }
}

AVL::Node *AVL::successor(Node *node) {
    Node *current = node;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

void AVL::remove_1(Node *&node, int id) {
    if (node == NULL) {
        cout << "unsuccessful" << endl;
        return;
    }
    if (id < node->id) {
        remove_1(node->left, id);
    } else if (id > node->id) {
        remove_1(node->right, id);
    } else {
        cout << "successful" << endl;
        if (node->left == NULL && node->right == NULL) {
            delete node;
            node = NULL;
        } else if (node->left == NULL) {
            Node *temp = node;
            node = node->right;
            delete temp;
        } else if (node->right == NULL) {
            Node *temp = node;
            node = node->left;
            delete temp;
        } else {
            Node *temp = successor(node->right);
            node->id = temp->id;
            node->name = temp->name;
            remove_1(node->right, temp->id);
        }

    }


}

bool AVL::remove(Node *&node, int id) {
    if (node == nullptr) {
        return false;
    }

    if (id < node->id) {
        return remove(node->left, id);
    } else if (id > node->id) {
        return remove(node->right, id);
    } else {
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            node = nullptr;
        } else if (node->left == nullptr) {
            Node* temp = node;
            node = node->right;
            delete temp;
        } else if (node->right == nullptr) {
            Node* temp = node;
            node = node->left;
            delete temp;
        } else {
            Node* temp = node->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            node->id = temp->id;
            node->name = temp->name;
            return remove(node->right, temp->id);
        }
        return true;
    }
}


bool AVL::removeInorder(Node *node, int n) {
    if(node == nullptr){
        return false;
    }

    vector<Node*> nodes;
    inOrderHelper(node, nodes);
    if( n > nodes.size()-1){
        return false;
    }
    else{
        return remove(nodes[n]->id);
    }
}

void execute(string command, AVL &avl){
    int index = command.find(' ');
    string call = command.substr(0, index);
    command = command.substr(index + 1);
    if (call == "insert"){
        command = command.substr(1);
        index = command.find('\"');
        string name = command.substr(0, index);
        command = command.substr(index + 2);
        if (command.length()>=8 && stoi(command)<100000000){
            int id = stoi(command);
            if (avl.insert(name, id)) {
                cout << "successful" << endl;
            }
            else {
                cout << "unsuccessful" << endl;
            }
        }
        else {
            cout << "unsuccessful" << endl;
        }
    }
    else if (call == "remove") {
        if (command.length()>=8 && stoi(command)<100000000){
            if (avl.remove(stoi(command))) {
                cout << "successful" << endl;
            }
            else {
                cout << "unsuccessful" << endl;
            }
        }
        else {
            cout << "unsuccessful" << endl;
        }
    }
    else if (call == "removeInorder"){
        if (avl.removeInorder(stoi(command))){
            cout << "successful" << endl;
        }
        else {
            cout << "unsuccessful" << endl;
        }
    }
    else if (call == "search") {
        if (command[0] == '"') {
            string name = command.substr(1, command.length() - 2);
            avl.searchName(name);
        }
        else {
            if (command.length()>=8 && stoi(command)<100000000){
                avl.searchID(stoi(command));
            }

        }
    }
    else if (call == "printInorder") {
        avl.inOrder();
    }
    else if (call == "printPreorder") {
        avl.preOrder();
    }
    else if (call == "printPostorder") {
        avl.postOrder();
    }
    else if (call == "printLevelCount") {
        avl.printLevel();
    }

}


int main() {
    AVL avl;
    int numLines;
    cin >> numLines;
    string line;
    vector<string> commands;

    for (int i = 0; i < numLines+1; i++)
    {
        getline(cin, line);
        commands.push_back(line);
    }
    for (int i = 0; i < commands.size(); i++){
        execute(commands[i], avl);
    }

    return 0;
}
