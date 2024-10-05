//
// Created by Zach on 2024-08-17.
//

#include "SequenceOrchestrator.hpp"

#include "Helpers/Binding.hpp"
#include "Helpers/Signal.hpp"

void Game::SequenceOrchestrator::_ready() {
  if (arrowSequence == nullptr) {
    ERR_PRINT("ArrowSequence not provided.");
    return;
  }

  if (sequences.size() < 1) {
    ERR_PRINT("No sequences provided.");
    return;
  }

  randomNumberGenerator.instantiate();
  arrowSequence->InitializeSequence(GetRandomSequence());

  CONNECT_SIGNAL(arrowSequence, "sequence_completed", &OnSequenceCompleted);
}

TypedArray<Game::Direction> Game::SequenceOrchestrator::GetRandomSequence() {
  randomNumberGenerator->randomize();

  const int index = randomNumberGenerator->randi_range(0, static_cast<int32_t>(sequences.size() - 1));
  TypedArray<Direction> sequence = cast_to<DirectionSequence>(sequences[index])->GetSequence();

  if (sequence.size() == 0) {
    ERR_PRINT("No direction in sequence.");
  }

  return sequence;
}

void Game::SequenceOrchestrator::OnSequenceCompleted() {
  arrowSequence->ClearSequence();
  arrowSequence->InitializeSequence(GetRandomSequence());
}

void Game::SequenceOrchestrator::_bind_methods() {
  BIND_PROPERTY(
    Variant::ARRAY,
    "sequences",
    GetSequences,
    SetSequences,
    PROPERTY_HINT_TYPE_STRING,
    String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":DirectionSequence")

  BIND_PROPERTY(
    Variant::OBJECT,
    "arrow_sequence",
    GetArrowSequence,
    SetArrowSequence,
    PROPERTY_HINT_NODE_TYPE,
    "ArrowSequence")
}
