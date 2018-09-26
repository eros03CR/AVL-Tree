/*
*Author: Erick Obando Solano B14757
*Date: 20 Sep 2018

*Go to Readme for variable declaration Nomenclature
*Obtain data from a file and generates an AVL Tree node
*/

#include "avltree_ObtainData.hpp"
//#include "AVL.hpp"


//for Standard Library usage
using namespace std;
//avltree AVLTree;
string  l_s_Name;
string  l_su64_ID;
string l_s_line;
uint64_t l_u64_ID;

int64_t ObtainData()
{
   /*Define name of file where data is located
   *the file defined is used to obtain data*/
   ifstream  FileIn;
   FileIn.open("lista_10.txt");

   //conversion from string to int
   //uint64_t l_u64_NumPeople = stoi(l_s_NumberData);

   //data is obtained from file and saved
    while(getline(FileIn,l_s_line)){
     stringstream ss(l_s_line);
     getline(ss,l_s_Name,',');
     getline(ss,l_su64_ID,',');

     stringstream iss(l_su64_ID);
     iss>>l_u64_ID;
     //int64_t  l_u64_ID = atoi(l_su64_ID);
    int  l_u64_ID = stoi(l_su64_ID);
 //initializing new node struc
    st_node* l_st_node= new st_node{
    l_u64_ID,l_s_Name,0, NULL,NULL, NULL, false};
  //  AVLTree.AVL_Insert(AVLTree.l_pcmRootNode,l_st_node);
  //output in terminal
    cout<<"ID "<<l_st_node->l_u64_key<<endl;
    cout<<"Name "<<l_st_node->l_ssm_Name<<endl;
    cout<<"Height "<<l_st_node->l_ssm_height<<endl;
    cout<<"lc "<<l_st_node->l_u32psm_leftchild<<endl;
    cout<<"isroot "<<l_st_node->l_u32psm_rightchild<<endl;
    cout<<"rc "<<l_st_node->l_bsm_isroot<<endl;
  //  cout<<"El root es "<<AVLTree.l_pcmRootNode->l_u64_key<<endl;
  //  cout<<"Altura de root es "<<AVLTree.l_pcmRootNode->l_ssm_height<<endl;
  //  if(AVLTree.l_pcmRootNode->l_u32psm_leftchild != NULL){
  //    cout<<"Left child de root es "<<AVLTree.l_pcmRootNode->l_u32psm_leftchild->l_u64_key<<endl;
  //  }
    //if(AVLTree.l_pcmRootNode->l_u32psm_rightchild != NULL){
//cout<<"Right child de root es "<<AVLTree.l_pcmRootNode->l_u32psm_rightchild->l_u64_key<<endl;
    //}
  //  return l_st_node->l_u64_key;

    }
  //  delete st_node;

FileIn.close();


}
