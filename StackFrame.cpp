#include "StackFrame.h"
#include <iostream>
#include <fstream>
#include "errors.h"
#include "constants.h"
using namespace std;





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
        
    };

    void deleteRightBalance(Node*& root, bool& shorter) {
        
    };

public:
    AVLTree() {
        this->root = NULL;
        count = 0;
    }

    //more func

    void insertNode(string key, float value, int type) {
        Node* insertPtr = new Node(key, value, type);
        bool taller = false;
        insertNodeRec(this->root, insertPtr, taller);
        return;
    }

    void deleteNode(string delKey) {
        bool success = false;
        bool shorter = false;
        deleteNodeRec(this->root, delKey, shorter, success);
        return;
    };

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
    };
};

StackFrame::StackFrame() : opStackMaxSize(OPERAND_STACK_MAX_SIZE), localVarSpaceSize(LOCAL_VARIABLE_SPACE_SIZE) {}

void StackFrame::run(string filename) {
    string mode;  // name of syntax
    string data;  // temporary string type before convert into suitable type
    int idata;    // integer variable
    float fdata;  // float variable
    int line = 1; // current line (start at 1)
    int err = 0;  // type of error

    fstream readfile; // interact with input file

    readfile.open(filename, ios::in); // open file in read mode

    readfile.close();
}