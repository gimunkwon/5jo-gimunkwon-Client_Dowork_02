#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlotWidget.generated.h"

class UImage;
class UButton;
class UPaperSprite;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnButtonPressed, FName, SelectedItem,UImage*, CurrentImage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBtnRightClicked, FName, CurrentSlotItem, UInventorySlotWidget*, SelectedWidgetInst);

UCLASS()
class NBC_CLIENT_DOWORK_01_API UInventorySlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void UpdateSlotImage(UPaperSprite* SpriteImage,FName SlotItemName);
	void ClearSlotData(int32 index, bool bIsUse);
	
	virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
	UPROPERTY(BlueprintAssignable)
	FOnButtonPressed OnButtonPressedOfItemName;
	UPROPERTY(BlueprintAssignable)
	FBtnRightClicked OnRightClicked;
	
protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> Image_Item;
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> Btn_InvenSlot;
	
	UFUNCTION()
	void OnButtonPressed();
	
	FName ItemName;
};
