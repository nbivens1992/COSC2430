#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "ArgumentManager.h"

class Problem {
private:
	string problem_id = "";
	string problem_name = "";
	string difficulty = "";
public:
	Problem();
	Problem(string str);
	Problem(string id, string name, string difficulty);
	~Problem();

	bool search(const string& category, const string& searchItem) const;
	const Problem& operator=(const Problem& a);
	void changeID(string newID);
	void changeName(string newName);
	void changeDifficulty(string newDiff);
	void print() const;
	string printString() const;
	string returnID() const;
	string returnName() const;
	string returnDifficulty() const;
};


struct node {
	Problem input;
	node* link;
};

class ListIterator {
private:
	node* current;
public:
	ListIterator();
	ListIterator(node* otherNode);
	Problem operator*();
	ListIterator operator++();
	const bool operator==(const ListIterator& right);
	const bool operator!=(const ListIterator& right);
};

class myLinkedList {
protected: 
	int count=0;
	node* head;
	node* tail;
public:
	myLinkedList();
	myLinkedList(const myLinkedList& other);
	~myLinkedList();
	const myLinkedList& operator=(const myLinkedList&);
	bool isEmpty() const;
	void print() const;
	string printString() const;
	int length() const;
	void destroyList();
	void initializeList();
	void copyList(const myLinkedList& otherList); //pg289 in book
	ListIterator front() const;
	ListIterator back() const;
	bool search(const string& category, const string& searchItem) const;
	void insertFirst(const Problem& newItem);
	void insertLast(const Problem& newItem);
	void insertAt(const Problem& newItem, int pos);
	void remove(int pos);
	void remove(string str);
	void swap(node*& n1, node*& n2);
	void sort(string str);
	void reverseSort(string str);
};

int main(int argc, char* argv[]) {
	ifstream inStream;
	ofstream outStream;
	ifstream comInStream;
	string str;
	/*inStream.open("input23.txt");
	outStream.open("output23.txt");*/
	
	
	//argument manager stuff

	if (argc <2)//must have 2 parameter
	{
		cout << "call this program with parameters like ./main input=input11.txt output=output11.txt" << endl;
		return 255;
	}

	ArgumentManager am(argc, argv);
	string inFileName = am.get("input");
	string outFileName = am.get("output");
	string commandFileName = am.get("command");

	inStream.open(inFileName.c_str());
	if (inStream.fail()) {
		cout << "Input file failed to open" << endl;
	}
	outStream.open(outFileName.c_str());
	if (outStream.fail()) {
		cout << "Input file failed to open" << endl;
	}
	comInStream.open(commandFileName.c_str());
	if (comInStream.fail()) {
		cout << "Command file failed to open" << endl;
	}
	



	myLinkedList myList;

	while(!inStream.eof()){
		getline(inStream, str);
		if (str != "") {
			myList.insertLast(Problem(str));
		}
	}


	
	stringstream ss;
	string temp;
	//comInStream.open("command23.txt");

	while (!comInStream.eof()) {
		getline(comInStream, str);
		string command;
		string category;
		string item;
		int pos;
		ss <<str;
		if (str != "") {
			ss >> temp;
			command = temp;
			if (command == "sort") {
				ss >> temp;
				category = temp;
				ss >> temp;
				if (temp == "increasing") {
					myList.sort(category);
				}
				else if (temp == "decreasing") {
					myList.reverseSort(category);
				}
				else
					cout << "command file read wrong" << endl;
				temp = "";
			}
			if (command == "remove") {
				ss >> temp;
				string delimiter1 = ":";
				size_t pos = 0;
				
				pos = temp.find(delimiter1);
				category = temp.substr(0, pos);
				item = temp.substr(pos + delimiter1.length(), temp.length());
				
				if (category == "pos") {
					stringstream ns(item);
					ns >> pos;
					myList.remove(pos);
					ns.str("");
					ns.clear();
				}
				else {
					myList.remove(item);
				}

			}
			if (command == "add") {
				ss >> temp;
				string delimiter1 = ":";
				size_t pos = 0;

				pos = temp.find(delimiter1);

				item = temp.substr(pos + delimiter1.length(), temp.length());
				stringstream ns(item);
				ns >> pos;
				ns.str("");
				ns.clear();

				getline(ss, temp);
				item = temp.substr(1,temp.length());
				
				myList.insertAt(Problem(item),pos);
			}
			
		}
		item = "";
		temp = "";
		str = "";
		ss.str("");
		ss.clear();
	}

	outStream << myList.printString();
	inStream.close();
	outStream.close();
	comInStream.close();
}

