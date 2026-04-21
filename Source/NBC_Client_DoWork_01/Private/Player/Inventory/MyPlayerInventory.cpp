#include "NBC_Client_DoWork_01/Public/Player/Inventory/MyPlayerInventory.h"



UMyPlayerInventory::UMyPlayerInventory()
{
	PrimaryComponentTick.bCanEverTick = true;
}



void UMyPlayerInventory::BeginPlay()
{
	Super::BeginPlay();
}



void UMyPlayerInventory::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

