#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerControlloer.generated.h"

class UInventoryWidget;
class UInputAction;
class UInputMappingContext;

UCLASS()
class NBC_CLIENT_DOWORK_01_API AMyPlayerControlloer : public APlayerController
{
	GENERATED_BODY()
public:
	AMyPlayerControlloer();
	
	virtual void BeginPlay() override;
	
#pragma region Input
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Input")
	TObjectPtr<UInputMappingContext> IMC_Default;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Input")
	TObjectPtr<UInputAction> IA_InvenToggle;
#pragma endregion 
	
protected:
	
#pragma region Widget
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Widget")
	TSubclassOf<UUserWidget> InventoryWidgetClass;
	UPROPERTY()
	TObjectPtr<UInventoryWidget> InventoryWidgetInst;
#pragma endregion
	
};
