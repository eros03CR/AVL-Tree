/*
*Author: Erick Obando Solano B14757
*Date: 20 Sep 2018

*Go to Readme for variable declaration Nomenclature
*Obtain data from a file and generates an AVL Tree node
*/

#include "AVL.hpp"
#include "avltree_ObtainData.hpp"
#include <stdio.h>

using namespace std;

int32_t k = 0; // Balance constant
int32_t height;
avltree::avltree(){
 std::cout<<"AVL created"<<std::endl;
 // Do nothing, just declare it
}

int avltree::AVL_Insert(struct st_node *ActualNode, struct st_node *InsertedNode){

	//Check if this is the first inserted node
	if(l_pcmRootNode == NULL){
		l_pcmRootNode = InsertedNode;  // Assign InsertedNode as the root node
		InsertedNode->l_ssm_height = 1;
		InsertedNode->l_bsm_isroot = true;
		l_pcmRootNode->l_bsm_isroot = true;
    height=InsertedNode->l_ssm_height;
		return height;
	}

	InsertedNode->st_parent = ActualNode;  // The actual node will be the parent of Inserted node

	// Left branch case
	if(InsertedNode->l_u64_key < ActualNode->l_u64_key){
		if(ActualNode->l_u32psm_leftchild == NULL){                 // If left child is empty assign inserted node there
			ActualNode->l_u32psm_leftchild = InsertedNode;
			InsertedNode->l_ssm_height = 1; //last node of the tree
		}else{AVL_Insert(ActualNode->l_u32psm_leftchild , InsertedNode);}
	}

	// Right branch case
	if(InsertedNode->l_u64_key > ActualNode->l_u64_key){
		if(ActualNode->l_u32psm_rightchild == NULL){                // If right child is empty assign inserted node there
			ActualNode->l_u32psm_rightchild = InsertedNode;
			InsertedNode->l_ssm_height = 1; //last node of the tree
		}else{AVL_Insert(ActualNode->l_u32psm_rightchild , InsertedNode);}
	}

	// Calculate the height of its parental ancestry
	AVL_CalcHeight(InsertedNode);
}



// Function to calculate the height of the parental ancestry of the last node inserted
int32_t avltree::AVL_CalcHeight(struct st_node *NodeChecked){

	//This is the root, no more recursivity -> GO OUT
	if (NodeChecked->l_bsm_isroot == true){
		return 0;
	}

	l_pcmNewNode = NodeChecked->st_parent; // Assign to l_pcmNewNode the parent of the node checked

	// Easy cases where there is just one child
	if(l_pcmNewNode->l_u32psm_leftchild == NULL || l_pcmNewNode->l_u32psm_rightchild == NULL){
		l_pcmNewNode->l_ssm_height = NodeChecked->l_ssm_height + 1;
	}

	// Complex cases where there is left and right children
	if(l_pcmNewNode->l_u32psm_leftchild != NULL && l_pcmNewNode->l_u32psm_rightchild != NULL){
		l_pcmAuxNode1 = l_pcmNewNode->l_u32psm_leftchild;
		l_pcmAuxNode2 = l_pcmNewNode->l_u32psm_rightchild;

		/* Check if the height of the left child is higher or equal to the height of
		 * the right child, if so, replace the its height with the height of the lc+1
		 * otherwhise it will be replaced with rc+1
 		 */
		if(l_pcmAuxNode1->l_ssm_height >= l_pcmAuxNode2->l_ssm_height){
			l_pcmNewNode->l_ssm_height = l_pcmAuxNode1->l_ssm_height + 1;
		}else{l_pcmNewNode->l_ssm_height = l_pcmAuxNode2->l_ssm_height + 1;}
	}

	// Calculate the k = lc_height - rc_height
	k = l_u32cmK_Rupture(l_pcmNewNode);
	cout<<"\n \nNodo actual es: "<<l_pcmNewNode->l_u64_key<<endl;
	cout<<"K es "<<k<<endl;
  return l_pcmNewNode->l_ssm_height;
	// Here I have to evaluate if is necessary to rotate due to |k|>=2
	// Recursive function to re-calculate the heights of all its parental ancestry
	AVL_CalcHeight(l_pcmNewNode);
}



//cambiar el nombre de function
int32_t avltree::l_u32cmK_Rupture(struct st_node *LastNodeInserted){
	//if(LastNodeInserted->l_bsm_isroot == false){l_pcmNewNode = LastNodeInserted->st_parent;}

	//Case where there is lc and rc
	if(l_pcmNewNode->l_u32psm_leftchild != NULL && l_pcmNewNode->l_u32psm_rightchild != NULL){
		l_pcmAuxNode1 = l_pcmNewNode->l_u32psm_leftchild;
		l_pcmAuxNode2 = l_pcmNewNode->l_u32psm_rightchild;
		return ((l_pcmAuxNode1->l_ssm_height)-(l_pcmAuxNode2->l_ssm_height));
	}
	// if lc == null
	if(l_pcmNewNode->l_u32psm_leftchild == NULL && l_pcmNewNode->l_u32psm_rightchild != NULL){
		l_pcmAuxNode2 = l_pcmNewNode->l_u32psm_rightchild;
		return (0-(l_pcmAuxNode2->l_ssm_height));
	}
	//if rc == null
	if(l_pcmNewNode->l_u32psm_leftchild != NULL && l_pcmNewNode->l_u32psm_rightchild == NULL){
		l_pcmAuxNode1 = l_pcmNewNode->l_u32psm_leftchild;
		return ((l_pcmAuxNode1->l_ssm_height)-0);
	}
	//if rc == lc == null
	if(l_pcmNewNode->l_u32psm_leftchild == NULL && l_pcmNewNode->l_u32psm_rightchild == NULL){
		return 0;
	}
}

