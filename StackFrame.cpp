#include "StackFrame.h"
#include <iostream>
#include <fstream>
#include "errors.h"
#include "constants.h"
using namespace std;

//forward declaration

class AVLTree;
class Stack;

/*
error enum
*/
enum error_type {
    tmm = 1, // type mismatch
    dbz,     // divide by zero
    sfl,     // stack full
    smt,     // stack empty
    aoor,    // array out of range
    udv      // undefined variable
};


class AVLTree {
public:
    class Node;
    enum balance_factor { LH, EH, RH };

protected:
    Node* root;
    int count;

private:
    void rotateRight(Node*& root) {
        Node* temp = root->left;
        root->left = temp->right;
        temp->right = root;
        root = temp;
        return;
    }

    void rotateLeft(Node*& root) {
        Node* temp = root->right;
        root->right = temp->left;
        temp->left = root;
        root = temp;
        return;
    }

    //a>b?
    bool ALargerThanB(string a, string b) {
        int i = 0, j = 0;
        while (i < a.size() && j < b.size()) {
            if (a[i] < b[j]) return false;
            if (a[i] > b[j]) return true;
            i++, j++;
        }
        if (i == a.size())return false;
        return true;
    }

    void insertNodeRec(Node*& root, Node* insertPtr, bool& taller) {
        if (root == NULL) {
            root = insertPtr;
            taller = true;
            return;
        }
        //root->key > insertPtr->key
        if (ALargerThanB(root->key, insertPtr->key)) {
            insertNodeRec(root->left, insertPtr, taller);
            //left tree is taller
            if (taller) {
                if (root->balance == LH) {
                    leftBalance(root, taller);
                }
                else if (root->balance == EH) {
                    root->balance = LH;
                }
                else {
                    root->balance = EH;
                    taller = false;
                }
            }
        }
        else {
            insertNodeRec(root->right, insertPtr, taller);
            //right tree is taller
            if (taller) {
                if (root->balance == RH) {
                    rightBalance(root, taller);
                }
                else if (root->balance == EH) {
                    root->balance = RH;
                }
                else {
                    root->balance = EH;
                    taller = false;
                }
            }
        }
        return;
    }

    void deleteNodeRec(Node* &root, string delKey, bool& shorter, bool&success) {
        if (root == NULL) {
            success = false;
            shorter = false;
            return;
        }
        if (ALargerThanB(root->key, delKey)) {
            deleteNodeRec(root->left, delKey, shorter, success);
            if (shorter) {
                deleteRightBalance(root, shorter);
            }
        }
        else if (ALargerThanB(delKey, root->key)) {
            deleteNodeRec(root->right, delKey, shorter, success);
            if (shorter) {
                deleteLeftBalance(root, shorter);
            }
        }
        else {
            Node* deletePtr = root;
            if (root->right == NULL) {
                root = root->left;
                success = true;
                shorter = true;
                delete deletePtr;
                return;
            }
            else if (root->left == NULL) {
                root = root->right;
                success = true;
                shorter = true;
                delete deletePtr;
                return;
            }
            else {
                Node* exchangePtr = root->left;
                while (exchangePtr->right != NULL) {
                    exchangePtr = exchangePtr->right;
                }
                *root = *exchangePtr;
                deleteNodeRec(root->left, exchangePtr->key, shorter, success);
            }
        }
        return;
    }

    void leftBalance(Node*& root, bool& taller) {
        Node* leftTree = root->left;
        if (leftTree->balance == LH) {
            root->balance = EH;
            leftTree->balance = EH;
            rotateRight(root);
            taller = false;
            return;
        }
        else {
            Node* rightTree = leftTree->right;
            if (rightTree->balance == LH) {
                root->balance = RH;
                leftTree->balance = EH;
            }
            else if (rightTree->balance == EH) {
                root->balance = EH;
                leftTree->balance = EH;
            }
            else {
                root->balance = EH;
                leftTree->balance = LH;
            }
            rightTree->balance = EH;
            rotateLeft(root->left);
            rotateRight(root);
            taller = false;
            return;
        }
    }

