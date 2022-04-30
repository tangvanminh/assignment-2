#ifndef __STACK_FRAME_H__
#define __STACK_FRAME_H__

#include <string>

class AVLTree;
class Stack;


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
    bool ALargerThanB(std::string a, std::string b) {
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

    void deleteNodeRec(Node*& root, std::string delKey, bool& shorter, bool& success) {
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
        }
        else {
            root->balance = EH;
            rightTree->balance = RH;
        }
        leftTree->balance = EH;
        rotateRight(root->right);
        rotateLeft(root);
        taller = false;
        return;
    }

    void deleteLeftBalance(Node*& root, bool& shorter) {
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

    Node* takeNodeRec(Node* root, std::string key) {
        if (root == NULL) return NULL;
        if (root->key == key) {
            Node* result = new Node(root->key, root->value, root->type);
            return result;
        }
        else if (ALargerThanB(root->key, key)) {
            return takeNodeRec(root->left, key);
        }
        else {
            return takeNodeRec(root->right, key);
        }
    }

    void parentRec(Node* current, std::string key) {
        if(current->left == NULL){
            if (current->right->key == key) {
                printf("%s\n", current->key.c_str());
                return;
            }
        }
        if(current->right == NULL){
            if (current->left->key == key) {
                printf("%s\n", current->key.c_str());
                return;
            }
        }
        
        if (ALargerThanB(current->key, key)) {
            parentRec(current->left,key);
            return;
        }
        else {
            parentRec(current->right, key);
            return;
        }
    }

public:
    AVLTree() {
        this->root = NULL;
        count = 0;
    }

    //more func

    //error is not included
    void insertNode(std::string key, float value, int type) {
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

    void deleteNode(std::string delKey) {
        bool success = false;
        bool shorter = false;
        deleteNodeRec(this->root, delKey, shorter, success);
        if (success) {
            this->count--;
        }
        return;
    };

    Node* takeNode(std::string key) {
        Node* temp = takeNodeRec(this->root, key);
        if (temp != NULL) {
            deleteNode(temp->key);
        }
        return temp;
    }

    Node* findNode(std::string key) {
        Node* temp = takeNodeRec(this->root, key);
        return temp;
    }

    void parent(std::string key) {
        if (this->root->key == key) {
            printf("null\n");
            return;
        }
        parentRec(this->root, key);
        return;
    }

    int size() {
        return this->count;
    }

public:
    //class Node
    class Node {
    private:
        std::string key;
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
        Node(std::string key, float value, int type, Node* left = NULL, Node* right = NULL, balance_factor balance = EH) {
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

        void printNode() {
            if (this == NULL) {
                printf("wrong key \n");
            }
            else if (this->type == 0) {
                printf("%d\n", int(this->value));
            }
            else {
                printf("%f\n", this->value);
            }
            return;
        }

        float Value() {
            return this->value;
        }

        int Type() {
            return this->type;
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
    Stack() : head(NULL), count(0) {}

    int size() {
        return this->count;
    }

    void push(float value, int type) {
        Node* insertPtr = new Node(value, type);
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


    Node* Top() {
        Node* temp = new Node();
        *temp = *(this->head);
        return temp;
    }

    void printTop() {
        Node* print = this->Top();
        if (print == NULL) {
            printf("wrong key \n");
        }
        else if (print->type == 0) {
            printf("%d\n", int(print->value));
        }
        else {
            printf("%f\n", print->value);
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
        float value;
        int type;
        Node* next;
        friend class Stack;
    public:
        Node() {
            this->value = 0;
            this->type = 0;
            this->next = NULL;
        }

        Node(float value, int type, Node* next = NULL) {
            this->value = value;
            this->type = type;
            this->next = next;
        }

        ~Node() {
            this->next = NULL;
            this->type = 0;
            this->value = 0;
        }

        void operator = (Node node) {
            this->value = node.value;
            this->type = node.type;
            return;
        }


        float Value() {
            return this->value;
        }

        int Type() {
            return this->type;
        }

    };
};

/*
StackFrame declaration
*/
class StackFrame {
    int opStackMaxSize; // max size of operand stack
    int localVarSpaceSize; // size of local variable array
    AVLTree localVarSpace; //local veariable space
    Stack opStack;  //operand stack

public:
    /*
    Constructor of StackFrame
    */
    StackFrame();

    /*
    Run the method written in the testcase
    @param filename name of the file
    */
    void run(std::string filename);

    void error(int& err, int line);

    //arithmetic 

    void iAdd(int& err);

    void fAdd(int& err);

    void iSub(int& err);

    void fSub(int& err);

    void iMul(int& err);

    void fMul(int& err);

    void iDiv(int& err);

    void fDiv(int& err);

    void iRem(int& err);

    //Load and store instruction
    void iConst(int val, int& err);

    void fConst(float val, int& err);

    void iLoad(std::string key, int& err);

    void fLoad(std::string key, int& err);

    void iStore(std::string key, int& err);

    void fStore(std::string key, int& err);

    void ItoF(int& err);

    void FtoI(int& err);

    void toP(int& err);

    void Val(std::string key, int& err);

    void Par(std::string key, int& err);
};

#endif // !__STACK_FRAME_H__