string removespaces(string str) {
	string temp;
	string newString="";
	stringstream ss(str);
	ss >> temp;
	newString = temp;
	while (ss >> temp) {
		newString = newString +" "+ temp;
	}
	ss.clear();
	return newString;
}
//ListIterator Function__________________________________________________________________________
ListIterator::ListIterator() {
	current = NULL;
}
ListIterator::ListIterator(node *otherNode) {
	current = otherNode;
}
Problem ListIterator::operator*() {
	return current->input;
}
ListIterator ListIterator::operator++(){
	current = current->link;
	return *this;
}
const bool ListIterator::operator==(const ListIterator& right) {
	return (current == right.current);
}
const bool ListIterator::operator!=(const ListIterator& right) {
	return (current != right.current);
}

//Linked List Functions____________________________________________________________________________________
myLinkedList::myLinkedList() {
	count = 0;
	head = NULL;
	tail = NULL;
}


myLinkedList::myLinkedList(const myLinkedList& other) {
	head = NULL;
	tail = NULL;
	copyList(other);
}

myLinkedList::~myLinkedList() {
	destroyList();
}

const myLinkedList& myLinkedList::operator=(const myLinkedList& otherList) {
	if (this != &otherList) {
		copyList(otherList);
	}
	return *this;
}

bool myLinkedList::isEmpty() const {
	bool result = false;
	if (head == NULL && tail == NULL && count == 0) {
		result = true;
	}
	return result;
}

void myLinkedList::print()const {
	node* iter = NULL;
	iter = head;
	while (iter != NULL) {
		iter->input.print();
		iter = iter->link;
	}
}

string myLinkedList::printString()const {
	node* current = NULL;
	current = head;
	string str="";
	while (current != NULL) {
		str=str+current->input.printString();
		current = current->link;
	}
	return str;
}
int myLinkedList::length() const {
	return count;
}

void myLinkedList::destroyList() {
	node* temp;
	while (head != NULL) {
		temp = head;
		head = head->link;
		delete temp;
	}
	tail = NULL;
	count = 0;
}
void myLinkedList::initializeList() {
	destroyList();
}

void myLinkedList::copyList(const myLinkedList& otherList) {
	node* newNode; //new Node
	node* iter;   // node to traverse

	if (head!=NULL) {
		destroyList();
	}
	if (otherList.head == NULL) {
		head = NULL;
		tail = NULL;
		count = 0;
	}
	else {
		iter = otherList.head;
		count = otherList.count;

		head = new node(); 
		head->input = iter->input;
		head->link = NULL;
		tail = head;
		iter = iter->link;
		//copy rest of list
		while (iter != NULL) {
			newNode = new node; //create new node structure
			newNode->input = iter->input; // newNode is equal to the input of equivalent node in otherList
			newNode->link = NULL; //Link is NULL bc it is going to be added to the end of the list
			tail->link = newNode; // add the new node to the end of the list
			tail = newNode; // make the new node the end of the list
			iter = iter->link; // iterate
		}
	}
}
ListIterator myLinkedList::front()const {
	ListIterator temp(head);
	return temp;
}

ListIterator myLinkedList::back()const {
	ListIterator temp(tail);
	return temp;
}

