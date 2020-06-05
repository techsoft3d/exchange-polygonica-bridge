//#include "stdafx.h"
#include "PgVisitTesselation.h"


PgVisitTesselation::PgVisitTesselation() : m_Points(NULL)
{
}


PgVisitTesselation::~PgVisitTesselation()
{
	if (m_Points != NULL) free( m_Points );
}

A3DStatus PgVisitTesselation::DrawSolid(const A3DRiRepresentationItem* pRi)
{
	A3DStatus iRet = A3D_SUCCESS;
	A3DRiRepresentationItemData	sRiData;
	A3D_INITIALIZE_DATA(A3DRiRepresentationItemData, sRiData);
	CHECK_RET(A3DRiRepresentationItemGet(pRi, &sRiData));

	A3DTessDataConnector sTessConnector(sRiData.m_pTessBase);

	//Get Points 
	double* pdPoints;
	unsigned uPointsSize;
	sTessConnector.Points(pdPoints, uPointsSize);

	// Get Indice
	std::vector<unsigned int> auIndices;

	sTessConnector.IndicesAsTriangleWithNormals(auIndices);

	std::vector<unsigned int>::iterator auIndicesIterator;

	// Create Hoops Visualize Buffer
	unsigned int uNbTriangles = auIndices.size() / 6;
	//HPoint * /*const*/ points = new HPoint[uNbTriangles * 3];
	m_Points = (HPoint*)malloc(sizeof(HPoint) * uNbTriangles * 3);
	m_PointsSize = uNbTriangles * 3;
	//float * const points = new float[uNbTriangles * 3][3];

	//Create Hoops Visualize Indice Buffer
	int* piIndice = new int[uNbTriangles * 4]; //(3, Pt Intice, Pt Indice, Pt Indice, 3, Pt Indice, Pt Indice, Pt Inidce, .....)
	int* piIndiceIter = piIndice;

	unsigned int uCount = 0;
	for (auIndicesIterator = auIndices.begin(); auIndicesIterator != auIndices.end(); piIndiceIter++, auIndicesIterator++, uCount++)
	{
		if (!(uCount % 3))							//Next Triangle
			*piIndiceIter++ = 3;
		*piIndiceIter = uCount;
		auIndicesIterator++;					//To skip Normal Indice
		m_Points[uCount].x = pdPoints[*auIndicesIterator];
		m_Points[uCount].y = pdPoints[*auIndicesIterator + 1];
		m_Points[uCount].z = pdPoints[*auIndicesIterator + 2];
	}
	unsigned uNbPtNormal = uCount;
	//HC_KEY shell_key = HC_KInsert_Shell(uNbPtNormal, points, uNbTriangles * 4, piIndice);
	//delete[] points;
	delete[] piIndice;

	A3DRiRepresentationItemGet(NULL, &sRiData);//*/
	return A3D_ERROR;
}
