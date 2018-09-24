/*
*Author: Erick Obando Solano B14757
*Date: 20 Sep 2018

*Go to Readme for variable declaration Nomenclature
*Obtain data from a file and generates an AVL Tree node
*/
#ifndef AVL
#define AVL

#include <iostream>
#include <string>
#include "avltree_ObtainData.hpp"

class avltree{
	public:
		avltree();
		int AVL_Insert(struct st_node *ActualNode, struct st_node *InsertedNode);    // Inserts checking balance
		//int AVL_Delete(struct st_node *DeletedNode);
		int AVL_RotateLL(struct st_node *BreakerNode);                     // Activated if AVL_Insert returns 1
		int AVL_RotateRR(struct st_node *BreakerNode);                     // Activated if AVL_Insert returns 2
		int AVL_RotateLR(struct st_node *BreakerNode);                     // Activated if AVL_Insert returns 3
		int AVL_RotateRL(struct st_node *BreakerNode);                     // Activated if AVL_Insert returns 4
		int32_t AVL_CalcHeight(struct st_node *NodeChecked);
		int32_t l_u32cmK_Rupture(struct st_node *LastNodeInserted);     // This variable will check the first K rupture (K>1)
		struct st_node *l_pcmRootNode = NULL;                              // It will point to the root of the AVL

	private:
		// AUX nodes
		struct st_node *l_pcmNewNode = NULL;                               // Temporary saver of parent node
		// 1-> saver of lc || 2-> saver of rc
		struct st_node *l_pcmAuxNode1 = NULL;
		struct st_node *l_pcmAuxNode2 = NULL;

};



/*AVL::AVL(void){
	// Do nothing, just declare it, the magic comes later
}*/

#endif
