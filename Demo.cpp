                        //          Auther : Dolev Hindy
#include "sources/BinaryTree.hpp"               // link us to the source hpp file.
#include <algorithm>
#include <vector>  
#include <cstring> 

using namespace std;
using namespace ariel;

bool IsOdd (int i) { if(i<0){i=(-1)*i;}
            return ((i%2)==1); }

bool IsLetter (char i) {  // function:
              //Small letter          Big letter
  return ((65 < i) && (i < 91))||((97 < i)&&(i < 123));
}
void printx2(int a)
{
    cout << a * 2 << " ";
}
void print_2(char a)
{
    cout << a+2 << " ";
}

int main(){
vector<double> CharsTreeVector; 
BinaryTree<char> CharsTree; 
CharsTree.add_root('a');
CharsTree.add_left('a', '+');     
CharsTree.add_right('a', 'b');      
cout << CharsTree << endl;

for (auto it=CharsTree.begin_preorder(); it!=CharsTree.end_preorder(); ++it) {
    cout << (*it) << " " ;  // prints: a + b
  }  
  cout << endl;
  for (auto it=CharsTree.begin_inorder(); it!=CharsTree.end_inorder(); ++it) {
    cout << (*it) << " " ;  // prints: + a b
  } 
  cout << endl;
  for (auto it=CharsTree.begin_postorder(); it!=CharsTree.end_postorder(); ++it) {
    cout << (*it) << " " ;  // prints: a b +
    CharsTreeVector.push_back(*it);
  }  
  cout << "\n" << endl;     // jump a line

  for_each (CharsTreeVector.begin(), CharsTreeVector.end(), IsLetter);
  cout << "This vec is contain just letters, but no symbols.";
  cout << "\n" << endl;     // jump a line

  cout << "This vec CharsTreeVector changed to ascii values +2." << endl; 
  for_each(CharsTreeVector.begin(), CharsTreeVector.end(), print_2);    
  cout << "\n" << endl; 

/*---------------------------------------------------------------------------------------------------------*/
vector<double> DoublesTreeVector;          //Used for testing
BinaryTree<double> DoublesTree; 
DoublesTree.add_root(49);
DoublesTree.add_left(49.0,-7);     
DoublesTree.add_right(49,7);
DoublesTree.add_left(-7,-1); 
DoublesTree.add_right(-7,7);     
cout << DoublesTree << endl;
/* Prints the tree in a reasonable format. For example:
        49
        |--------|
        -7        7
        |---|
        -1   7
  */


for (auto it=DoublesTree.begin_preorder(); it!=DoublesTree.end_preorder(); ++it) {
    cout << (*it) << " " ;
  }  // prints: 49 -7 -1 7 7
  cout << endl;
  for (auto it=DoublesTree.begin_inorder(); it!=DoublesTree.end_inorder(); ++it) {
    DoublesTreeVector.push_back(*it);
    cout << (*it) << " " ;
  }  // prints: -1 -7 7 49 7
  cout << endl;
  for (auto it=DoublesTree.begin_postorder(); it!=DoublesTree.end_postorder(); ++it) {
    cout << (*it) << " " ;
  }  // prints: -1 7 -7 7 49
  cout <<"\n"<< endl;
  
  int mycount = count_if (DoublesTreeVector.begin(), DoublesTreeVector.end(), IsOdd);
  std::cout << "DoublesTreeVector contains " << mycount  << " odd values.\n";

  cout << "Multiple of 2 of elements are : \n";
  for_each(DoublesTreeVector.begin(), DoublesTreeVector.end(), printx2);
  cout <<"\n"<< endl;

  
    return 0;
}