bool myLinkedList::search(const string& category, const string& searchItem)const {
	bool found = false;
	node* current;
	current = head;
	while (current != NULL && !found) {
		if (current->input.search(category, searchItem))
			found = true;
		else
			current = current->link;
	}

	return found;
}
void myLinkedList::insertFirst(const Problem& newItem) {
	node* newNode;

	newNode = new node();
	newNode->input = newItem;
	newNode->link = NULL;

	if (head == NULL) {
		head = newNode;
		tail = newNode;
		count++;
	}
	else {
		newNode->link = head;
		head = newNode;
		count++;
	}
}
void myLinkedList::insertLast(const Problem& newItem) {
	node* newNode;

	newNode = new node();
	newNode->input = newItem;
	newNode->link = NULL;

	if (head == NULL) {
		head = newNode;
		tail = newNode;
		count++;
	}
	else {
		tail->link = newNode;
		tail = newNode;
		count++;
	}
}
void myLinkedList::insertAt(const Problem& newItem, int pos) {
	node* newNode;
	node* current;
	node* trailCurrent;
	
	newNode = new node();
	newNode->input = newItem;
	newNode->link = NULL;
	if (search("problem_id", newItem.returnID())) {
		return;
	}
	else if (head == NULL ) { //inserting first node in empty list
		head = newNode;
		tail = newNode;
		count++;
	}
	else if (head != NULL && pos <= 0) { //inserting at front in non empty list
		newNode->link = head;
		head = newNode;
		count++;
	}
	else if (head != NULL && pos+1 >= count) { //inserting at back of non-empty list
		tail->link = newNode;
		count++;
	}
	else {
		trailCurrent = head;
		current = head->link;
		for (int i = 1; i < pos;i++) {
			trailCurrent = trailCurrent->link;
			current = current->link;
		}	
		trailCurrent->link = newNode;
		newNode ->link = current;
		count++;
	}
}
void myLinkedList::remove(int pos) {
	node* current;
	node* trailCurrent;

	if ( head ==NULL) {
		
	}
	else if (pos >= count||pos<0) {
		//do nothing
	}
	else if ( pos == 0) { //deleting first node of non empty list
		current = head;
		head = head->link;
		count--;
		if (head == NULL)
			tail = NULL;
		delete current;
	}
	else if (pos + 1 == count) { //deleting end of non-empty list
		current = head;
		for (int i = 1; i < pos; i++) {
			current = current->link;
		}
		trailCurrent = current->link;
		current->link = NULL;
		count--;
		delete trailCurrent;
	}
	else { // deleting anywhere else
		current = head;
		for (int i = 1; i < pos; i++) {
			current = current->link;
		}
		trailCurrent = current;
		current = current->link;
		trailCurrent->link = current->link;
		count--;
		delete current;
	}
}
void myLinkedList::remove(string str) {
	node* current;
	node* trailCurrent;

	if (!search("problem_id",str) && !search("problem_name", str)&& !search("difficulty", str)||head == NULL) {
		
	}
	
	else if(head!=NULL) { //deleting anything else in non-empty list
		trailCurrent = NULL;
		current = head;
		while (current != NULL && head!=NULL) {
			if (head->input.search("problem_id", str) || head->input.search("problem_name", str) || head->input.search("difficulty", str)) { //deleting first node of non empty list
				head = head->link;
				count--;
				if (head == NULL) {
					tail = NULL;
					delete current;
				}
				if(head!=NULL)
					current = head;
			}
			else
				 if (current->input.search("problem_id", str) || current->input.search("problem_name", str) || current->input.search("difficulty", str)) {
					trailCurrent->link = current->link;
					count--;
					if (tail == current) {//deleting last node
						tail = trailCurrent;
						delete current;
						current = NULL;
					}
					else{
						delete current;
						current = trailCurrent->link; //Will this work right after a delete??
					}
				}
				else {
					trailCurrent = current;
					current = current->link;
				}
		}

	}

}
void myLinkedList::swap(node*& n1, node*& n2) {
	node* trailN1;
	node* trailN2;
	node* currN1;
	node* currN2;
	bool foundn1 =false;
	bool foundn2 = false;

	if (count < 2 || n1==n2 || n1==NULL ||n2==NULL) {
		cout << "error swaping nodes " << endl;
	}
	else {
		//find n1 placement
		currN1 = head;
		trailN1 = NULL;
		while (currN1 != n1) {
			trailN1 = currN1;
			currN1 = currN1->link;
		}
		//find n2 placement
		currN2 = head;
		trailN2 = NULL;
		while (currN2 != n2) {
			trailN2 = currN2;
			currN2 = currN2->link;
		}

		if (trailN1 == NULL) {//n1 is the head
			trailN2->link = currN1;
			node* temp = currN1->link;
			currN1->link = currN2->link;
			currN2->link = temp;
			head = currN2;
		}
		else if (trailN2 == NULL) {//n2 is the head
			trailN1->link = currN2;
			node* temp = currN2->link;
			currN2->link = currN1->link;
			currN1->link = temp;
			head = currN1;
		}
		else {
			trailN1->link = currN2;
			trailN2->link = currN1;
			node* temp = currN1->link;
			currN1->link = currN2->link;
			currN2->link = temp;
		}

		if (currN1->link == NULL)
			tail = currN1;
		if (currN2->link == NULL)
			tail = currN2;
	}

}


