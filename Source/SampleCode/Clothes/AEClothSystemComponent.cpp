//// Copyright(c) Burning Galaxy LTD. All Rights Reserved.
//
//#include "AEClothSystemComponent.h"
//
//#include "GameCore/DataTable/Unreal/UnrealEquipMeshData.h"
//#include "GameCore/Object/AEClothObject.h"
//#include "GameCore/Object/AEClothObject_Shirt.h"
//#include "GameCore/Object/AEClothObject_Groom.h"
//#include "GameCore/Manager/SyncDataManager.h"
//#include "GameCore/DataTable/Sync/SyncAvatarData.h"
//#include "GameCore/DataTable/Sync/SyncUGCItemData.h"
//
//#include "Game/Keyword/AvatarKeywordConverter.h"
//#include "Game/Character/AeCharacterBase.h"
//
//#include "GalaxyCore/Public/Log/LogMacros.h"
//
//UAEClothSystemComponent::UAEClothSystemComponent(const FObjectInitializer& ObjectInitializer)
//	: Super(ObjectInitializer)
//{
//	SetComponentTickEnabled(false);
//}
//
//void UAEClothSystemComponent::OnRegister()
//{
//	Super::OnRegister();
//
//	_CachedAECharacter = GetOwner<AAeCharacterBase>();
//}
//
//UGCClothObject* UAEClothSystemComponent::PutOnClothItemByResourcePath(const FString& resourcePath, bool bPlayAnim)
//{
//	if (FClothInfo* adItem = AE_SYNCDATA_MANAGER().GetSyncData<USyncUGCItemData>().GetADItemResourceInfo(resourcePath))
//	{
//		const EquipInfo equipInfo = EquipInfo(adItem->ADItemMeshInfo.EquipType, adItem->ADItemMeshInfo.GenderType);
//		const FString assetKey = adItem->ADItemMeshInfo.MeshKey;
//		if (UGCClothObject* pPutOnCloth = PutOnClothItem(adItem->ADItemMeshInfo.EquipType, adItem->ADItemMeshInfo.GenderType, assetKey, resourcePath, bPlayAnim))
//		{
//			pPutOnCloth->SetResourcePath(resourcePath);
//			return pPutOnCloth;
//		}
//	}
//	return nullptr;
//}
//
//UMeshComponent* UAEClothSystemComponent::GetGroomCompByEquipType(EEquipType equipType) const
//{
//	UGCClothObject* pClothObject = GetClothObject(equipType);
//	if (pClothObject
//		&& pClothObject->IsA(UAEClothObject_Groom::StaticClass()))
//	{
//		return GetMeshCompByEquipType(equipType);
//	}
//	return nullptr;
//}
//
//void UAEClothSystemComponent::InitDefaultClothObject()
//{
//	Super::InitDefaultClothObject();
//
//	EGenderType GenderType = _CachedAECharacter.IsValid() ? _CachedAECharacter->GetGenderType() : EGenderType::NONE;
//
//	for (const auto& PutOnClothData : _DefaultPutOnCloth)
//	{
//		if (PutOnClothData._GenderType == GenderType)
//		{
//			PutOnClothItem(PutOnClothData._EquipType, PutOnClothData._GenderType, PutOnClothData._AssetKey);
//		}
//	}
//}
//
//void UAEClothSystemComponent::PutOnDefaultUnder()
//{
//	EGenderType GenderType = _CachedAECharacter.IsValid() ? _CachedAECharacter->GetGenderType() : EGenderType::NONE;
//
//	const FGCDefaultPutOnCloth* pFindUnderClothData = _DefaultPutOnCloth.FindByPredicate([GenderType](const FGCDefaultPutOnCloth& PutOnClothData)
//		{
//			if (PutOnClothData._EquipType == EEquipType::UNDER
//				&& PutOnClothData._GenderType == GenderType)
//			{
//				return true;
//			}
//			return false;
//		});
//	if (pFindUnderClothData)
//	{
//		PutOnClothItem(pFindUnderClothData->_EquipType, pFindUnderClothData->_GenderType, pFindUnderClothData->_AssetKey);
//	}
//}
//
//void UAEClothSystemComponent::BindCharacterEvents()
//{
//	if (_CachedAECharacter.IsValid())
//	{
//		_CachedAECharacter->GetOnChangedGenderTypeDelegate().AddUObject(this, &UGCClothSystemComponent::OnChagnedCharcterGender);
//	}
//}
//
//void UAEClothSystemComponent::UnbindCharacterEvents()
//{
//	if (_CachedAECharacter.IsValid())
//	{
//		_CachedAECharacter->GetOnChangedGenderTypeDelegate().RemoveAll(this);
//	}
//}
//
//void UAEClothSystemComponent::UpdateClothDataActiveMyAvatarInfo()
//{
//	auto avatarInfo = AE_SYNCDATA_MANAGER().GetSyncData<USyncAvatarData>().GetActiveAvatarInfo();
//	if (avatarInfo == nullptr)
//	{
//		UE_LOG_WITH_SCREEN_MSG_PRESET_ERROR(TEXT("[UClosetWidget::Internal_SyncAvatarClothData] AvatarInfo is null"));
//		return;
//	}
//
//	FAvatarInfo NewAvatarInfo = *avatarInfo;
//	for (uint8 EquipIdx = (uint8)EEquipType::GLASSES; EquipIdx < (uint8)EEquipType::MAX; ++EquipIdx)
//	{
//		if (UGCClothObject* pClothObject = GetClothObject((EEquipType)EquipIdx))
//		{
//			FEquipmentItemInfo CustomValue;
//			CustomValue.SetAssetKey(pClothObject->GetAssetKey());
//			CustomValue._ResourceFilePath = pClothObject->GetResourcePath();
//
//			NewAvatarInfo.FindOrAddEquipInfo(pClothObject->GetEquipType()) = CustomValue;
//		}
//		else
//		{
//			//해당 Type ClothObject없으면 빈 데이터 적용
//			const FEquipmentItemInfo EmptyInfo;
//			NewAvatarInfo.FindOrAddEquipInfo((EEquipType)EquipIdx) = EmptyInfo;
//		}
//	}
//
//	auto slotIdx = AE_SYNCDATA_MANAGER().GetSyncData<USyncAvatarData>().GetActiveAvatarSlotIdx();
//	AE_SYNCDATA_MANAGER().GetSyncData<USyncAvatarData>().AddMyAvatarInfo(slotIdx, NewAvatarInfo);
//}
//
//UGCClothObject* UAEClothSystemComponent::MakeDefaultSpecifyClothObject(const FName& objectName)
//{
//	return NewObject<UAEClothObject>(this, UAEClothObject::StaticClass(), objectName);
//}
//
//FName UAEClothSystemComponent::MakeNewObjectName(const EEquipType equipType) const
//{
//	return *FString::Format(TEXT("ClothObject_{0}"), { AE::FAvatarKeywordConverter::ConvertEnumToString(equipType) });
//}
