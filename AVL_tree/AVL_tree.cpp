	#include<iostream>
	#include<conio.h>
	using namespace std;

	class AVL_node_tree {
	public:
		int value;
		AVL_node_tree* left_child;
		AVL_node_tree* right_child;
		int height;
		~AVL_node_tree();
		AVL_node_tree(int value);
	};

	AVL_node_tree::~AVL_node_tree() {

	}

	AVL_node_tree::AVL_node_tree(int node_value) {
		this->value = node_value;
		this->left_child = nullptr;
		this->right_child = nullptr;
		this->height = 1;
	}

//==================================================================================================================

	int height(AVL_node_tree* node) {
		if (node == nullptr) {
			return 0;
		}
		else {
			return node->height;
		}
	}

//==================================================================================================================

	int max(int x, int y) {
		return (x > y) ? x : y;
	}


	AVL_node_tree* new_node(int value) {
		AVL_node_tree* node = new AVL_node_tree(value);
		return node;
	}

//==================================================================================================================

	AVL_node_tree* right_rotate(AVL_node_tree* ynode) {

		AVL_node_tree* xnode = ynode->left_child;

		AVL_node_tree* T2 = xnode->right_child;

		ynode->height = max(height(ynode->left_child), height((ynode->right_child + 1)));

		xnode->height = max(height(xnode->left_child), height((xnode->right_child + 1)));
		
		return xnode;
	}

//==================================================================================================================
	
	AVL_node_tree* left_rotate(AVL_node_tree* xnode) {

		AVL_node_tree* ynode = xnode->right_child;

		AVL_node_tree* T2 = ynode->left_child;

		xnode->height = max(height(xnode->left_child), height((xnode->right_child + 1)));

		ynode->height = max(height(ynode->left_child), height((ynode->right_child + 1)));

		return ynode;
	}

//==================================================================================================================
	
	int get_balance(AVL_node_tree* node) {
		if (node == nullptr) {
			return 0;
		}
		else {
			return (height(node->left_child) - height(node->right_child));
		}
	}

//==================================================================================================================

	AVL_node_tree* main_value_node(AVL_node_tree* node) {

		AVL_node_tree* currect = node;

		while (currect->left_child != nullptr) {

			currect = currect->left_child;
		}

		return currect;
	}

//==================================================================================================================
	AVL_node_tree* insert(AVL_node_tree* node, int value) {

		if (node == nullptr) {

			return (new AVL_node_tree(value));
		}

		if (value < node->value) {
			node->left_child = insert(node->left_child, value);
		}

		else
			if (value > node->value) {
				node->right_child = insert(node->right_child, value);
			}

		else
			return node;

		node->height = 1 + max(height(node->left_child), height(node->right_child));

		int balance = get_balance(node);

		if (balance > 1 && value < node->right_child->value) {

			return right_rotate(node);
		}
		if (balance<-1 && value > node->left_child->value) {

			return left_rotate(node);
		}

		if (balance > 1 && value > node->right_child->value) {

			node->left_child = left_rotate(node->left_child);

			return right_rotate(node);
		}

		if (balance<-1 && value<node->left_child->value) {

			node->right_child = right_rotate(node->right_child);

			return left_rotate(node);
		}

		return node;
	}

//==================================================================================================================
	
	AVL_node_tree* delete_node(AVL_node_tree* root, int value) {

		if (root == nullptr) {
			return root;
		}

		if (value < root->value) {

			root->left_child = delete_node(root->left_child, value);

		}

		else if (value > root->value) {

			root->right_child = delete_node(root->right_child, value);

		}

		else {

			if (root->left_child == nullptr || root->right_child == nullptr) {

				AVL_node_tree* tmp = root->left_child ? root->left_child : root->right_child;

				if (tmp == nullptr) {
					tmp = root;
					root = nullptr;
				}

				else
					*root = *tmp;
				free(tmp);

			}

			else {

				AVL_node_tree* tmp = main_value_node(root->right_child);

				root->value = tmp->value;

				root->right_child = delete_node(root->right_child, tmp->value);

			}
		}

		if (root == nullptr) {

			return root;

		}

		root->height = 1 + max(height(root->left_child), height(root->right_child));

		int balance = get_balance(root);

		if (balance > 1 && get_balance(root->left_child) >= 0) {

			return right_rotate(root);

		}

		if (balance > 1 && get_balance(root->left_child) < 0) {

			root->left_child = left_rotate(root->left_child);

			return right_rotate(root);
		}

		if (balance < -1 && get_balance(root->right_child) <= 0) {

			return left_rotate(root);

		}

		if (balance < -1 && get_balance(root->right_child) > 0) {

			root->right_child = right_rotate(root->right_child);

			return left_rotate(root);

		}

		return root;
	}

//==================================================================================================================

	void pre_order(AVL_node_tree* root) {

		if (root != nullptr) {

			cout << root->value << " ";
			pre_order(root->left_child);
			pre_order(root->right_child);

		}
	}

//==================================================================================================================

	class AVL_tree {
	public:
		AVL_node_tree* root;
		~AVL_tree();
		AVL_tree(AVL_node_tree* node);
	};

	AVL_tree::~AVL_tree() {

	}

	AVL_tree::AVL_tree(AVL_node_tree* node) {
		this->root = node;
	}

//==================================================================================================================

	int main() {
	
		return 0;
	}

//==================================================E N D==================================================