    void rightBalance(Node*& root, bool& taller) {
        Node* rightTree = root->right;
        if (rightTree->balance == RH) {
            root->balance = EH;
            rightTree->balance = EH;
            rotateLeft(root);
            taller = false;
            return;
        }
        Node* leftTree = rightTree->left;
        if (leftTree->balance == RH) {
            root->balance = LH;
            rightTree->balance = EH;
        }
        else if (leftTree->balance == EH) {
            root->balance = EH;
            rightTree->balance = EH;
        }else{
            root->balance = EH;
            rightTree->balance = RH;
        }
        leftTree->balance = EH;
        rotateRight(root->right);
        rotateLeft(root);
        taller = false;
        return;
    }

    void deleteLeftBalance(Node* &root, bool& shorter) {
        if (root->balance == RH) {
            root->balance = EH;
        }
        else if (root->balance == EH) {
            root->balance = LH;
            shorter = false;
        }
        else {
            Node* leftTree = root->left;
            if (leftTree->balance == RH) {
                Node* rightTree = leftTree->right;
                if (rightTree->balance == RH) {
                    leftTree->balance = LH;
                    root->balance = EH;
                }
                else if (rightTree->balance == EH) {
                    leftTree->balance = EH;
                    root->balance = EH;
                }
                else {
                    leftTree->balance = EH;
                    root->balance = RH;
                }
                rightTree->balance = EH;
                rotateLeft(root->left);
                rotateRight(root);
                shorter = false;
            }
            else {
                if (leftTree->balance == EH) {
                    leftTree->balance = RH;
                    root->balance = LH;
                    shorter = false;
                }
                else {
                    root->balance = EH;
                    leftTree->balance = EH;
                }
                rotateRight(root);
            }
        }
        return;
    }

    void deleteRightBalance(Node*& root, bool& shorter) {
        if (root->balance == LH) {
            root->balance = EH;
        }
        else if (root->balance == EH) {
            root->balance = RH;
            shorter = false;
        }
        else {
            Node* rightTree = root->right;
            if (rightTree->balance == LH) {
                Node* leftTree = rightTree->left;
                if (leftTree->balance == LH) {
                    rightTree->balance = RH;
                    root->balance = EH;
                }
                else if (leftTree->balance == EH) {
                    rightTree->balance = EH;
                    root->balance = EH;
                }
                else {
                    rightTree->balance = EH;
                    root->balance = LH;
                }
                leftTree->balance = EH;
                rotateRight(root->right);
                rotateLeft(root);
                shorter = false;
            }
            else {
                if (rightTree->balance == EH) {
                    rightTree->balance = LH;
                    root->balance = RH;
                    shorter = false;
                }
                else {
                    root->balance = EH;
                    rightTree->balance = EH;
                }
                rotateRight(root);
            }
        }
        return;
    }

    Node* takeNodeRec(Node* root, string key) {
        if (root == NULL) return NULL;
        if (root->key == key) {
            return root;
        }
        else if (ALargerThanB(root->key, key)) {
            return takeNodeRec(root->left, key);
        }
        else {
            return takeNodeRec(root->right, key);
        }
    }

public:
    AVLTree() {
        this->root = NULL;
        count = 0;
    }

    //more func

    //error is not included
    void insertNode(string key, float value, int type) {
        Node* insertPtr = new Node(key, value, type);
        bool taller = false;
        insertNodeRec(this->root, insertPtr, taller);
        this->count++;
        return;
    }

    void insertNode(Node* insertPtr) {
        bool taller = false;
        insertNodeRec(this->root, insertPtr, taller);
        this->count++;
        return;
    }

    void insertNode(Stack::Node* stPtr) {
        Node* insertPtr = new Node();
        insertPtr->toAVLNode(stPtr);
        bool taller = false;
        insertNodeRec(this->root, insertPtr, taller);
        this->count++;
        return;
    }

    void deleteNode(string delKey) {
        bool success = false;
        bool shorter = false;
        deleteNodeRec(this->root, delKey, shorter, success);
        if (success) {
            this->count--;
        }
        return;
    };

    Node* takeNode(string key) {
        Node* temp = takeNodeRec(this->root, key);
        if (temp != NULL) {
            deleteNode(temp->key);
        }
        return temp;
    }

