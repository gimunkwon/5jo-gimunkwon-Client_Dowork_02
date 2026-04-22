#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class UMenuAnchor;
class UComboBoxString;
class UTextBlock;
class UImage;
class UInventoryInfoWidget;
class UInventorySlotWidget;
class UGridPanel;
class UMyPlayerInventory;


UCLASS()
class NBC_CLIENT_DOWORK_01_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	
	bool UpdateInventoryItem(UMyPlayerInventory* InventoryInst);
	
	UFUNCTION()
	void UpdateInfoItemWidget(FName SelectedItemName,UImage* SelectedItemImage);
	UFUNCTION()
	void UpdatePlayerTitleText();
	UFUNCTION()
	void UpdatePlayerTitleToComboBox();
	UFUNCTION()
	void OnPlayerTitleComboxPressed(FString SelectedItem, ESelectInfo::Type SelectionType);
	UFUNCTION()
	void OnRightClickedInvenSlot(FName SelectedSlotItem);
protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UGridPanel> Grid_Inven;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Widget")
	TSubclassOf<UInventorySlotWidget> WBP_InvenSlot;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UInventoryInfoWidget> WBP_ItemInfoWidget;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> Text_PlayerTitle;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UComboBoxString> ComboBox_PlayerTitle;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UMenuAnchor> MenuA_SelectItem;
	
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Grid")
	int32 Grid_MaxRow;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Grid")
	int32 Grid_MaxColumn;
};

