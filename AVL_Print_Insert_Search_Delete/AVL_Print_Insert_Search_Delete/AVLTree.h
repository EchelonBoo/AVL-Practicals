#pragma once
//for cout and cerr statements
#include <iostream>
#include <string>
using namespace std;

//Stores the Balance Factor as an enumerated type - Stores values in a specific range
typedef enum {
	LH,
	EH,
	RH
}BalanceFactor;

//struct to store the node in the AVL Tree
template <class ItemType>
struct TreeNode {
	ItemType info; //the string
	ItemType root; //the root
	TreeNode* right; //pointer to the right node
	TreeNode* left; //pointer to the left node
	BalanceFactor balf; //extra part of node - balance factor
};

//Class for tree
template <class ItemType>
class TreeType {
public:
	TreeType(); //function declaration for contructor
	~TreeType(); //function declaration for destructor
	void InsertItem(ItemType item); //function delaration for InsertItem
	void PrintItem(); //function declaration for print function
	void SearchItem(ItemType item); //function declaration for the Search function
	void DeleteItem(ItemType item);//function delaration for the Delete function

private:
	void Insert(TreeNode<ItemType>*& tree, ItemType item, bool& taller); //function declaration for insert function --> called in InsertItem()
	void RightBalance(TreeNode<ItemType>*& tree, bool& taller); //function declaration for RightBalance() --> Called in Insert()
	void LeftBalance(TreeNode<ItemType>*& tree, bool& taller);//function declaration for LeftBalance() --> Called in Insert()
	void Print(TreeNode<ItemType>*& tree); //function declaration for print function --> called in PrintItem() --> pass in a pointer to a reference of the root
	void Search(TreeNode<ItemType>*& tree, ItemType item);//function declaration for the search function --> called in SearchItem() --> pass in a pointer to a reference of the root and the item
	void Delete(TreeNode<ItemType>*& tree, ItemType item, bool& shorter);//function declaration for the delete function --> called in DeleteItem() -->pass in the root, item and a boolean for shorter
	void DeleteNode(TreeNode<ItemType>*& tree, bool& shorter);
	void GetPredecessor(TreeNode<ItemType>* tree, ItemType& data);
	void DelRightBalance(TreeNode<ItemType>*& tree, bool& shorter);
	void DelLeftBalance(TreeNode<ItemType>*& tree, bool& shorter);
	TreeNode<ItemType>* root; //pointer to the root
};

#pragma region Constructors
//Constructor Definition
template <class ItemType>
TreeType<ItemType>::TreeType() {
	root = NULL;
}

//Destructor Definition
template <class ItemType>
TreeType<ItemType>::~TreeType() {

}

#pragma endregion

#pragma region Insert Functions

//Calls the Insert function
template <class ItemType>
void TreeType<ItemType> ::InsertItem(ItemType item)
// Calls recursive function Insert to insert item into tree.
{
	bool taller = false;
	Insert(root, item, taller);
}

//Function Definition for the INsert function --> Called in InsertItem
template <class ItemType>
void TreeType<ItemType>::Insert(TreeNode<ItemType>*& tree, ItemType item, bool& taller)
// Inserts item into tree.				 
// Post:	item is in tree; search property is maintained.
{
	if (tree == NULL) {

		// Insertion place found.
		tree = new TreeNode<ItemType>;
		tree->left = NULL;
		tree->right = NULL;
		tree->info = item;
		tree->balf = EH;
		taller = true;

	}
	else if (item == tree->info) {

		cerr << "Duplicate key is not allowed in AVL tree." << endl;

	}
	else if (item < tree->info) {

		Insert(tree->left, item, taller);
		if (taller)
			switch (tree->balf)
			{
			case LH:
				LeftBalance(tree, taller);
				break;
			case EH:
				tree->balf = LH;
				break;
			case RH:
				tree->balf = EH; taller = false;
				break;
			}
	}
	else {
		Insert(tree->right, item, taller);// Insert into right subtree if (taller)
		switch (tree->balf)
		{
		case RH:
			RightBalance(tree, taller);
			break;
		case EH:
			tree->balf = RH;
			break;
		case LH:
			tree->balf = EH;
			taller = false;
			break;
		}
	}
}

#pragma endregion

#pragma region Balance Functions

//balances out a broken tree --> the root is double right high and the root of the right subtree is equal height --> not allowed
template <class ItemType>
void TreeType<ItemType>::RightBalance(TreeNode<ItemType>*& tree, bool& taller)
{
	TreeNode<ItemType>* rs = tree->right;
	TreeNode<ItemType>* ls;

	switch (rs->balf)
	{
	case RH:
		tree->balf = rs->balf = EH;
		RotateLeft(tree);
		taller = false;
		break;
	case EH:
		cerr << "Tree already balanced " << endl;
		break;
	case LH:
		ls = rs->left;
		switch (ls->balf)
		{
		case RH:
			tree->balf = LH;
			rs->balf = EH;
			break;
		case EH:
			tree->balf = rs->balf = EH;
			break;
		case LH:
			tree->balf = EH;
			rs->balf = RH;
			break;
		}
		ls->balf = EH;
		RotateRight(tree->right);
		RotateLeft(tree);
		taller = false;
	}
}

