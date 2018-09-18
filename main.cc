#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include "dynmatrix.h"

using namespace std;

// construct a string representation 

void usage() {
  cerr << "Usage: upgma species.txt" << endl;
}

void printRowByRow(ClusterNode *head) {
  while (head) {
    cout <<setw(10)<<head->name<<":\t";
    DistanceNode *curD = head->row;
    while (curD) {
      cout <<curD->distance<<"\t";
      curD = curD->nextInRow;
    }
    cout <<endl;
    head = head->next;
  }
}

void printColumnByColumn(ClusterNode *head) {
  while (head) {
    cout <<setw(10)<<head->name<<":\t";
    DistanceNode *curD = head->column;
    while (curD) {
      cout <<curD->distance<<"\t";
      curD = curD->nextInColumn;
    }
    cout <<endl;
    head = head->next;
  }
}

string combineSpecies(ClusterNode *Node1, ClusterNode *Node2) {
	return  "(" + Node1->name + "," + Node2->name + ")";  
}

int countSpecies(ClusterNode *node) {
	string speciesName = node->name;
	int count = 0;
	for (int i = 0; i < speciesName.length(); i++) {
		if (speciesName[i] == ',')
			count++;
	}
	return count + 1;
}

double findDistance(ClusterNode *head, ClusterNode *node1, ClusterNode *node2) {
	int num = 0;
	int count = 0;
	ClusterNode *curr = head;
	
	while (curr != NULL) {
		if (node1 == curr)
			num = count;
		count += 1;
		curr = curr->next;
	}
	
	DistanceNode *temp = node2->row;
	for (int i = 0; i < num; i++) {
		temp = temp->nextInRow;
	}

	return temp->distance;
} 

double updateNewDistance(ClusterNode *head, ClusterNode *curr, ClusterNode *C, ClusterNode *D) {
	return (countSpecies(C)*findDistance(head, curr, C)+countSpecies(D)*findDistance(head, curr, D))/(countSpecies(C)+countSpecies(D));
}



int main( int argc, char *argv[] ) {
  if( argc != 2 ) {
    usage();
    return 0;
  }

  // let's start with empty DynMatrix:
  ClusterNode* head = NULL; 
  ClusterNode* tail = NULL;

  int n = 0; // number of species
  ifstream fin( argv[1] );
  if( fin.is_open() ) {
    // read species:
    string species;
    while ((fin.peek() != '\n') && (fin >> species)) {
      n++;
      //cout << species << endl;
      // YOUR CODE HERE: replace print statemnt by a code that insert a new species into DynMatrix
      addCluster(head, tail, species);
    }
    
    // read distances:
    DistanceNode *DN2 = head->row;
    for (int i=0; i<n && fin; i++) {
    	DistanceNode *DN1 = DN2;
    	for (int j=0; j<n && fin; j++) {
			double d;
			fin >> d;
			//cout << d << endl;
     		// YOUR CODE HERE: replace print statemnt by a code that updates distance field of the corresponding DistanceNode
     		DN1->distance = d;
     		DN1 = DN1->nextInRow;
      	}
      	DN2 = DN2->nextInColumn;
      }
    fin.close();
  }

  // YOUR CODE HERE: implement UPGMA method
  
  ClusterNode *C = NULL;
  ClusterNode *D = NULL;  

  
  while (head != tail) {
  
  	findMinimum(head, C, D);
   	addCluster(head, tail, combineSpecies(C, D)); 
 	ClusterNode *rand = head;
 	DistanceNode *temp1 = tail->column;

 	while (temp1->nextInColumn != NULL) {
 		temp1->distance = updateNewDistance(head, rand, C, D);
 		temp1 = temp1->nextInColumn;
 		rand = rand->next;
 	}
 
 	DistanceNode *temp2 = tail->row;
 	DistanceNode *temp3 = tail->column; 
 	while (temp2->nextInRow != NULL) {
 		temp2->distance = temp3->distance;
 		temp2 = temp2->nextInRow;
 		temp3 = temp3->nextInColumn;
 	}
 	
 	//printRowByRow(head);
 	//printColumnByColumn(head);
 
 	removeCluster(head, tail, C);
 	removeCluster(head, tail, D);
 	
 	//printRowByRow(head);
 	//cout<<endl<<endl;
}


  // print the name of the last remaining cluster
  if (head)
    cout << head->name << endl;

  // BONUS (optional): print the tree in a nice way

  return 0;
}
