#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct person
{ int DOB, SSN;
	string firstName, lastName;
	int balance;
  
  person (int s, int d, string l, string f, int b) {
    DOB = d;
    SSN = s;
    firstName = f;
    lastName = l;
    balance = b;
  }
  
	void print() {
		cout << DOB << ". " << firstName << " " << lastName << ". SSN:" << SSN << ". Bank Balance:" << balance << endl;
	}
};

struct node {
	person * data;
	node * left, * right;
	
	node (person * p, node * l = NULL, node * r = NULL) {
    data = p;
    left = l;
    right = r;
	}
	
	void print_all() {
		if (this == NULL) {
			return;
		}
		
		left -> print_all();
		data -> print();
		right -> print_all();
	}
};

struct tree {
	node * root;
	
	tree () {
		root = NULL;
	}
	
	void print_tree() {
		root -> print_all();
    cout << endl;
		return;
	}
  
  void add(person * p) {
    node * curr = root;
    if (curr == NULL) {
      root = new node(p);
      return;
    }
    
    node * prev = NULL;
    while (curr != NULL) {
      prev = curr;
      
      if (p -> lastName < curr -> data -> lastName)
        curr = curr->left;
      else if (p -> lastName > curr -> data -> lastName)
        curr = curr->right;
      else if ((p -> lastName == curr -> data -> lastName) && (p -> firstName < curr -> data -> firstName)) // last names are equal and first name is before so add to left
        curr = curr->left;
      else if ((p -> lastName == curr -> data -> lastName) && (p -> firstName >= curr -> data -> firstName))
        curr = curr->right;
    }
    if (p -> lastName < prev -> data -> lastName)
      prev->left = new node(p);
    else if (p -> lastName > prev -> data -> lastName)
      prev->right = new node(p);
    else if ((p -> lastName == prev -> data -> lastName) && (p -> firstName < prev -> data -> firstName)) // last names are equal and first name is before so add to left
      prev->left = new node(p);
    else if ((p -> lastName == prev -> data -> lastName) && (p -> firstName >= prev -> data -> firstName))
      prev->right = new node(p);
    
  }
  
  person * find(string f, string l) {
    // returns person matching firstname (f) and lastname (l)
    node * curr = root;
    
    while (curr != NULL)
    { if ((curr -> data -> firstName == f) && (curr -> data -> lastName == l))
        return curr -> data;
      if (l < curr->data->lastName)
        curr = curr->left;
      else if (l > curr->data->lastName)
        curr = curr->right;
      else if ((l == curr->data->lastName) && (f < curr->data->firstName))
        curr = curr->left;
      else
        curr = curr->right;
    }
    
    return NULL;
  }
};

tree read_data(tree t, string filename) {
  int DOB, SSN, balance;
  string firstName, lastName;
  
  //ifstream file("database1.txt");
  ifstream file(filename.c_str());
  
  if (file.fail()) { // no file
    cout << "Couldn't open file\n";
    exit(1);
  }
  while (true) {
    file >> SSN >> DOB >> firstName >> lastName >> balance;
    
    if (file.fail())
      break;
    
    person * p = new person(SSN, DOB, firstName, lastName, balance);
    t.add(p);
  }
  file.close();
	
	return t;
}

int main() {
  string filename = "/home/118/people1.txt";
	tree data_tree;
	data_tree = read_data(data_tree, filename);
  
  string word1, word2;
  while (true) {
    cout << "Enter command or name to search: ";
    cin >> word1 >> word2;
    
    if (word1 == "stop" && word2 == "it") {
      return 0;
    } else if (word1 == "print" && word2 == "all") {
      data_tree.print_tree();
      cout << endl << endl;
    } else {
      person * result = data_tree.find(word1, word2);
      if (result == NULL) {
        cout << "Couldn't find person!\n";
      } else {
        cout << endl;
        result -> print();
        cout << endl;
      }
    }
  }
}
