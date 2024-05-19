// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StaticDataInterface.h"
#include "SCTestStaticData.generated.h"

UCLASS(Blueprintable)
class SAMPLECODE_API USCTestStaticData : public UObject, public IStaticDataInterface
{
	GENERATED_BODY()
	
	//============= Begin Implements IStaticDataInterface ============
public:
	virtual void Clean() {}
	virtual void Initialization() {}
	//============= End Implements IStaticDataInterface ============
};
