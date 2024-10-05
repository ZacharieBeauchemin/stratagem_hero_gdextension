//
// Created by Zach on 2024-08-17.
//

#include "ArrowSequence.hpp"

#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/input.hpp>
#include "Helpers/Signal.hpp"

void Game::ArrowSequence::_ready() {
  ADD_SIGNAL(MethodInfo("sequence_completed"));

  SetupWrongInputTimer();

  directionArrowPackedScene = ResourceLoader::get_singleton()->load("res://objects/DirectionArrow.tscn");
}

void Game::ArrowSequence::_unhandled_input(const Ref<InputEvent>& inputEvent) {
  if (!canPlay) {
    return;
  }

  for (int i = 0; i < 4; i++) {
    const Direction direction = static_cast<Direction>(i);
    HandleDirectionInput(direction);
  }

  if (arrowIndex == arrows.size()) {
    canPlay = false;
    emit_signal("sequence_completed");
  }
}

void Game::ArrowSequence::InitializeSequence(const TypedArray<Direction>& directions) {
  for (int i = 0; i < directions.size(); i++) {
    const Direction direction = static_cast<Direction>(static_cast<int>(directions[i]));
    DirectionArrow* arrow = cast_to<DirectionArrow>(directionArrowPackedScene->instantiate());
    arrow->SetDirection(direction);
    add_child(arrow);
    arrows.push_back(arrow);
  }

  canPlay = true;
}

void Game::ArrowSequence::ClearSequence() {
  for (int i = 0; i < arrows.size(); i++) {
    DirectionArrow* direction_arrow = cast_to<DirectionArrow>(arrows[i]);
    remove_child(direction_arrow);
    direction_arrow->queue_free();
  }

  arrows.clear();
  arrowIndex = 0;
}

void Game::ArrowSequence::SetupWrongInputTimer() {
  wrongInputTimer = memnew(Timer);
  add_child(wrongInputTimer);

  wrongInputTimer->set_wait_time(0.2);
  wrongInputTimer->set_one_shot(true);

  CONNECT_SIGNAL(wrongInputTimer, "timeout", &ResetSequence)
}

void Game::ArrowSequence::HandleDirectionInput(const Direction direction) {
  if (
    const String stringDirection = DirectionToString(direction);
    !Input::get_singleton()->is_action_just_pressed(stringDirection)
  ) {
    return;
  }

  if (
    const DirectionArrow* currentArrow = cast_to<DirectionArrow>(arrows[arrowIndex]);
    currentArrow->GetDirection() == direction
  ) {
    HandleCorrect();
  } else {
    HandleError();
  }
}

void Game::ArrowSequence::HandleCorrect() {
  const DirectionArrow* current_arrow = cast_to<DirectionArrow>(arrows[arrowIndex]);
  current_arrow->DisplayCorrect();
  arrowIndex++;
}

void Game::ArrowSequence::HandleError() {
  canPlay = false;

  for (int i = 0; i < arrowIndex + 1; i++) {
    const DirectionArrow* arrow = cast_to<DirectionArrow>(arrows[i]);
    arrow->DisplayError();
  }

  wrongInputTimer->start();
}

void Game::ArrowSequence::ResetSequence() {
  for (int i = 0; i < arrowIndex + 1; i++) {
    const DirectionArrow* arrow = cast_to<DirectionArrow>(arrows[i]);
    arrow->DisplayDefault();
  }

  arrowIndex = 0;
  canPlay = true;
}

void Game::ArrowSequence::_bind_methods() {}
