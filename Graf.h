#pragma once
#include "Node.h"
#include "Arc.h"
#include <vector>
#include <fstream>
#include <algorithm>
#include <QPainter>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

class Graf
{

public:
	Graf() = default;
	~Graf();
	const std::vector<Node*>& GetVectorOfNodes();
	const std::vector<Arc*>& GetVectorOfArcs();
	void pushNode(Node* node);
	void pushArcs(Arc* arc);
	void pushArcs(Node* n1, Node* n2);
	friend std::istream& operator>>(std::istream& in,  Graf& graf);
	friend std::ostream& operator<<(std::ostream& o,  Graf& graf);
	void MakeNeighbours();
	bool valid(uint16_t line, uint16_t column);
	uint16_t getNrLines()const;
	uint16_t getNrCols()const;
	uint16_t getStartNode()const;
	const std::unordered_map<int, std::unordered_set<int>>& getNeighbours();
	uint16_t Previous(uint16_t node);

private:
	std::vector<Node*> m_nodes;
	std::vector<Arc*> m_arcs;
	uint16_t startNode;
	uint16_t m_nrLines, m_nrCols;
	std::unordered_map<int, std::unordered_set<int>> m_neighbours;
};

