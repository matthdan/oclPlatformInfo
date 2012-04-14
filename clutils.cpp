/*
 * Differents functions to get platform and device information
 *
 * Copyright (C) 2012  Matthieu DANIEL <matth.daniel@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

#include "clutils.h"

/**
 * Functions to get platform and informations the machine which execute this code!
 * @author Matthieu DANIEL
 */

//! All discoverable OpenCL platforms
static cl_platform_id platforms = NULL;
static cl_uint platformsNum;

//! All discoverable OpenCL devices
static cl_device_id devices = NULL;
static cl_uint devicesNum;


static cl_int status;

/**
 * This function initiate the OpenCL world and display all the informations
 * @param 
 * @return 
 */
void InitOCLWorld()
{
	
	platformsNum = oclGetPlatformNumber(platforms);
	for (int i = 0 ; i < platformsNum ; i++) {
		char* platformName = NULL;
        char* platformVendor = NULL;
		platformName = oclGetPlatformName(platforms);
		platformVendor = oclGetPlatformVendor(platforms);
		
		printf("Platform Name \t: %s \n",	platformName);
		printf("Vendor Name \t: %s \n",platformVendor);
		
	}
	
}

/**
 * This function return the number of openCL platform
 * @param cl_platform_id
 * @return cl_uint number of platform
 */
cl_uint oclGetPlatformNumber(cl_platform_id platform)
{
	cl_uint platformsNb;
	status = clGetPlatformIDs(1, &platform, &platformsNb);
	if (status != CL_SUCCESS)
	{
		printf("Error: Failure in clGetPlatformIDs \n");
		printf("Error: %d \n", status );
		exit(-1);
	}
	else if(platformsNb == 0) {
		// no platform available
		printf("No OpenCL platforms found\n");
        exit(-1);
	}
	else {
		printf("Number of plateforms : %i \n", platformsNb );
	}


	return platformsNb;
}

/**
 * This function return the name of openCL platform
 * @param cl_platform_id
 * @return char* name of the OpenCL platform
 */

char* oclGetPlatformName(cl_platform_id platform)
{
    size_t platformInfoSize;
    char* platformInfoStr = NULL;
	
    status = clGetPlatformInfo(platform, 
							   CL_PLATFORM_NAME, 
							   0, 			
							   NULL, 
							   &platformInfoSize);	
    if (status != CL_SUCCESS)
	{
		printf("Error: Failure in oclGetPlatformName \n");
		printf("Error: %d \n", status );
		exit(-1);
	}
	
    platformInfoStr = (char*)malloc(platformInfoSize);
	
    status = clGetPlatformInfo(platform, 
							   CL_PLATFORM_NAME, 
							   platformInfoSize, 			
							   platformInfoStr, 
							   NULL);	
    if (status != CL_SUCCESS)
	{
		printf("Error: Failure in oclGetPlatformName \n");
		printf("Error: %d \n", status );
		exit(-1);
	}
	
    return(platformInfoStr);
}

/**
 * This function return the vendor of openCL platform
 * @param cl_platform_id
 * @return char* name of the OpenCL vendor
 */

char* oclGetPlatformVendor(cl_platform_id platform)
{
	size_t platformInfoSize;
    char* platformInfoStr = NULL;
	
    status = clGetPlatformInfo(platform, 
							   CL_PLATFORM_VENDOR, 
							   0, 			
							   NULL, 
							   &platformInfoSize);	
    if (status != CL_SUCCESS)
	{
		printf("Error: Failure in oclGetPlatformVendor \n");
		printf("Error: %d \n", status );
		exit(-1);
	}
	
    platformInfoStr = (char*)malloc(platformInfoSize);
	
    status = clGetPlatformInfo(platform, 
							   CL_PLATFORM_VENDOR,
							   platformInfoSize, 			
							   platformInfoStr,
							   NULL);	
    if (status != CL_SUCCESS)
	{
		printf("Error: Failure in oclGetPlatformVendor \n");
		printf("Error: %d \n", status );
		exit(-1);
	}
	
    return(platformInfoStr);
}