// RECALCULAR ALTURAS Y UTILIZAR FUNCIONES!!! las rotaciones se implementan donde se calcula el k

int avltree::AVL_RotateLL(struct st_node *BreakerNode){
	/* Breaker node is the upper node of the rotation nodes affected (BreakerNode = z)
	 * This section will be full of ifs to avoid segmentation fault problems

	T1, T2, T3 and T4 are subtrees.
	         z                                       y
	        / \                                    /   \
 	       y  T4      Right Rotate (z)            x     z
	      / \          - - - - - - - - ->        / \   / \
	     x  T3                                  T1 T2 T3 T4
	    / \
	   T1 T2
	 */

	// Assigning parent of y
	if(BreakerNode->st_parent != NULL){
		BreakerNode->l_u32psm_leftchild->st_parent = BreakerNode->st_parent;
	}else{ // z is the root node
		BreakerNode->l_u32psm_leftchild->st_parent = NULL;
		BreakerNode->l_bsm_isroot = false;
		BreakerNode->l_u32psm_leftchild->l_bsm_isroot = true;

	}

	// Assigning y as the new parent of z
	BreakerNode->st_parent = BreakerNode->l_u32psm_leftchild;

	// Assigning T3 as the left child of z
	if(BreakerNode->l_u32psm_leftchild->l_u32psm_rightchild != NULL){
		BreakerNode->l_u32psm_leftchild = BreakerNode->l_u32psm_leftchild->l_u32psm_rightchild;
	}else{BreakerNode->l_u32psm_leftchild = NULL;}

	// Assigning z as the right child of y
	BreakerNode->l_u32psm_leftchild->l_u32psm_rightchild = BreakerNode;


	return 0;
}





int avltree::AVL_RotateRR(struct st_node *BreakerNode){
	/* Breaker node is the upper node of the rotation nodes affected (BreakerNode = z)
	 * This section will be full of ifs to avoid segmentation fault problems

	T1, T2, T3 and T4 are subtrees.
	  z                                y
	 / \                             /   \
	T1  y      Left Rotate(z)       z     x
	   / \     - - - - - - - ->    / \   / \
	  T2  x                       T1 T2 T3 T4
	     / \
	    T3 T4
	 */

	// Assigning parent of y
	if(BreakerNode->st_parent != NULL){
		BreakerNode->l_u32psm_rightchild->st_parent = BreakerNode->st_parent;
	}else{ // BreakerNode is the root
		BreakerNode->l_u32psm_rightchild->st_parent = NULL;
		BreakerNode->l_bsm_isroot = false;
		BreakerNode->l_u32psm_rightchild->l_bsm_isroot = true;
	}

	// Assigning y as the new parent of z
	BreakerNode->st_parent = BreakerNode->l_u32psm_rightchild;

	// Assigning T2 as the right child of z
	if(BreakerNode->l_u32psm_rightchild->l_u32psm_leftchild != NULL){
		BreakerNode->l_u32psm_rightchild = BreakerNode->l_u32psm_rightchild->l_u32psm_leftchild;
	}else{BreakerNode->l_u32psm_rightchild = NULL;}

	// Assigning z as the right child of y
	BreakerNode->l_u32psm_rightchild->l_u32psm_leftchild = BreakerNode;


	return 0;
}



int avltree::AVL_RotateLR(struct st_node *BreakerNode){
	/* Breaker node is the upper node of the rotation nodes affected (BreakerNode = z)
	 * This section will be full of ifs to avoid segmentation fault problems

	     z                              z                            x
	    / \                            / \                         /   \
	   y  T4   Left Rotate (y)        x  T4    Right Rotate(z)    y     z
	  / \      - - - - - - - - ->    /  \      - - - - - - - ->  / \   / \
	 T1  x                          y   T3                      T1 T2 T3 T4
	    / \                        / \
	   T2 T3                      T1 T2
	 */
	AVL_RotateRR(BreakerNode->l_u32psm_leftchild);      // Left rotate for y
	AVL_RotateLL(BreakerNode);                          // Right rotate for z
	return 0;
}




int avltree::AVL_RotateRL(struct st_node *BreakerNode){
	/* Breaker node is the upper node of the rotation nodes affected (BreakerNode = z)
	 * This section will be full of ifs to avoid segmentation fault problems

	   z                            z                             x
	  / \                          / \                          /   \
	 T1  y   Right Rotate (y)     T1  x      Left Rotate(z)    z     y
	    / \  - - - - - - - - ->      / \   - - - - - - - ->   / \   / \
	   x  T4                        T2  y                    T1 T2 T3 T4
	  / \                              / \
	 T2 T3                            T3 T4

	 */
	AVL_RotateLL(BreakerNode->l_u32psm_rightchild);
	AVL_RotateRR(BreakerNode);
	return 0;
}
