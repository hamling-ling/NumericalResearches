#pragma once
#ifndef MODELTYPE_H
#define MODELTYPE_H

#define MODEL_DELTA_T		0.033
#define MODEL_POINTS_LEN	3		// must be an odd number

namespace osakanamodel {

	typedef double MODELFLOAT;

	typedef struct MODELPOINT
	{
		MODELFLOAT x;
		MODELFLOAT y;
	} ModelPoint;

	typedef struct {
		MODELFLOAT theta;
		MODELFLOAT omega;
		MODELFLOAT t;
		MODELPOINT points[MODEL_POINTS_LEN];
	} SOLUTION;

	typedef union _MODELVEC3D
	{
		struct { MODELFLOAT x, y, z;};
		MODELFLOAT v[3];
	} MODELVEC3D;

	typedef union _MODELLINE
	{
		struct {
			MODELVEC3D a;
			MODELVEC3D b;
		};
		MODELVEC3D v[2];
	} MODELLINE;

	typedef union _SKIRECT
	{
		struct {
			MODELVEC3D bottom_left;
			MODELVEC3D bottom_right;
			MODELVEC3D top_right;
            MODELVEC3D top_left;
		};
		MODELVEC3D v[4];
	} MODELRECT;
}

#endif
