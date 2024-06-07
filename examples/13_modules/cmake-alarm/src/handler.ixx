export module Handler;

export import Alarms;

export namespace Handler {
  void cancel(typename Alarms::Alarm& alarm);
}
