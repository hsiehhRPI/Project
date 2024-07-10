/* ASSUMPTIONS:
1. When a node must be split and has an odd number of keys, the extra key will go to the new right-hand node.
2. There will never be a duplicate key passed to insert.
*/
#include <iostream>
#include <ostream>
#include <vector>

#ifndef DS_BPLUSTREE
#define DS_BPLUSTREE

///////////////////////////////////////////////////////////////////////////////
//DO NOT CHANGE THIS CODE
///////////////////////////////////////////////////////////////////////////////

//Do not implement the class here, this is a forward declaration. Implement at
//the bottom of the .h file
template <class T> class BPlusTree; 

template <class T>
class BPlusTreeNode{
public:
	BPlusTreeNode() : parent() {};
	bool is_leaf();
	bool contains(const T& key);

	//For grading only. This is bad practice to have, because
	//it exposes a private member variable.
	BPlusTreeNode* get_parent() { return parent; } 

	//We need this to let BPlusTree access private members
	friend class BPlusTree<T>; 
private:
	bool contains(const T& key,std::size_t low,std::size_t high);
	std::vector<T> keys;
	std::vector<BPlusTreeNode*> children;
	BPlusTreeNode* parent;
};

template <class T>
bool BPlusTreeNode<T>::is_leaf(){
	for(unsigned int i=0; i<children.size(); i++){
		if(children[i]){
			return false;
		}
	}
	return true;
}

template <class T>
bool BPlusTreeNode<T>::contains(const T& key){
	return contains(key,0,keys.size()-1);
}

//Private method takes advantage of the fact keys are sorted
template <class T>
bool BPlusTreeNode<T>::contains(const T& key,std::size_t low,std::size_t high){
	if(low>high){
		return false;
	}
	if(low==high){
		return key == keys[low];
	}
	std::size_t mid = (low+high)/2;
	if(key<=keys[mid]){
		return contains(key,0,mid);
	}
	else{
		return contains(key,mid+1,high);
	}
}

///////////////////////////////////////////////////////////////////////////////////////
//Your BPlusTree implementation goes below this point.
///////////////////////////////////////////////////////////////////////////////////////
//Declaration of BPlusTree class:
template <class T> class BPlusTree {
public:
	//CONSTRUCTOR`
	BPlusTree (int bVal_) : root(NULL) {
		bVal = bVal_ ;
		rSyb = NULL;
		lSyb = NULL;
	}
	BPlusTree (const BPlusTree<T>& old) {
		bVal = old.bVal;
		if (old == NULL) {
			root = NULL;
			return;
		}
		else {
			copy_tree(old->root, 0);
			return;
		}

	}
	//ACCESSOR(I later realized that we might only need this in printing)
	BPlusTreeNode<T>* getRoot() {return root;}
	unsigned long int getBval() {return bVal;}
	std::vector<T> getKeys() {return root->keys;}
	std::vector<T> getChildren() {return root->children;}
	//OTHER FUNCTIONS

	//Helper function for the copy constructor
	BPlusTreeNode<T>* copy_tree(BPlusTreeNode<T>* old, int counter) {
		/*
		BPlusTreeNode<T>* nRoot = BPlusTreeNode<T>();
		for (int n = 0; n < old->keys.size(); n++) {
			nRoot->keys.push_back(old->keys[n]);
		}
		for (int g = 0; g < old->children.size(); g++) {
			nRoot->children.push_back(old->children[g]);
			nRoot->children[g]->parent = nRoot;
		}
		nRoot->children[counter]=copy_tree(nRoot->children[counter],counter);
		*/
	}

	//Insert function, impliment outside of the class(see below)
	void insert(T key);

	//Helper function of find function
	BPlusTreeNode<T>* findNext(BPlusTreeNode<T>* branch, const T& target) {
		//BASE_CASE1(the node you are at contains the target value and it does not have any children)
		if (branch->contains(target) == true && branch->is_leaf() == true) {
			return branch;
		}
		//BASE_CASE2(the supposed node location is reached, but value not found, implying value not in tree) 
		if (branch->contains(target) != true && branch->is_leaf() == true) {
			return NULL;
		}
		//GENERAL_CASE(node you are on is not the target node and you are not on a leaf node)
		int hold = 0;
		for (int h = 0; h < root->keys.size(); h++) {
			if (target < root->keys[h]) {
				//Search to the left
				findNext(root->children[h], target);
			}
			else{
				findNext(root->children[h+1], target);
			}
		}
	} 

	BPlusTreeNode<T>* find(const T& key) {
		//Base case 0: Tree is empty(return NULL)
		if (!root) {
			return NULL;
		}
		else {
			findNext(root, key);
		}
	}

	std::ostream print_sideways (std::ostream outfile);
	std::ostream print_BFS (std::ostream outfile);
	std::ostream print_BFS_pretty(std::ostream outfile);
	//Helper functions for myself
	void splitNode (BPlusTree toSplit);
	//DESTRUCTOR
	~BPlusTree() {
		timber(root);
		delete root;
	}
	//Destroy Function(in all honesty, I had problem traversing the tree)
	void timber(BPlusTreeNode<T>* root) {
		if (!root) {
			return;
		}
		//Ideally, it is gonna go through the first layers 
		if (root->is_leaf()==true) {
			root->keys.clear();
			/*root = root->parent;
			for (int n = 0; n < root->children.size();n++) {
				delete root->children[n];
			}
			timber(root->parent);*/
		}
	}

private:
	//
	BPlusTreeNode<T>* root;
	BPlusTreeNode<T>* lSyb;
	BPlusTreeNode<T>* rSyb;
	// The B value, determines how many value contained until we should split the branch
	unsigned long int bVal;
};

