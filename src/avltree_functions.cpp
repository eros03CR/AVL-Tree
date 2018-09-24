/*
AVLTree implementation
 */

#include "avltree_functions.hpp"
#include "avltree_get_data.hpp"
#include <stdio.h>

using namespace std;

int32_t iNodesAmount = 0;
int32_t k = 0; // Balance constant
struct st_DataNode *LastNodeIns = NULL;
struct st_DataNode *l_pcmAuxNode3 = NULL;

avltree::avltree(){
 std::cout<<"AVL created \n"<<std::endl;
 // Do nothing, just declare it, the magic comes later
}

//int avltree::AVL_NodesAmount(){return iNodesAmount;}

int avltree::AVL_Insert(struct st_DataNode *ActualNode, struct st_DataNode *InsertedNode){
  /* 0 everything is ok
   * 1 Equal IDs
   * 2 ID out of range
   */
  //cout<<"\n Node inserted is "<<InsertedNode->sm_int64_key<<endl;

  if(InsertedNode->sm_int64_key < 100000000 || InsertedNode->sm_int64_key > 999999999){
    cout<<"ERROR: The ID shall be between 1 0000 0000 and 9 9999 9999."<<endl;
    return 2; // Ced shall be between the defined range
  }

  if(ActualNode != NULL){
    cout<<"\nNode inserted is "<<InsertedNode->sm_int64_key;
    cout<<" and is being compared with "<<ActualNode->sm_int64_key<<endl;
  }

  LastNodeIns = InsertedNode;

	//Check if this is the first inserted node
	if(l_pcmRootNode == NULL){
		l_pcmRootNode = InsertedNode;                               // Assign InsertedNode as the root node
		InsertedNode->sm_int32_Height = 1;
		InsertedNode->sm_boo_IsRoot = true;
		l_pcmRootNode->sm_boo_IsRoot = true;
    iNodesAmount++;
		return 0;
	}

  if(InsertedNode->sm_int64_key == ActualNode->sm_int64_key){
    if(l_pcmRootNode == ActualNode){
      l_pcmRootNode = NULL;
      InsertedNode->sm_boo_IsRoot = false;
      l_pcmRootNode->sm_boo_IsRoot = false;
      iNodesAmount--;
    }
    cout<<"ERROR: There cannot be 2 equal IDs."<<endl;
    return 1; // There cannot be any couple of ceds equal
  }

	InsertedNode->sm_ParentNode = ActualNode;  // The actual node will be the parent of Inserted node

	// Left branch case
	if(InsertedNode->sm_int64_key < ActualNode->sm_int64_key){
		if(ActualNode->sm_point_LeftChild == NULL){                 // If left child is empty assign inserted node there
			ActualNode->sm_point_LeftChild = InsertedNode;
			InsertedNode->sm_int32_Height = 1; //last node of the tree
      iNodesAmount++;
      cout<<"Insertion OK of "<<InsertedNode->sm_int64_key<<endl;
      return 0;
		}else{
      AVL_Insert(ActualNode->sm_point_LeftChild , InsertedNode);
    }
	}

	// Right branch case
	if(InsertedNode->sm_int64_key > ActualNode->sm_int64_key){
		if(ActualNode->sm__point_RightChild == NULL){                // If right child is empty assign inserted node there
			ActualNode->sm__point_RightChild = InsertedNode;
			InsertedNode->sm_int32_Height = 1; //last node of the tree
      iNodesAmount++;
      cout<<"Insertion OK of "<<InsertedNode->sm_int64_key<<endl;
      return 0;
		}else{
      AVL_Insert(ActualNode->sm__point_RightChild , InsertedNode);
    }
	}



	// Calculate the height of its parental ancestry
	AVL_CalcHeight(LastNodeIns);


}



