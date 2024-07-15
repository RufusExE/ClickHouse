#pragma once

#include <Storages/MergeTree/FutureMergedMutatedPart.h>
#include <Storages/MutationCommands.h>
#include <Core/SettingsEnums.h>

namespace DB
{

class StorageMergeTree;

struct StorageInMemoryMetadata;
using StorageMetadataPtr = std::shared_ptr<const StorageInMemoryMetadata>;
struct FutureMergedMutatedPart;
using FutureMergedMutatedPartPtr = std::shared_ptr<FutureMergedMutatedPart>;


struct CurrentlyMergingPartsTagger
{
    FutureMergedMutatedPartPtr future_part;
    ReservationSharedPtr reserved_space;
    StorageMergeTree & storage;
    // Optional tagger to maintain volatile parts for the JBOD balancer
    std::optional<CurrentlySubmergingEmergingTagger> tagger;

    CurrentlyMergingPartsTagger(
        FutureMergedMutatedPartPtr future_part_,
        size_t total_size,
        StorageMergeTree & storage_,
        const StorageMetadataPtr & metadata_snapshot,
        bool is_mutation);

    ~CurrentlyMergingPartsTagger();
};

using CurrentlyMergingPartsTaggerPtr = std::unique_ptr<CurrentlyMergingPartsTagger>;

struct MergeMutateSelectedEntry
{
    FutureMergedMutatedPartPtr future_part;
    CurrentlyMergingPartsTaggerPtr tagger;
    MutationCommandsConstPtr commands;
    MergeTreeTransactionPtr txn;
    LightweightMutationProjectionMode lightweight_delete_projection_mode;
    MergeMutateSelectedEntry(FutureMergedMutatedPartPtr future_part_, CurrentlyMergingPartsTaggerPtr tagger_,
                             MutationCommandsConstPtr commands_, const MergeTreeTransactionPtr & txn_ = NO_TRANSACTION_PTR,
                             const LightweightMutationProjectionMode & lightweight_delete_projection_mode_ = LightweightMutationProjectionMode::THROW)
        : future_part(future_part_)
        , tagger(std::move(tagger_))
        , commands(commands_)
        , txn(txn_)
        , lightweight_delete_projection_mode(lightweight_delete_projection_mode_)
    {}
};

using MergeMutateSelectedEntryPtr = std::shared_ptr<MergeMutateSelectedEntry>;

}
