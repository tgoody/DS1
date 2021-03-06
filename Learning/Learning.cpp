// Learning.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <string>
#include <iostream>
using namespace std;

struct Node {

	Node* next = NULL;
	Node* prev = NULL;
	string text = "";

};

void insertEnd(Node* head, string input) {
	Node* temp = head;
	while (temp->next != nullptr) {
		temp = temp->next;
	}
	Node* current = new Node;
	temp->next = current;
	current->prev = temp;
	current->text = input;
	
}

void insert(Node* head, int index, string input) {
	Node* temp = head;
	Node* current = new Node;
	current->text = input;
	for (int i = 1; i < index; i++) {
		if ((i + 1 == index) && temp->next == nullptr) {
			temp->next = current;
			current->prev = temp;
			return;
		}
		temp = temp->next;
	}
	current->prev = temp->prev;
	temp->prev->next = current;
	temp->prev = current;
	current->next = temp;
}

void edit(Node* head, int index, string input) {
	Node* temp = head;
	for (int i = 1; i < index; i++) {
		temp = temp->next;
	}
	temp->text = input;
}

void search(Node* head, string input){
	Node* temp = head;
	int count = 1;
	bool check = false;
	while (temp != nullptr) {
		if (temp->text.find(input) != string::npos) {
			cout << to_string(count) << " " << temp->text << endl;
			check = true;
		}
		temp = temp->next;
		count++;
	}
	if (!check) { cout << "not found" << endl; }
}

void deleteNode(Node* head, int index) {
	Node* temp = head;
	for (int i = 1; i < index; i++) {
		temp = temp->next;
		if (temp == nullptr) { return; }
	}
	temp->prev->next = temp->next;
	if (temp->next != nullptr) {
		temp->next->prev = temp->prev;
	}
	delete temp;
}

string quoteRemover(string bump) {

	string newString = "";
	string text = "";
	if (bump[0] == ' ') {
		for (int i = 1; i < bump.length(); i++) {
			text += bump[i];
		}
	}

	if (text[0] == text[text.length() - 1] && text[0] == '"') {
		for (int i = 1; i < text.length() - 1; i++) {
			newString += text[i];
		}
	}
	return newString;
}


int main()
{
	Node* head = new Node;
	int count = 0;
	int tempNum = 0;
	string userInput;
	string text = "";
	while (cin) {
		cin >> userInput;
		if (userInput == "insertEnd") {
			getline(cin, text);
			text = quoteRemover(text);
			if (count == 0) { 
				head->text = text; 
			}
			else { 
				insertEnd(head, text); 
			}
			count++;
		}
		else if (userInput == "insert"){

			cin >> tempNum;
			getline(cin, text);
			text = quoteRemover(text);
			if (tempNum <= (count + 1)) {
				insert(head, tempNum, text); count++;
			}
		}
		else if (userInput == "edit") {
			cin >> tempNum;
			getline(cin, text);
			text = quoteRemover(text);
			edit(head, tempNum, text);
		}
		else if (userInput == "print") {
			Node* temp = head;
			for (int i = 0; i < count; i++) {
				cout << to_string(i + 1) << " " << temp->text << endl;
				temp = temp->next;
			}
		}
		else if (userInput == "search") {
			getline(cin, text);
			text = quoteRemover(text);
			search(head, text);
		}
		else if (userInput == "delete") {
			cin >> tempNum;
			if (tempNum <= count) { deleteNode(head, tempNum); count--; }
		}
		else if (userInput == "quit") {
			return 0;
		}
	}


	return 0;
}

