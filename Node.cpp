#include "Node.h"

Node::Node(const uint16_t& nr, Node::NodType nodType): m_number(nr),m_steps(0)
{
    m_nodType[0] = nodType;
    m_nodType[1] = nodType;
}

Node::Node(const QPointF& point, const uint16_t& nr):m_point(point), m_number(nr), m_steps(0)
{
}

QPointF Node::GetPoint() const
{
    return m_point;
}

void Node::SetPoint(const QPointF& point)
{
    m_point = point;
}

void Node::SetNumber(const uint16_t& newNumber)
{
    m_number = newNumber;
}

uint16_t Node::GetNumber() const
{
    return m_number;
}

Node::NodType Node::GetTypeBeforeTraversal() const
{
    return m_nodType[0];
}

Node::NodType Node::GetTypeAfterTraversal() const
{
    return m_nodType[1];
}

uint16_t Node::GetSteps() const
{
    return m_steps;
}

void Node::SetSteps(uint16_t steps)
{
    m_steps = steps;
}

void Node::SetWalked()
{
    m_nodType[1] = NodType::EWalked;
}
