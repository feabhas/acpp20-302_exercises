export module Templates;

export import Constraints;

export template <Resetable T> 
void do_reset(T& object) {
  object.reset();
}
