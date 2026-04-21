#pragma once

#include "CoreMinimal.h"
#include "ItemdataTable.generated.h"

USTRUCT(BlueprintType)
struct FItemDataTable : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="RowData")
	FName ItemName;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="RowData")
	TObjectPtr<UTexture2D> ItemImage;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="RowData")
	FText ItemDescription;
};
