#pragma once
//This is a rip from cppreference.com on possible implementation of std::unique. What fascinates me is the use of && early termination in the
//algorithm. If && evaluates all of its predicates, this algorithm won't work
template<class ForwardIt>
ForwardIt unique(ForwardIt first, ForwardIt last)
{
    if (first == last)
        return last;

    ForwardIt result = first;
    while (++first != last) {
        if (!(*result == *first) && ++result != first) {
            *result = std::move(*first);
        }
    }
    return ++result;
}
