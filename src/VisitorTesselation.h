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

#ifndef A3D_VISIST_TESSELLATION
#define A3D_VISIST_TESSELLATION

#include "Visitors.h"

class A3DVisitorTesselation : public A3DVisitor
{
	 friend A3DVisitorContainer;

public:
	A3DVisitorTesselation(A3DVisitorContainer* psContainer = NULL) : A3DVisitor(psContainer) {};
	virtual ~A3DVisitorTesselation() {}

	virtual A3DStatus visitEnter(const A3DRiConnector& sConnector);
	virtual A3DStatus visitLeave(const A3DRiConnector& sConnector);

	virtual A3DStatus DrawSolid(const A3DRiRepresentationItem* pRi) { return A3D_SUCCESS; }
	virtual A3DStatus DrawCurve(const A3DRiRepresentationItem* pRi) {  return A3D_SUCCESS;}

};
#endif

