#include <iostream>
#include <chrono>
#include <vector>
#include <Windows.h>


#define SET_CONSOLE_RED() SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
#define SET_CONSOLE_GREEN() SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
using namespace std;


class Node
{
public:
	int key;
	int height;
	Node* left;
	Node* right;

	Node(int k)
	{
		key = k;
		height = 1;
		left = nullptr;
		right = nullptr;
	}
};


class BSTTree
{
public:
	Node* root;

	BSTTree()
	{
		root = nullptr;
	}

	Node* insert(Node* node, int key)
	{
		auto newNode = new Node(key);

		if (root == nullptr)
		{
			root = newNode;
			return root;
		}

		Node* current = root;
		Node* parent = nullptr;

		while (current != nullptr)
		{
			parent = current;

			if (key < current->key)
			{
				current = current->left;
			}
			else
			{
				current = current->right;
			}
		}

		if (key < parent->key)
		{
			parent->left = newNode;
		}
		else
		{
			parent->right = newNode;
		}

		return root;
	}

	void insertConsecutiveElements(const vector<int> &sequence)
	{
		for (int i = 0; i < sequence.size(); i++)
		{
			root = insert(root, sequence[i]);
		}
	}

	vector<int>& findSmallest()
	{
		vector<int> path;
		Node* current = root;
		cout<<"Path is :";
		while (current != nullptr)
		{
			
			cout<<current->key<<" ";
			current = current->left;
			
		}

		return path;
	}

	int& findLargest() const
	{
		Node* current = root;
		int smalestval;
		//cout<<"Path is ";
		while (current != nullptr)
		{
			//cout<<current->key<<" ";
			if (current->right == nullptr)
			{
				smalestval = current->key;
				cout<<" Largest is "<<current->key<<endl;

			}
			current = current->right;

		}

		return smalestval ;
	}

	Node* minValueNode(Node* node)
	{
		Node* current = node;
		while (current->left != nullptr)
		{
			current = current->left;
		}
		return current;
	}

	Node* deleteNode(Node* root, int key)
	{
		if (root == nullptr)
		{
			return root;
		}

		if (key < root->key)
		{
			root->left = deleteNode(root->left, key);
		}
		else if (key > root->key)
		{
			root->right = deleteNode(root->right, key);
		}
		else
		{
			if (root->left == nullptr)
			{
				Node* temp = root->right;
				delete root;
				return temp;
			}
			if (root->right == nullptr)
			{
				Node* temp = root->left;
				delete root;
				return temp;
			}
			Node* temp = minValueNode(root->right);
			root->key = temp->key;
			root->right = deleteNode(root->right, temp->key);
		}

		return root;
	}

	void preorderTraversal(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		cout << root->key << " ";
		preorderTraversal(root->left);
		preorderTraversal(root->right);
	}

	void inorderTraversal(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		
		inorderTraversal(root->left);
		cout<<root->key<<" ";
		inorderTraversal(root->right);


		
	}
};


class AVLTree
{
public:
	Node* root;

	AVLTree()
	{
		root = nullptr;
	}

	int height(Node* node)
	{
		if (node == nullptr)
		{
			return 0;
		}
		return node->height;
	}

	int balanceFactor(Node* node)
	{
		if (node == nullptr)
		{
			return 0;
		}
		return height(node->left) - height(node->right);
	}


	Node* leftRotate(Node* node)
	{
		Node* newRoot = node->right;
		node->right = newRoot->left;
		newRoot->left = node;

		node->height = 1 + max(height(node->left), height(node->right));
		newRoot->height = 1 + max(height(newRoot->left), height(newRoot->right));

		return newRoot;
	}


	Node* rightRotate(Node* node)
	{
		Node* newRoot = node->left;
		node->left = newRoot->right;
		newRoot->right = node;

		node->height = 1 + max(height(node->left), height(node->right));
		newRoot->height = 1 + max(height(newRoot->left), height(newRoot->right));

		return newRoot;
	}


	Node* balance(Node* node)
	{
		int bf = balanceFactor(node);

		if (bf > 1)
		{
			if (balanceFactor(node->left) < 0)
			{
				node->left = leftRotate(node->left);
			}
			return rightRotate(node);
		}
		if (bf < -1)
		{
			if (balanceFactor(node->right) > 0)
			{
				node->right = rightRotate(node->right);
			}
			return leftRotate(node);
		}

		return node;
	}

