#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class UGridPanel;
class UMyPlayerInventory;

UCLASS()
class NBC_CLIENT_DOWORK_01_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	void UpdateInventoryItem(UMyPlayerInventory* InventoryInst);
protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UGridPanel> Grid_Inven;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Widget")
	TSubclassOf<UUserWidget> WBP_InvenSlot;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Grid")
	int32 Grid_MaxRow;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Grid")
	int32 Grid_MaxColumn;
};
