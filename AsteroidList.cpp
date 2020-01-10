#include <galaxy-explorer/AsteroidList.hpp>
#include <iostream>
using namespace std;

//constructor for AsteroidListItem
//set next node and data to null
AsteroidListItem::AsteroidListItem() {
    this->next = nullptr;
    this->data = nullptr;
}

//copy constructor for AsteroidListItem
//set next to NULL and create a new Data with the asteroid passed in
AsteroidListItem::AsteroidListItem(Asteroid a) {
    this->next = nullptr;
    this->data = new Asteroid(a.getID(), a.getMass(), a.getHealth(), a.getCurrentHitbox(), a.getVelocity());
}

//destructor AsteroidListItem
AsteroidListItem::~AsteroidListItem() {
}

//constructor for AsteroidList
//do nothing
AsteroidList::AsteroidList(){
}

//copy constructor for AsteroidList
AsteroidList::AsteroidList(const AsteroidList& src){
    //if src is an empty list, do nothing
    if(src.head.getNext() == NULL){
        head.setNext(NULL);
        return;
    }
    
    AsteroidListItem * dst_ptr = &head;
    const AsteroidListItem * src_ptr = src.head.getNext();
    //if src is not empty
    while(src_ptr != NULL){
        //create a newNode with src's first node
        AsteroidListItem * newNode = new AsteroidListItem(src_ptr -> getData());
        //set the nextnode of dst_ptr to the newNode created
        dst_ptr -> setNext(newNode);
        //move dst_ptr to the newNode
        dst_ptr = newNode;
        //move src_ptr to the next node to continue to copy(as long as if src_ptr is not NULL)
        src_ptr = src_ptr -> getNext();
    }
    //set the last node's to point to NULL
    dst_ptr -> setNext(nullptr);
}

//destructor for AsteroidList
AsteroidList::~AsteroidList() {
}

//Add an asteroid at the beginning of this list
void AsteroidList::pushFront(Asteroid e) {
    //create newNode with asteroid e
    AsteroidListItem * newNode = new AsteroidListItem(e);
    //if the current list is empty, set the head to the new node created with asteroid e
    if(head.getNext() == NULL){
        head.setNext(newNode);
        //set the next pointer to be NULL
        newNode -> setNext(NULL);
        return;
    }else{
        //if the current list is not empty, set newNode's next to the first node
        newNode -> setNext(head.getNext());
        //set head to point to the newly inserted node at the beginning of the list
        head.setNext(newNode);
        return;
    }
}

//get the first node's data
Asteroid& AsteroidList::front() {
	return (head.getNext())->getData();
}

//get the first node's data
const Asteroid& AsteroidList::front() const {
	return (head.getNext())->getData();
}

bool AsteroidList::isEmpty() const {
    //head will be of ALI type
    //it's members will be NULL
    //therefore if head->next == NULL: it's pointing to nothing, empty ptr
    if(head.getNext() == NULL){
        return true;
    }else{
        //if the first node != NULL: there's at least one node
        return false;
    }
}


int AsteroidList::size() const {
    const AsteroidListItem * temp = head.getNext();
    //if emp == 0: empty linked list: return 0
    if(temp == NULL){
        return 0;
    }
    //if not empty, there's at least one node
    int numNodes = 1;
    //head isn't NULL: not empty
    while(temp -> getNext()!= NULL){
        //use temp to traverse down the list
        temp = temp -> getNext();
        //increment the number of nodes
        numNodes++;
    }
    return numNodes;
    
}


//if empty list, return NULL, else return the address of head(which is the position before the first item)
AsteroidListItem* AsteroidList::beforeBegin() {
    if(isEmpty()){
        return nullptr;
    }else{
        return &head; 
    }
}

//if empty list, return NULL, else return the address of head(which is the position before the first item)
const AsteroidListItem* AsteroidList::beforeBegin() const {
    if(isEmpty()){
        return nullptr;
    }else{
        return &head; 
    }
}

//return the ptr to first node
AsteroidListItem* AsteroidList::begin() {   
    return head.getNext();
}

//return the ptr to first node
const AsteroidListItem* AsteroidList::begin() const {
    return head.getNext();
}

//Return an item corresponding to the position of the last asteroidListItem
AsteroidListItem* AsteroidList::beforeEnd() {
      //make a temp ptr that points to the first node
    AsteroidListItem * temp = head.getNext();
    if(temp == NULL){
        //if empty, return NULL
        return nullptr;
    }else if(temp -> getNext() == NULL){
        //only one node
        return temp;
    }else{
        while(temp -> getNext() != NULL){
            //use temp to traverse through the list
            temp = temp -> getNext();
        }
        //return an item corresponding to the position of the last asteroid
        return temp;
    }
}

//Return an item corresponding to the position of the last asteroidListItem
const AsteroidListItem* AsteroidList::beforeEnd() const {
    //make a temp ptr that points to the first node
    const AsteroidListItem * temp = head.getNext();
    if(temp == NULL){
        //if empty linked list
        return nullptr;
    }else if(temp -> getNext() == NULL){
        //only one node linked list
        return temp;
    }else{
        while(temp -> getNext() != NULL){
            temp = temp -> getNext();
        }
        //return an item corresponding to the position of the last asteroid
        return temp;
    }
}

