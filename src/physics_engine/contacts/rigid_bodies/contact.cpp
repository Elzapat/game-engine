#include "physics_engine/contacts/rigid_bodies/contact.hpp"

Contact::Contact(
    std::shared_ptr<RigidBody> _first,
    std::shared_ptr<RigidBody> _second,
    float _friction,
    float _restitution
) :
    first(_first),
    second(_second),
    friction(_friction),
    restitution(_restitution) {}
