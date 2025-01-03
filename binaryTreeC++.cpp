#include <iostream>
#include <queue>

using namespace std;

/*
A program that:

- Creates a binary tree
- Modifies a value in the binary tree
- Searches for a value in the binary tree
- Deletes a value in the binary tree

100% made by Erick Manetti, Python version along with my portfolio found at:
https://github.com/ManettiMV?tab=repositories
*/

template <typename T> // Makes it generic, allowing any variable type (string, int, etc.)
class Node {
public:
    T data;                     // Value of the node
    Node* left;                 // Pointer to the left node
    Node* right;                // Pointer to the right node
    Node(T value) : data(value), left(nullptr), right(nullptr) {} // Constructor
};

template <typename T>
class BinaryTree {
private:
    Node<T>* root; // Pointer to the root node

    // Recursive function to delete a node from the tree
    Node<T>* deleteRecursive(Node<T>* current, T value) {
        if (current == nullptr) { 
            cout << "The current node is already null" << endl;
            return nullptr; 
        }
        /*
            If the current node has the desired value, delete it and replace it with a child node
        */
        if (current->data == value) { 
            // Checks if the child node does not exist; if not, delete the current node without changes
            if (!current->left && !current->right) {
                cout << "Deleting leaf node: " << value << endl;
                delete current;
                return nullptr;
            
            // Otherwise, take the value from the child node to replace it
            } 
            if (current->left == nullptr){  // Left
                Node<T>* temp = current->right;
                delete current;
                return temp;
            }
            if (current->right == nullptr){ // Right
                Node<T>* temp = current->left;
                delete current;
                return temp;
            }

            // Finds the successor and replaces the current value with its value
            Node<T>* successor = nextNode(current->right);
            current->data = successor->data;
            current->right = deleteRecursive(current->right, successor->data);
        }else{
            // Continues the process further down the tree if the value is not found
            current->left = deleteRecursive(current->left, value);
            current->right = deleteRecursive(current->right, value);
        }
        return current; // Returns the current node if no match is found
    }

    Node<T>* nextNode(Node<T>* node){   // Always chooses the left child if it exists
        while (node->left != nullptr) node = node->left;
        return node;
    }

    bool searchRecursive(Node<T>* current, T value){    // Checks if the value exists in the tree
        if (current==nullptr){  // If the node we want to access does not exist, returns false
            return false;
        }
        if (current->data == value) {   // If the current node has the value we are looking for, return true
            return true;
        }
        // Recursively calls for the left and right subtrees
        bool exists = searchRecursive(current->left, value) || searchRecursive(current->right, value);
        return exists;  // Returns the resulting value of the recursive calls to check if it exists in the tree
    }

    void inorderRecursive(Node<T>* node){ 
        if (node != nullptr){   // If the current node is null, do not print anything
            T value = node->data;
            inorderRecursive(node->left);       // Visits the left subtree first
            cout << value << " ";               // Then prints the root
            inorderRecursive(node->right);      // Finally visits the right subtree
        }
    }

    void preorderRecursive(Node<T>* node){
        if (node != nullptr){   // If the current node is null, do not print anything
            T value = node->data;
            cout << value << " ";               // Prints the root first
            preorderRecursive(node->left);      // Then visits the left subtree
            preorderRecursive(node->right);     // Finally visits the right subtree
        }
    }
    
    void postorderRecursive(Node<T>* node){
        if (node != nullptr){   // If the current node is null, do not print anything
            T value = node->data;
            postorderRecursive(node->left);     // Visits the left subtree first
            postorderRecursive(node->right);    // Then the right subtree
            cout << value << " ";               // Finally prints the root
        }
    }

public:
    BinaryTree() : root(nullptr) {} // Constructor

    // Public method to delete values
    void remove(T value) {
        root = deleteRecursive(root, value);
    }

    
    void insertNode(T value) {  // Function to insert a node into the tree
        Node<T>* newNode = new Node<T>(value);

        if (root == nullptr) {  // Checks if the tree is empty
            root = newNode;    
            return;        
        }

        queue<Node<T>*> q;  // Creates a queue to perform a level-order traversal
        q.push(root);

        // Continues checking nodes until finding an available position
        while (!q.empty()) { 
            // Retrieves and removes the first node from the queue
            Node<T>* current = q.front();
            q.pop();

            // Checks if the left child of the current node is empty
            if (current->left == nullptr) { 
                current->left = newNode; // Inserts the new node as the left child
                return; // Returns as the new node is already inserted
            } else {
                q.push(current->left); // Adds the left child to the queue for future checking
            }

            // Checks if the right child of the current node is empty
            if (current->right == nullptr) {
                current->right = newNode; // Inserts the new node as the right child
                return; // Returns as the new node is already inserted
            } else {
                q.push(current->right); // Adds the right child to the queue for future checking
            }
        }
    }

    void deleteNode(T value){   // Deletes a node with a value T
        deleteRecursive(value);
    }  
    
    bool search(T value){   // Searches for a value in the tree and returns true or false if it exists
        return searchRecursive(root, value);
    }      

    void inorder(){     // Traverses in order: left -> root -> right
        inorderRecursive(root);
        cout << endl;
    }     
    void preorder(){    // Traverses in pre-order: root -> left -> right
        preorderRecursive(root);
        cout << endl;
    }           
    void postorder(){   // Traverses in post-order: left -> right -> root
        postorderRecursive(root);
        cout << endl;
    }                
};

int main() {
    BinaryTree<int> tree;

    // Initial message
    cout << "Testing binary tree..." << endl;

    // Inserting nodes
    cout << "Inserting values into the tree: 10, 20, 30, 40, 50" << endl;
    tree.insertNode(10);
    tree.insertNode(20);
    tree.insertNode(30);
    tree.insertNode(40);
    tree.insertNode(50);

    // Displaying the tree in different orders
    cout << "In-order traversal: ";
    tree.inorder();

    cout << "Pre-order traversal: ";
    tree.preorder();

    cout << "Post-order traversal: ";
    tree.postorder();

    // Searching for values
    cout << "Searching for value 20: " << (tree.search(20) ? "Found" : "Not found") << endl;
    cout << "Searching for value 60: " << (tree.search(60) ? "Found" : "Not found") << endl;

    // Removing nodes
    cout << "Removing value 20..." << endl;
    tree.remove(20);
    cout << "In-order traversal after removing 20: ";
    tree.inorder();

    cout << "Removing value 10 (root)..." << endl;
    tree.remove(10);
    cout << "In-order traversal after removing 10: ";
    tree.inorder();

    cout << "Attempting to remove value 100 (does not exist):" << endl;
    tree.remove(100);

    // Checking for an empty tree
    cout << "Removing all remaining values: 30, 40, 50" << endl;
    tree.remove(30);
    tree.remove(40);
    tree.remove(50);

    cout << "In-order traversal after removing all elements: ";
    tree.inorder();

    return 0;
}