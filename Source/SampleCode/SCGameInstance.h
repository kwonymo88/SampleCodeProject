// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UObject/StrongObjectPtr.h"
#include "SCGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLECODE_API USCGameInstance : public UGameInstance
{
	GENERATED_BODY()
	

public:
	virtual void Init() override;
	virtual void Shutdown() override;
};
