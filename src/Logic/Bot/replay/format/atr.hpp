/*
ChatGPT ahh code, idk how it got here like actually


# macro.ast - Custom macro definitions for AST processing

# Define a macro for marking replay events
macro REPLAY_EVENT(name, args) {
    struct name {
        args;
    };
}

# Define a macro for serializing replay data
macro SERIALIZE_REPLAY(type) {
    void serialize(const type& obj, std::ostream& out);
    void deserialize(type& obj, std::istream& in);
}

# Example usage:
# REPLAY_EVENT(JumpEvent, int frame; float position;)
# SERIALIZE_REPLAY(JumpEvent)
*/