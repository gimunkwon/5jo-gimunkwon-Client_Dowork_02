#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyPlayerInventory.generated.h"


USTRUCT()
struct FItem
{
	GENERATED_BODY()
	
	FName Potion;
	FName Sword;
	FName Gold;
};


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NBC_CLIENT_DOWORK_01_API UMyPlayerInventory : public UActorComponent
{
	GENERATED_BODY()

public:
	UMyPlayerInventory();
protected:
	virtual void BeginPlay() override;
	
	TArray<FItem> Inventory;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="InventorySettings")
	int32 InventoryCapacity;
	
private:
	FItem ItemList;
};
