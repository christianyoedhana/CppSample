Knowing what not to do is just as important as knowing what to do. This is another QREF to demonstrate bad coding.
Apart from the obvious, like returning pointers of temporaries, of local thread variables, calling delete on a dereferenced std::unique_ptr object,
these are the subtly bad code.