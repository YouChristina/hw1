/*
CSCI 104: Homework 1 Problem 1

Write a recursive function to split a sorted singly-linked
list into two sorted linked lists, where one has the even 
numbers and the other contains the odd numbers. Students 
will receive no credit for non-recursive solutions. 
To test your program write a separate .cpp file and #include
split.h.  **Do NOT add main() to this file**.  When you submit
the function below should be the only one in this file.
*/

#include "split.h"

/* Add a prototype for a helper function here if you need */

void split(Node*& in, Node*& odds, Node*& evens)
{
  /* Add code here */
// WRITE YOUR CODE HERE
  //check if reached the end of in
  if (in == nullptr){
    //set the next node to nullptr to end list
    odds = nullptr; 
    evens = nullptr;
    return;
  }

  //check for odd or even
  if (in->value % 2 == 1){
    odds = in; //set odd head to in head
    Node* tmp = in->next;
    in = nullptr;
    split(tmp, odds->next, evens); //recursive call with next nodes
  } else {
    evens = in; //set even head to in head
    Node* tmp = in->next;
    in = nullptr;
    split(tmp, odds, evens->next); //recursive call with next nodes
  }

}

/* If you needed a helper function, write it here */
