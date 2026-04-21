#include "NBC_Client_DoWork_01/Public/Player/Controller/MyPlayerControlloer.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Compute/ComputeSocket.h"
#include "Player/MyPlayer.h"
#include "UI/InventoryWidget.h"

AMyPlayerControlloer::AMyPlayerControlloer()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void AMyPlayerControlloer::BeginPlay()
{
	Super::BeginPlay();
	
	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(GetLocalPlayer()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = Cast<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()))
		{
			if (IMC_Default)
			{
				SubSystem->AddMappingContext(IMC_Default,0);
			}
		}
	}
	
	// Widget
	
	if (InventoryWidgetClass)
	{
		InventoryWidgetInst = CreateWidget<UInventoryWidget>(this, InventoryWidgetClass);
		if (InventoryWidgetInst)
		{
			AMyPlayer* MyOwner = Cast<AMyPlayer>(GetOwner());
			
			InventoryWidgetInst->AddToViewport();
			if (MyOwner)
			{
				InventoryWidgetInst->UpdateInventoryItem(MyOwner->GetInventory());
			}
			
		}
	}
}
