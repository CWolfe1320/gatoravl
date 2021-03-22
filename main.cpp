#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <math.h> 

using namespace std;


class AVLNode {

private:

    int id;
    string name;


public:
    AVLNode* left;
    AVLNode* right;
    AVLNode() {
        name = "null";
        id = -1;
        left = nullptr;
        right = nullptr;
    }
    AVLNode(int _id, string _name) {
        id = _id;
        name = _name;
        left = nullptr;
        right = nullptr;
    }
    AVLNode(int _id, string _name, AVLNode* _left, AVLNode* _right) {
        /*In order to not have another two bloated constructors, when calling this
        without the intention of using both of the AVLNode pointers make sure to
        specify nullptr.*/
        id = _id;
        name = _name;
        left = _left;
        right = _right;
    }
    void SetName(string _name) {
        name = _name;
    }
    void SetID(int _id) {
        id = _id;
    }
    string GetName() {
        return name;
    }
    int GetID() {
        return id;
    }
};

// DIVIDER BETWEEN CLASS AND MAIN //

//My code for rotating the nodes from Stepik 5.1
//These four functions deal with rotating my nodes
void rotateLeft(AVLNode*& node)
{
    AVLNode* tempNode1 = new AVLNode();
    tempNode1 = node->right->left;
    node->right->left = node;
    node = node->right;
    node->left->right = tempNode1;

}

void rotateRight(AVLNode*& node)
{
    AVLNode* tempNode1 = new AVLNode();
    tempNode1 = node->left->right;
    node->left->right = node;
    node = node->left;
    node->right->left = tempNode1;

}

void rotateLeftRight(AVLNode*& node)
{

    AVLNode* tempNode1 = new AVLNode();
    tempNode1 = node->left->right->left;
    AVLNode* tempNode2 = new AVLNode();
    tempNode2 = node->left->right->right;
    node->left->right->left = node->left;
    node->left = node->left->right;
    node->left->left->right = NULL;
    rotateRight(node);
    node->left->right = tempNode1;
    node->right->left = tempNode2;

}

void rotateRightLeft(AVLNode*& node)
{
    AVLNode* temp = node->right->left->right;
    AVLNode* temp2 = node->right->left->left;
    node->right->left->right = node->right;
    node->right = node->right->left;
    node->right->right->left = NULL;
    node->right->left = node;
    AVLNode* newRoot = node->right;
    node->right = NULL;
    newRoot->left->right = temp2;
    newRoot->right->left = temp;
    node = newRoot;

}

//My Stepik code from 5.2 (albeit heavily altered to fit)
int TreeHeight(AVLNode* root) {
    if (root == nullptr) {
        return 0;
    }
    int leftHeight = 1;
    leftHeight = TreeHeight(root->left);
    int rightHeight = 1;
    rightHeight = TreeHeight(root->right);
    int inc = 1;
    if (rightHeight > leftHeight) {
        inc = rightHeight + 1;
    }
    else if (leftHeight > rightHeight) {
        inc = leftHeight + 1;
    }
    else {
        inc = leftHeight + 1;
    }

    return inc;
}

void balanceAVL(AVLNode*& root)
{

    int leftHeight = TreeHeight(root->left);
    int rightHeight = TreeHeight(root->right);

    int balanceFactor = leftHeight - rightHeight;


    if (balanceFactor < -1) {

        int rightTreeLeftHeight = TreeHeight(root->right->left);
        int rightTreeRightHeight = TreeHeight(root->right->right);
        int balanceFactorRight = rightTreeLeftHeight - rightTreeRightHeight;

        if (balanceFactorRight > 1) {
            rotateRightLeft(root);
        }
        else {
            rotateLeft(root);
        }
    }
    else if (balanceFactor > 1) {

        int leftTreeLeftHeight = TreeHeight(root->left->left);
        int leftTreeRightHeight = TreeHeight(root->left->right);
        int balanceFactorLeft = leftTreeLeftHeight - leftTreeRightHeight;

        if (balanceFactorLeft < -1) {
            rotateLeftRight(root);
        }
        else {
            rotateRight(root);
        }
    }
}

bool isAVL(AVLNode*& root)
{
    if (root == nullptr) {
        return true;
    }
    int leftHeight = TreeHeight(root->left);
    int rightHeight = TreeHeight(root->right);

    int finalAnswer = leftHeight - rightHeight;
    bool finalBoolLeft = false;
    bool finalBoolRight = false;
    finalBoolRight = isAVL(root->right);
    finalBoolLeft = isAVL(root->left);

    if (finalBoolLeft == false || finalBoolRight == false) {
        return false;
    }
    else if (finalAnswer >= -1 && finalAnswer <= 1) {
        return true;
    }
    else {
        balanceAVL(root);
        return false;
    }
}

