// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "StaticDataInterface.generated.h"

UINTERFACE()
class SAMPLECODE_API UStaticDataInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()

	
};

class SAMPLECODE_API IStaticDataInterface : public IInterface
{
	GENERATED_IINTERFACE_BODY()

public:
	virtual void Clean() {}
	virtual void Initialization() {}
};