int32_t avltree::l_u32cmK_Rupture(struct st_DataNode *LastNodeInserted){
	//if(LastNodeInserted->sm_boo_IsRoot == false){l_pcmNewNode = LastNodeInserted->sm_ParentNode;}

	//Case where there is lc and rc
	if(LastNodeInserted->sm_point_LeftChild != NULL && LastNodeInserted->sm__point_RightChild != NULL){
		l_pcmAuxNode1 = LastNodeInserted->sm_point_LeftChild;
		l_pcmAuxNode2 = LastNodeInserted->sm__point_RightChild;
		return ((l_pcmAuxNode1->sm_int32_Height)-(l_pcmAuxNode2->sm_int32_Height));
	}
	// if lc == null
	if(LastNodeInserted->sm_point_LeftChild == NULL && LastNodeInserted->sm__point_RightChild != NULL){
		l_pcmAuxNode2 = LastNodeInserted->sm__point_RightChild;
		return (0-(l_pcmAuxNode2->sm_int32_Height));
	}
	//if rc == null
	if(LastNodeInserted->sm_point_LeftChild != NULL && LastNodeInserted->sm__point_RightChild == NULL){
		l_pcmAuxNode1 = LastNodeInserted->sm_point_LeftChild;
		return ((l_pcmAuxNode1->sm_int32_Height)-0);
	}
	//if rc == lc == null
	if(LastNodeInserted->sm_point_LeftChild == NULL && LastNodeInserted->sm__point_RightChild == NULL){
		return 0;
	}
}

// RECALCULAR ALTURAS Y UTILIZAR FUNCIONES!!!

int avltree::AVL_RotateLL(struct st_DataNode *BreakerNode){
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

	// Assigning parent of z as parent of y
  cout<<"Rotando LL por "<<BreakerNode->sm_int64_key<<endl;
	if(BreakerNode->sm_boo_IsRoot != true){
		BreakerNode->sm_point_LeftChild->sm_ParentNode = BreakerNode->sm_ParentNode;
    if(BreakerNode->sm_ParentNode->sm_int64_key > BreakerNode->sm_int64_key){
      //parent is greather than child, we are lc
      BreakerNode->sm_ParentNode->sm_point_LeftChild = BreakerNode->sm_point_LeftChild;
    }else{BreakerNode->sm_ParentNode->sm__point_RightChild = BreakerNode->sm_point_LeftChild;}
	}else{ // z is the root node
		BreakerNode->sm_point_LeftChild->sm_ParentNode = NULL;
		BreakerNode->sm_boo_IsRoot = false;
		BreakerNode->sm_point_LeftChild->sm_boo_IsRoot = true;
    l_pcmRootNode = BreakerNode->sm_point_LeftChild;
	}

	// Assigning y as the new parent of z
	BreakerNode->sm_ParentNode = BreakerNode->sm_point_LeftChild;

	// Assigning T3 as the left child of z
	if(BreakerNode->sm_point_LeftChild->sm__point_RightChild != NULL){
    l_pcmAuxNode2 = BreakerNode->sm_point_LeftChild;
		BreakerNode->sm_point_LeftChild = BreakerNode->sm_point_LeftChild->sm__point_RightChild;
    // Assigning z as the right child of y
  	l_pcmAuxNode2->sm__point_RightChild = BreakerNode;
	}else{
    // Assigning z as the right child of y
  	BreakerNode->sm_point_LeftChild->sm__point_RightChild = BreakerNode;
    BreakerNode->sm_point_LeftChild = NULL;
  }

  if(BreakerNode->sm_ParentNode->sm_point_LeftChild != NULL){
    cout<<"en LL: lc de "<<BreakerNode->sm_ParentNode->sm_int64_key<<" es "<<BreakerNode->sm_ParentNode->sm_point_LeftChild->sm_int64_key<<endl;
  }
  if(BreakerNode->sm_ParentNode->sm__point_RightChild != NULL){
    cout<<"en LL: rc de "<<BreakerNode->sm_ParentNode->sm_int64_key<<" es "<<BreakerNode->sm_ParentNode->sm__point_RightChild->sm_int64_key<<endl;
  }
  // Update height of the nodes (just breakernode and its parents)
  //AVL_CalcHeight(LastNodeIns);

	return 0;
}





