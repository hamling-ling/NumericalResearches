#pragma once

static const double kThreshold = 0.8;
static const unsigned int kReservedBellNumber = 64;

typedef struct _NsdfPoint {
	double value;
	uint32_t index;
	uint32_t padding;
} NsdfPoint;
