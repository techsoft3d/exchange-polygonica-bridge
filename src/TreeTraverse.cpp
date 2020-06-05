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
/**
\file TreeConnector.cpp	

This file demonstrates how to programmatically Integrate 3DX getting the assembly
tree structure in your application

Steps are:
   Initialize Hoops 3D Exchange.
   Open a Cad File
   Traverse the assembly tree
   Dump the assembly structure in an XML file.	  
   Close Hoosp 3D Exchange

*********************************************************************/
   
#include "Visitors.h"

#include "TreeTraverse.h"
   


/************************************************************************************

	Traversing the assembly Structure

*************************************************************************************/
A3DStatus A3DProductOccurenceConnector::TraversePO(
						const A3DAsmProductOccurrence* pOccurrence,
						A3DVisitor* psVisitor)
{
	A3DStatus iRet = A3D_SUCCESS;
	CHECK_RET(psVisitor->visitEnter(*this));
	
	
	A3DAsmPartDefinition* pPart;
	CHECK_RET(GetPart(pPart));
	
	//Exercise
	A3DPartConnector sPartConnector(pPart);
	if(pPart)
	{
		CHECK_RET(sPartConnector.TraversePart(psVisitor));
	}
	std::vector<A3DAsmProductOccurrence*> apSons;
	CollectSons(apSons);
	A3DUns32 uI;
	for (uI = 0; uI < apSons.size(); uI++)
	{
		A3DProductOccurenceConnector sPoConnector(apSons[uI]);
		CHECK_RET(sPoConnector.TraversePO(apSons[uI], psVisitor));
	}
	CHECK_RET(psVisitor->visitLeave(*this));
	return A3D_SUCCESS;
}
 
A3DStatus A3DProductOccurenceConnector::CollectSons(
					std::vector<A3DAsmProductOccurrence*>& apSons) const 
{
	//Get Children or children on Prototype's	....Prototype's
	A3DAsmProductOccurrence*	 pPrototype	= m_sProductOccurenceData.m_pPrototype;
	A3DAsmProductOccurrence** ppPo = m_sProductOccurenceData.m_ppPOccurrences;
	unsigned int uSize = m_sProductOccurenceData.m_uiPOccurrencesSize;
	A3DStatus iRet = A3D_SUCCESS;

	while(uSize == 0 && pPrototype)
   	{
		A3DAsmProductOccurrenceData sPrototypeData;
		A3D_INITIALIZE_DATA( A3DAsmProductOccurrenceData, sPrototypeData);
		CHECK_RET(A3DAsmProductOccurrenceGet(pPrototype, &sPrototypeData));
		pPrototype =sPrototypeData.m_pPrototype;

		uSize = sPrototypeData.m_uiPOccurrencesSize;
		ppPo = sPrototypeData.m_ppPOccurrences;
		
		CHECK_RET(A3DAsmProductOccurrenceGet(NULL, &sPrototypeData));
	}

 	unsigned uI;
  	for( uI = 0; uI < uSize; uI++)
		apSons.push_back(ppPo[uI]);
	
	//Get Children on Externals
	if(m_sProductOccurenceData.m_pExternalData)
	{
		if(apSons.size() == 0)
		{
			A3DProductOccurenceConnector sExternalConnector(m_sProductOccurenceData.m_pExternalData);
			CHECK_RET(sExternalConnector.CollectSons(apSons));
		}
		else
			apSons.push_back(m_sProductOccurenceData.m_pExternalData);
	}
	return A3D_SUCCESS;
}

A3DStatus A3DProductOccurenceConnector::GetPart(
					A3DAsmPartDefinition*& pPart) const
{	
	pPart = NULL;
	A3DStatus iRet = A3D_SUCCESS;;
	if(m_sProductOccurenceData.m_pPart)
	{
		pPart = m_sProductOccurenceData.m_pPart;
		return A3D_SUCCESS;
	}

	A3DAsmProductOccurrence* pProductPrototype = m_sProductOccurenceData.m_pPrototype;
	while(pProductPrototype)
	{
		A3DAsmProductOccurrenceData sProductPrototypeData;
		A3D_INITIALIZE_DATA( A3DAsmProductOccurrenceData, sProductPrototypeData);
		CHECK_RET(A3DAsmProductOccurrenceGet(pProductPrototype, &sProductPrototypeData));
		if(sProductPrototypeData.m_pPart)
		{
			pPart =  sProductPrototypeData.m_pPart;
			return A3D_SUCCESS;
		}
		else
			pProductPrototype = sProductPrototypeData.m_pPrototype;
	}
	
	if(m_sProductOccurenceData.m_uiPOccurrencesSize == 0)
	{
		if(m_sProductOccurenceData.m_pExternalData)
		{
			A3DProductOccurenceConnector sExternalconnector(m_sProductOccurenceData.m_pExternalData);
	 		CHECK_RET(sExternalconnector.GetPart(pPart));
		}
	}
	return A3D_SUCCESS; 
}


//Exercise
  
A3DStatus A3DPartConnector::TraversePart(A3DVisitor*  psVisitor)
{
	A3DStatus iRet = A3D_SUCCESS;

	CHECK_RET(psVisitor->visitEnter(*this));

	//Traverse RI
	unsigned int uI;
	for(uI = 0; uI < m_sPartData.m_uiRepItemsSize; uI++)
	{
		A3DRiConnector sRiConnector(m_sPartData.m_ppRepItems[uI]);
		sRiConnector.TraverseRI(psVisitor);
		
	}

  	CHECK_RET(psVisitor->visitLeave(*this));
	return A3D_SUCCESS;
}

A3DStatus A3DRiConnector::TraverseRI(A3DVisitor* psVisitor)
{	
	A3DStatus iRet = A3D_SUCCESS;
	psVisitor->visitEnter(*this);

	psVisitor->visitLeave(*this);
	return A3D_SUCCESS;
}