int avltree::AVL_RotateRR(struct st_DataNode *BreakerNode){
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

	// Assigning parent of y the parent of z
  cout<<"Rotando RR por "<<BreakerNode->sm_int64_key<<endl;
	if(BreakerNode->sm_ParentNode != NULL){
		BreakerNode->sm__point_RightChild->sm_ParentNode = BreakerNode->sm_ParentNode;
    if(BreakerNode->sm_ParentNode->sm_int64_key > BreakerNode->sm_int64_key){
      //parent is greather than child, we are lc
      BreakerNode->sm_ParentNode->sm_point_LeftChild = BreakerNode->sm__point_RightChild;
    }else{
      BreakerNode->sm_ParentNode->sm__point_RightChild = BreakerNode->sm__point_RightChild;
    }
	}else{ // BreakerNode is the root
		BreakerNode->sm__point_RightChild->sm_ParentNode = NULL;
		BreakerNode->sm_boo_IsRoot = false;
		BreakerNode->sm__point_RightChild->sm_boo_IsRoot = true;
    l_pcmRootNode = BreakerNode->sm__point_RightChild;
	}

	// Assigning y as the new parent of z
	BreakerNode->sm_ParentNode = BreakerNode->sm__point_RightChild;

	// Assigning T2 as the right child of z
	if(BreakerNode->sm__point_RightChild->sm_point_LeftChild != NULL){
    l_pcmAuxNode1 = BreakerNode->sm__point_RightChild;
		BreakerNode->sm__point_RightChild = BreakerNode->sm__point_RightChild->sm_point_LeftChild;
    // Assigning z as the left child of y
  	l_pcmAuxNode1->sm_point_LeftChild = BreakerNode;
	}else{
    // Assigning z as the right child of y
  	BreakerNode->sm__point_RightChild->sm_point_LeftChild = BreakerNode;
    BreakerNode->sm__point_RightChild = NULL;
  }

  // Update height of the nodes (just breakernode and its parents)
  //AVL_CalcHeight(LastNodeIns);
  if(BreakerNode->sm_ParentNode->sm_point_LeftChild != NULL){
    cout<<"en RR: lc de "<<BreakerNode->sm_ParentNode->sm_int64_key<<" es "<<BreakerNode->sm_ParentNode->sm_point_LeftChild->sm_int64_key<<endl;
  }
  if(BreakerNode->sm_ParentNode->sm__point_RightChild != NULL){
    cout<<"en RR: rc de "<<BreakerNode->sm_ParentNode->sm_int64_key<<" es "<<BreakerNode->sm_ParentNode->sm__point_RightChild->sm_int64_key<<endl;
  }
	return 0;
}



int avltree::AVL_RotateLR(struct st_DataNode *BreakerNode){
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
  cout<<"Rotando LR por "<<BreakerNode->sm_int64_key<<endl;
  AVL_RotateRR(BreakerNode->sm_point_LeftChild);      // Left rotate for y
	AVL_RotateLL(BreakerNode);                          // Right rotate for z
  // Update height of the nodes (just breakernode and its parents)
  //AVL_CalcHeight(LastNodeIns);
	return 0;
}




int avltree::AVL_RotateRL(struct st_DataNode *BreakerNode){
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
  cout<<"Rotando RL por "<<BreakerNode->sm_int64_key<<endl;
  AVL_RotateLL(BreakerNode->sm__point_RightChild);
	AVL_RotateRR(BreakerNode);
  // Update height of the nodes (just breakernode and its parents)
  //AVL_CalcHeight(LastNodeIns);
	return 0;
}




int32_t avltree::AVL_DetRotType(struct st_DataNode *BreakerNode){
  if( k >= 2 ){// left branch is taller than right branch
    if(BreakerNode->sm_point_LeftChild->sm_point_LeftChild != NULL && BreakerNode->sm_point_LeftChild->sm__point_RightChild != NULL){
        // Can be LL or LR
        if(BreakerNode->sm_point_LeftChild->sm_point_LeftChild->sm_int32_Height > BreakerNode->sm_point_LeftChild->sm__point_RightChild->sm_int32_Height){
          //LL case
          cout<<"LL rotation needed."<<endl;
          AVL_RotateLL(BreakerNode);
          return 1;
        }else{
          // LR case
          cout<<"LR rotation needed."<<endl;
          AVL_RotateLR(BreakerNode);
          return 2;
        }
    }

    if(BreakerNode->sm_point_LeftChild->sm_point_LeftChild == NULL && BreakerNode->sm_point_LeftChild->sm__point_RightChild != NULL){
        // Can be just LR
        cout<<"LR rotation needed."<<endl;
        AVL_RotateLR(BreakerNode);
        return 2;
    }

    if(BreakerNode->sm_point_LeftChild->sm_point_LeftChild != NULL && BreakerNode->sm_point_LeftChild->sm__point_RightChild == NULL){
        // Can be just LL
        cout<<"LL rotation needed."<<endl;
        AVL_RotateLL(BreakerNode);
        return 1;
    }

  }

  if( k <= -2 ){ // Right branch is taller than right branch
    if(BreakerNode->sm__point_RightChild->sm__point_RightChild != NULL && BreakerNode->sm__point_RightChild->sm_point_LeftChild != NULL){
        // Can be RR or RL
        if(BreakerNode->sm__point_RightChild->sm__point_RightChild->sm_int32_Height > BreakerNode->sm__point_RightChild->sm_point_LeftChild->sm_int32_Height){
          //RR case
          cout<<"RR rotation needed."<<endl;
          AVL_RotateRR(BreakerNode);
          return 3;
        }else{
          // RL case
          cout<<"RL rotation needed."<<endl;
          AVL_RotateRL(BreakerNode);
          return 4;
        }
    }

    if(BreakerNode->sm__point_RightChild->sm__point_RightChild == NULL && BreakerNode->sm__point_RightChild->sm_point_LeftChild != NULL){
      // Can be just RL cause rr child is null
      cout<<"RL rotation needed."<<endl;
      AVL_RotateRL(BreakerNode);
      return 4;
    }

    if(BreakerNode->sm__point_RightChild->sm__point_RightChild != NULL && BreakerNode->sm__point_RightChild->sm_point_LeftChild == NULL){
      // Can be just RR cause rl child is null
      cout<<"RR rotation needed."<<endl;
      AVL_RotateRR(BreakerNode);
      return 3;
    }

  }
  return 0;

}



