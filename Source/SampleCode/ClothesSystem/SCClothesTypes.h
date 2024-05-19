 //Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SCClothesTypes.generated.h"

UENUM(BlueprintType)
enum class EEquipType : uint8
{
	NONE
	, FULLS
	, OUTER
	, SHIRT
	, DRESS
	, SUIT
	, SKIRT
	, GLOVE
	, PANTS
	, SOCKS
	, UNDER
	, HAT
	, HAIR
	, SHOES
	, MAX UMETA(Hidden)
};
ENUM_RANGE_BY_COUNT(EEquipType, EEquipType::MAX);