//opposite to RightBalance() -->balances out a broken tree --> the root is double left high and the root of the left subtree is equal height --> not allowed
template <class ItemType>
void TreeType<ItemType> ::LeftBalance(TreeNode<ItemType>*& tree, bool& taller)
{
	TreeNode<ItemType>* ls = tree->left;
	TreeNode<ItemType>* rs;

	switch (ls->balf)
	{
	case LH:
		tree->balf = ls->balf = EH;
		RotateRight(tree);
		taller = false;
		break;
	case EH:
		cerr << "Tree already balanced " << endl;
		break;
	case RH:
		rs = ls->right;

		switch (rs->balf)
		{
		case LH:
			tree->balf = RH;
			ls->balf = EH;
			break;
		case EH:
			tree->balf = ls->balf = EH;
			break;
		case RH:
			tree->balf = EH;
			ls->balf = LH;
			break;
		}

		rs->balf = EH;
		RotateLeft(tree->left);
		RotateRight(tree);
		taller = false;
	}
}

#pragma endregion

#pragma region Print Functions

//PrintAVL Definition --> calls the Print() function and passes it the root
template <class ItemType>
void TreeType<ItemType> ::PrintItem()
{
	Print(root);
}

//Print Definition 
template <class ItemType>
void TreeType<ItemType> ::Print(TreeNode<ItemType>*& tree)
{
	//if the tree is empty, do nothing
	if (tree == NULL) {
		return;
	}

	string balf, left, right;
	Print(tree->left); //calls the function with a pointer to the left node

	cout << "\t" << tree->info << ":\n"; //prints the string

	//Prints the left node if it is null
	if (tree->left == NULL)
	{
		left = "NULL";
		cout << "\n\t\tLeft: " << left;
	}
	else {//prints the string in the left node
		cout << "\n\t\tLeft: " << tree->left->info << "  ";
	}

	//prints the right node if it is null
	if (tree->right == NULL)
	{
		right = "NULL";
		cout << "\n\t\tRight: " << right;
	}
	else {//prints the string in the right node
		cout << "\n\t\tRight: " << tree->right->info << "  ";
	}

	//finds the balance factor
	switch (tree->balf) {
	case 0:
		balf = "LH\n";
		break;
	case 1:
		balf = "EH\n";
		break;
	case 2:
		balf = "RH\n";
		break;
	}

	cout << "\n\t\tBF: " << balf << endl; //prints the balance factor along with the string and left and right node contents

	Print(tree->right);//calls the function with a pointer to the right node
}

#pragma endregion

#pragma region Search Functions
template <class ItemType>
void TreeType<ItemType>::SearchItem(ItemType item) {
	Search(root, item);
}

template <class ItemType>
void TreeType<ItemType>::Search(TreeNode<ItemType>*& tree, ItemType item)
{
	//If the tree is  not empty
	if (tree != NULL)
	{
		if (item < tree->info) { //if the item being searched for is less that whats in the node, call the function again going to the next node to the left

			Search(tree->left, item);

		}
		else if (item > tree->info) {//if the item being searched for is less that whats in the node, call the function again going to the next node to the right

			Search(tree->right, item);

		}
		else { //eventually the item has to be found or not

			cout << "\nItem found in tree" << endl;

		}
	}
	else { // if the tree is empty there is nothing to search for
		cout << "\nItem not found in tree" << endl;
	}

}

#pragma endregion

#pragma region Delete Functions

template <class ItemType>
void TreeType<ItemType> ::DeleteItem(ItemType item) {
	// Calls recursive function Delete to delete item from tree.

	bool shorter;
	Delete(root, item, shorter);
}

template <class ItemType>
void TreeType<ItemType> ::Delete(TreeNode<ItemType>*& tree, ItemType item, bool& shorter) {
	if (tree != NULL)
	{
		if (item < tree->info)
		{
			Delete(tree->left, item, shorter);
			// Look in left subtree.
			if (shorter)
				switch (tree->balf)
				{
				case LH: tree->balf = EH; break;
				case EH: tree->balf = RH; shorter = false;
					break;
				case RH: DelRightBalance(tree, shorter);
				} // END SWITCH	
		}
		else if (item > tree->info)
		{
			Delete(tree->right, item, shorter);
			// Look in right subtree.
			if (shorter)
				switch (tree->balf)
				{
				case LH: DelLeftBalance(tree, shorter);
				break;				case EH: tree->balf = LH; shorter = false; 							break;
				case RH: tree->balf = EH; break;
				} // END SWITCH
		}
		else
			DeleteNode(tree, shorter);
		// Node found; call DeleteNode.
	} // END if (tree != NULL)
	else
	{
		cout << "\nNOTE: " << item
			<< " not in the tree so cannot be deleted.";
	}
}

