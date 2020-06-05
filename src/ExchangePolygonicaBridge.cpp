#include "ExchangePolygonicaBridge.h"

#include <iostream>

#include "hoops_license.h"

#define INITIALIZE_A3D_API
#include "A3DSDKIncludes.h"

#include "PgVisitTesselation.h"

ExchangePolygonicaBridge::ExchangePolygonicaBridge(PTEnvironment pg_environment) {
	this->pg_environment = pg_environment;
	
	if (!A3DSDKLoadLibrary(NULL))
	{
		printf("Cannot load exchange library\n");
		return;
	}

	if (A3D_SUCCESS != A3DLicPutUnifiedLicense(HOOPS_LICENSE)) {
		printf("Invalid Exchange License.\n");
		return;
	}

	A3DInt32 iMajorVersion = 0, iMinorVersion = 0;
	A3DDllGetVersion(&iMajorVersion, &iMinorVersion);

	if (A3D_SUCCESS != A3DDllInitialize(A3D_DLL_MAJORVERSION, A3D_DLL_MINORVERSION)) {
		printf("Exchange could not initialize.\n");
		return;
	}

	printf("HOOPS Exchanged Loaded.\n");
}

ExchangePolygonicaBridge::~ExchangePolygonicaBridge() {
	A3DDllTerminate();
}

int ExchangePolygonicaBridge::LoadFile(char* file_name, PgVisitTesselation* psPgVisitTesselation)
{
	A3DInt32 iRet = A3D_SUCCESS;

	//strcpy_s(filename, file_name);

	/////////////////////////////////////////////
	// 1- Load CAD file
	/////////////////////////////////////////////
	A3DRWParamsLoadData sReadParam;
	A3D_INITIALIZE_DATA(A3DRWParamsLoadData, sReadParam);
	sReadParam.m_sGeneral.m_bReadSolids = true;
	sReadParam.m_sGeneral.m_eReadGeomTessMode = kA3DReadGeomAndTess;
	sReadParam.m_sTessellation.m_eTessellationLevelOfDetail = kA3DTessLODExtraHigh;

	A3DAsmModelFile* pModelFile = NULL;
	//iRet = A3DAsmModelFileLoadFromFile(acCADFileUTF8, &sReadParam, &pModelFile);
	iRet = A3DAsmModelFileLoadFromFile(file_name, &sReadParam, &pModelFile);
	if (iRet != A3D_SUCCESS && iRet != A3D_LOAD_MISSING_COMPONENTS)
		return -1;

	/////////////////////////////////////////////
	// Traverse Assembly Tree Structure
	/////////////////////////////////////////////
	A3DAsmModelFileData sModelFileData;
	A3D_INITIALIZE_DATA(A3DAsmModelFileData, sModelFileData);
	CHECK_RET(A3DAsmModelFileGet(pModelFile, &sModelFileData));

	for (A3DUns32 uI = 0; uI < sModelFileData.m_uiPOccurrencesSize; uI++)
	{
		A3DProductOccurenceConnector sTreeConnector(sModelFileData.m_ppPOccurrences[uI]);
		CHECK_RET(sTreeConnector.TraversePO(sModelFileData.m_ppPOccurrences[uI], psPgVisitTesselation));
	}

	CHECK_RET(A3DAsmModelFileGet(NULL, &sModelFileData));
	return 0;
}

bool ExchangePolygonicaBridge::TesselationToSolid(PgVisitTesselation* psPgVisitTesselation, PTSolid* pSolid)
{
	size_t faceCount = psPgVisitTesselation->GetPointsSize() / 3; // pgArgs->shellKey.GetFaceCount();
	PTNat32* pg_faces = new PTNat32[faceCount * 3];
	PTStatus status = PFThreadRegister();

	int progress = 0;

	for (int i = 0; i < faceCount * 3; i++)
	{
		pg_faces[i] = i;
	}

	PTPoint* vertices = new PTPoint[psPgVisitTesselation->GetPointsSize()];

	progress = 0;

	for (int i = 0; i < psPgVisitTesselation->GetPointsSize(); i++)
	{
		vertices[i][0] = psPgVisitTesselation->GetPoints()[i].x;
		vertices[i][1] = psPgVisitTesselation->GetPoints()[i].y;
		vertices[i][2] = psPgVisitTesselation->GetPoints()[i].z;
	}

	status = PFSolidCreateFromMesh(
		pg_environment,
		faceCount,	// total number of triangles
		NULL,		// no internal loops
		NULL,		// all faces are triangles
		pg_faces,	// indices into vertex array
		vertices,		// pointer to vertex array
		NULL,		// no options
		pSolid		// resultant pg solid
	);

	PTSolidMergeVerticesOpts options;
	PMInitSolidMergeVerticesOpts(&options);
	status = PFSolidMergeVertices(*pSolid, &options);

	status = PFThreadUnregister();
	return status;
}

int ExchangePolygonicaBridge::Process(char* file_name, PTSolid* pSolid) {
	PgVisitTesselation sPgVisitTesselation;

	int ret = LoadFile(file_name, &sPgVisitTesselation);

	if (ret != A3D_SUCCESS) {
		printf("Failded to load file: %d\n", ret);
		return ret;
	}

	ret = TesselationToSolid(&sPgVisitTesselation, pSolid);

	if (ret != 0) {
		printf("Failed to create pg solid.\n");
	}

}