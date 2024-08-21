//
// Created by Zach on 2024-08-17.
//

#pragma once

#include <godot_cpp/classes/h_box_container.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/classes/resource_loader.hpp>

#include "DirectionArrow.hpp"

using namespace godot;

namespace Game {
    class ArrowSequence final : public HBoxContainer {
        GDCLASS(ArrowSequence, HBoxContainer);

    private:
        TypedArray<DirectionArrow> arrows;
        int arrowIndex = 0;
        bool canPlay = false;

        Ref<PackedScene> directionArrowPackedScene;
        Timer* wrongInputTimer = nullptr;

    public:
        void _ready() override;
        void _unhandled_input(const Ref<InputEvent>& input_event) override;

        void InitializeSequence(const TypedArray<int>& directions);
        void ClearSequence();

    protected:
        static void _bind_methods();

    private:
        void SetupWrongInputTimer();

        void HandleDirectionInput(Direction direction);

        void HandleCorrect();
        void HandleError();
        void ResetSequence();
    };
}