void myLinkedList::sort(string str) {
	if (head != NULL) {
		node* current;
		node* iter;

		//if str is ID
		if (str == "problem_id") {
			for (int i = 0; i < count - 1; i++) {
				current = head;
				iter = head->link;
				while (iter != NULL) {
					if (current->input.returnID() > iter->input.returnID()) {
						swap(current, iter);
						iter = current->link;
					}
					else {
						current = current->link;
						iter = iter->link;
					}
				}
			}
		}
		//if str is name
		if (str == "problem_name") {
			for (int i = 0; i < count - 1; i++) {
				current = head;
				iter = head->link;
				while (iter != NULL) {
					if (current->input.returnName() > iter->input.returnName()) {
						swap(current, iter);
						iter = current->link;
					}
					else {
						current = current->link;
						iter = iter->link;
					}
				}
			}
		}

		//if str is difficulty
		if (str == "difficulty") {
			int currDifficulty;
			int iterDifficulty;
			for (int i = 0; i < count - 1; i++) {
				current = head;
				iter = head->link;
				while (iter != NULL) {
					if (current->input.returnDifficulty() == "Hard")
						currDifficulty = 3;
					else if (current->input.returnDifficulty() == "Medium")
						currDifficulty = 2;
					else if (current->input.returnDifficulty() == "Easy")
						currDifficulty = 1;
					else
						cout << "Difficulty is neither Hard, Medium, or Easy";

					if (iter->input.returnDifficulty() == "Hard")
						iterDifficulty = 3;
					else if (iter->input.returnDifficulty() == "Medium")
						iterDifficulty = 2;
					else if (iter->input.returnDifficulty() == "Easy")
						iterDifficulty = 1;
					else
					{
						cout << "Difficulty is neither Hard, Medium, or Easy"; iterDifficulty = 0;
						currDifficulty = 0;
					}

					if (currDifficulty > iterDifficulty) {
						swap(current, iter);
						iter = current->link;
					}
					else {
						current = current->link;
						iter = iter->link;
					}
						
				}
			}
		}

	}
	else
		cout << "can't sort an empty list" << endl;
}

