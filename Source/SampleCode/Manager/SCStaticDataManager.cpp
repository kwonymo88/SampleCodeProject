
#include "SCStaticDataManager.h"
#include "SCTestStaticData.h"


DEFINE_LOG_CATEGORY( LogStaticDataManager );

#define CREATE_STATIC_DATA_IMPL(classType) CreateStaticData<classType>()

void USCStaticDataManager::Init()
{
	CreateStaticDatas();

	LoadAllData();

	CheckRelativeValidate();
}

void USCStaticDataManager::CreateStaticDatas()
{
	RemoveStaticDatas();

	UE_LOG(LogStaticDataManager, Log, TEXT("[UStaticDataManager::CreateStaticDatas] Begin Create Static Datas..."));
	CREATE_STATIC_DATA_IMPL(USCTestStaticData);
	UE_LOG(LogStaticDataManager, Log, TEXT("[UStaticDataManager::CreateStaticDatas] End Create Static Datas"));
}

void USCStaticDataManager::RemoveStaticDatas()
{
	for (const auto& StaticData : StaticDataList)
	{
		if (UObject* StaticDataObj = Cast<UObject>(StaticData.Value))
		{
			StaticData.Value->Clean();
			StaticDataObj->RemoveFromRoot();
		}
	}

	UE_LOG(LogStaticDataManager, Log, TEXT("[UStaticDataManager::RemoveStaticDatas] Static Data Removed - Count : [%d]"), StaticDataList.Num());
	StaticDataList.Empty();
}

void USCStaticDataManager::LoadAllData()
{
	for (const auto& StaticData : StaticDataList)
	{
		if (StaticData.Value)
		{
			StaticData.Value->Initialization();
		}
	}
}

bool USCStaticDataManager::CheckRelativeValidate()
{
	// Static 데이터가 로드 후 여러 Static 데이터 간의 유효성을 판단하는 코드는 이곳에 작성한다.
	return true;
}

void USCStaticDataManager::ShutDown()
{
	RemoveStaticDatas();
}

#undef CREATE_STATIC_DATA_IMPL

