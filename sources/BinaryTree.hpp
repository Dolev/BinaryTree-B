#pragma once
#include <iostream>
#include <vector>
// using this site : https://www.cs.odu.edu/~zeil/cs361/latest/Public/treetraversal/index.html
//  using this site : https://caiorss.github.io/C-Cpp-Notes/STL%20Iterators%20and%20Algorithms.html
//using namespace std;

namespace ariel {

	template <typename T>
	class BinaryTree {

		class Node { //        subclass Node
				//friend class BinaryTree;	
		public:
			T data;
			Node* left = nullptr;
			Node* right = nullptr;
			Node* parent = nullptr;

			Node(const T x) : parent(nullptr), left(nullptr), right(nullptr), data(x) {}
            ~Node() {
				if (left) {delete left;};
				if (right) {delete right;};
			} // recursive
			void setData(const T& temp) {
				data = temp;
			}
			T getData() {
				return this->data;
			}
            //          fixxing code for make tidy
            Node(const Node& other){
            }
            Node& operator=(Node other)
            { 
                 return *this;
            }
            Node ( Node && obj) noexcept{           //      helped by stak over flow
            }
            Node& operator=(Node&& other) noexcept {
                  return *this;
            }
            //
		};

		Node* root;

	public:

		BinaryTree() :root(nullptr) {}
		/*	~BinaryTree() {
				free(root);
			}*/
        ~BinaryTree(){}
		BinaryTree& add_root(T newRootVal) {
			if (root != nullptr) {
				root->setData(newRootVal);
				return *this;
			}
			root = new Node(newRootVal);
			return *this;
		}

		BinaryTree& add_left(T Parent_val, T Left_val) {
			Node* result = find(root, Parent_val);
			if (result != nullptr)
			{
				if (result->left != nullptr)
				{
					result->left->setData(Left_val);
				}
				else {
					result->left = new Node(Left_val);
				}
			}
			else {
				throw std::invalid_argument("Value dosen't exists");
			}
			return *this;
		}
		BinaryTree& add_right(T Parent_val, T Right_val) {
			Node* result = find(root, Parent_val);
			if (result != nullptr)
			{
				if (result->right != nullptr)
				{
					result->right->setData(Right_val);
				}
				else {
					result->right = new Node(Right_val);
				}
			}
			else {
				throw std::invalid_argument("Value dosen't exists");
			}
			return *this;
		}

		Node* find(Node* node, T value) { // add find()
			if (node == nullptr)
			{
				return nullptr;
			}
			if (node->data == value)
			{
				return node;
			}
			Node* leftNode = find(node->left, value);
			if (leftNode != nullptr)
			{
				return leftNode;
			}
			Node* rightNode = find(node->right, value);
			return rightNode;
		}
/*---------------------------------------------------------------------------------------------------------*/

		class PreorderIterator {				//        subclass Preorder Iterator
		private:									//         (parent - left  - right)
			std::vector <Node*> preVector;
			size_t preVectorIndex = 0;

		public:
			PreorderIterator(Node* node = nullptr) {
				if (node != nullptr)
				{
					fillVector(node);
				}
				preVector.push_back(nullptr);
			}
			void fillVector(Node* node)
			{
				if (node == nullptr) {
					return;
				}
				preVector.push_back(node);
				fillVector(node->left);
				fillVector(node->right);
			}
			
            

			bool operator != (const PreorderIterator& other) { //  Done
				return preVector.at(preVectorIndex) != other.preVector.at(other.preVectorIndex);
			}
			// comparison operators. just compare node pointers
			bool operator == (const PreorderIterator& other) { //  Done
				return preVector.at(preVectorIndex) == other.preVector.at(other.preVectorIndex);
			}

			// the value pointed to by nodePtr
			T& operator * () const {
				return preVector[preVectorIndex]->data;
			}
			// Dereference operator:
			T* operator -> () { //  Done
				return &preVector[preVectorIndex]->data;
			}

			// preincrement. move forward to next larger value
			PreorderIterator& operator++() {
				preVectorIndex++;
				return *this;
			}
			// postincrement
			PreorderIterator operator++(int val) {
				PreorderIterator saverPreInstance = *this;
				preVectorIndex++;
				return saverPreInstance;
			}  
		};

/*---------------------------------------------------------------------------------------------------------*/
		class InorderIterator {						//        subclass Inorder Iterator
		  private:									//     ( left - parent - right)
			std::vector <Node*> helperVector;
			size_t currentVectorIndex = 0;
		  public:
			InorderIterator(Node* node = nullptr) {
				if (node != nullptr)
				{
					fillVector(node);
				}
				helperVector.push_back(nullptr);
			}

			void fillVector(Node* node)
			{
				if (node == nullptr) {
					return;
				}
				fillVector(node->left);
				helperVector.push_back(node);
				fillVector(node->right);
			}            
			
