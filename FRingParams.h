#pragma once
#include "FRingParams.generated.h"


USTRUCT(BlueprintType)

struct FRingParams
{
	GENERATED_BODY()

	/**
	Number of asteroids in the ring
	*/

	UPROPERTY(EditAnywhere, BlueprintReadonly)
	int NumAsteroids = 100;
	/**
	Total radius of the ring
	*/
	UPROPERTY(EditAnywhere, BlueprintReadonly)
	float MajorRadius = 1000.f;
	/**
	Width of the ring
	*/
	UPROPERTY(EditAnywhere, BlueprintReadonly)
	float MinorRadius = 10000.f;
	/**
	Rotation of the ring
	*/

};