	Node* insert(Node* node, int key)
	{
		if (node == nullptr)
		{
			return new Node(key);
		}

		if (key < node->key)
		{
			node->left = insert(node->left, key);
		}
		else if (key > node->key)
		{
			node->right = insert(node->right, key);
		}
		else
		{
			return node;
		}

		node->height = 1 + max(height(node->left), height(node->right));

		return balance(node);
	}


	void insertConsecutiveElements(vector<int>& sequence)
	{
		AVLTree tree;

		for (int i = 0; i < sequence.size(); i++)
		{
			root = insert(root, sequence[i]);
		}
	}


	vector<Node*> findSmallest()
	{
		vector<Node*> path;
		Node* current = root;

		while (current != nullptr)
		{
			path.push_back(current);
			current = current->left;
		}
		return path;
	}

	vector<Node*> findLargest()
	{
		vector<Node*> path;
		Node* current = root;

		while (current != nullptr)
		{
			path.push_back(current);
			current = current->right;
		}

		return path;
	}


	Node* minValueNode(Node* node)
	{
		Node* current = node;
		while (current->left != nullptr)
		{
			current = current->left;
		}
		return current;
	}

	int getBalance(Node* node)
	{
		if (node == nullptr)
		{
			return 0;
		}
		return height(node->left) - height(node->right);
	}


	void preorderTraversal(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		cout << root->key << " ";
		preorderTraversal(root->left);
		preorderTraversal(root->right);
	}


	void inorderTraversal(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		inorderTraversal(root->left);
		cout << root->key << " ";
		inorderTraversal(root->right);
	}

	Node* deleteNode(Node* root, int key)
	{
		if (root == nullptr)
		{
			return root;
		}
		if (key < root->key)
		{
			root->left = deleteNode(root->left, key);
		}
		else if (key > root->key)
		{
			root->right = deleteNode(root->right, key);
		}
		else
		{
			if (root->left == nullptr)
			{
				Node* temp = root->right;
				delete root;
				return temp;
			}
			if (root->right == nullptr)
			{
				Node* temp = root->left;
				delete root;
				return temp;
			}
			Node* temp = minValueNode(root->right);
			root->key = temp->key;
			root->right = deleteNode(root->right, temp->key);
		}

		root->height = 1 + max(height(root->left), height(root->right));
		int balance = getBalance(root);

		if (balance > 1 && getBalance(root->left) >= 0)
		{
			return rightRotate(root);
		}
		if (balance > 1 && getBalance(root->left) < 0)
		{
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}
		if (balance < -1 && getBalance(root->right) <= 0)
		{
			return leftRotate(root);
		}
		if (balance < -1 && getBalance(root->right) > 0)
		{
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}

		return root;
	}

	AVLTree deleteNodes(AVLTree tree)
	{
		int numNodes;
		vector<int> keysToDelete;

		cout << "Enter the number of nodes to delete: ";
		cin >> numNodes;

		for (int i = 0; i < numNodes; i++)
		{
			int key;
			cout << "Enter the key value of node " << i + 1 << ": ";
			cin >> key;
			keysToDelete.push_back(key);
		}

		for (int i = 0; i < keysToDelete.size(); i++)
		{
			tree.root = deleteNode(tree.root, keysToDelete[i]);
		}

		return tree;
	}
};


void searchForMaxInBST(BSTTree bstTree)
{
	bstTree.findLargest();
}

void searchForMinMaxInAVL(AVLTree avlTree)
{
	SET_CONSOLE_RED()
	vector<Node*> path = avlTree.findSmallest();
	cout << "Largest element: " << path.back()->key << endl;
	cout << "Path is: ";
	for (auto node : path)
	{
		cout << node->key << " ";
	}
	cout << endl;
	SET_CONSOLE_GREEN()
}

void deleteNodesOfBST(BSTTree& bstTree)
{
	SET_CONSOLE_RED()
	int key;
	while (true)
	{
		cout << "Enter key of node to delete (0 to exit): ";
		cin >> key;

		if (key == 0)
		{
			break;
		}

		bstTree.root = bstTree.deleteNode(bstTree.root, key);
		bstTree.inorderTraversal(bstTree.root);
		cout << endl;
	}
	SET_CONSOLE_GREEN()
}

