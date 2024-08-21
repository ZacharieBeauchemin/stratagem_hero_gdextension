//
// Created by Zach on 2024-08-17.
//

#include "SequenceOrchestrator.hpp"

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

  if (arrowSequence->connect("sequence_completed", callable_mp(this, &OnSequenceCompleted)) != OK) {
    ERR_PRINT("Failed to connect sequence_completed signal.");
  }
}

TypedArray<int> Game::SequenceOrchestrator::GetRandomSequence() {
  randomNumberGenerator->randomize();

  const int index = randomNumberGenerator->randi_range(0, static_cast<int32_t>(sequences.size() - 1));
  TypedArray<int> sequence = cast_to<DirectionSequence>(sequences[index])->GetSequence();

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
  ClassDB::bind_method(D_METHOD("set_sequences", "sequences"), &SequenceOrchestrator::SetSequences);
  ClassDB::bind_method(D_METHOD("get_sequences"), &SequenceOrchestrator::GetSequences);
  const String sequences_hint =
      String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":DirectionSequence";
  ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "sequences", PROPERTY_HINT_TYPE_STRING, sequences_hint),
               "set_sequences",
               "get_sequences");

  ClassDB::bind_method(D_METHOD("set_arrow_sequence", "arrow_sequence"), &SequenceOrchestrator::SetArrowSequence);
  ClassDB::bind_method(D_METHOD("get_arrow_sequence"), &SequenceOrchestrator::GetArrowSequence);
  ADD_PROPERTY(
    PropertyInfo(Variant::OBJECT, "arrow_sequence", PROPERTY_HINT_NODE_TYPE, "ArrowSequence"),
    "set_arrow_sequence",
    "get_arrow_sequence");
}
