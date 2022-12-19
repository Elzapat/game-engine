#ifndef CONTACT_RESOLVER_HPP
#define CONTACT_RESOLVER_HPP

#include <vector>

#include "contact.hpp"
#include "physics_engine/rigid_body.hpp"
#include "time.hpp"

class ContactResolver {
    public:
        void resolve_contacts(std::vector<Contact> contacts);
        int iterations = 1;

    private:
        void prepare_contacts(std::vector<Contact>& contacts);
        void adjust_positions(std::vector<Contact>& contacts);
        void adjust_velocities(std::vector<Contact>& contacts);
        void update_penetrations();
};

#endif  // CONTACT_RESOLVER_HPP
