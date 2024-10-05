//
// Created by Zach on 2024-08-17.
//

#pragma once

#include <godot_cpp/classes/random_number_generator.hpp>

#include "ArrowSequence.hpp"
#include "Resources/DirectionSequence.hpp"

using namespace godot;

namespace Game {
    class SequenceOrchestrator final : public Node {
        GDCLASS(SequenceOrchestrator, Node);

    private:
        TypedArray<DirectionSequence> sequences;
        ArrowSequence* arrowSequence = nullptr;
        Ref<RandomNumberGenerator> randomNumberGenerator = nullptr;

    public:
        void _ready() override;

        void SetSequences(const TypedArray<DirectionSequence>& sequences) { this->sequences = sequences; }
        [[nodiscard]] TypedArray<DirectionSequence> GetSequences() const { return sequences; }

        void SetArrowSequence(ArrowSequence* arrowSequence) { this->arrowSequence = arrowSequence; }
        [[nodiscard]] ArrowSequence* GetArrowSequence() const { return arrowSequence; }

    protected:
        static void _bind_methods();

    private:
        TypedArray<Direction> GetRandomSequence();

        void OnSequenceCompleted();
    };
}
