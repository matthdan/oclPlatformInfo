/*
 * Differents functions to get platform and device information
 *
 * Copyright (C) 2012  matthieu DANIEL <matth.daniel@gmail.com>
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

#ifndef CLUTILS_H_
#define CLUTILS_H_

#include <stdlib.h>
#include <stdio.h>
#if defined(__APPLE__) || defined(__MACOSX)
#include <OpenCL/cl.h>
#else
#include <CL/cl.h>
#endif // !__APPLE__

void InitOCLWorld();

cl_uint oclGetPlatformNumber();

cl_uint oclGetDeviceNumber( cl_platform_id );

char* oclGetPlatformName( cl_platform_id );

char* oclGetPlatformVendor( cl_platform_id );

char* oclGetDeviceName( cl_device_id );

char* oclGetDeviceVendor( cl_device_id );

char* oclGetDeviceVersion( cl_device_id );

void oclInformationForDevice( cl_device_id );


#endif /* CLUTILS_H_ */