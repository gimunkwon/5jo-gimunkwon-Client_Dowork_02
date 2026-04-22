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
	
	if (ItemDataTable)
	{
		static const FString ContextString = "DataTableSearch";
		TArray<FItemDataTable*> TempRowArray;
		ItemDataTable->GetAllRows(ContextString,TempRowArray);
		for (int32 i = 0; i < TempRowArray.Num(); i++)
		{
			ItemInfo.Add(TempRowArray[i]->ItemName, TempRowArray[i]->ItemDescription);
		}
	}
	
	for (auto i : ItemInfo)
	{
		UE_LOG(LogTemp,Warning,TEXT("Map Key : %s | Value : %s"),*i.Key.ToString(), *i.Value.ToString());
	}
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
				Inventory[i] = *FindItemFromDataTable(ItemDataTable,ItemName);
				break;
			}
		}
	}
	
	if (AMyPlayerControlloer* PC  = Cast<AMyPlayerControlloer>(GetOwner()->GetInstigatorController()))
	{
		PC->GetInventoryWidget()->UpdateInventoryItem(this);
	}
}

FItemDataTable* UMyPlayerInventory::FindItemFromDataTable(UDataTable* DataTable,FName ItemName)
{
	static const FString ContextString = "DataTableSearch";
	
	if (DataTable)
	{
		FItemDataTable* FindRow = DataTable->FindRow<FItemDataTable>(ItemName, ContextString);
		return FindRow;
	}
	return nullptr;
}

void UMyPlayerInventory::DeleteItemFromInventory(int32 index)
{
	if (Inventory.IsValidIndex(index))
	{
		UE_LOG(LogTemp,Warning,TEXT("인벤토리 배열 삭제 완료!!"));
		Inventory[index] = FItemDataTable();
	}
}




