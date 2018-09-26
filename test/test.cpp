#include "catch.hpp"
/*
*Author: Erick Obando Solano B14757
*Date: 20 Sep 2018

*Go to Readme for variable declaration Nomenclature
*Obtain data from a file and generates an AVL Tree node
*/

#include "avltree_ObtainData.hpp"
#include "AVL.hpp"


//for Standard Library usage
using namespace std;
avltree AVLTree;
char DataList;
string  l_s_Name;
string  l_su64_ID;
string l_s_line;
uint64_t l_u64_ID;
uint64_t DataQuantity;

bool CheckFile(ifstream& inFile){
  return inFile.peek()==ifstream::traits_type::eof();
}


int64_t ObtainData()
{

   /*Define name of file where data is located
   *the file defined is used to obtain data*/
   ifstream  FileIn;
     FileIn.open("TestData.txt");



   if (!FileIn){
     cout<<"Error: File was not opened"<<endl;
     return 0;
   }
   if(CheckFile(FileIn)){
     cout<<"Error: File is empty. File shall include name and ID numbers (9 digits)\nFormat Example: \n Jake Peralta Rodriguez, 123456789"<<endl;
     return 0;
   }

   //File was opened successfully and is not empty
   //The info found in file shall not be empty

   //conversion from string to int
   //uint64_t l_u64_NumPeople = stoi(l_s_NumberData);

   //data is obtained from file and saved
    while(getline(FileIn,l_s_line)){


    //Conversion from string to int
     stringstream ss(l_s_line);
     getline(ss,l_s_Name,',');
     getline(ss,l_su64_ID,',');

     stringstream iss(l_su64_ID);
     iss>>l_u64_ID;
     //end of conversion
     if(iss.fail()){
       cout<<"Try Again ID"<<l_su64_ID<< ": ID number entered is not valid. ID is not an integer"<<endl;
       return 0;
       if(l_su64_ID.length()!=10){
         cout<<"ID:"<<l_su64_ID<< " ID number entered is not valid. Verify lenght of ID number (Lenght "<<l_su64_ID.length()<<")"<<endl;
         return 0;
       }
     }
     //int64_t  l_u64_ID = atoi(l_su64_ID);
    int  l_u64_ID = stoi(l_su64_ID);
 //initializing new node struc
    st_node* l_st_node= new st_node{
    l_u64_ID,l_s_Name,0, NULL,NULL, NULL, false};
   AVLTree.AVL_Insert(AVLTree.l_pcmRootNode,l_st_node);
  //output in terminal
    cout<<"ID "<<l_st_node->l_u64_key<<endl;
    cout<<"Name "<<l_st_node->l_ssm_Name<<endl;
    cout<<"Height "<<l_st_node->l_ssm_height<<endl;
    cout<<"lc "<<l_st_node->l_u32psm_leftchild<<endl;
    cout<<"isroot "<<l_st_node->l_u32psm_rightchild<<endl;
    cout<<"rc "<<l_st_node->l_bsm_isroot<<endl;
   cout<<"El root es "<<AVLTree.l_pcmRootNode->l_u64_key<<endl;
   cout<<"Altura de root es "<<AVLTree.l_pcmRootNode->l_ssm_height<<endl;
   if(AVLTree.l_pcmRootNode->l_u32psm_leftchild != NULL){
    cout<<"Left child de root es "<<AVLTree.l_pcmRootNode->l_u32psm_leftchild->l_u64_key<<endl;
 }
    if(AVLTree.l_pcmRootNode->l_u32psm_rightchild != NULL){
cout<<"Right child de root es "<<AVLTree.l_pcmRootNode->l_u32psm_rightchild->l_u64_key<<endl;
  }
    return l_u64_ID;

    }
  //  delete st_node;

FileIn.close();



}

TEST_CASE("Verify ID Number format","[id]"){

  SECTION("ID Number size is less than 9 digits"){
    REQUIRE(ObtainData() == 2);
  }

  SECTION("ID Number size is more than 10 digits"){
  REQUIRE(ObtainData() == NULL);
  }

  SECTION("ID Number shall be a integer "){
  REQUIRE(ObtainData() == 'ABCD');
   }


 SECTION("AVL Tree Height"){
    st_node *l_st_node= new st_node{
   1234,"Erick",1, NULL,NULL, NULL, false};

   st_node *InsertedNode= new st_node{
  1235,"Jake",1, NULL,NULL, NULL, false};
   AVLTree.AVL_Insert(l_st_node,InsertedNode);
  REQUIRE(l_st_node->l_ssm_height == 1);
  }
  SECTION("1st Node is  Root"){
  REQUIRE(AVLTree.l_pcmRootNode->l_bsm_isroot != true);
  }

}

//TEST_CASE("Root Revision","[root]"){

//}
