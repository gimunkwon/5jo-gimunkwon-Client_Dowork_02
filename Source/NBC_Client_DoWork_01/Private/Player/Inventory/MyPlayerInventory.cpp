#include "NBC_Client_DoWork_01/Public/Player/Inventory/MyPlayerInventory.h"



UMyPlayerInventory::UMyPlayerInventory()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	InventoryCapacity = 6;
	
	Inventory.SetNum(InventoryCapacity);
}



void UMyPlayerInventory::BeginPlay()
{
	Super::BeginPlay();
	
	Inventory.Emplace(ItemList.Potion);
	Inventory.Emplace(ItemList.Gold);
	Inventory.Emplace(ItemList.Sword);
}




