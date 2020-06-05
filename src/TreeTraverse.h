/*******************************************************************************
*
* Copyright (c) 2011 by Tech Soft 3D, LLC.
* The information contained herein is confidential and proprietary to
* Tech Soft 3D, LLC., and considered a trade secret as defined under
* civil and criminal statutes.  Tech Soft 3D shall pursue its civil
* and criminal remedies in the event of unauthorized use or misappropriation
* of its trade secrets.  Use of this information by anyone other than
* authorized employees of Tech Soft 3D, LLC. is granted only under a
* written non-disclosure agreement, expressly prescribing the scope and
* manner of such use.
*
*******************************************************************************/

#ifndef	  A3D_TREE_CONNECTOR
#define	 A3D_TREE_CONNECTOR
	
#include <vector>
#include "Connector.h"

class A3DVisitor;


class A3DProductOccurenceConnector	: public A3DConnector
{
public :

	A3DProductOccurenceConnector(const A3DAsmProductOccurrence* pProductOccurence)	
		:  A3DConnector(pProductOccurence)
	{
		A3D_INITIALIZE_DATA( A3DAsmProductOccurrenceData, m_sProductOccurenceData);
		A3DAsmProductOccurrenceGet(pProductOccurence, &m_sProductOccurenceData);
	}

	~A3DProductOccurenceConnector()	{ A3DAsmProductOccurrenceGet(NULL,  &m_sProductOccurenceData); }	

	A3DStatus TraversePO(const A3DAsmProductOccurrence* pOccurrence, A3DVisitor* psVisitor);

private :

	A3DStatus CollectSons(std::vector<A3DAsmProductOccurrence*>& apSons) const;

	A3DStatus GetPart(A3DAsmPartDefinition*& pPart) const;

public :

	A3DAsmProductOccurrenceData m_sProductOccurenceData;
};


class A3DPartConnector : public  A3DConnector
{
public:
	A3DPartConnector(const A3DAsmPartDefinition *pPart) : A3DConnector(pPart) 
	{
		A3D_INITIALIZE_DATA(A3DAsmPartDefinitionData, m_sPartData);
		A3DAsmPartDefinitionGet(pPart, &m_sPartData);
	}
	~A3DPartConnector()
	{
		A3DAsmPartDefinitionGet(NULL, &m_sPartData);
	}
	A3DStatus TraversePart(A3DVisitor*  psVisitor);

public :
	A3DAsmPartDefinitionData m_sPartData;
};

class A3DRiConnector : public  A3DConnector
{
	
public:
	
	A3DRiConnector(const A3DRiRepresentationItem *pRi) : A3DConnector(pRi)
	{
		A3D_INITIALIZE_DATA(A3DRiRepresentationItemData, m_sRiData);
		A3DRiRepresentationItemGet(pRi, &m_sRiData);
	}

	A3DStatus TraverseRI(A3DVisitor*  psVisitor);

public :

	A3DRiRepresentationItemData m_sRiData;
};
#endif