            bool operator != (const InorderIterator& other) { //  Done
				return helperVector.at(currentVectorIndex) != other.helperVector.at(other.currentVectorIndex);
			}
			// comparison operators. just compare node pointers
			bool operator == (const InorderIterator& other) { //  Done
				return helperVector.at(currentVectorIndex) == other.helperVector.at(other.currentVectorIndex);
			}

			// dereference operator. return a reference to
			// the value pointed to by nodePtr
			T& operator * () const { //  return value
				return helperVector[currentVectorIndex]->data;
			}
			// Dereference operator:
			T* operator -> () { //  return reference value              
				return &helperVector[currentVectorIndex]->data;
			}

			//preincrement. move forward to next larger value
			InorderIterator& operator++() { //looks good
				currentVectorIndex++;
				return *this;
			}
			// postincrement
			InorderIterator operator++(int val) {
				InorderIterator saverInstance = *this;
				currentVectorIndex++;
				return saverInstance;
			}
		};

/*---------------------------------------------------------------------------------------------------------*/
		class PostorderIterator { //       subclass Postorder Iterator
		private: //      (left  - right - parent)
			std::vector <Node*> postVector;
			size_t posVectorIndex = 0;
			
		public:
            
		    PostorderIterator(Node* node = nullptr) {
				if (node != nullptr)
				{
					fillVector(node);
				}
				postVector.push_back(nullptr);
			}
			void fillVector(Node* node)
			{
				if (node == nullptr) {
					return;
				}
				fillVector(node->left);
				fillVector(node->right);
				postVector.push_back(node);
			}
			
            
			bool operator != (const PostorderIterator& other) {
				return postVector.at(posVectorIndex) != other.postVector.at(other.posVectorIndex);
			}
			// comparison operators. just compare node pointers
			bool operator == (const PostorderIterator& other) { //  Done
				return postVector.at(posVectorIndex) == other.postVector.at(other.posVectorIndex);
			}

			// Dereference operator:
			T* operator -> () { //  Done
				return &postVector[posVectorIndex]->data;
			}
			// the value pointed to by nodePtr
			T& operator * () const {
				return postVector[posVectorIndex]->data;
			}

			// preincrement. move forward to next larger value
			PostorderIterator& operator++() {
				posVectorIndex++;
				return *this;
			}
			// postincrement
			PostorderIterator operator++(int val) {
				PostorderIterator saverPosInstance = *this;
				posVectorIndex++;
				return saverPosInstance;
			}
		};
/*---------------------------------------------------------------------------------------------------------*/
	
        BinaryTree& operator=(BinaryTree&& second) noexcept {
            this->root  = second.root;
            
            return *this;
        }
        BinaryTree& operator=(const BinaryTree& second) {
            
            if ( &second==this  ) {           }
           // check if root from other tree is not nullptr so that it won't try to access invalid memory
            if(second.root) {           // if second.root!=nullptr ->
                root = new Node{second.root->data};
                CopyConstructor(root, second.root);
                }
            
            return *this;
        }

//throw invalid_argument("Other tree root is empty ");
        BinaryTree(const BinaryTree& second) {
            if(second.root){
                this->root = new Node(second.root->data);
                CopyConstructor(root,second.root);
            }
        }

        void CopyConstructor(Node* src, const Node* dist) {
            if(dist->left){
                src->left = new Node(dist->left->data);
                CopyConstructor(src->left, dist->left);
            }
            if(dist->right){
                src->right = new Node(dist->right->data);
                CopyConstructor(src->right, dist->right);
            }
        }

        BinaryTree(BinaryTree &&second)  noexcept {     //  return true if potential exceptions - כלומר לא זורק חריגה
                this->root = second.root;
                second.root = nullptr;
        }

		InorderIterator begin() {
			begin_inorder();
			return root;
		}
		InorderIterator end() {
			end_inorder();
			return InorderIterator();
		}

		PreorderIterator begin_preorder() {
			return PreorderIterator(root);
		}
		PreorderIterator end_preorder() {
			return PreorderIterator();
		}

		InorderIterator begin_inorder() {
			return InorderIterator(root);
		}
		InorderIterator end_inorder() {
			return InorderIterator();
		}

		PostorderIterator begin_postorder() {
			return PostorderIterator(root);
		}
		PostorderIterator end_postorder() {
			return PostorderIterator();
		}

		bool operator == (const BinaryTree& CompTree) {								// i think the problem is here
			return true;
		}
		bool operator != (const BinaryTree& CompTree) {
			return false;
		}

		friend std::ostream& operator << (std::ostream& Output, const BinaryTree& binaryTree) {
			Output << "My BinaryTree is : " << std::endl; //// will want to recieve the tree
			return Output;
		};
	};
}
