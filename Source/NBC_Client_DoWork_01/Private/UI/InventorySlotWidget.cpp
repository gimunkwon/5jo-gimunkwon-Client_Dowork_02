#include "UI/InventorySlotWidget.h"

#include "PaperSprite.h"
#include "Components/Image.h"

void UInventorySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInventorySlotWidget::UpdateSlotImage(UPaperSprite* SpriteImage)
{
	if (Image_Item && SpriteImage)
	{
		Image_Item->SetBrushResourceObject(SpriteImage);
	}
}