void deleteNodesOfAVL(AVLTree& avlTree)
{
	SET_CONSOLE_RED()
	int key;
	while (true)
	{
		cout << "Enter key of node to delete (0 to exit): ";
		cin >> key;

		if (key == 0)
		{
			break;
		}

		Node* nodeToDelete = nullptr;
		Node* currentNode = avlTree.root;
		while (currentNode != nullptr)
		{
			if (key < currentNode->key)
			{
				currentNode = currentNode->left;
			}
			else if (key > currentNode->key)
			{
				currentNode = currentNode->right;
			}
			else
			{
				nodeToDelete = currentNode;
				break;
			}
		}

		if (nodeToDelete == nullptr)
		{
			cout << "Node with key " << key << " not found." << endl;
			continue;
		}

		avlTree.root = avlTree.deleteNode(avlTree.root, key);
		avlTree.inorderTraversal(avlTree.root);
		cout << endl;
	}
	SET_CONSOLE_GREEN()
}

void listAllElements(BSTTree bstTree, AVLTree avlTree)
{
	SET_CONSOLE_RED()
	cout << "In order BST Tree: ";
	bstTree.inorderTraversal(bstTree.root);
	cout << endl << "In order AVL Tree: ";
	avlTree.inorderTraversal(avlTree.root);
	cout << endl;

	cout << "Pre order BST Tree: ";
	bstTree.preorderTraversal(bstTree.root);
	cout << endl;
	cout << "Pre order AVL Tree: ";
	avlTree.preorderTraversal(avlTree.root);
	cout << endl;
	SET_CONSOLE_GREEN()
}


void deleteEntireTree(BSTTree& bstTree, AVLTree& avlTree)
{
	SET_CONSOLE_RED()
	bstTree.root = nullptr;
	avlTree.root = nullptr;
	cout << "Trees deleted." << endl;
	SET_CONSOLE_GREEN()
}

std::vector<int> generate_sequence(int n)
{
	std::vector<int> sequence(n);
	for (int i = 0; i < n; ++i)
	{
		sequence[i]= i;
	}
	return sequence;
}


void GetTime(BSTTree bstTree,AVLTree avlTree)
{
	
	
	cout << " Starting BST..." << endl;

	vector<double> timeofInorder_BST;
	vector<double> timeofInorder_AVL;
	vector<double> timeofFindMax_BST;
	vector<double> timeofFindMax_AVL;
	vector<double> timeofCreating_BST;
	vector<double> timeofCreating_AVL;



	vector<int> v1 = {100, 200, 500, 1000, 5000, 10000, 50000, 80000, 100000, 200000};
	for (int i = 0; i < 10; ++i)
	{
		const vector<int> sequence = generate_sequence(v1[i]);
		auto start = chrono::high_resolution_clock::now();
		bstTree.insertConsecutiveElements(sequence);
		cout<<endl;
		auto end = chrono::high_resolution_clock::now();
		cout << "Time of BST of size " << v1[i] << " is: " << chrono::duration_cast<chrono::duration<double, std::milli>>(end - start).count() << " ms " << endl;
		timeofCreating_BST.push_back(chrono::duration_cast<chrono::duration<double, std::milli>>(end - start).count());


		start = chrono::high_resolution_clock::now();
		bstTree.findLargest();
		cout<<endl;
		end = chrono::high_resolution_clock::now();
		cout << "Time of find BST Max is: " << std::chrono::duration<double, std::milli>(end - start).count() << " ms "	<< endl;
		timeofFindMax_BST.push_back( std::chrono::duration<double, std::milli>(end - start).count());

		start = chrono::high_resolution_clock::now();
		bstTree.inorderTraversal(bstTree.root);
		cout<<endl;
		end = chrono::high_resolution_clock::now();
		cout << "Time of inorder BST  is: " << chrono::duration_cast<chrono::duration<double, std::milli>>(end - start).count() << " ms " << endl;
		timeofInorder_BST.push_back(chrono::duration_cast<chrono::duration<double, std::milli>>(end - start).count());
	}

	cout << endl;
	cout << endl;
	SET_CONSOLE_RED()
	cout << " Starting AVL..." << endl;
	for (int i = 0; i < 10; ++i)
	{
		vector<int> sequence = generate_sequence(v1[i]);

		
		auto start = chrono::high_resolution_clock::now();
		avlTree.insertConsecutiveElements(sequence);
		auto end = chrono::high_resolution_clock::now();
		cout << "Time of AVL creating of size " << v1[i] << " is: " << chrono::duration_cast<chrono::duration<
			double, std::milli>>(end - start).count() << " ms " << endl;
		timeofCreating_AVL.push_back(chrono::duration_cast<chrono::duration<double, std::milli>>(end - start).count());

		start = chrono::high_resolution_clock::now();
		cout<<avlTree.findLargest().back()->key;
		end = chrono::high_resolution_clock::now();
		cout << "Time of AVL Max is: " << chrono::duration_cast<chrono::duration<double, std::milli>>(end - start).
			count() << " ms " << endl;
		timeofFindMax_AVL.push_back(chrono::duration_cast<chrono::duration<double, std::milli>>(end - start).count());


		start = chrono::high_resolution_clock::now();
		avlTree.inorderTraversal(avlTree.root);
		end = chrono::high_resolution_clock::now();
		cout << "Time of inorder AVL  is: " << chrono::duration_cast<chrono::duration<double, std::milli>>(end - start).
			count() << " ms " << endl;
		timeofInorder_AVL.push_back(chrono::duration_cast<chrono::duration<double, std::milli>>(end - start).count());
	}

	cout << endl;
	cout << endl;
	cout << endl;

	for (int q = 0; q < v1.size(); ++q)
	{
		cout << "Size = " << v1[q] << " Time BST inorder is" << timeofInorder_BST[q] << endl;
	}
	for (int q = 0; q < v1.size(); ++q)
	{
		cout << "Size = " << v1[q] << " Time AVL inorder is" << timeofInorder_AVL[q] << endl;
	}

	for (int q = 0; q < v1.size(); ++q)
	{
		cout << "Size = " << v1[q] << " Time BST creating is" << timeofCreating_BST[q] << endl;
	}
	for (int q = 0; q < v1.size(); ++q)
	{
		cout << "Size = " << v1[q] << " Time AVL creating is" << timeofCreating_AVL[q] << endl;
	}

	for (int q = 0; q < v1.size(); ++q)
	{
		cout << "Size = " << v1[q] << " Time BST find max is" << timeofFindMax_BST[q] << endl;
	}
	for (int q = 0; q < v1.size(); ++q)
	{
		cout << "Size = " << v1[q] << " Time AVL find max is" << timeofFindMax_AVL[q] << endl;
	}
}

