#include "SequenceOrchestrator.hpp"

#include "Helpers/BindProperty.hpp"
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

  CONNECT_SIGNAL(arrowSequence, "sequence_completed", &SequenceOrchestrator::OnSequenceCompleted);
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
  BIND_ARRAY_PROPERTY(
    "sequences",
    &SequenceOrchestrator::GetSequences,
    &SequenceOrchestrator::SetSequences,
    String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":DirectionSequence")

  BIND_OBJECT_PROPERTY(
    "arrow_sequence",
    &SequenceOrchestrator::GetArrowSequence,
    &SequenceOrchestrator::SetArrowSequence,
    "ArrowSequence")
}
