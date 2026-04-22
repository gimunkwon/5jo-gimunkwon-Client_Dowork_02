#include "NBC_Client_DoWork_01/Public/Player/MyPlayer.h"

#include "NBC_Client_DoWork_01/Public/Player/Inventory/MyPlayerInventory.h"
#include "Player/Controller/MyPlayerControlloer.h"


AMyPlayer::AMyPlayer()
	: InventoryAC(nullptr)
{
	PrimaryActorTick.bCanEverTick = false;
	InventoryAC = CreateDefaultSubobject<UMyPlayerInventory>(TEXT("InventoryComponent"));
}

void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	const UEnum* Enumptr = StaticEnum<EPlayer_Title>();
	
	if (Enumptr)
	{
		for (TSet<EPlayer_Title>::TConstIterator It = PlayerTitle.CreateConstIterator(); It; ++It)
		{
			FString TitleName = Enumptr->GetNameStringByValue((int64)*It);
			
			UE_LOG(LogTemp,Warning,TEXT("Currnet Player Title : %s"), *TitleName);
		}
	}
	
	if (AMyPlayerControlloer* PC = Cast<AMyPlayerControlloer>(GetController()))
	{
		if (PC)
		{
			UE_LOG(LogTemp,Warning,TEXT("UpdatePlayerTitleText..."));
			PC->GetInventoryWidget()->UpdatePlayerTitleText();
			PC->GetInventoryWidget()->UpdatePlayerTitleToComboBox();
		}
	}
}

void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMyPlayer::SetPlayerTitle(EPlayer_Title Player_Title)
{
	PlayerTitle.Add(Player_Title);
}