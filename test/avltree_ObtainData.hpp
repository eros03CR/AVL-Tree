/*
*Author: Erick Obando Solano B14757
*Date: 20 Sep 2018

*Go to Readme for variable declaration Nomenclature
*Obtain data from a file
*/

//head guards
#ifndef avltree_ObtainData
#define avltree_ObtainData

#include  <iostream>
#include  <stdint.h> //dealing with uint
#include  <string>
#include  <fstream>
#include  <iostream>
#include  <sstream>
#include <stdlib.h>
#include <stdio.h>
//#include "AVL.hpp"
//for Standard Library usage
using namespace std;

//Declaring function ObtainData
void ObtainData(void);

/*
*A Node,in a AVL Tree, has :
*   -Key:data of interest
*   -leftchild:data lower or equal than key
*   -rightchild:data greater than key
*   -height: AVL trees en AVL shall comply with |heightlchild-heightlright|<=1,
*In AVL Trees: complexity O(logn)
*/

//Creating the structure for the node
struct st_node
{
  int64_t l_u64_key;
  string  l_ssm_Name;
  int32_t  l_ssm_height;
  st_node  *l_u32psm_leftchild;
  st_node  *l_u32psm_rightchild;
  st_node  *st_parent;
  bool  l_bsm_isroot; //flag to define if it is a root TRUE=is root

};

#endif
