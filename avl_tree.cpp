template<typename T>
class AVLTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        int height;

        Node(const T& val) : data(val), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    int height(Node* node) {
        if (node == nullptr) return 0;
        return node->height;
    }

    int balanceFactor(Node* node) {
        if (node == nullptr) return 0;
        return height(node->left) - height(node->right);
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = std::max(height(y->left), height(y->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = std::max(height(x->left), height(x->right)) + 1;
        y->height = std::max(height(y->left), height(y->right)) + 1;

        return y;
    }

    Node* insert(Node* node, const T& val) {
        if (node == nullptr) return new Node(val);

        if (val < node->data) {
            node->left = insert(node->left, val);
        } else if (val > node->data) {
            node->right = insert(node->right, val);
        } else {
            return node; // Duplicate values not allowed
        }

        node->height = 1 + std::max(height(node->left), height(node->right));

        int balance = balanceFactor(node);

        // Left Left Case
        if (balance > 1 && val < node->left->data) {
            return rightRotate(node);
        }

        // Right Right Case
        if (balance < -1 && val > node->right->data) {
            return leftRotate(node);
        }

        // Left Right Case
        if (balance > 1 && val > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && val < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    Node* deleteNode(Node* root, const T& key) {
        if (root == nullptr) return root;

        if (key < root->data) {
            root->left = deleteNode(root->left, key);
        } else if (key > root->data) {
            root->right = deleteNode(root->right, key);
        } else {
            if (root->left == nullptr || root->right == nullptr) {
                Node* temp = root->left ? root->left : root->right;
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else {
                    *root = *temp;
                }
                delete temp;
            } else {
                Node* temp = minValueNode(root->right);
                root->data = temp->data;
                root->right = deleteNode(root->right, temp->data);
            }
        }

        if (root == nullptr) return root;

        root->height = 1 + std::max(height(root->left), height(root->right));

        int balance = balanceFactor(root);

        if (balance > 1 && balanceFactor(root->left) >= 0) {
            return rightRotate(root);
        }

        if (balance > 1 && balanceFactor(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && balanceFactor(root->right) <= 0) {
            return leftRotate(root);
        }

        if (balance < -1 && balanceFactor(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    int countNodes(Node* node) {
        if (node == nullptr) return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    int countSmallerThan(Node* node, const T& val) {
        if (node == nullptr) return 0;
        if (node->data < val) {
            return 1 + countNodes(node->left) + countSmallerThan(node->right, val);
        } else {
            return countSmallerThan(node->left, val);
        }
    }

    int countLargerThan(Node* node, const T& val) {
        if (node == nullptr) return 0;
        if (node->data > val) {
            return 1 + countNodes(node->right) + countLargerThan(node->left, val);
        } else {
            return countLargerThan(node->right, val);
        }
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(const T& val) {
        root = insert(root, val);
    }

    void remove(const T& val) {
        root = deleteNode(root, val);
    }

    int count() {
        return countNodes(root);
    }

    int countSmaller(const T& val) {
        return countSmallerThan(root, val);
    }

    int countLarger(const T& val) {
        return countLargerThan(root, val);
    }

    void inorderTraversal() {
        inorderTraversal(root);
    }

    void inorderTraversal(Node* node) {
        if (node == nullptr) return;
        inorderTraversal(node->left);
        std::cout << node->data << " ";
        inorderTraversal(node->right);
    }
};