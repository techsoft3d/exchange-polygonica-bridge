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


#ifndef A3D_VISITOR
#define A3D_VISITOR



//#include <TessConnector.h>
//#include <TreeTraverse.h>

#include "TessConnector.h"
#include "TreeTraverse.h"

#define CHECK_RET { if (iRet!=A3D_SUCCESS) return iRet; }	

class A3DConnector;
class A3DVisitorContainer;
class A3DVisitor
{
	A3DVisitorContainer* m_psContainer;
public :
	A3DVisitor(A3DVisitorContainer* psContainer = NULL) : m_psContainer(psContainer){}

	virtual A3DStatus visitEnter(const A3DConnector& sConnector) { return A3D_SUCCESS; }
	virtual A3DStatus visitLeave(const A3DConnector& sConnector) { return A3D_SUCCESS; }

	virtual A3DStatus visitEnter(const A3DRiConnector& sConnector) { return A3D_ERROR; }
	virtual A3DStatus visitLeave(const A3DRiConnector& sConnector) { return A3D_ERROR; }

	virtual A3DStatus visitEnter(const A3DPartConnector& sConnector) { return A3D_ERROR; }
	virtual A3DStatus visitLeave(const A3DPartConnector& sConnector) { return A3D_ERROR; }	

	virtual A3DStatus visitEnter(const A3DProductOccurenceConnector& sConnector) { return A3D_ERROR; }
	virtual A3DStatus visitLeave(const A3DProductOccurenceConnector& sConnector) { return A3D_ERROR; }	
};
 

class A3DAllNodeVisitor : public A3DVisitor
{
	
public :
	A3DAllNodeVisitor(A3DVisitorContainer* psContainer = NULL) : A3DVisitor(psContainer){}

	virtual A3DStatus visitEnter(const A3DConnector& sConnector) { return A3D_SUCCESS; }
	virtual A3DStatus visitLeave(const A3DConnector& sConnector) { return A3D_SUCCESS; }

	virtual A3DStatus visitEnter(const A3DRiConnector& sConnector) { return visitEnter((const A3DConnector&)sConnector); }
	virtual A3DStatus visitLeave(const A3DRiConnector& sConnector) { return visitLeave((const A3DConnector&)sConnector); }

	virtual A3DStatus visitEnter(const A3DPartConnector& sConnector) { return visitEnter((const A3DConnector&)sConnector); }
	virtual A3DStatus visitLeave(const A3DPartConnector& sConnector) { return visitLeave((const A3DConnector&)sConnector); }	

	virtual A3DStatus visitEnter(const A3DProductOccurenceConnector& sConnector) { return visitEnter((const A3DConnector&)sConnector); }
	virtual A3DStatus visitLeave(const A3DProductOccurenceConnector& sConnector) { return visitLeave((const A3DConnector&)sConnector); }	
};

#endif