// Function to calculate the height of the parental ancestry of the last node inserted
int32_t avltree::AVL_CalcHeight(struct st_DataNode *NodeChecked){

	//This is the root, no more recursivity -> GO OUT
	if (NodeChecked->sm_boo_IsRoot == true){
		return 0;
	}else{

	l_pcmNewNode = NodeChecked->sm_ParentNode; // Assign to l_pcmNewNode the parent of the node checked

  // Calculate height of NodeChecked prior to l_pcmNewNode
  if(NodeChecked->sm_point_LeftChild == NULL && NodeChecked->sm__point_RightChild == NULL){
    NodeChecked->sm_int32_Height = 1;
	}
  if(NodeChecked->sm_point_LeftChild != NULL && NodeChecked->sm__point_RightChild == NULL){
    NodeChecked->sm_int32_Height = NodeChecked->sm_point_LeftChild->sm_int32_Height + 1;
	}
  if(NodeChecked->sm_point_LeftChild == NULL && NodeChecked->sm__point_RightChild != NULL){
    NodeChecked->sm_int32_Height = NodeChecked->sm__point_RightChild->sm_int32_Height + 1;
	}
  if(NodeChecked->sm_point_LeftChild != NULL && NodeChecked->sm__point_RightChild != NULL){
    l_pcmAuxNode1 = NodeChecked->sm_point_LeftChild;
		l_pcmAuxNode2 = NodeChecked->sm__point_RightChild;
    if(l_pcmAuxNode1->sm_int32_Height >= l_pcmAuxNode2->sm_int32_Height){
			NodeChecked->sm_int32_Height = l_pcmAuxNode1->sm_int32_Height + 1;
		}else{NodeChecked->sm_int32_Height = l_pcmAuxNode2->sm_int32_Height + 1;}
	}

	// Updating the height of the parent of Node Checked

  // Easy cases where there is just one child
	if(l_pcmNewNode->sm_point_LeftChild == NULL || l_pcmNewNode->sm__point_RightChild == NULL){
		l_pcmNewNode->sm_int32_Height = NodeChecked->sm_int32_Height + 1;
	}

	// Complex cases where there is left and right children
	if(l_pcmNewNode->sm_point_LeftChild != NULL && l_pcmNewNode->sm__point_RightChild != NULL){
		l_pcmAuxNode1 = l_pcmNewNode->sm_point_LeftChild;
		l_pcmAuxNode2 = l_pcmNewNode->sm__point_RightChild;

		/* Check if the height of the left child is higher or equal to the height of
		 * the right child, if so, replace the its height with the height of the lc+1
		 * otherwhise it will be replaced with rc+1
 		 */
		if(l_pcmAuxNode1->sm_int32_Height >= l_pcmAuxNode2->sm_int32_Height){
			l_pcmNewNode->sm_int32_Height = l_pcmAuxNode1->sm_int32_Height + 1;
		}else{l_pcmNewNode->sm_int32_Height = l_pcmAuxNode2->sm_int32_Height + 1;}
	}

	// Calculate the k = lc_height - rc_height
	k = l_u32cmK_Rupture(l_pcmNewNode);
  // Determines the kind of rotation to execute and executes it
  int32_t aux = AVL_DetRotType(l_pcmNewNode);
  cout<<"root es "<<l_pcmRootNode->sm_int64_key<<endl;
  if(l_pcmRootNode->sm_point_LeftChild != NULL){cout<<"lc del root es "<<l_pcmRootNode->sm_point_LeftChild->sm_int64_key<<endl;}
  if(l_pcmRootNode->sm__point_RightChild != NULL){cout<<"rc del root es "<<l_pcmRootNode->sm__point_RightChild->sm_int64_key<<endl;}
  if(aux == 2 || aux == 4){
    cout<<"caso no LL ni RR"<<endl;
    cout<<"l_pcmNewNode es "<<l_pcmNewNode->sm_int64_key<<endl;
    /* rotation was LR or RL and the height calc is different cause
     * last node inserted is parent of its parents before rotation
     */

     // l_pcmNewNode could be the rc or lc of Last Node Inserted, but this doesn´t matter
     // cause anyway will be one of the childs of Last Node Inserted

     // Case where both childs are NULL
     if(l_pcmNewNode->sm_point_LeftChild == NULL && l_pcmNewNode->sm__point_RightChild == NULL){
       l_pcmNewNode->sm_int32_Height = 1;
     }

     // Easy cases where there is just one child
   	if(l_pcmNewNode->sm_point_LeftChild != NULL && l_pcmNewNode->sm__point_RightChild == NULL){
   		l_pcmNewNode->sm_int32_Height = l_pcmNewNode->sm_point_LeftChild->sm_int32_Height + 1;
   	}
    if(l_pcmNewNode->sm_point_LeftChild == NULL && l_pcmNewNode->sm__point_RightChild != NULL){
   		l_pcmNewNode->sm_int32_Height = l_pcmNewNode->sm__point_RightChild->sm_int32_Height + 1;
   	}

   	// Complex cases where there is left and right children
   	if(l_pcmNewNode->sm_point_LeftChild != NULL && l_pcmNewNode->sm__point_RightChild != NULL){
   		l_pcmAuxNode1 = l_pcmNewNode->sm_point_LeftChild;
   		l_pcmAuxNode2 = l_pcmNewNode->sm__point_RightChild;

   		/* Check if the height of the left child is higher or equal to the height of
   		 * the right child, if so, replace the its height with the height of the lc+1
   		 * otherwhise it will be replaced with rc+1
    		 */
   		if(l_pcmAuxNode1->sm_int32_Height >= l_pcmAuxNode2->sm_int32_Height){
   			l_pcmNewNode->sm_int32_Height = l_pcmAuxNode1->sm_int32_Height + 1;
   		}else{l_pcmNewNode->sm_int32_Height = l_pcmAuxNode2->sm_int32_Height + 1;}
   	}


      if(l_pcmNewNode->sm_ParentNode->sm_point_LeftChild == l_pcmNewNode){
      // We need to analyze the right child
      l_pcmAuxNode3 = l_pcmNewNode->sm_ParentNode->sm__point_RightChild;

      // Case where both childs are NULL
      if(l_pcmAuxNode3->sm_point_LeftChild == NULL && l_pcmAuxNode3->sm__point_RightChild == NULL){
        l_pcmAuxNode3->sm_int32_Height = 1;
      }

      if(l_pcmAuxNode3->sm_point_LeftChild != NULL && l_pcmAuxNode3->sm__point_RightChild == NULL){
     		l_pcmAuxNode3->sm_int32_Height = l_pcmAuxNode3->sm_point_LeftChild->sm_int32_Height + 1;
     	}
      if(l_pcmAuxNode3->sm_point_LeftChild == NULL && l_pcmAuxNode3->sm__point_RightChild != NULL){
     		l_pcmAuxNode3->sm_int32_Height = l_pcmAuxNode3->sm__point_RightChild->sm_int32_Height + 1;
     	}

     	// Complex cases where there is left and right children
     	if(l_pcmAuxNode3->sm_point_LeftChild != NULL && l_pcmAuxNode3->sm__point_RightChild != NULL){
        l_pcmAuxNode2 = l_pcmAuxNode3->sm__point_RightChild;
     		l_pcmAuxNode1 = l_pcmAuxNode3->sm_point_LeftChild;

     		/* Check if the height of the left child is higher or equal to the height of
     		 * the right child, if so, replace the its height with the height of the lc+1
     		 * otherwhise it will be replaced with rc+1
      		 */
     		if(l_pcmAuxNode1->sm_int32_Height >= l_pcmAuxNode2->sm_int32_Height){
     			l_pcmAuxNode3->sm_int32_Height = l_pcmAuxNode1->sm_int32_Height + 1;
     		}else{l_pcmAuxNode3->sm_int32_Height = l_pcmAuxNode2->sm_int32_Height + 1;}
     	}
    }else{
      // We need to analyze the left child
      l_pcmAuxNode3 = l_pcmNewNode->sm_ParentNode->sm_point_LeftChild;

      // Case where both childs are NULL
      if(l_pcmAuxNode3->sm_point_LeftChild == NULL && l_pcmAuxNode3->sm__point_RightChild == NULL){
        l_pcmAuxNode3->sm_int32_Height = 1;
      }

      if(l_pcmAuxNode3->sm_point_LeftChild != NULL && l_pcmAuxNode3->sm__point_RightChild == NULL){
     		l_pcmAuxNode3->sm_int32_Height = l_pcmAuxNode3->sm_point_LeftChild->sm_int32_Height + 1;
     	}
      if(l_pcmAuxNode3->sm_point_LeftChild == NULL && l_pcmAuxNode3->sm__point_RightChild != NULL){
     		l_pcmAuxNode3->sm_int32_Height = l_pcmAuxNode3->sm__point_RightChild->sm_int32_Height + 1;
     	}

     	// Complex cases where there is left and right children
     	if(l_pcmAuxNode3->sm_point_LeftChild != NULL && l_pcmAuxNode3->sm__point_RightChild != NULL){
        l_pcmAuxNode2 = l_pcmAuxNode3->sm__point_RightChild;
     		l_pcmAuxNode1 = l_pcmAuxNode3->sm_point_LeftChild;

     		/* Check if the height of the left child is higher or equal to the height of
     		 * the right child, if so, replace the its height with the height of the lc+1
     		 * otherwhise it will be replaced with rc+1
      		 */
     		if(l_pcmAuxNode1->sm_int32_Height >= l_pcmAuxNode2->sm_int32_Height){
     			l_pcmAuxNode3->sm_int32_Height = l_pcmAuxNode1->sm_int32_Height + 1;
     		}else{l_pcmAuxNode3->sm_int32_Height = l_pcmAuxNode2->sm_int32_Height + 1;}
     	}
    }
  }
  cout<<"altura de "<<l_pcmNewNode->sm_int64_key<<" es "<<l_pcmNewNode->sm_int32_Height<<endl;
  if(l_pcmNewNode->sm_point_LeftChild != NULL){
    cout<<"lc de "<<l_pcmNewNode->sm_int64_key<<" es "<<l_pcmNewNode->sm_point_LeftChild->sm_int64_key;
    cout<<" y su h es "<<l_pcmNewNode->sm_point_LeftChild->sm_int32_Height<<endl;
  }
  if(l_pcmNewNode->sm__point_RightChild != NULL){
    cout<<"rc de "<<l_pcmNewNode->sm_int64_key<<" es "<<l_pcmNewNode->sm__point_RightChild->sm_int64_key;
    cout<<" y su h es "<<l_pcmNewNode->sm__point_RightChild->sm_int32_Height<<endl;
  }
	// Here I have to evaluate if is necessary to rotate due to |k|>=2
	// Recursive function to re-calculate the heights of all its parental ancestry
  AVL_CalcHeight(l_pcmNewNode);
  }
}


