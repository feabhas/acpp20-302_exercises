export module Evening;

export namespace evening{
  const char* greeting();
}

module :private;

const char *message = "Good evening";

namespace evening {
  const char* greeting() { 
    return message; 
  }
}