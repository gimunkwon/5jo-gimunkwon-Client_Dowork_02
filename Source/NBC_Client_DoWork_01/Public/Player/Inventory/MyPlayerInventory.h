#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DataTable/ItemDataTable.h"
#include "MyPlayerInventory.generated.h"


struct FItemDataTable;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NBC_CLIENT_DOWORK_01_API UMyPlayerInventory : public UActorComponent
{
	GENERATED_BODY()

public:
	UMyPlayerInventory();
	UPROPERTY()
	TArray<FItemDataTable> Inventory;
protected:
	virtual void BeginPlay() override;
	void AddInventoryItem();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="InventorySettings")
	int32 InventoryCapacity;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="DataTable")
	TObjectPtr<UDataTable> ItemDataTable;
};
