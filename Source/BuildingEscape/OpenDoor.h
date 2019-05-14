// Copyright SH44N96.

#pragma once

#include "Engine/TriggerVolume.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	void OpenDoor();
	void CloseDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	float OpenAngle = -60.0f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume*  PressurePlateR;

	UPROPERTY(EditAnywhere)
	ATriggerVolume*  PressurePlateL;

	AActor* ActorThatOpens; // Remember pawn inherits from actor
	AActor* Owner; // The owning door

	bool FirstCloseDoor = false;
	bool Pressured = false;
};
