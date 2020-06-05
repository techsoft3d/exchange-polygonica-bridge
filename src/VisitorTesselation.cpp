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
#include "VisitorTesselation.h"
#include "TessConnector.h"

#define CHECK_RET { if (iRet!=A3D_SUCCESS) return iRet; }

A3DStatus A3DVisitorTesselation::visitEnter(const A3DRiConnector& sRiConnector)
{
	const A3DEntity* pRi  = sRiConnector.GetA3DEntity();
	A3DEEntityType eType=kA3DTypeUnknown;
	A3DStatus iRet = A3D_SUCCESS;
	CHECK_RET(A3DEntityGetType(pRi,&eType));
	if (iRet==A3D_SUCCESS)
	{
		switch(eType)
		{
			case kA3DTypeRiPointSet:
				break;
			case kA3DTypeRiDirection:
				break;
			case kA3DTypeRiCurve:
				break;
			case kA3DTypeRiCoordinateSystem:
				break;
			case kA3DTypeRiPlane:
				break;
			case kA3DTypeRiBrepModel:

				CHECK_RET(DrawSolid(pRi));
				
				break;
			case kA3DTypeRiPolyBrepModel:
				CHECK_RET(DrawSolid(pRi));
				break;
			
			default:
				iRet=A3D_NOT_IMPLEMENTED;
				break;
		}
	}
	return iRet;
}

A3DStatus A3DVisitorTesselation::visitLeave(const A3DRiConnector& sRi)
{
	return A3D_SUCCESS;
}
