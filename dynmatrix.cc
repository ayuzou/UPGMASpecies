#include "dynmatrix.h"


void addCluster(ClusterNode *&head,ClusterNode *&tail,const std::string& name)
// adds a cluster (at the tail) and the corresponding row and column to data structure
// distance of all added DistanceNodes should be initialized to 0.0
// at the end, tail should point to the newly added ClusterNode
{
  // YOUR CODE HERE
  if (head == NULL) {
  	ClusterNode *newClusterNode = new ClusterNode;
  	newClusterNode->name = name;
  	newClusterNode->prev = NULL;
  	newClusterNode->next = NULL;
  	tail = newClusterNode;
  	head = newClusterNode;
	DistanceNode *newDistanceNode = new DistanceNode;
	newDistanceNode->distance = 0.0;
	newDistanceNode->nextInColumn = NULL;
	newDistanceNode->nextInRow = NULL; 
	newClusterNode->row = newDistanceNode;
	newClusterNode->column = newDistanceNode;
	
	return;	
  } 
  
    ClusterNode *curr = new ClusterNode;
    curr->name = name;
    curr->prev = tail;
    curr->next = NULL;
    tail->next = curr;
    ClusterNode *rand = tail;
    tail = curr;
    
    
    DistanceNode *temp = rand->row;
    DistanceNode *RDN = new DistanceNode;
    curr->row = RDN;
    temp->nextInColumn = RDN;
    RDN->distance = 0.0;
    RDN->nextInRow = NULL;
    RDN->nextInColumn = NULL;
    temp = temp->nextInRow;
    
    while (temp != NULL) {
    	DistanceNode *DN2 = new DistanceNode;
    	DN2->distance = 0.0;
    	DN2->nextInColumn = NULL;
    	DN2->nextInRow = NULL;
    	RDN->nextInRow = DN2;
    	temp->nextInColumn = DN2;
    	temp = temp->nextInRow;
    	RDN = RDN->nextInRow;
	} 
	
	DistanceNode *newtemp = rand->column;
	DistanceNode *CDN = new DistanceNode;
	curr->column = CDN;
	newtemp->nextInRow = CDN;
	CDN->distance = 0.0;
    CDN->nextInRow = NULL;
    CDN->nextInColumn = NULL;
	newtemp = newtemp->nextInColumn;
		 
	 
	while (newtemp != NULL) {
		DistanceNode *DN2 = new DistanceNode;
		DN2->distance = 0.0;
    	DN2->nextInColumn = NULL;
    	DN2->nextInRow = NULL;
    	CDN->nextInColumn = DN2; 
    	newtemp->nextInRow = DN2;
    	newtemp = newtemp->nextInColumn;
    	CDN = CDN->nextInColumn;
	}
	
	
	 
}


void removeCluster(ClusterNode *&head, ClusterNode *&tail, ClusterNode *toBeRemoved)
// removes a cluster pointed to by toBeRemoved and the corresponding row and column
// if toBeRemoved is the first or last cluster then head or tail needs to be updated
{
	// YOUR CODE HERE
	if(head == tail) {
		if (head == toBeRemoved) 
		return;
	}

	if(head == toBeRemoved) {
		ClusterNode* temp = head->next;
		head = temp;
		
		while(temp != NULL) {
			temp->row = temp->row->nextInRow;
			temp->column = temp->column->nextInColumn;
			temp = temp->next;	
		}
		return;
	}

	ClusterNode* temp = head;
	while(temp->next != NULL) {
		if(temp->next == toBeRemoved) {
			temp->next = temp->next->next;

			DistanceNode* row = temp->row;
			while(row != NULL) {
				row->nextInColumn = row->nextInColumn->nextInColumn;
				row = row->nextInRow;
			}

			DistanceNode* column = temp->column;
			while(column != NULL) {
				column->nextInRow = column->nextInRow->nextInRow;
				column = column->nextInColumn;
			}
			break;
		}
		temp = temp->next;
	}	
}


void findMinimum(ClusterNode *head,ClusterNode *&C,ClusterNode *&D)
// finds the minimum distance (between two different clusters) in the data structure 
// and returns the two clusters via C and D
{
  	// YOUR CODE HERE
	double min = 100000000.0;
	ClusterNode *remb1 = head;
	ClusterNode *remb2 = head;
 	
 	while (remb1 != NULL) {
 		DistanceNode* temp = remb1->row;
 		while (temp != NULL) {
 			if (temp->distance != 0.0 && temp->distance < min) {
 				min = temp->distance;
 				C = remb1;
 				D = remb2;  				
 			}
  			remb2 = remb2 ->next;
 			temp = temp->nextInRow;
 		} 

 		remb1 = remb1->next;
 		remb2 = head;
 	}

}
