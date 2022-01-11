#include "Maze.h"
#include <QColorDialog>

Maze::Maze(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	std::ifstream f("data.txt");
	f >> graf;
	f.close();
	std::ofstream g("debug.txt");
	g << graf;
	g.close();
	graf.MakeNeighbours();
}

void Maze::paintEvent(QPaintEvent* event)
{
	QPainter p(this);

	this->drawGraf(p);
	drawBFS(p);
	//this->drawPixels(p);
}

void Maze::drawGraf(QPainter& p)
{
	QPointF startPoint;
	float X = 700, Y = 400;
	float nodeSize = 30;
	float distanceBetweenNodes = 70;
	uint16_t nrLines, nrCols;
	nrLines = graf.getNrLines();
	nrCols = graf.getNrCols();

	startPoint.setX(X);
	startPoint.setY(Y);
	graf.GetVectorOfNodes().at(0)->SetPoint(startPoint);
	QPen pen;
	pen.setWidth(20);
	pen.setColor(Qt::blue);
	p.setBrush(QBrush(Qt::green));

	for (int i = 0; i < nrLines; i++)
	{
		for (int j = 0; j < nrCols; j++)
		{
			Node* node = graf.GetVectorOfNodes().at(i * nrCols + j);
			node->SetPoint(QPointF(X, Y));
			uint16_t nodeNumber = graf.GetVectorOfNodes().at(i * nrCols + j)->GetNumber();

			switch (node->GetTypeBeforeTraversal())
			{
			case Node::NodType::EExit:
				p.setBrush(QBrush(Qt::red));
				break;
			case Node::NodType::EEntrance:
				p.setBrush(QBrush(Qt::cyan));
				break;
			case Node::NodType::ERoad:
				p.setBrush(QBrush(Qt::lightGray));
				break;
			case Node::NodType::EZid:
				p.setBrush(QBrush(Qt::black));
				break;
			}

			p.drawEllipse(node->GetPoint().x() - nodeSize / 2, node->GetPoint().y() - nodeSize / 2,
				nodeSize, nodeSize);
			p.drawText(X - 2, Y + 2, QString::number(nodeNumber + 1));
			X += distanceBetweenNodes;
		}
		Y += distanceBetweenNodes;
		X = 700;
	}

	const auto& neighbours = graf.getNeighbours();
	for (const auto& it : neighbours)
	{
		for (const auto& it2 : it.second)
		{
			QPointF sourcePoint, destPoint;
			QLineF line(graf.GetVectorOfNodes().at(it.first)->GetPoint(),
				graf.GetVectorOfNodes().at(it2)->GetPoint());
			qreal length = line.length();


			if (length > qreal(10.)) {
				QPointF edgeOffset(((line.dx() * qreal(nodeSize / 2)) / length),
					((line.dy() * qreal(nodeSize / 2)) / length));

				sourcePoint = line.p1() + edgeOffset;
				destPoint = line.p2() - edgeOffset;
			}
			else {
				sourcePoint = destPoint = line.p1();
			}

			QPen pen;
			pen.setWidth(2);

			p.setPen(pen);
			p.drawLine(sourcePoint, destPoint);
		}
	}
}

void Maze::drawBFS(QPainter& p)
{
	uint16_t startNode = graf.getStartNode();
	std::queue<int> positions;

	bool* traversed = new bool[graf.GetVectorOfNodes().size()];
	for (int i = 0; i < graf.GetVectorOfNodes().size(); i++)
		traversed[i] = false;

	const std::vector<Node*>& nodes = graf.GetVectorOfNodes();
	positions.push(startNode);

	while (!positions.empty())
	{
		int find = positions.front();
		traversed[find] = true;
		positions.pop();

		if (graf.getNeighbours().find(find) != graf.getNeighbours().end())
		{
			for (int neighbour : graf.getNeighbours().at(find))
			{
				if (!traversed[neighbour] && nodes[neighbour]->GetTypeBeforeTraversal() != Node::NodType::EExit)
				{
					positions.push(neighbour);
					nodes[neighbour]->SetSteps(nodes[find]->GetSteps() + 1);
					//nodes[neighbour]->SetWalked();
				}
				else
					if (nodes[neighbour]->GetTypeBeforeTraversal() == Node::NodType::EExit)
					{
						nodes[neighbour]->SetSteps(nodes[find]->GetSteps() + 1);
						SetPathBack(neighbour);
					}
			}
		}
	}

	drawPixels(p);
	delete[] traversed;
}

void Maze::SetPathBack(uint16_t node)
{
	const std::vector<Node*>& nodes = graf.GetVectorOfNodes();
	node = graf.Previous(node);
	while (nodes[node]->GetTypeBeforeTraversal() != Node::NodType::EEntrance)
	{
		nodes[node]->SetWalked();
		node = graf.Previous(node);
	}
}

void Maze::drawPixels(QPainter& p)
{
	int rectSize = 50;
	uint16_t nrLines, nrCols;
	float X = 50, Y = 60;
	nrLines = graf.getNrLines();
	nrCols = graf.getNrCols();
	QString stringToWrite;
	for (int i = 0; i < nrLines; i++)
	{
		for (int j = 0; j < nrCols; j++)
		{
			stringToWrite = "";
			Node* node = graf.GetVectorOfNodes().at(i * nrCols + j);
			node->SetPoint(QPointF(X, Y));
			uint16_t nodeNumber = graf.GetVectorOfNodes().at(i * nrCols + j)->GetNumber();

			switch (node->GetTypeAfterTraversal())
			{
			case Node::NodType::EExit:
				p.setBrush(QBrush(Qt::red));
				stringToWrite = "Exit";
				break;
			case Node::NodType::EEntrance:
				p.setBrush(QBrush(Qt::cyan));
				stringToWrite = "Entrance";
				break;
			case Node::NodType::ERoad:
				p.setBrush(QBrush(Qt::lightGray));
				break;
			case Node::NodType::EZid:
				p.setBrush(QBrush(Qt::black));
				break;
			case Node::NodType::EWalked:
				p.setBrush(QBrush(Qt::green));
				break;
			}

			p.drawRect(node->GetPoint().x() - rectSize / 2, node->GetPoint().y() - rectSize / 2,
				rectSize, rectSize);
			if (stringToWrite != "")
				p.drawText(X - 5, Y + 2, stringToWrite);
			X += rectSize;
		}
		Y += rectSize;
		X = 50;
	}
}
