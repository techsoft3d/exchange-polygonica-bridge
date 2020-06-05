// simple.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// Loads a file using HOOPS Exchange, converts part into a Polygonica Solid and saves to an STL.
//

#include <iostream>

#include "pgapi.h"
#include "pgkey.h"

#include "../../src/ExchangePolygonicaBridge.h"

PTEnvironment pg_environment;

static void handle_pg_error(PTStatus status, char* err_string)
{
	PTStatus status_code;
	PTStatus err_code;
	PTStatus func_code;
	PTStatus fatal_error = PV_STATUS_OK;
	/* The status is made up of 3 parts */
	status_code = PM_STATUS_FROM_API_ERROR_CODE(status);
	func_code = PM_FN_FROM_API_ERROR_CODE(status);
	err_code = PM_ERR_FROM_API_ERROR_CODE(status);
	if (status_code & PV_STATUS_BAD_CALL)
	{
		printf("PG:BAD_CALL: Function %d Error %d: %s\n", func_code, err_code, err_string);
	}
	if (status_code & PV_STATUS_MEMORY)
	{
		printf("PG:MEMORY: Function %d Error %d: %s\n", func_code, err_code, err_string);
		fatal_error |= status;
	}
	if (status_code & PV_STATUS_EXCEPTION)
	{
		printf("PG:EXCEPTION: Function %d Error %d: %s\n", func_code, err_code, err_string);
		fatal_error |= status;
	}
	if (status_code & PV_STATUS_FILE_IO)
	{
		printf("PG:FILE I/0: Function %d Error %d: %s\n", func_code, err_code, err_string);
	}
	if (status_code & PV_STATUS_INTERRUPT)
	{
		printf("PG:INTERRUPT: Function %d Error %d: %s\n", func_code, err_code, err_string);
	}
	if (status_code & PV_STATUS_INTERNAL_ERROR)
	{
		printf("PG:INTERNAL_ERROR: Function %d Error %d: %s\n", func_code, err_code, err_string);
		fatal_error |= status;
	}
}

int InitializePolygonica()
{
	PTStatus status = PFInitialise(PV_LICENSE, NULL);
	if (status) {
		printf("Polygonica failed to initialize.\n");
		return status;
	}

	status = PFEnvironmentCreate(NULL, &pg_environment);
	if (status) {
		printf("Failed to create Polygonica environment.");
		return status;
	}

	PFEntitySetPointerProperty(pg_environment, PV_ENV_PROP_ERROR_REPORT_CB, handle_pg_error);

	printf("Polygonica Loaded.\n");
	return status;
}

int main()
{   
	InitializePolygonica();

	ExchangePolygonicaBridge bridge(pg_environment);
	
	PTSolid solid = NULL;
	int ret = bridge.Process((char*)"Ring.CATPart", &solid);

	/* ADD ADDITIONAL POLYGONICA CODE HERE */

	PTStream stream;
	PTStreamFileOpts stream_options;
	stream_options.filename_is_wchar = 0;
	ret = PFStreamFileOpen((char*)"Ring.stl", PV_FILE_WRITE, &stream_options, &stream);

	ret = PFSolidWrite(solid, PV_SOLID_DATA_BINARY_STL, stream, NULL);
	ret = PFStreamClose(stream);

	PFEnvironmentDestroy(pg_environment);
	PFTerminate();
}