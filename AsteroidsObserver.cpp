/*
 * This file was developed for the Fall 2018 instance of ECE244 at the University of Toronto.
 * Creator: Matthew J. P. Walker
 */


#include <galaxy-explorer/AsteroidsObserver.hpp>

void AsteroidsObserver::onAsteroidInRange(Asteroid asteroid) {
    //set the first node to be a node which contains asteroid
    asteroid_list.pushFront(asteroid);
}

//update: delete the node with the same ID as asteroid and insert a node with asteroid
void AsteroidsObserver::onAsteroidUpdate(Asteroid asteroid) {
    bool foundAsteroid = false;
    //AsteroidListItem * newNode = new AsteroidListItem(asteroid);
    //pointer is now pointing to the head
    AsteroidListItem * pointer = asteroid_list.beforeBegin();
    AsteroidListItem * prev = nullptr;
    //empty list
    if(pointer == NULL){
        return;
    }
    if(pointer -> getNext() == NULL){
        return;
    }
    //now prev is pointing to head node
    prev = pointer;
    //pointer it pointing to the 1st node with data in it
    pointer = pointer -> getNext();
    while(pointer != NULL){
        if(pointer -> getData(). getID() == asteroid.getID()){
            foundAsteroid = true;
            //found, no need to keep traversing anymore
            break;
        }else if(pointer -> getData().getID() != asteroid.getID() && pointer -> getNext() != NULL){
            //if not found and the next node isn't null, traverse through
            prev = pointer;
            pointer = pointer -> getNext();
        }
    }
    if(foundAsteroid){
        //if found, erase the prev pointer(which is pointing to the node with asteroid with the same ID as asteroid's ID)
        asteroid_list.eraseAfter(prev);
        //insert a node with asteroid to update it
        asteroid_list.insertAfter(prev, asteroid);
    }
}

//delete the node with the same ID as asteroid
void AsteroidsObserver::onAsteroidOutOfRange(Asteroid asteroid) {
    bool foundAsteroid = false;
    AsteroidListItem * pointer = asteroid_list.beforeBegin();
    AsteroidListItem * prev = nullptr;
    //empty list
    if(pointer == NULL){
        return;
    }
    //empty list
    if(pointer -> getNext() == NULL){
        return;
    }
    //set prev to point to head
    //set pointer to point to the first node
    prev = pointer;
    pointer = pointer -> getNext();
    while(pointer != NULL){
        if(pointer -> getData(). getID() == asteroid.getID()){
            //if found, no need to keep traversing
            foundAsteroid = true;
            break;
        }else{
            //if not found and the next node isn't null, move pointer and prev to it's respective next node
            if(pointer -> getNext() != NULL){
                prev = pointer;
                pointer = pointer -> getNext();
            }else if(pointer == NULL){
                //gone through entire list and can't find it
                break;
            }
        }
    }
    if(foundAsteroid){
        //if found, make a new pointer to point to the node after the node that needs to be deleted
        AsteroidListItem * nodeAfterToDelete = pointer -> getNext();    
        //delete the data in the node
        delete &(pointer -> getData());
        //delete the node
        delete pointer;
        //set the next node of prev(node before the deleted node)000 to nodeAfterDelete to 
        prev ->setNext(nodeAfterToDelete);
    }
}

void AsteroidsObserver::onAsteroidDestroy(Asteroid asteroid) {
   bool foundAsteroid = false;
    AsteroidListItem * pointer = asteroid_list.beforeBegin();
    AsteroidListItem * prev = nullptr;
    //empty list
    if(pointer == NULL){
        return;
    }
    //empty list
    if(pointer -> getNext() == NULL){
        return;
    }
    //set prev to point to head
    //set pointer to point to the first node
    prev = pointer;
    pointer = pointer -> getNext();
    while(pointer != NULL){
        if(pointer -> getData(). getID() == asteroid.getID()){
            //if found, no need to keep traversing
            foundAsteroid = true;
            break;
        }else{
            //if not found and the next node isn't null, move pointer and prev to it's respective next node
            if(pointer -> getNext() != NULL){
                prev = pointer;
                pointer = pointer -> getNext();
            }else if(pointer == NULL){
                //gone through entire list and can't find it
                break;
            }
        }
    }
    if(foundAsteroid){
        //if found, make a new pointer to point to the node after the node that needs to be deleted
        AsteroidListItem * nodeAfterToDelete = pointer -> getNext();    
        //delete the data in the node
        delete &(pointer -> getData());
        //delete the node
        delete pointer;
        //set the next node of prev(node before the deleted node)000 to nodeAfterDelete to 
        prev ->setNext(nodeAfterToDelete);
    }
}
