

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Grab();
	void Release();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere)
	float Reach = 120.f;
	
	FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
	FVector LineTraceEnd;
	
	UPhysicsHandleComponent* PhysicsHandle= nullptr;
	UInputComponent* InputComponent = nullptr;

	void FindPhysicsHandle();
	void BindInput();
	void SetUpRayCasting();

	FHitResult GetFirstPBInReach() const;

	
};