struct st_DataNode* avltree::AVL_Search(struct st_DataNode *ActualNode, uint64_t u64SearchedNode){
  if(u64SearchedNode > ActualNode->sm_int64_key){
    if(ActualNode->sm__point_RightChild != NULL){
      AVL_Search(ActualNode->sm__point_RightChild, u64SearchedNode);
    }else{
      cout<<"The person does not exist in our database."<<endl;
      return ActualNode;
    }
  }
  if(u64SearchedNode < ActualNode->sm_int64_key){
    if(ActualNode->sm_point_LeftChild != NULL){
      AVL_Search(ActualNode->sm_point_LeftChild, u64SearchedNode);
    }else{
      cout<<"The person does not exist in our database."<<endl;
      return ActualNode;
    }
  }
  if(u64SearchedNode == ActualNode->sm_int64_key){
    cout<<"Your person is "<<ActualNode->sm_str_Name<<", with ID "<<ActualNode->sm_int64_key<<endl;
    return ActualNode;
  }
  if(u64SearchedNode < ActualNode->sm_int64_key && ActualNode->sm_point_LeftChild == NULL){
    cout<<"The person does not exist in our database."<<endl;
    return ActualNode;
  }
  if(u64SearchedNode > ActualNode->sm_int64_key && ActualNode->sm__point_RightChild == NULL){
    cout<<"The person does not exist in our database."<<endl;
    return ActualNode;
  }
}
