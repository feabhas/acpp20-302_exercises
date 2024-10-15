module;
#include <iosfwd>

export module Alarms;

export namespace Alarms 
{
  class Alarm 
  {
  public:
    enum class Type {unknown, warning, error, critical};
    Alarm() = default;
    Alarm(Type type, bool status);
    void reset();
    friend std::ostream& operator<< (std::ostream& out, const Alarm& alarm);
  private:
    Type type {};
    bool status {};
  };
}
