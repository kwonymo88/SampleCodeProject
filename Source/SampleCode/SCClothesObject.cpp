// Fill out your copyright notice in the Description page of Project Settings.

#include "SCClothesObject.h"
#include "SCClothesItemData.h"
#include "SCClothesSystemComponent.h"
#include "SCCharacter.h"

bool USCClothesObject::InitClothesObject(const USCClothesItemDataAsset* ClothesItemData)
{
	if (ClothesItemData == nullptr)
	{
		return false;
	}
	CachedClothItemData = ClothesItemData;

	InternalInitClothesObject();
	return true;
}

void USCClothesObject::BeginDestroy()
{
	Super::BeginDestroy();

	if (ClothesSkeletalMeshComp)
	{
		ClothesSkeletalMeshComp->DestroyComponent();
		ClothesSkeletalMeshComp = nullptr;
	}
}

void USCClothesObject::InitOwnerClothesSystemComponent()
{
	OwnerClothesSystemComponent = CastChecked<USCClothesSystemComponent>(GetOuter());
}

void USCClothesObject::InternalInitClothesObject()
{
	InitOwnerClothesSystemComponent();
	CreateMeshComponentToCharacter();
}

void USCClothesObject::CreateMeshComponentToCharacter()
{
	check(OwnerClothesSystemComponent);

	if (OwnerClothesSystemComponent)
	{
		if (ASCCharacter* OwnerSCCharacter = OwnerClothesSystemComponent->GetOwnerSCCharacter())
		{
			ClothesSkeletalMeshComp = NewObject<USkeletalMeshComponent>(this, ClothesSkeletalMeshCompClass ? ClothesSkeletalMeshCompClass.Get() : USkeletalMeshComponent::StaticClass());
			ClothesSkeletalMeshComp->AttachToComponent(OwnerSCCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, ClothesSkelMeshAttachSocketName);
			ClothesSkeletalMeshComp->SetCollisionProfileName(TEXT("NoCollision"));
			ClothesSkeletalMeshComp->SetMobility(EComponentMobility::Stationary);
			ClothesSkeletalMeshComp->SetEnableGravity(false);
			ClothesSkeletalMeshComp->bApplyImpulseOnDamage = false;
			ClothesSkeletalMeshComp->SetGenerateOverlapEvents(false);
			ClothesSkeletalMeshComp->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
			ClothesSkeletalMeshComp->RegisterComponent();

			check(CachedClothItemData != nullptr);
			ClothesSkeletalMeshComp->SetSkeletalMesh(CachedClothItemData->GetClothesItem().ClothesSkelMesh);
		}
	}
}
