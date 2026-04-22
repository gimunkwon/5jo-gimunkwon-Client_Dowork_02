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
	TMap<FName,FText> ItemInfo;
	
	void AddInventoryItem(FName ItemName);
	static FItemDataTable* FindItemFromDataTable (UDataTable* DataTable,FName ItemName);
	void DeleteItemFromInventory(int32 index);
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="InventorySettings")
	int32 InventoryCapacity;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="DataTable")
	TObjectPtr<UDataTable> ItemDataTable;
	UPROPERTY()
	TMap<FName, FText> ItemDescription;
};