void InsertNode(string name, int id, AVLNode*& root) {
    if (root->GetName() == "null") {
        root->SetName(name);
        root->SetID(id);
    }
    else {
        if (root->GetID() > id && root->left != nullptr) {
            InsertNode(name, id, root->left);
        }
        else if (root->right != nullptr) {
            InsertNode(name, id, root->right);
        }

        if (root->GetID() > id && root->left == nullptr) {
            AVLNode* node = new AVLNode(id, name);
            root->left = node;
        }
        else if (root->GetID() < id && root->right == nullptr) {
            AVLNode* node = new AVLNode(id, name);
            root->right = node;
        }
    }

}

void SearchID(string& name, int id, AVLNode* root) {
    if (root == nullptr) {
        return;
    }
    if (root->GetID() == id) {
        name = root->GetName();
    }
    else if (root->GetID() > id) {
        SearchID(name, id, root->left);
    }
    else if (root->GetID() < id) {
        SearchID(name, id, root->right);
    }
}

void SearchName(string name, bool& found, AVLNode* root) {
    if (root == nullptr) {
        return;
    }
    if (name == root->GetName()) {
        found = true;
        cout << root->GetID() << endl;
    }
    SearchName(name, found, root->left);
    SearchName(name, found, root->right);
}

AVLNode* InOrderSucc(AVLNode* root) {

    if (root->right != nullptr) {
        AVLNode* temp = root->right;
        while (temp->left) {
            temp = temp->left;
        }
        root = temp;
    }
    return root;
}

void InOrderSuccP(AVLNode*& root, AVLNode* succ) {

    if (root->left->GetID() == succ->GetID()) {
        root->left = nullptr;
    }
    else {
        InOrderSuccP(root->left, succ);
    }

}
//Whats going on here? Spaghetti put plainly. But the spaghetti is cooked perfectly. Do NOT touch it.
void RemoveID(int id, AVLNode*& root, bool& sTree) {
    if (root == nullptr) {
        return;
    }
    if (sTree) {
        if (root->right->GetID() == id) {
            if (sTree) {
                root->right->right->left = root->right->left;
                root->right = root->right->right;
                sTree = false;
                return;
            }
        }
        else if (root->left->GetID() == id) {
            if (sTree) {
                root->left->right->left = root->left->left;
                root->left = root->left->right;
                sTree = false;
                return;
            }
        }
        else if (root->GetID() == id) {
            if (root->right->left == nullptr) {
                root->right->left = root->left;
                root = root->right;
                sTree = false;
                return;
            }
        }
    }
    if (root->GetID() == id) {

        if (root->left != nullptr && root->right != nullptr && root->right->left != nullptr) {
            AVLNode* succ = new AVLNode();
            succ = InOrderSucc(root);


            if (succ->right != nullptr) {
                succ->right->right = root->right;
            }

            succ->left = root->left;
            succ->right = root->right;

            InOrderSuccP(root->right, succ);

            root = succ;
            return;
        }
        else if (root->left != nullptr && root->right != nullptr && root->right->left == nullptr) {
            sTree = true;
            return;
        }
        else if (root->left != nullptr) {
            root->left->right = root->right;
            root = root->left;
            return;
        }
        else if (root->right != nullptr) {
            root->right->left = root->left;
            root = root->right;
            return;
        }
        else if (root->left == nullptr && root->right == nullptr) {
            root = nullptr;
            return;
        }
    }
    else if (root->GetID() > id) {
        RemoveID(id, root->left, sTree);
    }
    else if (root->GetID() < id) {
        RemoveID(id, root->right, sTree);
    }
}

void PrintInOrder(AVLNode* root, string& pName) {
    if (root == nullptr) {
        return;
    }
        
    PrintInOrder(root->left, pName);

    pName = pName + ", " + root->GetName();

    PrintInOrder(root->right,pName);
}

void PrintPreOrder(AVLNode* root, string& pName) {
    if (root == nullptr) {
        return;
    }
    pName = pName + ", " + root->GetName();
    
    PrintPreOrder(root->left, pName);
    PrintPreOrder(root->right, pName);
}

void PrintPostOrder(AVLNode* root, string& pName) {
    if (root == nullptr) {
        return;
    }
    
    PrintPostOrder(root->left, pName);
    PrintPostOrder(root->right, pName);
    
    pName = pName + ", " + root->GetName();
}

void RemoveInOrder(AVLNode*& root, int& counter, int& rID, int n) {
    if (root == nullptr) {
        return;
    }

    if (counter == n) {
        rID = root->GetID();
    }

    RemoveInOrder(root->left, counter, rID, n);

    counter++;
    

    RemoveInOrder(root->right, counter, rID, n);
}