//Helper class: split
template <class T>
void split(BPlusTreeNode<T>* root, T& val) {
	//Base case 1: The root currently does not have a parent, add a parent to the root
	if (root->parent == NULL) {
		//Determine which value to be pushed to the parent
		BPlusTreeNode<T>* nCh = new BPlusTreeNode<T>();
		nCh->keys.push_back(val);
		nCh->parent = root;
		int hold = 0;
		for (int y = 0; y < root->keys.size(); y++) {
			hold = y;
			if (val < root->keys[y]) {
				//We cannot use the usual .insert() anymore, so we will have to move all the values back by 1 instead to make space
				for (int x = hold; x < root->keys.size(); x++) {
					root->keys[x+1] = root->keys[x]; 
					root->children[x+1] = root->children[x];
				}
			}
		}
		root->keys[hold] = val;
		root->children[hold] = nCh;

		int addV = root->keys.size()/2;
		BPlusTreeNode<T>* nRoot = new BPlusTreeNode<T>(root->keys[addV]);
		//Establish connection of og root to new root
		root->parent = nRoot;
		//Clean up the now appended value and split the branch to two
		//Make one new node, each gonna be the child for the later half(cause we could just pushback instead of insert)
		BPlusTreeNode<T>* otherChild = new BPlusTreeNode<T>();
		for (int n = hold; n < root->keys.size(); n++) {
			otherChild->keys.push_back(root->keys[n]);
		}
		std::vector<T> vHold;
		//clearing the first node, adding only needed values back in
		root->keys.clear();
		for (int y = 0; y < hold; y++) {
			root->keys.push_back(vHold[y]);
		}
		for (int g = 0; g < root->keys.size(); g++) {
			vHold.push_back(root->keys[g]);
		}
		for (int p = hold; p < root->children.size(); p++) {
			otherChild->children.push_back(root->children[p]);
			delete root->children[p];
		}
		//Estaboish connection between the newly formed root and the parent
		otherChild->parent = nRoot;
		//Now that things are cleaned up, add both nodes as child of the new root
		nRoot->children.push_back(root);
		nRoot->children.push_back(otherChild);
		root = nRoot;
		return;
	}
	//Base case: appending this value will not cause split anymore
	if (root->parent->children.size() < root->parent->bVal-2) {
		BPlusTreeNode<T>* nCh = new BPlusTreeNode<T>();
		nCh->keys.push_back(val);
		nCh->parent = root;
		//Determine which value to be pushed to the parent
		int hold = 0;
		for (int y = 0; y < root->keys.size(); y++) {
			hold = y;
			if (val < root->keys[y]) {
				//We cannot use the usual .insert() anymore, so we will have to move all the values back by 1 instead to make space
				for (int x = hold; x < root->keys.size(); x++) {
					root->keys[x+1] = root->keys[x]; 
					root->children[x+1] = root->children[x];
				}
			}
		}
		root->keys[hold] = val;
		root->children[hold] = nCh;
		//Now add them to the new parent
		int addV = root->keys.size()/2;
		BPlusTreeNode<T>* nRoot = new BPlusTreeNode<T>(root->keys[addV]);
		BPlusTreeNode<T>* otherChild = new BPlusTreeNode<T>();
		for (int n = hold; n < root->keys.size(); n++) {
			otherChild->keys.push_back(root->keys[n]);
		}
		std::vector<T> vHold;
		//clearing the first node, adding only needed values back in
		root->keys.clear();
		for (int y = 0; y < hold; y++) {
			root->keys.push_back(vHold[y]);
		}
		for (int g = 0; g < root->keys.size(); g++) {
			vHold.push_back(root->keys[g]);
		}
		for (int p = hold; p < root->children.size(); p++) {
			otherChild->children.push_back(root->children[p]);
			delete root->children[p];
		}
		//Estaboish connection between the newly formed root and the parent
		otherChild->parent = root->parent;
		//Now that things are cleaned up, add both nodes as child of the new root
		root->parent->children.push_back(root);
		root->parent->children.push_back(otherChild);
	}
	//General Case: split the parent
	if (root->parent->children.size() < root->parent->bVal-2) {
		for (int n = 0; n < root->children.size(); n++) {
			split(root->parent);
		}
	}
}

