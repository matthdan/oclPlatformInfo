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
static cl_platform_id* platforms = NULL;
static cl_uint platformsNum;

//! All discoverable OpenCL devices
static cl_device_id* devices = NULL;
static cl_uint devicesNum;


static cl_int status;

/**
 * This function initiate the OpenCL world and display all the informations
 * @param
 * @return
 */
void InitOCLWorld()
{
	platformsNum = oclGetPlatformNumber();
	
	for (int i = 0 ; i < platformsNum ; i++) {
		char* platformName = NULL;
		char* platformVendor = NULL;
		platformName = oclGetPlatformName(platforms[i]);
		platformVendor = oclGetPlatformVendor(platforms[i]);
		
		printf("Platform Name \t: %s \n",platformName);
		printf("Vendor Name \t: %s \n",platformVendor);
		
		devicesNum = oclGetDeviceNumber(platforms[i]);
		for(int j = 0 ; j < devicesNum ; j++){
			char* deviceName = NULL;
			char* deviceVendor = NULL;
			char* deviceVersion = NULL;
			deviceName = oclGetDeviceName( devices[j] );
			deviceVendor = oclGetDeviceVendor( devices[j] );
			deviceVersion = oclGetDeviceVersion( devices[j] );
			printf("+----- device %i \n" , j);
			printf("Device Name \t : %s \n" , deviceName);
			printf("Device Vendor \t : %s \n" , deviceVendor);
			printf("Device Version \t : %s \n" , deviceVersion);
			oclInformationForDevice( devices[j] );
		}
	}
}

/**
 * This function return the number of openCL platform
 * @param cl_platform_id
 * @return cl_uint number of platform
 */
cl_uint oclGetPlatformNumber()
{
	cl_uint platformsNb;
	status = clGetPlatformIDs(1, NULL, &platformsNb);
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
		// INIT
		platforms = (cl_platform_id*)malloc(platformsNb *sizeof(cl_platform_id));
		clGetPlatformIDs(platformsNb,
						 platforms,
						 NULL);
		
	}
	
	return platformsNb;
}

cl_uint oclGetDeviceNumber( cl_platform_id platform )
{
	cl_device_type deviceType = CL_DEVICE_TYPE_ALL;
	// if(devicePreference == 'c') {
	//   deviceType = CL_DEVICE_TYPE_CPU;
	// }
	// if(devicePreference == 'g') {
	//   deviceType = CL_DEVICE_TYPE_GPU;
	// }
	cl_uint numDeviceForThisPlatform;
	
	status = clGetDeviceIDs(platform ,
							deviceType,
							0,
							NULL,
							&numDeviceForThisPlatform );
	// If Error
	if (status != CL_SUCCESS)
    {
		printf("Error: Failure in clGetDeviceIDs \n");
		printf("Error: %d \n", status );
		exit(-1);
    }
	else if(numDeviceForThisPlatform == 0) {
		// no device available
		printf("No OpenCL device found\n");
		exit(-1);
	}
	else {
		printf("Number of device for this platform : %i \n", numDeviceForThisPlatform );
		// INIT
		devices = (cl_device_id*)malloc(sizeof(cl_device_id)*numDeviceForThisPlatform);
		status = clGetDeviceIDs(platform,
								deviceType,
								numDeviceForThisPlatform,
								devices,
								NULL);
		// if Error
		if (status != CL_SUCCESS)
		{
			printf("Error: Failure in clGetDeviceIDs __LINE__ \n");
			printf("Error: %d \n", status );
			exit(-1);
		}
	}
	
	return numDeviceForThisPlatform;
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

//! The the name of the device as supplied by the OpenCL implementation
char* oclGetDeviceName(cl_device_id dev)
{
	size_t devInfoSize;
	char* devInfoStr = NULL;
	
	// If dev is NULL, set it to the default device
	// if(dev == NULL) {
	//   dev = *devices;
	//}
	
	// Print the name
	status = clGetDeviceInfo(dev,
							 CL_DEVICE_NAME,
							 0,
							 NULL,
							 &devInfoSize);
	//if Error
	
	devInfoStr = (char*)malloc(devInfoSize);
	
	status = clGetDeviceInfo(dev,
							 CL_DEVICE_NAME,
							 devInfoSize,
							 devInfoStr,
							 NULL);
	//if Error
	
	return(devInfoStr);
}

//! Get the name of the vendor for a device
char* oclGetDeviceVendor(cl_device_id dev)
{
	size_t devInfoSize;
	char* devInfoStr = NULL;
	
	// If dev is NULL, set it to the default device
	// if(dev == NULL) {
	//   dev = *devices;
	// }
	
	// Print the vendor
	status = clGetDeviceInfo(dev,
							 CL_DEVICE_VENDOR,
							 0,
							 NULL,
							 &devInfoSize);
	// if Error
	
	devInfoStr = (char*)malloc(devInfoSize);
	
	status = clGetDeviceInfo(dev,
							 CL_DEVICE_VENDOR,
							 devInfoSize,
							 devInfoStr,
							 NULL);
	
	// If error
	
	return devInfoStr;
}

//! Get the name of the vendor for a device
char* oclGetDeviceVersion(cl_device_id dev)
{
	size_t devInfoSize;
	char* devInfoStr = NULL;
	
	// If dev is NULL, set it to the default device
	// if(dev == NULL) {
	//   dev = *devices;
	// }
	
	// Print the vendor
	status = clGetDeviceInfo(dev,
							 CL_DEVICE_VERSION,
							 0,
							 NULL,
							 &devInfoSize);
	// if Error
	
	devInfoStr = (char*)malloc(devInfoSize);
	
	status = clGetDeviceInfo(dev,
							 CL_DEVICE_VERSION,
							 devInfoSize,
							 devInfoStr,
							 NULL);
	// If Error
	
	return devInfoStr;
}

void oclInformationForDevice(cl_device_id dev)
{
	cl_ulong devGlobalSize;
	cl_ulong devLocalSize;
	cl_ulong unitKB = 1024;
	cl_ulong unitMB = 1048576;
	
	status = clGetDeviceInfo(dev,
							 CL_DEVICE_GLOBAL_MEM_SIZE,
							 sizeof(devGlobalSize),
							 &devGlobalSize,
							 NULL);
	//  If Error
	
	status = clGetDeviceInfo(dev,
							 CL_DEVICE_LOCAL_MEM_SIZE,
							 sizeof(devLocalSize),
							 &devLocalSize,
							 NULL);
	//  If Error
	
	printf("Global memroy size : %lu Bytes = %lu KBits = %lu MBits\n",devGlobalSize, devGlobalSize/unitKB, devGlobalSize/unitMB);
	printf("Local memroy size : %lu Bytes = %lu KBits\n",devLocalSize, devLocalSize/unitKB);
	
}

void oclCleanUp()
{
	
}

