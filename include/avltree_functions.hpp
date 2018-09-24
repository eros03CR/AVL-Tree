/*
 * Author: Kevin Trejos
 *
 */

#ifndef AVL
#define AVL

#include <iostream>
#include <string>
#include <stdint.h>
#include "avltree_get_data.hpp"

class avltree{
	public:
		avltree();
		int AVL_Insert(struct st_DataNode *ActualNode, struct st_DataNode *InsertedNode);    // Inserts checking balance
		struct st_DataNode *l_pcmRootNode = NULL;                              // It will point to the root of the AVL
		struct st_DataNode *AVL_Search(struct st_DataNode *ActualNode, uint64_t u64SearchedNode);

	private:
		// AUX nodes
		struct st_DataNode *l_pcmNewNode = NULL;                               // Temporary saver of parent node
		struct st_DataNode *l_pcmAuxNode1 = NULL;
		struct st_DataNode *l_pcmAuxNode2 = NULL;

		// Rotation functions
		int AVL_RotateLL(struct st_DataNode *BreakerNode);                     // Rotates if case is LL
		int AVL_RotateRR(struct st_DataNode *BreakerNode);                     // Rotates if case is RR
		int AVL_RotateLR(struct st_DataNode *BreakerNode);                     // Rotates if case is LR
		int AVL_RotateRL(struct st_DataNode *BreakerNode);                     // Rotates if case is RL

		// Auxiliary functions
		int32_t AVL_DetRotType(struct st_DataNode *BreakerNode);               // Determines the kind of rotation needed
		int32_t AVL_CalcHeight(struct st_DataNode *NodeChecked);
		int32_t l_u32cmK_Rupture(struct st_DataNode *LastNodeInserted);        // This variable will check the first K rupture (K>=2)
};



/*AVL::AVL(void){
	// Do nothing, just declare it, the magic comes later
}*/

#endif
