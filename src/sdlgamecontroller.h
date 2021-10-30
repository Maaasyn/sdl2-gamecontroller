#include <SDL2/SDL.h>
#include <SDL2/SDL_gamecontroller.h>
#include <napi.h>
#include <map>
#include <thread>

constexpr size_t ARRAY_LENGTH = 10;

class SdlGameController : public Napi::ObjectWrap<SdlGameController> {
 public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  SdlGameController(const Napi::CallbackInfo& info);

 private:
  static Napi::FunctionReference constructor;

  // Node methods
  Napi::Value pollEvents(const Napi::CallbackInfo& info);
  void enableGyroscope(const Napi::CallbackInfo& info);
  void enableAccelerometer(const Napi::CallbackInfo& info);
  void rumble(const Napi::CallbackInfo& info);
  void rumbleTriggers(const Napi::CallbackInfo& info);
  void setLeds(const Napi::CallbackInfo& info);

  // Internal methods
  bool SendEffect(SDL_GameController* gamecontroller);
  void RemoveController(const SDL_JoystickID which);
  int NextPlayer();

  static bool sdlInit;

  std::map<SDL_JoystickID, SDL_GameController*> gamecontrollers;
};
