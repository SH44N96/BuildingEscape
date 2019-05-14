// Copyright SH44N96.

#include "OpenDoor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
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
	if(GetTotalMassOfActorsOnPlate(PressurePlateR) > 20.f && GetTotalMassOfActorsOnPlate(PressurePlateL) > 10.f) // TODO make into a parameter
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

float UOpenDoor::GetTotalMassOfActorsOnPlate(ATriggerVolume* PressurePlate)
{
	float TotalMass = 0.f;

	// Find all the overlapping actors
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	// Iterate through them, adding their masses
	for(const auto* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s on pressure plate"), *Actor->GetName());
	}

	return TotalMass;
}
