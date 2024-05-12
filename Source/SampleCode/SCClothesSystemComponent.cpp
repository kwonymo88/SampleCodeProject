// Fill out your copyright notice in the Description page of Project Settings.

#include "SampleCode.h"
#include "SCClothesSystemComponent.h"
#include "SCClothesObject.h"
#include "SCCharacter.h"
#include "SCClothesItemData.h"

// Sets default values for this component's properties
USCClothesSystemComponent::USCClothesSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USCClothesSystemComponent::OnRegister()
{
	Super::OnRegister();
	InitOwnerCharacter();
	LoadClothesObjectClassesData();
	LoadDefaultClothesItem();
}

void USCClothesSystemComponent::BeginDestroy()
{
	Super::BeginDestroy();
	TakeOffAllClothes();
}

void USCClothesSystemComponent::InitOwnerCharacter()
{
	OwnerCharacter = GetOwner<ASCCharacter>();
	if (!OwnerCharacter)
	{
		if (AActor* OwnerActor = GetOwner())
		{
			UE_LOG(LogTemp, Error, TEXT("USCClothesSystemComponent only works with ASCCharacter. [%s] "), *GetNameSafe(OwnerActor));
		}
	}
}

void USCClothesSystemComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USCClothesSystemComponent::LoadClothesObjectClassesData()
{
	check(ClothesObjectClassDataClass);

	if (ClothesObjectClassDataClass)
	{
		ClothesObjectClassData = NewObject<USCClothesObjectClassData>(this, ClothesObjectClassDataClass);
	}
}

void USCClothesSystemComponent::LoadDefaultClothesItem()
{
	for (const auto& ClothesitemDataAsset : DefaultClothesItemDataAsset)
	{
		PutOnClothesItem(ClothesitemDataAsset);
	}
}

bool USCClothesSystemComponent::PutOnClothesItem(const USCClothesItemDataAsset* ClothesItemData)
{
	if (ClothesItemData == nullptr)
	{
		return false;
	}

	TakeOffClothes(ClothesItemData->GetEquipType());
	InternalPutOnClothes(ClothesItemData);
	return false;
}

void USCClothesSystemComponent::TakeOffClothes(const EEquipType TakeOffEquipType)
{
	if (TObjectPtr<USCClothesObject>* TakeOffClothesObject = EquipedClothesObjects.Find(TakeOffEquipType))
	{
		OnRemoveClothesObjectDelegate.Broadcast((*TakeOffClothesObject));
		EquipedClothesObjects.Remove(TakeOffEquipType);
		(*TakeOffClothesObject)->ConditionalBeginDestroy();
	}
}

void USCClothesSystemComponent::TakeOffAllClothes()
{
	for (const auto& ClothesObject : EquipedClothesObjects)
	{
		OnRemoveClothesObjectDelegate.Broadcast(ClothesObject.Value);
		ClothesObject.Value->ConditionalBeginDestroy();
	}
	EquipedClothesObjects.Empty();
}

bool USCClothesSystemComponent::InternalPutOnClothes(const USCClothesItemDataAsset* ClothesItemData)
{
	check(ClothesObjectClassData != nullptr);
	TSubclassOf<USCClothesObject> ClothesObjectClass = ClothesObjectClassData->GetClothesObjectClass(ClothesItemData->GetEquipType());
	check(ClothesObjectClass);
	USCClothesObject* NewClothesObject = NewObject<USCClothesObject>(this, ClothesObjectClass);
	if (NewClothesObject->InitClothesObject(ClothesItemData))
	{
		EquipedClothesObjects.Emplace(ClothesItemData->GetEquipType(), NewClothesObject);
		OnCreatedClothesObjectDelegate.Broadcast(NewClothesObject);
		return true;
	}

	return false;
}

TSubclassOf<USCClothesObject> USCClothesObjectClassData::GetClothesObjectClass(const EEquipType FindEquipType) const
{
	if (const TSubclassOf<USCClothesObject>* FindClothesObjectClass = ClothesObjectClasses.Find(FindEquipType))
	{
		return *FindClothesObjectClass;
	}
	else
	{
		return USCClothesObject::StaticClass();
	}
}
