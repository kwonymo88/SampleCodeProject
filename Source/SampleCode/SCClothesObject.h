// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SCClothesObject.generated.h"

class USCClothesItemDataAsset;
class USCClothesSystemComponent;
/**
 * 
 */
UCLASS(Blueprintable)
class SAMPLECODE_API USCClothesObject : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void BeginDestroy() override;

protected:
	UPROPERTY(Transient, BlueprintReadOnly)
	TObjectPtr<USCClothesSystemComponent> OwnerClothesSystemComponent;

	UPROPERTY(EditDefaultsOnly, Category="ClothesObject|Setting")
	TSubclassOf<USkeletalMeshComponent> ClothesSkeletalMeshCompClass;

	UPROPERTY(EditDefaultsOnly, Category = "ClothesObject|Setting")
	FName ClothesSkelMeshAttachSocketName;

	UPROPERTY(Transient, BlueprintReadOnly)
	TObjectPtr<USkeletalMeshComponent> ClothesSkeletalMeshComp;

	UPROPERTY(Transient, BlueprintReadOnly)
	TObjectPtr<const USCClothesItemDataAsset> CachedClothItemData;

protected:
	virtual void InitOwnerClothesSystemComponent();
	virtual void InternalInitClothesObject();
	virtual void CreateMeshComponentToCharacter();

public:
	bool InitClothesObject(const USCClothesItemDataAsset* ClothesItemData);
	const USkeletalMeshComponent* GetClothesSkeletalMeshComp() { return ClothesSkeletalMeshComp; }
};
