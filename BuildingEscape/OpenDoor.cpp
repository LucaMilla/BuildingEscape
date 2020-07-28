


#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "OpenDoor.h"
#include "GameFramework/Actor.h"

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
	
	OriginalRotation = GetOwner()->GetActorRotation();
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	TargetYaw += floor(OriginalRotation.Yaw);

	if (TargetYaw > 178)
	{
		TargetYaw -= 178;
	}

	if(!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has no PressurePlate set on OpenDoor Actor Component"), *GetOwner()->GetName());
	}

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor(DeltaTime);
		DoorOpenTimestamp = GetWorld()->GetTimeSeconds();
	}
	else
	{
		if (GetWorld()->GetTimeSeconds() >= (DoorOpenTimestamp + DoorShutDelay))
		{
			CloseDoor(DeltaTime);
		}
	}
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	OriginalRotation.Yaw = FMath::FInterpTo(GetOwner()->GetActorRotation().Yaw, TargetYaw, DeltaTime, OpenDoorSpeed);
	GetOwner()->SetActorRotation(OriginalRotation);
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	OriginalRotation.Yaw = FMath::FInterpTo(GetOwner()->GetActorRotation().Yaw, InitialYaw, DeltaTime, CloseDoorSpeed);
	GetOwner()->SetActorRotation(OriginalRotation);
}


