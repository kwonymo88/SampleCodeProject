// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SCClothesItemData.generated.h"

enum class EEquipType : uint8;

USTRUCT()
struct FSCClothesItem
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	EEquipType EquipType;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USkeletalMesh> ClothesSkelMesh;
};

UCLASS(BlueprintType)
class SAMPLECODE_API USCClothesItemDataAsset : public UDataAsset
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category="ClothesItemData|ItemData")
	FSCClothesItem ClothesItem;
	
public:
	EEquipType GetEquipType() const { return ClothesItem.EquipType; }
	const FSCClothesItem& GetClothesItem() const { return ClothesItem; }
};
