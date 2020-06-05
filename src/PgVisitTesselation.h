#pragma once

#include "VisitorTesselation.h"
#include "TessConnector.h"

struct HPoint
{
	double x, y, z;
};

class PgVisitTesselation : public A3DVisitorTesselation
{
	virtual A3DStatus DrawSolid(const A3DRiRepresentationItem* pRi);

	HPoint *m_Points;
	int m_PointsSize;

public:
	PgVisitTesselation();
	~PgVisitTesselation();

	HPoint* GetPoints() { return m_Points; }
	int GetPointsSize() { return m_PointsSize; }
};

