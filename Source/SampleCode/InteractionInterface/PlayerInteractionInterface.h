// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "UObject/WeakInterfacePtr.h"
#include "PlayerInteractionInterface.generated.h"

class IInteractiveObjectInterface;

UINTERFACE()
class UPlayerInteractionInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class SAMPLECODE_API IPlayerInteractionInterface : public IInterface
{
	GENERATED_IINTERFACE_BODY()

	friend class IInteractiveObjectInterface;

protected:
	TArray<TWeakInterfacePtr<IInteractiveObjectInterface>> OverlappedInteractiveObject;

	TWeakInterfacePtr<IInteractiveObjectInterface>	PriorityInteractiveObject;

protected:
	void DeterminePriorityInteractiveObject();
	void SetPriorityInteractiveObject(IInteractiveObjectInterface* NewPriorityInteractiveObject);

protected:
	virtual void OnUpdatePriorityInteractiveObject();

	//====================== Begin for friend class =============================
protected:
	void AddOverlappedInteractiveObject(IInteractiveObjectInterface* NewOverlappedInteractiveObject);
	void RemoveOverlappedInteractiveObject(IInteractiveObjectInterface* RemoveOverlappedInteractiveObject);
	//====================== End for friend class =============================

public:
	void TryInteract();
};
