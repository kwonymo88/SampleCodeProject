#pragma once
#include "CoreMinimal.h"
#include "SingletonTemplate.h"
#include "SCManager.h"
#include "StaticDataInterface.h"
#include "SCStaticDataManager.generated.h"

DECLARE_LOG_CATEGORY_EXTERN( LogStaticDataManager, Log, All );

UCLASS()
class SAMPLECODE_API USCStaticDataManager : public USCManager, public TSingleton<USCStaticDataManager>
{
	GENERATED_BODY()

public:
	virtual void Init() override;	
	virtual void ShutDown() override;

	template<class TStaticData>
	inline typename TEnableIf<TIsDerivedFrom<TStaticData, IStaticDataInterface>::IsDerived, TStaticData>::Type* GetStaticData();

private:
	void CreateStaticDatas();
	void RemoveStaticDatas();
	void LoadAllData();
	bool CheckRelativeValidate();

	template<class TStaticData>
	inline bool CreateStaticData();

private:
	TMap<FString, IStaticDataInterface*> StaticDataList;
};

template<class TStaticData>
bool USCStaticDataManager::CreateStaticData()
{
	if (false == ensure((TIsDerivedFrom<TStaticData, IStaticDataInterface>::IsDerived)))
	{
		checkf(false, TEXT("[USCStaticDataManager::CreateStaticData] inherite IStaticDataInterface"));
		return false;
	}

	if (TStaticData* NewStaticData = NewObject<TStaticData>())
	{
		NewStaticData->AddToRoot();
		StaticDataList.Emplace(NewStaticData->GetClass()->GetName(), NewStaticData);
		UE_LOG(LogStaticDataManager, Log, TEXT("[USCStaticDataManager::CreateStaticData] Success (%s)"), *TStaticData::StaticClass()->GetName());
		return true;
	}
	
	ensureMsgf(false, TEXT("[USCStaticDataManager::CreateStaticData] faild NewObject (%s)"), *TStaticData::StaticClass()->GetName());
	return false;

}

template<class TStaticData>
inline typename TEnableIf<TIsDerivedFrom<TStaticData, IStaticDataInterface>::IsDerived, TStaticData>::Type* USCStaticDataManager::GetStaticData()
{
	if (IStaticDataInterface* StaticDataInterface = StaticDataList.FindRef(TStaticData::StaticClass()->GetName()))
	{
		if (TStaticData* pCastedStaticData = CastChecked<TStaticData>(StaticDataInterface))
		{
			return pCastedStaticData;
		}
	}

	UE_LOG(LogStaticDataManager, Error, TEXT("[USCStaticDataManager::GetStaticData] Faild (%s)"), *TStaticData::StaticClass()->GetName());
	return nullptr;
};
