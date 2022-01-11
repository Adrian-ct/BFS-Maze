#include "Arc.h"

Arc::Arc(Node* n1, Node* n2) :m_node1(n1), m_node2(n2)
{
}

Arc::Arc(Node* n1, Node* n2, Type type) : m_node1(n1), m_node2(n2), m_type(type)
{
}

Node* const Arc::getFirstNode() const
{
	return m_node1;
}

Node* const Arc::getSecondNode() const
{
	return m_node2;
}

Arc::Type Arc::getType() const
{
	return m_type;
}