int main()
{

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
	
	

	int option = 0;

	BSTTree bstTree;
	AVLTree avlTree;
	
	
		



	



	
	//##############################################################################
	vector<int>sequence;
	cout << "Enter Values:" << endl;
	int a;
	do
	{
		cin >> a;
		if (a != 0)
		{
			sequence.push_back(a);
		}
	}
	while (a != 0 && sequence.size() < 10);


	auto start = chrono::high_resolution_clock::now();
	bstTree.insertConsecutiveElements(sequence);
	auto end = chrono::high_resolution_clock::now();

	cout << "Time of BST is:" << chrono::duration_cast<chrono::duration<double>>(end - start).count() << endl;


	start = chrono::high_resolution_clock::now();
	avlTree.insertConsecutiveElements(sequence);
	end = chrono::high_resolution_clock::now();
	cout << "Time of AVL is:" << chrono::duration_cast<chrono::duration<double>>(end - start).count() << endl;

	do
	{
		cout << "Menu:" << endl;
		cout << "1. Search for highest and lowest elements in the BST tree" << endl;
		cout << "2. Search for highest and lowest elements in the AVL tree" << endl;
		cout << "3. Delete nodes from the BST tree" << endl;
		cout << "4. Delete nodes from the AVL tree" << endl;
		cout << "5. List all elements of the tree in in-order and pre-order order" << endl;
		cout << "6. Delete the entire tree element by element using the post-order method" << endl;
		cout << "7. Exit" << endl;
		cout << "8. Get time"<<endl;
		cout << "Enter an option: ";
		cin >> option;


		switch (option)
		{
		case 1:
			{
				SET_CONSOLE_RED()
				searchForMaxInBST(bstTree);
				SET_CONSOLE_GREEN()
				break;
			}
		case 2:
			{
				SET_CONSOLE_RED()
				searchForMinMaxInAVL(avlTree);
				
				
				SET_CONSOLE_GREEN()
				break;
			}
		case 3:
			{
				deleteNodesOfBST(bstTree);

				break;
			}
		case 4:
			{
				deleteNodesOfAVL(avlTree);
				break;
			}
		case 5:
			{
				SET_CONSOLE_RED()
				listAllElements(bstTree, avlTree);
				SET_CONSOLE_GREEN()
				break;
			}
		case 6:
			{
				deleteEntireTree(bstTree, avlTree);
				break;
			}
		case 7:
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
			cout << "Exiting..." << endl;
			SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
			break;
		case 8:
			GetTime(bstTree,avlTree);
		default:
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
			cout << "Invalid option. Try again." << endl;
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
			break;
		}
	}
	while (option != 7);
}

