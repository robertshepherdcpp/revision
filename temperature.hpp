template<auto Particles, auto Speed>
struct particles
{
    constexpr auto increase_collisions()
    {
        /*collide the particles more frequently*/
        return particles<Particles, Speed>{};
    }
};

template<auto Temp>
struct by
{};

template<auto temp, auto a, auto b>
constexpr auto give_more_energy_to_particles(particles<a, b>)
{
    return particles<a, b + temp>{};
    /*
      Just to show that particles gain more energy this is not
      accurate! std::underfined_behaviour()!
    */
}

template<auto a, auto b>
constexpr auto make_more_frequent_success_collisions(particles<a, b> x)
{
    // make more collions between the particles
    return x.increase_collisions();
}

template<auto Part, auto Speed, auto Temp>
constexpr auto increase_temperature(particles<Part, Speed> p, by<Temp>)
{
    constexpr auto current = give_more_energy_to_particles<Temp>(p);
    constexpr auto now = make_more_frequent_success_collisions(current);
}

template<auto A, auto B>
constexpr auto has_activation_energy(particles<A, B> x)
{
    if constexpr (B == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

int main()
{
    particles<100, 0> particles_collection{};
    static_assert(!has_activation_energy(particles_collection), "Got 0 Energy!");
    increase_temperature(particles_collection, by<14>{});
}