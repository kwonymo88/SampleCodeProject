// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SCManager.generated.h"

UCLASS()
class SAMPLECODE_API USCManager : public UObject
{
	GENERATED_BODY()

public:
	virtual void Init();
	virtual void ShutDown();
};
