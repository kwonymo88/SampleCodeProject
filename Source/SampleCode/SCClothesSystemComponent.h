// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SCClothesSystemComponent.generated.h"

enum class EEquipType : uint8;

class USCClothesObject;
class ASCCharacter;
class USCClothesItemDataAsset;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCreatedClothesObjectDelegate, const USCClothesObject*, CreatedClothesObject);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRemoveClothesObjectDelegate, const USCClothesObject*, RemoveClothesObject);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateClothesObjectDelegate, const USCClothesObject*, UpdateClothesObject);

UCLASS( BlueprintType, Blueprintable )
class SAMPLECODE_API USCClothesObjectClassData : public UObject
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "ClothesObjectClassData|Setting")
	TMap<EEquipType, TSubclassOf<USCClothesObject>> ClothesObjectClasses;

public:
	/* USCClothesObject::StaticClass()의 리턴을 보장합니다 */
	TSubclassOf<USCClothesObject> GetClothesObjectClass(const EEquipType FindEquipType) const;
};

UCLASS( ClassGroup=(ClothesSystem), meta=(Blueprintable, BlueprintSpawnableComponent) )
class SAMPLECODE_API USCClothesSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USCClothesSystemComponent();

protected:
	virtual void BeginPlay() override;
	virtual void OnRegister() override;
	virtual void BeginDestroy() override;

protected:
	virtual void InitOwnerCharacter();
	virtual void LoadClothesObjectClassesData();
	virtual void LoadDefaultClothesItem();

	virtual void TakeOffClothes(const EEquipType TakeOffEquipType);
	virtual void TakeOffAllClothes();
	virtual bool InternalPutOnClothes(const USCClothesItemDataAsset* ClothesItemData);

public:
	virtual bool PutOnClothesItem(const USCClothesItemDataAsset* ClothesItemData);
	ASCCharacter* GetOwnerSCCharacter() const { return OwnerCharacter; }

protected:
	UPROPERTY(EditDefaultsOnly, Category="ClothesSystem|ClothesObjectClassData")
	TSubclassOf<USCClothesObjectClassData> ClothesObjectClassDataClass;

	UPROPERTY(Transient, BlueprintReadOnly, Category="ClothesSystem|ClothesObjectClassData")
	TObjectPtr<USCClothesObjectClassData>	ClothesObjectClassData;

	UPROPERTY(Transient, BlueprintReadOnly)
	TObjectPtr<ASCCharacter> OwnerCharacter;

	UPROPERTY(Transient, BlueprintReadOnly)
	TMap<EEquipType, TObjectPtr<USCClothesObject>> EquipedClothesObjects;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="ClothesSystem|Setting")
	TArray<TObjectPtr<USCClothesItemDataAsset>> DefaultClothesItemDataAsset;

//================ Begin Events ===============
public:
	UPROPERTY(BlueprintAssignable, Transient, Category="ClothesSystem|Events")
	FCreatedClothesObjectDelegate OnCreatedClothesObjectDelegate;

	UPROPERTY(BlueprintAssignable, Transient, Category="ClothesSystem|Events")
	FRemoveClothesObjectDelegate OnRemoveClothesObjectDelegate;

	UPROPERTY(BlueprintAssignable, Transient, Category="ClothesSystem|Events")
	FUpdateClothesObjectDelegate OnUpdateClothesObjectDelegate;
//================ End Events =================

};
