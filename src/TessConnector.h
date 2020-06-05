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

#ifndef	 A3D_TESS_CONNECTOR
#define	 A3D_TESS_CONNECTOR
	

#include <vector>
#include "Connector.h"



class A3DTessDataConnector : public A3DConnector
{
	A3DTess3DData m_sTessData;
	A3DTessBaseData m_sBaseTessData;


public :
	
	A3DTessDataConnector(const A3DTess3D* pTess3D);
	~A3DTessDataConnector();

	unsigned FacesSize() { return m_sTessData.m_uiFaceTessSize; }
	
	A3DStatus Points(double*& pPoint, unsigned int& uSize)		const;
	
	A3DStatus Normals(double*& pNormal, unsigned int& uSize)	const;

		//normal, point,normal, point,..., point
	A3DStatus IndicesAsTriangleWithNormals(
					std::vector<unsigned>& auIndices) const;

	A3DStatus IndicesPerFaceAsTriangleWithNormals(
					const unsigned& uFaceIndice,
					std::vector<unsigned>& auIndices) const;

	A3DStatus Indices(	
					std::vector<unsigned>& auTrianglesOneNormal,			//(normal, point, point,..., point)
					std::vector<unsigned>& auFanOneNormal,
					std::vector<unsigned>& auStripeOneNormal,
					std::vector<unsigned>& auTrianglesWithNormals,		//normal, point, ... , normal, point
					std::vector<unsigned>& auFanWithNormals,	   
					std::vector<unsigned>& auStripeWithNormal,	
					std::vector<unsigned>& auTrianglesOneNormalTexture,	//normal,{texture...},point,{texture...},point,{texture...},point
					std::vector<unsigned>& auFanOneNormalTextured,		   
					std::vector<unsigned>& auStripeOneNormalTextured,
					std::vector<unsigned>& auTrianglesWithNormalsTextured, //normal,{texture...},point,...,normal,{texture...},point
					std::vector<unsigned>& auFanWithNormalsTextured,
					std::vector<unsigned>& auStripeWithNormalsTextured) const;

	A3DStatus IndicesPerFace(
					const unsigned& uFaceIndice,
					std::vector<unsigned>& auTrianglesOneNormal,			//(normal, point, point,..., point)
					std::vector<unsigned>& auFanOneNormal,
					std::vector<unsigned>& auStripeOneNormal,
					std::vector<unsigned>& auTrianglesWithNormals,		//normal, point, ... , normal, point
					std::vector<unsigned>& auFanWithNormals,	   
					std::vector<unsigned>& auStripeWithNormal,	
					std::vector<unsigned>& auTrianglesOneNormalTexture,	//normal,{texture...},point,{texture...},point,{texture...},point
					std::vector<unsigned>& auFanOneNormalTextured,		   
					std::vector<unsigned>& auStripeOneNormalTextured,
					std::vector<unsigned>& auTrianglesWithNormalsTextured,//normal,{texture...},point,...,normal,{texture...},point
					std::vector<unsigned>& auFanWithNormalsTextured,
					std::vector<unsigned>& auStripeWithNormalsTextured) const;
};


#endif

										