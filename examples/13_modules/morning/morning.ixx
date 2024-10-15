export module Morning;

export namespace morning {
  const char* greeting();
}

module :private;

const char *message = "Good morning";

namespace morning {
  const char* greeting() { 
    return message; 
  }
}