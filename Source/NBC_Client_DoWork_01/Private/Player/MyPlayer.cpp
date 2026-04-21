#include "NBC_Client_DoWork_01/Public/Player/MyPlayer.h"

#include "NBC_Client_DoWork_01/Public/Player/Inventory/MyPlayerInventory.h"


AMyPlayer::AMyPlayer()
	: InventoryAC(nullptr)
{
	PrimaryActorTick.bCanEverTick = false;
	
	InventoryAC = CreateDefaultSubobject<UMyPlayerInventory>(TEXT("InventoryComponent"));
	
}

void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