    void printVal(string key) {
        Node* print = takeNode(key);
        if (print == NULL) {
            cout << "wrong key" << endl;
        }
        else if (print->type == 0) {
            cout << int(print->value) << endl;
        }
        else {
            cout << print->value << endl;
        }
        return;
    }

    int size() {
        return this->count;
    }

public:
    //class Node
    class Node {
    private:
        string key;
        float value;
        int type;
        Node* left, * right;
        balance_factor balance;
        friend class AVLTree;
        friend class Stack::Node;
    public:
        Node() {
            this->type = 0;
            this->value = 0;
            this->balance = EH;
            this->left = this->right = NULL;
        }
        Node(string key, float value, int type, Node* left=NULL, Node* right=NULL,balance_factor balance =EH) {
            this->key = key;
            this->value = value;
            this->type = type;
            this->left = left;
            this->right = right;
            this->balance = balance;
        }
        
        ~Node() {
            this->key = "";
            this->value = 0;
            this->type = 0;
            this->left = this->right = NULL;
            this->balance = EH;
        }

        void operator = (Node exch) {
            this->key = exch.key;
            this->value = exch.value;
            this->type = exch.type;
        }

        void toAVLNode(Stack::Node* st) {
            this->key = st->key;
            this->value = st->value;
            this->type = st->type;
            return;
        }
    };
};

//use linked list to decribe stack
class Stack {
public:
    class Node;
    

protected:
    Node* head;
    int count;

public:
    Stack(): head(NULL), count(0) {}

    int size() {
        return this->count;
    }

    void push(string key, float value, int type) {
        Node* insertPtr = new Node(key,value,type);
        if (this->head == NULL) {
            this->head = insertPtr;
        }
        else {
            insertPtr->next = this->head;
            head = insertPtr;
        }
        this->count++;
        return;
    }

    void push(Node* insertPtr) {
        if (this->head == NULL) {
            this->head = insertPtr;
        }
        else {
            insertPtr->next = this->head;
            head = insertPtr;
        }
        this->count++;
        return;
    }

    void push(AVLTree::Node* avlPtr) {
        Node* insertPtr = new Node();
        insertPtr->toStackNode(avlPtr);
        if (this->head == NULL) {
            this->head = insertPtr;
        }
        else {
            insertPtr->next = this->head;
            head = insertPtr;
        }
        this->count++;
        return;
    }

    Node* top() {
        Node* temp = new Node();
        *temp = *(this->head);
        return temp;
    }

    void printTop() {
        Node* print = this->top();
        if (print == NULL) {
            cout << "stack empty" << endl;
        }
        else if (print->type == 0) {
            cout << int(print->value) << endl;
        }
        else {
            cout << print->value << endl;
        }
        return;
    }

    void pop() {
        Node* temp = head;
        head = head->next;
        delete temp;
        this->count--;
        return;
    }


    
public:
    class Node {
        string key;
        float value;
        int type;
        Node* next;
        friend class Stack;
        friend class AVLTree::Node;
    public:
        Node() {
            this->key = "";
            this->value = 0;
            this->type = 0;
            this->next = NULL;
        }

        Node(string key, float value, int type, Node* next = NULL) {
            this->key = key;
            this->value = value;
            this->type = type;
            this->next = next;
        }

        ~Node() {
            this->next = NULL;
            this->key = "";
            this->type = 0;
            this->value = 0;
        }

        void operator = (Node node) {
            this->key = node.key;
            this->value = node.value;
            this->type = node.type;
            return;
        }

        void toStackNode (const AVLTree::Node* avl) {
            this->key = avl->key;
            this->value = avl->value;
            this->type = avl->type;
            return;
        }
    };
};

StackFrame::StackFrame() : opStackMaxSize(OPERAND_STACK_MAX_SIZE), localVarSpaceSize(LOCAL_VARIABLE_SPACE_SIZE) {}

void StackFrame::run(string filename) {
    string mode;  // name of syntax
    string data;  // temporary string type before convert into suitable type
    int idata = 0;    // integer variable
    float fdata = 0;  // float variable
    int line = 1; // current line (start at 1)
    int err = 0;  // type of error

    fstream readfile; // interact with input file

    readfile.open(filename, ios::in); // open file in read mode

    readfile.close();

    Stack::Node* a = new Stack::Node();
    
}