int main()
{
    //split the input string
    int arguments;
    string input;
    string intermediate;
    vector<string> args;

    //For the nodes
    AVLNode* root = new AVLNode();
    int id;
    string name;
    int nodeCount = 0;

    cin >> arguments;
    cin.ignore(); //flushing the yuckky buffer away      

    for (int i = 0; i < arguments; ++i) {
        //read in helping variables
        getline(cin, input);
        stringstream istream(input);
        string skip;

        //reads in first command
        getline(istream, intermediate, ' ');
        args.push_back(intermediate);

        if (intermediate == "insert") {
            getline(getline(istream, skip, '"'), intermediate, '"');
            args.push_back(intermediate);
            getline(istream, skip, ' ');
            getline(istream, intermediate);
            args.push_back(intermediate);
        }
        else if (intermediate == "search" && input.at(7) == '"') {
            getline(getline(istream, skip, '"'), intermediate, '"');
            args.push_back(intermediate);
        }
        else {
            while (getline(istream, intermediate, ' ')) {
                args.push_back(intermediate);
            }
        }

        //insert NAME ID
        if (args[0] == "insert") {
            //tests if the there are 8 digits in the id, and if name consists of only alpha characters (a-z A-Z) and spaces and if there are no duplicate ids.
            //if these conditions are met it inserts a node and prints successful. Otherwise it just prints unsuccessful.

            int idLength = 0;
            bool properName = true;

            id = stoi(args[2]);
            idLength = log10(id) + 1;
            bool duplicate = false;

            SearchID(name, id, root);

            if (name == "") {
                duplicate = false;
            }
            else {
                duplicate = true;
            }

            name = args[1];

            for (int i = 0; i < name.size(); ++i) {
                if (isalpha(name.at(i)) || name.at(i) == ' ') {
                    properName = true;
                }
                else {
                    properName = false;
                }
            }
            if (properName && idLength == 8 && !duplicate) {
                InsertNode(name, id, root);
                cout << "successful" << endl;
            }
            else {
                cout << "unsuccessful" << endl;
            }
        }
        //remove ID
        else if (args[0] == "remove") {
            bool sTree = false;
            RemoveID(stoi(args[1]), root, sTree);
            if (sTree) {
                RemoveID(stoi(args[1]), root, sTree);
            }

            SearchID(name, stoi(args[1]), root);

            if (name == "") {
                cout << "successful" << endl;
            }
            else {
                cout << "unsuccessful" << endl;
            }
        }
        //search ID
        //search NAME
        else if (args[0] == "search") {
            if (isalpha(args[1].at(0))) {
                bool found = false;
                SearchName(args[1], found, root);
                if (found == false) {
                    cout << "unsuccessful" << endl;
                }
            }
            else {
                SearchID(name, stoi(args[1]), root);

                if (name == "") {
                    cout << "unsuccessful" << endl;
                }
                else {
                    cout << name << endl;
                }

            }
        }
        //printInorder
        else if (args[0] == "printInorder") {
            string pName;
            PrintInOrder(root, pName);
            
            stringstream xstream(pName);
            getline(xstream, skip, ' ');
            getline(xstream, pName);

            cout << pName << endl;
        }
        //printPreorder
        else if (args[0] == "printPreorder") {
            string pName;
            PrintPreOrder(root, pName);

            stringstream xstream(pName);
            getline(xstream, skip, ' ');
            getline(xstream, pName);

            cout << pName << endl;
        }
        //printPostorder
        else if (args[0] == "printPostorder") {
            string pName;
            PrintPostOrder(root, pName);

            stringstream xstream(pName);
            getline(xstream, skip, ' ');
            getline(xstream, pName);

            cout << pName << endl;
        }
        //printLevelCount
        else if (args[0] == "printLevelCount") {
            if (root->GetID() == -1) {
                cout << 0 << endl;
            }
            else {
                cout << TreeHeight(root) << endl;
            }
        }
        //removeInorder
        else if (args[0] == "removeInorder") {
            
            int rID = -1;
            int counter = 0;
            int n = stoi(args[1]);

            RemoveInOrder(root, counter, rID, n);

            bool sTree = false;
            RemoveID(rID, root, sTree);
            if (sTree) {
                RemoveID(rID, root, sTree);
            }

            SearchID(name, rID, root);

            if (name == "" && rID != -1) {
                cout << "successful" << endl;
            }
            else {
                cout << "unsuccessful" << endl;
            }

        }
        
        //clears various variables in case they are holding something that could interfere in later loops.
        args.clear();
        input = "";
        intermediate = "";
        name = "";
        id = -1;

        while (!isAVL(root)) {}
    }

    return 0;
}