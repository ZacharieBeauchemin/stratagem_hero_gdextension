//
// Created by Zach on 2024-08-17.
//

#include "SequenceOrchestrator.hpp"

using namespace godot;

void initializer(const ModuleInitializationLevel level) {
  if (level != MODULE_INITIALIZATION_LEVEL_SCENE) {
    return;
  }

  ClassDB::register_runtime_class<Game::DirectionSequence>();
  ClassDB::register_runtime_class<Game::DirectionArrow>();
  ClassDB::register_runtime_class<Game::ArrowSequence>();
  ClassDB::register_runtime_class<Game::SequenceOrchestrator>();
}

void terminator(ModuleInitializationLevel _) {}

extern "C" {
  GDExtensionBool entrypoint(
    const GDExtensionInterfaceGetProcAddress getProcAddress,
    const GDExtensionClassLibraryPtr library,
    GDExtensionInitialization* initialization
  ) {
    const GDExtensionBinding::InitObject init_obj(getProcAddress, library, initialization);

    init_obj.register_initializer(initializer);
    init_obj.register_terminator(terminator);
    init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

    return init_obj.init();
  }
}
