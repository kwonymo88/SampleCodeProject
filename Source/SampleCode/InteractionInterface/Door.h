// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveObjectInterface.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

class UCapsuleComponent;

UENUM()
enum class EDoorState : uint8
{
	Open,
	Opening,
	Close,
	Closing
};

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FChangedDoorStateSignature, ADoor, OnChangedDoorState, EDoorState, UpdatedDoorState);

UCLASS()
class SAMPLECODE_API ADoor : public AActor, public IInteractiveObjectInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(Transient, BlueprintReadOnly)
	EDoorState	DoorState;

	void SetDoorState(const EDoorState NewDoorState);
	bool ShouldActionDoorState() const;

public:
	UPROPERTY(BlueprintAssignable, Category="Door|State")
	FChangedDoorStateSignature OnChangedDoorState;

public:
	bool OpenDoor();
	bool CloseDoor();

	UFUNCTION(BlueprintImplementableEvent)
	void BeginOpening();
	UFUNCTION(BlueprintCallable, Category="Door|Function")
	void EndOpening();
	UFUNCTION(BlueprintImplementableEvent)
	void BeginClosing();
	UFUNCTION(BlueprintCallable, Category = "Door|Function")
	void EndClosing();
		
	// ============== Begin IInteractiveObjectInterface ================
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door|Component", meta = (AllowPrivateAccess = "True"))
	TObjectPtr<UCapsuleComponent>	InteractionComponent;

	TWeakInterfacePtr<IPlayerInteractionInterface>	InteractingCharacterInterface;

public:
	virtual void DoInteract(IPlayerInteractionInterface* PlayerInteractionInterface) override;
	virtual void EndInteract() override;
	virtual bool ShouldInteract() const override;
	// ============== End IInteractiveObjectInterface ================
};
