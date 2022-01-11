#pragma once
#include "Node.h"

class Arc
{
public:
	enum class Type : uint16_t
	{
		EPath,
		ECycle
	};

	Arc() = default;
	Arc(Node* n1, Node* n2);
	Arc(Node* n1, Node* n2, Type type);
	Node* const getFirstNode()const;
	Node* const getSecondNode()const;
	Type getType()const;

private:
	Type m_type;
	Node* m_node1, * m_node2;

};