void myLinkedList::reverseSort(string str) {
	if (head != NULL) {
		node* current;
		node* iter;

		//if str is ID
		if (str == "problem_id") {
			for (int i = 0; i < count - 1; i++) {
				current = head;
				iter = head->link;
				while (iter != NULL) {
					if (current->input.returnID() < iter->input.returnID()) {
						swap(current, iter);
						iter = current->link;
					}
					else {
						current = current->link;
						iter = iter->link;
					}
				}
			}
		}
		//if str is name
		if (str == "problem_name") {
			for (int i = 0; i < count - 1; i++) {
				current = head;
				iter = head->link;
				while (iter != NULL) {
					if (current->input.returnName() < iter->input.returnName()) {
						swap(current, iter);
						iter = current->link;
					}
					else {
						current = current->link;
						iter = iter->link;
					}
				}
			}
		}

		//if str is difficulty
		if (str == "difficulty") {
			int currDifficulty;
			int iterDifficulty;
			for (int i = 0; i < count - 1; i++) {
				current = head;
				iter = head->link;
				while (iter != NULL) {
					if (current->input.returnDifficulty() == "Hard")
						currDifficulty = 3;
					else if (current->input.returnDifficulty() == "Medium")
						currDifficulty = 2;
					else if (current->input.returnDifficulty() == "Easy")
						currDifficulty = 1;
					else
						cout << "Difficulty is neither Hard, Medium, or Easy";

					if (iter->input.returnDifficulty() == "Hard") 
						iterDifficulty = 3; 
					else if (iter->input.returnDifficulty() == "Medium")
						iterDifficulty = 2;
					else if (iter->input.returnDifficulty() == "Easy")
						iterDifficulty = 1; 
					else
					{
						cout << "Difficulty is neither Hard, Medium, or Easy"; 
						iterDifficulty = 0; currDifficulty = 0;
					}

					if (currDifficulty <iterDifficulty) {
						swap(current, iter);
						iter = current->link;
					}
					else {
						current = current->link;
						iter = iter->link;
					}

				}
			}
		}

	}
	else
		cout << "can't sort an empty list" << endl;
}


//Problem Functions_________________________________________________________________________________
Problem::Problem() {
	problem_id = "";
	problem_name = "";
	difficulty = "";
}

Problem::Problem(string str) {
	string delimiter1 = ":";
	string delimiter2 = ",";
	size_t pos = 0;
	size_t pos2 = 0;
	string token;

	pos = str.find(delimiter1);
	pos2 = str.find(delimiter2);
	if (pos != string::npos) {
		token = str.substr(pos + delimiter1.length(), pos2 - delimiter2.length() - pos);
		problem_id = removespaces(token);
		str.erase(0, pos2 + delimiter2.length());
	}

	pos = str.find(delimiter1);
	pos2 = str.find(delimiter2);
	if (pos != string::npos) {
		token = str.substr(pos + delimiter1.length(), pos2 - delimiter2.length() - pos);
		problem_name = removespaces(token);
		str.erase(0, pos2 + delimiter2.length());
	}

	pos = str.find(delimiter1);
	pos2 = str.find(delimiter2);
	if (pos != string::npos) {
		token = str.substr(pos + delimiter1.length(), pos2 - delimiter2.length() - pos);
		difficulty = removespaces(token);
		str.erase(0, pos2 + delimiter2.length());
	}
}
Problem::Problem(string id, string name, string diff) {
	problem_id = id;
	problem_name = name;
	difficulty = diff;
}
Problem::~Problem() {
}

const Problem& Problem::operator=(const Problem& a) { 
	problem_id = a.problem_id;
	problem_name = a.problem_name;
	difficulty = a.difficulty;

	return *this;
}
void Problem::changeID(string newID) {
	problem_id = newID;
}

void Problem::changeName(string newname) {
	problem_name = newname;
}

void Problem::changeDifficulty(string newDiff) {
	difficulty = newDiff;
}

string Problem::returnID() const {
	return problem_id;
}

string Problem::returnName() const {
	return problem_name;
}

string Problem::returnDifficulty() const {
	return difficulty;
}

void Problem::print() const {
	cout << "problem_id:" << returnID() << ", problem_name:"
		<< returnName() << ", difficulty:" << returnDifficulty()<<endl;
}
string Problem::printString() const {
	string str;
	str = "problem_id:" + returnID() + ", problem_name:"+ returnName()+ ", difficulty:" + returnDifficulty()+"\n";
	return str;
}

bool Problem::search(const string& category, const string& searchItem)const {
	bool found = false;
	if (category != "problem_id" && category != "problem_name" && category != "difficulty") {
		cout << "searching for something other than ID#, name, or difficulty";
	
	}
	if (category == "problem_id" && searchItem == problem_id)
		found = true;
	if (category == "problem_name") {
		stringstream ss(problem_name);
		string temp;
		while (ss >> temp) {
			if (searchItem == temp)
				found = true;
		}
		ss << "";
		ss.clear();
	
	}
	if (category == "difficulty" && searchItem == difficulty)
		found = true;

	return found;
	}