//Return an item corresponding to the position immediately after the last asteroid.
//If this list is empty, return a value equal to `begin()` 
AsteroidListItem* AsteroidList::end() {
    if(isEmpty()){
        return this->begin();
    }else{
        return nullptr;
    }
}

//Return an item corresponding to the position immediately after the last asteroid.
//If this list is empty, return a value equal to `begin()` 
const AsteroidListItem* AsteroidList::end() const {
    if(isEmpty()){
        return this->begin();
    }else{
        return nullptr;
    }
}

//Add a single asteroid to this list, in the position immediately after `prev`.
//returns the item that was inserted
AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, Asteroid e) {
    if(prev -> getNext()!= NULL){
        //make a newNode with the asteroid passed in
        AsteroidListItem * newNode = new AsteroidListItem(e);
        //set the nextNode of the newNode to prev's nextNode
        newNode -> setNext(prev->getNext());
        //set prev's nextNode to the newNode
        prev -> setNext(newNode);
        return newNode;
    }else{
         //make a newNode with the asteroid passed in
        AsteroidListItem * newNode = new AsteroidListItem(e);
        //set the nextNode of the newNode to prev's nextNode
        newNode -> setNext(NULL);
        //set prev's nextNode to the newNode
        prev -> setNext(newNode);
        return newNode;
    }
}

//insert a others after insertionPoint
AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* insertionPoint, const AsteroidList& others) {
    //if the list to insert is empty: do nothing
    if(insertionPoint == NULL){
        return nullptr;
    }
    //if the list to insert is empty: do nothing
    if(others.head.getNext() == NULL){
        return insertionPoint;
    }
    if(insertionPoint != NULL && others.head.getNext() != NULL){
        AsteroidList nonConstList = others;
        //save the node that will need to append to last node of others
        AsteroidListItem * temp = insertionPoint -> getNext();
        //pointer for traversal of new ll to insert
        AsteroidListItem * ntraverse = nonConstList.head.getNext();
        //set the next node of the current node to the first node of the ll to insert
        insertionPoint -> setNext(ntraverse);
        //if there is a node after insertion point
        if(temp != NULL){
            while(ntraverse -> getNext()!= nullptr){          
                ntraverse = ntraverse -> getNext();
            } 
            //need to set the next node to temp, which is what's after insertion point
            ntraverse -> setNext(temp);
            return ntraverse;
            //if there's no node after the insertion point
        }else if(temp == NULL){
            while(ntraverse -> getNext()!= nullptr){          
                ntraverse = ntraverse -> getNext();
            } 
            //don't need to set the next node to temp since insertion point has nothing after if
            return ntraverse;
        }
    }
} 

//Given a position in this list, delete the following asteroid.
AsteroidListItem* AsteroidList::eraseAfter(AsteroidListItem* prev) {
    //is prev is empty, do nothing
    if(prev == nullptr){
        return nullptr;
    //if prev is last node, do nothing
    }
    
    //if the next node is null: delete nothing: delete nothing
    if(prev -> getNext() == nullptr){
        return nullptr;
    }
    
    //save the node after the node that is to be deleted
    AsteroidListItem * nodeAfterToDelete = prev -> getNext() -> getNext();
    
    //if there's no node after the node to be deleted
    if(nodeAfterToDelete == nullptr){
        //delete the data in the node
        delete &(prev -> getNext() -> getData());
        //delete the node
        delete prev->getNext();
        //set the next node to be null since the node to be deleted is the last node
        prev -> setNext(NULL);
        //return null since the node that was deleted is the last node
        return nullptr;
    }
    //if there are nodes after the node to be deleted
    if(nodeAfterToDelete != nullptr){
        //delete the data in the node
        delete &(prev -> getNext() -> getData());
        //delete the node
        delete prev->getNext();
        //set the previous node to point to the node after the node in which to be deleted
        prev -> setNext(nodeAfterToDelete);
        //return the node after the node to be deleted
        return nodeAfterToDelete;
    }
   
}

//clear the list
void AsteroidList::clear() {
    //if empty, do nothing
    if(isEmpty()){
        return;
    }
    //cptr points to the first node of ll
    AsteroidListItem * pptr = head.getNext();
    AsteroidListItem * cptr = pptr -> getNext();
    //pptr points to the head
    while(cptr != NULL){
        //deep delete the data
        delete &(pptr -> getData());
        //deep delete the node
        delete pptr;
        //shift the pointers to traverse and delete
        pptr = cptr;
        cptr = cptr->getNext();
        //head.setNext(NULL);
    }
    //set head to null
    head.setNext(nullptr);
    delete pptr;
}

//overloaded operator =
AsteroidList& AsteroidList::operator=(const AsteroidList& src) {
    //make a copy of src
    AsteroidList nonConstSrc = src;
    //assign this list to be equal to src
    head.setNext(nonConstSrc.head.getNext());
    //return this current list
    return *this;
}