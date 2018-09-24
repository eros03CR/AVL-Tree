/*
Header fro avltree_get_data
For Nomenclature go to README
Defines all the variables nad functions
*/

#ifndef avltree_get_data
#define avltree_get_data

//here include libraries
#include  <iostream>
#include  <stdint.h> //dealing with uint
#include  <string>
#include  <fstream>
#include  <iostream>
#include  <sstream>
#include <stdlib.h>
#include <stdio.h>
#include "avltree_functions.hpp"
//end libraries


//for Standard Library usage
using namespace std;

//here define variables
//end variables

//functions are mentioned
void ObtainData(void);

/*
*Note:
*Node has:
*Key:data of interest
*leftchild:data lower or equal than key
*rightchild:data greater than key
*height: AVL trees en AVL shall comply with |heightlchild-heightlright|<=1,
*
*In AVL Trees O(logn)
*/


//Here the functions are defined
//Creating the structure for the node
struct st_DataNode
{
  int64_t sm_int64_key;
  string  sm_str_Name;
  int32_t sm_int32_Height;
  st_DataNode *sm_point_LeftChild;
  st_DataNode *sm__point_RightChild;
  st_DataNode *sm_ParentNode;
  bool sm_boo_IsRoot; //defines it node is a  root IsRoot if True

/*  int64_t l_u64_key;
  string  l_ssm_Name;
  int32_t  l_ssm_height;
  st_node  *l_u32psm_leftchild;
  st_node  *l_u32psm_rightchild;
  st_node  *st_parent;
  bool  l_bsm_isroot; //flag to define if it is a root TRUE=is root
*/
};

//end function definition
#endif
