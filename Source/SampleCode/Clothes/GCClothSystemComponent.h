#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GCClothSystemComponent.generated.h"

//class UGCClothObject;
//
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCreatedClothObjectDelegate, const UGCClothObject*, CreatedClothObject);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPreRemoveClothObjectDelegate, const UGCClothObject*, PreRemoveClothObject);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateClothObjectDelegate, const UGCClothObject*, UpdateClothObject);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRemovedClothObjectDelegate, const EEquipType, RemovedClothObject);
//
//UCLASS(BlueprintType, Blueprintable)
//class GALAXYCORE_API UGCClothObjectClassData : public UObject
//{
//	GENERATED_BODY()
//	
//private:
//	UPROPERTY(EditDefaultsOnly, Category = "AE | UGCClothObjectClassData | ClothObject")
//	TMap<EEquipType, TSubclassOf<UGCClothObject>> _ClothObjectClasses;
//
//public:
//	const TSubclassOf<UGCClothObject>* GetClothObjectClass(const EEquipType equipType) const;
//};
//
//USTRUCT()
//struct FGCDefaultPutOnCloth
//{
//	GENERATED_USTRUCT_BODY()
//
//	UPROPERTY(EditAnywhere)
//	EEquipType _EquipType;
//	UPROPERTY(EditAnywhere)
//	EGenderType _GenderType;
//	UPROPERTY(EditAnywhere)
//	FString _AssetKey;
//};
//
//UCLASS(Blueprintable)
//class GALAXYCORE_API UGCClothSystemComponent : public UActorComponent
//{
//	GENERATED_BODY()
//	
//public:
//	UGCClothSystemComponent(const FObjectInitializer& ObjectInitializer);
//
//public:
//	virtual void OnRegister() override;
//	virtual void OnUnregister() override;
//	virtual void BeginPlay() override;
//
////============================= Interface =====================
//public:
//	virtual void UpdateClothDataActiveMyAvatarInfo();
//	virtual void InitDefaultClothObject();
//	void UpdateClothObject(UGCClothObject* pUpdateClothObject);
//	void UpdateCustomMaterial();
//
////=============================== Info =======================
//public:
//	UFUNCTION(BlueprintPure, Category = "AE | AEClothSystemComponent | Function")
//	static UGCClothSystemComponent* FindPawnClothSystemComponent(const AActor* Actor) { return (Actor ? Actor->FindComponentByClass<UGCClothSystemComponent>() : nullptr); }
//	UFUNCTION(BlueprintCallable, Category = "AE | AEClothSystemComponent | Function")
//	TArray<UGCClothObject*>	GetClothObjectListIgnoreBody() const;
//	UFUNCTION(BlueprintCallable, Category = "AE | AEClothSystemComponent | Function")
//	TArray<UGCClothObject*>	GetAllClothObjectList() const;
//	UMeshComponent* GetMeshCompByEquipType(EEquipType equipType) const;
//	UGCClothObject* GetClothObject(const FString& resourcePath, bool bIncludeDeferred = false) const;
//	UGCClothObject* GetClothObject(const EEquipType equipType, bool bIncludeDeferred = false) const;
//	bool			HasClothobject(const EEquipType equipType) const;
//	const TSubclassOf<UGCClothObject>	GetClothObjectClass(const EEquipType equipType) const;
//
////============================= Function ====================
//protected:
//	virtual FName MakeNewObjectName(const EEquipType equipType) const;
//	virtual UGCClothObject* MakeDefaultSpecifyClothObject(const FName& objectName);
//	void LoadClothObjectClassDataClass();
//	UGCClothObject* NewClothObject(const EEquipType equipType, const FName& objectName = NAME_None);
//	UGCClothObject* NewSpecifyClothObject(const EEquipType equipType, const FName& objectName = NAME_None);
//	virtual void PostPutOnClothObject(UGCClothObject* newClothObject);
//	virtual void DeterminePutOffCloth(UGCClothObject* newClothObject);
//	virtual void DetermineCullTexture(UGCClothObject* newClothObject);
//	virtual bool InternalTryInitCloth(const FGCCreateClothObjectInfo& createClothObjectInfo);
//
////============================= Property ========================
//protected:
//	UPROPERTY(Transient)
//	TWeakObjectPtr<ACharacter>	_OwnerCharacter;
//	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AE | AEClothSystemComponent | Info")
//	bool _bUseNewClothSystem = false;
//
//public:
//	bool GetUseNewClothSystem() const { return _bUseNewClothSystem; }
//
////============================== Data ===========================
//protected:
//	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly)
//	TMap<EEquipType, UGCClothObject*>	_ClothObjectList;
//	UPROPERTY(EditDefaultsOnly, Category = "AE | AEClothSystemComponent | Info")
//	TSubclassOf<UGCClothObjectClassData> _ClothObjectClassDataClass;
//	UPROPERTY(Transient, BlueprintReadOnly, Category = "AE | AEClothSystemComponent | Info")
//	UGCClothObjectClassData* _ClothObjectClassData;
//
////============================== DefaultCloth ===========================
//protected:
//	UPROPERTY(EditAnywhere, Category = "AE | AEClothSystemComponent | Info")
//	TArray<FGCDefaultPutOnCloth> _DefaultPutOnCloth;
//
//public:
//	virtual bool ShouldPutOnDefaultUnder() const;
//	virtual void PutOnDefaultUnder();
//
////================================ PutOn & PutOff ========================
//public:
//	UFUNCTION(BlueprintCallable, Category = "AE | AEClothSystemComponent | Function")
//	bool			PutOffAllClothObject();
//	UFUNCTION(BlueprintCallable, Category = "AE | AEClothSystemComponent | Function")
//	bool			PutOffClothObjectIgnoreBody();
//	UFUNCTION(BlueprintCallable, Category = "AE | AEClothSystemComponent | Function")
//	bool			PutOffClothObjectByEquipType(const EEquipType removeEquipType);
//	UFUNCTION(BlueprintCallable, Category = "AE | AEClothSystemComponent | Function")
//	bool			PutOffClothObject(const FString& resourcePath);
//	UFUNCTION(BlueprintCallable, Category = "AE | AEClothSystemComponent | Function")
//	virtual UGCClothObject* PutOnClothItem(const EEquipType equipType, const EGenderType genderType, const FString& assetKey, const FString& resourcePath, bool bPlayAnim = false);
//	virtual UGCClothObject* PutOnClothItem(const EEquipType equipType, const EGenderType genderType, const FString& assetKey, bool bPlayAnim = false);
//
//	bool			PutOffClothObject(UGCClothObject* pRemoveClothObject);
//	bool			PutOffClothObjectByEquipTypes(const TArray<EEquipType>& removeEquipTypes);
//
////=================== Deffered Cloth ===================
//protected:
//	// EEquipType : ParentEquip 기준으로 부착이 필요한 FAECreateClothObjectInfo에 대한 리스트 관리
//	TMap<EEquipType, TArray<FGCCreateClothObjectInfo>>	_DeferredClothObjecteList;
//
//	virtual void TryPutonClothDeferredList(const EEquipType parentEquipType);
//	virtual bool ShouldAddDeferredClothObject(const EEquipType parentEquipType, const UGCClothObject* pClothObject) const;
//	virtual void AddDeferredClothObject(const EEquipType parentEquipType, const FGCCreateClothObjectInfo& createClothObjectInfo);
//	virtual void RemoveDeferredClothObject(const EEquipType parentEquipType);
//	virtual UGCClothObject* GetDeferredClothObject(const EEquipType equipType) const;
//
//	//============================= Delegates ======================
//protected:
//	UPROPERTY(BlueprintAssignable, Category = " AE | AEClothSystemComponent | Event")
//	FCreatedClothObjectDelegate	_OnCratedClothObjectDelegate;
//
//	UPROPERTY(BlueprintAssignable, Category = " AE | AEClothSystemComponent | Event")
//	FPreRemoveClothObjectDelegate _OnPreRemoveClothObjectDelegate;
//
//	UPROPERTY(BlueprintAssignable, Category = " AE | AEClothSystemComponent | Event")
//	FUpdateClothObjectDelegate _OnUpdateClothObjectDelegate;
//
//	UPROPERTY(BlueprintAssignable, Category = " AE | AEClothSystemComponent | Event")
//	FRemovedClothObjectDelegate _OnRemovedClothObjectDelegate;
//
//public:
//	FCreatedClothObjectDelegate& GetCreatedClothObjectDelegate() { return _OnCratedClothObjectDelegate; }
//	FPreRemoveClothObjectDelegate& GetPreRemoveClothObjectDelegate() { return _OnPreRemoveClothObjectDelegate; }
//	FUpdateClothObjectDelegate& GetUpdateClothObjectDelegate() { return _OnUpdateClothObjectDelegate; }
//	FRemovedClothObjectDelegate& GetRemovedClothObjectDelegate() { return _OnRemovedClothObjectDelegate; }
//
//	//============================= Events ==========================
//protected:
//	virtual void BindCharacterEvents();
//	virtual void UnbindCharacterEvents();
//
//public:
//	virtual void OnChagnedCharcterGender(const EGenderType genderType);
//	virtual void OnSuccedClothItem(const FGCCreateClothObjectInfo& CreateClothObjectInfo, bool bPlayAnim);
//};
