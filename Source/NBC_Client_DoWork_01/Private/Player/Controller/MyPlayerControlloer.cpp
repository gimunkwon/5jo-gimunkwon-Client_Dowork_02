#include "NBC_Client_DoWork_01/Public/Player/Controller/MyPlayerControlloer.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Compute/ComputeSocket.h"

AMyPlayerControlloer::AMyPlayerControlloer()
{
	
}

void AMyPlayerControlloer::BeginPlay()
{
	Super::BeginPlay();
	
	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(GetLocalPlayer()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = Cast<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()))
		{
			// AddMapping
		}
	}
	
	// Widget
	
	if (InventoryWidgetClass)
	{
		InventoryWidgetInst = CreateWidget<UUserWidget>(this, InventoryWidgetClass);
		if (InventoryWidgetInst)
		{
			InventoryWidgetInst->AddToViewport();
		}
	}
}
