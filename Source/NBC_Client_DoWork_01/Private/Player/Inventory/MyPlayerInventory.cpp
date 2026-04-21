#include "NBC_Client_DoWork_01/Public/Player/Inventory/MyPlayerInventory.h"

#include "Player/Controller/MyPlayerControlloer.h"
#include "UObject/FastReferenceCollector.h"


UMyPlayerInventory::UMyPlayerInventory()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	InventoryCapacity = 30;
	
	Inventory.SetNum(InventoryCapacity);
	
}



void UMyPlayerInventory::BeginPlay()
{
	Super::BeginPlay();
}

FItemDataTable* UMyPlayerInventory::FindItemFromDataTable(FName ItemName)
{
	static const FString ContextString = "DataTableSearch";
	
	if (ItemDataTable)
	{
		FItemDataTable* FindRow = ItemDataTable->FindRow<FItemDataTable>(ItemName, ContextString);
		return FindRow;
	}
	return nullptr;
}

void UMyPlayerInventory::AddInventoryItem(FName ItemName)
{
	if (!ItemDataTable) return;
	
	FItemDataTable* EmptySlot = Inventory.FindByPredicate([](const FItemDataTable& Item){return Item.ItemName.IsNone();});
	if (!EmptySlot)
	{
		UE_LOG(LogTemp,Warning,TEXT("인벤토리 가득참"));
		return;
	}
	
	
	if (Inventory.Num() <= InventoryCapacity)
	{
		for (int32 i = 0; i < Inventory.Num(); i++)
		{
			UE_LOG(LogTemp,Warning,TEXT("Index %d : ItemName is %s"),i, *Inventory[i].ItemName.ToString());
			if (Inventory[i].ItemName.IsNone())
			{
				UE_LOG(LogTemp,Warning,TEXT("AddInventory"));
				Inventory[i] = *FindItemFromDataTable(ItemName);
				break;
			}
		}
	}
	
	if (AMyPlayerControlloer* PC  = Cast<AMyPlayerControlloer>(GetOwner()->GetInstigatorController()))
	{
		PC->GetInventoryWidget()->UpdateInventoryItem(this);
	}
}




