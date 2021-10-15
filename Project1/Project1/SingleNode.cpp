#include "SingleNode.h"



SingleNode::SingleNode()
{
	item = Item();
	next = &NIL;

}


SingleNode::SingleNode(Item itemValue)
{
	item = itemValue;
	next = &NIL;
}

SingleNode SingleNode::NIL = SingleNode();