template <class ItemType>
void TreeType<ItemType>::DeleteNode(TreeNode <ItemType>*& tree, bool& shorter)
// Delete the node pointed to by tree.
// Post: The user's data in the node pointed to by tree is no longer in the tree. // If tree is a leaf node or has only one non-NULL child pointer, the node 
// pointed to by tree is deleted; otherwise, the user's data is replaced by its
// logical predecessor and the predecessor's node is deleted.
{
	ItemType data;	TreeNode <ItemType>* tempPtr;
	tempPtr = tree;
	if (tree->left == NULL)
	{
		tree = tree->right;
		delete tempPtr;
		shorter = true;
	}
	else if (tree->right == NULL)
	{
		tree = tree->left;
		delete tempPtr;
		shorter = true;
	}
	else
	{
		GetPredecessor(tree, data);
		tree->info = data;
		Delete(tree->left, data, shorter);
		// Delete the predecessor node
		if (shorter)
			switch (tree->balf)
			{
			case LH: tree->balf = EH; break;
			case EH: tree->balf = RH; shorter = false;
				break;
			case RH: DelRightBalance(tree, shorter);
			}
	}
}

template <class ItemType>
void TreeType<ItemType>::GetPredecessor(TreeNode<ItemType>* tree, ItemType& data)
// Sets data to the info member of the right-most node in tree.
{
	tree = tree->left;
	while (tree->right != NULL)
		tree = tree->right;
	data = tree->info;
}

template <class ItemType>
void TreeType<ItemType>::DelRightBalance(TreeNode<ItemType>*& tree, bool& shorter)
{
	TreeNode<ItemType>* rs = tree->right;
	TreeNode<ItemType>* ls;
	switch (rs->balf)
	{
	case RH:	tree->balf = rs->balf = EH;
		RotateLeft(tree);
		shorter = true; break;
	case EH:	tree->balf = RH;
		rs->balf = LH;
		RotateLeft(tree);
		shorter = false; break;
	case LH:	ls = rs->left;
		switch (ls->balf)
		{
		case RH:	tree->balf = LH;
			rs->balf = EH; break;
		case EH:	tree->balf = rs->balf = EH;
			break;
		case LH:	tree->balf = EH;
			rs->balf = RH; break;
		} // END SWITCH

		ls->balf = EH;
		RotateRight(tree->right);
		RotateLeft(tree);
		shorter = true;
	}
}

template <class ItemType>
void TreeType<ItemType>::DelLeftBalance(TreeNode<ItemType>*& tree, bool& shorter)
{
	TreeNode<ItemType>* ls = tree->left;
	TreeNode<ItemType>* rs;
	switch (ls->balf)
	{
	case LH:	tree->balf = ls->balf = EH;
		RotateRight(tree);
		shorter = true; break;
	case EH:	tree->balf = LH;
		ls->balf = RH;
		RotateRight(tree);
		shorter = false; break;
	case RH:	rs = ls->right;
		switch (rs->balf)
		{
		case LH:	tree->balf = RH;
			ls->balf = EH; break;
		case EH:	tree->balf = ls->balf = EH;
			break;
		case RH:	tree->balf = EH;
			ls->balf = LH; break;
		} // END SWITCH
		rs->balf = EH;
		RotateLeft(tree->left);
		RotateRight(tree);
		shorter = true;
	}
}



#pragma endregion

#pragma region Rotate Functions
//Rotate Left Code --> The tree is right high --> the root is right high and the root of the right sub tree is right high
template <class ItemType>
void RotateLeft(TreeNode<ItemType>*& tree) {

	TreeNode<ItemType>* rs;

	if (tree == NULL) {
		cerr << "It is impossible to rotate an empty tree in RotateLeft" << endl;
	} //if the tree is empty, do nothing

	else if (tree->right == NULL) {
		cerr << "It is impossible to make an empty subtree the root in RotateLeft" << endl;
	}// if the node to the right of the root is empty, do nothing.

	else { //rotate the tree

		rs = tree->right;
		tree->right = rs->left;
		rs->left = tree;
		tree = rs;
	}
}

//Rotate Right Code --> The tree is left high --> the root is left high and the root of the left sub tree is right high
template <class ItemType>
void RotateRight(TreeNode<ItemType>*& tree) {

	TreeNode<ItemType>* ls;

	if (tree == NULL) {
		cerr << "It is impossible to rotate an empty tree in RotateRight" << endl;
	}// if the tree is empty, do nothing

	else if (tree->left == NULL) {
		cerr << "It is impossible to make an empty subtree the root in RotateRight" << endl;
	}//if the node to the left of the root is empty, do nothing

	else {//rotate the tree

		ls = tree->left;
		tree->left = ls->right;
		ls->right = tree;
		tree = ls;
	}
}

#pragma endregion