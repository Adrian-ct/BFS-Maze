#pragma once
#include <QPoint>

class Node
{
public:
	enum class NodType :uint16_t
	{
		EZid,
		ERoad,
		EExit,
		EEntrance,
		EWalked,
		None
	};

	Node(const uint16_t& nr, NodType nodType);
	Node(const QPointF& point, const uint16_t& nr);

public:

	QPointF GetPoint()const;
	void SetPoint(const QPointF& point);
	void SetNumber(const uint16_t& newNumber);
	uint16_t GetNumber()const;

	NodType GetTypeBeforeTraversal()const;
	NodType GetTypeAfterTraversal()const;
	uint16_t GetSteps()const;
	void SetSteps(uint16_t steps);
	void SetWalked();

private:
	NodType m_nodType[2];
	QPointF m_point;
	uint16_t m_number;
	uint16_t m_steps;
};

