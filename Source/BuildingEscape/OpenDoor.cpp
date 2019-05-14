// Copyright SH44N96.


#include "OpenDoor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	OpenDoor();
}

void UOpenDoor::OpenDoor()
{
	Owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
}

void UOpenDoor::CloseDoor()
{
	Owner->SetActorRotation(FRotator(0.f, 0.f, 0.f));
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the Trigger Volume
	// If the ActorThatOpens is in the volume
	if(PressurePlateR->IsOverlappingActor(ActorThatOpens)) // && PressurePlateL->IsOverlappingActor(ActorThatOpens)
	{
		Pressured = true;
	}

	if(GetWorld()->GetTimeSeconds() > 1.5f)
	{
		FirstCloseDoor = true;
	}

	if(FirstCloseDoor && !Pressured)
	{
		CloseDoor();
	}
	else if(FirstCloseDoor && Pressured)
	{
		OpenDoor();
	}
}

