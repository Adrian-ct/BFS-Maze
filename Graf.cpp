#include "Graf.h"

Graf::~Graf()
{
	for (Node* node : m_nodes)
		delete node;
	m_nodes.clear();

	for (Arc* arc : m_arcs)
		delete arc;
	m_arcs.clear();

}

const std::vector<Node*>& Graf::GetVectorOfNodes()
{
	return m_nodes;
}

const std::vector<Arc*>& Graf::GetVectorOfArcs()
{
	return m_arcs;
}

void Graf::pushNode(Node* node)
{
	m_nodes.push_back(node);
}

void Graf::pushArcs(Arc* arc)
{
	m_arcs.push_back(arc);
}

void Graf::pushArcs(Node* n1, Node* n2)
{
	m_arcs.push_back(new Arc(n1, n2));
}

void Graf::MakeNeighbours() {
	int16_t lines[] = { -1,1,0,0 };
	int16_t cols[] = { 0,0,-1,1 };
	//std::ofstream of("debug.txt");
	
	//bool* traversed = new bool[m_nodes.size()];
	/*for (int i = 0; i < m_nodes.size(); i++)
		traversed[i] = false;*/

	for (int i = 0; i < m_nrLines; i++)
	{
		for (int j = 0; j < m_nrCols; j++)
			if (m_nodes[i * m_nrCols + j]->GetTypeBeforeTraversal() != Node::NodType::EZid)
			{
				//traversed[i * m_nrCols + j] = true;

				int node = m_nodes[i * m_nrCols + j]->GetNumber();
				for (int k = 0; k < 4; k++)
				{
					int16_t newLine = (i + lines[k]);
					int16_t newCols = (j + cols[k]);
					int pos = newLine * m_nrCols + newCols;

					if (valid(i + lines[k], j + cols[k]) && m_nodes[pos]->GetTypeBeforeTraversal() != Node::NodType::EZid)
					{
						if (m_nodes[pos]->GetTypeBeforeTraversal() == Node::NodType::EEntrance)
							startNode = pos;
						int16_t neighbour = m_nodes[pos]->GetNumber();

						m_neighbours[node].insert(neighbour);
					}
				}
			}
	}

	
	//of.close();
	//delete[] traversed;
}

bool Graf::valid(uint16_t line, uint16_t column)
{
	return (line >= 0 && line < m_nrLines&& column >= 0 && column < m_nrCols);
}

uint16_t Graf::getNrLines() const
{
	return m_nrLines;
}

uint16_t Graf::getNrCols() const
{
	return m_nrCols;
}

uint16_t Graf::getStartNode() const
{
	return startNode;
}

const std::unordered_map<int, std::unordered_set<int>>& Graf::getNeighbours() 
{
	return m_neighbours;
}

uint16_t Graf::Previous(uint16_t node)
{
	for (int x : m_neighbours[node])
	{
		if (m_nodes[x]->GetSteps() == m_nodes[node]->GetSteps() - 1)
			return x;
	}
	return 0;
}

std::istream& operator>>(std::istream& in, Graf& graf)
{
	uint32_t count = 0;
	uint16_t nrLines = 0;
	std::string aux;

	std::getline(in, aux);
	graf.m_nrCols = aux.size();

	while (!aux.empty()) {
		nrLines++;
		for (char i : aux) {
			if (i >= '0' && i <= '3')
			{
				int x = i - '0';
				graf.pushNode(new Node(count++, static_cast<Node::NodType>(x)));
			}
		}
		aux = "";
		std::getline(in, aux);
	}

	graf.m_nrLines = nrLines;

	return in;
}

std::ostream& operator<<(std::ostream& o, Graf& graf)
{
	for (int i = 0; i < graf.m_nrLines; i++)
	{
		for (int j = 0; j < graf.m_nrCols; j++)
			o << static_cast<int>(graf.m_nodes[i * graf.m_nrCols + j]->GetTypeBeforeTraversal());
		o << "\n";
	}
	return o;
}
