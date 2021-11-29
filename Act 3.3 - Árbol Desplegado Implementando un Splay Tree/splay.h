/*
Author: Daniel Rodriguez Figueroa

A01612889

correcion act 3.3
*/

#include <string>
#include <sstream>

template <class T> class SplayTree;

template <class T>
class Node{

    public:

        Node(T);
        Node(T, Node<T>*, Node<T>*, Node<T>*);
        Node<T>* add(T);
        Node<T>* remove(T);
        Node<T>* find(T);
        void removeChilds();
        void inorder(std::stringstream&) const;
        void print_tree(std::stringstream&) const;
        void preorder(std::stringstream&) const;
        Node<T>* splay(Node<T>*, Node<T>*);

        friend class SplayTree<T>;

    private:

        T value;
        Node *left, *right, *parent;
        unsigned int count;
        Node<T> *succesor();
        Node<T> *rot_left(Node<T>*);
        Node<T> *rot_right(Node<T>*);
        
};

template <class T>
Node<T>::Node(T val) : value(val), left(0), right(0), parent(0) {}

template <class T>
Node<T>::Node(T val, Node<T> *le, Node<T> *ri, Node<T> *p):
    value(val), left(le), right(ri), parent(p) {}

template <class T>
Node<T>* Node<T>::add(T val){
    if (val < value){
		if (left != NULL){
			return left->add(val);
		} else{
			left = new Node<T>(val);
			left->parent = this;
			return left;
		}
	} else{
		if (right != NULL){
			return right->add(val);
		} else{
			right = new Node<T>(val);
			right->parent = this;
			return right;
		}
	}
}

template <class T>
Node<T>* Node<T>::remove(T val) {
	Node<T> *succ, *old;

	if (val < value){
		if (left != NULL) {
			if (left->value == val) {
				old = left;
				if(old->left != NULL && old->right != NULL){ 
					succ = left->succesor();
					if (succ != NULL) {
						succ->left = old->left;
						succ->right = old->right;
						succ->parent = old->parent;
						if(succ->left)
							succ->left->parent = succ;
						if(succ->right)
							succ->right->parent = succ;
					}
					left = succ;
				} else if (old->right != NULL){ 
					old->right->parent = left->parent;
					left = old->right;

				} else if (old->left != NULL){ 
					old->left->parent = left->parent;
					left = old->left;
				} else { 
					left = 0;
				}
				delete old;
				return this;
			} else {
				return left->remove(val);
			}
		}
	} else if (val > value) {
		if (right != NULL) {
			if (right->value == val) {
				old = right;
				if(old->left != NULL && old->right != NULL){ 
					succ = right->succesor();
					if (succ != NULL) {
						succ->left = old->left;
						succ->right = old->right;
						succ->parent = old->parent;
						if(succ->left)
							succ->left->parent = succ;
						if(succ->right)
							succ->right->parent = succ;
					}
					right = succ;
				} else if (old->right != NULL){ 
					old->right->parent = right->parent;
					right = old->right;

				} else if (old->left != NULL){ 
					old->left->parent = right->parent;
					right = old->left;
				} else {  
					right = NULL;
				}
				delete old;
				return this;
			} else {
				return right->remove(val);
			}
		}
	}
	return this; 
}

template <class T>
Node<T>* Node<T>::find(T val){
	if (val == value){
		return this;
	} else if (val < value){
		if (left != NULL){
            return left->find(val);
        } else{
            return this;
        }
	} else{
		if (right != NULL){
            return right->find(val);
        } else{
            return this;
        }	
	}
}

template <class T>
void Node<T>::removeChilds() {
	if (left != NULL) {
		left->removeChilds();
		delete left;
		left = NULL;
	}
	if (right != NULL) {
		right->removeChilds();
		delete right;
		right = NULL;
	}
}

template <class T>
Node<T>* Node<T>::succesor(){
	Node<T> *le, *ri;
	le = left;
	ri = right;

	if (right->left == NULL) {
		right = right->right;
		ri->right = NULL;
		return ri;
	}

	Node<T> *parent, *child;
	parent = right;
	child = right->left;
	while (child->left != NULL) {
		parent = child;
		child = child->left;
	}
	parent->left = child->right;
	child->right = NULL;
	return child;
}

template <class T>
Node<T>* Node<T>::rot_left(Node<T>* x){
	Node<T> *y = x->right;
	x->right = y->left;

	if(y->left)
		y->left->parent = x;

	y->left = x;
	y->parent = x->parent;
	x->parent = y;

	if(y->parent){
		if(y->parent->left && y->parent->left->value == x->value)
			y->parent->left = y;
		else
			y->parent->right = y;
	}
	return y;
}

