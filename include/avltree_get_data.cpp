/*
*File created by: Erick Obando
*For Nomenclature go to README file
*Obtain data from a file and generates an AVL Tree node

*/
#include "avltree_get_data.hpp"
#include "avltree_functions.hpp"

uint8_t TestInsert = 0;

//for Standard Library usage
using namespace std;

//Here define the variables
avltree AVLTree;
string  str_Name;
string  str_ID;
string str_DataLine;
int64_t int64_ID;
int64_t intContador;
char DataList;
//end variable definition

//Here define the functions
void ObtainData()
{
  bool CheckFile(ifstream& inFile){
    return inFile.peek()==ifstream::traits_type::eof();
  }


  /*Define the data from the files available*/
  ifstream  InputFile;
  cout<<"LOADING DATA"<<endl;
  cout<<"Select the data list:\n 1-List with 10 people.\n 2-List of 1000 people.\n 3-List of 5000 people \n4-Test."<<endl;
  //User defines the file
  cin>>DataList;
  switch (DataList) {
    case '1':
    InputFile.open("lista_10.txt");
    break;

    case '2':
    InputFile.open("lista_100.txt");
    break;

    case '3':
    InputFile.open("lista_1000.txt");
    break;

    case '4':
    InputFile.open("lista_5000.txt");

    case '5':
    InputFile.open("lista_10000.txt");
    break;

    case '6':
    InputFile.open("TestData.txt");
    break;

    //default:
  //   cout<<"Invalid input. Try Again"<<endl;
  //   break;
  }

   //data is obtained from file and saved
    while(getline(InputFile,str_DataLine)){
     stringstream ss(str_DataLine);
     getline(ss,str_Name,',');
     getline(ss,str_ID,',');

     //conversion from string to int
     stringstream iss(str_ID);
     iss>>int64_ID;
     int  int64_ID = stoi(str_ID);
     if(iss.fail()){
       cout<<"Try Again ID"<<str_ID<< ": ID number entered is not valid. ID is not an integer"<<endl;

       if(str_ID.length()!=10){
         cout<<"ID:"<<str_ID<< " ID number entered is not valid. Verify lenght of ID number (Lenght "<<l_su64_ID.length()<<")"<<endl;
         intContador++;
       }
     //initializing new node struc
     st_DataNode* st_AVLNode= new st_DataNode{
     int64_ID,str_Name,0, NULL,NULL, NULL, false};

     //test Insert function
     TestInsert = AVLTree.AVL_Insert(AVLTree.l_pcmRootNode,st_AVLNode);
     }


InputFile.close();
}


cout<<"\n\nPeople Information Database. Choose an option:\n 1- Insert new person. \n2- Search a person (using ID number). \n3- Obtain tree height.\n 4. Get Tree's root. \n5. Get Tree's size. \n6. Exit."<<endl;
cin>>option;
switch (option) {
 case '1':
 cout<<"Not available"<<endl;
 break;

 case '2':
 cout<<"Insert the ID of the person to search."<<endl;
 cin>>int64_ID;
 break;

 case '3':
 cout<<"The height of the tree is: "<<endl;
 //shows tree height
 cout<<"The height of the created tree: "<<AVLTree.l_pcmRootNode->sm_int32_Height<<endl;
 if(AVLTree.l_pcmRootNode->sm_point_LeftChild != NULL){
  cout<<"Root's Left Child: "<<AVLTree.l_pcmRootNode->sm_point_LeftChild->sm_int64_key<<endl;
 }
 if(AVLTree.l_pcmRootNode->sm__point_RightChild != NULL){
  cout<<"Root's Right Child: "<<AVLTree.l_pcmRootNode->sm__point_RightChild->sm_int64_key<<endl;
 }
 break;

 case '4':
 cout<<"The size of the tree is: "<<intContador<<endl;
 break;

 case '5':
 cout<<"The root of the tree is: "<<AVLTree.l_pcmRootNode<<endl;
 break;

 case '6':
 cout<<"Exiting program"<<endl;
 break;

 default:
 cout<<"Value entered not valid.Try again"<<endl;
 break;
}

}
//end function definition