template<class T>
void BPlusTree<T>::insert(T key) {
	//There are a few scenario we must consider
	//Base case: the vector of root is less than bVal, where inserting this value will not make a new BPlusTreeNode
	//Vectors are unsorted, so we will have to find an index to insert it to

	//BASE_CASE(If tree is empty, there are space to add however we want, make the new node as the root of the tree)
	if (root == NULL) {
		BPlusTreeNode<T>* branch = new BPlusTreeNode<T>();
		root = branch;
		root->keys.push_back(key);
		//Establish relationship between the branch and its parent(root)
		//Insert it to the vector of the root
		//There is something wrong here
	}
	//CASE1(There are still space to add the node and the tree won't split) 
	//We need to make sure all of the children of said node is are leaves, somehow...
	if (root->is_leaf() == false && root->children.size() < bVal-1) {
		int hold = 0;
		for (int y = 0; y < root->keys.size(); y++) {
			hold = y;
			if (key < root->keys[y]) {
				//We cannot use the usual .insert() anymore, so we will have to move all the values back by 1 instead to make space
				for (int x = hold; x < root->keys.size(); x++) {
					root->keys[x+1] = root->keys[x]; 
				}
			}
		}
		BPlusTreeNode<T>* branch = new BPlusTreeNode<T>();
		branch->parent = root;
		root->children[hold] = branch;
		root->keys[hold] = key;
	}
	//CASE2: Addition of this child will definitely cause the tree to split 
	if (root->children.size() == bVal-1) {
		//split(root, key); <----This doesn't really work
	}

}

//Helper function, since all the children are BPlusTreeNode and not BPlusTree

template<class T>
std::ostream  BPlusTree<T>::print_sideways (std::ostream outfile) {
	//Every new value is on a new line
	if (!root) {
		outfile << "Tree is empty." << std::endl;
	}
	/*
	if (root->is_leaf()==false) {
		for (int n = 0; n < root->keys.size(); n++) {
		outfile <<root->keys[n]<<std::endl;
		}
		print_BFS(outfile);
	}
	if (root->is_leaf()==true) {
		return outfile;
	}*/
}
template<class T>
std::ostream  BPlusTree<T>::print_BFS (std::ostream outfile) {
	//Print it horizontal, all the childrens of the same node is on one line
	if (!root) {
		outfile << "Tree is empty." << std::endl;
	}
	/*
	if (root->is_leaf()==false) {
		for (int n = 0; n < root->keys.size(); n++) {
		outfile <<"    "<<root->keys[n] <<"    ";
		}
		outfile<<std::endl;
		print_BFS(outfile);
	}
	if (root->is_leaf()==true) {
		return outfile;
	}*/
	
}
template<class T>
std::ostream  BPlusTree<T>::print_BFS_pretty(std::ostream outfile) {
	//Omit the space between the printing
	if (!root) {
		outfile << "Tree is empty." << std::endl;
	}
	/*
	if (root->is_leaf()==false) {
		for (int n = 0; n < root->keys.size(); n++) {
		outfile <<root->keys[n];
		}
		outfile<<std::endl;
		print_BFS(outfile);
	}
	if (root->is_leaf()==true) {
		return outfile;
	}*/

}
#endif