template <class T>
Node<T>* Node<T>::rot_right(Node<T>* x){
	Node<T> *y = x->left;
	x->left = y->right;

	if(y->right)
		y->right->parent = x;

	y->right = x;
	y->parent = x->parent;
	x->parent = y;

	if(y->parent){
		if(y->parent->left && y->parent->left->value == x->value)
			y->parent->left = y;
		else
			y->parent->right = y;
	}
	return y;
}

template <class T>
Node<T>* Node<T>::splay(Node<T>* root, Node<T>* x){
	while(x->parent != NULL){

		if(x->parent->value == root->value){
			if(x->parent->left && x->parent->left->value == x->value){
				rot_right(x->parent);
			}else{
				rot_left(x->parent);
			}
		}else{
			Node<T>*p = x->parent; 
			Node<T>*g = p->parent;
			if(p->left && g->left &&
				x->value == p->left->value && p->value == g->left->value){
				rot_right(g);
				rot_right(p);
			}else if(p->right && g->right &&
				x->value == p->right->value && p->value == g->right->value){
				rot_left(g);
				rot_left(p);
			}else	if(p->left && g->right &&
				x->value == p->left->value && p->value == g->right->value){
				rot_right(p);
				rot_left(g);
			}else{
				rot_left(p);
				rot_right(g);
			}
		}
	}
	return x;
}

template <class T>
void Node<T>::inorder(std::stringstream &aux) const {
	if (left != NULL) {
		left->inorder(aux);
	}
	if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << value;
	if (right != NULL) {
		right->inorder(aux);
	}
}

template <class T>
void Node<T>::print_tree(std::stringstream &aux) const {
	if (parent != NULL){
		aux << "\n node " << value;
		aux << " parent " << parent->value;
	}else
		aux << "\n root " << value;
	if (left != NULL)
		aux << " left " << left->value;
	if (right != NULL)
		aux << " right " << right->value;
	aux << "\n";

	if (left != NULL) {
		left->print_tree(aux);
	}
	if (right != NULL) {
		right->print_tree(aux);
	}
}

template <class T>
void Node<T>::preorder(std::stringstream &aux) const {
	aux << value;
	if (left != NULL) {
		aux << " ";
		left->preorder(aux);
	}
	if (right != NULL) {
		aux << " ";
		right->preorder(aux);
	}
}

template <class T>
class SplayTree {
private:
	Node<T> *root;
	int count;

public:
	SplayTree();
	~SplayTree();
	bool empty() const;
    int size() const;
	void add(T);
	bool find(T);
	void remove(T);
	void removeAll();

    std::string preorder() const;
	std::string inorder() const;
	std::string print_tree() const;
};

template <class T>
SplayTree<T>::SplayTree() : root(0){
    count = 0;
}

template<class T>
SplayTree<T>::~SplayTree() {
	removeAll();
}

template<class T>
bool SplayTree<T>::empty() const{
	return (root == NULL);
}

template <class T>
int SplayTree<T>::size() const{
	return count;
}

template<class T>
void SplayTree<T>::add(T val){

	if(root != NULL){
		Node<T>* added = root->add(val);
		root = root->splay(root, added);
	}
    else{
		root = new Node<T>(val);
	}
	count++;
}

template <class T>
bool SplayTree<T>::find(T val){
	if (root != NULL) {
		Node<T>* found = root->find(val);
		root = root->splay(root,found);
		return (root->value == val);
	} else {
		return false;
	}
}

template <class T>
void SplayTree<T>::remove(T val) {
	if (root != NULL) {
		if (val == root->value) {
			Node<T> *succ = root->succesor();
			if (succ != NULL) {
					succ->left = root->left;
					succ->right = root->right;
					succ->parent = NULL;
					if(succ->left)
						succ->left->parent = succ;
					if(succ->right)
						succ->right->parent = succ;
			}
			delete root;
			root = succ;
		} else {
			Node<T>* p = root->remove(val);
			root = root->splay(root,p);
		}
	}
	count--;
}

template <class T>
void SplayTree<T>::removeAll() {
	if (root != NULL) {
		root->removeChilds();
	}
	delete root;
	root = 0;
	count = 0;
}

template <class T>
std::string SplayTree<T>::preorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->preorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string SplayTree<T>::inorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->inorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string SplayTree<T>::print_tree() const {
	std::stringstream aux;

	aux << "\n ================================ ";
	if (!empty()) {
		root->print_tree(aux);
	}
	aux << " ================================ \n";
	return aux.str();
}