#include "DoubleNode.h"

DoubleNode DoubleNode::NIL = DoubleNode();

DoubleNode::DoubleNode()
{
	content = string();
	next = &NIL;
	prev = &NIL;
}



DoubleNode::DoubleNode(string contentNode)
{
	content = contentNode;
	next = &NIL;
	prev = &NIL;
}