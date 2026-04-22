#include "UI/InventorySlotWidget.h"

#include "PaperSprite.h"
#include "Components/Button.h"
#include "Components/Image.h"

void UInventorySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (Btn_InvenSlot)
	{
		Btn_InvenSlot->OnClicked.AddDynamic(this,&UInventorySlotWidget::OnButtonPressed);
	}
}

void UInventorySlotWidget::UpdateSlotImage(UPaperSprite* SpriteImage,FName SlotItemName)
{
	if (Image_Item && SpriteImage)
	{
		Image_Item->SetBrushResourceObject(SpriteImage);
	}
	if (!SlotItemName.IsNone())
	{
		ItemName = SlotItemName;
	}
}

void UInventorySlotWidget::OnButtonPressed()
{
	UE_LOG(LogTemp,Warning,TEXT("CurrentSlot Item Name was %s"),*ItemName.ToString());
	
	if (OnButtonPressedOfItemName.IsBound())
	{
		OnButtonPressedOfItemName.Broadcast(ItemName,Image_Item);
	}
}

FReply UInventorySlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		UE_LOG(LogTemp,Warning,TEXT("오른쪽 마우스 클릭 이벤트 발생!!"));
		if (OnRightClicked.IsBound())
		{
			OnRightClicked.Broadcast(ItemName);
		}
		return FReply::Handled();
	}
	
	return FReply::Unhandled();
}