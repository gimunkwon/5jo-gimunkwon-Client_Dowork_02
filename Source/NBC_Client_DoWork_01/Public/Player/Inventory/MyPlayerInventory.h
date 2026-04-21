#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyPlayerInventory.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NBC_CLIENT_DOWORK_01_API UMyPlayerInventory : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UMyPlayerInventory();

protected:
	
	virtual void BeginPlay() override;

public:
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
