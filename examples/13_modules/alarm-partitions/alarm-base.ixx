module;
#include <iosfwd>
export module Alarm:Base;


export namespace Alarms 
{
  class Alarm 
  {
  public:
    enum class Type {warning, error, critical};
    Alarm() = default;
    Alarm(Type type, bool status);
    void reset();
    Type get_type() const {return type;}
    friend std::ostream& operator<< (std::ostream& out, const Alarm& alarm);
  private:
    Type type {};
    bool status {};
  };
}
