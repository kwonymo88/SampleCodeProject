//// Copyright(c) Burning Galaxy LTD. All Rights Reserved.
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "Components/ActorComponent.h"
//#include "GameCore/Keyword/AvatarKeyword.h"
//#include "GalaxyCore/Public/Clothes/GCClothSystemComponent.h"
//#include "AEClothSystemComponent.generated.h"
//
///**
// * 
// */
//struct FAEClothObjectInfo;
//struct FMaterialInfo;
//
//class UAEClothObject;
//class AAeCharacterBase;
//class UUnrealEquipMeshData;
//class UMeshComponent;
//
//struct FAECreateClothObjectInfo : public FGCCreateClothObjectInfo
//{
//	
//};
//
//UCLASS(BlueprintType, Blueprintable)
//class UClothObjectClassData : public UGCClothObjectClassData
//{
//	GENERATED_BODY()
//
//};
//
//USTRUCT()
//struct FDefaultPutOnCloth : public FGCDefaultPutOnCloth
//{
//	GENERATED_USTRUCT_BODY()
//
//};
//
//UCLASS(Blueprintable)
//class WORLD_API UAEClothSystemComponent : public UGCClothSystemComponent
//{
//	GENERATED_BODY()
//	
//protected:
//	UPROPERTY(Transient)
//	TWeakObjectPtr<AAeCharacterBase>	_CachedAECharacter;
//	
//public:
//	UAEClothSystemComponent(const FObjectInitializer& ObjectInitializer);
//	virtual void OnRegister() override;
//
//public:
//	UGCClothObject* PutOnClothItemByResourcePath(const FString& resourcePath, bool bPlayAnim = false);
//	UMeshComponent* GetGroomCompByEquipType(EEquipType equipType) const;
//
//public:
//	virtual void InitDefaultClothObject() override;
//	virtual void PutOnDefaultUnder() override;
//	virtual void BindCharacterEvents() override;
//	virtual void UnbindCharacterEvents() override;
//	virtual void UpdateClothDataActiveMyAvatarInfo() override;
//	virtual UGCClothObject* MakeDefaultSpecifyClothObject(const FName& objectName) override;
//
//	virtual FName MakeNewObjectName(const EEquipType equipType) const override;
//};
