#include "Header.h"

Node::Node(int k, int v) 
	: key(k), value(v), next(nullptr), previous(nullptr) {}; //node constructor


LRUCache::LRUCache(int cap)
	: capacity(cap), head(nullptr), tail(nullptr) {};//constructor

//HELPER FUNCITONS

void LRUCache::removeNode(Node* node) {
	if (node->previous != nullptr) { //if there is a previous node
		node->previous->next = node->next; //connect previous node to next node
	} 
	else {
		head = node->next; //if there is no previous node, then node must be the head - so the head must be reassigned to node->next
	}

	if (node->next != nullptr) {
		node->next->previous = node->previous; //connect next node to previous node
	}
	else {
		tail = node->previous; //if current node is tail, assign tail to previous node
	}
}

void LRUCache::addNodeToTail(Node* node) {
	node->next = nullptr; //new node is at the tail end of the list
	node->previous = tail; //previous pointer is old tail

	if (tail != nullptr) { //tail = nullptr means list is empty
		tail->next = node; //move tail->next from nullptr to node
	}
	tail = node; //node is new tail

	if (head == nullptr) { //list is empty, need to assign head and tail to new node
		head = node;
	}
}

void LRUCache::moveToTail(Node* node) {
	removeNode(node); //unlink from current position
	addNodeToTail(node); //move it to MRU position
}


//CACHE OPERATIONS

int LRUCache::get(int key) {
	if (cacheMap.find(key) == cacheMap.end()) { //key does not exist in the cache
		return -1;
	}
	
	Node* node = cacheMap[key]; //assign pointer in cacheMap that points to value to temporary variable node
	moveToTail(node); //move node to MRU position
	return node->value; //return value of node
} 

void LRUCache::put(int key, int value) {
	if (cacheMap.find(key) != cacheMap.end()) { //if the key already exists, just update the value of it
		Node* node = cacheMap[key];
		node->value = value; //access the node to which cacheMap[key] points and reassign the value attached to it
		moveToTail(node);
	}

	Node* newNode = new Node(key, value); //node does not exist, so we create it
	cacheMap[key] = newNode; //create the mapping for the new node
	addNodeToTail(newNode); //add new node to tail

	if (cacheMap.size() > capacity) {

		cacheMap.erase(head->key); //remove the mapping to the head node from the cacheMap

		Node* temp = head; //prepare to delete
		removeNode(head); //use above function to remove head node
		delete temp; //dynamically deallocate the memory
	}
}