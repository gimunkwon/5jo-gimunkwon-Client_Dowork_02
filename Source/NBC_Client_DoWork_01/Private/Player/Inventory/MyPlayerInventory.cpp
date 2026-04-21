#include "NBC_Client_DoWork_01/Public/Player/Inventory/MyPlayerInventory.h"

#include "Player/Controller/MyPlayerControlloer.h"


UMyPlayerInventory::UMyPlayerInventory()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	InventoryCapacity = 30;
	
	Inventory.Reserve(InventoryCapacity);
	
}



void UMyPlayerInventory::BeginPlay()
{
	Super::BeginPlay();
	
	AddInventoryItem();
}

void UMyPlayerInventory::AddInventoryItem()
{
	if (!ItemDataTable) return;
	
	static const FString ContextString(TEXT("ItemData"));
	FItemDataTable* Row = ItemDataTable->FindRow<FItemDataTable>(TEXT("Gold"),ContextString);
	FItemDataTable* Row_02 = ItemDataTable->FindRow<FItemDataTable>(TEXT("Sword"),ContextString);
	
	if (Row)
	{
		UE_LOG(LogTemp,Warning,TEXT("Add Success"));
		if (AMyPlayerControlloer* PC  = Cast<AMyPlayerControlloer>(GetOwner()->GetInstigatorController()))
		{
			PC->GetInventoryWidget()->UpdateInventoryItem(this);
		}
	}
}




