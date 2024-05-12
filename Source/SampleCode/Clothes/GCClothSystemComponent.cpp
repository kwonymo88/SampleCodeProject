// Copyright(c) Burning Galaxy LTD. All Rights Reserved.

//#include "Clothes/GCClothSystemComponent.h"

//
//UGCClothSystemComponent::UGCClothSystemComponent(const FObjectInitializer& ObjectInitializer)
//	: Super(ObjectInitializer)
//{
//	SetComponentTickEnabled(false);
//}
//
//void UGCClothSystemComponent::OnRegister()
//{
//	Super::OnRegister();
//	_ClothObjectList.Reserve((int32)EEquipType::MAX);
//	_OwnerCharacter = GetOwner<ACharacter>();
//	if (!_OwnerCharacter.IsValid())
//	{
//		UE_LOG_WITH_SCREEN_MSG_PRESET_WARNING(TEXT("[UGCClothSystemComponent::OnRegister] not parent AAeCharacterBase"));
//		DestroyComponent();
//	}
//	BindCharacterEvents();
//}
//
//void UGCClothSystemComponent::OnUnregister()
//{
//	Super::OnUnregister();
//	UnbindCharacterEvents();
//	for (auto& Clothobject : _ClothObjectList)
//	{
//		Clothobject.Value->BeginDestroyClothObject();
//	}
//	_ClothObjectList.Empty();
//}
//
//void UGCClothSystemComponent::BeginPlay()
//{
//	Super::BeginPlay();
//	LoadClothObjectClassDataClass();
//}
//
//TArray<UGCClothObject*> UGCClothSystemComponent::GetClothObjectListIgnoreBody() const
//{
//	TArray<UGCClothObject*> ClothObjectList;
//	for (const auto& ClothObjectItem : _ClothObjectList)
//	{
//		if (ClothObjectItem.Value->GetEquipType() > EEquipType::BASE)
//		{
//			ClothObjectList.Emplace(ClothObjectItem.Value);
//		}
//	}
//	return ClothObjectList;
//}
//
//TArray<UGCClothObject*> UGCClothSystemComponent::GetAllClothObjectList() const
//{
//	TArray<UGCClothObject*> ClothObjectList;
//	for (const auto& ClothObjectItem : _ClothObjectList)
//	{
//		ClothObjectList.Emplace(ClothObjectItem.Value);
//	}
//	return ClothObjectList;
//}
//
//UGCClothObject* UGCClothSystemComponent::PutOnClothItem(const EEquipType equipType, const EGenderType genderType, const FString& assetKey, const FString& resourcePath, bool bPlayAnim)
//{
//	if (assetKey.IsEmpty())
//		return nullptr;
//
//	bool bNewClothObject = false;
//	UGCClothObject* pAEClothObject = GetClothObject(equipType);
//	if (!pAEClothObject)
//	{
//		bNewClothObject = true;
//		pAEClothObject = NewClothObject(equipType, MakeNewObjectName(equipType));
//	}
//	check(pAEClothObject);
//
//	FGCCreateClothObjectInfo CreateClothObjectInfo;
//	CreateClothObjectInfo.Init(equipType, genderType, assetKey, resourcePath, bPlayAnim, pAEClothObject);
//	if (ShouldAddDeferredClothObject(pAEClothObject->GetParentEquipType(), pAEClothObject))
//	{
//		AddDeferredClothObject(pAEClothObject->GetParentEquipType(), CreateClothObjectInfo);
//		return nullptr;	//DeferedList에 들어가면 성공일지 실패일지 모르니 일단 nullptr 로 리턴
//	}
//	else
//	{
//		InternalTryInitCloth(CreateClothObjectInfo);
//	}
//
//	return pAEClothObject;
//}
//
//UGCClothObject* UGCClothSystemComponent::PutOnClothItem(const EEquipType equipType, const EGenderType genderType, const FString& assetKey, bool bPlayAnim)
//{
//	return PutOnClothItem(equipType, genderType, assetKey, FString(), bPlayAnim);
//}
//
//bool UGCClothSystemComponent::InternalTryInitCloth(const FGCCreateClothObjectInfo& createClothObjectInfo)
//{
//	if (createClothObjectInfo._ClothObject == nullptr)
//	{
//		return false;
//	}
//
//	bool bCreatedClothObject = false;
//
//	FGCClothObjectInfo	ClothObjectInfo;
//	ClothObjectInfo.Init(createClothObjectInfo._EquipType, createClothObjectInfo._GenderType, createClothObjectInfo._AssetKey, createClothObjectInfo._ResourcePath);
//	if (createClothObjectInfo._ClothObject->SetClothObjectInfo(ClothObjectInfo))
//	{
//		//bool bPlayAnim = createClothObjectInfo._ClothObject->IsA(UAEClothObject_Groom::StaticClass()) ? false : createClothObjectInfo._bPlayAnim;
//		OnSuccedClothItem(createClothObjectInfo, createClothObjectInfo._bPlayAnim);
//		if (createClothObjectInfo._ClothObject)
//		{
//			_ClothObjectList.FindOrAdd(createClothObjectInfo._EquipType, createClothObjectInfo._ClothObject);
//			if (_OnCratedClothObjectDelegate.IsBound())
//			{
//				_OnCratedClothObjectDelegate.Broadcast(createClothObjectInfo._ClothObject);
//			}
//			PostPutOnClothObject(createClothObjectInfo._ClothObject);
//
//			TryPutonClothDeferredList(createClothObjectInfo._EquipType);
//
//			bCreatedClothObject = true;
//		}
//	}
//	else
//	{
//		createClothObjectInfo._ClothObject->BeginDestroyClothObject();
//	}
//
//	if (createClothObjectInfo._EquipType == EEquipType::SHOES)
//	{
//
//	}
//	return bCreatedClothObject;
//}
//
//FName UGCClothSystemComponent::MakeNewObjectName(const EEquipType equipType) const
//{
//	return FName();
//}
//
//void UGCClothSystemComponent::UpdateClothDataActiveMyAvatarInfo()
//{	
//
//}
//
//UMeshComponent* UGCClothSystemComponent::GetMeshCompByEquipType(EEquipType equipType) const
//{
//	UGCClothObject* pClothObject = GetClothObject(equipType);
//	return pClothObject ? pClothObject->GetMeshComponent() : nullptr;
//}
//
//bool UGCClothSystemComponent::PutOffClothObject(const FString& resourcePath)
//{
//	if (UGCClothObject* TargetClothObject = GetClothObject(resourcePath))
//	{
//		return PutOffClothObject(TargetClothObject);
//	}
//	return false;
//}
//
//bool UGCClothSystemComponent::PutOffClothObject(UGCClothObject* pRemoveClothObject)
//{
//	if (pRemoveClothObject)
//	{
//		if (_OnPreRemoveClothObjectDelegate.IsBound())
//		{
//			_OnPreRemoveClothObjectDelegate.Broadcast(pRemoveClothObject);
//		}
//
//		const EEquipType TargetEquipType = pRemoveClothObject->GetEquipType();
//
//		pRemoveClothObject->BeginDestroyClothObject();
//		if (_ClothObjectList.Remove(TargetEquipType))
//		{
//			_OnRemovedClothObjectDelegate.Broadcast(TargetEquipType);
//
//			if (ShouldPutOnDefaultUnder())
//			{
//				PutOnDefaultUnder();
//			}
//
//			return true;
//		}
//	}
//	return false;
//}
//
//bool UGCClothSystemComponent::PutOffAllClothObject()
//{
//	TMap<EEquipType, UGCClothObject*> CopyClothObjectList = _ClothObjectList;
//	for (auto& Clothobject : CopyClothObjectList)
//	{
//		PutOffClothObjectByEquipType(Clothobject.Value->GetEquipType());
//	}
//
//	if (ShouldPutOnDefaultUnder())
//	{
//		PutOnDefaultUnder();
//	}
//
//	return true;
//}
//
//bool UGCClothSystemComponent::PutOffClothObjectIgnoreBody()
//{
//	TMap<EEquipType, UGCClothObject*> CopyClothObjectList = _ClothObjectList;
//	for (auto& Clothobject : CopyClothObjectList)
//	{
//		if (FGCClothesTypeHelper::IsClothesIgnoreBody(Clothobject.Value->GetEquipType()))
//		{
//			PutOffClothObjectByEquipType(Clothobject.Value->GetEquipType());
//		}
//	}
//
//	if (ShouldPutOnDefaultUnder())
//	{
//		PutOnDefaultUnder();
//	}
//
//	return false;
//}
//
//bool UGCClothSystemComponent::PutOffClothObjectByEquipType(const EEquipType removeEquipType)
//{
//	if (UGCClothObject** pClothObject = _ClothObjectList.Find(removeEquipType))
//	{
//		return PutOffClothObject(*pClothObject);
//	}
//	return false;
//}
//
//bool UGCClothSystemComponent::PutOffClothObjectByEquipTypes(const TArray<EEquipType>& removeEquipTypes)
//{
//	for (const auto& removeEquipType : removeEquipTypes)
//	{
//		PutOffClothObjectByEquipType(removeEquipType);
//	}
//	return true;
//}
//
//UGCClothObject* UGCClothSystemComponent::GetClothObject(const FString& resourcePath, bool bIncludeDeferred) const
//{
//	for (auto& ClothoObject : _ClothObjectList)
//	{
//		if (ClothoObject.Value->GetResourcePath().Compare(resourcePath) == 0)
//		{
//			return ClothoObject.Value;
//		}
//	}
//	return nullptr;
//}
//
//UGCClothObject* UGCClothSystemComponent::GetClothObject(const EEquipType equipType, bool bIncludeDeferred) const
//{
//	UGCClothObject* pResultClothObject = _ClothObjectList.FindRef(equipType);
//	if (bIncludeDeferred
//		&& pResultClothObject == nullptr)
//	{
//		pResultClothObject = GetDeferredClothObject(equipType);
//	}
//
//	return pResultClothObject;
//}
//
//bool UGCClothSystemComponent::HasClothobject(const EEquipType equipType) const
//{
//	return GetClothObject(equipType) != nullptr ? true : false;
//}
//
//void UGCClothSystemComponent::UpdateClothObject(UGCClothObject* pUpdateClothObject)
//{
//	if (_OnUpdateClothObjectDelegate.IsBound())
//	{
//		_OnUpdateClothObjectDelegate.Broadcast(pUpdateClothObject);
//	}
//}
//
//void UGCClothSystemComponent::InitDefaultClothObject()
//{
//	
//}
//
//void UGCClothSystemComponent::UpdateCustomMaterial()
//{
//	TArray<UGCClothObject*> ClothObjectes = GetClothObjectListIgnoreBody();
//	for (const auto& ClothObject : ClothObjectes)
//	{
//		ClothObject->UpdateCustomMaterial();
//	}
//}
//
//UGCClothObject* UGCClothSystemComponent::NewClothObject(const EEquipType equipType, const FName& objectName /*= NAME_None*/)
//{
//	UGCClothObject* pClothObject = NewSpecifyClothObject(equipType, objectName);
//	if (!pClothObject)
//	{
//		pClothObject = MakeDefaultSpecifyClothObject(objectName);
//	}
//
//	if (pClothObject && _OwnerCharacter.IsValid())
//	{
//		pClothObject->SetOwnerCharacter(_OwnerCharacter.Get());
//		return pClothObject;
//	}
//	return nullptr;
//}
//
//UGCClothObject* UGCClothSystemComponent::NewSpecifyClothObject(const EEquipType equipType, const FName& objectName)
//{
//	const TSubclassOf<UGCClothObject> ClothObjectClass = GetClothObjectClass(equipType);
//	if (ClothObjectClass)
//	{
//		return NewObject<UGCClothObject>(this, ClothObjectClass, objectName);
//	}
//	return nullptr;
//}
//
//void UGCClothSystemComponent::PostPutOnClothObject(UGCClothObject* newClothObject)
//{
//	if (newClothObject)
//	{
//		DeterminePutOffCloth(newClothObject);
//		DetermineCullTexture(newClothObject);
//	}
//}
//
//void UGCClothSystemComponent::DeterminePutOffCloth(UGCClothObject* newClothObject)
//{
//	if (!_bUseNewClothSystem)
//	{
//		return;
//	}
//
//	EEquipType EquipType = newClothObject ? newClothObject->GetEquipType() : EEquipType::NONE;
//	if (EquipType != EEquipType::NONE)
//	{
//		switch (EquipType)
//		{
//		case EEquipType::FULLS:
//			PutOffClothObjectByEquipTypes({
//				EEquipType::OUTER,
//				EEquipType::SHIRT,
//				EEquipType::DRESS,
//				EEquipType::SUIT,
//				EEquipType::SKIRT,
//				EEquipType::PANTS,
//				EEquipType::SKIRT,
//				});
//			break;
//		case EEquipType::SHOES:
//			[[fallthrough]];
//		case EEquipType::SOCKS:
//			[[fallthrough]];
//		case EEquipType::OUTER:
//			PutOffClothObjectByEquipTypes({
//				EEquipType::FULLS,
//				});
//			break;
//		case EEquipType::SHIRT:
//			PutOffClothObjectByEquipTypes({
//				EEquipType::FULLS,
//				EEquipType::DRESS,
//				EEquipType::SUIT,
//				});
//			break;
//		case EEquipType::DRESS:
//			PutOffClothObjectByEquipTypes({
//				EEquipType::FULLS,
//				EEquipType::SHIRT,
//				EEquipType::SUIT,
//				EEquipType::SKIRT,
//				EEquipType::PANTS,
//				});
//			break;
//		case EEquipType::SUIT:
//			PutOffClothObjectByEquipTypes({
//				EEquipType::FULLS,
//				EEquipType::SHIRT,
//				EEquipType::DRESS,
//				EEquipType::SKIRT,
//				EEquipType::PANTS,
//				});
//			break;
//		case EEquipType::SKIRT:
//			PutOffClothObjectByEquipTypes({
//				EEquipType::FULLS,
//				EEquipType::DRESS,
//				EEquipType::SUIT,
//				EEquipType::PANTS,
//				});
//			break;
//		case EEquipType::GLOVE:
//			break;
//		case EEquipType::PANTS:
//			PutOffClothObjectByEquipTypes({
//				EEquipType::FULLS,
//				EEquipType::DRESS,
//				EEquipType::SUIT,
//				EEquipType::SKIRT,
//				EEquipType::FULLS
//				});
//			break;
//		case EEquipType::UNDER:
//			break;
//		default:
//			//UE_LOG_WITH_SCREEN_MSG_PRESET_ERROR(TEXT("[UGCClothSystemComponent::DeterminePutOffClothAfterPutOnCloth] Specify PutOffClothObject"));
//			break;
//		}
//	}
//}
//
//void UGCClothSystemComponent::DetermineCullTexture(UGCClothObject* newClothObject)
//{
//	int PutonClothThickness = newClothObject->GetThickness();
//	for (auto& ClothoObject : _ClothObjectList)
//	{
//		if (ClothoObject.Value->GetThickness() != PutonClothThickness)
//		{
//
//		}
//	}
//}
//
//void UGCClothSystemComponent::OnSuccedClothItem(const FGCCreateClothObjectInfo& CreateClothObjectInfo, bool bPlayAnim)
//{
//	if (EEquipType::HEAD == CreateClothObjectInfo._EquipType)
//	{
//	}
//}
//
//bool UGCClothSystemComponent::ShouldPutOnDefaultUnder() const
//{
//	if (!HasClothobject(EEquipType::UNDER))
//	{
//		return true;
//	}
//	return false;
//}
//
//void UGCClothSystemComponent::PutOnDefaultUnder()
//{
//	
//}
//
//void UGCClothSystemComponent::BindCharacterEvents()
//{
//	
//}
//
//void UGCClothSystemComponent::UnbindCharacterEvents()
//{
//	
//}
//
//UGCClothObject* UGCClothSystemComponent::MakeDefaultSpecifyClothObject(const FName& objectName)
//{
//	return nullptr;
//}
//
//void UGCClothSystemComponent::OnChagnedCharcterGender(const EGenderType genderType)
//{
//	TMap<EEquipType, UGCClothObject*> CopyClothObjectList = _ClothObjectList;
//	for (const auto& Clothobject : CopyClothObjectList)
//	{
//		if (Clothobject.Value->GetGenderType() != genderType)
//		{
//			PutOffClothObjectByEquipType(Clothobject.Value->GetEquipType());
//		}
//	}
//}
//
//void UGCClothSystemComponent::TryPutonClothDeferredList(const EEquipType parentEquipType)
//{
//	if (TArray<FGCCreateClothObjectInfo>* CreateClothObjectList = _DeferredClothObjecteList.Find(parentEquipType))
//	{
//		for (auto& DeferredClothObject : *CreateClothObjectList)
//		{
//			InternalTryInitCloth(DeferredClothObject);
//		}
//	}
//	_DeferredClothObjecteList.Remove(parentEquipType);
//}
//
//bool UGCClothSystemComponent::ShouldAddDeferredClothObject(const EEquipType parentEquipType, const UGCClothObject* pClothObject) const
//{
//	check(pClothObject)
//	if (parentEquipType != EEquipType::NONE)
//	{
//		if (GetClothObject(parentEquipType) == nullptr)
//		{
//			return true;
//		}
//		else if (UGCClothObject* pParentClothObject = GetClothObject(parentEquipType))
//		{
//			EEquipType ParentEquipType = pParentClothObject->GetParentEquipType();
//			while (ParentEquipType != EEquipType::NONE)
//			{
//				pParentClothObject = GetClothObject(ParentEquipType);
//				if (pParentClothObject == nullptr)
//				{
//					return true;
//				}
//				else
//				{
//					ParentEquipType = pParentClothObject->GetParentEquipType();
//				}
//			}
//		}
//	}
//
//	return false;
//}
//
//void UGCClothSystemComponent::AddDeferredClothObject(const EEquipType parentEquipType, const FGCCreateClothObjectInfo& createClothObjectInfo)
//{
//	//TArray<FAECreateClothObjectInfo>* DeferedClothList = _DeferredClothObjecteList.Find(parentEquipType);
//	TArray<FGCCreateClothObjectInfo>& DeferedClothList = _DeferredClothObjecteList.FindOrAdd(parentEquipType);
//	DeferedClothList.Emplace(createClothObjectInfo);
//}
//
//void UGCClothSystemComponent::RemoveDeferredClothObject(const EEquipType parentEquipType)
//{
//	_DeferredClothObjecteList.Remove(parentEquipType);
//}
//
//UGCClothObject* UGCClothSystemComponent::GetDeferredClothObject(const EEquipType equipType) const
//{
//	for (const auto& DeferredClothObjectList : _DeferredClothObjecteList)
//	{
//		for (const auto& DerredClothObject : DeferredClothObjectList.Value)
//		{
//			if (DerredClothObject._ClothObject
//				&& DerredClothObject._ClothObject->GetEquipType() == equipType)
//			{
//				return DerredClothObject._ClothObject;
//			}
//		}
//	}
//	return nullptr;
//}
//
//void UGCClothSystemComponent::LoadClothObjectClassDataClass()
//{
//	if (_ClothObjectClassDataClass)
//	{
//		_ClothObjectClassData = NewObject<UGCClothObjectClassData>(this, _ClothObjectClassDataClass);
//	}
//}
//const TSubclassOf<UGCClothObject> UGCClothSystemComponent::GetClothObjectClass(const EEquipType equipType) const
//{
//	if (_ClothObjectClassData)
//	{
//		if (const TSubclassOf<UGCClothObject>* AEClothObjectClass = _ClothObjectClassData->GetClothObjectClass(equipType))
//		{
//			return *AEClothObjectClass;
//		}
//	}
//	return nullptr;
//}
//
//const TSubclassOf<UGCClothObject>* UGCClothObjectClassData::GetClothObjectClass(const EEquipType equipType) const
//{
//	return _ClothObjectClasses.Find(equipType);
//}
